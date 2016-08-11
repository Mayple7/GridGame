/*!****************************************************************************
\file    MathUtilities.cpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Aug 26, 2015

\brief   

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         Dependencies
*/
#include "stdinc.h"
#include "MathUtilities.h"

/*=================================
*      Forward Declarations
*/

/*=================================
*      Namespace Umbrella
*/
namespace utilities
{
  float RandomLowHigh(float low, float high)
  {
    if ((high - low) <= EPSILON)
    {
      return low;
    }

    return low + (static_cast <float> (rand()) / static_cast <float> (RAND_MAX )) * (high - low);
  }
  float Clamp(float value, float low, float high)
  {
    if (value > high)
    {
      return high;
    }
    else if (value < low)
    {
      return low;
    }
    return value;
  }
}

