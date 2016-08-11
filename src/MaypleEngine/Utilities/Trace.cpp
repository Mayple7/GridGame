/*!****************************************************************************
\file    Trace.cpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 26, 2015

\brief   Handles warning and error logging

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*     Preprocessor Definitions
*/
// To prevent errors with fopen
/*=================================
*         Dependencies
*/
#include "stdinc.h"
#include "Trace.h"

/*=================================
*      Class Static Variables
*/
// Default is trace on
FILE *Trace::m_DefaultStream = stdout;
Trace_Type_ Trace::m_TraceType = Trace_Type_::WarningsAsErrors_;
unsigned int Trace::m_DisplayType = TRACE_DISPLAY_CONSOLE | TRACE_DISPLAY_LOG;
std::string Trace::m_ErrorLogFile = "";

/*=================================
*      Class Public Functions
*/
void Trace::Initialize(Trace_Type_ type,
                       unsigned int displayType,
                       const char *logFile)
{
  m_TraceType = type;
  m_DisplayType = displayType;

  // If we are not displaying to log then we don't need
  // to clear the log file
  if (!(displayType & TRACE_DISPLAY_LOG))
  {
    return;
  }


  m_ErrorLogFile = logFile ? logFile : DEFAULT_ERROR_FILE;

  // Clear Error log
  FILE *fClear = fopen(m_ErrorLogFile.c_str(), "wt");

  if (!fClear)
  {
    fprintf(stderr, "Error (InitializeFunction): \n" 
                    "  Unable to open log file. Disabling "
                    "logging to file.");
    
    m_DisplayType = TRACE_DISPLAY_CONSOLE;
    return;
  }

  fclose(fClear);
}

bool Trace::Warning(const char *fileName, const char *fmt, ...)
{
  // Do nothing if we only care about errors
  if (m_TraceType == Trace_Type_::ErrorsOnly_)
  {
    return false;
  }
  
  va_list args;
  va_start(args, fmt);
  // Write out message
  switch (m_DisplayType)
  {
  case TRACE_DISPLAY_CONSOLE:
    WriteConsole("Warning", 
                 fileName,
                 fmt,
                 args);
    break;
  case TRACE_DISPLAY_LOG:
    WriteLog("Warning",
             fileName,
             fmt,
             args);
    break;
  case (TRACE_DISPLAY_CONSOLE | TRACE_DISPLAY_LOG):
    WriteConsole("Warning", 
                 fileName,
                 fmt,
                 args);
    WriteLog("Warning",
             fileName,
             fmt,
             args);
    break;
  }
  va_end(args);



  // Whether or not we should break at on warning
  if (m_TraceType == Trace_Type_::WarningsAsErrors_)
  {
    return true;
  }

  return false;
}

bool Trace::Error(const char *fileName, const char *fmt, ...)
{
  va_list args;
  // Write out message
  va_start(args, fmt);
  switch (m_DisplayType)
  {
  case TRACE_DISPLAY_CONSOLE:
    WriteConsole("Error", 
                 fileName,
                 fmt,
                 args);
    break;
  case TRACE_DISPLAY_LOG:
    WriteLog("Error",
             fileName,
             fmt,
             args);
    break;
  case (TRACE_DISPLAY_CONSOLE | TRACE_DISPLAY_LOG):
    WriteConsole("Error", 
                 fileName,
                 fmt,
                 args);
    WriteLog("Error",
             fileName,
             fmt,
             args);
    break;
  }
  va_end(args);



  // Whether or not we should break at on error
  if (m_TraceType != Trace_Type_::AssertsDisabled_)
  {
    return true;
  }

  return false;
}

/*=================================
*     Class Private Functions
*/
void Trace::WriteMessage(FILE *file, 
                         const char *errorType,
                         const char *fileName, 
                         const char *fmt, 
                         va_list args)
{
  std::string message = errorType;
  message += "(";
  message += fileName;
  message += "):\n";
  message += "  ";
  message += fmt;
  message += "\n\n";

  // Write out the message to the stream
  vfprintf(file, message.c_str(), args);

  // Ensure that message gets printed
  fflush(file);
}
void Trace::WriteConsole(const char *errorType,
                         const char *fileName, 
                         const char *fmt, 
                         va_list args)
{
  // Perform variadic message writing
  WriteMessage(m_DefaultStream,
               errorType,
               fileName,
               fmt,
               args);
}

void Trace::WriteLog(const char *errorType,
                     const char *fileName, 
                     const char *fmt, 
                     va_list args)
{
  // Open Log
  FILE *fLog = fopen(m_ErrorLogFile.c_str(), "at");

  if (!fLog)
  {
    fprintf(stderr, "Error (WriteLog): \n"
                    "  Unable to open log file. Disabling "
                    "logging to file.");
    
    m_DisplayType = TRACE_DISPLAY_CONSOLE;
    return;
  }
  
  WriteMessage(fLog,
               errorType,
               fileName,
               fmt,
               args);

  fclose(fLog);

}