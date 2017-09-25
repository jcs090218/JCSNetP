/**
* $File: JCSNetP_TCPSocket.cpp $
* $Date: 2017-04-09 23:20:05 $
* $Revision: $
* $Creator: Jen-Chieh Shen $
* $Notice: See LICENSE.txt for modification and distribution information
*                   Copyright (c) 2017 by Shen, Jen-Chieh $
*/

#include "../JCSNetP.h"


EXTERN_C_BEGIN
NS_JCS_BEGIN


JCSNetP_TCPSocket::JCSNetP_TCPSocket(SOCKET& inSocket)
    : m_socket(inSocket)
{
    FD_ZERO(&m_master_set);
    FD_ZERO(&m_working_set);
    FD_ZERO(&m_max_sd);
}

JCSNetP_TCPSocket::~JCSNetP_TCPSocket()
{
    this->Close();
}

// Connect using socket address object handle.
int JCSNetP_TCPSocket::Connect(
    const JCSNetP_SocketAddress& inAddress,
    int32 inTimeout /*= BLOCKSECONDS*/)
{
    int err = connect(m_socket, &inAddress.m_sockAddr, inAddress.GetSize());
    if (err < 0)
    {
        JCSNetP_SocketUtil::ReportError("TCOSocket::Connect");
        return -JCSNetP_SocketUtil::GetLastError();
    }
    else
    {
        timeval timeout;
        timeout.tv_sec = inTimeout;
        timeout.tv_usec = 0;
        fd_set writeset, exceptset;
        FD_ZERO(&writeset);
        FD_ZERO(&exceptset);
        FD_SET(m_socket, &writeset);
        FD_SET(m_socket, &exceptset);

        int32 ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
        if (ret == 0 || ret < 0)
        {
            Close();

            JCSNetP_SocketUtil::ReportError("TCOSocket::Connect");
            return -JCSNetP_SocketUtil::GetLastError();
        }
        else  // ret > 0  
        {
            ret = FD_ISSET(m_socket, &exceptset);
            if (ret)     // or (!FD_ISSET(m_sockClient, &writeset)  
            {
                Close();

                JCSNetP_SocketUtil::ReportError("TCOSocket::Connect");
                return -JCSNetP_SocketUtil::GetLastError();
            }
        }
    }

    return NO_ERROR;
}

// Bind to the specific route.
int JCSNetP_TCPSocket::Bind(const JCSNetP_SocketAddress& inBindAddress)
{
    int error = bind(m_socket, &inBindAddress.m_sockAddr, inBindAddress.GetSize());
    if (error < 0)
    {
        JCSNetP_SocketUtil::ReportError("TCPSocket::Bind");
        return JCSNetP_SocketUtil::GetLastError();
    }

    return NO_ERROR;
}

// Listen to specific client.
int JCSNetP_TCPSocket::Listen(int inBackLog /*= SOMAXCONN*/)
{
    int err = listen(m_socket, inBackLog);
    if (err < 0)
    {
        JCSNetP_SocketUtil::ReportError("TCPSocket::Listen");
        return -JCSNetP_SocketUtil::GetLastError();
    }

    /* Initialize the master fd_set */

    FD_ZERO(&m_master_set);

    // 持續追蹤最大的 file descriptor
    this->m_max_sd = this->m_socket;  // 到此為止，就是它了

    // 將 listener 新增到 master set
    FD_SET(m_socket, &m_master_set);

    return NO_ERROR;
}

// Accept the connection?
JCSNetP_TCPSocketPtr JCSNetP_TCPSocket::Accept(JCSNetP_SocketAddress& inFromAddress)
{
    socklen_t length = inFromAddress.GetSize();
    SOCKET newSocket = accept(m_socket, &inFromAddress.m_sockAddr, &length);

    this->m_new_sd = newSocket;

    if (newSocket != INVALID_SOCKET)
    {
        /* Print out connection info. */
        char remoteIP[INET6_ADDRSTRLEN];
        JCS_INFO(
            "IoSession with /%s:%d opened", 
            inet_ntop(
                inFromAddress.GetAsSockAddrIn()->sin_family, 
                &inFromAddress.GetAsSockAddrIn()->sin_addr, 
                remoteIP, INET6_ADDRSTRLEN), 
            newSocket);

        /** 
         * Add the new incoming connection to the master read set.
         */
        FD_SET(m_new_sd, &m_master_set);
        if (m_new_sd > m_max_sd)
            m_max_sd = m_new_sd;

        return JCSNetP_TCPSocketPtr(new JCSNetP_TCPSocket(newSocket));
    }
    else
    {
        /**
         * NIO will keep accepting new socket, this will make it keep 
         * reporting error even we know that there are no error here...
         * So we just report error when the NIO is not been set!
         */
        if (!m_blockingIo)
            JCSNetP_SocketUtil::ReportError("TCPSocket::Accept");

        return nullptr;
    }
}

// Check if there is data coming from another socket. Use for
// Non - blocking socket.
int32 JCSNetP_TCPSocket::Select()
{
    memcpy(&m_working_set, &m_master_set, sizeof(m_master_set));

    int32 err = select(this->m_max_sd + 1, &m_working_set, NULL, NULL, NULL);

    if (err < 0)
    {
        /**
         * NIO will keep accepting new socket, this will make it keep
         * reporting error even we know that there are no error here...
         * So we just report error when the NIO is not been set!
         */
        if (!m_blockingIo)
            JCSNetP_SocketUtil::ReportError("TCPSocket::Select");

        return -JCSNetP_SocketUtil::GetLastError();
    }

    /* We need to know the actual error code here... */
    return err;
}

// Send data to the other side.
int32 JCSNetP_TCPSocket::Send(const void* inData, size_t inLen)
{
    int bytesSentCount = send(m_socket, static_cast<const char*>(inData), inLen, 0);
    if (bytesSentCount < 0)
    {
        JCSNetP_SocketUtil::ReportError("TCPSocket::Send");
        return -JCSNetP_SocketUtil::GetLastError();
    }
    return bytesSentCount;
}

// Receive data from the other side.
int32 JCSNetP_TCPSocket::Receive(void* inBuffer, size_t inLen)
{
    int bytesReceivedCount = recv(m_socket, static_cast<char*>(inBuffer), inLen, 0);
    if (bytesReceivedCount < 0)
    {
        JCSNetP_SocketUtil::ReportError("TCPSocket::Receive");
        return -JCSNetP_SocketUtil::GetLastError();
    }
    return bytesReceivedCount;
}

// Set socket blocking or non-blocking.
int JCSNetP_TCPSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
{
    this->m_blockingIo = inShouldBeNonBlocking;

    /** 
     * Set socket to be nonblocking. All of the sockets for
     * the incoming connections will also be nonblocking since
     * they will inherit that state from the listening socket. 
     */

#if _WIN32
    u_long arg = inShouldBeNonBlocking ? 1 : 0;
    int result = ioctlsocket(m_socket, FIONBIO, &arg);
#else
    int flags = fcntl(m_socket, F_GETFL, 0);
    flags = inShouldBeNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
    int result = fcntl(mSocket, F_SETFL, flags);
#endif

    if (result == SOCKET_ERROR)
    {
        JCSNetP_SocketUtil::ReportError("TCPSocket::SetNonBlockingMode");
        return JCSNetP_SocketUtil::GetLastError();
    }
    else
    {
        return NO_ERROR;
    }
}

// Close the socket and cleanup.
void JCSNetP_TCPSocket::Close()
{
    JCSNetP_SocketUtil::CloseSocket(m_socket);
    JCSNetP_SocketUtil::CleanUp();
}

// Destory the socket.
void JCSNetP_TCPSocket::Dispose()
{
    /* Clean up all of the sockets that are open. */
    for (int index = 0; 
        index <= m_max_sd; 
        ++index)
    {
        if (FD_ISSET(index, &m_master_set))
        {
            JCSNetP_SocketUtil::CloseSocket(index);
        }
    }

    // 關閉  
    struct linger so_linger;
    so_linger.l_onoff = 1;
    so_linger.l_linger = 500;
    int32 ret = setsockopt(m_socket, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

    Close();

    m_socket = INVALID_SOCKET;
}

NS_JCS_END
EXTERN_C_END
