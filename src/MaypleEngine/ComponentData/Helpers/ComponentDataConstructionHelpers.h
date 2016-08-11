/*!****************************************************************************
\file    ComponentDataConstructionHelpers.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Jun 12, 2015

\brief   List of construction macros

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

/*=================================
*      Forward Declarations
*/

/*=================================
*       Macros
*/

// Declares the declaration part of a component's construction
#define START_DECLARE_COMPONENT_CONSTRUCTION(NAMESPACE, COMPONENTNAME, CAMELCOMPONENTNAME) \
void Construct##COMPONENTNAME() \
{ \
  hndl *data = (hndl *)lpParam; \
  auto *CAMELCOMPONENTNAME##ComponentData = componentSpace::ComponentDataLocator::GetData<COMPONENTNAME##ComponentData>(); \
  hndl _openSlot = 0xFFFFFFFF; \
  hndl _newSlot =  0x00000000;

// End of a component's declaration of construction
#define END_DECLARE_COMPONENT_CONSTRUCTION \
  *(data) = _openSlot; \
}

  
#define INITIALIZE_SLOT2(CAMELNAME, CAMELCOMPONENTNAME) \
_newSlot = CAMELCOMPONENTNAME##ComponentData->m_##CAMELNAME##Container.AllocateSlot(); \
ERROR_IF(_openSlot != 0xFFFFFFFF && _newSlot != _openSlot, "Slot allocations are not aligned!"); \
_openSlot = _newSlot; 

#define INITIALIZE_SLOT3(CAMELNAME, CAMELCOMPONENTNAME, DEFAULT) \
_newSlot = CAMELCOMPONENTNAME##ComponentData->m_##CAMELNAME##Container.AllocateSlot(); \
ERROR_IF(_openSlot != 0xFFFFFFFF && _newSlot != _openSlot, "Slot allocations are not aligned!"); \
CAMELCOMPONENTNAME##ComponentData->m_##CAMELNAME##Container[_newSlot] = DEFAULT; \
_openSlot = _newSlot; 


#define INITIALIZE_SLOT(...) CALL_OVERLOAD(INITIALIZE_SLOT, __VA_ARGS__)


// Declares the declaration part of a component's destruction
#define START_DECLARE_COMPONENT_DESTRUCTION(NAMESPACE, COMPONENTNAME, CAMELCOMPONENTNAME) \
void Destruct##COMPONENTNAME() \
{ \
  hndl *data = (hndl *)lpParam; \
  auto *CAMELCOMPONENTNAME##ComponentData = componentSpace::ComponentDataLocator::GetData<COMPONENTNAME##ComponentData>();

// End of a component's declaration of destruction
#define END_DECLARE_COMPONENT_DESTRUCTION \
}

#define UNINITIALIZE_SLOT(CAMELNAME, CAMELCOMPONENTNAME) \
  CAMELCOMPONENTNAME##ComponentData->m_##CAMELNAME##Container.Remove(*data);
