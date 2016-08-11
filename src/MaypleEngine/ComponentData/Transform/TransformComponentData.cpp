/*!****************************************************************************
\file    TransformComponentData.cpp
\author  Kaden Nugent (kaden.n)
\date    May 20, 2015

\brief	 Data for transform components.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

////////////////////////////////////////////////////////////////////////// DEPENDENCIES

// Standard include
#include "stdinc.h"

// This component's header files
#include "UpdateTransforms.h"
#include "TransformComponentData.h"

// Managers
#include "ManagerLocator.h"
#include "ObjectManager.h"
#include "Prism.h"
#include "WindowManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "ObjectEntity.h"

// Math libraries
#include "VectorMath.h"
#include "MatrixMath.h"
#include "QuaternionMath.h"
#include "MathConstants.h"
#include "DieselMathGeometryUtilities.h"
#include "DieselMathUtilities.h"

// General component data
#include "ComponentDataLocator.h"
#include "ComponentData.h"
#include "ModelComponentData.h"
#include "AnimatedModelComponentData.h"
#include "ShadowModelComponentData.h"
#include "TranslucentModelComponentData.h"
#include "CameraComponentData.h"

// Job related
#include "JobManager.h"
#include "ExecutionManager.h"

#include "PRenderObject.h"
#include "PHUDObject.h"
#include "PConstants.h"

/*=================================
*            Locals
*/
namespace 
{
	/*=================================
	*       Local Variables
	*/
  uint32 c_translationOffsetMaxDepth = 100;
	
	/*=================================
	*       Local Functions
	*/
	
}

////////////////////////////////////////////////////////////////////////// MACROS

////////////////////////////////////////////////////////////////////////// DECLARATIONS

START_DECLARE_COMPONENT_DEFINITION(coreSpace, Transform, transform)

  START_DECLARE_COMPONENT_CONSTRUCTION(coreSpace, Transform, transform)
    INITIALIZE_SLOT(position, transform, math::CreateVectorType(0.0f, 0.0f, 0.0f, 1.0f));
    INITIALIZE_SLOT(scale, transform, math::CreateVectorType(1.0f, 1.0f, 1.0f, 1.0f));
    INITIALIZE_SLOT(rotation, transform);
    INITIALIZE_SLOT(rotationMatrix, transform);
    INITIALIZE_SLOT(transformMatrix, transform);
    INITIALIZE_SLOT(eulerAngles, transform);
  END_DECLARE_COMPONENT_CONSTRUCTION

  START_DECLARE_COMPONENT_DESTRUCTION(coreSpace, Transform, transform)
    UNINITIALIZE_SLOT(position, transform);
    UNINITIALIZE_SLOT(scale, transform);
    UNINITIALIZE_SLOT(rotation, transform);
    UNINITIALIZE_SLOT(rotationMatrix, transform);
    UNINITIALIZE_SLOT(transformMatrix, transform);
    UNINITIALIZE_SLOT(eulerAngles, transform);
  END_DECLARE_COMPONENT_DESTRUCTION

  // Constructor
  TransformComponentData::TransformComponentData(void)
  {
  }

  hndl TransformComponentData::AttachComponent(hndl objectHandle, luabridge::LuaRef **args)
  {
    hndl newComponent = Create(objectHandle);

    // Check for starting values

    // Position
    if (args && args[0])
    {
      SetPosition(newComponent, math::ToPoint4(args[0]->cast<scriptSpace::vectorBinding::LuaVector>()));
    }

    // Scale
    if (args && args[1])
    {
      SetScale(newComponent, math::CreateVectorType(args[1]->cast<scriptSpace::vectorBinding::LuaVector>().m_vec));
    }
    else
    {
      SetScale(newComponent, math::CreateVectorType(1, 1, 1));
    }

    // Rotation
    if (args && args[2])
    {
      SetRotation(newComponent, math::ToVectorType(args[2]->cast<scriptSpace::vectorBinding::LuaVector>()));
    }
    else
    {
      SetRotation(newComponent, math::CreateVectorType(0, 0, 0, 1));
    }

    return newComponent;
  }

  void TransformComponentData::DetachComponent(hndl objectHandle)
  {
    Destroy(objectHandle);
  }

  AUTO_LUAREG_COMPONENT_MEMBER_FUNCTION(Transform, Print);
  AUTO_LUAREG_COMPONENT_MEMBER_FUNCTION(Transform, Orbit);
  AUTO_LUAREG_COMPONENT_REGULAR_FUNCTION(Transform, GetComponentNumber);

  int TransformComponentData::GetComponentNumber()
  {
    return m_positionContainer.GetSize();
  }

  void TransformComponentData::Print(hndl componentHandle)
  {
    VectorFloat4 temp;
    
    math::StoreVectorType(GetPosition(componentHandle), &temp.x);

    std::cout << temp.x << ", " << temp.y << ", " << temp.z << std::endl;
  }

  float TransformComponentData::Orbit(hndl componentHandle, float time, float length, const scriptSpace::vectorBinding::LuaVector &center)
  {
    VectorFloat4 orbitPos;

    orbitPos.x = std::cos(time) * length + center.Get<0>();
    orbitPos.y = center.Get<1>();
    orbitPos.z = std::sin(time) * length + center.Get<2>();
    orbitPos.w = 0.0f;

    SetPosition(componentHandle, orbitPos);

    return std::fmodf(length + 0.004f, 2.0f);
  }

  AUTO_GET_SET_PROPERTY_POINT(Transform, Position, position);
  AUTO_GET_SET_PROPERTY_POINT(Transform, Scale, scale);

  // Custom rotation lua definitions
  AUTO_LUAREG_COMPONENT_PROPERTY_VECTOR(Transform, Rotation);
  void TransformComponentData::SetRotationLua(hndl componentHandle, const scriptSpace::vectorBinding::LuaVector &newValue)
  {
    SetRotation(componentHandle, math::CreateVectorType(newValue.m_vec[0], newValue.m_vec[1], newValue.m_vec[2]));
  }
  VectorType &TransformComponentData::GetRotation(hndl componentHandle)
  {
    m_eulerAnglesContainer[componentHandle] = math::GetEulerQuaternion(m_rotationContainer[componentHandle]);
    return m_eulerAnglesContainer[componentHandle];
  }
  void VECTOR_CALL TransformComponentData::SetRotation(hndl componentHandle, VectorType newValue)
  {
    m_rotationContainer[componentHandle] = math::CreateQuaternion(newValue);
  }
  coreSpace::DynamicEntity TransformComponentData::ArbitraryGetRotation(hndl componentHandle)
  {
    coreSpace::DynamicEntity val;
    val.Set(GET_COMPONENT_DATA(TransformComponentData)->GetRotation(componentHandle));
    return val;
  }
  void TransformComponentData::ArbitrarySetRotation(hndl componentHandle, coreSpace::DynamicEntity newValue)
  {
    VectorType val;
    newValue.Get(val);
    GET_COMPONENT_DATA(TransformComponentData)->SetRotation(componentHandle, val);
  }
  const int32 CONCATENATE(c_propertyGet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertyGetter("Transform", "Rotation", TransformComponentData::ArbitraryGetRotation);
  const int32 CONCATENATE(c_propertySet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertySetter("Transform", "Rotation", TransformComponentData::ArbitrarySetRotation);

  //////////////////////////////////////////////////////////////////////////
  // position offset

  AUTO_LUAREG_COMPONENT_PROPERTY_VECTOR(Transform, OffsetPosition);
  void TransformComponentData::SetOffsetPositionLua(hndl componentHandle, const scriptSpace::vectorBinding::LuaVector &newValue)
  {
    SetOffsetPosition(componentHandle, math::CreateVectorType(newValue.m_vec[0], newValue.m_vec[1], newValue.m_vec[2]));
  }
  VectorType &TransformComponentData::GetOffsetPosition(hndl componentHandle)
  {
    static VectorType forRef;

    hndl parentObjHndl = GET_OBJECT_MANAGER->GetObject(GetObject(componentHandle)).GetParent();
    if(parentObjHndl == INVALID_HANDLE || GetComponent(parentObjHndl) == INVALID_HANDLE)
    {
      forRef = GetPosition(componentHandle);
      return forRef;
    }

    forRef = math::SubVectorType(GetPosition(componentHandle), GetPosition(GetComponent(parentObjHndl)));
    return forRef;
  }
  void VECTOR_CALL TransformComponentData::SetOffsetPosition(hndl componentHandle, VectorType newValue)
  {
    hndl parentObjHndl = GET_OBJECT_MANAGER->GetObject(GetObject(componentHandle)).GetParent();
    if(parentObjHndl == INVALID_HANDLE || GetComponent(parentObjHndl) == INVALID_HANDLE)
    {
      SetPosition(componentHandle, newValue);
      return;
    }

    SetPosition(componentHandle, math::AddVectorType(GetPosition(GetComponent(parentObjHndl)), newValue));
  }
  coreSpace::DynamicEntity TransformComponentData::ArbitraryGetOffsetPosition(hndl componentHandle)
  {
    coreSpace::DynamicEntity val;
    val.Set(GET_COMPONENT_DATA(TransformComponentData)->GetOffsetPosition(componentHandle));
    return val;
  }
  void TransformComponentData::ArbitrarySetOffsetPosition(hndl componentHandle, coreSpace::DynamicEntity newValue)
  {
    VectorType val;
    newValue.Get(val);
    GET_COMPONENT_DATA(TransformComponentData)->SetOffsetPosition(componentHandle, val);
  }
  // const int32 CONCATENATE(c_propertyGet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertyGetter("Transform", "OffsetPosition", TransformComponentData::ArbitraryGetOffsetPosition);
  // const int32 CONCATENATE(c_propertySet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertySetter("Transform", "OffsetPosition", TransformComponentData::ArbitrarySetOffsetPosition);

  //////////////////////////////////////////////////////////////////////////
  // scale offset

  AUTO_LUAREG_COMPONENT_PROPERTY_VECTOR(Transform, OffsetScale);
  void TransformComponentData::SetOffsetScaleLua(hndl componentHandle, const scriptSpace::vectorBinding::LuaVector &newValue)
  {
    SetOffsetScale(componentHandle, math::CreateVectorType(newValue.m_vec[0], newValue.m_vec[1], newValue.m_vec[2]));
  }
  VectorType &TransformComponentData::GetOffsetScale(hndl componentHandle)
  {
    static VectorType forRef;

    hndl parentObjHndl = GET_OBJECT_MANAGER->GetObject(GetObject(componentHandle)).GetParent();
    if(parentObjHndl == INVALID_HANDLE || GetComponent(parentObjHndl) == INVALID_HANDLE)
    {
      forRef = GetScale(componentHandle);
      return forRef;
    }

    VectorFloat4 parentScale = GetScale(GetComponent(parentObjHndl));
    VectorType scaleVec = math::CreateVectorType(1.0f / parentScale.x, 1.0f / parentScale.y, 1.0f / parentScale.z);
    forRef = math::ScaleVectorType(GetScale(componentHandle), scaleVec);
    return forRef;
  }
  void VECTOR_CALL TransformComponentData::SetOffsetScale(hndl componentHandle, VectorType newValue)
  {
    hndl parentObjHndl = GET_OBJECT_MANAGER->GetObject(GetObject(componentHandle)).GetParent();
    if(parentObjHndl == INVALID_HANDLE || GetComponent(parentObjHndl) == INVALID_HANDLE)
    {
      SetScale(componentHandle, newValue);
      return;
    }

    SetScale(componentHandle, math::ScaleVectorType(GetScale(GetComponent(parentObjHndl)), newValue));
  }
  coreSpace::DynamicEntity TransformComponentData::ArbitraryGetOffsetScale(hndl componentHandle)
  {
    coreSpace::DynamicEntity val;
    val.Set(GET_COMPONENT_DATA(TransformComponentData)->GetOffsetScale(componentHandle));
    return val;
  }
  void TransformComponentData::ArbitrarySetOffsetScale(hndl componentHandle, coreSpace::DynamicEntity newValue)
  {
    VectorType val;
    newValue.Get(val);
    GET_COMPONENT_DATA(TransformComponentData)->SetOffsetScale(componentHandle, val);
  }
  // const int32 CONCATENATE(c_propertyGet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertyGetter("Transform", "OffsetScale", TransformComponentData::ArbitraryGetOffsetScale);
  // const int32 CONCATENATE(c_propertySet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertySetter("Transform", "OffsetScale", TransformComponentData::ArbitrarySetOffsetScale);

  //////////////////////////////////////////////////////////////////////////
  // rotation offset

  AUTO_LUAREG_COMPONENT_PROPERTY_VECTOR(Transform, OffsetRotation);
  void TransformComponentData::SetOffsetRotationLua(hndl componentHandle, const scriptSpace::vectorBinding::LuaVector &newValue)
  {
    SetOffsetRotation(componentHandle, math::CreateVectorType(newValue.m_vec[0], newValue.m_vec[1], newValue.m_vec[2]));
  }
  VectorType &TransformComponentData::GetOffsetRotation(hndl componentHandle)
  {
    static VectorType forRef;

    hndl parentObjHndl = GET_OBJECT_MANAGER->GetObject(GetObject(componentHandle)).GetParent();
    if(parentObjHndl == INVALID_HANDLE || GetComponent(parentObjHndl) == INVALID_HANDLE)
    {
      forRef = GetRotation(componentHandle);
      return forRef;
    }

    forRef = math::ScaleVectorType(GetRotation(componentHandle), GetRotation(GetComponent(parentObjHndl)));
    return forRef;
  }
  void VECTOR_CALL TransformComponentData::SetOffsetRotation(hndl componentHandle, VectorType newValue)
  {
    hndl parentObjHndl = GET_OBJECT_MANAGER->GetObject(GetObject(componentHandle)).GetParent();
    if(parentObjHndl == INVALID_HANDLE || GetComponent(parentObjHndl) == INVALID_HANDLE)
    {
      SetRotation(componentHandle, newValue);
      return;
    }

    // SetRotation(componentHandle, math::ScaleVectorType(GetRotation(GetComponent(parentObjHndl)), newValue));
  }
  coreSpace::DynamicEntity TransformComponentData::ArbitraryGetOffsetRotation(hndl componentHandle)
  {
    coreSpace::DynamicEntity val;
    val.Set(GET_COMPONENT_DATA(TransformComponentData)->GetOffsetRotation(componentHandle));
    return val;
  }
  void TransformComponentData::ArbitrarySetOffsetRotation(hndl componentHandle, coreSpace::DynamicEntity newValue)
  {
    VectorType val;
    newValue.Get(val);
    GET_COMPONENT_DATA(TransformComponentData)->SetOffsetRotation(componentHandle, val);
  }
  // const int32 CONCATENATE(c_propertyGet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertyGetter("Transform", "OffsetRotation", TransformComponentData::ArbitraryGetOffsetRotation);
  // const int32 CONCATENATE(c_propertySet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertySetter("Transform", "OffsetRotation", TransformComponentData::ArbitrarySetOffsetRotation);

  //////////////////////////////////////////////////////////////////////////
  // offset helper functions

  void coreSpace::TransformComponentData::TransformTranslationOffset(hndl componentHandle, VectorType newPos, uint32 depth /*= 0*/)
  {
    if (depth >= c_translationOffsetMaxDepth)
    {
      TRACE_ERROR(NULL,
                  "This component seems to have infinite children: %d", componentHandle);
      return;
    }
    VectorType dt = math::SubVectorType(newPos, GetPosition(componentHandle));
    SetPosition(componentHandle, newPos);

    auto& children = GET_OBJECT_MANAGER->GetObject(GetObject(componentHandle)).GetChildren();

    if(children.empty() == true)
    {
      return;
    }

    for(hndl childHndl : children)
    {
      hndl transformHndl = GetComponent(childHndl);

      TRACE_ERROR(transformHndl != componentHandle,
                  "How can you have yourself as a parent something is seriously wrong.");
      TransformTranslationOffset(transformHndl, math::AddVectorType(GetPosition(transformHndl), dt), depth + 1);
    }
  }

  void coreSpace::TransformComponentData::TransformScaleOffset(hndl componentHandle, VectorType newScale, VectorType anchor)
  {
    VectorType scaleVec = math::CreateVectorType(1.0f / GetScale(componentHandle).m128_f32[0], 1.0f / GetScale(componentHandle).m128_f32[1], 1.0f / GetScale(componentHandle).m128_f32[2]);
    VectorType scaleDt = math::ScaleVectorType(newScale, scaleVec);
    VectorType relativeToAnchorVector = math::SubVectorType(GetPosition(componentHandle), anchor);
    relativeToAnchorVector = math::ScaleVectorType(relativeToAnchorVector, scaleDt);

    TransformScaleOffsetHelper(componentHandle, scaleDt, anchor);
  }

  void coreSpace::TransformComponentData::TransformScaleOffsetHelper(hndl componentHandle, VectorType scaleDt, VectorType anchor)
  {
    VectorType relativeToAnchorVector = math::SubVectorType(GetPosition(componentHandle), anchor);
    relativeToAnchorVector = math::ScaleVectorType(relativeToAnchorVector, scaleDt);
    SetPosition(componentHandle, math::ToPoint4(math::AddVectorType(anchor, relativeToAnchorVector)));
    SetScale(componentHandle, math::ScaleVectorType(GetScale(componentHandle), scaleDt));

    auto& children = GET_OBJECT_MANAGER->GetObject(GetObject(componentHandle)).GetChildren();

    if(children.empty() == true)
    {
      return;
    }

    for(hndl childHndl : children)
    {
      TransformScaleOffsetHelper(GetComponent(childHndl), scaleDt, anchor);
    }
  }

  void coreSpace::TransformComponentData::TransformRotateOffset(hndl componentHandle, VectorType newRotEuler, VectorType anchor)
  {
    VectorType rotDt = math::SubVectorType(newRotEuler, GetRotation(componentHandle));
    TransformRotateOffsetHelper(componentHandle, rotDt, anchor);
  }

  void coreSpace::TransformComponentData::TransformRotateOffsetHelper(hndl componentHandle, VectorType rotDt, VectorType anchor)
  {
    MatrixType initialRotMat = math::CreateMatrixTypeFromEuler(GetRotation(componentHandle));
    MatrixType relativeOffsetPosMat = math::CreateTranslationMatrixType(math::SubVectorType(GetPosition(componentHandle), anchor));
    MatrixType deltaRotMat = math::CreateMatrixTypeFromEuler(rotDt);

    MatrixType result = MxM(MxM(deltaRotMat, relativeOffsetPosMat), initialRotMat);

    SetPosition(componentHandle, math::ToPoint4(math::AddVectorType(math::GetColumnMatrixType(result, 3), anchor)));
    GET_TRANSFORM_DATA->m_rotationContainer[componentHandle] = (componentHandle, math::CreateQuaternion(result));

    auto& children = GET_OBJECT_MANAGER->GetObject(GetObject(componentHandle)).GetChildren();

    if(children.empty() == true)
    {
      return;
    }

    for(hndl childHndl : children)
    {
      TransformRotateOffsetHelper(GetComponent(childHndl), rotDt, anchor);
    }
  }

  ////////////////////////////////////////////////////////////////////////// CFRAME

  AUTO_LUAREG_COMPONENT_PROPERTY_MATRIX(Transform, CFrame);
  void TransformComponentData::SetCFrameLua(hndl componentHandle, const scriptSpace::cframeBinding::LuaCFrame &newValue)
  {
    SetCFrame(componentHandle, newValue);
  }
  scriptSpace::cframeBinding::LuaCFrame TransformComponentData::GetCFrameLua(hndl componentHandle)
  {
    return scriptSpace::cframeBinding::LuaCFrame(GetCFrame(componentHandle));
  }
  MatrixType TransformComponentData::GetCFrame(hndl componentHandle)
  {
    MatrixType val = math::MatrixTypeMultMatrixType(math::CreateTranslationMatrixType(GetPosition(componentHandle)), math::CreateMatrixType(m_rotationContainer.GetByValue(componentHandle)));
    return val;
  }
  void VECTOR_CALL TransformComponentData::SetCFrame(hndl componentHandle, MatrixType newValue)
  {
    m_rotationContainer[componentHandle] = math::CreateQuaternion(newValue);
    m_positionContainer[componentHandle] = math::GetColumnMatrixType(newValue, 3);
  }
  coreSpace::DynamicEntity TransformComponentData::ArbitraryGetCFrame(hndl componentHandle)
  {
    coreSpace::DynamicEntity val;
    val.Set(GET_COMPONENT_DATA(TransformComponentData)->GetCFrame(componentHandle));
    return val;
  }
  void TransformComponentData::ArbitrarySetCFrame(hndl componentHandle, coreSpace::DynamicEntity newValue)
  {
    MatrixType val;
    newValue.Get(val);
    GET_COMPONENT_DATA(TransformComponentData)->SetCFrame(componentHandle, val);
  }
  const int32 CONCATENATE(c_propertyGet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertyGetter("Transform", "CFrame", TransformComponentData::ArbitraryGetCFrame);
  const int32 CONCATENATE(c_propertySet, __COUNTER__) = scriptSpace::LuaDataManager::RegisterArbitraryPropertySetter("Transform", "CFrame", TransformComponentData::ArbitrarySetCFrame);

  ////////////////////////////////////////////////////////////////////////// BASIS
  AUTO_LUAREG_COMPONENT_MEMBER_FUNCTION(Transform, GetExtentScalar);
  VectorType TransformComponentData::GetExtentScalar(hndl componentHandle)
  {
    hndl objectHandle = GetObject(componentHandle);

    auto *modelComponentData = GET_COMPONENT_DATA(prism::ModelComponentData);
    hndl modelComponent = modelComponentData->GetComponent(objectHandle);

    if (modelComponent != INVALID_HANDLE)
    {
      auto extent = modelComponentData->m_modelContainer[modelComponent]->m_extentScalar;
      return math::CreateVectorType(extent.x, extent.y, extent.z,0.0f); 
    }

    auto *animatedModelComponentData = GET_COMPONENT_DATA(prism::AnimatedModelComponentData);
    hndl animatedModelComponent = animatedModelComponentData->GetComponent(objectHandle);
    if (animatedModelComponent != INVALID_HANDLE)
    {
      auto extent = animatedModelComponentData->m_modelContainer[animatedModelComponent]->m_extentScalar;
      return math::CreateVectorType(extent.x, extent.y, extent.z,0.0f);
    }

    auto *translucentModelComponentData = GET_COMPONENT_DATA(prism::TranslucentModelComponentData);
    hndl translucentModelComponent = translucentModelComponentData->GetComponent(objectHandle);
    if(translucentModelComponent != INVALID_HANDLE)
    {
      auto extent = translucentModelComponentData->m_modelContainer[translucentModelComponent]->m_extentScalar;
      return math::CreateVectorType(extent.x, extent.y, extent.z, 0.0f);
    }
    return math::CreateVectorType(1.0f, 1.0f, 1.0f, 0.0f);
  }

  AUTO_LUAREG_COMPONENT_MEMBER_FUNCTION(Transform, GetXBasis);
  VectorType TransformComponentData::GetXBasis(hndl componentHandle) const
  {
    MatrixType basis = math::CreateMatrixType(m_rotationContainer.GetByValue(componentHandle));
    return math::GetColumnMatrixType(basis, 0);
  }

  AUTO_LUAREG_COMPONENT_MEMBER_FUNCTION(Transform, GetYBasis);
  VectorType TransformComponentData::GetYBasis(hndl componentHandle) const
  {
    MatrixType basis = math::CreateMatrixType(m_rotationContainer.GetByValue(componentHandle));
    return math::GetColumnMatrixType(basis, 1);
  }

  AUTO_LUAREG_COMPONENT_MEMBER_FUNCTION(Transform, GetZBasis);
  VectorType TransformComponentData::GetZBasis(hndl componentHandle) const
  {
    MatrixType basis = math::CreateMatrixType(m_rotationContainer.GetByValue(componentHandle));
    return math::GetColumnMatrixType(basis, 2);
  }

  
  prism::PAABB TransformComponentData::GetAABB(hndl componentHandle) 
  {
    TRACE_ERROR(m_rotationMatrixContainer.IsAlive(componentHandle),
                "This component handle isn't alive");
    // We are retrieving the extent scalar converting it and the scale to a half vector
    // We then rotate the half vector to get the correct aabb
    VectorType extentScalar = math::InverseVectorType(math::ToPoint4(GetExtentScalar(componentHandle)));
    VectorType scaledExtentScalar = math::ScaleVectorType(math::ScaleVectorType(m_scaleContainer[componentHandle], 0.5f), extentScalar);
    scaledExtentScalar = math::AbsoluteValueVectorType(scaledExtentScalar);
    MatrixType rotation = m_rotationMatrixContainer[componentHandle];
    //MatrixType rotation = math::CreateMatrixType(m_rotationContainer[componentHandle]);
    

    // faster than multiply 9 vectors by rotation and retrieving the length and adding them
    VectorType r0 = math::DotVectorType(math::AbsoluteValueVectorType(rotation.rows[0]), scaledExtentScalar);
    VectorType r1 = math::DotVectorType(math::AbsoluteValueVectorType(rotation.rows[1]), scaledExtentScalar);
    VectorType r2 = math::DotVectorType(math::AbsoluteValueVectorType(rotation.rows[2]), scaledExtentScalar);

    // construct a vector from the dot products
    VectorType shuffle0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(0, 0, 0, 0)); // r0.x, r0.x, r1.x, r1.x
    VectorType finalShuffle = _mm_shuffle_ps(shuffle0, r2, _MM_SHUFFLE(0, 0, 2, 0)); // s0.x, s0.z, r2.x, r2.x
    finalShuffle = math::ToVectorType(finalShuffle);


    return prism::PAABB(m_positionContainer[componentHandle], math::ToVectorType(finalShuffle));
  }

  prism::PAABB TransformComponentData::GetAABBRaw(hndl componentHandle)
  {
    TRACE_ERROR(m_rotationMatrixContainer.IsAlive(componentHandle),
                "This component handle isn't alive");
    // We are retrieving the extent scalar converting it and the scale to a half vector
    // We then rotate the half vector to get the correct aabb
    VectorType extentScalar = math::InverseVectorType(math::ToPoint4(GetExtentScalar(componentHandle)));
    VectorType scaledExtentScalar = math::ScaleVectorType(math::ScaleVectorType(m_scaleContainer[componentHandle], 0.5f), extentScalar);
    scaledExtentScalar = math::AbsoluteValueVectorType(scaledExtentScalar);
    //MatrixType rotation = m_rotationMatrixContainer[componentHandle];
    MatrixType rotation = math::CreateMatrixType(m_rotationContainer[componentHandle]);
    

    // faster than multiply 9 vectors by rotation and retrieving the length and adding them
    VectorType r0 = math::DotVectorType(math::AbsoluteValueVectorType(rotation.rows[0]), scaledExtentScalar);
    VectorType r1 = math::DotVectorType(math::AbsoluteValueVectorType(rotation.rows[1]), scaledExtentScalar);
    VectorType r2 = math::DotVectorType(math::AbsoluteValueVectorType(rotation.rows[2]), scaledExtentScalar);

    // construct a vector from the dot products
    VectorType shuffle0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(0, 0, 0, 0)); // r0.x, r0.x, r1.x, r1.x
    VectorType finalShuffle = _mm_shuffle_ps(shuffle0, r2, _MM_SHUFFLE(0, 0, 2, 0)); // s0.x, s0.z, r2.x, r2.x
    finalShuffle = math::ToVectorType(finalShuffle);


    return prism::PAABB(m_positionContainer[componentHandle], math::ToVectorType(finalShuffle));
  }

  prism::PAABB TransformComponentData::GetAABB(hndl componentHandle, float radius)
  {
    // We are retrieving the extent scalar converting it and the scale to a half vector
    // We then rotate the half vector to get the correct aabb
    VectorType scaledExtentScalar = math::CreateVectorType(radius);
    MatrixType rotation = m_rotationMatrixContainer[componentHandle];

    // faster than multiply 9 vectors by rotation and retrieving the length and adding them
    VectorType r0 = math::DotVectorType(math::AbsoluteValueVectorType(rotation.rows[0]), scaledExtentScalar);
    VectorType r1 = math::DotVectorType(math::AbsoluteValueVectorType(rotation.rows[1]), scaledExtentScalar);
    VectorType r2 = math::DotVectorType(math::AbsoluteValueVectorType(rotation.rows[2]), scaledExtentScalar);

    // construct a vector from the dot products
    VectorType shuffle0 = _mm_shuffle_ps(r0, r1, _MM_SHUFFLE(0, 0, 0, 0)); // r0.x, r0.x, r1.x, r1.x
    VectorType finalShuffle = _mm_shuffle_ps(shuffle0, r2, _MM_SHUFFLE(0, 0, 2, 0)); // s0.x, s0.z, r2.x, r2.x


    //return prism::PAABB(m_positionContainer[componentHandle], finalShuffle);
    return prism::PAABB(m_positionContainer[componentHandle], math::ToVectorType(finalShuffle));
  }
  AUTO_LUAREG_COMPONENT_MEMBER_FUNCTION(Transform, RotateToVector);
  void TransformComponentData::RotateToVector(hndl componentHandle, scriptSpace::vectorBinding::LuaVector const &vector)
  {
    RotateToVectorDetail(componentHandle, math::CreateVectorType(vector.m_vec[0], vector.m_vec[1], vector.m_vec[2], 0.0f));
  }

  void VECTOR_CALL TransformComponentData::RotateToVectorDetail(hndl componentHandle, VectorType vector)
  {
    VectorType crossed = math::CrossVectorType(math::g_worldY, math::NormalizeVectorType(vector));

    float sinTheta = math::MagnitudeVectorTypeScalar(crossed);

    float angle = std::asin(sinTheta);

    m_rotationContainer[componentHandle] = math::CreateQuaternion(math::NormalizeVectorType(crossed), angle * RADIANS_TO_DEGREES);
  }

  AUTO_LUAREG_COMPONENT_MEMBER_FUNCTION(Transform, Rotate);
  void TransformComponentData::Rotate(hndl componentHandle, scriptSpace::cframeBinding::LuaCFrame const &quat)
  {
    VectorType deltaQuaternion = quat.ToVector();
    _Rotate(componentHandle, deltaQuaternion);
  }

  void VECTOR_CALL TransformComponentData::_Rotate(hndl componentHandle, VectorType quat)
  {
    VectorType newQuaternion = math::NormalizeVectorType(math::QuaternionMultQuaternion(m_rotationContainer.GetByValue(componentHandle), quat));
    m_rotationContainer[componentHandle] = newQuaternion;
  }
  unsigned TransformComponentData::Extract(prism::PRenderObject *objects, 
                                           const hndl *objectHandles, 
                                           size_t *objectTypes, 
                                           unsigned size)
  {
    unsigned i = 0;
    // Retrieve the transform data
    for (; i < size; ++i)
    {
      hndl component = GetComponent(objectHandles[i]);

      TRACE_ERROR(component != INVALID_HANDLE,
                  "Shouldn't have a render object without a transform.");

      
      _ExtractObject(&objects[i], &objectTypes[i], component);
    }

    return i;
  }

  unsigned TransformComponentData::Extract(prism::PAnimatedRenderObject *objects, 
                                           const hndl *objectHandles, 
                                           size_t *objectTypes, 
                                           unsigned size)
  {
    unsigned i = 0;
    // Retrieve the transform data
    for (; i < size; ++i)
    {
      hndl component = GetComponent(objectHandles[i]);

      if(component == INVALID_HANDLE)
        continue;
//       TRACE_ERROR(component != INVALID_HANDLE,
//                   "Shouldn't have a render object without a transform.");

      
      _ExtractObject(&objects[i], &objectTypes[i], component);
    }

    return i;
  }

  void TransformComponentData::_ExtractObject(prism::PRenderObject *object,
                                                  size_t *objectType,
                                                  size_t componentHandle)
  {
    math::GetMatrixType(m_transformMatrixContainer[componentHandle], &object->m_objData.g_world);
    math::GetMatrixType(m_rotationMatrixContainer[componentHandle], &object->m_objData.g_rotation);
  }

  MatrixType TransformComponentData::_CalculateTransform(hndl transform)
  {
    MatrixType trans = math::CreateTranslationMatrixType(m_positionContainer[transform]);
    VectorType quat = m_rotationContainer[transform];
    MatrixType rot = math::CreateMatrixType(quat);
    MatrixType scale = math::CreateScaleMatrixType(m_scaleContainer[transform]);
    MatrixType result = MxM(trans, MxM(rot, scale));
    return result;
  }

  AUTO_LUAREG_COMPONENT_MEMBER_FUNCTION(Transform, AlignBasis);
  void TransformComponentData::AlignBasis(hndl transform, int32 basis, scriptSpace::vectorBinding::LuaVector const &vector)
  {
    _AlignBasis(transform, basis, vector, m_rotationContainer.GetByValue(transform));
  }

  void VECTOR_CALL TransformComponentData::_AlignBasis(hndl transform, int32 basis, VectorType vector, VectorType initialOrientation)
  {
    MatrixType rotMat = math::CreateMatrixType(initialOrientation);
    VectorType basisVector = math::GetColumnMatrixType(rotMat, basis % 3);

    if (math::IsEqualVectorType(basisVector, vector))
      return;

    if (basis > 2)
      basisVector = math::NegateVectorType(basisVector);

    VectorType cross = math::CrossVectorType(vector, basisVector);

    if (math::IsEqualVectorType(cross, math::g_vector4Zero))
    {
      if (basis != 1 && basis != 4)
        cross = math::g_worldY;
      else
        cross = math::g_worldX;
    }
    cross = math::NormalizeVectorType(cross);

    f32 theta = math::AngleBetween(vector, basisVector);

    VectorType deltaQuat = math::CreateQuaternion(cross, theta);

    VectorType newQuaternion = math::NormalizeVectorType(math::QuaternionMultQuaternion(initialOrientation, deltaQuat));
    m_rotationContainer[transform] = newQuaternion;
  }

  // Jobs
  void TransformComponentData::_PushExecutionNodes(void) const
  {
    //int dummyPropertyFn = scriptSpace::LuaDataManager::RegisterPropertyFunc("Transform", "Position", luabridge::AddPropertyComponent < decltype(&TransformComponentData::GetPosition), decltype(&TransformComponentData::SetPositionLua), scriptSpace::TransformBind, &TransformComponentData::GetPosition, &TransformComponentData::SetPositionLua> );

    REGISTER_COMPONENT_TRANSFORMS("PushAliveTransformComponents", PushAliveTransforms);
    REGISTER_COMPONENT_TRANSFORMS("UpdateTransforms", UpdateTransforms);

//     auto *node0 = GET_EXECUTION_MANAGER->GetExecutionNode("PushAliveTransformComponents");
//     GET_EXECUTION_MANAGER->AddDependency(GET_EXECUTION_MANAGER->GetRoot(), node0);
// 
//     auto *node1 = GET_EXECUTION_MANAGER->GetExecutionNode("UpdateTransforms");
//     GET_EXECUTION_MANAGER->AddDependency(node0, node1);
  }
END_DECLARE_COMPONENT_DEFINITION
