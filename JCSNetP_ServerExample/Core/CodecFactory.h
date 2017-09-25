#ifndef __CODECFACTORY_H__
/**
 * $File: CodecFactory.h $
 * $Date: 2017-04-16 22:37:00 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __CODECFACTORY_H__

#include <JCSNetP.h>


/**
 * @class CodecFactory
 * @brief
 */
class CodecFactory
    : public JCSNetP_ProtocolCodecFactory
{
private:

public:
    virtual ~CodecFactory();

    /**
     * @func GetDecoder
     * @brief Return the deocder handler.
     * @return decoder to do decode packet.
     */
    virtual JCSNetP_ProtocolDecoder* GetDecoder(JCSNetP_IoSession* arg0) = 0;

    /**
     * @func GetEncoder
     * @brief Return the encoder handler.
     * @return encocder to do encode packet.
     */
    virtual JCSNetP_ProtocolEncoder* GetEncoder(JCSNetP_IoSession arg0) = 0;

    /* setter */

    /* getter */

};

#endif /* __CODECFACTORY_H__ */
