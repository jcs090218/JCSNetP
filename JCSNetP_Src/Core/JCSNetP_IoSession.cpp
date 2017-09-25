/**
 * $File: JCSNetP_IoSession.cpp $
 * $Date: 2017-04-16 00:03:21 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../JCSNetP.h"

NS_JCS_BEGIN

JCSNetP_IoSession::JCSNetP_IoSession(
    int32 inNetworkId,
    JCSNetP_TCPSocketPtr& inSocketAddress)
    :  m_networkId(inNetworkId)
    , m_pTCPSocket(inSocketAddress)
    , m_pUDPSocket(nullptr)
{

}

JCSNetP_IoSession::JCSNetP_IoSession(
    int32 inNetworkId,
    JCSNetP_UDPSocketPtr& inSocketAddress)
    : m_networkId(inNetworkId)
    , m_pTCPSocket(nullptr)
    , m_pUDPSocket(inSocketAddress)
{

}

JCSNetP_IoSession::~JCSNetP_IoSession()
{

}

// Close the session (CLIENT)
void JCSNetP_IoSession::Close(bool inAct)
{
    if (inAct)
    {
        SafeDeleteSharedPtr(this->m_pTCPSocket);
        SafeDeleteSharedPtr(this->m_pUDPSocket);
    }
}

// Closes this session immediately.
void JCSNetP_IoSession::CloseNow()
{
    this->Close(true);
}

// Unique id for this session.
int32 JCSNetP_IoSession::GetId()
{
    return this->m_networkId;
}

// Check if the session active?
bool JCSNetP_IoSession::IsActive()
{
    return false;
}

// Check the connection is open.
bool JCSNetP_IoSession::IsConnected()
{
    return false;
}

// Write the message to the other end.
void JCSNetP_IoSession::Write(JCSNetP_InputMemoryBitStream& inBuffer)
{

}

NS_JCS_END
