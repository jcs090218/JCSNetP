#ifndef __JCSNETP_PROTOCOLDECODER_H__
/**
 * $File: JCSNetP_ProtocolDecoder.h $
 * $Date: 2017-04-16 02:50:20 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_PROTOCOLDECODER_H__


NS_JCS_BEGIN

/**
 * @class JCSNetP_ProtocolDecoder
 * @brief  Interface for all protocol decoder.
 */
class JCSNetP_ProtocolDecoder
{
public:
    virtual ~JCSNetP_ProtocolDecoder() { }

    /**
     * @func DoDecode
     * @brief Do decode packet algorithm and decrypt key here.
     */
    virtual bool DoDecode(/*IoSession session, IoBuffer in, ProtocolDecoderOutput out*/) = 0;
};

NS_JCS_END
typedef JCSNetP::JCSNetP_ProtocolDecoder JCSNetP_ProtocolDecoder;


#endif /* __JCSNETP_PROTOCOLDECODER_H__ */
