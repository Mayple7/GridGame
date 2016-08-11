/*!****************************************************************************
\file    DelegateMemberParam1.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Generic delegate for a member function with one parameter

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
#include "IDelegateParam1.h"

/*=================================
*         Classes
*/
template <typename ClassType, 
          typename Param1,
          void (ClassType::*DelFunc)(Param1)>
class DelegateMemberParam1 : public IDelegateParam1<Param1>
{
  /*=================================
  *       Type Definitions
  */
public:
  typedef void (ClassType::*DelFuncType)(Param1);
  /*=================================
  *         Class Variables
  */
private:
  ClassType *m_obj;
  DelFuncType m_delFunc;

  /*=================================
  *      Class Public Functions
  */
public:
  DelegateMemberParam1(ClassType *obj);
  ~DelegateMemberParam1();



  /*=================================
  *     Class Protected Functions
  */
protected:
  virtual void _ExecuteDetail();

};




#include "DelegateMemberParam1.hpp"
