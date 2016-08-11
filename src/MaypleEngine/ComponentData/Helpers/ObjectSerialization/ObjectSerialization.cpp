/*!****************************************************************************
\file    ObjectSerialization.cpp
\author  Kaden Nugent (kaden.n)
\date    July 29, 2015

\brief   Serialize me captain.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"

// Son J, ohayou gozaimasu, おはようございます。
#include "json.h"

#include "ObjectSerialization.h" // This header file
#include "ManagerLocator.h"      // Managers
#include "ObjectManager.h"       // Object management
#include "LuaDataManager.h"      // Arbitrary component and property retrieval
#include "DynamicEntity.h"       // For grabbing any and all element types
#include "ScriptEntity.h"        // Scripts
#include "ActiveAudioEvents.h "  // Audio
#include "DataEntity.h"          // User data
#include "StringManager.h"       // String manager
#include "KeyframeComponentData.h" // Special Serialization

namespace coreSpace
{
  // Helpers
  namespace
  {
    template <typename T>
    void DynamicJsonSet(DynamicEntity& dyn, Json::Value& root)
    {
      T val;
      dyn.Get(val);

      root = Json::Value(val);
    }
  }

  // Recursively write to a given json root
  void JsonHierarchySet(DynamicEntity& dyn, std::string const& name, Json::Value& root)
  {
    if (dyn.Type() == Type_Int_)
    {
      DynamicJsonSet<int32>(dyn, root[name]);
    }
    else if (dyn.Type() == Type_Uint_)
    {
      DynamicJsonSet<uint32>(dyn, root["U#" + name]);
    }
    else if (dyn.Type() == Type_Int64_)
    {
      int64 val;
      dyn.Get(val);

      Json::Value vec(Json::arrayValue);
      vec.append(Json::Value(static_cast<uint32>((val >> 32) & 0xffffffff)));
      vec.append(Json::Value(static_cast<uint32>(val & 0xffffffff)));

      root["Z#" + name] = vec;
    }
    else if (dyn.Type() == Type_Uint64_)
    {
      uint64 val;
      dyn.Get(val);

      Json::Value vec(Json::arrayValue);
      vec.append(Json::Value(static_cast<uint32>((val >> 32) & 0xffffffff)));
      vec.append(Json::Value(static_cast<uint32>(val & 0xffffffff)));

      root["X#" + name] = vec;
    }
    else if (dyn.Type() == Type_Bool_)
    {
      DynamicJsonSet<bool>(dyn, root[name]);
    }
    else if (dyn.Type() == Type_Rigidbody_)
    {
      physicsSpace::Rigidbody_Type_ val;
      dyn.Get(val);

      root["R#" + name] = Json::Value(static_cast<int32>(val));
    }
    else if (dyn.Type() == Type_Float_)
    {
      DynamicJsonSet<f32>(dyn, root[name]);
    }
    else if (dyn.Type() == Type_String_)
    {
      std::string val;
      dyn.Get(val);

      root[name] = val;
    }
    else if (dyn.Type() == Type_Vector_)
    {
      VectorType val;
      dyn.Get(val);

      f32 sweg[4];
      math::GetElementsVectorType(val, sweg);

      Json::Value vec(Json::arrayValue);
      vec.append(Json::Value(sweg[0]));
      vec.append(Json::Value(sweg[1]));
      vec.append(Json::Value(sweg[2]));
      vec.append(Json::Value(sweg[3]));

      root[name] = vec;
    }
    else if (dyn.Type() == Type_Array_)
    {
      std::vector<coreSpace::DynamicEntity> valArray;
      dyn.Get(valArray);

      Json::Value container(Json::arrayValue);
      Dynamic_Type_ containerType = Type_Null_;

      while (!valArray.empty())
      {
        coreSpace::DynamicEntity& val = valArray.back();

        if (val.Type() == Type_Script_)
        {
          Json::Value script(Json::arrayValue);

          scriptSpace::ScriptEntity temp;
          val.Get(temp);

          script.append(Json::Value(temp.m_name));
          script.append(Json::Value(temp.m_type));

          container.append(script);

          containerType = Type_Script_;
        }
        else if (val.Type() == Type_Data_)
        {
          Json::Value data;

          DataEntity temp;
          val.Get(temp);

          JsonHierarchySet(temp, HASH_GEN(temp.m_name), data);

          container.append(data);

          containerType = Type_Data_;
        }

        valArray.pop_back();
      }

      if (containerType == Type_Data_)
        root["D#" + name] = container;
      else if (containerType == Type_Script_)
        root["S#" + name] = container;
    }
    else
    {
      // Unserializable type
      std::cout << "Cannot serialize: " << name << std::endl;
    }
  }

  // Recursively read to a dynamic element, from a given json root
  DynamicEntity JsonHierarchyGet(std::string& propertyName, const Json::Value& propertyCurr)
  {
    DynamicEntity dyn;

    // Special cases forced type
    std::size_t positionFound = propertyName.find("#");
    if (positionFound != std::string::npos)
    {
      const char typeChar = propertyName[0];
      propertyName = propertyName.substr(positionFound + 1);

      // Unsigned
      if (typeChar == 'U')
      {
        dyn.Set(propertyCurr.asUInt());
      }
      // Int 64
      else if (typeChar == 'Z')
      {
        dyn.Set(static_cast<int64>((static_cast<uint64>(propertyCurr[0u].asUInt()) << 32) | static_cast<uint64>(propertyCurr[1u].asUInt())));
      }
      // Unsigned 64
      else if (typeChar == 'X')
      {
        dyn.Set((static_cast<uint64>(propertyCurr[0u].asUInt()) << 32) | static_cast<uint64>(propertyCurr[1u].asUInt()));
      }
      // RigidbodyType
      else if (typeChar == 'R')
      {
        int32 val = propertyCurr.asInt();
        dyn.Set(static_cast<physicsSpace::Rigidbody_Type_>(val));
      }
      // Script
      else if (typeChar == 'S')
      {
        std::vector<coreSpace::DynamicEntity> valArray;

        for (uint32 i = 0; i < propertyCurr.size(); ++i)
        {
          scriptSpace::ScriptEntity script;

          script.m_name = propertyCurr[i][0u].asString();
          script.m_type = static_cast<scriptSpace::Script_Type_>(propertyCurr[i][1u].asInt());

          coreSpace::DynamicEntity temp;
          temp.Set(script);
          valArray.push_back(temp);
        }

        dyn.Set(valArray);
      }
      // Data
      else if (typeChar == 'D')
      {
        std::vector<coreSpace::DynamicEntity> valArray;

        for (uint32 i = 0; i < propertyCurr.size(); ++i)
        {
          std::string dataName = propertyCurr[i].getMemberNames()[0];
          DataEntity data(JsonHierarchyGet(dataName, propertyCurr[i][dataName]));
          data.m_name = HASH_GEN(dataName);
          data.m_id = coreSpace::dataID++;

          coreSpace::DynamicEntity temp;
          temp.Set(data);
          valArray.push_back(temp);
        }

        dyn.Set(valArray);
      }
    }

    // Check each property type
    else if (propertyCurr.isInt())
    {
      dyn.Set(propertyCurr.asInt());
    }
    else if (propertyCurr.isBool())
    {
      dyn.Set(propertyCurr.asBool());
    }
    else if (propertyCurr.isDouble())
    {
      dyn.Set(static_cast<f32>(propertyCurr.asDouble()));
    }
    else if (propertyCurr.isString())
    {
      dyn.Set(propertyCurr.asString());
    }
    else if (propertyCurr.isArray())
    {
      // It is a vector
      if (propertyCurr.size() <= 4)
      {
        f32 val[4] = { 0, 0, 0, 0 };

        for (uint32 i = 0; i < propertyCurr.size(); ++i)
          val[i] = static_cast<float>(propertyCurr[i].asDouble());

        VectorType vec = math::CreateVectorType(val);

        dyn.Set(vec);
      }
    }

    return dyn;
  }

  void SerializeHierarchy(hndl objectHandle, Json::Value &root)
  {
    // Go through the hierarchy, get all underlying objects
    auto& obj = GET_OBJECT_MANAGER->GetObject(objectHandle);
    std::string JsonName(std::to_string(objectHandle) + "@" + obj.m_name);

    // seralize the object name even when there are not children
    root[JsonName];

    for (hndl it : obj.GetChildren()) // HANDLE IT, BOTCH
    {
      SerializeHierarchy(it, root[JsonName]["Children"]);
    }

    // Check those components yo
    for (auto& it : scriptSpace::LuaDataManager::GetLuaDataMap())
    {
      if (!it.second.m_componentDetacher)
        continue;

      // Get the component handle
      hndl componentHandle = it.second.m_componentHandle(objectHandle);

      if (componentHandle < 0)
        continue;

      if (JsonName.substr(2) == "Level" && it.first == "ShadowModel")
      {
        WARN_IF(true, "Shadow model serialized!");
        continue;
      }

      if (it.first == "Keyframe")
      {
        GET_COMPONENT_DATA(aiSpace::KeyframeComponentData)->CustomSerializeComponent(componentHandle, it, JsonName, root);
        continue;
      }

      if (it.second.m_propertyData.size() > 0)
      {
        // serialize the component even if it doesn't have any serializable properties
        root[JsonName][it.first];

        for (auto& prop : it.second.m_propertyData)
        {
          if (!prop.second.m_propertyGetter || prop.first == "CFrame")
            continue;

          JsonHierarchySet(prop.second.m_propertyGetter(componentHandle), prop.first, root[JsonName][it.first]);
        }
      }
      else
      {
        root[JsonName] = Json::nullValue;
      }

    }
  }

  void DeserializeComponentHierarchy(const Json::Value &root, hndl ownerHandle)
  {
    // Components
    for (Json::ValueIterator it = root.begin(); it != root.end(); ++it)
    {
      const char* componentName = it.memberName();
      const Json::Value& compRoot = root[componentName];

      // Psudo "child" component
      if(std::strcmp(componentName, "Children") == 0)
      {
        DeserializeObjectHierarchy(compRoot, ownerHandle);
      }
      // All other components
      else
      {
        if (std::strcmp(componentName, "Keyframe") == 0)
        {
          GET_COMPONENT_DATA(aiSpace::KeyframeComponentData)->CustomDeserializeComponent(ownerHandle, std::string(componentName), root);
          continue;
        }

        luabridge::LuaRef *args[8] = { nullptr };
        scriptSpace::LuaDataManager::CallAttachFunc(componentName, ownerHandle, args);

        // Set all the properties
        for(Json::ValueIterator prop = compRoot.begin(); prop != compRoot.end(); ++prop)
        {
          // Retrieve the component handle
          auto& propertyCont = scriptSpace::LuaDataManager::GetLuaDataMap()[componentName];
          hndl componentHandle = propertyCont.m_componentHandle(ownerHandle);

          // Get the correct name (if it is a uint, that is stored in the name)
          std::string propertyName = prop.memberName();
          const Json::Value& propertyCurr = compRoot[propertyName];

          DynamicEntity dyn = JsonHierarchyGet(propertyName, propertyCurr);

          auto& dataProp = propertyCont.m_propertyData.find(propertyName);

          if(dyn.Type() == Type_Null_ || dataProp == propertyCont.m_propertyData.end())
          {
            // Unserializable type
            std::cout << "Cannot deserialize: " << prop.memberName() << std::endl;
          }
          else
          {
            // Mad h4xx
            dataProp->second.m_propertySetter(componentHandle, dyn);
          }
        }

      }
    }
  }

  void DeserializeObjectHierarchy(const Json::Value &root, hndl parentHandle)
  {
    // Children
    for (Json::ValueIterator it = root.begin(); it != root.end(); ++it)
    {
      std::string memberName = it.memberName();

      // Get rid of the extra data if it exists
      std::size_t positionFound = memberName.find("@");
      if (positionFound != std::string::npos)
        memberName = memberName.substr(positionFound + 1);

      // Create the object, add its components
      hndl objectHandle = GET_OBJECT_MANAGER->CreateObject(memberName, parentHandle);
      DeserializeComponentHierarchy(root[it.memberName()], objectHandle);
    }
  }
}
