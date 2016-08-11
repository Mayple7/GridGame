/*!****************************************************************************
\file    DataStructureAlgorithms.h
\author  Seth England (seth.england)
\date    Jul 18, 2015

\brief   Contains an array that defines a power set.
Stops at 5.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#include "CustomTypes.h"

namespace utilities
{
  template<typename T>
  void MergeSortCopy(T *dataToSort, T *workingArray, int startIndex, int endIndex)
  {
    for (int i = startIndex; i < endIndex; ++i)
    {
      dataToSort[i] = workingArray[i];
    }
  }

  template<typename T>
  void MergeSort(T *dataToSort, T *workingArray, int32 numElements)
  {
    MergeSortSplit(dataToSort, workingArray, 0, numElements);
  }

  template<typename T>
  void MergeSortSplit(T *dataToSort, T *workingArray, int startIndex, int endIndex)
  {
    if (endIndex - startIndex < 2)
      return;

    int middle = (startIndex + endIndex) / 2;
    MergeSortSplit(dataToSort, workingArray, startIndex, middle);
    MergeSortSplit(dataToSort, workingArray, middle, endIndex);
    MergeSortMerge(dataToSort, workingArray, startIndex, middle, endIndex);
    MergeSortCopy(dataToSort, workingArray, startIndex, endIndex);
  }

  template<typename T>
  void MergeSortMerge(T *dataToSort, T *workingArray, int startIndex, int middleIndex, int endIndex)
  {
    int index0 = startIndex;
    int index1 = middleIndex;

    for (int i = startIndex; i < endIndex; ++i)
    {
      if (index0 < middleIndex && (index1 >= endIndex || dataToSort[index0] <= dataToSort[index1]))
      {
        workingArray[i] = dataToSort[index0];
        ++index0;
      }
      else
      {
        workingArray[i] = dataToSort[index1];
        ++index1;
      }
    }
  }
}