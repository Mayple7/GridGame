/*!****************************************************************************
\file    HeterogeneousAllocator.h
\author  Seth England (seth.england)
\date    Apr 15, 2015

\brief   Slot map data structure.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
#pragma once

#include "CustomTypes.h"
#include "StackAllocator.h"

#define MEMORY_MANAGER_CAPACITY 700000000
#define LOG_2_MAX_BLOCK_SIZE 31
#define MAX_BLOCK_SIZE 2147483648 // 2^31
#define MAX_ALLOCATION_SIZE 65000000

#define LOCK_GAURD_MUTEX(mutexToLock) std::lock_guard<std::mutex> lock(mutexToLock)

namespace memorySpace
{
  extern char g_allocatorMemory[MEMORY_MANAGER_CAPACITY];

  class MemoryManager
  {
  public:
    MemoryManager(int32 initialCapacity);

    void* Allocate(int32 allocationSize);

    void Delete(void *memory);

    struct MemoryStats
    {
    private:
      unsigned long m_initialCapacity;
      unsigned long m_bytesAllocated;
      unsigned long m_bytesFree;

    public:
      friend class MemoryManager;
      int32 GetCapacity(void) const { return m_initialCapacity; }
      int32 GetBytesAllocated(void) const { return m_bytesAllocated; }
      int32 GetBytesFree(void) const { return m_bytesFree; }
    };
    MemoryStats const& GetStats(void) const;

  private:
#pragma pack(push, 1)
    struct MemoryBlockHeader
    {
      MemoryBlockHeader *m_next = NULL;
      int32 m_allocated;
      int32 m_logPow2;
      int32 m_padding;
    };
#pragma pack(pop)

    struct Pow2Result
    {
      int32 m_pow2;
      int32 m_logPow2;
    };
    Pow2Result _CalculatePow2(int32 size);

    // Free list functions
    int32 _AllocateNewFreeList(void);
    void _InitializeNewFreeList(int32 pow2, int32 freeList);
    MemoryBlockHeader* _PullBlock(int32 freeListHandle);
    void _AddBlock(int32 freeListHandle, MemoryBlockHeader *memory);

    // Memory block functions
    int32 _AllocateMemoryBlock(int32 pow2);
    void _InitializeMemoryBlock(int32 block, int32 memoryHandle);

    // Memory stats functions
    void _RecordAllocation(MemoryBlockHeader *memory);
    void _RecordFree(MemoryBlockHeader *memory);

    // Oversized allocation / dellocation functions
    void* _AllocateOversized(int32 byteSize);
    void _FreeOversized(void *memory);

    StackAllocator m_underlyingMemory;

    std::mutex m_masterLock;

    MemoryBlockHeader* m_freeListHeads[LOG_2_MAX_BLOCK_SIZE + 1];

    MemoryStats m_stats;
  };

  extern MemoryManager g_memoryManagerSingleton;
}