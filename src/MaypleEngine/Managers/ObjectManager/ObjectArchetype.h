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
    int numComponents;
    int nameLength;
    int byteLength;

    ArchetypeObjectHeader(int numComponents_ = 0, int nameLength_ = 0, int byteLength_ = 0) :
      numComponents(numComponents_),
      byteLength(byteLength_),
      nameLength(nameLength_){}
  };

  struct ArchetypeComponentHeader
  {
    int size;
    char type;

    ArchetypeComponentHeader(int size_ = 0, componentSpace::Component_Type_ type_ = componentSpace::Component_Type_::Undefined_) :
      size(size_),
      type(type_){}
  };

  struct ObjectArchetype
  {
    char *data;
    int byteSize;
  };
}