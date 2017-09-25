#ifndef __JCSNETP_NAME_H__
/**
 * $File: JCSNetP_Name.h $
 * $Date: 2017-04-09 20:41:56 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_NAME_H__


#include <stdint.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef uint8_t uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef uint64_t uint64;

// sometime if u just want the result 1 or 0,
// u can use this so CPU will keep on stacking with
// 4 bytes and not break the order.
typedef int32 bool32;

typedef float float32;
typedef double float64;

typedef long double ld64;

typedef long long32;
typedef long long long64;
typedef unsigned long ulong32;
typedef unsigned long long ulong64;

typedef signed char sbyte;
typedef unsigned char byte;
typedef unsigned int size_t;

// these types are not standard, only exist in windows
#ifdef WIN32
typedef __int64 int64;
typedef unsigned __int64 uint64;
#endif


#endif /* __JCSNETP_NAME_H__ */
