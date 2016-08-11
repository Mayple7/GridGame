/*!****************************************************************************
\file    Plane.h
\author  Dan Muller

\brief   Plane math

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"

#include "Math.hpp"

namespace MaypleMath
{
  Plane::Plane(void)
  {
    m_normal = Vector4(0, 0, 0, 0);
    m_d = 1;
  }

  Plane::Plane(Vector4 point0, Vector4 point1, Vector4 point2)
  {
    Set(point0, point1, point2);
  }

  Plane::Plane(Vector4 normal, Vector4 point)
  {
    m_normal = normal.Normalized();
    m_d = Dot(m_normal, point);
  }

  void Plane::Set(Vector4 point0, Vector4 point1, Vector4 point2)
  {
    m_normal = Cross(point1 - point0, point2 - point0);
    if(m_normal.LengthSq() == 0)
      m_normal.x += EPSILON;
    m_normal.Normalize();
    m_d = Dot(m_normal, point0);
  }

  float Plane::Distance(Vector4 point) const
  {
    return Dot(m_normal, point) - m_d;
  }

  Vector4 Plane::Intersection(Vector4 start, Vector4 end) const
  {
    Vector4 lineDirection = (end - start).Normalized();
    float denominator = Dot(lineDirection, m_normal);
    if(denominator > -EPSILON && denominator < EPSILON)
      denominator = EPSILON;

    float distance = Dot(start, m_normal) - m_d;
    float t = distance / denominator;

    return start - (lineDirection * t);
  }

  ProjectResult Plane::Project(Vector4 point) const
  {
    ProjectResult returnValue;
    returnValue.m_distance = Dot(point, m_normal) - m_d;

    returnValue.m_point = point - (m_normal * returnValue.m_distance);

    return returnValue;
  }
}
