/**
 * $File: JCSNetP_SocketConnector.cpp $
 * $Date: 2017-04-16 02:32:06 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../JCSNetP.h"

EXTERN_C_BEGIN
NS_JCS_BEGIN

JCSNetP_SocketConnector::JCSNetP_SocketConnector(
    JCSNetP_SocketType inSocketType /*= JCSNetP_SocketType::TCP*/,
    bool inBlocking /*= true*/)
    : m_socketType(inSocketType)
    , m_blocking(inBlocking)
    , m_pTCPSocket(nullptr)
    , m_pUDPSocket(nullptr)
    , m_pCodeFactory(nullptr)
    , m_pIoHandlerAdapter(nullptr)
    , m_timeout(BLOCKSECONDS)
{

}

JCSNetP_SocketConnector::~JCSNetP_SocketConnector()
{

}

// Connect to the other end (acceptor).
void JCSNetP_SocketConnector::Connect(
    JCSNetP_SocketAddress& inBindAddress,
    SocketAddressFamily inFamily /*= SocketAddressFamily::INET*/)
{
    // check both socket are point to empty address.
    if (m_pTCPSocket || m_pUDPSocket)
    {
        JCS_LOG("Socket Connector have already be created. [%s]", "");
        return;
    }

    // initialize socket device.
    JCSNetP_SocketUtil::StaticInit();

    // check socket type
    switch (m_socketType)
    {
    case JCSNetP_SocketType::NONE:
    {
        JCS_LOG("Cannot create socket acceptor with socket type unknown. [%s]",
            "JCSNetP_SocketType::NONE");
        return;
    }
    break;
    case JCSNetP_SocketType::TCP:
    {
        this->m_pTCPSocket = JCSNetP_SocketUtil::CreateTCPSocket(inFamily);

        // connect to the server, with timeout.
        this->m_pTCPSocket->Connect(inBindAddress, m_timeout);

        this->m_pTCPSocket->SetNonBlockingMode(m_blocking);
    }
    break;
    case JCSNetP_SocketType::UDP:
    {
        this->m_pUDPSocket = JCSNetP_SocketUtil::CreateUDPSocket(inFamily);

        this->m_pUDPSocket->SetNonBlockingMode(m_blocking);
    }
    break;
    }

}

// Handle the codec factory for both encoder and decoder.
void JCSNetP_SocketConnector::AddLast(JCSNetP_ProtocolCodecFactory& inCodecFilter)
{
    this->m_pCodeFactory = &inCodecFilter;
}

// Handle the packet after decrypt and ready to encrypt.
void JCSNetP_SocketConnector::SetHandler(JCSNetP_IoHandlerAdapter& inAdapter)
{
    this->m_pIoHandlerAdapter = &inAdapter;
}

// Disconnect from the acceptor and dispose the socket object.
void JCSNetP_SocketConnector::Dispose()
{
    if (m_pTCPSocket)
        m_pTCPSocket->Close();
    if (m_pUDPSocket)
        m_pUDPSocket->Close();
}

// Set connection time out.
void JCSNetP_SocketConnector::SetConnectTimeoutCheckInterval(int32 inTimeout)
{
    this->m_timeout = inTimeout;
}

NS_JCS_END
EXTERN_C_END
