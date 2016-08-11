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

/*=================================
*      Forward Declarations
*/

/*=================================
*       Macros
*/
// Stat Declare helper macros
#define SDECL_FORWARD \
namespace componentSpace \
{ \
  struct ComponentData; \
} 

#define SDECL_COMPONENT_BIND(COMPONENTNAME) \
namespace scriptSpace \
{ \
  class COMPONENTNAME##Bind : public BaseBind \
  { \
  public: \
    COMPONENTNAME##Bind(); \
    virtual ~COMPONENTNAME##Bind(); \
    COMPONENTNAME##Bind(hndl newHandle); \
    COMPONENTNAME##Bind(COMPONENTNAME##Bind const& rhs); \
    std::string ToString() const; \
    static luabridge::LuaRef COMPONENTNAME##Bind::Lua##COMPONENTNAME##FromObject(hndl component); \
  }; \
} \

#define DECLARE_OBJECT_TO_COMPONENT_MULTI_MAP \
dataStructures::SlotMap<dataStructures::Array<int32>> m_objectToComponentHandles; \
dataStructures::Array<int32> m_nullObjectToComponentHandles; \
dataStructures::Array<int32>& _GetColliderHandlesFromObject(int32 objectHandle); \
void _MapObjectToMultiComponentHandle(int32 componentHandle); \
void _UnmapObjectToMultiComponentHandle(int32 componentHandle); \

// Declares the declaration part of a component
#define START_DECLARE_COMPONENT(NAMESPACE, COMPONENTNAME, CAMELCOMPONENTNAME) \
SDECL_FORWARD \
SDECL_COMPONENT_BIND(COMPONENTNAME) \
namespace NAMESPACE \
{ \
  void Initialize##COMPONENTNAME##ComponentData(); \
  extern int CONC(dummy, COMPONENTNAME, AutoReg); \
  void Construct##COMPONENTNAME(); \
  void Destruct##COMPONENTNAME(); \
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
    static void AddToObjectStatic(CONC(COMPONENTNAME, ComponentData) *CAMELCOMPONENTNAME##Data, hndl objectHandle, hndl componentHandle); \
    static int32 GetNumberOf##COMPONENTNAME(COMPONENTNAME##ComponentData *CAMELCOMPONENTNAME##Data, hndl objectHandle); \
    hndl AttachComponent(hndl objectHandle, luabridge::LuaRef **args); \
    void DetachComponent(hndl objectHandle); \
    void _PushExecutionNodes(void) const; \
    dataStructures::Array<hndl> m_alive##COMPONENTNAME; \
    luabridge::LuaRef GetOwner(hndl componentHandle); \
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
  static coreSpace::DynamicEntity ArbitraryGet##NAME(hndl componentHandle); \
  static void ArbitrarySet##NAME(hndl componentHandle, coreSpace::DynamicEntity newValue);

// Declares a getter, setter and a member container of the given type with the given name
#define AUTO_DECLARE_GET_SET_PROPERTY(TYPE, NAME, CAMELNAME) \
  dataStructures::SlotMap<TYPE> m_##CAMELNAME##Container; \
  AUTO_DECLARE_GET_SET_FUNCTIONS(TYPE, NAME)

#define AUTO_DECLARE_GET_SET_PROPERTY_STRING(NAME, CAMELNAME) \
  dataStructures::SlotMap<size_t> m_##CAMELNAME##Container; \
  void Set##NAME(hndl componentHandle, const std::string &CAMELNAME); \
  std::string const& Get##NAME(hndl componentHandle); \
  static coreSpace::DynamicEntity ArbitraryGet##NAME(hndl componentHandle); \
  static void ArbitrarySet##NAME(hndl componentHandle, coreSpace::DynamicEntity newValue);

// Declares a getter, setter and a member container of vector type with the given name
#define AUTO_DECLARE_GET_SET_PROPERTY_VECTOR_FUNCTIONS(NAME) \
  scriptSpace::vectorBinding::LuaVector Get##NAME##Lua(hndl componentHandle); \
  void Set##NAME##Lua(hndl componentHandle, const scriptSpace::vectorBinding::LuaVector &newValue); \
  void VECTOR_CALL Set##NAME(hndl componentHandle, VectorType CAMELNAME); \
  VectorType &Get##NAME(hndl componentHandle); \
  static coreSpace::DynamicEntity ArbitraryGet##NAME(hndl componentHandle); \
  static void ArbitrarySet##NAME(hndl componentHandle, coreSpace::DynamicEntity newValue);

#define AUTO_DECLARE_GET_SET_PROPERTY_VECTOR(NAME, CAMELNAME) \
  dataStructures::SlotMap<VectorType> m_##CAMELNAME##Container; \
  AUTO_DECLARE_GET_SET_PROPERTY_VECTOR_FUNCTIONS(NAME); \

// Declares a getter, setter and a member container of matrix type with the given name
#define AUTO_DECLARE_GET_SET_PROPERTY_MATRIX_FUNCTIONS(NAME); \
  scriptSpace::cframeBinding::LuaCFrame Get##NAME##Lua(hndl componentHandle); \
  void Set##NAME##Lua(hndl componentHandle, const scriptSpace::cframeBinding::LuaCFrame &newValue); \
  void VECTOR_CALL Set##NAME(hndl componentHandle, MatrixType CAMELNAME); \
  MatrixType Get##NAME(hndl componentHandle); \
  static coreSpace::DynamicEntity ArbitraryGet##NAME(hndl componentHandle); \
  static void ArbitrarySet##NAME(hndl componentHandle, coreSpace::DynamicEntity newValue);

#define AUTO_DECLARE_GET_SET_PROPERTY_MATRIX(NAME, CAMELNAME) \
  dataStructures::SlotMap<MatrixType> m_##CAMELNAME##Container; \
  AUTO_DECLARE_GET_SET_PROPERTY_MATRIX_FUNCTIONS(NAME); \

// Declares a member container (No getter or setter)
#define AUTO_DECLARE_PROPERTY_ONLY(TYPE, CAMELNAME) \
  dataStructures::SlotMap<TYPE> m_##CAMELNAME##Container;
