#ifndef __JCS_VLD_H__
/**
 * $File: JCS_vld.h $
 * $Date: $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2015 by Shen, Jen-Chieh $
 */
#define __JCS_VLD_H__


// User define visual studio plugin "Visual Leak Detector".

#if defined(_JCSVLD) || defined(_JCS_VLD) || \
defined(__JCS_VLD__) || defined (JCS_VLD) || \
defined(_JCS_VLD_) || defined(_JCSVLD_)

#ifdef _DEBUG

//-----------------------------------
#ifdef _WIN32
// Visual Studio Deleaker
#include "../../Libraries/vld/include/vld.h"

//-----------------------------------
#elif _OSX

//-----------------------------------
#else // Cross OS

#endif
//-----------------------------------

#endif // _DEBUG

#endif // _JCSVLD || _JCS_VLD || etc.


#endif // __JCS_VLD_H__

