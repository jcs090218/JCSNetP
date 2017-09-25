#ifndef __JCSNETP_UDPNETWORKMANAGER_H__
/**
 * $File: JCSNetP_UDPNetworkManager.h $
 * $Date: 2017-04-15 23:30:42 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_UDPNETWORKMANAGER_H__


EXTERN_C_BEGIN
NS_JCS_BEGIN


/**
 * @func JCSNetP_UDPNetworkManager
 * @brief UDP network manager, use to handle all the packet and some
 * customizable settings.
 */
class JCS_DLL JCSNetP_UDPNetworkManager
{
private:
    JCSNetP_UDPSocketPtr m_socket = nullptr;

public:
    JCSNetP_UDPNetworkManager();
    virtual ~JCSNetP_UDPNetworkManager();

    /* setter */

    /* getter */

};

NS_JCS_END
typedef JCSNetP::JCSNetP_UDPNetworkManager JCSNetP_UDPNetworkManager;
EXTERN_C_END

#endif /* __JCSNETP_UDPNETWORKMANAGER_H__ */
