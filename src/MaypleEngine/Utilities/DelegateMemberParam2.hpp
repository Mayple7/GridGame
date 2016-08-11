/*!****************************************************************************
\file    DelegateMemberParam2.hpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Generic delegate for a member function with two parameter

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         Dependencies
*/


/*=================================
*      Class Public Functions
*/
template <typename ClassType, 
          typename Param1,
          typename Param2,
          void (ClassType::*DelFunc)(Param1, Param2)>
DelegateMemberParam2<ClassType, Param1, Param2, DelFunc>::DelegateMemberParam2(ClassType *obj)
: IDelegateParam2<Param1, Param2>()
, m_obj(obj)
, m_delFunc(DelFunc)
{

}

template <typename ClassType, 
          typename Param1,
          typename Param2,
          void (ClassType::*DelFunc)(Param1, Param2)>
DelegateMemberParam2<ClassType, Param1, Param2, DelFunc>::~DelegateMemberParam2()
{

}


/*=================================
*    Class Protected Functions
*/
template <typename ClassType, 
          typename Param1,
          typename Param2,
          void (ClassType::*DelFunc)(Param1, Param2)>
void DelegateMemberParam2<ClassType, Param1, Param2, DelFunc>::_ExecuteDetail()
{
  (m_obj->*m_delFunc)(m_param1, m_param2);
}

