#ifndef __JCSNETP_DEFINES_H__
/**
* $File: JCSNetP_Defines.h $
* $Date: 2017-04-09 23:26:41 $
* $Revision: $
* $Creator: Jen-Chieh Shen $
* $Notice: See LICENSE.txt for modification and distribution information
*                   Copyright (c) 2017 by Shen, Jen-Chieh $
*/
#define __JCSNETP_DEFINES_H__


/* Windows Socket Defines */
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h>
#include <WinSock2.h>
#include <Ws2tcpip.h>
typedef int socklen_t;
//typedef char* receiveBufer_t;
#else
/* POSIX Socket Defines */
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
//typedef void* receiveBufer_t;
typedef int SOCKET;
const int NO_ERROR = 0;
const int INVALID_SOCKET = -1;
const int WSAECONNRESET = ECONNRESET;
const int WSAEWOULDBLOCK = EAGAIN;
const int SOCKET_ERROR = -1;
#endif


#if _WIN32
#include <conio.h>
#endif

#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <list>
#include <queue>
#include <deque>
#include <unordered_set>
#include <cassert>
#include <thread>

#include <cstdlib>
#include <cstdint>
#include <type_traits>

#endif /* __JCSNETP_DEFINES_H__ */
