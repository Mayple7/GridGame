/*!****************************************************************************
\file    ComponentDataPropertyDefinitionHelpers.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Jun 11, 2015

\brief   Property definitions

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

/*=================================
*      Forward Declarations
*/

/*=================================
*      Macros
*/

/*=================================
*      Vectors
*/
#define AUTO_DYNAMIC_PROPERTY_REG_VECTOR(COMPONENTNAME, NAME, CAMELNAME) \
coreSpace::DynamicEntity COMPONENTNAME##ComponentData::ArbitraryGet##NAME(hndl componentHandle) \
{ \
  coreSpace::DynamicEntity val; \
  val.Set(GET_COMPONENT_DATA(COMPONENTNAME##ComponentData)->Get##NAME(componentHandle)); \
  return val; \
} \
void COMPONENTNAME##ComponentData::ArbitrarySet##NAME(hndl componentHandle, coreSpace::DynamicEntity newValue) \
{ \
  VectorType val; \
  newValue.Get(val); \
  GET_COMPONENT_DATA(COMPONENTNAME##ComponentData)->Set##NAME(componentHandle, val); \
} \
const int32 CONCATENATE(c_propertyGet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertyGetter(#COMPONENTNAME, #NAME, COMPONENTNAME##ComponentData::ArbitraryGet##NAME); \
const int32 CONCATENATE(c_propertySet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertySetter(#COMPONENTNAME, #NAME, COMPONENTNAME##ComponentData::ArbitrarySet##NAME);

// Declares the get set property functionality for the given vector member
#define AUTO_GET_SET_PROPERTY_VECTOR(COMPONENTNAME, NAME, CAMELNAME) \
AUTO_LUAREG_COMPONENT_PROPERTY_VECTOR(COMPONENTNAME, NAME); \
AUTO_DYNAMIC_PROPERTY_REG_VECTOR(COMPONENTNAME, NAME, CAMELNAME) \
void COMPONENTNAME##ComponentData::Set##NAME##Lua(hndl componentHandle, const scriptSpace::vectorBinding::LuaVector &newValue) \
{ \
  Set##NAME(componentHandle, math::CreateVectorType(newValue.m_vec[0], newValue.m_vec[1], newValue.m_vec[2])); \
} \
VectorType &COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void VECTOR_CALL COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, VectorType newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
} 

// Declares the get set property functionality for the given vector member
#define AUTO_GET_SET_PROPERTY_COLOR_NO_DYNAMIC(COMPONENTNAME, NAME, CAMELNAME) \
AUTO_LUAREG_COMPONENT_PROPERTY_VECTOR(COMPONENTNAME, NAME); \
void COMPONENTNAME##ComponentData::Set##NAME##Lua(hndl componentHandle, const scriptSpace::vectorBinding::LuaVector &newValue) \
{ \
  Set##NAME(componentHandle, math::CreateVectorType(newValue.m_vec[0], newValue.m_vec[1], newValue.m_vec[2], newValue.m_vec[3])); \
} \
VectorType &COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void VECTOR_CALL COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, VectorType newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
} 

#define AUTO_GET_SET_PROPERTY_COLOR(COMPONENTNAME, NAME, CAMELNAME) \
AUTO_LUAREG_COMPONENT_PROPERTY_VECTOR(COMPONENTNAME, NAME); \
AUTO_DYNAMIC_PROPERTY_REG_VECTOR(COMPONENTNAME, NAME, CAMELNAME) \
void COMPONENTNAME##ComponentData::Set##NAME##Lua(hndl componentHandle, const scriptSpace::vectorBinding::LuaVector &newValue) \
{ \
  Set##NAME(componentHandle, math::CreateVectorType(newValue.m_vec[0], newValue.m_vec[1], newValue.m_vec[2], newValue.m_vec[3])); \
} \
VectorType &COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void VECTOR_CALL COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, VectorType newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
} 


// Declares the get set property functionality for the given vector member
#define AUTO_GET_SET_PROPERTY_POINT(COMPONENTNAME, NAME, CAMELNAME) \
AUTO_LUAREG_COMPONENT_PROPERTY_VECTOR(COMPONENTNAME, NAME); \
void COMPONENTNAME##ComponentData::Set##NAME##Lua(hndl componentHandle, const scriptSpace::vectorBinding::LuaVector &newValue) \
{ \
  Set##NAME(componentHandle, math::CreateVectorType(newValue.m_vec[0], newValue.m_vec[1], newValue.m_vec[2], 1.0f)); \
} \
VectorType &COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void VECTOR_CALL COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, VectorType newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
} \
coreSpace::DynamicEntity COMPONENTNAME##ComponentData::ArbitraryGet##NAME(hndl componentHandle) \
{ \
  coreSpace::DynamicEntity val; \
  val.Set(GET_COMPONENT_DATA(COMPONENTNAME##ComponentData)->Get##NAME(componentHandle)); \
  return val; \
} \
void COMPONENTNAME##ComponentData::ArbitrarySet##NAME(hndl componentHandle, coreSpace::DynamicEntity newValue) \
{ \
  VectorType val; \
  newValue.Get(val); \
  GET_COMPONENT_DATA(COMPONENTNAME##ComponentData)->Set##NAME(componentHandle, val); \
} \
const int32 CONCATENATE(c_propertyGet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertyGetter(#COMPONENTNAME, #NAME, COMPONENTNAME##ComponentData::ArbitraryGet##NAME); \
const int32 CONCATENATE(c_propertySet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertySetter(#COMPONENTNAME, #NAME, COMPONENTNAME##ComponentData::ArbitrarySet##NAME);

// Declares the get set property functionality for the given matrix member
#define AUTO_GET_SET_PROPERTY_MATRIX(COMPONENTNAME, NAME, CAMELNAME) \
MatrixType COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void VECTOR_CALL COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, MatrixType newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
} \
coreSpace::DynamicEntity COMPONENTNAME##ComponentData::ArbitraryGet##NAME(hndl componentHandle) \
{ \
  coreSpace::DynamicEntity val; \
  val.Set(GET_COMPONENT_DATA(COMPONENTNAME##ComponentData)->Get##NAME(componentHandle)); \
  return val; \
} \
void COMPONENTNAME##ComponentData::ArbitrarySet##NAME(hndl componentHandle, coreSpace::DynamicEntity newValue) \
{ \
  MatrixType val; \
  newValue.Get(val); \
  GET_COMPONENT_DATA(COMPONENTNAME##ComponentData)->Set##NAME(componentHandle, val); \
} \
const int32 CONCATENATE(c_propertyGet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertyGetter(#COMPONENTNAME, #NAME, COMPONENTNAME##ComponentData::ArbitraryGet##NAME); \
const int32 CONCATENATE(c_propertySet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertySetter(#COMPONENTNAME, #NAME, COMPONENTNAME##ComponentData::ArbitrarySet##NAME);

// Declares the get set property functionality for the given member
#define AUTO_DYNAMIC_PROPERTY_REG_STRING(COMPONENTNAME, NAME, CAMELNAME) \
coreSpace::DynamicEntity COMPONENTNAME##ComponentData::ArbitraryGet##NAME(hndl componentHandle) \
{ \
  coreSpace::DynamicEntity val; \
  std::string str = std::string(GET_COMPONENT_DATA(COMPONENTNAME##ComponentData)->Get##NAME(componentHandle)); \
  val.Set(str); \
  return val; \
} \
void COMPONENTNAME##ComponentData::ArbitrarySet##NAME(hndl componentHandle, coreSpace::DynamicEntity newValue) \
{ \
  std::string val; \
  newValue.Get(val); \
  GET_COMPONENT_DATA(COMPONENTNAME##ComponentData)->Set##NAME(componentHandle, val); \
} \
const int32 CONCATENATE(c_propertyGet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertyGetter(#COMPONENTNAME, #NAME, COMPONENTNAME##ComponentData::ArbitraryGet##NAME); \
const int32 CONCATENATE(c_propertySet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertySetter(#COMPONENTNAME, #NAME, COMPONENTNAME##ComponentData::ArbitrarySet##NAME);


#define AUTO_GET_SET_PROPERTY_STRING(COMPONENTNAME, NAME, CAMELNAME) \
AUTO_LUAREG_COMPONENT_PROPERTY(COMPONENTNAME, NAME); \
AUTO_DYNAMIC_PROPERTY_REG_STRING(COMPONENTNAME, NAME, CAMELNAME) \
std::string const& COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return GET_STRING_MANAGER->Hash(m_##CAMELNAME##Container[componentHandle]); \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, const std::string &newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = GET_STRING_MANAGER->Hash(newValue.c_str()); \
} 

#define AUTO_DYNAMIC_PROPERTY_REG(TYPE, COMPONENTNAME, NAME, CAMELNAME) \
coreSpace::DynamicEntity COMPONENTNAME##ComponentData::ArbitraryGet##NAME(hndl componentHandle) \
{ \
  coreSpace::DynamicEntity val; \
  val.Set(GET_COMPONENT_DATA(COMPONENTNAME##ComponentData)->Get##NAME(componentHandle)); \
  return val; \
} \
void COMPONENTNAME##ComponentData::ArbitrarySet##NAME(hndl componentHandle, coreSpace::DynamicEntity newValue) \
{ \
  TYPE val; \
  newValue.Get(val); \
  GET_COMPONENT_DATA(COMPONENTNAME##ComponentData)->Set##NAME(componentHandle, val); \
} \
const int32 CONCATENATE(c_propertyGet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertyGetter(#COMPONENTNAME, #NAME, COMPONENTNAME##ComponentData::ArbitraryGet##NAME); \
const int32 CONCATENATE(c_propertySet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertySetter(#COMPONENTNAME, #NAME, COMPONENTNAME##ComponentData::ArbitrarySet##NAME);

// Declares the get set property functionality for the given member
#define AUTO_GET_SET_PROPERTY(TYPE, COMPONENTNAME, NAME, CAMELNAME) \
AUTO_LUAREG_COMPONENT_PROPERTY(COMPONENTNAME, NAME); \
AUTO_DYNAMIC_PROPERTY_REG(TYPE, COMPONENTNAME, NAME, CAMELNAME) \
TYPE COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, TYPE newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
} 
#define AUTO_GET_SET_PROPERTY_CALL(TYPE, COMPONENTNAME, NAME, CAMELNAME, CALL) \
AUTO_LUAREG_COMPONENT_PROPERTY(COMPONENTNAME, NAME); \
AUTO_DYNAMIC_PROPERTY_REG(TYPE, COMPONENTNAME, NAME, CAMELNAME) \
TYPE COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, TYPE newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
  CALL(componentHandle); \
} 

#define AUTO_GET_SET_PROPERTY_NO_DYNAMIC(TYPE, COMPONENTNAME, NAME, CAMELNAME) \
AUTO_LUAREG_COMPONENT_PROPERTY(COMPONENTNAME, NAME); \
TYPE COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, TYPE newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
} 

#define AUTO_GET_SET_PROPERTY_NO_DYNAMIC_CALL(TYPE, COMPONENTNAME, NAME, CAMELNAME, CALL) \
AUTO_LUAREG_COMPONENT_PROPERTY(COMPONENTNAME, NAME); \
TYPE COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, TYPE newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
  CALL(componentHandle); \
} 
