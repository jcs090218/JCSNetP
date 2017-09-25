/**
 * $File: JCSNetP_UDPSocket.cpp $
 * $Date: 2017-04-09 23:42:19 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../JCSNetP.h"


EXTERN_C_BEGIN
NS_JCS_BEGIN

JCSNetP_UDPSocket::JCSNetP_UDPSocket(SOCKET inSocket)
	: m_socket(inSocket)
{

}

JCSNetP_UDPSocket::~JCSNetP_UDPSocket()
{
    this->Close();
}

// Bind the address.
int JCSNetP_UDPSocket::Bind(const JCSNetP_SocketAddress& inBindAddress)
{
	int error = bind(m_socket, &inBindAddress.m_sockAddr, inBindAddress.GetSize());
	if (error != 0)
	{
		JCSNetP_SocketUtil::ReportError("UDPSocket::Bind");
		return JCSNetP_SocketUtil::GetLastError();
	}

	return NO_ERROR;
}

// Send buffer to another end.
int JCSNetP_UDPSocket::SendTo(
	const void* inToSend, 
	int inLength, 
	const JCSNetP_SocketAddress& inToAddress)
{
	int byteSentCount = sendto(m_socket,
		static_cast< const char* >(inToSend),
		inLength,
		0, &inToAddress.m_sockAddr, inToAddress.GetSize());
	if (byteSentCount <= 0)
	{
		// we'll return error as negative number to indicate less than 
		// requested amount of bytes sent...
		JCSNetP_SocketUtil::ReportError("UDPSocket::SendTo");
		return -JCSNetP_SocketUtil::GetLastError();
		return 0;
	}
	else
	{
		return byteSentCount;
	}
}

// Receive buffer from another end.
int JCSNetP_UDPSocket::ReceiveFrom(
	void* inToReceive, 
	int inMaxLength, 
	JCSNetP_SocketAddress& outFromAddress)
{
	socklen_t fromLength = outFromAddress.GetSize();

	int readByteCount = recvfrom(m_socket,
		static_cast< char* >(inToReceive),
		inMaxLength,
		0, &outFromAddress.m_sockAddr, &fromLength);
	if (readByteCount >= 0)
	{
		return readByteCount;
	}
	else
	{
		int error = JCSNetP_SocketUtil::GetLastError();

		if (error == WSAEWOULDBLOCK)
		{
			return 0;
		}
		else if (error == WSAECONNRESET)
		{
			/**
			 * this can happen if a client closed and we haven't DC'd yet.
			 * this is the ICMP message being sent back saying the port 
			 * on that computer is closed
			 */
			JCS_LOG("Connection reset from %s", outFromAddress.ToString().c_str());
			return -WSAECONNRESET;
		}
		else
		{
			JCSNetP_SocketUtil::ReportError("UDPSocket::ReceiveFrom");
			return -error;
		}
	}
}

// Set socket blocking or non-blocking.
int JCSNetP_UDPSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
{
    /**
     * Set socket to be nonblocking. All of the sockets for
     * the incoming connections will also be nonblocking since
     * they will inherit that state from the listening socket.
     */

#if _WIN32
	u_long arg = inShouldBeNonBlocking ? 1 : 0;
	int result = ioctlsocket(m_socket, FIONBIO, &arg);
#else
	int flags = fcntl(mSocket, F_GETFL, 0);
	flags = inShouldBeNonBlocking ? (flags | O_NONBLOCK) : (flags & ~O_NONBLOCK);
	int result = fcntl(mSocket, F_SETFL, flags);
#endif

	if (result == SOCKET_ERROR)
	{
		JCSNetP_SocketUtil::ReportError("UDPSocket::SetNonBlockingMode");
		return JCSNetP_SocketUtil::GetLastError();
	}
	else
	{
		return NO_ERROR;
	}
}

// Close the socket and cleanup.
void JCSNetP_UDPSocket::Close()
{
#if _WIN32
    closesocket(m_socket);
    JCSNetP_SocketUtil::CleanUp();
#else
    close(m_socket);
#endif
}

// Destory the socket.
void JCSNetP_UDPSocket::Dispose()
{
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
