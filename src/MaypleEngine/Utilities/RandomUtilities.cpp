/*!****************************************************************************
\file    RandomUtilities.cpp
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
*         Dependencies
*/
#include "stdinc.h"
#include "RandomUtilities.h"

#include <random>

/*=================================
*      Forward Declarations
*/

/*=================================
*      Namespace Umbrella
*/
namespace utilities
{
  // Random number [0, 1]
  float RandomReal()
  {
    std::random_device rd; // Seed for the PRNG
    std::mt19937 generator(rd());
    std::uniform_real_distribution<float> distribution(0, 1);
    return distribution(generator);
  }

  // Random number between a given range [low, high]
  float RandomRange(float low, float high)
  {
    if ((high - low) <= EPSILON)
      return low;

    return low + RandomReal() * (high - low);
  }

  // Random number following a bell curve with a mean and standard deviation
  float RandomGaussian(float mean, float deviation)
  {
    std::random_device rd; // Seed for the PRNG
    std::mt19937 generator(rd());
    std::normal_distribution<float> distribution(mean, deviation);

    return distribution(generator);
  }

  // Random number following a bell curve clamped to [0, 1]
  float RandomGaussianReal()
  {
    std::random_device rd; // Seed for the PRNG
    std::mt19937 generator(rd());
    std::normal_distribution<float> distribution(0.5f, 0.15f);

    // Get a distribution that is in the range [0, 1]
    float finalDistribution;

    do
      finalDistribution = distribution(generator);
    while (finalDistribution < 0.0f || finalDistribution > 1.0f);

    return finalDistribution;
  }

} // utilities
