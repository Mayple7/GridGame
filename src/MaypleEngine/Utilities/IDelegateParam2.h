/*!****************************************************************************
\file    IDelegateParam2.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Interface for a delegate with 1 parameter

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
#include "IDelegate.h"

/*=================================
*         Classes
*/
template <typename Param1, typename Param2>
class IDelegateParam2 : public IDelegate
{
  /*=================================
  *         Class Variables
  */
protected:
  Param1 m_param1;
  Param2 m_param2;

  /*=================================
  *         Class Functions
  */
public:
  IDelegateParam2();
  IDelegateParam2(Param1 param1, Param2 param2);
  ~IDelegateParam2();

  void SetParam1(Param1 param);
  void SetParam2(Param2 param);
  Param1 GetParam1() const;
  Param2 GetParam2() const;

};

#include "IDelegateParam2.hpp"
