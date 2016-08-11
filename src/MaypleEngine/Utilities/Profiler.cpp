/*!****************************************************************************
\file    Profiler.cpp
\author  Dan Muller (d.muller)
\date    

\brief   

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#include "stdinc.h"

#include "Profiler.h"

#define RUN_PROFILER_ON_START false
#define SAVE_ALL_REPORTS false
#define MAX_SAMPLES 10000

DECLARE_JOB(InitializeProfiler)
{

  START_JOB;

  managerSpace::ManagerLocator::SetProfiler(new profilerSpace::Profiler(GET_TIME_MANAGER));

  END_JOB;

}

namespace profilerSpace
{
  Profiler::Profiler(TimeManager *timeManager) : m_timeManager(timeManager)
  {
#ifdef _EDITOR
    // Profiler will always be off at the start of the editor
    m_runProfiler = false;
#else
    // Profiler will be handled by the define
    m_runProfiler = RUN_PROFILER_ON_START;
#endif
    m_profilerStart = false;
    m_profilerStop = false;
    m_tempFileName = "ProfilerData/temp_data.txt";
  }


  Profiler::~Profiler()
  {
    CreateReport();
    m_timeManager = nullptr;
  }

  // Tells the profiler to start tracking beginning next frame
  void Profiler::StartProfiler(void)
  {
    m_profilerStart = true;
  }

  // Tells the profiler to end tracking at the beginning of the next frame
  void Profiler::StopProfiler(void)
  {
    m_profilerStop = true;
  }

  // Begins profiling data
  void Profiler::BeginProfiling(void)
  {
    m_sampleList.clear();
    m_runProfiler = true;
    m_profilerStart = false;
  }

  // Ends the profiling and saves the profiler data
  void Profiler::EndProfiling(void)
  {
    CreateReport();
    m_runProfiler = false;
    m_profilerStop = false;
  }

  void Profiler::UpdateProfiler(void)
  { 
    // Starts profiling
    if(m_profilerStop)
      EndProfiling();

    // Stops profiling
    if(m_profilerStart)
      BeginProfiling();
  }

  void Profiler::AddSample(const char* name, const f32& time)
  {
    if(!m_runProfiler)
      return;

    if (m_sampleList.size() > MAX_SAMPLES)
    {
      return;
    }

    std::lock_guard<std::mutex> lockGuard(m_sampleListLock);
    m_sampleList.push_back(ProfileSample(name, time));
  }

  void Profiler::AddSample(const ProfileSample& sample)
  {
    if(!m_runProfiler)
      return;

    if (m_sampleList.size() > MAX_SAMPLES)
    {
      return;
    }

    std::lock_guard<std::mutex> lockGuard(m_sampleListLock);
    m_sampleList.push_back(sample);
  }


  //typedef std::pair<const char*, f32> SamplePair;
  bool StatCompare(ProfileSample left, ProfileSample right)
  {
    return left.GetTime() > right.GetTime();
  }

  void Profiler::CreateReport(void)
  {
    if(m_sampleList.size() == 0)
      return;

    std::cout << "Creating Profiler Report: Collating " << m_sampleList.size() << " samples" << std::endl;

    std::vector<ProfileSample> collatedList;
    std::vector<std::pair<uint32, f32>> averageTime;
    unsigned i;

    bool fExists;
    f32 total = 0.0f;
    for (ProfileSample s : m_sampleList)
    {
      total += s.GetTime();
      fExists = false;
      for (i = 0; !fExists && i < collatedList.size(); ++i)
      {
        if (strcmp(collatedList[i].m_executionName, s.GetName()) == 0)
        {
          fExists = true;
          if(collatedList[i].m_executionTime < s.GetTime())
            collatedList[i].m_executionTime = s.GetTime();
          averageTime[i].first++;
          averageTime[i].second += s.GetTime();
        }
      }

      if (!fExists)
      {
        collatedList.push_back(s);
        averageTime.push_back(std::make_pair<uint32, f32>(1, s.GetTime()));
      }
    }

    std::cout << "Collated " << m_sampleList.size() << " samples into " << collatedList.size() << " unique entries" << std::endl;

    std::sort(collatedList.begin(), collatedList.end(), &StatCompare);

    // Create the time string to create unique filenames
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y_%m_%d_%H%M%S", &tstruct);

    // Create the filename
    m_previousReportString = "ProfilerData/cpureport_";
    m_previousReportString.append(buf);
    m_previousReportString.append(".txt");

    FILE* outputFile = fopen(m_tempFileName.c_str(), "wt");

    if (!outputFile)
    {
      std::cout << "Unable to open profiler report file." << std::endl;
      return;
    } 

    unsigned concurrentThreadsSupported = std::thread::hardware_concurrency();
    fprintf(outputFile, "Execution Node Name : Num Samples : Maximum Time : Average Time\n");
    for (unsigned i = 0; i < collatedList.size(); ++i)
    {
      collatedList[i].m_executionTime = collatedList[i].m_executionTime;
      fprintf(outputFile, "\t%s: %d : %f : %f\n", collatedList[i].m_executionName, averageTime[i].first, collatedList[i].m_executionTime, averageTime[i].second / averageTime[i].first);
    }

    fclose(outputFile);
  }

  // Saves the previous report to archive
  void Profiler::SavePreviousReport(void)
  {
    if(m_previousReportString.empty())
    {
      GET_DEBUG_MANAGER->HandleWarningFailure(__FILE__, __LINE__, "%s", "No previous report to save.");
      return;
    }
    
    FILE* outputFile = fopen(m_previousReportString.c_str(), "wt");

    std::ifstream source(m_tempFileName);
    std::ofstream destination(m_previousReportString);

    destination << source.rdbuf();

    m_previousReportString.clear();
  }
}
