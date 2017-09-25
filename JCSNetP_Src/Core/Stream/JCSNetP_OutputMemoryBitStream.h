#ifndef __JCSNETP_OUTPUTMEMORYBITSTREAM_H__
/**
 * $File: JCSNetP_OutputMemoryBitStream.h $
 * $Date: 2017-04-15 02:25:44 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_OUTPUTMEMORYBITSTREAM_H__


NS_JCS_BEGIN

/**
 * @class JCSNetP_OutputMemoryBitStream
 * @brief
 */
class JCS_DLL JCSNetP_OutputMemoryBitStream
{
private:
	char* m_buffer;
	uint32 m_bitHead;
	uint32 m_bitCapacity;

public:
	JCSNetP_OutputMemoryBitStream();
    ~JCSNetP_OutputMemoryBitStream();

	/**
	 * @func WritesBits
	 * @brief Write 8 bits into stream.
	 * @param inData : 8 bits data.
	 * @param inBitCount : size of data.
	 */
	void WriteBits(uint8 inData, uint32 inBitCount);

	/**
	 * @func WritesBits
	 * @brief Write unknown bits into stream.
	 * @param inData : data into stream.
	 * @param inBitCount : size of the data.
	 */
	void WriteBits(const void* inData, uint32 inBitCount);

	/**
	 * @func WriteByes
	 * @brief Write bytes into stream.
	 * @param inData : data write into stream.
	 * @param inBytCount : size of the data write into stream.
	 */
	void WriteBytes(const void* inData, uint32 inByteCount);

	/**
	 * @func Write <T>
	 * @brief Write typename into stream.
	 * @param inData : data write into stream.
	 * @param inBitCount : size of the type passed in.
	 */
	template <typename T>
	void Write(T inData, uint32 inBitCount = sizeof(T) * 8)
	{
		static_assert(std::is_arithmetic<T>::value ||
			std::is_enum<T>::value,
			"Generic Write only supports primitive data types");

		WriteBits(&inData, inBitCount);
	}

	/**
	 * @Write
	 * @brief Write boolean into stream, this will simply be 
	 * translate into 0 or 1.
	 * @param inData : boolean value.
	 */
	void Write(bool inData) { WriteBits(&inData, 1); }

	/** 
	 * @Write
	 * @brief Write the string object into stream.
	 * @param inString : string object write into stream.
	 */
	void Write(const std::string& inString);

    /* setter */

    /* getter */
	const char* GetBufferPtr() const { return this->m_buffer; }
	uint32 GetBitLength() const { return this->m_bitHead; }
	uint32 GetByteLength() const { return (this->m_bitHead + 7) >> 3; }

private:

	/**
	 * @class ReallocBuffer
	 * @brief Allocate memory for this buffer stream.
	 * @param inNewBitCapacity : new bit capacity.
	 */
	void ReallocBuffer(uint32 inNewBitLength);
};

NS_JCS_END
typedef JCSNetP::JCSNetP_OutputMemoryBitStream JCSNetP_OutputMemoryBitStream;

#endif /* __JCSNETP_OUTPUTMEMORYBITSTREAM_H__ */
