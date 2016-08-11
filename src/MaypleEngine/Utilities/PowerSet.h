/*!****************************************************************************
\file    PowerSet.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Jul 18, 2015

\brief   Contains an array that defines a power set. 
         Stops at 5.

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

  namespace powerSet
  {
    const int c_maxPowerSet = 6;
    const int c_powerSetCounts[c_maxPowerSet + 1] =
    {
      1,
      2,
      4,
      8,
      16,
      32,
      64,
    };

    const int c_powerSet[][c_maxPowerSet] =
    {
      { -1, -1, -1, -1, -1, -1, },
      { 0, -1, -1, -1, -1, -1, },
      { 1, -1, -1, -1, -1, -1, },
      { 0, 1, -1, -1, -1, -1, },
      { 2, -1, -1, -1, -1, -1, },
      { 0, 2, -1, -1, -1, -1, },
      { 1, 2, -1, -1, -1, -1, },
      { 0, 1, 2, -1, -1, -1, },
      { 3, -1, -1, -1, -1, -1, },
      { 0, 3, -1, -1, -1, -1, },
      { 1, 3, -1, -1, -1, -1, },
      { 0, 1, 3, -1, -1, -1, },
      { 2, 3, -1, -1, -1, -1, },
      { 0, 2, 3, -1, -1, -1, },
      { 1, 2, 3, -1, -1, -1, },
      { 0, 1, 2, 3, -1, -1, },
      { 4, -1, -1, -1, -1, -1, },
      { 0, 4, -1, -1, -1, -1, },
      { 1, 4, -1, -1, -1, -1, },
      { 0, 1, 4, -1, -1, -1, },
      { 2, 4, -1, -1, -1, -1, },
      { 0, 2, 4, -1, -1, -1, },
      { 1, 2, 4, -1, -1, -1, },
      { 0, 1, 2, 4, -1, -1, },
      { 3, 4, -1, -1, -1, -1, },
      { 0, 3, 4, -1, -1, -1, },
      { 1, 3, 4, -1, -1, -1, },
      { 0, 1, 3, 4, -1, -1, },
      { 2, 3, 4, -1, -1, -1, },
      { 0, 2, 3, 4, -1, -1, },
      { 1, 2, 3, 4, -1, -1, },
      { 0, 1, 2, 3, 4, -1, },
      { 5, -1, -1, -1, -1, -1, },
      { 0, 5, -1, -1, -1, -1, },
      { 1, 5, -1, -1, -1, -1, },
      { 0, 1, 5, -1, -1, -1, },
      { 2, 5, -1, -1, -1, -1, },
      { 0, 2, 5, -1, -1, -1, },
      { 1, 2, 5, -1, -1, -1, },
      { 0, 1, 2, 5, -1, -1, },
      { 3, 5, -1, -1, -1, -1, },
      { 0, 3, 5, -1, -1, -1, },
      { 1, 3, 5, -1, -1, -1, },
      { 0, 1, 3, 5, -1, -1, },
      { 2, 3, 5, -1, -1, -1, },
      { 0, 2, 3, 5, -1, -1, },
      { 1, 2, 3, 5, -1, -1, },
      { 0, 1, 2, 3, 5, -1, },
      { 4, 5, -1, -1, -1, -1, },
      { 0, 4, 5, -1, -1, -1, },
      { 1, 4, 5, -1, -1, -1, },
      { 0, 1, 4, 5, -1, -1, },
      { 2, 4, 5, -1, -1, -1, },
      { 0, 2, 4, 5, -1, -1, },
      { 1, 2, 4, 5, -1, -1, },
      { 0, 1, 2, 4, 5, -1, },
      { 3, 4, 5, -1, -1, -1, },
      { 0, 3, 4, 5, -1, -1, },
      { 1, 3, 4, 5, -1, -1, },
      { 0, 1, 3, 4, 5, -1, },
      { 2, 3, 4, 5, -1, -1, },
      { 0, 2, 3, 4, 5, -1, },
      { 1, 2, 3, 4, 5, -1, },
      { 0, 1, 2, 3, 4, 5, },
    };
  }

  // Used to calculate the power set
  //void printPowerSet(char *set, int set_size)
  //{
  //    /*set_size of power set of a set with set_size
  //      n is (2**n -1)*/
  //    unsigned int pow_set_size = static_cast<unsigned>(pow(2, set_size));
  //    int counter, j;
  // 
  //    /*Run from counter 000..0 to 111..1*/
  //    for(counter = 0; counter < static_cast<int>(pow_set_size); counter++)
  //    {
  //      int printed = 0;
  //      printf("{ ");
  //      for(j = 0; j < set_size; j++)
  //       {
  //          /* Check if jth bit in the counter is set
  //             If set then pront jth element from set */
  //          if(counter & (1<<j))
  //          {
  //            printf("%c, ", set[j]);
  //            ++printed;
  //          }
  //       }

  //       while (printed < set_size)
  //       {
  //         printf("-1, ");
  //         ++printed;
  //       }
  //       
  //       printf("},\n");
  //    }
  //}
  //    char set[] = 
  //    {
  //      '0',
  //      '1',
  //      '2',
  //      '3',
  //      '4',
  //      '5',
  //    };
  //    printPowerSet(set, sizeof(set) / sizeof(set[0]));
}

