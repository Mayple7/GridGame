/*!****************************************************************************
\file    IDelegateParam2.hpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Interface for a delegate with 2 parameter

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         Dependencies
*/
#include "IDelegateParam2.h"


/*=================================
*      Class Public Functions
*/
template <typename Param1, typename Param2>
IDelegateParam2<Param1, Param2>::IDelegateParam2()
: m_param1()
{
}

template <typename Param1, typename Param2>
IDelegateParam2<Param1, Param2>::IDelegateParam2(Param1 param1, Param2 param2)
: m_param1(param1)
, m_param2(param2)
{
}

template <typename Param1, typename Param2>
IDelegateParam2<Param1, Param2>::~IDelegateParam2()
{
}

template <typename Param1, typename Param2>
void IDelegateParam2<Param1, Param2>::SetParam1(Param1 param)
{
  m_param1 = param;
}

template <typename Param1, typename Param2>
void IDelegateParam2<Param1, Param2>::SetParam2(Param2 param)
{
  m_param2 = param;
}

template <typename Param1, typename Param2>
Param1 IDelegateParam2<Param1, Param2>::GetParam1() const
{
  return m_param1;
}

template <typename Param1, typename Param2>
Param2 IDelegateParam2<Param1, Param2>::GetParam2() const
{
  return m_param2;
}
