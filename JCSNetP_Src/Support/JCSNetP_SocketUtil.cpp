/**
 * $File: JCSNetP_SocketUtil.cpp $
 * $Date: 2017-04-11 22:23:50 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../JCSNetP.h"


NS_JCS_BEGIN

// Initialize socket data I/O.
bool JCSNetP_SocketUtil::StaticInit()
{
#if _WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		ReportError("Starting Up");
		return false;
	}
#endif
	return true;
}

// Clean up socket I/O.
void JCSNetP_SocketUtil::CleanUp()
{
#if _WIN32
	WSACleanup();
#endif
}

// Report socket error.
void JCSNetP_SocketUtil::ReportError(const char* inOperationDesc)
{
#if _WIN32
	LPVOID lpMsgBuf;
	DWORD errorNum = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);


	JCS_LOG("Error %s: %d- %s", inOperationDesc, errorNum, lpMsgBuf);
#else
	JCS_LOG("Error: %hs", inOperationDesc);
#endif
}

// Get the last error code from OS API.
int JCSNetP_SocketUtil::GetLastError()
{
#if _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif

}

// Check the connection has error?
bool JCSNetP_SocketUtil::HasError()
{
#ifdef _WIN32
    int32 err = WSAGetLastError();
    if (err != WSAEWOULDBLOCK)
    {
#else
    int32 err = errno;
    if (err != EINPROGRESS && err != EAGAIN) {
#endif
        return true;
    }
    return false;
}

// Create a UDP socket.
JCSNetP_UDPSocketPtr JCSNetP_SocketUtil::CreateUDPSocket(SocketAddressFamily inFamily)
{
	SOCKET s = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);

	if (s != INVALID_SOCKET)
	{
		return JCSNetP_UDPSocketPtr(new JCSNetP_UDPSocket(s));
	}
	else
	{
		ReportError("SocketUtil::CreateUDPSocket");
		return nullptr;
	}
}

// Create a TCP socket.
JCSNetP_TCPSocketPtr JCSNetP_SocketUtil::CreateTCPSocket(SocketAddressFamily inFamily)
{
	SOCKET s = socket(inFamily, SOCK_STREAM, NULL);

    if (s == INVALID_SOCKET)
    {
        ReportError("SocketUtil::CreateTCPSocket");
        return nullptr;
    }

    int on = 1;
    /* Allow socket descriptor to be reuseable    */
    int err = setsockopt(
        s,
        SOL_SOCKET, 
        SO_REUSEADDR, 
        (char*)&on, 
        sizeof(on));
	
    if (err < 0)
    {
        ReportError("SocketUtil::CreateTCPSocket");
        return nullptr;
    }
		

    return JCSNetP_TCPSocketPtr(new JCSNetP_TCPSocket(s));
}

// 
fd_set* JCSNetP_SocketUtil::FillSetFromVector(
	fd_set& outSet, 
	const std::vector<JCSNetP_TCPSocketPtr>* inSockets,
	int& ioNaxNfds)
{
	if (inSockets)
	{
		FD_ZERO(&outSet);

		for (const JCSNetP_TCPSocketPtr& socket : *inSockets)
		{
			FD_SET(socket->m_socket, &outSet);
#if !_WIN32
			ioNaxNfds = std::max(ioNaxNfds, socket->m_socket);
#endif
		}
		return &outSet;
	}
	else
	{
		return nullptr;
	}
}

// 
void JCSNetP_SocketUtil::FillVectorFromSet(
	std::vector<JCSNetP_TCPSocketPtr>* outSockets,
	const std::vector<JCSNetP_TCPSocketPtr>* inSockets,
	const fd_set& inSet)
{
	if (inSockets && outSockets)
	{
		outSockets->clear();
		for (const JCSNetP_TCPSocketPtr& socket : *inSockets)
		{
			if (FD_ISSET(socket->m_socket, &inSet))
			{
				outSockets->push_back(socket);
			}
		}
	}
}

// Check if there are new incoming data that has not been process.
int JCSNetP_SocketUtil::Select(
	const std::vector<JCSNetP_TCPSocketPtr>* inReadSet,
	std::vector<JCSNetP_TCPSocketPtr>* outReadSet,
	const std::vector<JCSNetP_TCPSocketPtr>* inWriteSet,
	std::vector<JCSNetP_TCPSocketPtr>* outWriteSet,
	const std::vector<JCSNetP_TCPSocketPtr>* inExceptSet,
	std::vector<JCSNetP_TCPSocketPtr>* outExceptSet)
{
	// build up some sets from our vectors
	fd_set read, write, except;

	int nfds = 0;

	fd_set* readPtr = FillSetFromVector(read, inReadSet, nfds);
	fd_set* writePtr = FillSetFromVector(write, inWriteSet, nfds);
	fd_set* exceptPtr = FillSetFromVector(except, inExceptSet, nfds);

	int toRet = select(nfds + 1, readPtr, writePtr, exceptPtr, nullptr);

	if (toRet > 0)
	{
		FillVectorFromSet(outReadSet, inReadSet, read);
		FillVectorFromSet(outWriteSet, inWriteSet, write);
		FillVectorFromSet(outExceptSet, inExceptSet, except);
	}
	return toRet;
}

// Receive data from this particular socket descriptor.
int32 JCSNetP_SocketUtil::Receive(SOCKET inSocket, void* inBuffer, size_t inLen)
{
    return recv(inSocket, static_cast<char*>(inBuffer), inLen, 0);
}

// Cross platform close socket function.
void JCSNetP_SocketUtil::CloseSocket(SOCKET inSocket)
{
#if _WIN32
    closesocket(inSocket);
#else
    close(inSocket);
#endif
}

NS_JCS_END
