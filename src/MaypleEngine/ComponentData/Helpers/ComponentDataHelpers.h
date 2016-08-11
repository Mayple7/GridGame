/*!****************************************************************************
\file    ComponentDataHelpers.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    May 15, 2015

\brief   Macro Helpers for component data

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         include guard
*/
#pragma once

/*=================================
*         Dependencies
*/
#include "MacroUtilities.h"
#undef GetObject // Stupid microsoft
#include "LuaDataRegister.h"
#include "ComponentDataDeclarationHelpers.h"
#include "ComponentDataPropertyDefinitionHelpers.h"
#include "ComponentDataDefinitionHelpers.h"
#include "ComponentDataConstructionHelpers.h"

/*=================================
*      Forward Declarations
*/

/*=================================
*           Macros
*/

#define AUTO_DECLARE_PROPERTY_GET(TYPE, NAME, CAMELNAME) \
  TYPE Get##NAME(hndl componentHandle);

#define AUTO_DECLARE_PROPERTY_SET(TYPE, NAME, CAMELNAME) \
  void Set##NAME(hndl componentHandle, TYPE CAMELNAME);




