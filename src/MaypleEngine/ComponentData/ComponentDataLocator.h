/*!****************************************************************************
\file    ComponentDataLocator.h
\author  Seth England (seth.england)
\date    May 4, 2015

\brief   I don't want to fill this out anymore

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

// Macro definitions for quicker creation
#include "DebugManager.h"
#include "ComponentDataHelpers.h"

#define MAX_COMPONENTS 1000

namespace coreSpace { struct TransformComponentData; struct DataContainerComponentData; }

#define GET_COMPONENT_DATA(COMPONENTNAME) componentSpace::ComponentDataLocator::GetData<COMPONENTNAME>()
#define GET_TRANSFORM_DATA componentSpace::ComponentDataLocator::GetData<coreSpace::TransformComponentData>()
 
namespace componentSpace
{
  class ComponentDataLocator
  {
    static void *s_createFuncs[MAX_COMPONENTS];
    static void *s_components[MAX_COMPONENTS];
    static int32 s_componentCount;

  public:
    static int32 RegisterComponent(void *createFunc);

    static void InitializeComponents(void);

    template <typename T>
    static T *GetData();

    inline static void SetDataWithIndex(void *data, int32 index)
    {
      s_components[index] = data;
    }

    inline static void *GetDataWithIndex(int32 index)
    {
      return s_components[index];
    }
  };
}
