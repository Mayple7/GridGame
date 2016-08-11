/*!****************************************************************************
\file    SlotMapSpecializations.hpp
\author  Seth England (seth.england)
\date    Apr 15, 2015

\brief   Slot map data structure.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"

#include "SlotMap.h"

namespace dataStructures
{
  template<>
  SlotMap<VectorType>::SlotMap(int initialCapacity, int alignment, bool constructItems, bool destroyItems) :
    m_array(nullptr),
    m_capacity(0),
    m_size(0),
    m_alignment(SIMD_ALIGNMENT),
    m_constructItems(constructItems),
    m_destroyItems(destroyItems),
    m_freeList(nullptr),
    m_freeListBack(-1),
    m_alive(nullptr)
  {

    CONSTRUCT_SLOT_MAP;

  }

  template<>
  SlotMap<MatrixType>::SlotMap(int initialCapacity, int alignment, bool constructItems, bool destroyItems):
    m_array(nullptr),
    m_capacity(0),
    m_size(0),
    m_alignment(SIMD_ALIGNMENT),
    m_constructItems(constructItems),
    m_destroyItems(destroyItems),
    m_freeList(nullptr),
    m_freeListBack(-1),
    m_alive(nullptr)
  {

    CONSTRUCT_SLOT_MAP;

  }

  template<>
  SlotMap<std::string>::SlotMap(int initialCapacity, int alignment, bool constructItems, bool destroyItems) :
    m_array(nullptr),
    m_capacity(0),
    m_size(0),
    m_alignment(-1),
    m_constructItems(true),
    m_destroyItems(true),
    m_freeList(nullptr),
    m_freeListBack(-1),
    m_alive(nullptr)
  {

    CONSTRUCT_SLOT_MAP;

  }
}