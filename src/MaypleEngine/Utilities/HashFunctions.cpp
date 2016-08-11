/*!****************************************************************************
\file    HashFunctions.cpp
\author  Seth England (seth.england)
\date    Apr 15, 2015

\brief   Slot map data structure.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"
#include "HashFunctions.h"
#include "VectorMath.h"

namespace utilities
{
  int32 HashVectorType(VectorType const &value)
  {
    f32 h1 = (f32)73856093;
    f32 h2 = (f32)19349663; 
    f32 h3 = (f32)83492791;

    f32 buffer[4];
    math::GetElementsVectorType(value, buffer);

    f32 bH1 = buffer[0] * h1;
    f32 bH2 = buffer[1] * h2;
    f32 bH3 = buffer[2] * h3;
    int32 n = *(int32 *)&bH1 ^ *(int32 *)&bH2 ^ *(int32 *)&bH3;

    return n;
  }
}