/*!****************************************************************************
\file    DataEntity.h
\author  Dan Muller (d.muller)
\date    July 30, 2015

\brief	 Data for data component.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include <string>

#include "DynamicEntity.h"

namespace coreSpace
{
  static uint32 dataID = 0;

  class DataEntity : public DynamicEntity
  {
  public:
    uint32 m_name;
    uint32 m_id;

    DataEntity() : m_name(0), m_id(0), DynamicEntity() {}
    DataEntity(DynamicEntity const& dyn) : m_name(0), m_id(0), DynamicEntity(dyn)
    {
    }
    ~DataEntity() {}
  };
}
