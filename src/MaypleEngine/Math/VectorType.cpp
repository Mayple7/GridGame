/*!****************************************************************************
\file    VectorType.cpp
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
#include "VectorType.hpp"

// If anything needs to be cleared form the dynamic entity, this does it
#define CLEAR_VECTOR_TYPE \
if (m_type == Type_Vector2_) \
  delete m_data.m_vector2Ptr; \
else if (m_type == Type_Vector3_) \
  delete m_data.m_vector3Ptr; \
else if (m_type == Type_Vector4_) \
  delete m_data.m_vector4Ptr;

#define COPY_VECTOR_TYPE \
m_type = vectorType.m_type; \
if (vectorType.m_type == Type_Vector2_) \
{ \
  m_data.m_vector2Ptr = new Vector2(*vectorType.m_data.m_vector2Ptr); \
} \
else if (vectorType.m_type == Type_Vector3_) \
{ \
  m_data.m_vector3Ptr = new Vector3(*vectorType.m_data.m_vector3Ptr); \
} \
else if (vectorType.m_type == Type_Vector4_) \
{ \
  m_data.m_vector4Ptr = new Vector4(*vectorType.m_data.m_vector4Ptr); \
} \
else \
  m_data = vectorType.m_data;

namespace MaypleMath
{
  VectorType::VectorType()
  {
    m_type = Type_NullVector_;
  }

  VectorType::VectorType(const VectorType& vectorType)
  {
    COPY_VECTOR_TYPE
  }

  VectorType::~VectorType()
  {
    CLEAR_VECTOR_TYPE
  }

  VectorType& VectorType::operator=(const VectorType& vectorType)
  {
    COPY_VECTOR_TYPE

    return *this;
  }

  bool VectorType::operator==(const VectorType& rhs) const
  {
    if(m_type != rhs.m_type)
    {
      return false;
    }

    return memcmp(&m_data, &rhs.m_data, sizeof(m_data)) == 0;
  }

  bool VectorType::operator!=(const VectorType& rhs) const
  {
    return !operator==(rhs);
  }

  ////////////////////////////////////////////////////////////////////////// Setters

  void VectorType::Set(Vector2 val)
  {
    CLEAR_VECTOR_TYPE

    m_type = Type_Vector2_;
    *m_data.m_vector2Ptr = val;
  }

  void VectorType::Set(Vector3 val)
  {
    CLEAR_VECTOR_TYPE

    m_type = Type_Vector3_;
    *m_data.m_vector3Ptr = val;
  }

  void VectorType::Set(Vector4 val)
  {
    CLEAR_VECTOR_TYPE

    m_type = Type_Vector4_;
    *m_data.m_vector4Ptr = val;
  }

  ////////////////////////////////////////////////////////////////////////// Getters

  void VectorType::Get(Vector2 &val) const
  {
    if(m_type == Type_Vector2_)
    {
      val = *m_data.m_vector2Ptr;
    }
    else if(m_type == Type_Vector3_)
    {
      val.x = m_data.m_vector3Ptr->x;
      val.y = m_data.m_vector3Ptr->y;
    }
    else if(m_type == Type_Vector4_)
    {
      val.x = m_data.m_vector4Ptr->x;
      val.y = m_data.m_vector4Ptr->y;
    }
  }

  void VectorType::Get(Vector3 &val) const
  {
    if(m_type == Type_Vector2_)
    {
      val.x = m_data.m_vector2Ptr->x;
      val.y = m_data.m_vector2Ptr->y;
      val.z = 0;
    }
    else if(m_type == Type_Vector3_)
    {
      val = *m_data.m_vector3Ptr;
    }
    else if(m_type == Type_Vector4_)
    {
      val.x = m_data.m_vector4Ptr->x;
      val.y = m_data.m_vector4Ptr->y;
      val.z = m_data.m_vector4Ptr->z;
    }
  }

  void VectorType::Get(Vector4 &val) const
  {
    if(m_type == Type_Vector2_)
    {
      val.x = m_data.m_vector2Ptr->x;
      val.y = m_data.m_vector2Ptr->y;
      val.z = 0;
      val.w = 0;
    }
    else if(m_type == Type_Vector3_)
    {
      val.x = m_data.m_vector3Ptr->x;
      val.y = m_data.m_vector3Ptr->y;
      val.z = m_data.m_vector3Ptr->z;
      val.w = 0;
    }
    else if(m_type == Type_Vector4_)
    {
      val = *m_data.m_vector4Ptr;
    }
  }

  ////////////////////////////////////////////////////////////////////////// Type

  // Get the current type of the dynamic entity
  Vector_Type_ VectorType::Type() const
  {
    return m_type;
  }
}
