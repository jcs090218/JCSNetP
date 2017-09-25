#ifndef __JCSNETP_SOCKETUTIL_H__
/**
 * $File: JCSNetP_SocketUtil.h $
 * $Date: 2017-04-11 22:14:45 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_SOCKETUTIL_H__


NS_JCS_BEGIN


/**
 * @class JCSNetP_SocketUtil
 * @brief Socket utilities put here...
 */
class JCS_DLL JCSNetP_SocketUtil
{
public:
	/**
	 * @func StaticInit
	 * @brief Initialize socket data I/O.
	 */
	static bool	StaticInit();
	/**
	 * @func CleanUp
	 * @brief Clean up socket I/O.
	 */
	static void	CleanUp();

	/**
	 * @func ReportError
	 * @brief Report socket error.
	 * @param inOperationDesc : Error description.
	 */
	static void	ReportError(const char* inOperationDesc);
	/**
	 * @func GetLastError
	 * @brief Get the last error code from OS API.
	 * @return int : Error code operation.
	 */
	static int GetLastError();

    /**
     * @func HasError
     * @brief Check the connection has error?
     * @return bool : true, has error. fasle, no error.
     */
    static bool HasError();

	/**
	 * @func Select
	 * @brief Check if there are new incoming data that has not been 
     * process.
	 * @param inReadSet : 
	 * @param outReadSet : 
	 * @param inWriteSet : 
	 * @param outWriteSet : 
	 * @param inExceptSet : 
	 * @param outExceptSet : 
	 * @return int : error code.
	 */
	static int Select(
		const std::vector<JCSNetP_TCPSocketPtr>* inReadSet,
		std::vector<JCSNetP_TCPSocketPtr>* outReadSet,
		const std::vector<JCSNetP_TCPSocketPtr>* inWriteSet,
		std::vector<JCSNetP_TCPSocketPtr>* outWriteSet,
		const std::vector<JCSNetP_TCPSocketPtr >* inExceptSet,
		std::vector<JCSNetP_TCPSocketPtr>* outExceptSet);


    /** 
     * @func Receive
     * @brief Receive data from this particular socket descriptor.
     * @param inBuffer : buffer to want data to put.
     * @param inLen : data len.
     * @return int32 : byte count data receive.
     */
    static int32 Receive(SOCKET inSocket, void* inBuffer, size_t inLen);

    /**
     * @func CloseSocket
     * @brief Cross platform close socket function.
     */
    static void CloseSocket(SOCKET inSocket);

	/**
	 * @func CreateUDPSocket
	 * @brief Create a UDP socket.
	 * @param inFamily : 
	 * @return JCSNetP_UDPSocketPtr : 
	 */
	static JCSNetP_UDPSocketPtr	CreateUDPSocket(SocketAddressFamily inFamily);

	/**
	 * @func CreateTCPSocket
	 * @brief Create a TCP socket.
	 * @param inFamily :
	 * @return JCSNetP_TCPSocketPtr :
	 */
	static JCSNetP_TCPSocketPtr	CreateTCPSocket(SocketAddressFamily inFamily);

private:

	/**
	 * @func FillSetFromVector
	 * @brief 
	 * @param outSet : 
	 * @param inSockets : 
	 * @param inNaxNfds : 
	 * @return fd_set* : 
	 */
	inline static fd_set* FillSetFromVector(
		fd_set& outSet, 
		const std::vector<JCSNetP_TCPSocketPtr>* inSockets,
		int& ioNaxNfds);

	/**
	 * @func FillVectorFromSet
	 * @brief 
	 * @param outSockets : 
	 * @param inSockets : 
	 * @param inSet : 
	 */
	inline static void FillVectorFromSet(
		std::vector<JCSNetP_TCPSocketPtr>* outSockets,
		const std::vector<JCSNetP_TCPSocketPtr>* inSockets,
		const fd_set& inSet);
};

NS_JCS_END
typedef JCSNetP::JCSNetP_SocketUtil JCSNetP_SocketUtil;


#endif /* __JCSNETP_SOCKETUTIL_H__ */
