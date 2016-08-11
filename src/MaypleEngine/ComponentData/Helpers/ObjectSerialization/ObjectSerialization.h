/*!****************************************************************************
\file    ObjectSerialization.h
\author  Kaden Nugent (kaden.n)
\date    July 29, 2015

\brief   Serialize me captain.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include <string>

#include "CustomTypes.h" // Diesel engine types

namespace coreSpace
{
  // Predeclarations
  class DynamicEntity;

  void JsonHierarchySet(DynamicEntity& dyn, std::string const& name, Json::Value& root);
  DynamicEntity JsonHierarchyGet(std::string& propertyName, const Json::Value& propertyCurr);
  void SerializeHierarchy(hndl objectHandle, Json::Value &root);
  void DeserializeComponentHierarchy(const Json::Value &root, hndl ownerHandle);
  void DeserializeObjectHierarchy(const Json::Value &root, hndl parentHandle);
}
