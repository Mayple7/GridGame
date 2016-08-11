/*!****************************************************************************
File:         ObjectEntity.h

Description:  Declarations for the object structure itself.

******************************************************************************/

#pragma once

#include "SlotMap.h"
#include "CustomTypes.h"

namespace objectSpace
{
  // The object, the root of all creations (sort of)
  class Object
  {
  public:
    // Default constructor
    Object(std::string const& objectName = "GameObject", std::string const& archetypeName = "Custom");

    // Default destructor
    ~Object();

    // Assignment operator
    Object& operator=(const Object& rhs);

    // Gets the parent of this object (Lua only)
    hndl GetParent() const;

    // Sets the parent of this object
    void SetParent(hndl parent);

    // Adds a child to this object's child list
    void AddChild(hndl child);

    // Find first child by the given name (Lua only)
    hndl FindFirstChild(const std::string& name) const;

    // Gathers all the children, easier for the taking
    const std::vector<hndl>& GetChildren() const;

    // Whether or not this object has a descendant with the given handle
    bool HasDescendant(hndl objectHandle) const;

    // Whether or not this object is a certain base archetype
    bool IsA(std::string archetypeName) const;

    // Gets the archetype by name
    std::string GetArchetypeName() const;

    // Gets the archetype by hash
    size_t GetArchetypeHash() const;

    // Sets the archetype name
    void SetArchetypeName(std::string archetypeName);

    // Checks if the item is locked or not
    bool8 IsLocked(void) const;

    // Locks an object so it can't be modified
    void LockObject(void);

    // returns if object is active
    bool8 IsActive() const;

    // set if the object is active
    void SetActive(bool8 active);

    // Name of this object (Mostly for Lua integration)
    std::string m_name;

    // This object's index into the object map
    hndl m_index;

  private:
    bool8 IsAllParentActive() const;
    void SetAllChildrenActive(bool8 active);

    // Parent object, can only have one.
    hndl m_parent;

    // Whether or not this object can be tampered with
    bool8 m_locked;

    // Whether this object is active
    bool8 m_isActive;

    // Child pointer array, children are not always needed (obviously)
    std::vector<hndl> m_children;

    // This object's archetype, will be custom if components are added manually
    std::string m_archetype;
    size_t m_typehash;
  };

} // namespace objectSpace
