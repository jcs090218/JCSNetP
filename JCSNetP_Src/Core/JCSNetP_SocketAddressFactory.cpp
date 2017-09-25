/**
 * $File: JCSNetP_SocketAddressFactory.cpp $
 * $Date: 2017-04-11 23:40:38 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../JCSNetP.h"


NS_JCS_BEGIN

// Convert string to IPv4 format.
JCSNetP_SocketAddressPtr JCSNetP_SocketAddressFactory::CreateIPv4FromString(const std::string& inString)
{
	auto pos = inString.find_last_of(':');
	std::string host, service;
	if (pos != std::string::npos)
	{
		host = inString.substr(0, pos);
		service = inString.substr(pos + 1);
	}
	else
	{
		host = inString;
		//use default port...
		service = "0";
	}
	addrinfo hint;
	memset(&hint, 0, sizeof(hint));
	hint.ai_family = AF_INET;

	addrinfo* result;
	int error = getaddrinfo(host.c_str(), service.c_str(), &hint, &result);
	if (error != 0 && result != nullptr)
	{
		JCSNetP_SocketUtil::ReportError("SocketAddressFactory::CreateIPv4FromString");
		return nullptr;
	}

	while (!result->ai_addr && result->ai_next)
	{
		result = result->ai_next;
	}

	if (!result->ai_addr)
	{
		return nullptr;
	}

	auto toRet = std::make_shared<JCSNetP_SocketAddress>(*result->ai_addr);

	freeaddrinfo(result);

	return toRet;

}

NS_JCS_END
