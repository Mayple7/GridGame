/*!****************************************************************************
\file    TransformComponentData.cpp
\author  Kaden Nugent (kaden.n)
\date    May 20, 2015

\brief	 Data for transform components.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

////////////////////////////////////////////////////////////////////////// DEPENDENCIES

// Standard include
#include "stdinc.h"

// This component's header files
#include "TransformComponentData.h"

// Managers
#include "ManagerLocator.h"

// General component data
#include "ComponentDataLocator.h"
#include "ComponentData.h"

/*=================================
*            Locals
*/
namespace 
{
	/*=================================
	*       Local Variables
	*/
  uint32 c_translationOffsetMaxDepth = 100;
	
	/*=================================
	*       Local Functions
	*/
	
}

////////////////////////////////////////////////////////////////////////// MACROS

////////////////////////////////////////////////////////////////////////// DECLARATIONS

//START_DECLARE_COMPONENT_DEFINITION(coreSpace, Transform, transform)
void InitializeTransformComponentData(void);

namespace
{
  int32 s_componentIndex = componentSpace::ComponentDataLocator::RegisterComponent(InitializeTransformComponentData);
}

void InitializeTransformComponentData(void)
{
  auto *data = (coreSpace::CONCATENATE(Transform, ComponentData)*)malloc(sizeof(coreSpace::CONCATENATE(Transform, ComponentData)));
  new (data)coreSpace::CONCATENATE(Transform, ComponentData)();
  componentSpace::ComponentDataLocator::SetDataWithIndex(data, s_componentIndex);
}

template <>
coreSpace::TransformComponentData *componentSpace::ComponentDataLocator::GetData<coreSpace::TransformComponentData>()
{
  return static_cast<coreSpace::TransformComponentData *>(componentSpace::ComponentDataLocator::GetDataWithIndex(s_componentIndex));
}

namespace coreSpace
{
  extern int TransformAutoReg = 0;
  int TransformAutoReg2 = ++TransformAutoReg;
  hndl TransformComponentData::GetComponent(hndl objectHandle)
  {
    if (!m_objectToComponentHandle.IsAlive(objectHandle))
    {
      return INVALID_HANDLE;
    }
    return m_objectToComponentHandle[objectHandle];
  }

  hndl TransformComponentData::GetObject(hndl componentHandle)
  {
    return m_componentToObjectHandle[componentHandle];
  }

  hndl TransformComponentData::Create(hndl objectHandle)
  {
    hndl componentHandle;
    _CreateTransform(&componentHandle);
    _AddToObject(objectHandle, componentHandle);
    return componentHandle;
  }

  void TransformComponentData::Destroy(hndl objectHandle)
  {
    hndl componentHandle = GetComponent(objectHandle);
    if (componentHandle >= 0)
    {
      _DestroyTransform(&componentHandle);
      _RemoveFromObject(objectHandle, componentHandle);
    }
  }

  int32 TransformComponentData::GetNumberOfTransform(TransformComponentData *transformData, hndl objectHandle)
  {
    if (transformData->m_objectToComponentHandle.IsAlive(objectHandle))
      return 1;
    return 0;
  }

  void TransformComponentData::_AddToObject(hndl objectHandle, hndl componentHandle)
  {
    if (objectHandle >= m_objectToComponentHandle.GetCapacity())
    {
      m_objectToComponentHandle.Expand(2 * objectHandle);
    }
    m_objectToComponentHandle[objectHandle] = componentHandle;
    m_objectToComponentHandle.SetAlive(objectHandle, true);
    if (componentHandle >= m_componentToObjectHandle.GetCapacity())
    {
      m_componentToObjectHandle.Expand(2 * componentHandle);
    }
    m_componentToObjectHandle[componentHandle] = objectHandle;
    m_componentToObjectHandle.SetAlive(componentHandle, true);
  }

  void TransformComponentData::_RemoveFromObject(hndl objectHandle, hndl componentHandle)
  {
    m_objectToComponentHandle.SetAlive(objectHandle, false);
    m_componentToObjectHandle.SetAlive(componentHandle, false);
    m_objectToComponentHandle[objectHandle] = -1;
    m_componentToObjectHandle[componentHandle] = -1;
  }

  hndl TransformComponentData::GetComponentStatic(hndl objectHandle)
  {
    return GET_COMPONENT_DATA(coreSpace::TransformComponentData)->GetComponent(objectHandle);
  }

  void TransformComponentData::AddToObjectStatic(TransformComponentData *transformData, hndl objectHandle, hndl componentHandle)
  {
    transformData->_AddToObject(objectHandle, componentHandle);
  }

  void TransformComponentData::_CreateTransform(hndl *componentHandle)
  {
    ConstructTransform(componentHandle);
  }

  void TransformComponentData::_DestroyTransform(hndl *componentHandle)
  {
    DestructTransform(componentHandle);
  }

  START_DECLARE_COMPONENT_CONSTRUCTION(coreSpace, Transform, transform)
    INITIALIZE_SLOT(position, transform, MaypleMath::Vector2(0.0f, 0.0f));
    INITIALIZE_SLOT(scale, transform, MaypleMath::Vector2(1.0f, 1.0f));
    INITIALIZE_SLOT(rotation, transform);
  END_DECLARE_COMPONENT_CONSTRUCTION

  START_DECLARE_COMPONENT_DESTRUCTION(coreSpace, Transform, transform)
    UNINITIALIZE_SLOT(position, transform);
    UNINITIALIZE_SLOT(scale, transform);
    UNINITIALIZE_SLOT(rotation, transform);
  END_DECLARE_COMPONENT_DESTRUCTION

  // Constructor
  TransformComponentData::TransformComponentData(void)
  {
  }

  hndl TransformComponentData::AttachComponent(hndl objectHandle)
  {
    hndl newComponent = Create(objectHandle);

    // Check for starting values

    // Position
    SetPosition(newComponent, Vector2(0, 0));
    
    // Scale
    SetScale(newComponent, Vector2(1, 1));
    
    // Rotation
    SetRotation(newComponent, 0);
    
    return newComponent;
  }

  void TransformComponentData::DetachComponent(hndl objectHandle)
  {
    Destroy(objectHandle);
  }

  void TransformComponentData::Print(hndl componentHandle)
  {
    Vector2 pos = GetPosition(componentHandle);
    std::cout << pos.x << ", " << pos.y << std::endl;

    f32 rot = GetRotation(componentHandle);
    std::cout << rot << "degrees" << std::endl;

    Vector2 scale = GetScale(componentHandle);
    std::cout << scale.x << ", " << scale.y << std::endl;
  }

  AUTO_GET_SET_PROPERTY_VECTOR2(Transform, Position, position);
  AUTO_GET_SET_PROPERTY_VECTOR2(Transform, Scale, scale);

  f32 TransformComponentData::GetRotation(hndl componentHandle)
  {
    return m_rotationContainer[componentHandle];
  }
  void TransformComponentData::SetRotation(hndl componentHandle, f32 newValue)
  {
    m_rotationContainer[componentHandle] = newValue;
  }
  
  Matrix3 TransformComponentData::_CalculateTransform(hndl componentHandle)
  {
    return BuildTransform(m_positionContainer[componentHandle], m_rotationContainer[componentHandle], m_scaleContainer[componentHandle]);
  }

END_DECLARE_COMPONENT_DEFINITION
