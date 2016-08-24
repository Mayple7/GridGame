/*!****************************************************************************
\file    StackAllocator.h
\author  Seth England (seth.england)
\date    Apr 15, 2015

\brief   Slot map data structure.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#include "DebugManager.h"
#define EXPANSION_FACTOR 2

namespace memorySpace
{
  class StackAllocator
  {
  public:
    StackAllocator(int stackByteSize = 4, char *stack = NULL);

    template<typename T>
    int Allocate(T **ppType);

    int Allocate(int byteSize);

    template<typename T>
    T* Get(int offset);

    void Expand(int newByteSize);

    void Clear(void);

  private:
    void _Allocate(char **newMemory, int newByteSize);
    void _Free(void);
    void _CheckExpansion(int deltaByteOffset);
    void _MoveOffsetTo16ByteBoundary(void);

    int m_maxByteOffset;
    int m_currentByteOffset;
    char *m_stack;
    std::mutex m_allocationLock;
  };

  template<typename T>
  int StackAllocator::Allocate(T **ppType)
  {
    int offset = Allocate(sizeof(T));
    *ppType = (T *)m_stack[m_currentByteOffset];

    return offset;
  }

  template<typename T>
  inline T* StackAllocator::Get(int offset)
  {
    //ERROR_IF(offset > m_currentByteOffset, "Offset %i out of bounds", offset);

    ERROR_IF(offset % SIMD_ALIGNMENT != 0, "Misaligned data/n");
    return (T *)&m_stack[offset];
  }
}