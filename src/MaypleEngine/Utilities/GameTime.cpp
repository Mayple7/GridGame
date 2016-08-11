/*!****************************************************************************
\file    GameTime.cpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 26, 2015

\brief   Maintains time for game

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         Dependencies
*/
#include "stdinc.h"
#include "GameTime.h"

/*=================================
*      Forward Declarations
*/

/*=================================
*      Namespace Umbrella
*/
namespace utilities
{

  /*=================================
  *      Class Public Functions
  */
  GameTime::GameTime()
  : m_startFrameTime(0.0)
  , m_newTime(0.0)
  , m_totalTime(0.0)
  , m_deltaTime(0.0)
  {

  }
  GameTime::~GameTime()
  {

  }

  void GameTime::SetMaxFrames(unsigned frames)
  {
    m_frameTimeMin =  1000.0 / static_cast<double>(frames);
  }

  void GameTime::StartFrame()
  {
    //m_startFrameTime = static_cast<double>(timeGetTime());
  }

  void GameTime::EndFrame()
  {
    //do
    //{
    //  double curTime = static_cast<double>(timeGetTime());

    //  m_deltaTime = curTime - m_startFrameTime;

    //} while (m_deltaTime <= m_frameTimeMin);

    //m_totalTime += m_deltaTime;
  }

  double GameTime::GetCurTime() const
  {
    //return static_cast<double>(timeGetTime());
    return 0.0;
  }

  double GameTime::GetTotalTime() const
  {
    return m_totalTime;
  }

  double GameTime::GetDeltaTime() const
  {
    return m_deltaTime;
  }
  /*=================================
  *     Class Protected Functions
  */

  /*=================================
  *     Class Private Functions
  */

}

