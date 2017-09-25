/**
 * $File: JCSNetP_InputMemoryBitStream.cpp $
 * $Date: 2017-04-15 02:28:22 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../../JCSNetP.h"

NS_JCS_BEGIN

JCSNetP_InputMemoryBitStream::JCSNetP_InputMemoryBitStream(
	char* inBuffer,  
	uint32 inBitCount)
	: m_buffer(inBuffer)
	, m_bitCapacity(inBitCount)
	, m_bitHead(0)
	, m_isBufferOwner(false)
{

}

JCSNetP_InputMemoryBitStream::JCSNetP_InputMemoryBitStream(
	const JCSNetP_InputMemoryBitStream& inOther) :
	m_bitCapacity(inOther.m_bitCapacity),
	m_bitHead(inOther.m_bitHead),
	m_isBufferOwner(true)
{
	// allocate buffer of right size
	int byteCount = m_bitCapacity / 8;
	m_buffer = static_cast<char*>(malloc(byteCount));

	// copy
	memcpy(m_buffer, inOther.m_buffer, byteCount);
}

JCSNetP_InputMemoryBitStream::~JCSNetP_InputMemoryBitStream()
{
	if (m_isBufferOwner)
		free(m_buffer);
}

// Read bits from stream.
void JCSNetP_InputMemoryBitStream::ReadBits(uint8& outData, uint32 inBitCount)
{
    uint32 byteOffset = m_bitHead >> 3;
    uint32 bitOffset = m_bitHead & 0x7;

    outData = static_cast< uint8_t >(m_buffer[byteOffset]) >> bitOffset;

    uint32 bitsFreeThisByte = 8 - bitOffset;
    if (bitsFreeThisByte < inBitCount)
    {
        // we need another byte
        outData |= static_cast< uint8_t >(m_buffer[byteOffset + 1]) << bitsFreeThisByte;
    }

    // don't forget a mask so that we only read the bit we wanted...
    outData &= (~(0x00ff << inBitCount));

    m_bitHead += inBitCount;
}

// Read bits from stream.
void JCSNetP_InputMemoryBitStream::ReadBits(void* outData, uint32 inBitCount)
{
    uint8* destByte = reinterpret_cast<uint8*>(outData);

    // write all the bytes
    while (inBitCount > 8)
    {
        ReadBits(*destByte, 8);
        ++destByte;
        inBitCount -= 8;
    }

    // write anything left
    if (inBitCount > 0)
    {
        ReadBits(*destByte, inBitCount);
    }
}

// Read a bytes from stream
void JCSNetP_InputMemoryBitStream::ReadBytes(void* outData, uint32 inByteCount)
{ 
    ReadBits(outData, inByteCount << 3); 
}

// Reset the stream capacity.
void JCSNetP_InputMemoryBitStream::ResetToCapacity(uint32 inByteCapacity)
{ 
    this->m_bitCapacity = inByteCapacity << 3; 
    this->m_bitHead = 0; 
}

// Read the string value out from the stream.
void JCSNetP_InputMemoryBitStream::Read(std::string& inString)
{
    uint32 elementCount;
    Read(elementCount);
    inString.resize(elementCount);

    for (auto& element : inString)
    {
        Read(element);
    }
}

NS_JCS_END
