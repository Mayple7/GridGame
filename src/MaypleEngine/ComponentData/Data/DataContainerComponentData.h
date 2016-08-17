/*!****************************************************************************
\file    DataComponentData.h
\author  Dan Muller (d.muller)
\date    July 30, 2015

\brief   Data component data 

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#pragma once

////////////////////////////////////////////////////////////////////////// DEPENDENCIES

// Custom containers
#include "SlotMap.h"
#include <utility>

// Makes component creation easier
#include "ComponentDataHelpers.h"

// Binding
#include "DataEntity.h"

/*=================================
*      Forward Declarations
*/

START_DECLARE_COMPONENT(coreSpace, DataContainer, dataContainer)

// Members (these must be public so the can be accessed outside the class during construction)
AUTO_DECLARE_GET_SET_PROPERTY(dataStructures::SlotMap<DataEntity>, DataEntity, dataEntity);

// New values for C++
void NewIntValue(hndl componentHandle, std::string newName, int32 newValue);
void NewUintValue(hndl componentHandle, std::string newName, uint32 newValue);
void NewFloatValue(hndl componentHandle, std::string newName, f32 newValue);
void NewBoolValue(hndl componentHandle, std::string newName, bool8 newValue);
void NewVectorValue(hndl componentHandle, std::string newName, VectorType& newValue);
void NewStringValue(hndl componentHandle, std::string newName, std::string newValue);

// Set value overloads for C++
void SetIntValue(hndl componentHandle, uint32 nameVal, int32 newValue);
void SetUintValue(hndl componentHandle, uint32 nameVal, uint32 newValue);
void SetFloatValue(hndl componentHandle, uint32 nameVal, f32 newValue);
void SetBoolValue(hndl componentHandle, uint32 nameVal, bool8 newValue);
void SetVectorValue(hndl componentHandle, uint32 nameVal, VectorType& newValue);
void SetStringValue(hndl componentHandle, uint32 nameVal, std::string newValue);

// Get value overloads for C++ (I edited these to return a bool as well whether or not the value exists)
std::pair<int32, bool> GetIntValue(hndl componentHandle, uint32 nameVal);
std::pair<uint32, bool> GetUintValue(hndl componentHandle, uint32 nameVal);
std::pair<f32, bool> GetFloatValue(hndl componentHandle, uint32 nameVal);
std::pair<bool8, bool> GetBoolValue(hndl componentHandle, uint32 nameVal);
std::pair<VectorType, bool> GetVectorValue(hndl componentHandle, uint32 nameVal);
std::pair<std::string, bool> GetStringValue(hndl componentHandle, uint32 nameVal);

END_DECLARE_COMPONENT(DataContainer)
