/*!****************************************************************************
\file    StackAllocator.cpp
\author  Seth England (seth.england)
\date    Apr 15, 2015

\brief   Slot map data structure.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "stdinc.h"
#include "StackAllocator.h"
#include "CustomTypes.h"

namespace memorySpace
{
  StackAllocator::StackAllocator(int stackByteSize, char *stack):
    m_maxByteOffset(stackByteSize),
    m_currentByteOffset(0),
    m_stack(stack)
  {
    if (!stack)
    {
      _Allocate(&m_stack, stackByteSize);
    }

    _MoveOffsetTo16ByteBoundary();
    m_stack = &m_stack[m_currentByteOffset];
    m_currentByteOffset = 0;
  }

  void StackAllocator::_Allocate(char **newMemory, int newStackByteSize)
  {
    *newMemory = (char *)_aligned_malloc(newStackByteSize, SIMD_ALIGNMENT);
  }

  void StackAllocator::_Free(void)
  {
    if (m_stack)
    {
      _aligned_free(m_stack);
    }
  }

  void StackAllocator::_CheckExpansion(int deltaByteOffset)
  {
    int newByteOffset = m_currentByteOffset + deltaByteOffset;

    if (newByteOffset > m_maxByteOffset)
    {
      ERROR_IF(true, "Out of memory");
      Expand(EXPANSION_FACTOR * newByteOffset);
    }
  }

  void StackAllocator::_MoveOffsetTo16ByteBoundary(void)
  {
    int32 deltaOffset = (unsigned long)(&m_stack[m_currentByteOffset]) % SIMD_ALIGNMENT;

    if (!deltaOffset)
      return;

    _CheckExpansion(m_currentByteOffset + deltaOffset);

    m_currentByteOffset += (SIMD_ALIGNMENT - deltaOffset);
  }

  int StackAllocator::Allocate(int byteSize)
  {
    std::lock_guard<std::mutex> lock(m_allocationLock);
    _CheckExpansion(byteSize);

    int offset = m_currentByteOffset;
    m_currentByteOffset += byteSize;

    _MoveOffsetTo16ByteBoundary();

    return offset;
  }

  void StackAllocator::Expand(int newByteSize)
  {
    WARN_IF(true, "Stack allocator expansion.\n");

    char *newStack;
    _Allocate(&newStack, newByteSize);

    std::memcpy(newStack, m_stack, m_currentByteOffset);
    m_maxByteOffset = newByteSize;

    _Free();

    m_stack = newStack;
  }

  void StackAllocator::Clear(void)
  {
    m_currentByteOffset = 0;
  }
}