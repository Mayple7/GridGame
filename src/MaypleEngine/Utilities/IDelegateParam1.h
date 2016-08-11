/*!****************************************************************************
\file    IDelegateParam1.h
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
template <typename Param1>
class IDelegateParam1 : public IDelegate
{
  /*=================================
  *         Class Variables
  */
protected:
  Param1 m_param1;

  /*=================================
  *         Class Functions
  */
public:
  IDelegateParam1();
  IDelegateParam1(Param1 param);
  ~IDelegateParam1();

  void SetParam1(Param1 param);
  Param1 GetParam1() const;

};

#include "IDelegateParam1.hpp"
