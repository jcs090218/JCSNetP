#ifndef __JCSNETP_INPUTMEMORYSTREAM_H__
/**
 * $File: JCSNetP_InputMemoryStream.h $
 * $Date: 2017-04-15 01:48:21 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_INPUTMEMORYSTREAM_H__


NS_JCS_BEGIN

class JCSNetP_LinkingContext;
class ClientObject;

/** 
 * @class JCSNetP_InputMemoryStream
 * @brief Store memory on heap and ready to be read
 * and write or I/O.
 */
class JCS_DLL JCSNetP_InputMemoryStream
{
private:
	char* m_buffer;
	uint32 m_head;
	uint32 m_capacity;

	JCSNetP_LinkingContext* m_pLinkingContext;

public:
	/**
	 * @func JCSNetP_InputMemoryStream
	 * @brief Constructor
	 * @param inBuffer : buffer read.
	 * @param inByteCount : buffer length.
	 */
    JCSNetP_InputMemoryStream(char* inBuffer, uint32 inByteCount);
    ~JCSNetP_InputMemoryStream();

	/**
	 * @func Read
	 * @brief 
	 * @param outData : 
	 * @param inByteCount : 
	 */
	void Read(void* outData, uint32 inByteCount);

	/**
	 * @func Read <T>
	 * @brief Read the T type data.
	 * @param outData : data going to read out.
	 */
	template <typename T> 
	void Read(T& outData)
	{
		static_assert(std::is_arithmetic< T >::value ||
			std::is_enum< T >::value,
			"Generic Read only supports primitive data types");
		Read(&outData, sizeof(outData));
	}

	/**
	 * @func Read <T>
	 * @brief Read the vector<T> to memory stream.
	 * @param outVector : vector buffer memory to output.
	 */
	template <typename T>
	void Read(std::vector<T>& outVector)
	{
		size_t elementCount;
		Read(elementCount);
		outVector.resize(elementCount);

		for (const T& element : outVector)
			Read(element);
	}

	/**
	 * @func GetRemainingDataSize
	 * @brief Get the remaining data size in buffer stream.
	 */
	uint32 GetRemainingDataSize() const;

	/** 
	 * @func Read
	 * @brief Read the client object out from the memory stream.
	 * @param outClientObject : client object read and store the value here.
	 */
	void Read(ClientObject*& outClientObject);

    /* setter */
    
    /* getter */

};

NS_JCS_END

#endif /* __JCSNETP_INPUTMEMORYSTREAM_H__ */
