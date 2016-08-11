/*!****************************************************************************
\file    IDelegate.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Base interface for delegates

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

/*=================================
*         Classes
*/
class IDelegate
{
  /*=================================
  *         Class Variables
  */
private:

  /*=================================
  *         Class Functions
  */
public:
  IDelegate();
  ~IDelegate();

  void Execute();
protected:
  virtual void _ExecuteDetail() = 0;

};

