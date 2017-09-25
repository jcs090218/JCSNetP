#ifndef __JCSNETP_SOCKETTYPE_H__
/**
 * $File: JCSNetP_SocketType.h $
 * $Date: 2017-04-16 02:03:46 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_SOCKETTYPE_H__


NS_JCS_BEGIN

/**
 * @enum JCSNetP_SocketType
 * @brief List of all the socket type.
 */
enum JCSNetP_SocketType
{
    NONE,
    TCP,
    UDP,
};

NS_JCS_END
typedef JCSNetP::JCSNetP_SocketType JCSNetP_SocketType;

#endif /* __JCSNETP_SOCKETTYPE_H__ */
