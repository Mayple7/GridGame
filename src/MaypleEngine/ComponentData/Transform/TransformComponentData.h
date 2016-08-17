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
    int GetComponentNumber();
    // Members (these must be public so the can be accessed outside the class during construction)
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR3(Position, position);
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR3(Scale, scale);
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR3(Rotation, rotation);

    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR3_FUNCTIONS(OffsetPosition);
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR3_FUNCTIONS(OffsetScale);
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR3_FUNCTIONS(OffsetRotation);

    void TransformTranslationOffset(hndl componentHandle, VectorType newPos, uint32 depth = 0);

    void TransformScaleOffset(hndl componentHandle, VectorType newScale, VectorType anchor);
    void TransformScaleOffsetHelper(hndl componentHandle, VectorType scaleDt, VectorType anchor);

    void TransformRotateOffset(hndl componentHandle, VectorType newRotEuler, VectorType anchor);
    void TransformRotateOffsetHelper(hndl componentHandle, VectorType rotDt, VectorType anchor);

    VectorType GetXBasis(hndl componentHandle) const;
    VectorType GetYBasis(hndl componentHandle) const;
    VectorType GetZBasis(hndl componentHandle) const;

    MatrixType _CalculateTransform(hndl transform);

    AUTO_DECLARE_PROPERTY_ONLY(MatrixType, rotationMatrix);
    AUTO_DECLARE_PROPERTY_ONLY(MatrixType, transformMatrix);
    // Don't try to get this property unless it's through GetRotation,
    // it will probably be garbage
    AUTO_DECLARE_PROPERTY_ONLY(VectorType, eulerAngles);

END_DECLARE_COMPONENT(Transform)
