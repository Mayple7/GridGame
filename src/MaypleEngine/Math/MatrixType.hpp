/*!****************************************************************************
\file    VectorType.h
\author  Kaden Nugent (kaden.n)
\date    July 19, 2015

\brief   A dynamic entity for arbitrary component data retrieval.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include "Math.hpp"

namespace MaypleMath
{
  enum Matrix_Type_
  {
    Type_Matrix2_,
    Type_Matrix3_,
    Type_Matrix4_,
    Type_NullMatrix_
  };

  class MatrixType
  {
  public:
    MatrixType();
    MatrixType(const MatrixType& matrixType);
    ~MatrixType();

    MatrixType& operator=(const MatrixType& dynamicEntity);
    bool operator==(const MatrixType& rhs) const;
    bool operator!=(const MatrixType& rhs) const;

    void Set(Matrix2 val);
    void Set(Matrix3 val);
    void Set(Matrix4 val);
    
    void Get(Matrix2 &val) const;
    void Get(Matrix3 &val) const;
    void Get(Matrix4 &val) const;
    
    // Get the current type of the dynamic entity
    Matrix_Type_ Type() const;

  private:
    union
    {
      Matrix2 *m_matrix2Ptr;
      Matrix3 *m_matrix3Ptr;
      Matrix4 *m_matrix4Ptr;
    } m_data;

    Matrix_Type_ m_type;

  };
}
