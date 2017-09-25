#ifndef __JCSNETP_SOCKETADDRESS_H__
/**
 * $File: JCSNetP_SocketAddress.h $
 * $Date: 2017-04-09 23:38:51 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_SOCKETADDRESS_H__


EXTERN_C_BEGIN
NS_JCS_BEGIN

/**
 * @class SocketAddress
 * @brief Socket address complete handle rather than
 * just a string.
 */
class JCS_DLL JCSNetP_SocketAddress
{
private:
    friend class JCSNetP_TCPSocket;
    friend class JCSNetP_UDPSocket;

    sockaddr m_sockAddr;

    uint16 m_port = -1;

public:
    JCSNetP_SocketAddress();
    JCSNetP_SocketAddress(const sockaddr& inSockAddr);
    JCSNetP_SocketAddress(uint16 inAddress);
    JCSNetP_SocketAddress(const char* inHost, uint16 inPort);
    JCSNetP_SocketAddress(uint32 inAddress, uint16 inPort);

    ~JCSNetP_SocketAddress();

	bool operator==(const JCSNetP_SocketAddress& inOther) const;

	/**
	 * @func GetHash
	 * @brief Hash of the object.
	 * @return size_t : Hash size.
	 */
	size_t GetHash() const;

	/**
	 * @func GetSize
	 * @brief get the size of the object.
	 * @return uint32 : value of the size.
	 */
    uint32 GetSize()const;

	/**
	 * @func ToString
	 * @brief Convert object to string.
	 * @return std::string : object string.
	 */
    std::string ToString() const;

    /* setter */

    /* getter */
    uint16 GetPort() const { return this->m_port; }

private:

#if _WIN32
	/** 
	 * @func GetIP4Ref
	 * @brief Get the IP version 4 references.
	 * @return uint32 : value.
	 */
    uint32& GetIP4Ref();
	/**
	 * @func GetIP4Ref
	 * @brief Function overloading for constant getter.
	 * @return uint32 : value.
	 */
    const uint32& GetIP4Ref() const;
#else
	/**
	 * @func GetIP4Ref
	 * @brief Get the IP version 4 references.
	 * @return uint32 : value.
	 */
    uint32& GetIP4Ref();
	/**
	 * @func GetIP4Ref
	 * @brief Function overloading for constant getter.
	 * @return uint32 : value.
	 */
    const uint32_t& GetIP4Ref() const;
#endif

	/**
	 * @func GetAsSockAddrIn
	 * @brief Get socket address
	 * @return sockaddr_in : value.
	 */
    sockaddr_in* GetAsSockAddrIn();
	/**
	 * @func GetAsSockAddrIn
	 * @brief Get socket address as constant.
	 * @return sockaddr_in : value.
	 */
    const sockaddr_in* GetAsSockAddrIn() const;
};


NS_JCS_END
typedef JCSNetP::JCSNetP_SocketAddress JCSNetP_SocketAddress;
typedef std::shared_ptr<JCSNetP::JCSNetP_SocketAddress> JCSNetP_SocketAddressPtr;
EXTERN_C_END


namespace std
{
	/**
	 * @struct hash<JCSNetP_SocketAddress>
	 * @brief 
	 */
	template<> 
    struct hash<JCSNetP_SocketAddress>
	{
		size_t operator()(const JCSNetP_SocketAddress& inAddress) const
		{
			return inAddress.GetHash();
		}
	};
}

#endif /* __JCSNETP_SOCKETADDRESS_H__ */
