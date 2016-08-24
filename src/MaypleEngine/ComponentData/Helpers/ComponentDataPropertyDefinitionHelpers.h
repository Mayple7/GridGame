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
#pragma once

/*=================================
*      Vector Properties
*/
// Declares the get set property functionality for the given vector member
#define AUTO_GET_SET_PROPERTY_VECTOR2(COMPONENTNAME, NAME, CAMELNAME) \
Vector2 &COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, Vector2 newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
} 

#define AUTO_GET_SET_PROPERTY_VECTOR3(COMPONENTNAME, NAME, CAMELNAME) \
Vector3 &COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, Vector3 newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
}

#define AUTO_GET_SET_PROPERTY_VECTOR4(COMPONENTNAME, NAME, CAMELNAME) \
Vector4 &COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, Vector4 newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
}

/*=================================
*      Matrix Properties
*/
// Declares the get set property functionality for the given matrix member
#define AUTO_GET_SET_PROPERTY_MATRIX2(COMPONENTNAME, NAME, CAMELNAME) \
Matrix2 COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, Matrix2 newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
}

#define AUTO_GET_SET_PROPERTY_MATRIX3(COMPONENTNAME, NAME, CAMELNAME) \
Matrix3 COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, Matrix3 newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
}

#define AUTO_GET_SET_PROPERTY_MATRIX4(COMPONENTNAME, NAME, CAMELNAME) \
Matrix4 COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, Matrix4 newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
}

/*=================================
*      Special Properties
*/
// Declares the get set property functionality for the given member
#define AUTO_GET_SET_PROPERTY_STRING(COMPONENTNAME, NAME, CAMELNAME) \
std::string const& COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return GET_STRING_MANAGER->Hash(m_##CAMELNAME##Container[componentHandle]); \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, const std::string &newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = GET_STRING_MANAGER->Hash(newValue.c_str()); \
} 

// Declares the get set property functionality for the given member
#define AUTO_GET_SET_PROPERTY(TYPE, COMPONENTNAME, NAME, CAMELNAME) \
TYPE COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, TYPE newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
} 

#define AUTO_GET_SET_PROPERTY_CALL(TYPE, COMPONENTNAME, NAME, CAMELNAME, CALL) \
TYPE COMPONENTNAME##ComponentData::Get##NAME(hndl componentHandle) \
{ \
  return m_##CAMELNAME##Container[componentHandle]; \
} \
void COMPONENTNAME##ComponentData::Set##NAME(hndl componentHandle, TYPE newValue) \
{ \
  m_##CAMELNAME##Container[componentHandle] = newValue; \
  CALL(componentHandle); \
} 
