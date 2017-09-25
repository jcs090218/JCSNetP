/**
 * $File: JCSNetP_OutputMemoryStream.cpp $
 * $Date: 2017-04-15 01:16:54 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../../JCSNetP.h"


NS_JCS_BEGIN

JCSNetP_OutputMemoryStream::JCSNetP_OutputMemoryStream()
	: m_pLinkingContext(nullptr)
{
	ReallocBuffer(32);
}

JCSNetP_OutputMemoryStream::~JCSNetP_OutputMemoryStream()
{
	std::free(m_buffer);
}

// Reallocate the memory ready for buffer input.
void JCSNetP_OutputMemoryStream::ReallocBuffer(uint32 inNewLength)
{
	m_buffer = static_cast<char*>(std::realloc(m_buffer, inNewLength));
	//handle realloc failure
	//...
	m_capacity = inNewLength;
}

// Write the buffer to stream, store on heap.
void JCSNetP_OutputMemoryStream::Write(
	const void* inData, 
	size_t inByteCount)
{
	//make sure we have space...
	uint32 resultHead = m_head + static_cast< uint32_t >(inByteCount);
	if (resultHead > m_capacity)
	{
		ReallocBuffer(std::max(m_capacity * 2, resultHead));
	}

	//copy into buffer at head
	std::memcpy(m_buffer + m_head, inData, inByteCount);

	//increment head for next write
	m_head = resultHead;
}

// Write the vector data to stream.
void JCSNetP_OutputMemoryStream::Write(const std::vector<int>& inIntVector)
{
	size_t elementCount = inIntVector.size();
	Write(elementCount);
	Write(inIntVector.data(), elementCount * sizeof(int));
}

// Write the string object to buffer stream.
void JCSNetP_OutputMemoryStream::Write(const std::string& inString)
{
	size_t elementCount = inString.size();
	Write(elementCount);
	Write(inString.data(), elementCount * sizeof(char));
}

// Store network Id and store it in the server list.
void JCSNetP_OutputMemoryStream::Write(const ClientObject* inClientObject)
{
	uint32 networkId = m_pLinkingContext->GetNetworkId(
		const_cast<ClientObject* >(inClientObject),
		false);
	Write(networkId);
}

NS_JCS_END
