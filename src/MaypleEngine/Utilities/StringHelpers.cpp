/*!****************************************************************************
\file    StringHelpers.cpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 26, 2015

\brief   Helper functions for strings

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         Dependencies
*/
#include "stdinc.h"
#include "StringHelpers.h"
/*=================================
*      Namespace Umbrella
*/
namespace utilities
{
  std::wstring ConvertToWString(const std::string &str)
  {
    std::wstring wStr(str.begin(), str.end());

    return wStr;
  }
  std::string ConvertFromWString(const std::wstring &wStr)
  {
    std::string str(wStr.begin(), wStr.end());

    return str;
  }
}
