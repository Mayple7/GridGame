/*!****************************************************************************
\file    DelegateMemberParam2.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Generic delegate for a member function with two parameter

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
#include "IDelegateParam2.h"

/*=================================
*         Classes
*/
template <typename ClassType, 
          typename Param1,
          typename Param2,
          void (ClassType::*DelFunc)(Param1, Param2)>
class DelegateMemberParam2 : public IDelegateParam2<Param1, Param2>
{
  /*=================================
  *       Type Definitions
  */
public:
  typedef void (ClassType::*DelFuncType)(Param1, Param2);
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
  DelegateMemberParam2(ClassType *obj);
  ~DelegateMemberParam2();

  /*=================================
  *      Class Private Functions
  */
protected:
  virtual void _ExecuteDetail();

};




#include "DelegateMemberParam2.hpp"
