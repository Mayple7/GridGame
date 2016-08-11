/*!****************************************************************************
\file    DirectoryWatcher.cpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 26, 2015

\brief   Watches a given directory to see if any changes were made

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

/*=================================
*         Dependencies
*/
#include "stdinc.h"
#include "dirent.h"
#include "DirectoryWatcher.h"
#include "Trace.h"

/*=================================
*      Static Variables
*/
std::hash<std::string> DirectoryWatcher::m_stringHasher;
DirectoryWatcher::DirectoryMap DirectoryWatcher::m_directoryMap;
float DirectoryWatcher::m_counter = 0.0f;
float DirectoryWatcher::m_watchInterval = 0.0f;

/*=================================
*      Class Public Functions
*/
void DirectoryWatcher::SetDirectoryToWatch(const char *directoryPath,
                                           IDelegateParam1<const char*> *del)
{
  size_t hashedString = m_stringHasher(directoryPath);

  // Add to the end of the vector
  m_directoryMap[hashedString].m_directoryPath = directoryPath;
  m_directoryMap[hashedString].m_delegates.push_back(del);

  _UpdateFileMap(&m_directoryMap[hashedString], false);
}

void DirectoryWatcher::SetWatchInterval(float interval)
{
  m_watchInterval = interval;
}

void DirectoryWatcher::Update(float dt)
{
  m_counter += dt;
  if (m_counter > m_watchInterval)
  {
    m_counter = 0.0f;
    _WatchDirectories();
  }
}


void DirectoryWatcher::_WatchDirectories()
{
  for (auto &mapIt : m_directoryMap)
  {
    _UpdateFileMap(&mapIt.second, true);
  }

}

void DirectoryWatcher::_UpdateFileMap(DirectoryInfo *dInfo, bool callDels)
{
  // Iterate over all the files in the directory and detect if they have been changed
  const char *directoryPath = dInfo->m_directoryPath;

  DIR *directory = opendir(directoryPath);
  dirent *dirFile;
  if (!directory)
  {
    TRACE_ERROR(NULL,
                "Unable to open the directory: %s",
                directoryPath);
    return;
  }

  while ((dirFile = readdir(directory)))
  {
    // Skip the . and ..
    // Not sure why dirent gives you this
    if (dirFile->d_name[0] ==  '.')
     continue;

    // If the "file" is actually another directory do some nice recursion
    if (dirFile->d_type == DT_DIR)
    {
      char newPath[256];
      strcpy(newPath, dInfo->m_directoryPath);
      strcat(newPath, dirFile->d_name);
      strcat(newPath, "/");

      // Create a new directory info for the subdirectory
      DirectoryInfo dInfoNew;
      dInfoNew.m_delegates = dInfo->m_delegates;
      dInfoNew.m_fileMap = dInfo->m_fileMap;
      dInfoNew.m_directoryPath = newPath;

      _UpdateFileMap(&dInfoNew, callDels);

      // Add to the updates to the file map
      dInfo->m_fileMap = dInfoNew.m_fileMap;
    }
    // Otherwise check if it has been updated
    else
    {
      std::string filePath = directoryPath;
      filePath += dirFile->d_name;

      //std::hash<const char *> hasher;
      //size_t otherhash = hasher(filePath.c_str());
      size_t fileHash = m_stringHasher(filePath);

      _UpdateFileInfo(dInfo, fileHash, filePath, callDels);
    }
  }

  closedir(directory);

}

void DirectoryWatcher::_UpdateFileInfo(DirectoryInfo *dInfo, size_t fileHash, const std::string &filePath, bool callDels)
{
  WIN32_FIND_DATA newFileData;

  HANDLE handle = FindFirstFile(filePath.c_str(), &newFileData);

  if (handle == INVALID_HANDLE_VALUE)
  {
    TRACE_WARNING(NULL,
                "Dirent could locate file, but FindFirstFile couldn't.: %s",
                filePath.c_str());
    return;
  }

  // Determine if we should call dels
  if (callDels)
  {
    auto mapIt = dInfo->m_fileMap.find(fileHash);
    // Always call dels on new files
    if (mapIt == dInfo->m_fileMap.end())
    {
      _CallDels(dInfo, filePath, nullptr, &newFileData.ftLastWriteTime);
    }
    else
    {
      _CallDels(dInfo, filePath, &mapIt->second.m_lastUpdated, &newFileData.ftLastWriteTime);
    }
  }

  // Update the file data
  FileInfo *fileInfo = &dInfo->m_fileMap[fileHash];
  fileInfo->m_lastUpdated = newFileData.ftLastWriteTime;
  SYSTEMTIME time;
  FileTimeToSystemTime(&newFileData.ftLastWriteTime, &time);
  fileInfo->m_systemLastUpdated = time;
}
void DirectoryWatcher::_CallDels(DirectoryInfo *dInfo, const std::string &filePath,  FILETIME *oldTime, const FILETIME *newTime)
{
  // Always call dels on new files
  if (!oldTime)
  {
    _CallDelsDetail(dInfo, filePath);
    return;
  }

  if (CompareFileTime(oldTime, newTime))
  {
    _CallDelsDetail(dInfo, filePath);
  }

}

void DirectoryWatcher::_CallDelsDetail(DirectoryInfo *dInfo, const std::string &filePath)
{
  for (size_t i = 0; i < dInfo->m_delegates.size(); ++i)
  {
    dInfo->m_delegates[i]->SetParam1(filePath.c_str());
    dInfo->m_delegates[i]->Execute();
  }
}

