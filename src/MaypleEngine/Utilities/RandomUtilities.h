/*!****************************************************************************
\file    RandomUtilities.h
\author  Kaden Nugent (kaden.n)
\date    Nov 20, 2015

\brief   Contains some random functions.
         I don't know what they are, it's random.

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
*         Dependencies
*/

/*=================================
*      Forward Declarations
*/

namespace utilities
{
  // Random number [0, 1]
  float RandomReal();

  // Random number between a given range [low, high]
  float RandomRange(float low, float high);

  // Random number following a bell curve with a mean and standard deviation
  float RandomGaussian(float mean, float deviation);

  // Random number following a bell curve clamped to [0, 1]
  float RandomGaussianReal();

} // utilities
