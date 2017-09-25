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
#include "ServerExample.h"

#ifdef _DEBUG
#pragma comment(lib, "JCSNetPd.lib")
#else
#pragma comment(lib, "JCSNetP.lib")
#endif

#define PORT 8671



/**
 * @func main
 * @brief Program Entry Point
 * @param argc : argument count
 * @param argv : argument vector
 * @return int : program exception code.
 */
int main(int argc, char* argv[])
{
    JCSNetP_SocketAcceptor tcpAcceptor;

    /* 设定这个过滤器将以对象为单位读取数据 */
    //tcpAcceptor.AddLast();

    /* 设定服务器消息处理器 */
    //tcpAcceptor.SetHandler();

    try
    {
        tcpAcceptor.Bind(JCSNetP_SocketAddress(PORT));
        printf("服務端起動成功... 端口號為: %d", PORT);
    }
    catch (std::exception e)
    {
        printf("服務端異常...");
    }

    // --------------------
    std::cin.get();
    return 0;
}
