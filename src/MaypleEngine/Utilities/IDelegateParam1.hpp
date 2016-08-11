/*!****************************************************************************
\file    IDelegateParam1.hpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Interface for a delegate with 1 parameter

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         Dependencies
*/
#include "IDelegateParam1.h"


/*=================================
*      Class Public Functions
*/
template <typename Param1>
IDelegateParam1<Param1>::IDelegateParam1()
: m_param1()
{
}

template <typename Param1>
IDelegateParam1<Param1>::IDelegateParam1(Param1 param)
: m_param1(param)
{
}

template <typename Param1>
IDelegateParam1<Param1>::~IDelegateParam1()
{
}

template <typename Param1>
void IDelegateParam1<Param1>::SetParam1(Param1 param)
{
  m_param1 = param;
}

template <typename Param1>
Param1 IDelegateParam1<Param1>::GetParam1() const
{
  return m_param1;
}
