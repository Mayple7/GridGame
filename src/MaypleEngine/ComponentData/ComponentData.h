/*!****************************************************************************
\file    ComponentData.h
\author  Seth England (seth.england)
\date    Apr 28, 2015

\brief	 Common stuff for components.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#define INVALID_HANDLE -1
#define COMPONENT_NAME_MAX_LENGTH 64

namespace componentSpace
{
#define ADD_NAME( name ) \
      name,

  enum Component_Type_
  {
#include "ComponentTypes.h"
  };

  struct ComponentData
  {
    int size;
    char *data;
    Component_Type_ type;

    ComponentData(int size_ = 0, char *data_ = NULL, Component_Type_ type_ = Component_Type_::Undefined_) :
      size(size_),
      data(data_),
      type(type_){}
  };

  typedef void(*AddToObject)(void *componentData, int32 objectHandle, int32 componentHandle);
  typedef void (*SerializeComponent)(void *componentData, int32 componentHandle, Json::Value &value);
  typedef ComponentData (*CompileComponent)(Json::Value const &value);
  typedef int32 (*DeserializeComponent)(void *componentData, ComponentData *compiledComponent);
  typedef int32 (*GetNumComponents)(void *componentData, int32 objectHandle);
  typedef void(*GetComponents)(void *componentData, int32 objectHandle, int32 *componentHandles);

} // namespace componentSpace