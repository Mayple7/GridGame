/*!****************************************************************************
\file    HashStringMap.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   A wrapper around std map in order to have more efficient string 
         searching

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
*         Template Classes
*/
template<typename T>
class HashStringMap
{
/*=================================
*      Class Variables
*/
public:
  static std::hash<std::string> m_sHash;
private:
  typedef std::unordered_map<size_t, T> THashStringMap;
  THashStringMap m_cArchMap;

/*=================================
*      Class Functions
*/
public:
  HashStringMap()
  : m_cArchMap()
  {
    m_cArchMap.max_load_factor(0.5f);
  }
  HashStringMap(const HashStringMap<T> &rhs)
  : m_cArchMap(rhs.m_cArchMap)
  {
  }

  ~HashStringMap()
  {

  }

  HashStringMap<T> &operator = (const HashStringMap<T> &rhs)
  {
    if (this == &rhs)
    {
      return *this;
    }
    m_cArchMap = rhs.m_cArchMap;
    return *this;
  }
  typename THashStringMap::iterator find(const std::string &rName)
  {
    return m_cArchMap.find(m_sHash(rName));
  }
  typename THashStringMap::iterator find(size_t val)
  {
    return m_cArchMap.find(val);
  }
  typename THashStringMap::const_iterator find(const std::string &rName) const
  {
    return m_cArchMap.find(m_sHash(rName));
  }
  typename THashStringMap::const_iterator find(size_t val) const
  {
    return m_cArchMap.find(val);
  }
  typename THashStringMap::iterator begin()
  {
    return m_cArchMap.begin();
  }
  typename THashStringMap::const_iterator begin() const
  {
    return m_cArchMap.begin();
  }
  typename THashStringMap::iterator end()
  {
    return m_cArchMap.end();
  }
  typename THashStringMap::const_iterator end() const
  {
    return m_cArchMap.end();
  }
  void erase(const std::string &rName)
  {
    m_cArchMap.erase(m_sHash(rName));
  }
  void erase(size_t hashedName)
  {
    m_cArchMap.erase(hashedName);
  }
  void clear()
  {
    m_cArchMap.clear();
  }
  T &operator[](size_t val)
  {
    return m_cArchMap[val];
  }
  T &operator[](const std::string &rName)
  {
    return m_cArchMap[m_sHash(rName)];
  }

  const T &operator[](const std::string &rName) const
  {
    size_t hash = m_sHash(rName);
    auto mapIt = m_cArchMap.find(hash);
    return mapIt->second;
  }

  std::pair<typename THashStringMap::iterator, bool> emplace(size_t val, T pObject)
  {
    return m_cArchMap.emplace(val, pObject);
  }
  std::pair<typename THashStringMap::iterator, bool> emplace(const std::string &rArchFileName, T pObject)
  {
    return m_cArchMap.emplace(m_sHash(rArchFileName), pObject);
  }

  size_t HashString(const std::string &rString)
  {
    return m_sHash(rString);
  }

private:
  // Intentionally private
};

/*=================================
*    Static Member Instantiation
*/
template <typename T>
std::hash<std::string> HashStringMap<T>::m_sHash;

