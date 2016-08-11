/*!****************************************************************************
\file    Math.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Basic typedefs for simple math

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         include guard
*/
#pragma once

/*=================================
*      Forward Declarations
*/

namespace utilities
{
  float RandomLowHigh(float low, float high);
  float Clamp(float value, float low, float high);
}
