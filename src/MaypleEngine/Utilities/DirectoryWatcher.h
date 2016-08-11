/*!****************************************************************************
\file    DirectoryWatcher.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Watches a given directory to see if any changes were made

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         Include Guard
*/
#pragma once

/*=================================
*         Dependencies
*/
#include <map>
#include <vector>
#include <functional>
#include "IDelegateParam1.h"

/*=================================
*      Forward Declarations
*/
class IDelegate;

/*=================================
*         Classes
*/
class DirectoryWatcher
{
  /*=================================
  *       Type Definitions
  */
public:
  struct FileInfo
  {
    FILETIME m_lastUpdated;
    SYSTEMTIME m_systemLastUpdated;
  };
  struct DirectoryInfo
  {
    const char *m_directoryPath;
    std::vector<IDelegateParam1<const char*> *> m_delegates;
    std::map<size_t, FileInfo> m_fileMap;
  };

  // Need a map of path which contains a vector of delegates to call
  // when we find an updated file.
  typedef std::map<size_t, DirectoryInfo> DirectoryMap;
  /*=================================
  *         Class Variables
  */
private:

  static std::hash<std::string> m_stringHasher;
  static DirectoryMap m_directoryMap;
  static float m_counter;
  static float m_watchInterval;

  /*=================================
  *         Class Functions
  */
public:
  static void SetDirectoryToWatch(const char *directoryPath,
                                  IDelegateParam1<const char*> *del);
  static void SetWatchInterval(float interval);
  static void Update(float dt);

private:
  static void _WatchDirectories();
  static void _UpdateFileMap(DirectoryInfo *dInfo, bool callDels);
  static void _UpdateFileInfo(DirectoryInfo *dInfo, size_t fileHash, const std::string &filePath, bool callDels);
  static void _CallDels(DirectoryInfo *dInfo, const std::string &filePath, FILETIME *oldTime, const FILETIME *newTime);
  static void _CallDelsDetail(DirectoryInfo *dInfo, const std::string &filePath);
  
  DirectoryWatcher();
  ~DirectoryWatcher();

};

