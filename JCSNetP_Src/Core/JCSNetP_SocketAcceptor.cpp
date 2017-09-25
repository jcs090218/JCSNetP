/**
 * $File: JCSNetP_SocketAcceptor.cpp $
 * $Date: 2017-04-16 02:05:53 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../JCSNetP.h"

EXTERN_C_BEGIN
NS_JCS_BEGIN

JCSNetP_SocketAcceptor::JCSNetP_SocketAcceptor(
    JCSNetP_SocketType inSocketType /*= JCSNetP_SocketType::TCP*/, 
    bool inBlocking /*= true*/)
    : m_socketType(inSocketType)
    , m_blocking(inBlocking)
    , m_pTCPSocket(nullptr)
    , m_pUDPSocket(nullptr)
    , m_pCodeFactory(nullptr)
    , m_pIoHandlerAdapter(nullptr)
{

}

JCSNetP_SocketAcceptor::~JCSNetP_SocketAcceptor()
{
    SafeDeleteObject(this->m_pCodeFactory);
    SafeDeleteObject(this->m_pIoHandlerAdapter);
}

// Create the socket and be ready to accept the connection.
void JCSNetP_SocketAcceptor::Bind(
    JCSNetP_SocketAddress& inBindAddress,
    SocketAddressFamily inFamily /*= SocketAddressFamily::INET*/)
{
    // check both socket are point to empty address.
    if (m_pTCPSocket || m_pUDPSocket)
    {
        JCS_LOG("Socket Acceptor have already be created. [%s]", "");
        return;
    }

    // initialize socket device.
    JCSNetP_SocketUtil::StaticInit();

    int err = 0;


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

        if (!m_pTCPSocket)
        {
            JCS_ERROR("[%s] Faild to create socket...", "JCSNetP_SocketAcceptor");
            return;
        }

        err = m_pTCPSocket->SetNonBlockingMode(m_blocking);
        if (err < JCS_NO_ERROR)
        {
            JCS_ERROR("[%s] Faild to set NIO...", "JCSNetP_SocketAcceptor");
            Dispose();
            return;
        }

        err = this->m_pTCPSocket->Bind(inBindAddress);
        if (err < JCS_NO_ERROR)
        {
            JCS_ERROR("[%s] Faild to bind socket...", "JCSNetP_SocketAcceptor");
            Dispose();
            return;
        }

        // start listening the connection
        int err = this->m_pTCPSocket->Listen();
        if (err < JCS_NO_ERROR)
        {
            JCS_ERROR("[%s] Faild to Listen socket...", "JCSNetP_SocketAcceptor");
            Dispose();
            return;
        }

        JCS_INFO("Server active successful... Port: %hu", inBindAddress.GetPort());

        /* Process through data. */
        ProcessTCP(inBindAddress);
    }
    break;
    case JCSNetP_SocketType::UDP:
    {
        this->m_pUDPSocket = JCSNetP_SocketUtil::CreateUDPSocket(inFamily);

        this->m_pUDPSocket->Bind(inBindAddress);

        this->m_pUDPSocket->SetNonBlockingMode(m_blocking);
    }
    break;
    }
}

// Handle the codec factory for both encoder and decoder.
void JCSNetP_SocketAcceptor::AddLast(JCSNetP_ProtocolCodecFactory& inCodecFilter)
{
    this->m_pCodeFactory = &inCodecFilter;
}

// Handle the packet after decrypt and ready to encrypt.
void JCSNetP_SocketAcceptor::SetHandler(JCSNetP_IoHandlerAdapter& inAdapter)
{
    this->m_pIoHandlerAdapter = &inAdapter;
}

/**
 * Get the unique network Id, make sure other could not get the
 * network Id, because once the this function get call one network Id
 * will be released.
 */
int32 JCSNetP_SocketAcceptor::GetUniqueNetworkId()
{
    int32 networkId = this->m_networkId;

    ++this->m_networkId;

    return networkId;
}

// Process through all the socket list and see there are data 
// coming in.
void JCSNetP_SocketAcceptor::ProcessTCP(JCSNetP_SocketAddress& inBindAddress)
{
    JCSNetP_TCPSocketPtr newTCPConnection = nullptr;
    JCSNetP_TCPSocketPtr tcpSocketPtr = GetTCPSocketPtr();

    int err = -1;
    int desc_ready;

    char recvBuffer[_MAX_MSGSIZE];
    int recvLen = 0;


#ifdef JCS_DEBUG
    printf("Press 'ESC' to exit the program...\n");
#endif

    // main loop.
    while (true)
    {
        if (!m_pTCPSocket)
        {
            JCS_ERROR("[%s] Exit loop because socket get disposed...", "JCSNetP_SocketAcceptor");
            break;
        }

        err = tcpSocketPtr->Select();
        if (err < JCS_NO_ERROR)
        {
            JCS_ERROR("[%s] Failed to select()", "JCSNetP_SocketAcceptor");
            break;
        }

        desc_ready = err;

        // 在現存的連線中尋找需要讀取的資料
        for (int index = 0;
            index <= tcpSocketPtr->GetMaxSd() && desc_ready > 0;
            ++index)
        {
            /* Check to see if this descriptor is ready */
            if (FD_ISSET(index, &tcpSocketPtr->GetWorkingSds()))
            {
                /**
                * A descriptor was found that was readable - one
                * less has to be looked for.  This is being done
                * so that we can stop looking at the working set
                * once we have found all of the descriptors that
                * were ready.
                */
                desc_ready = -1;

                /* Check to see if this is the listening socket */
                if (index == tcpSocketPtr->GetListenSocket())
                {
                    do
                    {
                        /* Accept new connection. */
                        newTCPConnection = tcpSocketPtr->Accept(inBindAddress);

                        if (tcpSocketPtr->GetNewSd() < 0)
                        {
                            break;
                        }
                        else
                        {
                            JCS_INFO("Open connection between server and client...");

                            int32 networkId = GetUniqueNetworkId();

                            // create new iosession.
                            JCSNetP_IoSessionPtr pNewSession
                                = JCSNetP_IoSessionPtr(
                                    new JCSNetP_IoSession(
                                        networkId,
                                        newTCPConnection));

                            // add in to the list.
                            m_ioSessionMap[networkId] = pNewSession;
                        }

                        /**
                         * Loop back up and accept another incoming
                         * connection                                 
                         */
                    } while (tcpSocketPtr->GetNewSd() != -1);
                }
                /** 
                 * This is not the listening socket, therefore an
                 * existing connection must be readable
                 */
                else
                {
                    int32 closeConnection = JCS_FALSE;

                    /**
                     * Receive all incoming data on this socket 
                     * before we loop back and call select again. 
                     */
                    while (true)
                    {
                        /** 
                         * Receive data on this connection until the 
                         * recv fails with EWOULDBLOCK. If any other 
                         * failure occurs, we will closesocket the 
                         * connection.                            
                         */
                        err = JCSNetP_SocketUtil::Receive(index, recvBuffer, sizeof(recvBuffer));

                        if (err < 0)
                        {
                            if (errno != EWOULDBLOCK)
                                closeConnection = JCS_TRUE;
                            break;
                        }

                        /**
                         * Check to see if the connection has been
                         * closesocket by the client.
                         */
                        if (err == 0)
                        {
                            JCS_INFO("Client has disconnected...");
                            closeConnection = JCS_TRUE;
                            break;
                        }

                        recvLen = err;
                        JCS_LOG("  %d bytes received\n", recvLen);
                    }

                    /**
                     * If the closesocket_conn flag was turned on, 
                     * we need to clean up this active connection. 
                     * This clean up process includes removing the 
                     * descriptor from the master set and determining 
                     * the new maximum descriptor value based on the 
                     * bits that are still turned on in the master set.
                     */
                    if (closeConnection)
                    {
                        JCSNetP_SocketUtil::CloseSocket(index);

                        FD_CLR(index, &tcpSocketPtr->GetMasterSet());

                        if (index == tcpSocketPtr->GetMaxSd())
                        {
                            while (FD_ISSET(tcpSocketPtr->GetMaxSd(), &tcpSocketPtr->GetMasterSet()) == JCS_FALSE)
                            {
                                tcpSocketPtr->SetMaxSd(tcpSocketPtr->GetMaxSd() - 1);
                            }
                        }
                    }
                } /* End of existing connection is readable */
            } /* End of if (FD_ISSET(i, &working_set)) */
        } /* End of loop through selectable descriptors */

#if _WIN32
        if (_kbhit())
        {
            // press ESC to exit break through the program loop.
            if (_getch() == 27)
                break;
        }
#endif
    }
}

// Process through all the socket list and see there are data
// coming in.
void JCSNetP_SocketAcceptor::ProcessUDP(JCSNetP_SocketAddress& inBindAddres)
{

}

// clean up the acceptor object. (SERVER)
void JCSNetP_SocketAcceptor::Dispose()
{
    SafeDeleteSharedPtr(this->m_pTCPSocket);
    SafeDeleteSharedPtr(this->m_pUDPSocket);
}

NS_JCS_END
EXTERN_C_END