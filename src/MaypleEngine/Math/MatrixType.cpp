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
#include "MatrixType.hpp"

// If anything needs to be cleared form the dynamic entity, this does it
#define CLEAR_MATRIX_TYPE \
if (m_type == Type_Matrix2_) \
  delete m_data.m_matrix2Ptr; \
else if (m_type == Type_Matrix3_) \
  delete m_data.m_matrix3Ptr; \
else if (m_type == Type_Matrix4_) \
  delete m_data.m_matrix4Ptr;

#define COPY_MATRIX_TYPE \
m_type = matrixType.m_type; \
if (matrixType.m_type == Type_Matrix2_) \
{ \
  m_data.m_matrix2Ptr = new Matrix2(*matrixType.m_data.m_matrix2Ptr); \
} \
else if (matrixType.m_type == Type_Matrix3_) \
{ \
  m_data.m_matrix3Ptr = new Matrix3(*matrixType.m_data.m_matrix3Ptr); \
} \
else if (matrixType.m_type == Type_Matrix4_) \
{ \
  m_data.m_matrix4Ptr = new Matrix4(*matrixType.m_data.m_matrix4Ptr); \
} \
else \
  m_data = matrixType.m_data;

namespace MaypleMath
{
  MatrixType::MatrixType()
  {
    m_type = Type_NullMatrix_;
  }

  MatrixType::MatrixType(const MatrixType& matrixType)
  {
    COPY_MATRIX_TYPE
  }

  MatrixType::~MatrixType()
  {
    CLEAR_MATRIX_TYPE
  }

  MatrixType& MatrixType::operator=(const MatrixType& matrixType)
  {
    CLEAR_MATRIX_TYPE

      return *this;
  }

  bool MatrixType::operator==(const MatrixType& rhs) const
  {
    if(m_type != rhs.m_type)
    {
      return false;
    }

    return memcmp(&m_data, &rhs.m_data, sizeof(m_data)) == 0;
  }

  bool MatrixType::operator!=(const MatrixType& rhs) const
  {
    return !operator==(rhs);
  }

  ////////////////////////////////////////////////////////////////////////// Setters

  void MatrixType::Set(Matrix2 val)
  {
    CLEAR_MATRIX_TYPE

    m_type = Type_Matrix2_;
    *m_data.m_matrix2Ptr = val;
  }

  void MatrixType::Set(Matrix3 val)
  {
    CLEAR_MATRIX_TYPE

    m_type = Type_Matrix3_;
    *m_data.m_matrix3Ptr = val;
  }

  void MatrixType::Set(Matrix4 val)
  {
    CLEAR_MATRIX_TYPE

    m_type = Type_Matrix4_;
    *m_data.m_matrix4Ptr = val;
  }

  ////////////////////////////////////////////////////////////////////////// Getters

  void MatrixType::Get(Matrix2 &val) const
  {
    if(m_type == Type_Matrix2_)
    {
      val = *m_data.m_matrix2Ptr;
    }
  }

  void MatrixType::Get(Matrix3 &val) const
  {
    if(m_type == Type_Matrix3_)
    {
      val = *m_data.m_matrix3Ptr;
    }
  }

  void MatrixType::Get(Matrix4 &val) const
  {
    if(m_type == Type_Matrix4_)
    {
      val = *m_data.m_matrix4Ptr;
    }
  }

  ////////////////////////////////////////////////////////////////////////// Type

  // Get the current type of the dynamic entity
  Matrix_Type_ MatrixType::Type() const
  {
    return m_type;
  }
}
