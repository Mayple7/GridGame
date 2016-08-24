/*!****************************************************************************
\file    HeterogeneousAllocator.cpp
\author  Seth England (seth.england)
\date    Apr 15, 2015

\brief   Slot map data structure.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#include "stdinc.h"
#include "MemoryManager.h"
#include "DebugManager.h"

namespace memorySpace
{
  MemoryManager::MemoryManager(int32 initialCapacity) :
    m_underlyingMemory(initialCapacity, g_allocatorMemory)
  {
    m_stats.m_initialCapacity = initialCapacity;
    m_stats.m_bytesFree = initialCapacity;
    m_stats.m_bytesAllocated = 0;

    for (int i = 0; i < LOG_2_MAX_BLOCK_SIZE + 1; ++i)
    {
      m_freeListHeads[i] = NULL;
    }
  }

  void* MemoryManager::Allocate(int32 allocationSize)
  {
    LOCK_GAURD_MUTEX(m_masterLock);

    if (allocationSize >= MAX_ALLOCATION_SIZE)
    {
      int sizePlusHeader = allocationSize + sizeof(MemoryBlockHeader);
      MemoryBlockHeader *bigAssAlloc = (MemoryBlockHeader *)VirtualAlloc(NULL, sizePlusHeader, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

      ERROR_IF(!bigAssAlloc, "BigAssAlloc of size %i failed", sizePlusHeader);

      bigAssAlloc->m_padding = MAX_ALLOCATION_SIZE;

      void *userMemory = (void*)((char*)bigAssAlloc + sizeof(MemoryBlockHeader));

      return userMemory;
    }

    allocationSize += sizeof(MemoryBlockHeader);
    Pow2Result pow2 = _CalculatePow2(allocationSize);

    if (pow2.m_pow2 < allocationSize)
    {
      pow2.m_pow2 *= 2;
      pow2.m_logPow2++;
    }

    int32 freeListIter = pow2.m_logPow2;
    MemoryBlockHeader *freeList = m_freeListHeads[freeListIter];

    bool freeListEmpty = false;
    
    if (!freeList)
    {
      freeListEmpty = true;
    }
    
    MemoryBlockHeader *memory = NULL;

    // List of size does not exist
    if (freeListEmpty)
    {    
      int32 newMemoryHandle = m_underlyingMemory.Allocate(pow2.m_pow2);

      // Initialize memory
      memory = m_underlyingMemory.Get<MemoryBlockHeader>(newMemoryHandle);
      memory->m_logPow2 = pow2.m_logPow2;
      memory->m_next = NULL; 
    }
    else
    {
      MemoryBlockHeader *freeMemoryBlock = _PullBlock(freeListIter);

      if(freeMemoryBlock->m_logPow2 != pow2.m_logPow2)
        std::cout << "Memory block not correct power of 2: " << freeMemoryBlock->m_logPow2 << std::endl;

      if(freeMemoryBlock->m_allocated)
        std::cout << "Memory block is allocated" << std::endl;

      // Initialize memory
      memory = freeMemoryBlock;
      memory->m_logPow2 = pow2.m_logPow2;
      memory->m_next = NULL;
    }

    _RecordAllocation(memory);

    int sizeOfHeader = sizeof(MemoryBlockHeader);
    void *userMemory = (void*)((char*)memory + sizeof(MemoryBlockHeader));

    return userMemory;
  }

  void MemoryManager::Delete(void *memory)
  {
    LOCK_GAURD_MUTEX(m_masterLock);
    MemoryBlockHeader *header = (MemoryBlockHeader *)((char *)memory - sizeof(MemoryBlockHeader));

    if (header->m_padding == MAX_ALLOCATION_SIZE)
    {
      VirtualFree(header, NULL, MEM_RELEASE);
      return;
    }
    
    ERROR_IF(!header->m_allocated, "Memory block is not allocated \n");

    int32 freeListHandle = header->m_logPow2;

    _AddBlock(freeListHandle, header);
    
    _RecordFree(header);
  }

  MemoryManager::MemoryStats const& MemoryManager::GetStats(void) const
  {
    return m_stats;
  }

  MemoryManager::Pow2Result MemoryManager::_CalculatePow2(int32 size)
  {
    Pow2Result result;
    result.m_logPow2 = (int32)std::ceil(std::log2((double)size));
    result.m_pow2 = (int32)std::pow(2, (double)result.m_logPow2);

    if (result.m_pow2 < size)
    {
      result.m_logPow2++;
      result.m_pow2 *= 2;
    }

    return result;
  }

  MemoryManager::MemoryBlockHeader* MemoryManager::_PullBlock(int32 freeListHandle)
  {
    MemoryManager::MemoryBlockHeader *freeBlock = m_freeListHeads[freeListHandle];

    MemoryManager::MemoryBlockHeader *next = freeBlock->m_next;

    m_freeListHeads[freeListHandle] = next;

    ERROR_IF(!freeBlock, "Invalid memory block handle \n");

    return freeBlock;
  }

  void MemoryManager::_AddBlock(int32 freeListHandle, MemoryBlockHeader *memory)
  {
    MemoryBlockHeader *oldFreeHead = m_freeListHeads[freeListHandle];

    m_freeListHeads[freeListHandle] = memory;
    memory->m_next = oldFreeHead;
  }
  
  void MemoryManager::_RecordAllocation(MemoryBlockHeader *memory)
  {
    int32 byteSize = (int32)std::powf(2, (f32)memory->m_logPow2);
    memory->m_allocated = true;
    m_stats.m_bytesAllocated += byteSize;
    m_stats.m_bytesFree -= byteSize;
  }

  void MemoryManager::_RecordFree(MemoryBlockHeader *memory)
  {
    int32 byteSize = (int32)std::powf(2, (f32)memory->m_logPow2);
    memory->m_allocated = false;
    m_stats.m_bytesAllocated -= byteSize;
    m_stats.m_bytesFree += byteSize;
  }

  // Oversized allocation / dellocation functions
  void* MemoryManager::_AllocateOversized(int32 byteSize)
  {
    return NULL;
  }

  void MemoryManager::_FreeOversized(void *memory)
  {

  }

  char g_allocatorMemory[MEMORY_MANAGER_CAPACITY];
  MemoryManager g_memoryManagerSingleton(MEMORY_MANAGER_CAPACITY);
}