/*!****************************************************************************
\file    TimeUtilities.cpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Mar 03, 2016

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
#include <string>
#include "TimeUtilities.h"
#include "CustomTypes.h"

/*=================================
*      Forward Declarations
*/

/*=================================
*      Namespace Umbrella
*/
namespace utilities
{

  /*=================================
  *      Class Public Functions
  */
  void TimeStandardFormat(float inputSeconds, std::string &outString)
  {
    float temp = inputSeconds / 60.0f;
    // 
    float minutes = std::floor(temp);
    // Seconds are the remainder portion when converted to minutes
    float seconds = temp - minutes;
    seconds *= 60.0f;
    temp = minutes / 60.0f;
    float hours = std::floor(temp);
    minutes = temp - hours;
    minutes *= 60.0f;
    std::string result;
    outString = std::to_string(static_cast<uint32>(hours));
    outString += "h ";
    outString += std::to_string(static_cast<uint32>(minutes));
    outString += "m ";
    outString += std::to_string(static_cast<uint32>(seconds));
    outString += "s ";
  }

  /*=================================
  *     Class Protected Functions
  */


  /*=================================
  *     Class Private Functions
  */

}

