/*!****************************************************************************
\file    ManagerLocator.h
\author  Dan Muller

\brief   Manager locator to handle all the systems

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

namespace timeSpace{ class TimeManager; }
namespace stringSpace{ class StringManager; }
namespace windowSpace{ class WindowManager; }
namespace inputSpace{ class InputManager; }
namespace debugSpace{ class DebugManager; }
namespace objectSpace{ class ObjectManager; }
namespace graphicsSpace{ class GraphicsManager; }
namespace fileSpace{ class FileManager; }
namespace gizmoSpace{ class GizmoManager; }
namespace dataStructures{ class HeterogeneousAllocator; }
namespace systemSpace{ class SystemManager; }
namespace cameraSpace{ class CameraManager; }
namespace editorSpace{ class Editor; }
namespace physicsSpace{ class PhysicsManager; }

// Quick get macros for managers
#define GET_TIME_MANAGER managerSpace::ManagerLocator::GetTimeManager()
#define GET_STRING_MANAGER managerSpace::ManagerLocator::GetStringManager()
#define GET_WINDOW_MANAGER managerSpace::ManagerLocator::GetWindowManager()
#define GET_OBJECT_MANAGER managerSpace::ManagerLocator::GetObjectManager()
#define GET_DEBUG_MANAGER managerSpace::ManagerLocator::GetDebugManager()
#define GET_INPUT_MANAGER managerSpace::ManagerLocator::GetInputManager()
#define GET_GRAPHICS_MANAGER managerSpace::ManagerLocator::GetGraphicsManager()
#define GET_FILE_MANAGER managerSpace::ManagerLocator::GetFileManager()
#define GET_GIZMO_MANAGER managerSpace::ManagerLocator::GetGizmoManager()
#define GET_MEMORY_MANAGER managerSpace::ManagerLocator::GetMemoryManager()
#define GET_SYSTEM_MANAGER managerSpace::ManagerLocator::GetSystemManager()
#define GET_CAMERA_MANAGER managerSpace::ManagerLocator::GetCameraManager()
#define GET_EDITOR managerSpace::ManagerLocator::GetEditor()
#define GET_PHYSICS_MANAGER managerSpace::ManagerLocator::GetPhysicsManager()

namespace managerSpace
{
  class ManagerLocator
  {
    public:
      // Setters
      static void SetTimeManager(timeSpace::TimeManager *timeManager);
      static void SetStringManager(stringSpace::StringManager *stringManager);
      static void SetWindowManager(windowSpace::WindowManager *windowManager);
      static void SetInputManager(inputSpace::InputManager *inputManager);
      static void SetDebugManager(debugSpace::DebugManager *debugManager);
      static void SetObjectManager(objectSpace::ObjectManager *objectManager);
      static void SetGraphicsManager(graphicsSpace::GraphicsManager *graphicsManager);
      static void SetFileManager(fileSpace::FileManager *fileManager);
      static void SetMemoryManager(dataStructures::HeterogeneousAllocator *memoryManager);
      static void SetSystemManager(systemSpace::SystemManager *systemManager);
      static void SetCameraManager(cameraSpace::CameraManager* cameraManager);
      static void SetPhysicsManager(physicsSpace::PhysicsManager* physicsManager);
      
      // Getters
      static timeSpace::TimeManager* GetTimeManager(void);
      static stringSpace::StringManager* GetStringManager(void);
      static windowSpace::WindowManager* GetWindowManager(void);
      static inputSpace::InputManager* GetInputManager(void);
      static debugSpace::DebugManager* GetDebugManager(void);
      static objectSpace::ObjectManager* GetObjectManager(void);
      static graphicsSpace::GraphicsManager* GetGraphicsManager(void);
      static fileSpace::FileManager* GetFileManager(void);
      static gizmoSpace::GizmoManager* GetGizmoManager(void);
      static dataStructures::HeterogeneousAllocator* GetMemoryManager(void);
      static systemSpace::SystemManager* GetSystemManager(void);
      static cameraSpace::CameraManager* GetCameraManager(void);
      static editorSpace::Editor* GetEditor(void);
      static physicsSpace::PhysicsManager* GetPhysicsManager(void);

  private:
      static timeSpace::TimeManager *m_timeManager;
      static stringSpace::StringManager *m_stringManager;
      static windowSpace::WindowManager *m_windowManager;
      static inputSpace::InputManager *m_inputManager;
      static debugSpace::DebugManager *m_debugManager;
      static objectSpace::ObjectManager *m_objectManager;
      static graphicsSpace::GraphicsManager *m_graphicsManager;
      static fileSpace::FileManager *m_fileManager;
      static gizmoSpace::GizmoManager *m_gizmoManager;
      static dataStructures::HeterogeneousAllocator *m_memoryManager;
      static systemSpace::SystemManager *m_systemManager;
      static cameraSpace::CameraManager *m_cameraManager;
      static editorSpace::Editor *m_editor;
      static physicsSpace::PhysicsManager *m_physicsManager;
  };
} // namespace managers