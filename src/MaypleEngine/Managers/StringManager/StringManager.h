/*!****************************************************************************
\file    StringManager.h
\author  Kaden Nugent (kaden.n)
\date    May 17, 2015

\brief   Hashes strings to and from unsigned integers.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include "CustomTypes.h"    // Diesel Engine specific types
#include "ManagerLocator.h"
#include "SlotMap.h"

// Generates a hash (either uint32 OR const standard string)
#define HASH_GEN(value) \
GET_STRING_MANAGER->Hash(value)

typedef std::unordered_map<size_t, std::string> stringmap;

void InitializeStringManager(void);

namespace stringSpace
{
  class StringManager
  {
  public:
    StringManager();  // Default constructor
    ~StringManager(); // Default destructor

    size_t Hash(char const *newString); // Hash from a string to an unsigned integer
    size_t Hash(std::string const &newString); // Hash from a string to an unsigned integer
    std::string const& Hash(size_t newInt);    // Hash from an unsigned integer to a string

  private:
    std::string m_emptyString;

    // Hashes the given string to an unsigned integer
    size_t HashStringToInt(char const *newString);

    // Gets a string that was hashed from the given unsigned integer
    // If no string is found, it returns an empty string
    std::string const& HashIntToString(size_t newInt);

    stringmap m_stringMap;                // Map of hashed strings
    std::hash<std::string> m_hashFunction; // The hash function for the strings

    std::mutex m_hashMutex;
  };

} // namespace scriptSpace
