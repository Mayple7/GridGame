/*!****************************************************************************
\file    FileManager.h
\author  Seth England (seth.england)
\date    May 2, 2015

\brief   Execution manager

\par     Checked By:

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

void InitializeFileManager(void);

namespace fileSpace
{
  class FileManager
  {
  public:
    std::vector<size_t> GetFilepathsInDirectory(char const *directoryPath) const;
    std::vector<size_t> GetFilepathsInDirectoryRecursive(char const *directoryPath) const;

    size_t StripFilePath(std::string const &path) const;
    size_t StripFileExtension(std::string const &path) const;
    size_t StripFilePathAndExtention(std::string const &path) const;
  };
} //namespace fileSpace