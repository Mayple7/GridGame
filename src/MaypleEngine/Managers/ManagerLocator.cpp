/*!****************************************************************************
\file    ManagerLocator.cpp
\author  Dan Muller

\brief   Manager locator to handle all the systems

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"
#include "ManagerLocator.h"

namespace managerSpace
{

  ////////////////////////////////////////////////////////////////////////// SETTERS
  void ManagerLocator::SetTimeManager(timeSpace::TimeManager *timeManager)
  {
    m_timeManager = timeManager;
  }

  void ManagerLocator::SetStringManager(stringSpace::StringManager *stringManager)
  {
    m_stringManager = stringManager;
  }

  void ManagerLocator::SetWindowManager(windowSpace::WindowManager *windowManager)
  {
    m_windowManager = windowManager;
  }

  void ManagerLocator::SetInputManager(inputSpace::InputManager *inputManager)
  {
    m_inputManager = inputManager;
  }

  void ManagerLocator::SetObjectManager(objectSpace::ObjectManager *objectManager)
  {
    m_objectManager = objectManager;
  }

  void ManagerLocator::SetGraphicsManager(graphicsSpace::GraphicsManager *graphicsManager)
  {
    m_graphicsManager = graphicsManager;
  }

  void ManagerLocator::SetFileManager(fileSpace::FileManager *fileManager)
  {
    m_fileManager = fileManager;
  }

  void ManagerLocator::SetMemoryManager(dataStructures::HeterogeneousAllocator *memoryManager)
  {
    m_memoryManager = memoryManager;
  }

  void ManagerLocator::SetSystemManager(systemSpace::SystemManager *systemManager)
  {
    m_systemManager = systemManager;
  }

  void ManagerLocator::SetCameraManager(cameraSpace::CameraManager* cameraManager)
  {
    m_cameraManager = cameraManager;
  }

  void ManagerLocator::SetPhysicsManager(physicsSpace::PhysicsManager* physicsManager)
  {
    m_physicsManager = physicsManager;
  }

  ////////////////////////////////////////////////////////////////////////// GETTERS

  timeSpace::TimeManager* ManagerLocator::GetTimeManager(void)
  {
    return m_timeManager;
  }

  stringSpace::StringManager* ManagerLocator::GetStringManager(void)
  {
    return m_stringManager;
  }

  windowSpace::WindowManager* ManagerLocator::GetWindowManager(void)
  {
    return m_windowManager;
  }

  inputSpace::InputManager* ManagerLocator::GetInputManager(void)
  {
    return m_inputManager;
  }

  debugSpace::DebugManager* ManagerLocator::GetDebugManager(void)
  {
    return m_debugManager;
  }

  objectSpace::ObjectManager* ManagerLocator::GetObjectManager(void)
  {
    return m_objectManager;
  }

  graphicsSpace::GraphicsManager* ManagerLocator::GetGraphicsManager(void)
  {
    return m_graphicsManager;
  }

  fileSpace::FileManager* ManagerLocator::GetFileManager(void)
  {
    return m_fileManager;
  }

  systemSpace::SystemManager* ManagerLocator::GetSystemManager(void)
  {
    return m_systemManager;
  }

  cameraSpace::CameraManager* ManagerLocator::GetCameraManager(void)
  {
    return m_cameraManager;
  }

  physicsSpace::PhysicsManager* ManagerLocator::GetPhysicsManager(void)
  {
    return m_physicsManager;
  }

  ////////////////////////////////////////////////////////////////////////// PREDECLARATIONS
  timeSpace::TimeManager *ManagerLocator::m_timeManager = nullptr;
  stringSpace::StringManager *ManagerLocator::m_stringManager = nullptr;
  windowSpace::WindowManager *ManagerLocator::m_windowManager = nullptr;
  inputSpace::InputManager *ManagerLocator::m_inputManager = nullptr;
  debugSpace::DebugManager *ManagerLocator::m_debugManager = nullptr;
  objectSpace::ObjectManager *ManagerLocator::m_objectManager = nullptr;
  graphicsSpace::GraphicsManager *ManagerLocator::m_graphicsManager = nullptr;
  fileSpace::FileManager *ManagerLocator::m_fileManager = nullptr;
  dataStructures::HeterogeneousAllocator *ManagerLocator::m_memoryManager = nullptr;
  systemSpace::SystemManager *ManagerLocator::m_systemManager = nullptr;
  cameraSpace::CameraManager *ManagerLocator::m_cameraManager = nullptr;
  physicsSpace::PhysicsManager *ManagerLocator::m_physicsManager = nullptr;
}