/*!****************************************************************************
\file    ObjectManager.h
\author  Kaden Nugent (kaden.n)
\date    Apr 24, 2015

\brief   Handles the how objects are stored.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include "SlotMap.h"
#include "CustomTypes.h"
#include "ObjectEntity.h"
#include "ComponentData.h"

void InitializeObjectManager(void);

namespace objectSpace
{
  // The manager structure
  class ObjectManager
  {
  public:
    ObjectManager();  // Default constructor
    ~ObjectManager(); // Default destructor

    // Adds an object to the object list
    hndl CreateObject(std::string const& objectName = "GameObject", hndl parent = -1, std::string const& archetypeName = "Custom");
    hndl CreateObjectFromArchetype(size_t archetypeNameHash, hndl parent = -1);
    hndl CreateObjectFromArchetype(std::string const& archetypeName, hndl parent = -1);

    // Special object creation
    hndl CreateObjectRoot();
    hndl CreateObjectSpace(const std::string& objectName = "GameSpace");

    // Places a given object into the debris
    void DestroyObject(hndl objectHandle, f32 timeToDelete = 0);

    // Permanently deletes all objects stored within it's bounds
    void ClearDebris(f32 deltaTime);

    // Gets the object by reference using the object's handle
    objectSpace::Object &GetObject(hndl objectHandle);

    // Checks to see whether or not a certain object exists
    bool IsAlive(hndl objectHandle) const;

    bool IsActive(hndl objectHandle) const;
    // Get Object handle
    hndl GetObjectHandleByName(const std::string& objectName) const;
    hndl GetObjectHandleByName(size_t objectNameHash) const;

    // Serialization
    void RegisterComponentData(componentSpace::Component_Type_ type,
                               componentSpace::AddToObject addToObjectFunction,
                               componentSpace::SerializeComponent serializeFunction,
                               componentSpace::CompileComponent compileFunction,
                               componentSpace::DeserializeComponent deserializeFunction,
                               componentSpace::GetNumComponents numComponentsFunction,
                               componentSpace::GetComponents getComponentsFunction,
                               void *componentData
                              );
    void SerializeObject(hndl objectHandle, char const *name);
    void CompileObject(char const *name);
    
    int32 GetNumObjects(void);

    hndl GetRootHandle(void);
    hndl GetLevelHandle(void);
    hndl GetEnemyHandle(void);

  private:
    // Tells the object manager about the components in the engine
    struct ComponentDefinition
    {
      ComponentDefinition(componentSpace::Component_Type_ type = (componentSpace::Component_Type_)0,
                          componentSpace::AddToObject addToObjectFunction = NULL,
                          componentSpace::SerializeComponent serializeFunction = NULL,
                          componentSpace::CompileComponent compileFunction = NULL,
                          componentSpace::DeserializeComponent deserializeFunction = NULL,
                          componentSpace::GetNumComponents numComponentsFunction = NULL,
                          componentSpace::GetComponents getComponentsFunction = NULL,
                          void *data = NULL
                         );

      componentSpace::Component_Type_ m_type;
      componentSpace::AddToObject m_addToObjectFunction;
      componentSpace::SerializeComponent m_serializeFunction;
      componentSpace::CompileComponent m_compileFunction;
      componentSpace::DeserializeComponent m_deserializeFunction;
      componentSpace::GetNumComponents m_numComponentsFunction;
      componentSpace::GetComponents m_getComponentsFunction;
      void *m_data;
    };

    ComponentDefinition *_GetComponentDefinition(componentSpace::Component_Type_ type);
    void _ComponentTypeToString(componentSpace::Component_Type_ type, char *string) const;
    componentSpace::Component_Type_ _StringToComponentType(char const *string) const;

    // Frees an object and its children from memory
    void FreeObject(hndl objectHandle);

    // Holds all objects in the game (sys WOW)
    dataStructures::SlotMap<Object> m_objectList;

    // Holds objects ready for destruction, takes a pointer to the object and the time to delete
    std::map< hndl, f32 > m_objectDebris;

    // Component definitions
    dataStructures::SlotMap<ComponentDefinition> m_componentDefinitions;

    // Hold onto the root
    hndl m_root;

    // Hold onto the main game area
    hndl m_level;
    hndl m_enemy;

    Object m_nullObject;
  };

} // namespace objectSpace
