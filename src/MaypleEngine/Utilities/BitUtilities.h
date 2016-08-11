/*!****************************************************************************
\file    BitUtilities.h
\author  Kurihi Chargualaf (k.chargualaf)
\date    Apr 25, 2015

\brief   Contains some helper bit macro functions

\par 
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/
/*=================================
*         Include Guard
*/
#pragma once

/*=================================
*         Dependencies
*/

/*=================================
*         Macro Functions
*/
#define BIT_FLAG(x) (1 << (x))
#define BIT_COMPARE(x,y) ((x) & (y))
#define BIT_ALIGN(x,y) ( ((x) + ((y) - 1)) & ~((y) - 1))
#define BIT_SET(output, bit) (output | BIT_FLAG(bit))
#define BIT_UNSET(output, bit) (output & ~BIT_FLAG(bit))

#define BIT_FLAG_64(x) (1ULL << static_cast<uint64>(x))
#define BIT_COMPARE_64(x,y) (static_cast<uint64>(x) & static_cast<uint64>(y))
#define BIT_ALIGN_64(x,y) ( ((static_cast<uint64>(x)) + (static_cast<uint64>(y) - 1ULL)) & ~(static_cast<uint64>(y) - 1ULL))
#define BIT_SET_64(output, bit) (output | BIT_FLAG_64(static_cast<uint64>(bit)))
#define BIT_UNSET_64(output, bit) (output & ~BIT_FLAG_64(static_cast<uint64>(bit)))


