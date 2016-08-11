/*!****************************************************************************
File:         TimeManager.cpp

Description:  Manages the time

******************************************************************************/

#include "stdinc.h"

#include "TimeManager.h"
#include "ManagerLocator.h"

namespace timeSpace
{

  ////////////////////////////////////////////////////////////////////////// PUBLIC

  // Default constructor
  TimeManager::TimeManager() : m_frameRate(60), m_deltaTime(1.0f / m_frameRate)
  {
    QueryPerformanceFrequency(&m_frequency);
    QueryPerformanceCounter(&m_frameStart);
  }

  // Default destructor
  TimeManager::~TimeManager()
  {}

  // Resets the frame time and calculates dt
  void TimeManager::UpdateDeltaTime(bool capFramerate)
  {
    float desiredDt = 1.0f / static_cast<float>(m_frameRate);
    float newDt;

    do
    {
      QueryPerformanceCounter(&m_frameEnd);
      newDt = static_cast<float>(m_frameEnd.QuadPart - m_frameStart.QuadPart) / static_cast<float>(m_frequency.QuadPart);
    } while(capFramerate && newDt < desiredDt);

    m_deltaTime = newDt;

    // Get the start time for the next dt
    QueryPerformanceCounter(&m_frameStart);
  }

  // Gets the current delta time
  float TimeManager::GetDeltaTime()
  {
    return m_deltaTime;
  }

  // Gets the elapsed delta, for debug purposes only
  float TimeManager::GetElapsedDeltaTime()
  {
    QueryPerformanceCounter(&m_frameEnd);
    return static_cast<float>(m_frameEnd.QuadPart - m_frameStart.QuadPart) / static_cast<float>(m_frequency.QuadPart);
  }

  float TimeManager::GetTime(void)
  {
    LARGE_INTEGER currentTime;
    QueryPerformanceCounter(&currentTime);
    return static_cast<float>(currentTime.QuadPart) / static_cast<float>(m_frequency.QuadPart);
  }
}
