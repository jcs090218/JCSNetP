#ifndef __JCSNETP_SOCKETACCEPTOR_H__
/**
 * $File: JCSNetP_SocketAcceptor.h $
 * $Date: 2017-04-16 01:36:14 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_SOCKETACCEPTOR_H__


EXTERN_C_BEGIN

NS_JCS_BEGIN

enum SocketAddressFamily;

class JCSNetP_ProtocolCodecFactory;
class JCSNetP_IoHandlerAdapter;
class JCSNetP_IoSession;


/**
 * @class JCSNetP_SocketAcceptor
 * @brief This is class when handle all the SOCKETs and codec.
 * Include encoder and decoder filter. Plus this class is for server not 
 * the client.
 */
class JCSNetP_SocketAcceptor
{
private:
    // type of the socket, default is TCP.
    JCSNetP_SocketType m_socketType = JCSNetP_SocketType::TCP;

    // socket object.
    JCSNetP_TCPSocketPtr m_pTCPSocket = nullptr;
    JCSNetP_UDPSocketPtr m_pUDPSocket = nullptr;

    // blocking IO, default true.
    bool m_blocking = true;

    // factory to hold the packet encoder and decoder.
    JCSNetP_ProtocolCodecFactory* m_pCodeFactory = nullptr;
    
    // packet handler.
    JCSNetP_IoHandlerAdapter* m_pIoHandlerAdapter = nullptr;

    // give all the clients a Id, this will be increasing.
    int32 m_networkId = -1;

    // map of all the clients and network Id.
    std::unordered_map<int32, JCSNetP_IoSessionPtr> m_ioSessionMap;


public:
    JCSNetP_SocketAcceptor(
        JCSNetP_SocketType inSocketType = JCSNetP_SocketType::TCP, 
        bool inBlocking = true);
    virtual ~JCSNetP_SocketAcceptor();

    /**
     * @func Create
     * @brief Create the socket and be ready to accept the connection.
     * @param inBindAddress : internet address to bind.
     * @param inFamily : internet protocol version.
     */
    void Bind(
        JCSNetP_SocketAddress& inBindAddress,
        SocketAddressFamily inFamily = SocketAddressFamily::INET);

    /**
     * @func SetHandler
     * @brief Handle the codec factory for both encoder and decoder.
     * @param inCodecFilter : codec factory, in order to connect
     * encoder and decoder.
     */
    void AddLast(JCSNetP_ProtocolCodecFactory& inCodecFilter);

    /**
     * @func SetHandler
     * @brief Handle the packet after decrypt and ready to encrypt.
     * @param inAdapter : Packet handler.
     */
    void SetHandler(JCSNetP_IoHandlerAdapter& inAdapter);

    /**
     * @func Dispose
     * @brief clean up the acceptor object.
     */
    void Dispose();

    /* setter */

    /* getter */
    JCSNetP_SocketType GetSocketType() const { return this->m_socketType; }
    JCSNetP_TCPSocketPtr GetTCPSocketPtr() const { return this->m_pTCPSocket; }
    JCSNetP_UDPSocketPtr GetUDPSocketPtr() const { return this->m_pUDPSocket; }

private:

    /**
     * @func GetUniqueNetworkId
     * @brief Get the unique network Id, make sure other could not get the 
     * network Id, because once the this function get call one network Id 
     * will be released.
     * @return int32 : unique network Id.
     */
    int32 GetUniqueNetworkId();

    /** 
     * @func ProcessTCP
     * @brief Process through all the socket list and see there are data
     * coming in.
     */
    void ProcessTCP(JCSNetP_SocketAddress& inBindAddress);

    /**
     * @func ProcessUDP
     * @brief Process through all the socket list and see there are data
     * coming in.
     */
    void ProcessUDP(JCSNetP_SocketAddress& inBindAddres);
};

NS_JCS_END
typedef JCSNetP::JCSNetP_SocketAcceptor JCSNetP_SocketAcceptor;
EXTERN_C_END

#endif /* __JCSNETP_SOCKETACCEPTOR_H__ */
