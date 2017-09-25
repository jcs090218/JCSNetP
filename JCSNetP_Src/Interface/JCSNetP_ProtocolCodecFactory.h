#ifndef __JCSNETP_PROTOCOLCODECFACTORY_H__
/**
 * $File: JCSNetP_ProtocolCodecFactory.h $
 * $Date: 2017-04-16 02:41:16 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_PROTOCOLCODECFACTORY_H__



NS_JCS_BEGIN

class JCSNetP_ProtocolEncoder;
class JCSNetP_ProtocolDecoder;
class JCSNetP_IoSession;

/**
 * @class JCSNetP_ProtocolCodecFactory
 * @brief Codec factory, so the network engine could get the
 * customize decoder and encoder here.
 */
class JCSNetP_ProtocolCodecFactory
{
public:
    virtual ~JCSNetP_ProtocolCodecFactory() { }

    /**
     * @func GetDecoder
     * @brief Return the deocder handler.
     * @return decoder to do decode packet.
     */
    virtual JCSNetP_ProtocolDecoder* GetDecoder(JCSNetP_IoSession& arg0) = 0;

    /**
     * @func GetEncoder
     * @brief Return the encoder handler.
     * @return encocder to do encode packet.
     */
    virtual JCSNetP_ProtocolEncoder* GetEncoder(JCSNetP_IoSession& arg0) = 0;

};

NS_JCS_END
typedef JCSNetP::JCSNetP_ProtocolCodecFactory JCSNetP_ProtocolCodecFactory;

#endif /* __JCSNETP_PROTOCOLCODECFACTORY_H__ */
