#ifndef __JCSNETP_WSTRINGUTIL_H__
/**
 * $File: JCSNetP_WStringUtil.h $
 * $Date: 2017-04-19 23:37:02 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_WSTRINGUTIL_H__

NS_JCS_BEGIN

/**
 * @func WGetCommandLineArg
 * @beif Get the command line's arguments.
 * @param inIndex : argument vector index.
 * @return std::string : arugment result.
 */
std::wstring WGetCommandLineArg(int inIndex);

/**
 * @func WSprintf
 * @brief Print out the char in format.
 * @param inFormat : format string.
 * @param ... : arguments' data.
 * @return std::string : formated and added data string.
 */
std::wstring WSprintf(const wchar_t* inFormat, ...);

/**
 * @func LogW
 * @brief do message logger
 * @param inFormat : format string.
 * @param ... : arguments' data.
 */
void LogW(const wchar_t* inFormat, ...);

/**
 * @func InfoW
 * @brief do message logger
 * @param inFormat : format string.
 * @param ... : arguments' data.
 */
void InfoW(const wchar_t* inFormat, ...);

/**
 * @func WarningsW
 * @brief do warnings logger
 * @param inFormat : format string.
 * @param ... : arguments' data.
 */
void WarningsW(const wchar_t* inFormat, ...);

/**
 * @func ErrorW
 * @brief do error logger
 * @param inFormat : format string.
 * @param ... : arguments' data.
 */
void ErrorW(const wchar_t* inFormat, ...);


/**
 * @def JCS_LOG_W
 * @brief Rewrap message logger.
 * @param ... : arguments' data.
 */
#define JCS_LOG_W(...) LogW(__VA_ARGS__);
/**
 * @def JCS_INFO_W
 * @brief Rewrap info logger.
 * @param ... : arguments' data.
 */
#define JCS_INFO_W(...) InfoW(__VA_ARGS__);
/**
 * @def JCS_WARNINGS_W
 * @brief Rewrap warnings logger.
 * @param ... : arguments' data.
 */
#define JCS_WARNINGS_W(...) WarningsW(__VA_ARGS__);
/**
 * @def JCS_ERROR_W
 * @brief Rewrap error logger.
 * @param ... : arguments' data.
 */
#define JCS_ERROR_W(...) ErrorW(__VA_ARGS__);

NS_JCS_END

#endif /* __JCSNETP_WSTRINGUTIL_H__ */
