/*!****************************************************************************
\file    ComponentDataLocator.cpp
\author  Seth England (seth.england)
\date    May 4, 2015

\brief   I don't want to fill this out anymore

\par     Checked By:

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include "stdinc.h"

// Component's coresponding data
#include "TransformComponentData.h"
#include "DataContainerComponentData.h"

// This file's header
#include "ComponentDataLocator.h"


namespace componentSpace
{
  // Initialize to 0
  void* ComponentDataLocator::s_createFuncs[MAX_COMPONENTS] = {nullptr};
  void *ComponentDataLocator::s_components[MAX_COMPONENTS] = {nullptr};
  int32 ComponentDataLocator::s_componentCount = 0;

  int32 ComponentDataLocator::RegisterComponent(void* createFunc)
  {
    // Can't use Error if as not init before load time
    //assert(s_componentCount + 1 < MAX_COMPONENTS);
    //             "Index is greater than max components\n");
    s_createFuncs[s_componentCount] = createFunc;

    return s_componentCount++;
  }

  void ComponentDataLocator::InitializeComponents(void)
  {
    for(int i = 0; i < s_componentCount; ++i)
    {
      s_createFuncs[i];
    }
  }
}
