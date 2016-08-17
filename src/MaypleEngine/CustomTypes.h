/*!****************************************************************************
\file    CustomTypes.h
\author  Kaden Nugent (kaden.n)
\date    Apr 5, 2015

\brief   General type declarations for the Diesel Engine.

\par
<b> Copyright (C) 2015-2016 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited. </b>
******************************************************************************/

#pragma once

#define VECTOR_CALL    __vectorcall
#define RESTRICT       __declspec(restrict)
#define SIMD_ALIGNMENT 16
#define ALIGN_SIMD     __declspec(align(SIMD_ALIGNMENT))

typedef INT8       int8;   // | 8 bits|  Range:                 -128 -> 127
typedef INT16     int16;   // |16 bits|  Range:               -32768 -> 32767
typedef INT32     int32;   // |32 bits|  Range:          -2147483648 -> 2147483647
typedef INT64     int64;   // |64 bits|  Range: -9223372036854775808 -> 9223372036854775807
typedef UINT8     uint8;   // | 8 bits|  Range:                    0 -> 255
typedef UINT16   uint16;   // |16 bits|  Range:                    0 -> 65535
typedef UINT32   uint32;   // |32 bits|  Range:                    0 -> 4294967295
typedef UINT64   uint64;   // |64 bits|  Range:                    0 -> 18446744073709551615
typedef CHAR      char8;   // | 8 bits|  Range:                 -128 -> 127
typedef WCHAR    char16;   // |16 bits|  Range:               -32768 -> 32767
typedef UCHAR    uchar8;   // | 8 bits|  Range:                    0 -> 255
typedef time_t   time64;   // |32 bits|  Range:                    0 -> 4294967295
typedef bool      bool8;   // | 8 bits|  Range:                false -> true
typedef FLOAT       f32;   // |32 bits|  
typedef double      f64;   // |64 bits|
typedef uchar8     byte;   // | 8 bits|

// typedef __m128 VectorType; // |128 bits|
// typedef __m128i IVectorType; // For Integers
// 
// typedef 
// struct ALIGN_SIMD
// {
//   __m128 rows[4];
//   operator VectorType();
// } MatrixType;              // |512 bits|


typedef int32 hndl; // A handle, used as an index
#define INVALID_HANDLE -1

