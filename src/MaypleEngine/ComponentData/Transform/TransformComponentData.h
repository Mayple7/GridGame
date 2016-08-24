/*!****************************************************************************
\file    TransformComponentData.h
\author  Kaden Nugent (kaden.n)
\date    May 20, 2015

\brief	 Data for transform components.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

////////////////////////////////////////////////////////////////////////// DEPENDENCIES

// Custom containers
#include "SlotMap.h"

// Makes component creation easier
#include "ComponentDataHelpers.h"

/*=================================
*      Forward Declarations
*/
START_DECLARE_COMPONENT(coreSpace, Transform, transform)

    void Print(hndl componentHandle);

    // Members (these must be public so the can be accessed outside the class during construction)
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR2(Position, position);
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR2(Scale, scale);
    AUTO_DECLARE_GET_SET_PROPERTY(f32, Rotation, rotation);

    Matrix3 _CalculateTransform(hndl componentHandle);

END_DECLARE_COMPONENT(Transform)
