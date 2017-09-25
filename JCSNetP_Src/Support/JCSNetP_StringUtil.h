#ifndef __JCSNETP_STRINGUTIL_H__
/**
 * $File: JCSNetP_StringUtil.h $
 * $Date: 2017-04-11 22:13:27 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_STRINGUTIL_H__


NS_JCS_BEGIN

/**
 * @func GetCommandLineArg
 * @beif Get the command line's arguments.
 * @param inIndex : argument vector index.
 * @return std::string : arugment result.
 */
std::string GetCommandLineArg(int inIndex);

/**
 * @func Sprintf
 * @brief Print out the char in format.
 * @param inFormat : format string.
 * @param ... : arguments' data.
 * @return std::string : formated and added data string.
 */
std::string Sprintf(const char* inFormat, ...);

/**
 * @func Log
 * @brief do message logger
 * @param inFormat : format string.
 * @param ... : arguments' data.
 */
void Log(const char* inFormat, ...);

/**
 * @func Info
 * @brief do info logger
 * @param inFormat : format string.
 * @param ... : arguments' data.
 */
void Info(const char* inFormat, ...);

/**
 * @func Warnings
 * @brief do warnings logger
 * @param inFormat : format string.
 * @param ... : arguments' data.
 */
void Warnings(const char* inFormat, ...);

/**
 * @func Error
 * @brief do error logger
 * @param inFormat : format string.
 * @param ... : arguments' data.
 */
void Error(const char* inFormat, ...);


/**
 * @def JCS_LOG
 * @brief Rewrap message logger.
 * @param ... : arguments' data.
 */
#define JCS_LOG(...) Log(__VA_ARGS__);
/**
 * @def JCS_INFO
 * @brief Rewrap info logger.
 * @param ... : arguments' data.
 */
#define JCS_INFO(...) Info(__VA_ARGS__);
/**
 * @def JCS_WARNINGS
 * @brief Rewrap warnings logger.
 * @param ... : arguments' data.
 */
#define JCS_WARNINGS(...) Warnings(__VA_ARGS__);
/**
 * @def JCS_ERROR
 * @brief Rewrap error logger.
 * @param ... : arguments' data.
 */
#define JCS_ERROR(...) Error(__VA_ARGS__);

NS_JCS_END

#endif /* __JCSNETP_STRINGUTIL_H__ */
