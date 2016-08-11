/*!****************************************************************************
\file    GameTime.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Maintains time for game

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         include guard
*/
#pragma once

/*=================================
*         Dependencies
*/

/*=================================
*      Forward Declarations
*/

/*=================================
*      Namespace Umbrella
*/
namespace utilities
{

  /*=================================
  *         Classes
  */
  class GameTime
  {
    /*=================================
    *         Type Definitions
    */
  public:
    /*=================================
    *         Class Variables
    */
  private:
    double m_startFrameTime;
    double m_newTime;
    double m_totalTime;
    double m_deltaTime;
    double m_frameTimeMin;

    /*=================================
    *         Class Functions
    */
  public:
    GameTime();
    virtual ~GameTime();

    void SetMaxFrames(unsigned frames);
    void StartFrame();
    void EndFrame();
    double GetCurTime() const;
    double GetTotalTime() const;
    double GetDeltaTime() const;

  protected:
    /*=================================
    *     Class Protected Functions
    */

  private:
    /*=================================
    *     Class Private Functions
    */
  };

}

