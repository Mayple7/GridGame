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

// Binding
#include "BaseBind.h"
#include "ScriptManager.h"
#include "CFrameBinding.h"

// Object to component binding relationships
#include "ObjectBinding.h"

// Job creation
#include "JobDeclaration.h"
#include "VectorBinding.h"
#include "CFrameBinding.h"

#include "DieselMathPlane.h"
#include "PAABB.h"


/*=================================
*      Forward Declarations
*/
namespace prism
{
  struct PHUDObject;
  struct PRenderObject;
  struct PAnimatedRenderObject;
}


START_DECLARE_COMPONENT(coreSpace, Transform, transform)

    void Print(hndl componentHandle);
    int GetComponentNumber();
    float Orbit(hndl componentHandle, float time, float length, const scriptSpace::vectorBinding::LuaVector &center);
    // Members (these must be public so the can be accessed outside the class during construction)
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR(Position, position);
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR(Scale, scale);
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR(Rotation, rotation);

    AUTO_DECLARE_GET_SET_PROPERTY_MATRIX(CFrame, cframe);

    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR_FUNCTIONS(OffsetPosition);
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR_FUNCTIONS(OffsetScale);
    AUTO_DECLARE_GET_SET_PROPERTY_VECTOR_FUNCTIONS(OffsetRotation);

    void TransformTranslationOffset(hndl componentHandle, VectorType newPos, uint32 depth = 0);

    void TransformScaleOffset(hndl componentHandle, VectorType newScale, VectorType anchor);
    void TransformScaleOffsetHelper(hndl componentHandle, VectorType scaleDt, VectorType anchor);

    void TransformRotateOffset(hndl componentHandle, VectorType newRotEuler, VectorType anchor);
    void TransformRotateOffsetHelper(hndl componentHandle, VectorType rotDt, VectorType anchor);

    VectorType GetExtentScalar(hndl componentHandle);

    VectorType GetXBasis(hndl componentHandle) const;
    VectorType GetYBasis(hndl componentHandle) const;
    VectorType GetZBasis(hndl componentHandle) const;
    prism::PAABB GetAABB(hndl componentHandle);
    prism::PAABB GetAABBRaw(hndl componentHandle);
    prism::PAABB GetAABB(hndl componentHandle, float radius);

    void RotateToVector(hndl componentHandle, scriptSpace::vectorBinding::LuaVector const &vector);
    void VECTOR_CALL RotateToVectorDetail(hndl componentHandle, VectorType vector);
    void Rotate(hndl componentHandle, scriptSpace::cframeBinding::LuaCFrame const &quat);
    void VECTOR_CALL _Rotate(hndl componentHandle, VectorType quat);

    unsigned Extract(prism::PRenderObject *objects, 
                     const hndl *objectHandles, 
                     size_t *objectTypes, 
                     unsigned size);


    unsigned Extract(prism::PAnimatedRenderObject *objects, 
                     const hndl *objectHandles, 
                     size_t *objectTypes, 
                     unsigned size);

    void _ExtractObject(prism::PRenderObject  *object,
                        size_t *objectType,
                        size_t componentHandle);


    MatrixType _CalculateTransform(hndl transform);

    // 0 = x
    // 1 = y
    // 2 = z
    // 3 = -x
    // 4 = -y
    // 5 = -z
    void AlignBasis(hndl transform, int32 basis, scriptSpace::vectorBinding::LuaVector const &vector);
    void VECTOR_CALL _AlignBasis(hndl transformm, int32 basis, VectorType vector, VectorType initialOrientation);

    AUTO_DECLARE_PROPERTY_ONLY(MatrixType, rotationMatrix);
    AUTO_DECLARE_PROPERTY_ONLY(MatrixType, transformMatrix);
    // Don't try to get this property unless it's through GetRotation,
    // it will probably be garbage
    AUTO_DECLARE_PROPERTY_ONLY(VectorType, eulerAngles);

END_DECLARE_COMPONENT(Transform)
