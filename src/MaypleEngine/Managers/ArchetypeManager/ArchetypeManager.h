/*!****************************************************************************
\file    ArchetypeStorager.h
\author  Melvin Tan (melvin.tan)
\date    Oct 21, 2015

\brief   Manages Archetype data 

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#pragma once

#include "CustomTypes.h"
#include "json.h"
#include <map>

namespace archetypeSpace
{
  class ArchetypeManager
  {
  public:
    ArchetypeManager();
    ~ArchetypeManager() = default;

    // load level json be name
    void RegisterLevel(const std::string& levelName);

    // overwrites archetype if archetype exists
    void RegisterArchetype(const std::string& archetypeName, const Json::Value& root);
    void RegisterArchetype(uint64 archetypeName, const Json::Value& root);
    void RemoveArchetype(const std::string& archetypeName);

    bool IsArchetypeExist(const std::string& archetypeName) const;
    const Json::Value& GetArchetype(const std::string& archetypeName) const;

  private:
    void LoadAllArchetypesFromFolders();

    std::map<size_t, Json::Value> m_archetypeStore;
  };
}

void InitializeArchetypeManager(void);
