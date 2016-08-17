/*!****************************************************************************
\file    Profiler.h
\author  Dan Muller (d.muller)
\date    

\brief   

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#pragma once
#include "ProfileSample.h"
#include "TimeManager.h"

namespace profilerSpace
{
  using timeSpace::TimeManager;

  class Profiler
  {
  public:
    Profiler(TimeManager *timeManager);
    ~Profiler();

    void AddSample(const char* name, const f32 &time);
    void AddSample(const ProfileSample& sample);

    void CreateReport(void);
    void SavePreviousReport(void);

    void StartProfiler(void);
    void StopProfiler(void);

    void UpdateProfiler(void);

  private:
    void BeginProfiling(void);
    void EndProfiling(void);

    bool8 m_runProfiler;
    bool8 m_profilerStart;
    bool8 m_profilerStop;
    TimeManager *m_timeManager;
    std::mutex m_sampleListLock;
    std::vector<ProfileSample> m_sampleList;

    std::string m_tempFileName;
    std::string m_previousReportString;
  };
}
