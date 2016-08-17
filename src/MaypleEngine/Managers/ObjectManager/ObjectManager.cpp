/*!****************************************************************************
\file    ObjectManager.cpp
\author  Kaden Nugent (kaden.n)
\date    Apr 24, 2015

\brief   Handles the how objects are stored.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"
#include "ObjectManager.h"
#include "ComponentDataLocator.h"
#include "ManagerLocator.h"
#include "ObjectArchetype.h"
#include "ObjectSerialization.h"
// #include "ArchetypeStorager.h"
// #include "LevelManager.h"

namespace objectSpace
{

  void InitializeObjectManager(void)
  {
    managerSpace::ManagerLocator::SetObjectManager(new objectSpace::ObjectManager());
  }

  ////////////////////////////////////////////////////////////////////////// PUBLIC

  // Default constructor
  ObjectManager::ObjectManager() : m_root(-1), m_level(-1), m_objectList(10, -1, true), m_nullObject("NULL_OBJECT")
  {
    // Temporarily add a bunch of archetypes here
    std::string directory("Serialized/Archetypes/");
    HANDLE dir;
    WIN32_FIND_DATA fileData;

    // Check if files exist in this directory
    if ((dir = FindFirstFile((directory + "*").c_str(), &fileData)) == INVALID_HANDLE_VALUE)
      return;

    do {
      std::string fileName(fileData.cFileName);
      const bool is_directory = (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;

      if (fileName[0] == '.')
        continue;

      if (is_directory)
        continue;

      auto dotPos = fileName.find(".");
      if (dotPos != std::string::npos)
      {
        fileName = fileName.substr(0, dotPos);
      }

    } while (FindNextFile(dir, &fileData));

    FindClose(dir);
  }

  // Default destructor
  ObjectManager::~ObjectManager()
  {
  
  }

  // Adds the game root
  hndl ObjectManager::CreateObjectRoot()
  {
    // Get an index to an open slot
    hndl newHandle = m_objectList.AllocateSlot();

    Object* newObject = new(&m_objectList[newHandle]) Object("Game", "Custom");
    newObject->m_index = newHandle;
    newObject->LockObject();

    // Set the root
    m_root = newHandle;

    // Root should be the only object without a parent
    newObject->SetParent(-1);

    return newHandle;
  }

  // Adds a new space
  hndl ObjectManager::CreateObjectSpace(const std::string& objectName)
  {
    // Get an index to an open slot
    hndl newHandle = m_objectList.AllocateSlot();

    Object* newObject = new(&m_objectList[newHandle]) Object(objectName, "Custom");
    newObject->m_index = newHandle;
    newObject->LockObject();

    // If the main level hasn't been assigned, this must be it
    if (m_level < 0)
      m_level = newHandle;

    // All spaces branch from the root
    newObject->SetParent(m_root);

    if(objectName == "Enemy")
      m_enemy = newHandle;

    return newHandle;
  }

  // Adds an object to the object list
  hndl ObjectManager::CreateObject(const std::string& objectName, hndl parent, std::string const& archetypeName)
  {
    // Get an index to an open slot
    hndl newHandle = m_objectList.AllocateSlot();

    Object* newObject = new(&m_objectList[newHandle]) Object(objectName, archetypeName);
    newObject->m_index = newHandle;

    // Runtime h4xx, bind the child to the parent's properties list
    //scriptSpace::objectBinding::Obj::AddChildPropertyName(objectName.c_str());

    // Set the parent
    if (parent < 0)
    {
      // No parent given, add to the level
      newObject->SetParent(m_level);
    }
    else
    {
      // Parent given 
      newObject->SetParent(parent);
    }

    newObject->SetActive(GetObject(newObject->GetParent()).IsActive());

    // Update the editor if linked up
#ifdef _EDITOR
    editor::AddToObjectBrowser(newHandle);
#endif

    return newHandle;
  }

  hndl ObjectManager::CreateObjectFromArchetype(size_t archetypeNameHash, hndl parent)
  {
    return CreateObjectFromArchetype(HASH_GEN(archetypeNameHash), parent);
  }

  hndl ObjectManager::CreateObjectFromArchetype(std::string const& archetypeName, hndl parent)
  {
    if(GET_ARCHETYPE_STORAGER->IsArchetypeExist(archetypeName) == true)
    {
      const Json::Value& root = GET_ARCHETYPE_STORAGER->GetArchetype(archetypeName);

      if(parent < 0)
        parent = m_level;

      hndl mainObject = -1;

      // Parse the json values and place the objects in the game
      for(Json::ValueIterator it = root.begin(); it != root.end(); ++it)
      {
        std::string memberName = it.memberName();

        std::size_t positionFound = memberName.find("@");
        if(positionFound != std::string::npos)
          memberName = memberName.substr(positionFound + 1);

        mainObject = CreateObject(memberName, parent, archetypeName);

        coreSpace::DeserializeComponentHierarchy(root[it.memberName()], mainObject);
      }

      return mainObject;
    }
    else
    {
      const Json::Value root;

      std::ifstream inFile("Serialized/Archetypes/" + archetypeName + ".json");

      // Check if the desired archetype is actually a level
      if(!inFile.is_open())
      {
        inFile = std::ifstream("Serialized/Levels/" + archetypeName + ".json");
      }

      if(!inFile.is_open())
      {
        std::cout << "Unable to open file: Serialized/Archetypes/" + archetypeName + ".json";
        return -1;
      }

      Json::Reader reader;

      if(!reader.parse(inFile, const_cast<Json::Value&>(root), false))
      {
        std::cout << "Unable to parse file: Serialized/Archetypes/" + archetypeName + ".json";
        return -1;
      }

      if(parent < 0)
        parent = m_level;

      hndl mainObject = -1;

      // Parse the json values and place the objects in the game
      for(Json::ValueIterator it = root.begin(); it != root.end(); ++it)
      {
        std::string memberName = it.memberName();

        std::size_t positionFound = memberName.find("@");
        if(positionFound != std::string::npos)
          memberName = memberName.substr(positionFound + 1);

        mainObject = CreateObject(memberName, parent, archetypeName);

        coreSpace::DeserializeComponentHierarchy(root[it.memberName()], mainObject);
      }

      return mainObject;
    }
  }

  // Places a given object into the debris
  void ObjectManager::DestroyObject(hndl objectHandle, f32 timeToDelete)
  {
    // If the object is already on the debris list, just update it's time 
    m_objectDebris[objectHandle] = timeToDelete;

    // Remove child from parent (if there is a parent)
    GET_OBJECT_MANAGER->GetObject(objectHandle).SetParent(-1);
  }

  // Permanently deletes all objects stored within it's bounds
  void ObjectManager::ClearDebris(f32 deltaTime)
  {
    for (auto it = m_objectDebris.begin(); it != m_objectDebris.end(); /* Manual incrementing */ )
    {
      // Don't decrement object's time if the game is paused
      if (!GET_LEVEL_MANAGER->IsGamePaused())
        it->second -= deltaTime;
      
      // Release the object if time is up
      if (it->second < 0)
      {
        FreeObject(it->first);
        it = m_objectDebris.erase(it);
      }
      // Manually increase iterator
      else
        ++it;
    }
  }

  // Gets the object by reference using the object's handle
  Object &ObjectManager::GetObject(hndl objectHandle)
  {
    if(objectHandle < 0)
    {
      // If the current line is not in Lua, print a C++ error
      debugSpace::GetDebugInstance()->HandleAssertFailure(__FILE__, __LINE__, "Attempt to access a nil object");

      return m_nullObject;
    }

    return m_objectList[objectHandle];
  }

  // Checks to see whether or not a certain object exists
  bool ObjectManager::IsAlive(hndl objectHandle) const
  {
    return m_objectList.IsAlive(objectHandle);
  }

  bool ObjectManager::IsActive(hndl objectHandle) const
  {
    return m_objectList[objectHandle].IsActive();
  }

  hndl ObjectManager::GetObjectHandleByName(const std::string& objectName) const
  {
    return GetObjectHandleByName(GET_STRING_MANAGER->Hash(objectName));
  }

  hndl ObjectManager::GetObjectHandleByName(size_t objectNameHash) const
  {
    uint32 size = m_objectList.GetSize();
    for (uint32 i = 0; i < size; ++i)
    {
      if (m_objectList.IsAlive(i) == false)
      {
        continue;
      }

      if (GET_STRING_MANAGER->Hash(m_objectList[i].m_name) == objectNameHash)
      {
        return i;
      }
    }

    return INVALID_HANDLE;
  }

  void ObjectManager::RegisterComponentData(componentSpace::Component_Type_ type,
                                            componentSpace::AddToObject addToObjectFunction,
                                            componentSpace::SerializeComponent serializeFunction,
                                            componentSpace::CompileComponent compileFunction,
                                            componentSpace::DeserializeComponent deserializeFunction,
                                            componentSpace::GetNumComponents numComponentsFunction,
                                            componentSpace::GetComponents getComponentsFunction,
                                            void *componentData)
  {

    int32 newDefinition = m_componentDefinitions.AllocateSlot();
    new (&m_componentDefinitions[newDefinition]) ComponentDefinition(type, addToObjectFunction, serializeFunction, compileFunction, deserializeFunction, numComponentsFunction, getComponentsFunction, componentData);

  }

  ObjectManager::ComponentDefinition::ComponentDefinition(componentSpace::Component_Type_ type,
                                                          componentSpace::AddToObject addToObjectFunction,
                                                          componentSpace::SerializeComponent serializeFunction,
                                                          componentSpace::CompileComponent compileFunction,
                                                          componentSpace::DeserializeComponent deserializeFunction,
                                                          componentSpace::GetNumComponents numComponentsFunction,
                                                          componentSpace::GetComponents getComponentsFunction,
                                                          void *data
                                                         ):
    m_type(type),
    m_addToObjectFunction(addToObjectFunction),
    m_serializeFunction(serializeFunction),
    m_compileFunction(compileFunction),
    m_deserializeFunction(deserializeFunction),
    m_numComponentsFunction(numComponentsFunction),
    m_getComponentsFunction(getComponentsFunction),
    m_data(data)
  {
  }

  void ObjectManager::SerializeObject(hndl objectHandle, char const *name)
  {

    char archetypeFilePath[128] = "Archetypes/";
    std::strcat(archetypeFilePath, name);
    std::strcat(archetypeFilePath, ".json");

    std::ofstream archetypeFile(archetypeFilePath, std::ios_base::out | std::ios_base::trunc);

    ERROR_IF(!archetypeFile.is_open(), "Unable to open archetype file %s", archetypeFilePath);

    auto &object = m_objectList[objectHandle];
    Json::Value serializedObject;
    Json::StyledStreamWriter file;
    char componentTypeBuffer[sizeof(char) + 1];

    serializedObject["Name"] = object.m_name;

    int numComponentTypes = m_componentDefinitions.GetSize();
    for (int i = 0; i < numComponentTypes; ++i)
    {
      auto &definition = m_componentDefinitions[i];
      int numComponents = definition.m_numComponentsFunction(definition.m_data, objectHandle);
      if (numComponents > 0)
      {
        int32 *handles = (int32 *)alloca(sizeof(int32) * numComponents);
        definition.m_getComponentsFunction(definition.m_data, objectHandle, handles);

        for (int i = 0; i < numComponents; ++i)
        {
          _ComponentTypeToString(definition.m_type, componentTypeBuffer);
          Json::Value &serializedComponent = serializedObject[componentTypeBuffer];
          definition.m_serializeFunction(definition.m_data, handles[i], serializedComponent);
        }
      }
    }

    file.write(archetypeFile, serializedObject);

  }

  void ObjectManager::CompileObject(char const *name)
  {

    char archetypeFilePath[128] = "Archetypes/";
    std::strcat(archetypeFilePath, name);
    std::strcat(archetypeFilePath, ".json");

    std::ifstream archetypeFile(archetypeFilePath);

    ERROR_IF(!archetypeFile.is_open(), "Unable to open archetype file %s", archetypeFilePath);

    Json::Reader archetypeReader;
    Json::Value readArchetype;
    dataStructures::Array<componentSpace::ComponentData> componentDataArray;

    archetypeReader.parse(archetypeFile,readArchetype,false);

    for (auto iter = readArchetype.begin(); iter != readArchetype.end(); ++iter)
    {
      auto *definition = _GetComponentDefinition(_StringToComponentType(iter.memberName()));

      if (!definition)
        continue;

      componentSpace::ComponentData componentData = definition->m_compileFunction(*iter);
      componentData.type = definition->m_type;

      componentDataArray.PushBack(componentData);
    }

    // Compute the byte size of the object
    ArchetypeObjectHeader objectHeader;

    // Name length
    char const *objectName = readArchetype["Name"].asCString();
    objectHeader.nameLength = std::strlen(objectName);

    // Number of components
    objectHeader.numComponents = componentDataArray.GetSize();

    // Tally up the header

    // Size of the header
    objectHeader.byteLength += sizeof(objectHeader);

    // Size of the name
    objectHeader.byteLength += objectHeader.nameLength;

    dataStructures::Array<ArchetypeComponentHeader> componentHeaders(componentDataArray.GetSize());
    for (unsigned i = 0; i < componentDataArray.GetSize(); ++i)
    {
      auto &componentData = componentDataArray[i];
      ArchetypeComponentHeader componentHeader(componentData.size, componentData.type);
      componentHeaders.PushBack(componentHeader);

      // Add length of component header
      objectHeader.byteLength += sizeof(componentHeader);

      // Add length of data
      objectHeader.byteLength += componentHeader.size;
    }

    ObjectArchetype binaryArchetype;

    binaryArchetype.byteSize = objectHeader.byteLength;
    binaryArchetype.data = new char[binaryArchetype.byteSize];

    // Write the object header
    int totalBytesWritten = 0;
    int bytesWritten = sizeof(objectHeader);
    std::memcpy(binaryArchetype.data, &objectHeader, bytesWritten);
    totalBytesWritten += bytesWritten;

    // Write the object name
    bytesWritten = objectHeader.nameLength;
    std::memcpy(&binaryArchetype.data[totalBytesWritten], objectName, bytesWritten);
    totalBytesWritten += bytesWritten;

    // Write each component
    for (unsigned i = 0; i < componentHeaders.GetSize(); ++i)
    {
      auto &componentHeader = componentHeaders[i];
      auto &componentData = componentDataArray[i];

      // Write the component header
      bytesWritten = sizeof(componentHeader);
      std::memcpy(&binaryArchetype.data[totalBytesWritten], &componentHeader, bytesWritten);
      totalBytesWritten += bytesWritten;

      // Write the component data
      bytesWritten = componentHeader.size;
      std::memcpy(&binaryArchetype.data[totalBytesWritten], componentData.data, bytesWritten);
      totalBytesWritten += bytesWritten;
    }

    // Free the component data
    for (unsigned i = 0; i < componentDataArray.GetSize(); ++i)
    {
      free(componentDataArray[i].data);
    }

    ERROR_IF(totalBytesWritten != objectHeader.byteLength, "Detected size mismatch in compilation");

    char compiledArchetypeFilePath[128] = "CompiledArchetypes/";
    std::strcat(compiledArchetypeFilePath, name);
    std::strcat(compiledArchetypeFilePath, ".carch");

    std::ofstream compiledArchetypeFile(compiledArchetypeFilePath,std::ios_base::out | std::ios_base::trunc | std::ios_base::binary);

    ERROR_IF(!compiledArchetypeFile.is_open(), "Unable to open archetype file %s", compiledArchetypeFilePath);

    compiledArchetypeFile.write(binaryArchetype.data, binaryArchetype.byteSize);

  }

  // Returns the number of objects alive in the OM
  int32 ObjectManager::GetNumObjects(void)
  {
    return m_objectList.GetSize();
  }

  // Returns the handle for the root object (Game)
  hndl ObjectManager::GetRootHandle(void)
  {
    return m_root;
  }

  // Returns the handle for the level object
  hndl ObjectManager::GetLevelHandle(void)
  {
    return m_level;
  }

  // Return the handle for the enemy space
  hndl ObjectManager::GetEnemyHandle(void)
  {
    return m_enemy;
  }

  ObjectManager::ComponentDefinition *ObjectManager::_GetComponentDefinition(componentSpace::Component_Type_ type)
  {

    for (int i = 0; i < m_componentDefinitions.GetCapacity(); ++i)
    {
      if (!m_componentDefinitions.IsAlive(i))
        continue;

      if (type == m_componentDefinitions[i].m_type)
      {
        return &m_componentDefinitions[i];
      }
    }

    return NULL;

  }

  ////////////////////////////////////////////////////////////////////////// PRIVATE

  void ObjectManager::_ComponentTypeToString(componentSpace::Component_Type_ type, char *string) const
  {
    string[0] = type;
    string[1] = NULL;
  }

  componentSpace::Component_Type_ ObjectManager::_StringToComponentType(char const *string) const
  {
    return (componentSpace::Component_Type_)string[0];
  }

  void CompileObject(hndl objectHandle, char const *name);

  // Frees an object and its children from memory
  void ObjectManager::FreeObject(hndl objectHandle)
  {
    // Temporary check for double freeing objects [DEBUG]
    if (m_objectList.IsAlive(objectHandle))
    {
      // Destroy all components
      for (auto& it = scriptSpace::LuaDataManager::GetLuaDataMap().begin(); it != scriptSpace::LuaDataManager::GetLuaDataMap().end(); ++it)
      {
        if (it->second.m_componentDetacher && it->second.m_componentHandle(objectHandle) != INVALID_HANDLE)
          it->second.m_componentDetacher(objectHandle);
      }

      // Recursively free all descendants
      const std::vector<hndl>& children = m_objectList[objectHandle].GetChildren();

      for (auto& it = children.begin(); it != children.end(); ++it)
        FreeObject(*it);

      // Remove the object from the slot map
      m_objectList.Remove(objectHandle);
    }
    else
    {
      std::cout << m_objectList[objectHandle].m_name << " was almost double freed." << std::endl;
    }
  }

} // namespace objectSpace
