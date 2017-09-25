/**
 * $File: ProgramMain.cpp $
 * $Date: 2017-04-16 20:27:37 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include <iostream>

#include <JCSNetP.h>

#ifdef _DEBUG
#pragma comment(lib, "JCSNetPd.lib")
#else
#pragma comment(lib, "JCSNetP.lib")
#endif

#define PORT 8671
#define HOST "127.0.0.1"

/**
 * @func main
 * @brief Program Entry Point
 * @param argc : argument count
 * @param argv : argument vector
 * @return int : program exception code.
 */
int main(int argc, char* argv[])
{
    JCSNetP_SocketConnector tcpConnector;

    JCSNetP_SocketAddress address(HOST, PORT);

    /* 设定这个过滤器将以对象为单位读取数据 */
    //tcpConnector.AddLast();

    /* 设定服务器消息处理器 */
    //tcpConnector.SetHandler();

    /* Set connect timeout.*/
    tcpConnector.SetConnectTimeoutCheckInterval(30);

    try
    {
        tcpConnector.Connect(address);
    }
    catch (std::exception e)
    {
        printf("客戶端連接異常...");
    }

    // --------------------
    std::cin.get();
    return 0;
}

