/*!****************************************************************************
\file    ObjectArchetype.h
\author  Seth England (seth.england)
\date    Apr 30, 2015

\brief   Declarations for the object structure itself.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include "ComponentData.h"

namespace objectSpace
{
  struct ArchetypeObjectHeader
  {
    int32 numComponents;
    int32 nameLength;
    int32 byteLength;

    ArchetypeObjectHeader(int32 numComponents_ = 0, int32 nameLength_ = 0, int32 byteLength_ = 0) :
      numComponents(numComponents_),
      byteLength(byteLength_),
      nameLength(nameLength_){}
  };

  struct ArchetypeComponentHeader
  {
    int32 size;
    char8 type;

    ArchetypeComponentHeader(int32 size_ = 0, componentSpace::Component_Type_ type_ = componentSpace::Component_Type_::Undefined_) :
      size(size_),
      type(type_){}
  };

  struct ObjectArchetype
  {
    char8 *data;
    int32 byteSize;
  };
}