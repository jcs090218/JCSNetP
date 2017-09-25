#ifndef __JCSNETP_INPUTMEMORYBITSTREAM_H__
/**
 * $File: JCSNetP_InputMemoryBitStream.h $
 * $Date: 2017-04-15 02:28:21 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_INPUTMEMORYBITSTREAM_H__


NS_JCS_BEGIN

/**
 * @class JCSNetP_InputMemoryBitStream
 * @brief 
 */
class JCS_DLL JCSNetP_InputMemoryBitStream
{
private:
	char*  m_buffer;
	uint32 m_bitHead;
	uint32 m_bitCapacity;
	bool   m_isBufferOwner;

public:
    /**
     * @func JCSNetP_InputMemoryBitStream
     * @brief Constructor
     * @param inBuffer : buffer to be read.
     * @param inBitCount : size of stream.
     * @return 'JCSNetP_InputMemoryBitStream' object
     */
	JCSNetP_InputMemoryBitStream(char* inBuffer, uint32 inBitCount);
    /**
     * @func JCSNetP_InputMemoryBitStream
     * @brief Constructor
     * @param inOther : set new stream to the other stream.
     * @return 'JCSNetP_InputMemoryBitStream' object
     */
	JCSNetP_InputMemoryBitStream(const JCSNetP_InputMemoryBitStream& inOther);
	~JCSNetP_InputMemoryBitStream();

    /**
     * @func ReadBits
     * @brief Read bits from stream.
     * @param outData : get data out from stream
     * @param inBitCount : size of bit to read.
     */
	void ReadBits(uint8& outData, uint32 inBitCount);

    /**
     * @func ReadBits
     * @brief Read bits from stream.
     * @param outData : read data out from stream.
     * @param inBitCount : size of bits to read.
     */
	void ReadBits(void* outData, uint32 inBitCount);

    /**
     * @func ReadBytes
     * @brief Read a bytes from stream
     * @param outData : read data out from stream.
     * @param inByteCount : size of bytes to read.
     */
	void ReadBytes(void* outData, uint32 inByteCount);

    /**
     * @func Read
     * @brief Read the typename value into stream.
     * @param inData : data value.
     * @param inBitCount : size of the data.
     */
    template <typename T>
    void Read(T& inData, uint32 inBitCount = sizeof(T) * 8)
    {
        static_assert(std::is_arithmetic< T >::value ||
            std::is_enum< T >::value,
            "Generic Read only supports primitive data types");

        ReadBits(&inData, inBitCount);
    }

    /**
     * @func Read
     * @brief Read the unsigned integer 32bit out from stream.
     * @param outData : read data out from stream.
     * @param inBitCount : size of the data.
     */
    void Read(uint32& outData, uint32 inBitCount = 32) { ReadBits(&outData, inBitCount); }

    /**
     * @func Read
     * @brief Read the integer 32bit out from stream.
     * @param outData : read data out from stream.
     * @param inBitCount : size of the data.
     */
    void Read(int& outData, uint32 inBitCount = 32) { ReadBits(&outData, inBitCount); }

    /**
     * @func Read
     * @brief Read the float 32bit out from stream.
     * @param outData : read data out from stream.
     * @param inBitCount : size of the data.
     */
    void Read(float& outData) { ReadBits(&outData, 32); }

    /**
     * @func Read
     * @brief Read the unsigned integer 16bit out from stream.
     * @param outData : read data out from stream.
     * @param inBitCount : size of the data.
     */
    void Read(uint16& outData, uint32 inBitCount = 16) { ReadBits(&outData, inBitCount); }

    /**
     * @func Read
     * @brief Read the integer 16bit out from stream.
     * @param outData : read data out from stream.
     * @param inBitCount : size of the data.
     */
    void Read(int16& outData, uint32 inBitCount = 16) { ReadBits(&outData, inBitCount); }

    /**
     * @func Read
     * @brief Read the unsigned integer 8bit out from stream.
     * @param outData : read data out from stream.
     * @param inBitCount : size of the data.
     */
    void Read(uint8& outData, uint32 inBitCount = 8) { ReadBits(&outData, inBitCount); }

    /**
     * @func Read
     * @brief Read the bool 1bit out from stream.
     * @param outData : read data out from stream.
     * @param inBitCount : size of the data.
     */
    void Read(bool& outData) { ReadBits(&outData, 1); }

    /**
     * @func Read
     * @brief Read the string value out from the stream.
     * @param inString : string pointer to point.
     */
    void Read(std::string& inString);

    /**
     * @func ResetToCapacity
     * @brief Reset the stream capacity.
     * @param inByteCapacity : target byte compacity in stream.
     */
    void ResetToCapacity(uint32 inByteCapacity);

	/* setter */

	/* getter */
	const char* GetBufferPtr() const { return m_buffer; }
	uint32 GetRemainingBitCount() const { return m_bitCapacity - m_bitHead; }
};

NS_JCS_END
typedef JCSNetP::JCSNetP_InputMemoryBitStream JCSNetP_InputMemoryBitStream;

#endif /* __JCSNETP_INPUTMEMORYBITSTREAM_H__ */
