#ifndef __JCSNETP_TCPSOCKET_H__
/**
 * $File: JCSNetP_TCPSocket.h $
 * $Date: 2017-04-09 23:20:02 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_TCPSOCKET_H__


#include "JCSNetP_SocketAddress.h"


EXTERN_C_BEGIN
NS_JCS_BEGIN

/**
 * @class JCSNetP_TCPSocket
 * @brief TCP socket object class.
 */
class JCS_DLL JCSNetP_TCPSocket
{
private:
	// NOTE(jenchieh): should allow call from this class.
	friend class JCSNetP_SocketUtil;

    // check this socket blocking IO
    bool m_blockingIo = false;

	// socket object.
    SOCKET m_socket;

    // 最大的 file descriptor 數目
    int32 m_max_sd;

    // master file descriptor 清單
    fd_set m_master_set;

    // 給 select() 用的暫時 file descriptor 清單
    fd_set m_working_set;

    // 新接受的 accept() socket descriptor
    int32 m_new_sd;
    

public:
    ~JCSNetP_TCPSocket();
	
	/**
	 * @func Connect
	 * @brief Connect using socket address object handle.
	 * @param inAddress : socket adress object handle.
	 * @return int : execution code.
	 */
	int Connect(
        const JCSNetP_SocketAddress& inAddress, 
        int32 inTimeout = BLOCKSECONDS);

	/**
	 * @func Bind
	 * @brief Bind to the specific route.
	 * @param inToAddress :
	 * @return int : execution code.
	 */
	int Bind(const JCSNetP_SocketAddress& inBindAddress);

	/**
	 * @func Listen
	 * @brief Listen to specific client.
	 * @param inBackLog :
	 * @return int : execution code.
	 */
	int Listen(int inBackLog = SOMAXCONN);

	/**
	 * @func Accept
	 * @brief Accept the connection?
	 * @param inFromAddress : Address object identifier.
	 * @return shared_ptr<JCSNetP_TCPSocket> : Pointer to the client/server accepted.
	 */
	std::shared_ptr<JCSNetP_TCPSocket> Accept(JCSNetP_SocketAddress& inFromAddress);

    /**
     * @func Select
     * @brief Check if there is data coming from another socket. Use for
     * Non-blocking socket.
     * @param inFromAddress : Address object identifier.
     * @return int32 : execution code.
     */
    int32 Select();

	/**
	 * @func Send
	 * @brief Send data to the other side.
	 * @param inData : data to send
	 * @param inLen : length of the data
	 * @return int32 : send byte count.
	 */
	int32 Send(const void* inData, size_t inLen);

	/**
	 * @func Receive
	 * @brief Receive data from the other side.
	 * @param inBuffer : buffere received.
	 * @param inLen : length of the data
	 * @return int32 : receive byte count.
	 */
	int32 Receive(void* inBuffer, size_t inLen);

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
    void SetMaxSd(const int32 val) { this->m_max_sd = val; }

	/* getter */
    SOCKET GetListenSocket() const { return this->m_socket; }
    fd_set GetWorkingSds() const { return this->m_working_set; }
    int32 GetMaxSd() const { return this->m_max_sd; }
    int32 GetNewSd() const { return this->m_new_sd; }
    fd_set GetMasterSet() const { return this->m_master_set; }

private:

	/* Does not allow call from user. */
    JCSNetP_TCPSocket(SOCKET& inSocket);

};

NS_JCS_END
typedef JCSNetP::JCSNetP_TCPSocket JCSNetP_TCPSocket;

typedef std::shared_ptr<JCSNetP::JCSNetP_TCPSocket> JCSNetP_TCPSocketPtr;
template class JCS_DLL std::shared_ptr<JCSNetP_TCPSocket>;

EXTERN_C_END

#endif /* __JCSNETP_TCPSOCKET_H__ */
