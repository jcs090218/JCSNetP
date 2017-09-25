#ifndef __SOCKETADDRESSFAMILY_H__
/**
 * $File: SocketAddressFamily.h $
 * $Date: 2017-04-16 02:56:47 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __SOCKETADDRESSFAMILY_H__


NS_JCS_BEGIN

/**
 * @enum SocketAddressFamily
 * @brief List of the socket address type.
 */
enum SocketAddressFamily
{
    INET = AF_INET,
    INET6 = AF_INET6,
};

NS_JCS_END

#endif /* __SOCKETADDRESSFAMILY_H__ */
