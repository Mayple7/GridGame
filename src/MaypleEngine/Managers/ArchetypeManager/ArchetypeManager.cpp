/*!****************************************************************************
\file    ArchetypeStorager.cpp
\author  Melvin Tan (melvin.tan)
\date    Oct 21, 2015

\brief   Manages Archetype data

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#include "stdinc.h"

#include "ArchetypeManager.h"
#include "Trace.h"
#include "ManagerLocator.h"
#include "FileManager.h"
#include "StringManager.h"
#include <algorithm>

void InitializeArchetypeStorager(void)
{
  managerSpace::ManagerLocator::SetArchetypeManager(new archetypeSpace::ArchetypeManager());
}

namespace archetypeSpace
{

  ArchetypeManager::ArchetypeManager()
  {
    LoadAllArchetypesFromFolders();
  }

  void ArchetypeManager::RegisterLevel(const std::string& levelName)
  {
    std::string filepath = "Serialized/Levels/" + levelName + ".json";

    std::ifstream inFile(filepath);
    Json::Value root;
    Json::Reader reader;

    if(!inFile.is_open() || reader.parse(inFile, root, false) == false)
    {
      TRACE_ERROR(false, ("Unable to open file: " + filepath).c_str());
      return;
    }

    m_archetypeStore[GET_STRING_MANAGER->Hash(levelName)] = root;
  }

  void ArchetypeManager::RegisterArchetype(const std::string& archetypeName, const Json::Value& root)
  {
    RegisterArchetype(GET_STRING_MANAGER->Hash(archetypeName), root);
  }

  void ArchetypeManager::RegisterArchetype(uint64 archetypeName, const Json::Value& root)
  {
    m_archetypeStore[archetypeName] = root;
  }

  void ArchetypeManager::RemoveArchetype(const std::string& archetypeName)
  {
    m_archetypeStore.erase(GET_STRING_MANAGER->Hash(archetypeName));
  }

  bool ArchetypeManager::IsArchetypeExist(const std::string& archetypeName) const
  {
    return m_archetypeStore.find(GET_STRING_MANAGER->Hash(archetypeName)) != m_archetypeStore.end();
  }

  const Json::Value& ArchetypeManager::GetArchetype(const std::string& archetypeName) const
  {
    size_t hash = GET_STRING_MANAGER->Hash(archetypeName);
    TRACE_ERROR(m_archetypeStore.find(hash) != m_archetypeStore.end(), "Archetype not found.");
    return m_archetypeStore.at(hash);
  }

  void ArchetypeManager::LoadAllArchetypesFromFolders()
  {
    const char* directories[] = {"Serialized/Archetypes"
      //   , "Serialized/Levels"
      //   , "Serialized/Particles"
    };

    for(const char* dir : directories)
    {
      auto filepaths = GET_FILE_MANAGER->GetFilepathsInDirectory(dir);
      uint64 filepathsSize = filepaths.size();

      for(uint64 i = 0; i < filepathsSize; ++i)
      {
        const std::string& filepath = GET_STRING_MANAGER->Hash(filepaths[i]);

        std::ifstream inFile(filepath);
        Json::Value root;
        Json::Reader reader;

        if(!inFile.is_open() || reader.parse(inFile, root, false) == false)
        {
          TRACE_ERROR(false, ("Unable to open file: " + filepath).c_str());
          continue;
        }

        // Store the archetype by its hashed name
        RegisterArchetype(GET_FILE_MANAGER->StripFilePathAndExtention(filepath), root);
      }
    }
  }

}
