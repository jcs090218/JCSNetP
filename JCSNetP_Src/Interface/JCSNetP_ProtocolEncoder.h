#ifndef __JCSNETP_PROTOCOLENCODER_H__
/**
 * $File: JCSNetP_ProtocolEncoder.h $
 * $Date: 2017-04-16 02:45:06 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_PROTOCOLENCODER_H__


NS_JCS_BEGIN

class JCSNetP_IoSession;

/**
 * @class JCSNetP_ProtocolEncoder
 * @brief Interface for all protocol encoder.
 */
class JCSNetP_ProtocolEncoder
{
public:
    virtual ~JCSNetP_ProtocolEncoder() { }

    /**
     * @func Dispose
     * @brief Dispose packet.
     */
    virtual void Dispose(JCSNetP_IoSession& session) = 0;

    /**
     * @func Encode
     * @brief Encode packet.
     */
    virtual void Encode(
        JCSNetP_IoSession& session/*, 
        void* message, 
        ProtocolEncoderOutput out*/) = 0;
};

NS_JCS_END
typedef JCSNetP::JCSNetP_ProtocolEncoder JCSNetP_ProtocolEncoder;

#endif /* __JCSNETP_PROTOCOLENCODER_H__ */
