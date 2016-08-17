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
  enum Vector_Type_
  {
    Type_Vector2_,
    Type_Vector3_,
    Type_Vector4_,
    Type_NullVector_
  };

  class VectorType
  {
  public:
    VectorType();
    VectorType(const VectorType& vectorType);
    ~VectorType();

    VectorType& operator=(const VectorType& dynamicEntity);
    bool operator==(const VectorType& rhs) const;
    bool operator!=(const VectorType& rhs) const;

    void Set(Vector2 val);
    void Set(Vector3 val);
    void Set(Vector4 val);
    
    void Get(Vector2 &val) const;
    void Get(Vector3 &val) const;
    void Get(Vector4 &val) const;
    
    // Get the current type of the dynamic entity
    Vector_Type_ Type() const;

  private:
    union
    {
      Vector2 *m_vector2Ptr;
      Vector3 *m_vector3Ptr;
      Vector4 *m_vector4Ptr;
    } m_data;

    Vector_Type_ m_type;

  };
}
