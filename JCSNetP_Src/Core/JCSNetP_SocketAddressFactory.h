#ifndef __JCSNETP_SOCKETADDRESSFACTORY_H__
/**
 * $File: JCSNetP_SocketAddressFactory.h $
 * $Date: 2017-04-11 23:40:23 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_SOCKETADDRESSFACTORY_H__


NS_JCS_BEGIN

/**
 * @class JCSNetP_SocketAddressFactory
 * @brief Factory create socket address object.
 */
class JCS_DLL JCSNetP_SocketAddressFactory
{
public:

	/**
	 * @func CreateIPv4FromString
	 * @brief Convert string to IPv4 format.
	 * @param inString : string to convert.
	 */
	static JCSNetP_SocketAddressPtr CreateIPv4FromString(const std::string& inString);
};

NS_JCS_END

#endif /* __JCSNETP_SOCKETADDRESSFACTORY_H__ */
