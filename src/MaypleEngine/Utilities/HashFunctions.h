/*!****************************************************************************
\file    HashFunctions.h
\author  Seth England (seth.england)
\date    Apr 15, 2015

\brief   Slot map data structure.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include "CustomTypes.h"

namespace utilities
{
  template<typename T>
  int32 GenericPODHash(T const &value)
  {
    T h1 = (T)0x8da6b343;
    T h2 = (T)0xd8163841;
    T h3 = (T)0xcb1ab31f;

    int32 n = value * h1 + value * h2 + value * h3;

    return n;
  }

  int32 HashVectorType(VectorType const &value);
}