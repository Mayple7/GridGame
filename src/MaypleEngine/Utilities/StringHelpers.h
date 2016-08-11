/*!****************************************************************************
\file    StringHelpers.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Helper functions for strings

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

/*=================================
*      Namespace Umbrella
*/
namespace utilities
{

  /*=================================
  *         Functions
  */
  // Not very good should be replaced
  std::wstring ConvertToWString(const std::string &str);
  std::string ConvertFromWString(const std::wstring &wStr);

  struct StringCompare
  {
    bool operator()(char const *a, char const *b)
    {
      int offset = 0;
      return std::strcmp(a, b) < 0;
    }
  };

  // djb2 hash
  struct StringHash
  {
    size_t operator()(char const *string)
    {
      unsigned long hash = 5381;
      char c;

      while (c = *string++)
        hash = ((hash << 5) + hash) + c;

      return hash;
    }
  };
}
