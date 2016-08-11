/*!****************************************************************************
\file    Plane.h
\author  Dan Muller

\brief   Plane math

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include "Vector3.hpp"

namespace MaypleMath
{
  struct ProjectResult
  {
    float m_distance;
    Vector4 m_point;
  };

  class Plane
  {
  public:
    Plane(void);
    Plane(Vector4 point0, Vector4 point1, Vector4 point2);
    Plane(Vector4 normal, Vector4 point);

    void Set(Vector4 point0, Vector4 point1, Vector4 point2);
    float Distance(Vector4 point) const;

    Vector4 Intersection(Vector4 start, Vector4 end) const;
    ProjectResult Project(Vector4 point) const;

    Vector4 m_normal;
    float m_d;
  };
}
