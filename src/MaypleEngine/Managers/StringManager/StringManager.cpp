/*!****************************************************************************
\file    StringManager.cpp
\author  Kaden Nugent (kaden.n)
\date    May 17, 2015

\brief   Hashes strings to and from unsigned integers.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"

#include "ManagerLocator.h"
#include "StringManager.h"  // This file's declarations

void InitializeStringManager(void)
{
  managerSpace::ManagerLocator::SetStringManager(new stringSpace::StringManager());
}

namespace stringSpace
{
  ////////////////////////////////////////////////////////////////////////// PUBLIC

  // Default constructor
  StringManager::StringManager() : m_stringMap()
  {
    m_stringMap.max_load_factor(0.5f);
  }

  // Default destructor
  StringManager::~StringManager()
  {
  
  }

  // Hash from a string to an unsigned integer
  size_t StringManager::Hash(char const *newString)
  {
    return HashStringToInt(newString);
  }

  size_t StringManager::Hash(std::string const &newString)
  {
    return HashStringToInt(newString.c_str());
  }

  // Hash from an unsigned integer to a string
  std::string const& StringManager::Hash(size_t newInt)
  {
    std::lock_guard<std::mutex> lock(m_hashMutex);
    return HashIntToString(newInt);
  }

  ////////////////////////////////////////////////////////////////////////// PRIVATE

  // Hashes the given string to an unsigned integer
  size_t StringManager::HashStringToInt(char const *newString)
  {
    std::lock_guard<std::mutex> lock(m_hashMutex);

    // Generate the hash values (will be used as the key)
    size_t hashValue = m_hashFunction(newString);

    // Insert the hashed pair
    m_stringMap[hashValue] = newString;

    return hashValue;
  }

  // Gets a string that was hashed from the given unsigned integer
  // If no string is found, it returns an empty string
  std::string const& StringManager::HashIntToString(size_t newInt)
  {
    return m_stringMap[newInt];
  }

} // namespace scriptSpace
