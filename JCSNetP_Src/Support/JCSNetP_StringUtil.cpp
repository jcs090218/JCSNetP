/**
 * $File: JCSNetP_StringUtil.cpp $
 * $Date: 2017-04-11 22:16:47 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../JCSNetP.h"

NS_JCS_BEGIN

#if !_WIN32
extern const char** __argv;
extern int __argc;

// Window specific
void OutputDebugStringA(const char* inString)
{
    printf("%s", inString);

}
#endif

// Get the command line's arguments.
std::string GetCommandLineArg(int inIndex)
{
    if( inIndex < __argc )
    {
        return std::string( __argv[ inIndex ] );
    }

    return std::string();
}

// do logger
std::string Sprintf(const char* inFormat, ...)
{
    //not thread safe...
    static char temp[ 4096 ];

    va_list args;
    va_start(args, inFormat);

#if _WIN32
    _vsnprintf_s(temp, 4096, 4096, inFormat, args);
#else
    vsnprintf(temp, 4096, inFormat, args);
#endif
    return std::string(temp);
}

// do message logger
void Log(const char* inFormat, ...)
{
#ifdef JCS_DEBUG
    //not thread safe...
    static char temp[4096];

    va_list args;
    va_start(args, inFormat);

#if _WIN32
    _vsnprintf_s(temp, 4096, 4096, inFormat, args);
#else
    vsnprintf(temp, 4096, inFormat, args);
#endif

    OutputDebugStringA("LOG: ");
    OutputDebugStringA(temp);
    OutputDebugStringA("\n");
#endif
}

// do info logger
void Info(const char* inFormat, ...)
{
#ifdef JCS_DEBUG
    //not thread safe...
    static char temp[4096];

    va_list args;
    va_start(args, inFormat);

#if _WIN32
    _vsnprintf_s(temp, 4096, 4096, inFormat, args);
#else
    vsnprintf(temp, 4096, inFormat, args);
#endif

    OutputDebugStringA("INFO: ");
    OutputDebugStringA(temp);
    OutputDebugStringA("\n");
#endif
}

// do warnings logger
void Warnings(const char* inFormat, ...)
{
#ifdef JCS_DEBUG
    //not thread safe...
    static char temp[4096];

    va_list args;
    va_start(args, inFormat);

#if _WIN32
    _vsnprintf_s(temp, 4096, 4096, inFormat, args);
#else
    vsnprintf(temp, 4096, inFormat, args);
#endif

    OutputDebugStringA("WARNINGS: ");
    OutputDebugStringA(temp);
    OutputDebugStringA("\n");
#endif
}

// do error logger
void Error(const char* inFormat, ...)
{
#ifdef JCS_DEBUG

    //not thread safe...
    static char temp[4096];

    va_list args;
    va_start(args, inFormat);

#if _WIN32
    _vsnprintf_s(temp, 4096, 4096, inFormat, args);
#else
    vsnprintf(temp, 4096, inFormat, args);
#endif

    OutputDebugStringA("ERROR: ");
    OutputDebugStringA(temp);
    OutputDebugStringA("\n");

#endif
}

NS_JCS_END
