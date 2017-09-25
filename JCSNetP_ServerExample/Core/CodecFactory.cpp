/**
 * $File: CodecFactory.cpp $
 * $Date: 2017-04-16 22:37:04 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../ServerExample.h"


CodecFactory::~CodecFactory()
{

}

// Return the deocder handler.
JCSNetP_ProtocolDecoder* GetDecoder(/*IoSession arg0*/)
{
    return nullptr;
}

// Return the encoder handler.
JCSNetP_ProtocolEncoder* GetEncoder(/*IoSession arg0*/)
{
    return nullptr;
}
