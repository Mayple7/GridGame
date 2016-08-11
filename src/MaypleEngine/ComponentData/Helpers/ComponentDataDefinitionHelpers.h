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
DECLARE_JOB(CONCATENATE(Initialize,COMPONENTNAME,ComponentData)); \
namespace \
{ \
  int32 s_componentIndex = componentSpace::ComponentDataLocator::RegisterComponent(CONCATENATE(Initialize,COMPONENTNAME,ComponentData)); \
} \
DECLARE_JOB(CONCATENATE(Initialize,COMPONENTNAME,ComponentData)) \
{ \
  START_JOB; \
  auto *data = (NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData)*)_aligned_malloc(sizeof(NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData)), SIMD_ALIGNMENT); \
  new (data)NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData)(); \
  data->_PushExecutionNodes(); \
  componentSpace::ComponentDataLocator::SetDataWithIndex(data, s_componentIndex); \
  END_JOB; \
} \
template <> \
NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData) *componentSpace::ComponentDataLocator::GetData<NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData)>() \
{ \
  return static_cast<NAMESPACE::CONCATENATE(COMPONENTNAME,ComponentData) *>(componentSpace::ComponentDataLocator::GetDataWithIndex(s_componentIndex));\
}

#define SDEF_BIND(NAMESPACE, COMPONENTNAME) \
namespace scriptSpace \
{ \
  COMPONENTNAME##Bind::COMPONENTNAME##Bind() {} \
  COMPONENTNAME##Bind::~COMPONENTNAME##Bind() {} \
  COMPONENTNAME##Bind::COMPONENTNAME##Bind(hndl newHandle) : BaseBind(newHandle) \
  {} \
  COMPONENTNAME##Bind::COMPONENTNAME##Bind(COMPONENTNAME##Bind const& rhs) \
  { \
    m_handle = rhs.m_handle; \
  } \
  std::string COMPONENTNAME##Bind::ToString() const \
  { \
    return #COMPONENTNAME + std::string(" Component"); \
  } \
  luabridge::LuaRef COMPONENTNAME##Bind::Lua##COMPONENTNAME##FromObject(hndl objectHandle) \
  { \
    int32 componentHandle = GET_COMPONENT_DATA(NAMESPACE::COMPONENTNAME##ComponentData)->GetComponent(objectHandle); \
    return luabridge::LuaRef(GET_SCRIPT_MANAGER->m_state, COMPONENTNAME##Bind(componentHandle)); \
  } \
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
SDEF_BIND(NAMESPACE, COMPONENTNAME) \
namespace NAMESPACE \
{ \
  AUTO_LUAREG_COMPONENT_CLASS(COMPONENTNAME); \
  extern int CONCATENATE(dummy, COMPONENTNAME, AutoReg) = 0; \
  int CONCATENATE(dummy, COMPONENTNAME, AutoReg2) = ++CONCATENATE(dummy, COMPONENTNAME, AutoReg); \
  int CONCATENATE(dummy, COMPONENTNAME, StringFn) = scriptSpace::LuaDataManager::RegisterMemberFunc(#COMPONENTNAME, "__tostring", scriptSpace::AddMemberFunction < decltype(&scriptSpace::COMPONENTNAME##Bind::ToString), &scriptSpace::COMPONENTNAME##Bind::ToString > ); \
  int CONCATENATE(dummy, COMPONENTNAME, AttachFn) = scriptSpace::LuaDataManager::RegisterAttachFunc(#COMPONENTNAME, scriptSpace::AddAttachComponent< COMPONENTNAME##ComponentData, decltype(&COMPONENTNAME##ComponentData::AttachComponent), &COMPONENTNAME##ComponentData::AttachComponent > ); \
  int CONCATENATE(dummy, COMPONENTNAME, DetachFn) = scriptSpace::LuaDataManager::RegisterDetachFunc(#COMPONENTNAME, scriptSpace::AddDetachComponent< COMPONENTNAME##ComponentData, decltype(&COMPONENTNAME##ComponentData::DetachComponent), &COMPONENTNAME##ComponentData::DetachComponent > ); \
  int CONCATENATE(dummy, COMPONENTNAME, LuaGetFn) = scriptSpace::LuaDataManager::RegisterLuaComponentFromObject(#COMPONENTNAME, scriptSpace::COMPONENTNAME##Bind::Lua##COMPONENTNAME##FromObject); \
  int CONCATENATE(dummy, COMPONENTNAME, GetComFn) = scriptSpace::LuaDataManager::RegisterGetComponentHandleFunc(#COMPONENTNAME, COMPONENTNAME##ComponentData::GetComponentStatic); \
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
  } \
  AUTO_LUAREG_COMPONENT_PROPERTY_READONLY(COMPONENTNAME, Owner); \
  luabridge::LuaRef COMPONENTNAME##ComponentData::GetOwner(hndl componentHandle) \
  { \
    if (GET_COMPONENT_DATA(NAMESPACE::COMPONENTNAME##ComponentData)->GetObject(componentHandle) == INVALID_HANDLE) \
      return luabridge::LuaRef(GET_SCRIPT_MANAGER->m_state, luabridge::Nil()); \
    else \
      return luabridge::LuaRef(GET_SCRIPT_MANAGER->m_state, scriptSpace::objectBinding::Obj(GET_COMPONENT_DATA(NAMESPACE::COMPONENTNAME##ComponentData)->GetObject(componentHandle))); \
  }

// End of a component's definition
#define END_DECLARE_COMPONENT_DEFINITION \
}

// Creates an execution node for a transform (name of node, variable amount of functions)
#define REGISTER_COMPONENT_TRANSFORMS(NAME, ...) \
{ \
  jobSpace::DataTransform transforms[] = \
  { \
    __VA_ARGS__ \
  }; \
GET_EXECUTION_MANAGER->RegisterExecutionNode(executionSpace::ExecutionNodeConfig(NAME), transforms, sizeof(transforms) / sizeof(transforms[0])); \
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
