#ifndef __JCSNETP_OUTPUTMEMORYSTREAM_H__
/**
 * $File: JCSNetP_OutputMemoryStream.h $
 * $Date: 2017-04-15 01:16:52 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_OUTPUTMEMORYSTREAM_H__

NS_JCS_BEGIN

#define STREAM_ENDIANNESS 0
#define PLATFORM_ENDIANNESS 0

class JCSNetP_LinkingContext;
class ClientObject;

/**
 * @class JCSNetP_OutputMemoryStream
 * @brief Store memory on heap and ready to be read
 * and write or I/O.
 */
class JCS_DLL JCSNetP_OutputMemoryStream
{
private:
	char* m_buffer;
	uint32 m_head;
	uint32 m_capacity;

	JCSNetP_LinkingContext* m_pLinkingContext;

public:
	JCSNetP_OutputMemoryStream();
	~JCSNetP_OutputMemoryStream();

	/**
	 * @func ReallocBuffer
	 * @brief Reallocate the memory ready for buffer input.
	 * @param inNewLength :
	 */
	void ReallocBuffer(uint32 inNewLength);

	/**
	 * @func Write
	 * @brief Write the buffer to stream, store on heap.
	 * @param inData : data input.
	 * @param inByteCount : length of the data input.
	 */
	void Write(const void* inData, size_t inByteCount);

	/** 
	 * @func Write <T>
	 * @brief Write a typename data to stream.
	 * @param inData : typename value.
	 */
	template <typename T> 
	void Write(T inData)
	{
		static_assert(
			std::is_arithmetic<T>::value ||
			std::is_enum<T>::value,
			"Generic Write only supports primitive data types");

		if (STREAM_ENDIANNESS == PLATFORM_ENDIANNESS)
		{
			Write(&inData, sizeof(inData));
		}
		else
		{
			T swappedData = ByteSwap(inData);
			Write(&swappedData, sizeof(swappedData));
		}
	}

	/**
	 * @func Write
	 * @brief Write the vector data to stream.
	 * @param inIntVector
	 */
	void Write(const std::vector<int>& inIntVector);

	/**
	 * @func Write <T>
	 * @brief Write the vector data type into buffer stream.
	 * @param inVector : vector<T> to write into buffer stream.
	 */
	template <typename T>
	void Write(const std::vector<T>& inVector)
	{
		uint32 elementCount = inVector.size();
		Write(elementCount);
		for (const T& element : inVector)
			Write(element);
	}

	/**
	 * @func Write
	 * @brief Write the string object to buffer stream.
	 * @param inString : string object to write into buffer.
	 */
	void Write(const std::string& inString);

	/**
	 * @func Write
	 * @brief Store network Id and store it in the server list.
	 * @param inClientObject : client object passed.
	 */
	void Write(const ClientObject* inClientObject);

    /* setter */

    /* getter */
	const char* GetBufferPtr() const { return this->m_buffer; }
	uint32 GetLength() const { return this->m_head; }
};

NS_JCS_END
typedef JCSNetP::JCSNetP_OutputMemoryStream JCSNetP_OutputMemoryStream;

#endif /* __JCSNETP_OUTPUTMEMORYSTREAM_H__ */
