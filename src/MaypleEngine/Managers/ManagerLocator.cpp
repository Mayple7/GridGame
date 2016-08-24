/*!****************************************************************************
\file    ManagerLocator.cpp
\author  Dan Muller

\brief   Manager locator to handle all the systems

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"
#include "ManagerLocator.h"

namespace managerSpace
{

  ////////////////////////////////////////////////////////////////////////// SETTERS
  void ManagerLocator::SetTimeManager(timeSpace::TimeManager *timeManager)
  {
    m_timeManager = timeManager;
  }

  void ManagerLocator::SetStringManager(stringSpace::StringManager *stringManager)
  {
    m_stringManager = stringManager;
  }

  void ManagerLocator::SetDebugManager(debugSpace::DebugManager *debugManager)
  {
    m_debugManager = debugManager;
  }

  void ManagerLocator::SetObjectManager(objectSpace::ObjectManager *objectManager)
  {
    m_objectManager = objectManager;
  }

  void ManagerLocator::SetFileManager(fileSpace::FileManager *fileManager)
  {
    m_fileManager = fileManager;
  }

  void ManagerLocator::SetArchetypeManager(archetypeSpace::ArchetypeManager *archetypeManager)
  {
    m_archetypeManager = archetypeManager;
  }

  ////////////////////////////////////////////////////////////////////////// GETTERS

  timeSpace::TimeManager* ManagerLocator::GetTimeManager(void)
  {
    return m_timeManager;
  }

  stringSpace::StringManager* ManagerLocator::GetStringManager(void)
  {
    return m_stringManager;
  }

  debugSpace::DebugManager* ManagerLocator::GetDebugManager(void)
  {
    return m_debugManager;
  }

  objectSpace::ObjectManager* ManagerLocator::GetObjectManager(void)
  {
    return m_objectManager;
  }

  fileSpace::FileManager* ManagerLocator::GetFileManager(void)
  {
    return m_fileManager;
  }

  archetypeSpace::ArchetypeManager* ManagerLocator::GetArchetypeManager(void)
  {
    return m_archetypeManager;
  }

  ////////////////////////////////////////////////////////////////////////// PREDECLARATIONS
  timeSpace::TimeManager *ManagerLocator::m_timeManager = nullptr;
  stringSpace::StringManager *ManagerLocator::m_stringManager = nullptr;
  debugSpace::DebugManager *ManagerLocator::m_debugManager = nullptr;
  objectSpace::ObjectManager *ManagerLocator::m_objectManager = nullptr;
  fileSpace::FileManager *ManagerLocator::m_fileManager = nullptr;
  archetypeSpace::ArchetypeManager* ManagerLocator::m_archetypeManager = nullptr;
}