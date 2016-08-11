/*!****************************************************************************
\file    RecycleQueue.h
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
*         include guard
*/
#pragma once

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
  *         Classes
  */
  template <typename DataType>
  class RecycleQueue
  {
    /*=================================
    *         Type Definitions
    */
  public:
    /*=================================
    *         Class Variables
    */
  protected:
    std::vector<DataType> &m_data;
    unsigned m_currentIndex;


    /*=================================
    *      Class Public Functions
    */
  public:
    RecycleQueue(std::vector<DataType> &data);
    virtual ~RecycleQueue();

    unsigned GetCurrentIndex() const;
    DataType *PopFront();
    void Reset();

    


  protected:
    /*=================================
    *     Class Protected Functions
    */
    
  private:
    /*=================================
    *     Class Private Functions
    */
    
  };
}

#include "RecycleQueue.hpp"

