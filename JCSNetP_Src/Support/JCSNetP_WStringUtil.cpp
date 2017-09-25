/**
 * $File: JCSNetP_WStringUtil.cpp $
 * $Date: 2017-04-19 23:37:05 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../JCSNetP.h"

NS_JCS_BEGIN

#if !_WIN32
extern const wchar_t** __argv;
extern int __argc;

// Window specific
void OutputDebugStringW(const wchar_t* inString)
{
    printf("%s", inString);

}
#endif

// Get the command line's arguments.
std::wstring WGetCommandLineArg(int inIndex)
{
    if (inIndex < __argc)
    {
        return std::wstring(__wargv[inIndex]);
    }

    return std::wstring();
}

// do logger
std::wstring WSprintf(const wchar_t* inFormat, ...)
{
    //not thread safe...
    static wchar_t temp[4096];

    va_list args;
    va_start(args, inFormat);

#if _WIN32
    _vsnwprintf_s(temp, 4096, 4096, inFormat, args);
#else
    _vsnwprintf_s(temp, 4096, inFormat, args);
#endif
    return std::wstring(temp);
}

// do message logger
void LogW(const wchar_t* inFormat, ...)
{
#ifdef JCS_DEBUG
    //not thread safe...
    static wchar_t temp[4096];

    va_list args;
    va_start(args, inFormat);

#if _WIN32
    _vsnwprintf_s(temp, 4096, 4096, inFormat, args);
    
#else
    _vsnwprintf_s(temp, 4096, inFormat, args);
#endif

    OutputDebugStringW(L"LOG: ");
    OutputDebugStringW(temp);
    OutputDebugStringW(L"\n");
#endif
}

// do info logger
void InfoW(const wchar_t* inFormat, ...)
{
#ifdef JCS_DEBUG
    //not thread safe...
    static wchar_t temp[4096];

    va_list args;
    va_start(args, inFormat);

#if _WIN32
    _vsnwprintf_s(temp, 4096, 4096, inFormat, args);

#else
    _vsnwprintf_s(temp, 4096, inFormat, args);
#endif

    OutputDebugStringW(L"INFO: ");
    OutputDebugStringW(temp);
    OutputDebugStringW(L"\n");
#endif
}

// do warnings logger
void WarningsW(const wchar_t* inFormat, ...)
{
#ifdef JCS_DEBUG
    //not thread safe...
    static wchar_t temp[4096];

    va_list args;
    va_start(args, inFormat);

#if _WIN32
    _vsnwprintf_s(temp, 4096, 4096, inFormat, args);
#else
    _vsnwprintf_s(temp, 4096, inFormat, args);
#endif

    OutputDebugStringW(L"WARNINGS: ");
    OutputDebugStringW(temp);
    OutputDebugStringW(L"\n");
#endif
}

// do error logger
void ErrorW(const wchar_t* inFormat, ...)
{
#ifdef JCS_DEBUG

    //not thread safe...
    static wchar_t temp[4096];

    va_list args;
    va_start(args, inFormat);

#if _WIN32
    _vsnwprintf_s(temp, 4096, 4096, inFormat, args);
#else
    _vsnwprintf_s(temp, 4096, inFormat, args);
#endif

    OutputDebugStringW(L"ERROR: ");
    OutputDebugStringW(temp);
    OutputDebugStringW(L"\n");

#endif
}

NS_JCS_END
