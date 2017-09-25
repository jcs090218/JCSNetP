#ifndef __JCSNETP_H__
/**
 * $File: JCSNetP.h $
 * $Date: 2017-04-09 20:46:05 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_H__


/* helper macros */
#include "JCSNetP_StdAfx.h"

/* 'Enum' directory */
#include "Enum/SocketAddressFamily.h"
#include "Enum/JCSNetP_SocketType.h"

/* 'Interface' directory */
#include "Interface/JCSNetP_ProtocolCodecFactory.h"
#include "Interface/JCSNetP_ProtocolDecoder.h"
#include "Interface/JCSNetP_ProtocolEncoder.h"
#include "Interface/JCSNetP_IoHandlerAdapter.h"

/* 'Core' directory */
#include "Core/JCSNetP_Constants.h"
#include "Core/JCSNetP_Util.h"
#include "Core/ByteSwap.h"
#include "Core/JCSNetP_SocketAddress.h"
#include "Core/JCSNetP_SocketAddressFactory.h"
#include "Core/JCSNetP_UDPSocket.h"
#include "Core/JCSNetP_TCPSocket.h"
#include "Core/JCSNetP_LinkingContext.h"
#include "Core/JCSNetP_IoSession.h"
#include "Core/JCSNetP_SocketAcceptor.h"
#include "Core/JCSNetP_SocketConnector.h"

/* 'Core/Manager' directory */
#include "Core/Manager/JCSNetP_TCPNetworkManager.h"
#include "Core/Manager/JCSNetP_UDPNetworkManager.h"

/* 'Core/Stream' directory */
#include "Core/Stream/JCSNetP_InputMemoryStream.h"
#include "Core/Stream/JCSNetP_InputMemoryBitStream.h"
#include "Core/Stream/JCSNetP_OutputMemoryStream.h"
#include "Core/Stream/JCSNetP_OutputMemoryBitStream.h"

/* 'Support' directory */
#include "Support/JCS_vld.h"
#include "Support/JCSNetP_Defines.h"
#include "Support/JCSNetP_Name.h"
#include "Support/JCSNetP_SafePointer.h"
#include "Support/JCSNetP_StringUtil.h"
#include "Support/JCSNetP_WStringUtil.h"
#include "Support/JCSNetP_SocketUtil.h"

#endif /* __JCSNETP_H__ */
