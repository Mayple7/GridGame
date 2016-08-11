/*!****************************************************************************
\file    Trace.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Handles warning and error logging

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
#include "DebugManager.h"
#include <assert.h>
#include <string>
#include <stdarg.h>

/*=================================
*         Enum Classes
*/
enum class Trace_Type_
{
  Standard_,
  ErrorsOnly_,
  WarningsAsErrors_,
  AssertsDisabled_,

  Count_,
}; 

/*=================================
*         MACROS
*/
#define POWER_OF_TWO(X) (1 << X)

// Made defines for Bit Manipulation
#define TRACE_DISPLAY_LOG POWER_OF_TWO(1)
#define TRACE_DISPLAY_CONSOLE POWER_OF_TWO(2)

#define TRACE_ENABLED

#define MY_FUNC_NAME __FUNCTION__

#define LOCATION_DETAIL(LINE) \
       MY_FUNC_NAME "-" #LINE " ~" __FILE__
        
#define LOCATION_LINE(X)\
        LOCATION_DETAIL(X)

#define DEFAULT_ERROR_FILE "error.log"

#ifdef OLD_TRACE
/*! 
  \brief
    Creates warning based on whether the expression
    is false.
  \param EXP
    The expression to evaluate
  \param FMT
    The format of the message
  \param ...
    The variadic arguments. 
*/
#ifdef TRACE_ENABLED                     
#define TRACE_WARNING(EXP, FMT, ...)      \
  do                                       \
  {                                        \
    if (!(EXP))                            \
    {                                      \
      if (Trace::Warning(LOCATION_LINE(__LINE__), (FMT), ##__VA_ARGS__)) \
      {                                    \
      }                                    \
    }                                      \
  } while(0)                           
#else                                    
#define TRACE_WARNING( EXP, FMT, ...)      \
  do                                       \
  {                                        \
    (void)sizeof(EXP);                     \
  } while(0)                               
#endif

/*! 
  \brief
    Creates error based on whether the expression
    is false.
  \param EXP
    The expression to evaluate
  \param FMT
    The format of the message
  \param ...
    The variadic arguments. Must have at least one
    argument. If no argument is need then just put
    NULL.
*/
#ifdef TRACE_ENABLED                     
#define TRACE_ERROR( EXP, FMT, ...)        \
  do                                       \
  {                                        \
    if (!(EXP))                            \
    {                                      \
      if (Trace::Error(LOCATION_LINE(__LINE__), (FMT), ##__VA_ARGS__)) \
      {                                    \
        __debugbreak();                    \
      }                                    \
    }                                      \
  } while(0)                            
#else                                    
#define TRACE_ERROR( EXP, FMT, ...)        \
  do                                       \
  {                                        \
    (void)sizeof(EXP);                     \
  } while(0)                               
#endif
#else
#define TRACE_WARNING(EXP, FMT, ...)      \
  WARN_IF((!(EXP)), FMT, __VA_ARGS__)

#define TRACE_ERROR( EXP, FMT, ...)        \
  ERROR_IF((!(EXP)), FMT, __VA_ARGS__)

#endif

/*=================================
*         Classes
*/
class Trace
{
  /*=================================
  *         Class Variables
  */
private:
  static FILE *m_DefaultStream;
  static Trace_Type_ m_TraceType;
  static unsigned int m_DisplayType;
  static std::string m_ErrorLogFile;



  /*=================================
  *         Class Functions
  */
public:

  static void Initialize(Trace_Type_ type, 
                         unsigned int displayType = TRACE_DISPLAY_CONSOLE,
                         const char *logFile = nullptr);
  static bool Warning(const char *fileName, const char *fmt, ...);
  static bool Error(const char *fileName, const char *fmt, ...);

private:
  static void WriteMessage(FILE *file, 
                           const char *errorType,
                           const char *fileName, 
                           const char *fmt, 
                           va_list args);
  static void WriteConsole(const char *errorType,
                           const char *fileName, 
                           const char *fmt, 
                           va_list args);
  static void WriteLog(const char *errorType,
                       const char *fileName, 
                       const char *fmt, 
                       va_list args);

  // Intentionally private and unimplemented
  Trace();
  ~Trace();


};





