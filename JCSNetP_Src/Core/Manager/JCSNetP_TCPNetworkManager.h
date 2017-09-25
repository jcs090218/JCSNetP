#ifndef __JCSNETP_TCPNETWORKMANAGER_H__
/**
 * $File: JCSNetP_TCPNetworkManager.h $
 * $Date: 2017-04-15 23:29:22 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_TCPNETWORKMANAGER_H__


NS_JCS_BEGIN


/**
 * @func JCSNetP_TCPNetworkManager
 * @brief TCP network manager, use to handle all the packet and some
 * customizable settings.
 */
class JCS_DLL JCSNetP_TCPNetworkManager
{
private:
    JCSNetP_TCPSocketPtr m_socket;

    int	m_bytesSentThisFrame;

    float m_dropPacketChance;
    float m_simulatedLatency;

public:
    JCSNetP_TCPNetworkManager();
    virtual ~JCSNetP_TCPNetworkManager();

    /* setter */

    /* getter */

};

NS_JCS_END
typedef JCSNetP::JCSNetP_TCPNetworkManager JCSNetP_TCPNetworkManager;

#endif /* __JCSNETP_TCPNETWORKMANAGER_H__ */
