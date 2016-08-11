/*!****************************************************************************
\file    RecycleQueue.hpp
\author  Kurihi Chargualaf (k.chargualaf)
\date    May 04, 2015

\brief   Basically wrapper around a vector to retrieve the front of the 
         vector and move to the next. It is like a queue that doesn't
         delete it contents.

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         Dependencies
*/

/*=================================
*      Forward Declarations
*/

/*=================================
*      Namespace Umbrella
*/
namespace utilities
{

  /*=================================
  *      Class Public Functions
  */
  template <typename DataType>
  RecycleQueue<DataType>::RecycleQueue(std::vector<DataType> &data)
  : m_data(data)
  , m_currentIndex(0)
  {
  }

  template <typename DataType>
  RecycleQueue<DataType>::~RecycleQueue()
  {
  }

  template <typename DataType>
  unsigned RecycleQueue<DataType>::GetCurrentIndex() const
  {
    return m_currentIndex;
  }

  template <typename DataType>
  DataType *RecycleQueue<DataType>::PopFront()
  {
    if (m_currentIndex >= m_data.size())
    {
      return nullptr;
    }

    return &m_data[m_currentIndex++];
  }

  template <typename DataType>
  void RecycleQueue<DataType>::Reset()
  {
    m_currentIndex = 0;
  }

  /*=================================
  *     Class Protected Functions
  */


  /*=================================
  *     Class Private Functions
  */

}

