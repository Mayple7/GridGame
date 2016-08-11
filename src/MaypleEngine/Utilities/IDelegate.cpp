/*!****************************************************************************
\file    IDelegate.cpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 26, 2015

\brief   Base interface for delegates

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         Dependencies
*/
#include "stdinc.h"
#include "IDelegate.h"


/*=================================
*      Class Public Functions
*/
IDelegate::IDelegate()
{
}

IDelegate::~IDelegate()
{
}

void IDelegate::Execute()
{
  _ExecuteDetail();
}

