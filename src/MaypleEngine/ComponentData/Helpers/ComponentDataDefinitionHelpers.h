/*!****************************************************************************
\file    ComponentDataDefinitionHelpers.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Jun 11, 2015

\brief   Definition helper macros

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
*           Macros
*/
// Specifically for previously made components(Seths)
// Should use the START_DECLARE_COMPONENT_DEFINITION instead
#define REGISTER_COMPONENT(NAMESPACE, COMPONENTNAME, CAMELCOMPONENTNAME) \
void CONCATENATE(Initialize,COMPONENTNAME,ComponentData)(void); \
namespace \
{ \
  int32 s_componentIndex = componentSpace::ComponentDataLocator::RegisterComponent(CONCATENATE(Initialize,COMPONENTNAME,ComponentData)); \
} \
void CONCATENATE(Initialize,COMPONENTNAME,ComponentData)(void) \
{ \
  auto *data = (NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData)*)_aligned_malloc(sizeof(NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData)), SIMD_ALIGNMENT); \
  new (data)NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData)(); \
  componentSpace::ComponentDataLocator::SetDataWithIndex(data, s_componentIndex); \
} \
template <> \
NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData) *componentSpace::ComponentDataLocator::GetData<NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData)>() \
{ \
  return static_cast<NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData) *>(componentSpace::ComponentDataLocator::GetDataWithIndex(s_componentIndex));\
}

#define DEFINE_OBJECT_TO_COMPONENT_MULTIMAP(COMPONENTNAME) \
dataStructures::Array<int32>& COMPONENTNAME##ComponentData::_GetColliderHandlesFromObject(int32 objectHandle) \
{ \
  if(objectHandle >= m_objectToComponentHandles.GetCapacity()) \
    return m_nullObjectToComponentHandles; \
  if(!m_objectToComponentHandles.IsAlive(objectHandle)) \
    return m_objectToComponentHandles[objectHandle]; \
  return m_objectToComponentHandles[objectHandle]; \
} \
\
void COMPONENTNAME##ComponentData::_MapObjectToMultiComponentHandle(int32 componentHandle) \
{ \
  int32 objectHandle = GetObject(componentHandle); \
  \
  if (objectHandle >= m_objectToComponentHandles.GetCapacity()) \
  { \
    m_objectToComponentHandles.Expand(2 * objectHandle); \
  } \
  \
  m_objectToComponentHandles[objectHandle].PushBack(componentHandle); \
  m_objectToComponentHandles.SetAlive(objectHandle, true); \
} \
void COMPONENTNAME##ComponentData::_UnmapObjectToMultiComponentHandle(int32 componentHandle) \
{ \
  \
  int32 objectHandle = GetObject(componentHandle); \
  auto &objectToComponents = m_objectToComponentHandles[objectHandle]; \
  for (unsigned i = 0; i < objectToComponents.GetSize(); ++i) \
  { \
    int32 handle = objectToComponents[i]; \
    \
    if (componentHandle == handle) \
    { \
      std::swap(objectToComponents[i], objectToComponents[objectToComponents.GetSize() - 1]); \
      objectToComponents.PopBack(); \
      break; \
    } \
  } \
  \
  if (objectToComponents.GetSize() == 0)\
  { \
    m_objectToComponentHandles.SetAlive(objectHandle, false); \
  } \
} \

// Declares the definition part of the component
#define START_DECLARE_COMPONENT_DEFINITION(NAMESPACE, COMPONENTNAME, CAMELCOMPONENTNAME) \
REGISTER_COMPONENT(NAMESPACE, COMPONENTNAME, CAMELCOMPONENTNAME) \
namespace NAMESPACE \
{ \
  extern int CONCATENATE(dummy, COMPONENTNAME, AutoReg) = 0; \
  int CONCATENATE(dummy, COMPONENTNAME, AutoReg2) = ++CONCATENATE(dummy, COMPONENTNAME, AutoReg); \
  hndl COMPONENTNAME##ComponentData::GetComponent(hndl objectHandle) \
  { \
    if (!m_objectToComponentHandle.IsAlive(objectHandle)) \
    { \
      return INVALID_HANDLE; \
    } \
    return m_objectToComponentHandle[objectHandle]; \
  } \
  hndl COMPONENTNAME##ComponentData::GetObject(hndl componentHandle) \
  { \
    return m_componentToObjectHandle[componentHandle]; \
  } \
  hndl COMPONENTNAME##ComponentData::Create(hndl objectHandle) \
  { \
    hndl componentHandle; \
    _Create##COMPONENTNAME(&componentHandle); \
    _AddToObject(objectHandle, componentHandle); \
    return componentHandle; \
  } \
  void COMPONENTNAME##ComponentData::Destroy(hndl objectHandle) \
  { \
    hndl componentHandle = GetComponent(objectHandle); \
    if (componentHandle >= 0) \
    { \
      _Destroy##COMPONENTNAME(&componentHandle); \
      _RemoveFromObject(objectHandle, componentHandle); \
    } \
  } \
  int32 COMPONENTNAME##ComponentData::GetNumberOf##COMPONENTNAME(COMPONENTNAME##ComponentData *CAMELCOMPONENTNAME##Data, hndl objectHandle) \
  { \
    if (CAMELCOMPONENTNAME##Data->m_objectToComponentHandle.IsAlive(objectHandle)) \
      return 1; \
    return 0; \
  } \
  void COMPONENTNAME##ComponentData::_AddToObject(hndl objectHandle, hndl componentHandle) \
  { \
    if (objectHandle >= m_objectToComponentHandle.GetCapacity()) \
    { \
      m_objectToComponentHandle.Expand(2 * objectHandle); \
    } \
    m_objectToComponentHandle[objectHandle] = componentHandle; \
    m_objectToComponentHandle.SetAlive(objectHandle, true); \
    if (componentHandle >= m_componentToObjectHandle.GetCapacity()) \
    { \
      m_componentToObjectHandle.Expand(2 * componentHandle); \
    } \
    m_componentToObjectHandle[componentHandle] = objectHandle; \
    m_componentToObjectHandle.SetAlive(componentHandle, true); \
  } \
  void COMPONENTNAME##ComponentData::_RemoveFromObject(hndl objectHandle, hndl componentHandle) \
  { \
    m_objectToComponentHandle.SetAlive(objectHandle, false); \
    m_componentToObjectHandle.SetAlive(componentHandle, false); \
    m_objectToComponentHandle[objectHandle] = -1; \
    m_componentToObjectHandle[componentHandle] = -1; \
  } \
  hndl COMPONENTNAME##ComponentData::GetComponentStatic(hndl objectHandle) \
  { \
    return GET_COMPONENT_DATA(NAMESPACE::COMPONENTNAME##ComponentData)->GetComponent(objectHandle); \
  } \
  void COMPONENTNAME##ComponentData::AddToObjectStatic(COMPONENTNAME##ComponentData *CAMELCOMPONENTNAME##Data, hndl objectHandle, hndl componentHandle) \
  { \
    CAMELCOMPONENTNAME##Data->_AddToObject(objectHandle, componentHandle); \
  } \
  void COMPONENTNAME##ComponentData::_Create##COMPONENTNAME(hndl *componentHandle) \
  { \
    Construct##COMPONENTNAME((void *)componentHandle); \
  } \
  void COMPONENTNAME##ComponentData::_Destroy##COMPONENTNAME(hndl *componentHandle) \
  { \
    Destruct##COMPONENTNAME((void*)componentHandle); \
  }

// End of a component's definition
#define END_DECLARE_COMPONENT_DEFINITION \
}

#define ATTACH_CONSTRUCT(MEMBER, INDEX, TYPE) \
    if (args && args[INDEX]) \
    { \
      Set##MEMBER(newComponent, args[INDEX]->cast<TYPE>()); \
    }
#define ATTACH_CONSTRUCT_VECTOR(MEMBER, INDEX) \
    if (args && args[INDEX]) \
    { \
      Set##MEMBER(newComponent, math::CreateVectorType(args[INDEX]->cast<scriptSpace::vectorBinding::LuaVector>().m_vec)); \
    }
