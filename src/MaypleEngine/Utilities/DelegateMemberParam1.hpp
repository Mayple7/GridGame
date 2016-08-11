/*!****************************************************************************
\file    DelegateMemberParam1.hpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Generic delegate for a member function with one parameter

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
          void (ClassType::*DelFunc)(Param1)>
DelegateMemberParam1<ClassType, Param1, DelFunc>::DelegateMemberParam1(ClassType *obj)
: IDelegateParam1<Param1>()
, m_obj(obj)
, m_delFunc(DelFunc)
{

}

template <typename ClassType, 
          typename Param1,
          void (ClassType::*DelFunc)(Param1)>
DelegateMemberParam1<ClassType, Param1, DelFunc>::~DelegateMemberParam1()
{

}


/*=================================
*    Class Protected Functions
*/

template <typename ClassType, 
          typename Param1,
          void (ClassType::*DelFunc)(Param1)>
void DelegateMemberParam1<ClassType, Param1, DelFunc>::_ExecuteDetail()
{
  (m_obj->*m_delFunc)((m_param1));
}


