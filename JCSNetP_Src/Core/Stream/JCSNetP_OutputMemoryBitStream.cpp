/**
 * $File: JCSNetP_OutputMemoryBitStream.cpp $
 * $Date: 2017-04-15 02:25:43 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../../JCSNetP.h"


NS_JCS_BEGIN

JCSNetP_OutputMemoryBitStream::JCSNetP_OutputMemoryBitStream()
	: m_bitHead(0)
	, m_buffer(nullptr)
{
	ReallocBuffer(1500 * 8);
}

JCSNetP_OutputMemoryBitStream::~JCSNetP_OutputMemoryBitStream()
{
	std::free(this->m_buffer);
}

// Write 8 bits into stream.
void JCSNetP_OutputMemoryBitStream::WriteBits(
	uint8 inData, 
	uint32 inBitCount)
{
    uint32 nextBitHead = m_bitHead + static_cast<uint32>(inBitCount);

    if (nextBitHead > m_bitCapacity)
    {
        ReallocBuffer(std::max(m_bitCapacity * 2, nextBitHead));
    }

    // calculate the byteOffset into our buffer
    // by dividing the head by 8
    // and the bitOffset by taking the last 3 bits
    uint32 byteOffset = m_bitHead >> 3;
    uint32 bitOffset = m_bitHead & 0x7;

    uint8 currentMask = ~(0xff << bitOffset);
    m_buffer[byteOffset] = (m_buffer[byteOffset] & currentMask) | (inData << bitOffset);

    // calculate how many bits were not yet used in
    // our target byte in the buffer
    uint32 bitsFreeThisByte = 8 - bitOffset;

    // if we needed more than that, carry to the next byte
    if (bitsFreeThisByte < inBitCount)
    {
        // we need another byte
        m_buffer[byteOffset + 1] = inData >> bitsFreeThisByte;
    }

    m_bitHead = nextBitHead;
}

// 
void JCSNetP_OutputMemoryBitStream::WriteBits(
	const void* inData, 
	uint32 inBitCount)
{
    const char* srcByte = static_cast<const char*>(inData);

    // write all the bytes
    while (inBitCount > 8)
    {
        WriteBits(*srcByte, 8);
        ++srcByte;
        inBitCount -= 8;
    }

    // write anything left
    if (inBitCount > 0)
    {
        WriteBits(*srcByte, inBitCount);
    }
}

// Write bytes into stream.
void JCSNetP_OutputMemoryBitStream::WriteBytes(
	const void* inData, 
	uint32 inByteCount)
{ 
	WriteBits(inData, inByteCount << 3); 
}

// Write the string object into stream.
void JCSNetP_OutputMemoryBitStream::Write(const std::string& inString)
{
	uint32 elementCount = static_cast<uint32>(inString.size());

	Write(elementCount);

	for (const auto& element : inString)
		Write(element);
}

// Allocate memory for this buffer stream.
void JCSNetP_OutputMemoryBitStream::ReallocBuffer(uint32 inNewBitLength)
{
	if (m_buffer == nullptr)
	{
		//just need to memset on first allocation
		m_buffer = static_cast<char*>(std::malloc(inNewBitLength >> 3));
		memset(m_buffer, 0, inNewBitLength >> 3);
	}
	else
	{
		//need to memset, then copy the buffer
		char* tempBuffer = static_cast<char*>(std::malloc(inNewBitLength >> 3));
		memset(tempBuffer, 0, inNewBitLength >> 3);
		memcpy(tempBuffer, m_buffer, m_bitCapacity >> 3);
		std::free(m_buffer);
		m_buffer = tempBuffer;
	}

	//handle realloc failure
	//...
	m_bitCapacity = inNewBitLength;
}

NS_JCS_END
