/*!****************************************************************************
\file    ObjectEntity.cpp
\author  Kaden Nugent (kaden.n)
\date    Apr 26, 2015

\brief   Implementation for the object structure itself.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"         // Precompiled header
#include "ObjectEntity.h"   // This file's declarations
#include "ManagerLocator.h" // For getting the object manager

namespace objectSpace
{

  ////////////////////////////////////////////////////////////////////////// PUBLIC

  // Default constructor
  Object::Object(std::string const& objectName, std::string const& archetypeName)
    : m_name(objectName), m_locked(false), m_parent(-1), m_archetype(archetypeName), m_typehash(HASH_GEN(archetypeName))
    , m_isActive(true)
  {}

  // Default destructor
  Object::~Object()
  {}

  // Assignment operator
  Object& Object::operator=(const Object& rhs)
  {
    m_name      = rhs.m_name;
    m_index     = rhs.m_index;
    m_locked    = rhs.m_locked;
    m_parent    = rhs.m_parent;
    m_children  = rhs.m_children;
    m_archetype = rhs.m_archetype;
    m_typehash  = rhs.m_typehash;
    m_isActive  = rhs.m_isActive;

    return *this;
  }

  // Gets the parent of this object
  hndl Object::GetParent() const
  {
    return m_parent;
  }

  // Sets the parent of this object
  void Object::SetParent(hndl parent)
  {
    ObjectManager* manager = GET_OBJECT_MANAGER;

    // Remove child from old parent (if there is an old parent)
    if (m_parent > -1)
    {
      objectSpace::Object &oldParentObject = manager->GetObject(m_parent);
      oldParentObject.m_children.erase(std::remove(oldParentObject.m_children.begin(), oldParentObject.m_children.end(), m_index), oldParentObject.m_children.end());
    }

    // Make sure the new parent is not a descendant
    if (parent > -1)
    {
      objectSpace::Object &parentObject = manager->GetObject(parent);

      if (HasDescendant(parent))
      {
        // A child cannot be the parent of its parent
        printf("Error: \"%s\" is a child of \"%s\"\n", parentObject.m_name.c_str(), m_name.c_str());
        return;
      }
      else if (m_parent > 0 && manager->GetObject(m_index).IsLocked())
      {
        // If the object is locked, don't allow changing the parent, unless the parent doesn't exist
        printf("Error: \"%s\" is a locked object\n", m_name.c_str());
        return;
      }
      
      // Add the child
      parentObject.AddChild(m_index);
    }

    // Set the new parent
    m_parent = parent;
  }

  // Adds a child to this object's child list
  void Object::AddChild(hndl child)
  {
    m_children.push_back(child);
  }

  // Find first child by the given name
  hndl Object::FindFirstChild(const std::string& name) const
  {
    ObjectManager* manager = GET_OBJECT_MANAGER;

    for (auto &it : m_children)
    {
      if (manager->GetObject(it).m_name == name)
        return it;
    }

    return -1;
  }

  // Gathers all the children, easier for the taking
  const std::vector<hndl>& Object::GetChildren() const
{
    return m_children;
  }

  // Whether or not this object has a descendant with the given handle
  bool Object::HasDescendant(hndl objectHandle) const
  {
    ObjectManager* manager = GET_OBJECT_MANAGER;

    for (auto it = m_children.begin(); it != m_children.end(); ++it)
    {
      if(manager->GetObject(*it).m_index == objectHandle)
        return true;
      else
      {
        if(manager->GetObject(*it).HasDescendant(objectHandle) == true)
        {
          return true;
        }
      }
    }

    return false;
  }

  // Whether or not this object is a certain base archetype
  bool Object::IsA(std::string archetypeName) const
  {
    return m_archetype == archetypeName;
  }

  // Gets the archetype by name
  std::string Object::GetArchetypeName() const
  {
    return m_archetype;
  }

  // Gets the archetype by hash
  size_t Object::GetArchetypeHash() const
  {
    return m_typehash;
  }

  // Sets the archetype name
  void Object::SetArchetypeName(std::string archetypeName)
  {
    m_archetype = archetypeName;
  }

  // Checks if the item is locked or not
  bool8 Object::IsLocked(void) const
  {
    return m_locked;
  }

  // Locks an object so it can't be modified
  void Object::LockObject(void)
  {
    m_locked = true;
  }

  bool8 Object::IsActive() const
  {
    return m_isActive;
  }

  void Object::SetActive(bool8 active)
  {
    if(active == true && IsAllParentActive() == false)
    {
      WARN_IF(false, "Not all parents are active, cannot set current object to active.");
      return;
    }

    m_isActive = active;
    SetAllChildrenActive(active);
  }

  bool8 Object::IsAllParentActive() const
  {
    hndl parentHndl = GetParent();

    while(parentHndl != INVALID_HANDLE)
    {
      if (parentHndl == m_index)
      {
        WARN_IF(true, "Parent and child share the same handle: %i", parentHndl);
        return false;
      }

      auto & parent = GET_OBJECT_MANAGER->GetObject(parentHndl);

      if(parent.IsActive() == false)
      {
        return false;
      }

      parentHndl = parent.GetParent();
    }

    return true;
  }

  void Object::SetAllChildrenActive(bool8 active)
  {
    auto& childrenCont = GetChildren();
    for(hndl child : childrenCont)
    {
      GET_OBJECT_MANAGER->GetObject(child).m_isActive = active;
      GET_OBJECT_MANAGER->GetObject(child).SetAllChildrenActive(active);
    }
  }

} // namespace objectSpace
