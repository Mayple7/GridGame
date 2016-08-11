/*!****************************************************************************
\file    DynamicEntity.h
\author  Kaden Nugent (kaden.n)
\date    July 19, 2015

\brief   A dynamic entity for arbitrary component data retrieval.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include <map>
#include <string>

#include "CustomTypes.h" // Diesel engine types

namespace physicsSpace
{
  enum Rigidbody_Type_;
}

namespace scriptSpace
{
  struct ScriptEntity;
}

namespace audioSpace
{
  class ActiveAudioEvent;
}

namespace coreSpace
{
  class DataEntity;

  enum Dynamic_Type_
  {
    Type_Null_,
    Type_Int_,
    Type_Int64_,
    Type_Uint_,
    Type_Uint64_,
    Type_Float_,
    Type_Bool_,
    Type_Rigidbody_,
    Type_Vector_,
    Type_Matrix_,
    Type_Script_,
    Type_Data_,
    Type_String_,
    Type_Array_
  };

  class DynamicEntity
  {
  public:
    DynamicEntity();
    DynamicEntity(const DynamicEntity& dynamicEntity);
    ~DynamicEntity();

    DynamicEntity& operator=(const DynamicEntity& dynamicEntity);
    bool operator==(const DynamicEntity& rhs) const;
    bool operator!=(const DynamicEntity& rhs) const;

    void Set(int32 val);
    void Set(int64 val);
    void Set(uint32 val);
    void Set(uint64 val);
    void Set(f32 val);
    void Set(bool8 val);
    void Set(std::string &val);
    void Set(VectorType &val);
    void Set(MatrixType &val);
    void Set(scriptSpace::ScriptEntity &val);
    void Set(DataEntity &val);
    void Set(physicsSpace::Rigidbody_Type_ val);
    void Set(std::vector<DynamicEntity> &val);

    void Get(int32 &val) const;
    void Get(int64 &val) const;
    void Get(uint32 &val) const;
    void Get(uint64 &val) const;
    void Get(f32 &val) const;
    void Get(bool8 &val) const;
    void Get(std::string &val) const;
    void Get(VectorType &val) const;
    void Get(MatrixType &val) const;
    void Get(scriptSpace::ScriptEntity &val) const;
    void Get(DataEntity &val) const;
    void Get(physicsSpace::Rigidbody_Type_ &val) const;
    void Get(std::vector<DynamicEntity> &val) const;

    // Get the current type of the dynamic entity
    Dynamic_Type_ Type() const;

  private:
    union
    {
      int32 m_int;
      int64 m_int64;
      uint32 m_uint;
      uint64 m_uint64;
      f32 m_float;
      bool8 m_bool;
      std::string *m_stringPtr;
      VectorType *m_vectorPtr;
      MatrixType *m_matrixPtr;
      scriptSpace::ScriptEntity *m_scriptPtr;
      DataEntity *m_dataPtr;
      physicsSpace::Rigidbody_Type_ m_rigidBody;

      std::vector<DynamicEntity> *m_arrayPtr;
    } m_data;

    Dynamic_Type_ m_type;

  };
}
