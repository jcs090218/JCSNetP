/**
 * $File: JCSNetP_InputMemoryStream.cpp $
 * $Date: 2017-04-15 01:48:18 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../../JCSNetP.h"


NS_JCS_BEGIN

JCSNetP_InputMemoryStream::JCSNetP_InputMemoryStream(
	char* inBuffer, 
	uint32 inByteCount)
	: m_buffer(inBuffer)
	, m_capacity(inByteCount)
	, m_head(0)
	, m_pLinkingContext(nullptr)
{

}

JCSNetP_InputMemoryStream::~JCSNetP_InputMemoryStream()
{
	std::free(m_buffer);
}

uint32 JCSNetP_InputMemoryStream::GetRemainingDataSize() const
{ 
	return this->m_capacity - this->m_head;
}

void JCSNetP_InputMemoryStream::Read(void* outData, uint32 inByteCount)
{
	uint32 resultHead = this->m_head + inByteCount;
	if (resultHead > m_capacity)
	{
		//handle error, no data to read!
		//...
	}

	std::memcpy(outData, this->m_buffer + this->m_head, inByteCount);

	this->m_head = resultHead;
}

// Read the client object out from the memory stream.
void JCSNetP_InputMemoryStream::Read(ClientObject*& outClientObject)
{
	uint32 networkId;
	Read(networkId);

	// get the value.
	outClientObject = m_pLinkingContext->GetClientObject(networkId);
}

NS_JCS_END
