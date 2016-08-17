/*!****************************************************************************
\file    SlotMap.h
\author  Seth England (seth.england)
\date    Apr 15, 2015

\brief   Slot map data structure.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#ifdef _DEBUG
#define BOUNDS_CHECK
#endif

// namespace coreSpace
// {
//   class DataEntity;
// }

#include "CustomTypes.h"
#include "DebugManager.h"
#include "ManagerLocator.h"

namespace dataStructures
{
  template<typename T>
  class SlotMap
  {
  public:
    class const_iterator;

    class iterator
    {
    public:
      iterator(int idx, SlotMap<T>* container) : m_container(container), m_idx(idx) { }
      operator const_iterator() { return const_iterator(m_idx, m_container); }

      T& operator* () { return m_container->operator[](m_idx); };
      const T& operator* () const { return m_container->operator[](m_idx); }

      iterator& operator= (const iterator& rhs) { m_container = rhs.m_container; m_idx = rhs.m_idx; return *this; }

      bool operator== (const iterator& rhs) const { return (m_idx >= m_container->GetCapacity() || m_idx < 0) || m_idx == rhs.m_idx; }
      bool operator!= (const iterator& rhs) const { return !operator==(rhs); }

      iterator& operator++ ()
      {
        int newIdx = m_idx + 1;
        while(newIdx < m_container->GetCapacity() && m_container->IsAlive(newIdx) == false)
        {
          ++newIdx;
        }

        m_idx = (newIdx >= m_container->GetCapacity()) ? -1 : newIdx;
        return *this;
      }

      iterator& operator-- ()
      {
        int newIdx = m_idx - 1;
        while(newIdx >= 0 && m_container->IsAlive(newIdx) == false)
        {
          --newIdx;
        }

        m_idx = newIdx;
        return *this;
      }

      iterator operator++ (int)
      {
        iterator newIt = *this;
        return ++newIt;
      }

      iterator operator-- (int)
      {
        iterator newIt = *this;
        return --newIt;
      }

    private:
      SlotMap<T>* m_container = nullptr;
      int m_idx = -1;
    };

    class const_iterator
    {
    public:
      const_iterator(int idx, const SlotMap<T>* container) : m_container(container), m_idx(idx) { }

      const T& operator* () const { return m_container->operator[](m_idx); }

      const_iterator& operator= (const const_iterator& rhs) { m_container = rhs.m_container; m_idx = rhs.m_idx; return *this; }

      bool operator== (const const_iterator& rhs) const { return (m_idx >= m_container->GetCapacity() || m_idx < 0) || m_idx == rhs.m_idx; }
      bool operator!= (const const_iterator& rhs) const { return !operator==(rhs); }

      const_iterator& operator++ ()
      {
        int newIdx = m_idx + 1;
        while(newIdx < m_container->GetCapacity() && m_container->IsAlive(newIdx) == false)
        {
          ++newIdx;
        }

        m_idx = (newIdx >= m_container->GetCapacity()) ? -1 : newIdx;
        return *this;
      }

      const_iterator& operator-- ()
      {
        int newIdx = m_idx - 1;
        while(newIdx >= 0 && m_container->IsAlive(newIdx) == false)
        {
          --newIdx;
        }

        m_idx = newIdx;
        return *this;
      }

      const_iterator operator++ (int)
      {
        iterator newIt = *this;
        return ++newIt;
      }

      const_iterator operator-- (int)
      {
        iterator newIt = *this;
        return --newIt;
      }

    private:
      const SlotMap<T>* m_container = nullptr;
      int m_idx = -1;
    };

  public:
    SlotMap(int initialCapacity = 10, int alignment = -1, bool constructItems = false, bool destroyItems = false);
    SlotMap(SlotMap<T> const &rhs);
    ~SlotMap(void);

    T& operator[](int index);
    T const& operator[](int index) const;

    T GetByValue(int index) const;

    // Do not use this unless your using it not as an allocator
    void SetAlive(int index, bool alive);

    bool IsAlive(int index) const;

    int Insert(T const &item);

    int AllocateSlot(void);
    void AllocateBlock(int *handles, int size);

    void Remove(int index);
    void Clear(void);

    int GetCapacity(void) const;
    int GetSize(void) const;

    int const* GetFreeList(void) const;
    int GetFreeListLength(void) const;

    SlotMap<T>& operator=(SlotMap<T> const &rhs);
	bool operator==( SlotMap<T> const &rhs ) const;

    void Expand(int newCapacity);

    T const* GetFirstElementConst(void) const;

    int GetFirstAliveElement(void) const;

    void Serialize(std::ostream *output) const;
    void Deserialize(std::istream *input);

	iterator begin();
	iterator end();

	const_iterator cbegin() const;
	const_iterator cend() const;

	iterator insert( const_iterator position, const T& val );

  private:
    int _GetFreeSlot(void);
    void _Allocate(unsigned number,
      T **newLocation,
      int **newFreeList,
      bool **newAlive);
    void _Free(void);
    void _Construct(void);

    T *m_array;

    int m_capacity;
    int m_size;
    int m_alignment;
    bool m_constructItems;
    bool m_destroyItems;

    int *m_freeList;
    int m_freeListBack;

    bool *m_alive;
  };

#define CONSTRUCT_SLOT_MAP \
  _Allocate(initialCapacity, &m_array, &m_freeList, &m_alive); \
  m_capacity = initialCapacity; \
  \
  for (int i = 0; i < m_capacity; ++i) \
  { \
    m_freeList[i] = m_capacity - 1 - i; \
  } \
  m_freeListBack = m_capacity - 1; \

  template<typename T>
  SlotMap<T>::SlotMap(int initialCapacity, int alignment, bool constructItems, bool destroyItems) :
    m_array(nullptr),
    m_capacity(0),
    m_size(0),
    m_alignment(alignment),
    m_constructItems(constructItems),
    m_destroyItems(destroyItems),
    m_freeList(nullptr),
    m_freeListBack(-1),
    m_alive(nullptr)
  {
    CONSTRUCT_SLOT_MAP;
  }
  template<>
  SlotMap<VectorType>::SlotMap(int initialCapacity, int alignment, bool constructItems, bool destroyItems);

  template<>
  SlotMap<MatrixType>::SlotMap(int initialCapacity, int alignment, bool constructItems, bool destroyItems);

  template<>
  SlotMap<std::string>::SlotMap(int initialCapacity, int alignment, bool constructItems, bool destroyItems);

  template<typename T>
  SlotMap<T>::SlotMap(SlotMap<T> const &rhs):
    m_alignment(rhs.m_alignment),
    m_constructItems(rhs.m_constructItems),
    m_destroyItems(rhs.m_destroyItems)
  {
    unsigned rhsCapacity = rhs.GetCapacity();

    T *newArray;
    bool *newAlive;
    int *newFreeList;

    _Allocate(rhsCapacity, &newArray, &newFreeList, &newAlive);

    for (unsigned i = 0; i < rhsCapacity; ++i)
    {
      newArray[i] = rhs[i];
      newAlive[i] = rhs.m_alive[i];
      newFreeList[i] = rhs.m_freeList[i];
    }

    m_size = rhs.GetSize();
    m_capacity = rhsCapacity;

    m_array = newArray;
    m_alive = newAlive;
    m_freeList = newFreeList;
    m_freeListBack = rhs.m_freeListBack;
  }

  template<typename T>
  SlotMap<T>::~SlotMap(void)
  {
    _Free();
  }

  template<typename T>
  T& SlotMap<T>::operator[](int index)
  {
#ifdef BOUNDS_CHECK
    ERROR_IF(index >= m_capacity, "Array index %i is out of bounds, capacity is %i", index, m_capacity);
    ERROR_IF(index < 0, "Array index %i is less than zero", index);
#endif

    return m_array[index];
  }

  template<typename T>
  T const& SlotMap<T>::operator[](int index) const
  {
#ifdef BOUNDS_CHECK
    ERROR_IF(index >= m_capacity, "Array index %i is out of bounds, capacity is %i", index, m_capacity);
    ERROR_IF(index < 0, "Array index %i is less than zero", index);
#endif

    return m_array[index];
  }

  template<typename T>
  T SlotMap<T>::GetByValue(int index) const
  {
#ifdef BOUNDS_CHECK
    ERROR_IF(index >= m_capacity, "Array index %i is out of bounds, capacity is %i", index, m_capacity);
    ERROR_IF(index < 0, "Array index %i is less than zero", index);
#endif

    return m_array[index];
  }

  template<typename T>
  void SlotMap<T>::SetAlive(int index, bool alive)
  {
#ifdef BOUNDS_CHECK
    ERROR_IF(index >= m_capacity, "Array index %i is out of bounds, capacity is %i", index, m_capacity);
    ERROR_IF(index < 0, "Array index %i is less than zero", index);
#endif

    m_alive[index] = alive;
  }

  template<typename T>
  bool SlotMap<T>::IsAlive(int index) const
  {

    if (index >= m_capacity || index < 0)
      return false;

    return m_alive[index];

  }

#define ALLOCATE_SLOT \
    m_alive[freeIndex] = true; \
    m_freeList[m_freeListBack] = -1; \
    --m_freeListBack; \
    ++m_size; \

  template<typename T>
  int SlotMap<T>::Insert(T const &item)
  {
    
    int freeIndex = _GetFreeSlot();

    m_array[freeIndex] = item;

    ALLOCATE_SLOT;

    return freeIndex;

  }

  template<typename T>
  int SlotMap<T>::AllocateSlot(void)
  {

    int freeIndex = _GetFreeSlot();

    ALLOCATE_SLOT;


    if (m_constructItems)
    {
      new (&m_array[freeIndex]) T();
    }

    return freeIndex;

  }

#undef ALLOCATE_SLOT

  template<typename T>
  void SlotMap<T>::AllocateBlock(int *handles, int size)
  {

    for (int i = 0; i < size; ++i)
    {
      handles[i] = AllocateSlot();
    }

  }

  template<typename T>
  void SlotMap<T>::Remove(int index)
  {

#ifdef BOUNDS_CHECK
    ERROR_IF(index >= m_capacity, "Array index %i is out of bounds, capacity is %i", index, m_capacity);
    ERROR_IF(index < 0, "Array index %i is less than zero", index);
#endif

    if (m_destroyItems)
    {
      m_array[index].~T();
    }
    m_alive[index] = false;
    --m_size;
#ifdef BOUNDS_CHECK
    for (int i = 0; i < m_capacity; ++i)
    {
      ERROR_IF(m_freeList[i] == index, "Element is already on free list");
    }
#endif
    ++m_freeListBack;
    m_freeList[m_freeListBack] = index;

  }

  template<typename T>
  void SlotMap<T>::Clear(void)
  {

    for (int i = m_capacity - 1; i >= 0; --i)
    {
      if (IsAlive(i))
      {
        Remove(i);
      }
    }

  }

  template<typename T>
  int SlotMap<T>::GetCapacity(void) const
  {
    return m_capacity;
  }

  template<typename T>
  int SlotMap<T>::GetSize(void) const
  {
    return m_size;
  }

  template<typename T>
  int const* SlotMap<T>::GetFreeList(void) const
  {
    return m_freeList;
  }

  template<typename T>
  int SlotMap<T>::GetFreeListLength(void) const
  {
    return m_freeListBack + 1;
  }

  template<typename T>
  SlotMap<T>& SlotMap<T>::operator=(SlotMap<T> const &rhs)
  {
    int32 rhsCapacity = rhs.GetCapacity();
    bool allocateNewMemory = true;//(m_capacity < rhsCapacity || m_constructItems != rhs.m_constructItems); //Free list back bug

    m_alignment = rhs.m_alignment;
    m_constructItems = rhs.m_constructItems;
    m_destroyItems = rhs.m_destroyItems;

    T *newArray;
    bool *newAlive;
    int *newFreeList;

    if (allocateNewMemory)
    {
      _Allocate(rhsCapacity, &newArray, &newFreeList, &newAlive);
    }
    else
    {
      newArray = m_array;
      newAlive = m_alive;
      newFreeList = m_freeList;
    }

    for (int32 i = 0; i < rhsCapacity; ++i)
    {
      newArray[i] = rhs[i];
      newAlive[i] = rhs.m_alive[i];
      newFreeList[i] = rhs.m_freeList[i];
    }

    m_size = rhs.GetSize();
    m_freeListBack = rhs.m_freeListBack;

    if (allocateNewMemory)
    {
      _Free();
      m_capacity = rhsCapacity;
    }

    m_array = newArray;
    m_alive = newAlive;
    m_freeList = newFreeList;

    return *this;
  }

  template <typename T>
  bool SlotMap<T>::operator== ( SlotMap<T> const & rhs ) const
  {
	  if ( m_size != rhs.m_size )
	  {
		  return false;
	  }

	  auto first = cbegin();
	  auto last = cend();
	  auto rhsFirst = rhs.cbegin();

	  while ( first != last )
	  {
		  if ( *first != *rhsFirst )
		  {
			  return false;
		  }

		  ++first;
		  ++rhsFirst;
	  }

	  return true;
  }

  template<typename T>
  int SlotMap<T>::_GetFreeSlot(void)
  {

    int backFreeList = m_freeListBack;

    if (backFreeList < 0)
    {
      ERROR_IF(backFreeList < -1, "%s", "Overflow detected, too many elements inserted without an expansion");

      Expand(2 * m_capacity);
    }

    backFreeList = m_freeListBack;

    return m_freeList[backFreeList];

  }

  template<typename T>
  void SlotMap<T>::_Allocate(unsigned number, 
                             T **newLocation, 
                             int **newFreeList, 
                             bool **newAlive)
  {
    //Allocate the array
    //if (m_alignment > -1)
    //{
    //  *newLocation = (T*)_aligned_malloc(sizeof(T) * number, m_alignment);
    //}
    //else
    //{
    //  *newLocation = (T*)malloc(sizeof(T) * number);
    //}
    *newLocation = (T * )GET_MEMORY_MANAGER->Allocate(sizeof(T) * number);

    // Allocate new free list
    //*newFreeList = (int *)malloc(sizeof(int) * number);
    *newFreeList = (int *)GET_MEMORY_MANAGER->Allocate(sizeof(int) * number);
    
    // Allocate alive array
    //*newAlive = (bool *)calloc(number, sizeof(bool));
    int newAliveByteSize = sizeof(bool) * number;
    *newAlive = (bool *)GET_MEMORY_MANAGER->Allocate(newAliveByteSize);
    std::memset(*newAlive, NULL, newAliveByteSize);

    if (m_constructItems)
    {
      for (unsigned i = 0; i < number; ++i)
      {
        new (&(*newLocation)[i]) T();
      }
    }

  }

  template<typename T>
  void SlotMap<T>::_Free(void)
  {
    if (m_destroyItems)
    {
      for (int i = 0; i < m_capacity; ++i)
      {
        m_array[i].~T();
      }
    }

    //if (m_alignment > -1)
    //{
    //  _aligned_free(m_array);
    //}
    //else
    //{
    //  free(m_array);
    //}
    GET_MEMORY_MANAGER->Delete(m_array);

    //free(m_alive);
    GET_MEMORY_MANAGER->Delete(m_alive);

    //free(m_freeList);
    GET_MEMORY_MANAGER->Delete(m_freeList);
  }

  template<typename T>
  void SlotMap<T>::Expand(int capacity)
  {
    if (capacity < m_capacity)
      return;

    T *newArray;
    bool *newAlive;
    int *newFreeList;
    int newCapacity = capacity;

    _Allocate(newCapacity, &newArray, &newFreeList, &newAlive);

    // Copy array data
    for (int i = 0; i < m_capacity; ++i)
    {
      newArray[i] = m_array[i];
      newAlive[i] = m_alive[i];
    }

    // Add new elements to free list
    int numNewElements = newCapacity - m_capacity;
    int i = 0;
    for (; i < numNewElements; ++i)
    {
      newFreeList[i] = (m_capacity + numNewElements - 1) - i;
    }
    m_freeListBack = numNewElements - 1;

    // Set the rest of the free list to not free
    for (; i < newCapacity; ++i)
    {
      newFreeList[i] = -1;
    }

    _Free();

    m_capacity = newCapacity;
    m_array = newArray;
    m_alive = newAlive;
    m_freeList = newFreeList;
  }

  template<typename T>
  T const* SlotMap<T>::GetFirstElementConst(void) const
  {
    return m_array;
  }

  template<typename T>
  int SlotMap<T>::GetFirstAliveElement(void) const
  {

    int aliveIndex = -1;
    for (int i = 0; i < m_capacity; ++i)
    {
      if (IsAlive(i))
      {
        aliveIndex = i;
        break;
      }
    }

    return aliveIndex;

  }

  template<typename T>
  void SlotMap<T>::Serialize(std::ostream *output) const
  {
    output->write((char *)&m_capacity, sizeof(m_capacity));
    output->write((char *)&m_size, sizeof(m_size));
    output->write((char *)&m_alignment, sizeof(m_alignment));
    output->write((char *)&m_constructItems, sizeof(m_constructItems));
    output->write((char *)&m_destroyItems, sizeof(m_destroyItems));
    output->write((char *)&m_freeListBack, sizeof(m_freeListBack));

    // Serialize array
    output->write((char *)m_array, m_capacity * sizeof(T));

    // Serialize alive array
    output->write((char *)m_alive, m_capacity * sizeof(*m_alive));

    // Serialize free list
    output->write((char *)m_freeList, m_capacity * sizeof(*m_freeList));
  }

  template<typename T>
  void SlotMap<T>::Deserialize(std::istream *input)
  {
    int32 newCapacity;
    int32 newSize;
    int32 newAlignment;
    bool newConstructItems;
    bool newDestroyItems;
    int32 newFreeListBack;
    T *newArray;
    bool *newAlive;
    int32 *newFreeList;
    
    input->read((char *)&newCapacity, sizeof(newCapacity));
    input->read((char *)&newSize, sizeof(newSize));
    input->read((char *)&newAlignment, sizeof(newAlignment));
    input->read((char *)&newConstructItems, sizeof(newConstructItems));
    input->read((char *)&newDestroyItems, sizeof(newDestroyItems));
    input->read((char *)&newFreeListBack, sizeof(newFreeListBack));

    _Free();

    m_alignment = newAlignment;
    m_constructItems = newConstructItems;
    m_destroyItems = newDestroyItems;
    _Allocate(newCapacity, &newArray, &newFreeList, &newAlive);

    m_capacity = newCapacity;
    m_size = newSize;
    m_freeListBack = newFreeListBack;

    m_array = newArray;
    m_alive = newAlive;
    m_freeList = newFreeList;

    input->read((char *)m_array, sizeof(T) * newCapacity);
    input->read((char *)m_alive, sizeof(*m_alive) * newCapacity);
    input->read((char *)m_freeList, sizeof(*m_freeList) * newCapacity);

  }

  template <typename T>
  typename SlotMap<T>::iterator SlotMap<T>::begin()
  {
	  return ++SlotMap<T>::iterator( -1, this );
  }

  template <typename T>
  typename SlotMap<T>::iterator SlotMap<T>::end()
  {
	  return SlotMap<T>::iterator( GetCapacity(), this );
  }

  template <typename T>
  typename SlotMap<T>::const_iterator SlotMap<T>::cbegin() const
  {
	  return ++SlotMap<T>::const_iterator( -1, this );
  }
  
  template <typename T>
  typename SlotMap<T>::const_iterator SlotMap<T>::cend() const
  {
	  return SlotMap<T>::const_iterator( GetCapacity(), this );
  }

} // namespace dataStructures
