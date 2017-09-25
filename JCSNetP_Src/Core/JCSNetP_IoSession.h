#ifndef __JCSNETP_IOSESSION_H__
/**
 * $File: JCSNetP_IoSession.h $
 * $Date: 2017-04-16 00:02:18 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_IOSESSION_H__


NS_JCS_BEGIN

class JCSNetP_InputMemoryBitStream;

/**
 * @class JCSNetP_IoSession
 * @brief  A handle which represents connection between two end-points 
 * regardless of transport types.
 */
class JCS_DLL JCSNetP_IoSession
{
private:
    /* unique identifier. */
    int32 m_networkId;

    // TODO(jenchieh): make this a interface so the code can be more 
    // cleaner and modular.
    /* socket object */
    JCSNetP_TCPSocketPtr m_pTCPSocket = nullptr;
    JCSNetP_UDPSocketPtr m_pUDPSocket = nullptr;

public:
    JCSNetP_IoSession(
        int32 inNetworkId,
        JCSNetP_TCPSocketPtr& inSocketAddress);
    JCSNetP_IoSession(
        int32 inNetworkId,
        JCSNetP_UDPSocketPtr& inSocketAddress);

    virtual ~JCSNetP_IoSession();

    /**
     * @func Close
     * @brief Close the session
     * @param inAct : immediately - true to close this session 
     * immediately . The pending write requests will simply be 
     * discarded. false to close this session after all queued 
     * write requests are flushed.
     */
    void Close(bool inAct);

    /**
     * @func CloseNow
     * @brief Closes this session immediately.
     */
    void CloseNow();

    /**
     * @func GetId
     * @brief Unique id for this session.
     * @return long : id value.
     */
    int32 GetId();

    /**
     * @func IsActive
     * @brief Check if the session active?
     * @return bool : is the session active?
     */
    bool IsActive();

    /**
     * @func IsConnected
     * @brief Check the connection is open.
     * @return bool : is connection connect?
     */
    bool IsConnected();
    
    /**
     * @func Write
     * @brief Write the message to the other end.
     * @param inBuffer : buffer to write over the network.
     */
    void Write(JCSNetP_InputMemoryBitStream& inBuffer);

    /* setter */

    /* getter */
    JCSNetP_TCPSocketPtr GetTCPSocket() const { return this->m_pTCPSocket; }
    JCSNetP_UDPSocketPtr GetUDPSocket() const { return this->m_pUDPSocket; }
};

NS_JCS_END
typedef std::shared_ptr<JCSNetP::JCSNetP_IoSession> JCSNetP_IoSessionPtr;
typedef JCSNetP::JCSNetP_IoSession JCSNetP_IoSession;

#endif /* __JCSNETP_IOSESSION_H__ */
