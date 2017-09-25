#ifndef __JCSNETP_UDPSOCKET_H__
/**
 * $File: JCSNetP_UDPSocket.h $
 * $Date: 2017-04-09 23:40:58 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_UDPSOCKET_H__


EXTERN_C_BEGIN
NS_JCS_BEGIN

/**
 * @class JCSNetP_UDPSocket
 * @brief 
 */
class JCS_DLL JCSNetP_UDPSocket
{
private:
	// NOTE(jenchieh): should allow call from this class.
	friend class JCSNetP_SocketUtil;

	// socket object.
	SOCKET m_socket;

public:
    ~JCSNetP_UDPSocket();

	/**
	 * @func Bind
	 * @brief Bind the address.
	 * @param inToAddress : address object.
	 * @return int : 0 = success, -1 = error.
	 */
	int Bind(const JCSNetP_SocketAddress& inToAddress);

	/**
	 * @func SendTo
	 * @brief Send buffer to another end.
	 * @param inToSend : 
	 * @param inLength : length of the data/
	 * @param inToAddress : address sent.
	 * @return int : 0 = success, -1 = error.
	 */
	int SendTo(
		const void* inToSend, 
		int inLength, 
		const JCSNetP_SocketAddress& inToAddress);

	/**
	 * @func ReceiveFrom
	 * @brief Receive buffer from another end.
	 * @param inToReceive : 
	 * @param inMaxLength : maxinum data length.
	 * @param outFromAddress : 
	 * @return int : 0 = success, -1 = error.
	 */
	int ReceiveFrom(
		void* inToReceive, 
		int inMaxLength, 
		JCSNetP_SocketAddress& outFromAddress);

	/**
	 * @func SetNonBlockingMode
	 * @brief Set socket blocking or non-blocking.
	 * @param inShouldBeNonBlocking : 
	 *	    true = non-blocking I/O, 
	 *      false = blocking I/O.
	 * @return int : 0 = success, -1 = error.
	 */
	int SetNonBlockingMode(bool inShouldBeNonBlocking);

    /**
     * @func Close
     * @brief Close the socket and cleanup.
     */
    void Close();

    /**
     * @func Dispose
     * @brief Destory the socket.
     */
    void Dispose();

	/* setter */

    /* getter */

private:
	/**
	 * @func Constructor
	 * @brief constructor - does not allow call from user.
	 * @param inSocket : socket object.
	 */
    JCSNetP_UDPSocket(SOCKET inSocket);
};

NS_JCS_END
typedef JCSNetP::JCSNetP_UDPSocket JCSNetP_UDPSocket;

typedef std::shared_ptr<JCSNetP_UDPSocket> JCSNetP_UDPSocketPtr;
template class JCS_DLL std::shared_ptr<JCSNetP_UDPSocket>;

EXTERN_C_END

#endif /* __JCSNETP_UDPSOCKET_H__ */
