/*!****************************************************************************
\file    UpdateTransform.cpp
\author  Kaden Nugent (kaden.n)
\date    May 20, 2015

\brief	 Update for the transform component.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

////////////////////////////////////////////////////////////////////////// DEPENDENCIES

// Standard include
#include "stdinc.h"

// This component's header files
#include "UpdateTransforms.h"
#include "TransformComponentData.h"

// General component data
#include "ComponentDataLocator.h"

// Math libraries
#include "VectorMath.h"
#include "MatrixMath.h"
#include "QuaternionMath.h"

// Grafix
#include "PRenderObject.h"
#include "Prism.h"

// Manager locator
#include "ManagerLocator.h"

// Job related
#include "JobManager.h"
#include "JobHelpers.h"

#include "TimeManager.h"
////////////////////////////////////////////////////////////////////////// DECLARATIONS

// Refreshes the list of alive components
DECLARE_JOB(PushAliveTransforms)
{
  START_JOB;

  auto *transformData = GET_TRANSFORM_DATA;
  auto &transformPositions = transformData->m_positionContainer;
  auto &aliveTransforms = transformData->m_aliveTransform;

  aliveTransforms.Clear();

  int capacity = transformPositions.GetCapacity();

  for (int i = 0; i < capacity; ++i)
  {
    if (transformPositions.IsAlive(i))
    {
      aliveTransforms.PushBack(i);
    }
  }

  END_JOB;
}


// Helper job for this component's update
DECLARE_JOB(UpdateTransformsHelper)
{
  START_JOB;

  auto *jobData = GET_JOB_DATA(jobSpace::JobDataSplitStruct);
  auto *transformData = GET_TRANSFORM_DATA;
  int32 *transformHandles = (int32 *)jobData->data;
  int32 numTransforms = jobData->numData;

  // For now just use identity for scalar TODO(kdot): Add the actual scale here
  VectorType inverseTranslationScalar = math::CreateVectorType(1, 1, 1, -1);
  VectorType identityScalar = math::CreateVectorType(1, 1, 1, 1);

  // Loop through all existing components
  for (int i = 0; i < numTransforms; ++i)
  {
    int32 transformHandle = transformHandles[i];
    MatrixType trans = math::CreateTranslationMatrixType(transformData->m_positionContainer[transformHandle]);
    VectorType quat = transformData->m_rotationContainer[transformHandle];
    MatrixType rot = math::CreateMatrixType(quat);
    MatrixType scale = math::CreateScaleMatrixType(transformData->m_scaleContainer[transformHandle]);
    MatrixType result = MxM(trans, MxM(rot, scale));

    transformData->m_transformMatrixContainer[transformHandle] = result;
    
    transformData->m_rotationMatrixContainer[transformHandle] = rot;
  }

  END_JOB;
}

// Spawns jobs to update the component
DECLARE_JOB(UpdateTransforms)
{
  START_JOB;

  auto *transformData = GET_TRANSFORM_DATA;
  int numTransforms = transformData->m_aliveTransform.GetSize();
  int32 *transformHandles = &transformData->m_aliveTransform[0];
  int32 numWorkers = jobManager->GetNumberOfWorkers();

  jobSpace::JobDataSplitStruct *splitHelperData = (jobSpace::JobDataSplitStruct *)alloca(sizeof(jobSpace::JobDataSplitStruct) * numWorkers);
  jobSpace::DataTransform *splitHelperTransforms = (jobSpace::DataTransform *)alloca(sizeof(jobSpace::DataTransform) * numWorkers);
  int32 helpersSpawned = 0;
  SplitData<int32>(numWorkers, transformHandles, numTransforms, UpdateTransformsHelper, splitHelperData, splitHelperTransforms, &helpersSpawned);

  jobSpace::Job *transformUpdateHelperJobs = INIT_JOBS_DATA_ARRAY(splitHelperData, splitHelperTransforms, helpersSpawned);

  jobSpace::JobCounter counter;
  ENQUEUE_JOBS_AND_WAIT(transformUpdateHelperJobs, helpersSpawned, counter);

  END_JOB;
}
