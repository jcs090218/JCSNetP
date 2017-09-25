#ifndef __JCSNETP_CONSTANTS_H__
/**
 * $File: JCSNetP_Constants.h $
 * $Date: 2017-04-17 00:38:35 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_CONSTANTS_H__


NS_JCS_BEGIN

#define _MAX_MSGSIZE 16 * 1024          // 暫定一個消息最大回16k
#define BLOCKSECONDS 30                 // INIT函數阻塞時間
#define INBUFSIZE    (64 * 1024)        // 具体尺寸根据剖面报告调整  接收数据的缓存
#define OUTBUFSIZE   (8 * 1024)         // 具体尺寸根据剖面报告调整。 发送数据的缓存，当不超过8K时，FLUSH只需要SEND一次

#define DEFAULT_HOST_NAME "127.0.0.1"
#define DEFAULT_PORT 8585

NS_JCS_END

#endif /* __JCSNETP_CONSTANTS_H__ */
