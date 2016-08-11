/*!****************************************************************************
\file    MiniDump.cpp
\author  Dan Muller (d.muller)
\date    Jul 18, 2015

\brief   Holds the functionality for debugging the game after a crash.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"

#include "dbghelp.h"
#include "MiniDump.h"
#include "DebugManager.h"

#include <codecvt>
#include <ShlObj.h>

#define MEGA_DUMP 0
#define NORMAL_DUMP 1
#define LIGHT_DUMP 0

std::string GetExceptionString(DWORD exceptionCode)
{
  switch (exceptionCode)
  {
  case EXCEPTION_ACCESS_VIOLATION:
    return "ACCESS_VIOLATION";
  case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
    return "ARRAY_BOUNDS_EXCEEDED";
  case EXCEPTION_BREAKPOINT:
    return "BREAKPOINT";
  case EXCEPTION_DATATYPE_MISALIGNMENT:
    return "DATATYPE_MISALIGNMENT";
  case EXCEPTION_FLT_DENORMAL_OPERAND:
    return "FLT_DENORMAL_OPERAND";
  case EXCEPTION_FLT_DIVIDE_BY_ZERO:
    return "FLT_DIVIDE_BY_ZERO";
  case EXCEPTION_FLT_INEXACT_RESULT:
    return "FLT_INEXACT_RESULT";
  case EXCEPTION_FLT_INVALID_OPERATION:
    return "FLT_INVALID_OPERATION";
  case EXCEPTION_FLT_OVERFLOW:
    return "FLT_OVERFLOW";
  case EXCEPTION_FLT_STACK_CHECK:
    return "FLT_STACK_CHECK";
  case EXCEPTION_FLT_UNDERFLOW:
    return "FLT_UNDERFLOW";
  case EXCEPTION_ILLEGAL_INSTRUCTION:
    return "ILLEGAL_INSTRUCTION";
  case EXCEPTION_IN_PAGE_ERROR:
    return "IN_PAGE_ERROR";
  case EXCEPTION_INT_DIVIDE_BY_ZERO:
    return "INT_DIVIDE_BY_ZERO";
  case EXCEPTION_INT_OVERFLOW:
    return "INT_OVERFLOW";
  case EXCEPTION_INVALID_DISPOSITION:
    return "INVALID_DISPOSITION";
  case EXCEPTION_NONCONTINUABLE_EXCEPTION:
    return "NONCONTINUABLE_EXCEPTION";
  case EXCEPTION_PRIV_INSTRUCTION:
    return "PRIV_INSTRUCTION";
  case EXCEPTION_SINGLE_STEP:
    return "SINGLE_STEP";
  case EXCEPTION_STACK_OVERFLOW:
    return "STACK_OVERFLOW";
  default:
    return "UNKNOWN_EXCEPTION";
  }
}

// Checks if the program is running with admin privs
bool8 IsElevated(void)
{
  bool8 elevated = false;
  HANDLE hToken = NULL;
  if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
  {
    TOKEN_ELEVATION Elevation;
    DWORD cbSize = sizeof(TOKEN_ELEVATION);
    if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize))
    {
      elevated = true;
    }
  }
  if (hToken)
  {
    CloseHandle(hToken);
  }

  return elevated;
}

// Writes the dump file
LONG WINAPI WriteDump(EXCEPTION_POINTERS* pException)
{
  // Create the minidump exception information
  MINIDUMP_EXCEPTION_INFORMATION exceptionInfo;
  exceptionInfo.ThreadId = GetCurrentThreadId();
  exceptionInfo.ExceptionPointers = pException;
  exceptionInfo.ClientPointers = FALSE;

  // Create the time string to create unique filenames
  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y_%m_%d_%H%M%S_", &tstruct);
  std::string fileName;

  // Create the filename
  if (!IsElevated())
  {
    std::string saveLocation;
    wchar_t* pathLocation = 0;

    // Get the app data folder
    ERROR_IF(SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_CREATE, NULL, &pathLocation), "Getting Appdata Directory Failed!");

    // Uses the string stream (.AFS = Animus Fault Settings)
    std::wstringstream stringStream;
    stringStream << pathLocation << L"/DigiPen/AnimusFaultDumps";

    //setup converter
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

    //use converter (.to_bytes: wstr->str, .from_bytes: str->wstr)
    std::string filePath = converter.to_bytes(stringStream.str());

    CreateDirectory(filePath.c_str(), NULL);

    // Frees the memory so there is no leak
    CoTaskMemFree(static_cast<void*>(pathLocation));

    fileName = filePath + "/animusfault_";
  }
  else
  {
    fileName = "animusfault_";
  }
  fileName.append(buf);
  fileName.append(GetExceptionString(pException->ExceptionRecord->ExceptionCode));
  fileName.append(".dmp");

  if (MEGA_DUMP)
    // Write the dump file
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), CreateFile(fileName.c_str(), GENERIC_WRITE, FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL), (MINIDUMP_TYPE)(MiniDumpNormal | MiniDumpWithFullMemory | MiniDumpWithHandleData | MiniDumpWithUnloadedModules), &exceptionInfo, NULL, NULL);
  else if (NORMAL_DUMP)
    // Write the dump file
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), CreateFile(fileName.c_str(), GENERIC_WRITE, FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL), (MINIDUMP_TYPE)(MiniDumpNormal | MiniDumpWithDataSegs | MiniDumpWithIndirectlyReferencedMemory), &exceptionInfo, NULL, NULL);
  else if (LIGHT_DUMP)
    // Write the dump file
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), CreateFile(fileName.c_str(), GENERIC_WRITE, FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL), (MINIDUMP_TYPE)(MiniDumpNormal), &exceptionInfo, NULL, NULL);


  // Return continue search
  return EXCEPTION_CONTINUE_SEARCH;
}
