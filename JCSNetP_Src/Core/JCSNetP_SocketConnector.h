#ifndef __JCSNETP_SOCKETCONNECTOR_H__
/**
 * $File: JCSNetP_SocketConnector.h $
 * $Date: 2017-04-16 02:32:04 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_SOCKETCONNECTOR_H__

EXTERN_C_BEGIN
NS_JCS_BEGIN

/**
 * @class JCSNetP_SocketConnector
 * @brief Opposite class of 'JCSNetP_SocketAcceptor', this class is use
 * for client to connect to the acceptor which is the server.
 */
class JCS_DLL JCSNetP_SocketConnector
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

    // timeout to connect to server.
    int32 m_timeout = BLOCKSECONDS;

    // client unique id.
    int32 m_networkId = -1;

public:
    JCSNetP_SocketConnector(
        JCSNetP_SocketType inSocketType = JCSNetP_SocketType::TCP,
        bool inBlocking = true);
    virtual  ~JCSNetP_SocketConnector();

    /**
     * @func Connect
     * @brief Connect to the other end (acceptor).
     * @param inBindAddress : internet address to bind.
     * @param inFamily : internet protocol version.
     */
    void Connect(
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
     * @brief Disconnect from the acceptor and dispose the socket object.
     */
    void Dispose();

    /**
     * @func SetConnectTimeoutCheckInterval
     * @brief Set connection time out.
     * @param inTimeout : time to do time out.
     */
    void SetConnectTimeoutCheckInterval(int32 inTimeout);

    /* setter */

    /* getter */

};

NS_JCS_END
typedef JCSNetP::JCSNetP_SocketConnector JCSNetP_SocketConnector;
EXTERN_C_END

#endif /* __JCSNETP_SOCKETCONNECTOR_H__ */
