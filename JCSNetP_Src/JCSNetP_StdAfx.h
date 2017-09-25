#ifndef __JCSNETP_STDAFX_H__
/**
 * $File: JCSNetP_StdAfx.h $
 * $Date: 2017-04-09 20:48:08 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_STDAFX_H__


// Leak Detector
#ifdef _WIN32
#define _JCS_VLD
#else

#endif

// Namespace define
#ifdef __cplusplus
#define NS_JCS_BEGIN namespace JCSNetP {
#define NS_JCS_END   }
#define USING_NS_JCS using namespace JCSNetP
#define NS_JCS       ::JCSNetP
#else
#define NS_JCS_BEGIN
#define              NS_JCS_END
#define USING_NS_JCS
#define              NS_JCS
#endif

// Debug/Release
#ifdef _DEBUG
#define JCS_DEBUG
#define _JCS_DEBUG
#else
#define JCS_RELEASE
#define _JCS_RELEASE
#endif

// Assert
#if JCS_DISABLE_ASSERT > 0
#define JCS_ASSERT(cond)
#else
#define JCS_ASSERT(cond) assert(cond)
#endif
#define JCS_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/**
 * NOTE(jenchieh): comment this out if importing dll
 * We are exporting to dll file.
 */
#define EXPORTS_DLL

/**
 * Defines import/export dynamic link library.
 */
#ifndef EXPORTS_DLL
/****************** Import ********************/
#if defined (_MSC_VER)
// Microsoft
#define DECLSPEC_ACTION __declspec(dllimport)
#define JCS_DLL __declspec(dllimport)
#elif defined (__GNUC__)
// GCC
#define DECLSPEC_ACTION __attribute__((visibility(dllimport)))
#define JCS_DLL __attribute__((visibility(dllimport)))
#else
// Default
#define DECLSPEC_ACTION
#define JCS_DLL
#endif
#else
/****************** Export ********************/
#if defined (_MSC_VER)
// Microsoft
#define DECLSPEC_ACTION __declspec(dllexport)
#define JCS_DLL __declspec(dllexport)
#elif defined (__GNUC__)
// GCC
#define DECLSPEC_ACTION __attribute__((visibility(dllexport)))
#define JCS_DLL __attribute__((visibility(dllexport)))
#else
// Default
#define DECLSPEC_ACTION
#define JCS_DLL
#endif
#endif


// prevent redefined
#undef EXTERN_C_BEGIN
#undef EXTERN_C_END

// c plus plus define?
#ifdef __cplusplus
#define EXTERN_C_BEGIN extern "C" {
#define EXTERN_C_END }
#else
#define EXTERN_C_BEGIN
#define EXTERN_C_END
#endif


// define static use.
/**
 * @def PUBLIC
 * @brief Use of global function declaration. (public)
 */
#define PUBLIC 
/**
 * @def PRIATE
 * @brief Use of global function declaration. (private)
 */
#define PRIVATE static

/**
 * @def JCS_TRUE
 * @brief If we have the integer value represent true or false, we can 
 * use this represent true.
 */
#define JCS_TRUE  1
/**
 * @def JCS_FALSE
 * @brief If we have the integer value represent true or false, we can
 * use this represent false.
 */
#define JCS_FALSE 0

/**
 * Ignore compiler warnings.
 */
#if _WIN32
/**
 * @def _WINSOCK_DEPRECATED_NO_WARNINGS
 * @brief Ignore function 'inet_addr' warngins.
 */
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#define JCS_NO_ERROR 0
#define JCS_HAS_ERROR -1

// Predefined.
#include "Support/JCS_vld.h"
#include "Support/JCSNetP_Defines.h"
#include "Support/JCSNetP_Name.h"
#include "Support/JCSNetP_SafePointer.h"
#include "Core/JCSNetP_Constants.h"

// Libraries


////// LINKER ////////////////
#ifdef _WIN32
#pragma comment(lib, "Ws2_32.lib")
#else

#endif

#endif /* __JCSNETP_STDAFX_H__ */
