/*!****************************************************************************
\file    ComponentDataDeclarationHelpers.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Jun 11, 2015

\brief   Declaration Helpers

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
#include "DynamicEntity.h"

/*=================================
*      Forward Declarations
*/

/*=================================
*       Macros
*/
// Stat Declare helper macros
#define FORWARD_DECLARE_COMPONENT \
namespace componentSpace \
{ \
  struct ComponentData; \
} 

// Declares the declaration part of a component
#define START_DECLARE_COMPONENT(NAMESPACE, COMPONENTNAME, CAMELCOMPONENTNAME) \
FORWARD_DECLARE_COMPONENT \
namespace NAMESPACE \
{ \
  void Initialize##COMPONENTNAME##ComponentData(); \
  extern int CONCATENATE(dummy, COMPONENTNAME, AutoReg); \
  void Construct##COMPONENTNAME(hndl* data); \
  void Destruct##COMPONENTNAME(hndl* data); \
  struct COMPONENTNAME##ComponentData \
  { \
    hndl Create(hndl objectHandle); \
    void Destroy(hndl objectHandle); \
    COMPONENTNAME##ComponentData(); \
    dataStructures::SlotMap<int32> m_objectToComponentHandle; \
    dataStructures::SlotMap<int32> m_componentToObjectHandle; \
    hndl GetComponent(hndl objectHandle); \
    hndl GetObject(hndl componentHandle); \
    static hndl GetComponentStatic(hndl objectHandle); \
    static void AddToObjectStatic(CONCATENATE(COMPONENTNAME, ComponentData) *CAMELCOMPONENTNAME##Data, hndl objectHandle, hndl componentHandle); \
    static int32 GetNumberOf##COMPONENTNAME(COMPONENTNAME##ComponentData *CAMELCOMPONENTNAME##Data, hndl objectHandle); \
    hndl AttachComponent(hndl objectHandle); \
    void DetachComponent(hndl objectHandle); \
    std::vector<hndl> m_alive##COMPONENTNAME; \
    void _AddToObject(hndl objectHandle, hndl componentHandle); \

// End of a component's declaration
#define END_DECLARE_COMPONENT(COMPONENTNAME) \
  private: \
    void _RemoveFromObject(hndl objectHandle, hndl componentHandle); \
    void _Create##COMPONENTNAME(hndl *data); \
    void _Destroy##COMPONENTNAME(hndl *data); \
  }; \
}

#define AUTO_DECLARE_GET_SET_FUNCTIONS(TYPE, NAME) \
  void Set##NAME(hndl componentHandle, TYPE CAMELNAME); \
  TYPE Get##NAME(hndl componentHandle); \

// Declares a getter, setter and a member container of the given type with the given name
#define AUTO_DECLARE_GET_SET_PROPERTY(TYPE, NAME, CAMELNAME) \
  dataStructures::SlotMap<TYPE> m_##CAMELNAME##Container; \
  AUTO_DECLARE_GET_SET_FUNCTIONS(TYPE, NAME)

#define AUTO_DECLARE_GET_SET_PROPERTY_STRING(NAME, CAMELNAME) \
  dataStructures::SlotMap<size_t> m_##CAMELNAME##Container; \
  void Set##NAME(hndl componentHandle, const std::string &CAMELNAME); \
  std::string const& Get##NAME(hndl componentHandle); \

// Declares a getter, setter and a member container of vector type with the given name
#define AUTO_DECLARE_GET_SET_PROPERTY_VECTOR2_FUNCTIONS(NAME) \
  void Set##NAME(hndl componentHandle, Vector2 CAMELNAME); \
  Vector2 &Get##NAME(hndl componentHandle); \

#define AUTO_DECLARE_GET_SET_PROPERTY_VECTOR2(NAME, CAMELNAME) \
  dataStructures::SlotMap<Vector2> m_##CAMELNAME##Container; \
  AUTO_DECLARE_GET_SET_PROPERTY_VECTOR2_FUNCTIONS(NAME); \

// Declares a getter, setter and a member container of vector type with the given name
#define AUTO_DECLARE_GET_SET_PROPERTY_VECTOR3_FUNCTIONS(NAME) \
  void Set##NAME(hndl componentHandle, Vector3 CAMELNAME); \
  Vector3 &Get##NAME(hndl componentHandle); \

#define AUTO_DECLARE_GET_SET_PROPERTY_VECTOR3(NAME, CAMELNAME) \
  dataStructures::SlotMap<Vector3> m_##CAMELNAME##Container; \
  AUTO_DECLARE_GET_SET_PROPERTY_VECTOR3_FUNCTIONS(NAME); \

// Declares a getter, setter and a member container of matrix type with the given name
#define AUTO_DECLARE_GET_SET_PROPERTY_MATRIX_FUNCTIONS(NAME); \
  void Set##NAME(hndl componentHandle, MatrixType CAMELNAME); \
  MatrixType Get##NAME(hndl componentHandle); \

#define AUTO_DECLARE_GET_SET_PROPERTY_MATRIX(NAME, CAMELNAME) \
  dataStructures::SlotMap<MatrixType> m_##CAMELNAME##Container; \
  AUTO_DECLARE_GET_SET_PROPERTY_MATRIX_FUNCTIONS(NAME); \

// Declares a member container (No getter or setter)
#define AUTO_DECLARE_PROPERTY_ONLY(TYPE, CAMELNAME) \
  dataStructures::SlotMap<TYPE> m_##CAMELNAME##Container;
