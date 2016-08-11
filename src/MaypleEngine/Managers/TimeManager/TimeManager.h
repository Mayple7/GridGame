/*!****************************************************************************
\file    TimeManager.h
\author  Dan Muller

\brief   Manages the time

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

// Gets the last frame's delta time (f32) from the time manager
#define GET_DT \
GET_TIME_MANAGER->GetDeltaTime()

// Use only for debug purposes
#define DEBUG_GET_ELAPSED_DT \
GET_TIME_MANAGER->GetElapsedDeltaTime()

namespace timeSpace
{

  class TimeManager
  {
  public:
    TimeManager();  // Default constructor
    ~TimeManager(); // Default destructor

    void UpdateDeltaTime(bool capFramerate = true); // Resets the frame time and calculates dt
    float GetDeltaTime(); // Gets the current delta time

    // Gets the elapsed delta, for debug purposes only
    float GetElapsedDeltaTime();
    float GetTime(void);

  private: //data
    LARGE_INTEGER m_frequency;
    LARGE_INTEGER m_frameStart;
    LARGE_INTEGER m_frameEnd;
    unsigned int m_frameRate;
    float m_deltaTime;
  };
}
