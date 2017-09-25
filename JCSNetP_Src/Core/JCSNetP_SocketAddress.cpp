/**
 * $File: JCSNetP_SocketAddress.cpp $
 * $Date: 2017-04-09 23:40:01 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../JCSNetP.h"

EXTERN_C_BEGIN
NS_JCS_BEGIN

JCSNetP_SocketAddress::JCSNetP_SocketAddress()
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetIP4Ref() = INADDR_ANY;
    GetAsSockAddrIn()->sin_port = 0;
}

JCSNetP_SocketAddress::JCSNetP_SocketAddress(
    const sockaddr& inSockAddr)
{
    memcpy(&m_sockAddr, &inSockAddr, sizeof(sockaddr));
}

JCSNetP_SocketAddress::JCSNetP_SocketAddress(uint16 inPort)
    : m_port(inPort)
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetIP4Ref() = htonl(INADDR_ANY);
    GetAsSockAddrIn()->sin_port = htons(inPort);
}

JCSNetP_SocketAddress::JCSNetP_SocketAddress(
    const char* inAddress,
    uint16 inPort)
    : m_port(inPort)
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetIP4Ref() = htonl(INADDR_ANY);
    GetAsSockAddrIn()->sin_port = htons(inPort);
    GetAsSockAddrIn()->sin_addr.s_addr = inet_addr(inAddress);
}

JCSNetP_SocketAddress::JCSNetP_SocketAddress(
    uint32 inAddress,
    uint16 inPort)
{
    GetAsSockAddrIn()->sin_family = AF_INET;
    GetIP4Ref() = htonl(inAddress);
    GetAsSockAddrIn()->sin_port = htons(inPort);
}

JCSNetP_SocketAddress::~JCSNetP_SocketAddress()
{

}

// operator ==
bool JCSNetP_SocketAddress::operator==(const JCSNetP_SocketAddress& inOther) const
{
    return (m_sockAddr.sa_family == AF_INET &&
        GetAsSockAddrIn()->sin_port == inOther.GetAsSockAddrIn()->sin_port) &&
        (GetIP4Ref() == inOther.GetIP4Ref());
}

// Hash of the object.
size_t JCSNetP_SocketAddress::GetHash() const
{
    return (GetIP4Ref()) |
        ((static_cast<uint32>(GetAsSockAddrIn()->sin_port)) << 13) |
        m_sockAddr.sa_family;
}

// get the size of the object.
uint32 JCSNetP_SocketAddress::GetSize() const
{
    return sizeof(sockaddr);
}

// Convert object to string.
std::string JCSNetP_SocketAddress::ToString() const
{
#if _WIN32
    const sockaddr_in* s = GetAsSockAddrIn();
    char destinationBuffer[128];

    InetNtopA(
		s->sin_family, 
		const_cast<in_addr*>(&s->sin_addr), 
		destinationBuffer, 
		sizeof(destinationBuffer));

    return Sprintf("%s:%d", destinationBuffer, ntohs(s->sin_port));
#else
    //not implement on mac for now...
    return string( "not implemented on mac for now" );
#endif
}

#if _WIN32
// Get the IP version 4 references.
uint32& JCSNetP_SocketAddress::GetIP4Ref()
{
    return *reinterpret_cast<uint32*>(&GetAsSockAddrIn()->sin_addr.S_un.S_addr);
}

// Function overloading for constant getter.
const uint32& JCSNetP_SocketAddress::GetIP4Ref() const
{
    return *reinterpret_cast<const uint32*>(&GetAsSockAddrIn()->sin_addr.S_un.S_addr);
}

#else

// Get the IP version 4 references.
uint32_t& JCSNetP_SocketAddress::GetIP4Ref()
{
    return GetAsSockAddrIn()->sin_addr.s_addr;
}

// Function overloading for constant getter.
const uint32& JCSNetP_SocketAddress::GetIP4Ref() const
{
    return GetAsSockAddrIn()->sin_addr.s_addr;
}
#endif

// Get socket address
sockaddr_in* JCSNetP_SocketAddress::GetAsSockAddrIn()
{
    return reinterpret_cast<sockaddr_in*>(&m_sockAddr);
}

// Get socket address as constant.
const sockaddr_in* JCSNetP_SocketAddress::GetAsSockAddrIn() const
{
    return reinterpret_cast<const sockaddr_in*>(&m_sockAddr);
}

NS_JCS_END
EXTERN_C_END
