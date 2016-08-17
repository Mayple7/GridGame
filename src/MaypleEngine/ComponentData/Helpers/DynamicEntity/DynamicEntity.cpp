/*!****************************************************************************
\file    DynamicEntity.cpp
\author  Kaden Nugent (kaden.n)
\date    July 19, 2015

\brief   A dynamic entity for arbitrary component data retrieval.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"

// This header file
#include "DynamicEntity.h"

#include "DataEntity.h"         // Container for user data

// If anything needs to be cleared form the dynamic entity, this does it
#define CLEAR_DYNAMIC_TYPE \
if (m_type == Type_String_) \
  delete m_data.m_stringPtr; \
else if (m_type == Type_Vector_) \
  _aligned_free(m_data.m_vectorPtr); \
else if (m_type == Type_Matrix_) \
  _aligned_free(m_data.m_matrixPtr); \
else if (m_type == Type_Data_) \
  delete m_data.m_dataPtr; \
else if (m_type == Type_Array_) \
  delete m_data.m_arrayPtr;

#define COPY_DYNAMIC_TYPE \
m_type = dynamicEntity.m_type; \
if (dynamicEntity.m_type == Type_String_) \
  m_data.m_stringPtr = new std::string(*dynamicEntity.m_data.m_stringPtr); \
else if (dynamicEntity.m_type == Type_Vector_) \
{ \
  m_data.m_vectorPtr = new VectorType(*dynamicEntity.m_data.m_vectorPtr); \
} \
else if (dynamicEntity.m_type == Type_Matrix_) \
{ \
  m_data.m_matrixPtr = new MatrixType(*dynamicEntity.m_data.m_matrixPtr); \
} \
else if (dynamicEntity.m_type == Type_Data_) \
{ \
  m_data.m_dataPtr = new DataEntity(*dynamicEntity.m_data.m_dataPtr); \
} \
else if (dynamicEntity.m_type == Type_Array_) \
{ \
  m_data.m_arrayPtr = new std::vector<DynamicEntity>(*dynamicEntity.m_data.m_arrayPtr); \
} \
else \
  m_data = dynamicEntity.m_data;

namespace coreSpace
{
  DynamicEntity::DynamicEntity()
  {
    m_type = Type_Null_;
  }

  DynamicEntity::DynamicEntity(const DynamicEntity& dynamicEntity)
  {
    COPY_DYNAMIC_TYPE
  }

  DynamicEntity::~DynamicEntity()
  {
    CLEAR_DYNAMIC_TYPE
  }

  DynamicEntity& DynamicEntity::operator=(const DynamicEntity& dynamicEntity)
  {
    COPY_DYNAMIC_TYPE

    return *this;
  }

  bool DynamicEntity::operator==(const DynamicEntity& rhs) const
  {
    if(m_type != rhs.m_type)
    {
      return false;
    }

    switch(m_type)
    {
    case Type_Float_:
      return fabs(m_data.m_float - rhs.m_data.m_float) < EPSILON;
      break;
    }

    return memcmp(&m_data, &rhs.m_data, sizeof(m_data)) == 0;
  }

  bool DynamicEntity::operator!=(const DynamicEntity& rhs) const
  {
    return !operator==(rhs);
  }

  ////////////////////////////////////////////////////////////////////////// Setters

  void DynamicEntity::Set(int32 val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_Int_;
    m_data.m_int = val;
  }

  void DynamicEntity::Set(int64 val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_Int64_;
    m_data.m_int64 = val;
  }

  void DynamicEntity::Set(uint32 val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_Uint_;
    m_data.m_uint = val;
  }

  void DynamicEntity::Set(uint64 val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_Uint64_;
    m_data.m_uint64 = val;
  }

  void DynamicEntity::Set(f32 val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_Float_;
    m_data.m_float = val;
  }

  void DynamicEntity::Set(bool8 val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_Bool_;
    m_data.m_bool = val;
  }

  void DynamicEntity::Set(std::string &val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_String_;
    m_data.m_stringPtr = new std::string(val);
  }

  void DynamicEntity::Set(VectorType &val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_Vector_;
    m_data.m_vectorPtr = new VectorType(val);
  }

  void DynamicEntity::Set(MatrixType &val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_Matrix_;
    m_data.m_matrixPtr = new MatrixType(val);
  }

  void DynamicEntity::Set(DataEntity &val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_Data_;
    m_data.m_dataPtr = new DataEntity(val);
  }

  void DynamicEntity::Set(std::vector<DynamicEntity> &val)
  {
    CLEAR_DYNAMIC_TYPE

    m_type = Type_Array_;
    m_data.m_arrayPtr = new std::vector<DynamicEntity>(val);
  }

  ////////////////////////////////////////////////////////////////////////// Getters

  void DynamicEntity::Get(int32 &val) const
  {
    if (m_type == Type_Int_)
    {
      val = m_data.m_int;
    }
    else if (m_type == Type_Float_)
    {
      val = static_cast<int32>(m_data.m_float);
    }
  }

  void DynamicEntity::Get(int64 &val) const
  {
    if (m_type == Type_Int64_)
    {
      val = m_data.m_int64;
    }
    else if (m_type == Type_Float_)
    {
      val = static_cast<int64>(m_data.m_float);
    }
  }

  void DynamicEntity::Get(uint32 &val) const
  {
    if (m_type == Type_Uint_)
    {
      val = m_data.m_uint;
    }
    else if (m_type == Type_Float_)
    {
      val = static_cast<uint32>(m_data.m_float);
    }
  }

  void DynamicEntity::Get(uint64 &val) const
  {
    if (m_type == Type_Uint64_)
    {
      val = m_data.m_uint64;
    }
    else if (m_type == Type_Float_)
    {
      val = static_cast<uint64>(m_data.m_float);
    }
  }

  void DynamicEntity::Get(f32 &val) const
  {
    if (m_type == Type_Float_)
    {
      val = m_data.m_float;
    }
    else if (m_type == Type_Float_)
    {
      val = static_cast<f32>(m_data.m_float);
    }
  }

  void DynamicEntity::Get(bool8 &val) const
  {
    if (m_type == Type_Bool_)
    {
      val = m_data.m_bool;
    }
    else if (m_type == Type_Float_)
    {
      val = m_data.m_float != 0.0f;
    }
  }

  void DynamicEntity::Get(std::string &val) const
  {
    if (m_type == Type_String_)
    {
      val = std::string(m_data.m_stringPtr->c_str());
    }
  }

  void DynamicEntity::Get(VectorType &val) const
  {
    if (m_type == Type_Vector_)
    {
      val = *m_data.m_vectorPtr;
    }
  }

  void DynamicEntity::Get(MatrixType &val) const
  {
    if (m_type == Type_Matrix_)
    {
      val = *m_data.m_matrixPtr;
    }
  }

  void DynamicEntity::Get(DataEntity &val) const
  {
    if (m_type == Type_Data_)
    {
      val = *m_data.m_dataPtr;
    }
  }

  void DynamicEntity::Get(std::vector<DynamicEntity> &val) const
  {
    if (m_type == Type_Array_)
    {
      val = std::vector<DynamicEntity>(*m_data.m_arrayPtr);
    }
  }

  ////////////////////////////////////////////////////////////////////////// Type

  // Get the current type of the dynamic entity
  Dynamic_Type_ DynamicEntity::Type() const
  {
    return m_type;
  }
}
