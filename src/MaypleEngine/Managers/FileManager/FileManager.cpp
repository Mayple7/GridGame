/*!****************************************************************************
\file    FileManager.cpp
\author  Seth England (seth.england)
\date    May 2, 2015

\brief   Execution manager

\par     Checked By:

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"
#include "FileManager.h"
#include "ManagerLocator.h"
#include "StringManager.h"

void InitializeFileManager(void)
{
  managerSpace::ManagerLocator::SetFileManager(new fileSpace::FileManager());
}

namespace fileSpace
{
  std::vector<size_t> FileManager::GetFilepathsInDirectory(char const *directoryPath) const
  {
    std::vector<size_t> hashedFilePaths;
    std::string directory = directoryPath;

    WIN32_FIND_DATA fileData;
    HANDLE position;

    if (directory.back() != '\\' && directory.back() != '/')
      directory.append("/");

    // Get first file in directory and check if successful
    position = FindFirstFile((directory + "*").c_str(), &fileData);
    if (position == INVALID_HANDLE_VALUE)
    {
      DWORD errorCode = GetLastError();
      if (errorCode == ERROR_NO_MORE_FILES)
      {
        // log Attempting to find files in empty directory:
      }
      else
      {
        // ERRORIF: Error attempting to get filepaths in directory: [errorCode]
      }

      return hashedFilePaths;
    }

    std::string filepath(fileData.cFileName);
    do
    {
      filepath = fileData.cFileName;
      // Skip if file is just a directory symbol
      if (filepath == "." || filepath == "..")
        continue;

      if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        continue;

      // Make sure to add directory back to name
      filepath = directory + filepath;
      hashedFilePaths.push_back(GET_STRING_MANAGER->Hash(filepath.c_str()));
    } while (FindNextFile(position, &fileData) != 0);

    DWORD errorCode = GetLastError();
    // ERRORIF(errorCode != ERROR_NO_MORE_FILES) (same error msg as above)

    FindClose(position);
    return hashedFilePaths;
  }

  std::vector<size_t> FileManager::GetFilepathsInDirectoryRecursive(char const *directoryPath) const
  {
    std::vector<size_t> hashedFilePaths;
    std::string directory = directoryPath;

    WIN32_FIND_DATA fileData;
    HANDLE position;

    if (directory.back() != '\\' && directory.back() != '/')
      directory.append("/");

    // Get first file in directory and check if successful
    position = FindFirstFile((directory + "*").c_str(), &fileData);
    if (position == INVALID_HANDLE_VALUE)
    {
      DWORD errorCode = GetLastError();
      if (errorCode == ERROR_NO_MORE_FILES)
      {
        // log Attempting to find files in empty directory:
      }
      else
      {
        // ERRORIF: Error attempting to get filepaths in directory: [errorCode]
      }

      return hashedFilePaths;
    }

    std::string filepath(fileData.cFileName);
    do
    {
      filepath = fileData.cFileName;
      if (filepath == "." || filepath == "..")
        continue;

      // Skip if file is just a directory symbol
      if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
        auto filesInSubDir = GetFilepathsInDirectory(filepath.c_str());
        size_t numFilesInSubDir = filesInSubDir.size();
        for (int i = 0; i < numFilesInSubDir; ++i)
        {
          hashedFilePaths.push_back(filesInSubDir[i]);
        }
      }

      // Make sure to add directory back to name
      filepath = directory + filepath;
      hashedFilePaths.push_back(GET_STRING_MANAGER->Hash(filepath.c_str()));
    } while (FindNextFile(position, &fileData) != 0);

    DWORD errorCode = GetLastError();
    // ERRORIF(errorCode != ERROR_NO_MORE_FILES) (same error msg as above)

    FindClose(position);
    return hashedFilePaths;
  }

  size_t FileManager::StripFilePath(std::string const &filepath) const
  {
    return GET_STRING_MANAGER->Hash(filepath.substr(filepath.find_last_of("/\\") + 1).c_str());
  }

  size_t FileManager::StripFileExtension(std::string const &file) const
  {
    std::string filename = file;
    size_t index = filename.rfind(".");
    if (index != std::string::npos)
      filename.erase(filename.rfind("."));

    return GET_STRING_MANAGER->Hash(filename.c_str());
  }

  size_t FileManager::StripFilePathAndExtention(std::string const &path) const
  {
    return StripFileExtension(GET_STRING_MANAGER->Hash(StripFilePath(path)));
  }
}
