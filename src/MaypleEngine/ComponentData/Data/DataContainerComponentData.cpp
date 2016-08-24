/*!****************************************************************************
\file    DataComponentData.cpp
\author  Dan Muller (d.muller)
\date    July 30, 2015

\brief	 Data for data components.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

////////////////////////////////////////////////////////////////////////// DEPENDENCIES

// Standard include
#include "stdinc.h"

// This component's header files
#include "DataContainerComponentData.h"

// Managers
#include "ManagerLocator.h"

// General component data
#include "ComponentDataLocator.h"
#include "ComponentData.h"

// Job related
#include "DebugManager.h"

////////////////////////////////////////////////////////////////////////// MACROS

////////////////////////////////////////////////////////////////////////// DECLARATIONS

START_DECLARE_COMPONENT_DEFINITION(coreSpace, DataContainer, dataContainer)

  START_DECLARE_COMPONENT_CONSTRUCTION(coreSpace, DataContainer, dataContainer)
    INITIALIZE_SLOT(dataEntity, dataContainer);
  END_DECLARE_COMPONENT_CONSTRUCTION

  START_DECLARE_COMPONENT_DESTRUCTION(coreSpace, DataContainer, dataContainer)
    UNINITIALIZE_SLOT(dataEntity, dataContainer);
  END_DECLARE_COMPONENT_DESTRUCTION

// Constructor
DataContainerComponentData::DataContainerComponentData(void) : m_dataEntityContainer(10, -1, true, false)
{
}

hndl DataContainerComponentData::AttachComponent(hndl objectHandle)
{
  hndl newComponent = Create(objectHandle);

  return newComponent;
}

void DataContainerComponentData::DetachComponent(hndl objectHandle)
{
  hndl componentHandle = GetComponent(objectHandle);

  if(m_dataEntityContainer.IsAlive(componentHandle))
  {
    // Remove all data containers
    for(hndl j = 0; j < m_dataEntityContainer[componentHandle].GetCapacity(); ++j)
    {
      if(m_dataEntityContainer[componentHandle].IsAlive(j))
      {
        m_dataEntityContainer[componentHandle].Remove(j);
      }
    }
  }

  Destroy(objectHandle);
}

////////////////////////////////////////////////////////////////////////// Special data grabbing

dataStructures::SlotMap<DataEntity> DataContainerComponentData::GetDataEntity(hndl componentHandle)
{
  return m_dataEntityContainer[componentHandle];
}

void DataContainerComponentData::SetDataEntity(hndl componentHandle, dataStructures::SlotMap<DataEntity> newValue)
{
  m_dataEntityContainer[componentHandle] = newValue;
}

// New Data entity in the container
void DataContainerComponentData::NewIntValue(hndl componentHandle, std::string newName, int32 newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Data name
  if(newName.empty())
  {
    // Data name is required
    GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data name required!");
  }
  else
  {
    DataEntity currEntity;

    // Set the name for the data entity
    currEntity.m_name = HASH_GEN(newName);

    // Verify there is no duplicate names
    for(int i = 0; i < currContainer.GetSize(); ++i)
    {
      if(currContainer.IsAlive(i) && currContainer[i].m_name == currEntity.m_name)
      {
        GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data names must be different!");
        return;
      }
    }

    // Creates the new data entity
    currEntity.m_id = ++dataID;
    currEntity.Set(newValue);

    // Create the slot in the container
    currContainer[currContainer.AllocateSlot()] = currEntity;
  }
}

void DataContainerComponentData::NewUintValue(hndl componentHandle, std::string newName, uint32 newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Data name
  if(newName.empty())
  {
    // Data name is required
    GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data name required!");
  }
  else
  {
    DataEntity currEntity;

    // Set the name for the data entity
    currEntity.m_name = HASH_GEN(newName);

    // Verify there is no duplicate names
    for(int i = 0; i < currContainer.GetSize(); ++i)
    {
      if(currContainer.IsAlive(i) && currContainer[i].m_name == currEntity.m_name)
      {
        GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data names must be different!");
        return;
      }
    }

    // Creates the new data entity
    currEntity.m_id = ++dataID;
    currEntity.Set(newValue);

    // Create the slot in the container
    currContainer[currContainer.AllocateSlot()] = currEntity;
  }
}

void DataContainerComponentData::NewFloatValue(hndl componentHandle, std::string newName, f32 newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Data name
  if(newName.empty())
  {
    // Data name is required
    GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data name required!");
  }
  else
  {
    DataEntity currEntity;

    // Set the name for the data entity
    currEntity.m_name = HASH_GEN(newName);

    // Verify there is no duplicate names
    for(int i = 0; i < currContainer.GetSize(); ++i)
    {
      if(currContainer.IsAlive(i) && currContainer[i].m_name == currEntity.m_name)
      {
        GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data names must be different!");
        return;
      }
    }

    // Creates the new data entity
    currEntity.m_id = ++dataID;
    currEntity.Set(newValue);

    // Create the slot in the container
    currContainer[currContainer.AllocateSlot()] = currEntity;
  }
}

void DataContainerComponentData::NewBoolValue(hndl componentHandle, std::string newName, bool8 newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Data name
  if(newName.empty())
  {
    // Data name is required
    GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data name required!");
  }
  else
  {
    DataEntity currEntity;

    // Set the name for the data entity
    currEntity.m_name = HASH_GEN(newName);

    // Verify there is no duplicate names
    for(int i = 0; i < currContainer.GetSize(); ++i)
    {
      if(currContainer.IsAlive(i) && currContainer[i].m_name == currEntity.m_name)
      {
        GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data names must be different!");
        return;
      }
    }

    // Creates the new data entity
    currEntity.m_id = ++dataID;
    currEntity.Set(newValue);

    // Create the slot in the container
    currContainer[currContainer.AllocateSlot()] = currEntity;
  }
}

void DataContainerComponentData::NewVectorValue(hndl componentHandle, std::string newName, VectorType& newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Data name
  if(newName.empty())
  {
    // Data name is required
    GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data name required!");
  }
  else
  {
    DataEntity currEntity;

    // Set the name for the data entity
    currEntity.m_name = HASH_GEN(newName);

    // Verify there is no duplicate names
    for(int i = 0; i < currContainer.GetSize(); ++i)
    {
      if(currContainer.IsAlive(i) && currContainer[i].m_name == currEntity.m_name)
      {
        GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data names must be different!");
        return;
      }
    }

    // Creates the new data entity
    currEntity.m_id = ++dataID;
    currEntity.Set(newValue);

    // Create the slot in the container
    currContainer[currContainer.AllocateSlot()] = currEntity;
  }
}

void DataContainerComponentData::NewStringValue(hndl componentHandle, std::string newName, std::string newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Data name
  if(newName.empty())
  {
    // Data name is required
    GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data name required!");
  }
  else
  {
    DataEntity currEntity;

    // Set the name for the data entity
    currEntity.m_name = HASH_GEN(newName);

    // Verify there is no duplicate names
    for(int i = 0; i < currContainer.GetSize(); ++i)
    {
      if(currContainer.IsAlive(i) && currContainer[i].m_name == currEntity.m_name)
      {
        GET_DEBUG_MANAGER->HandleAssertFailure(__FILE__, __LINE__, "%s", "Data names must be different!");
        return;
      }
    }

    // Creates the new data entity
    currEntity.m_id = ++dataID;
    currEntity.Set(newValue);

    // Create the slot in the container
    currContainer[currContainer.AllocateSlot()] = currEntity;
  }
}

// Set value overloads for C++
void DataContainerComponentData::SetIntValue(hndl componentHandle, uint32 nameVal, int32 newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Verify there is no duplicate names
  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Set(newValue);
      return;
    }
  }
}

void DataContainerComponentData::SetUintValue(hndl componentHandle, uint32 nameVal, uint32 newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Verify there is no duplicate names
  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Set(newValue);
      return;
    }
  }
}

void DataContainerComponentData::SetFloatValue(hndl componentHandle, uint32 nameVal, f32 newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Verify there is no duplicate names
  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Set(newValue);
      return;
    }
  }
}

void DataContainerComponentData::SetBoolValue(hndl componentHandle, uint32 nameVal, bool8 newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Verify there is no duplicate names
  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Set(newValue);
      return;
    }
  }
}

void DataContainerComponentData::SetVectorValue(hndl componentHandle, uint32 nameVal, VectorType& newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Verify there is no duplicate names
  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Set(newValue);
      return;
    }
  }
}

void DataContainerComponentData::SetStringValue(hndl componentHandle, uint32 nameVal, std::string newValue)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];

  // Verify there is no duplicate names
  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Set(newValue);
      return;
    }
  }
}

// Get value overloads for C++
std::pair<int32, bool> DataContainerComponentData::GetIntValue(hndl componentHandle, uint32 nameVal)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];
  bool valueExists = false;
  int32 result;

  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Get(result);
      valueExists = true;
      break;
    }
  }

  return std::make_pair(result, valueExists);
}

std::pair<uint32, bool> DataContainerComponentData::GetUintValue(hndl componentHandle, uint32 nameVal)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];
  bool valueExists = false;
  uint32 result;

  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Get(result);
      valueExists = true;
      break;
    }
  }

  return std::make_pair(result, valueExists);
}

std::pair<f32, bool> DataContainerComponentData::GetFloatValue(hndl componentHandle, uint32 nameVal)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];
  bool valueExists = false;
  f32 result;

  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Get(result);
      valueExists = true;
      break;
    }
  }

  return std::make_pair(result, valueExists);
}

std::pair<bool8, bool> DataContainerComponentData::GetBoolValue(hndl componentHandle, uint32 nameVal)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];
  bool valueExists = false;
  bool8 result;

  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Get(result);
      valueExists = true;
      break;
    }
  }

  return std::make_pair(result, valueExists);
}

std::pair<VectorType, bool> DataContainerComponentData::GetVectorValue(hndl componentHandle, uint32 nameVal)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];
  bool valueExists = false;
  VectorType result;

  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Get(result);
      valueExists = true;
      break;
    }
  }

  return std::make_pair(result, valueExists);
}

std::pair<std::string, bool> DataContainerComponentData::GetStringValue(hndl componentHandle, uint32 nameVal)
{
  auto& currContainer = m_dataEntityContainer[componentHandle];
  bool valueExists = false;
  std::string result;

  for(int i = 0; i < currContainer.GetSize(); ++i)
  {
    if(currContainer.IsAlive(i) && currContainer[i].m_name == nameVal)
    {
      currContainer[i].Get(result);
      valueExists = true;
      break;
    }
  }

  return std::make_pair(result, valueExists);
}

// Jobs
void DataContainerComponentData::_PushExecutionNodes(void) const
{

}

END_DECLARE_COMPONENT_DEFINITION