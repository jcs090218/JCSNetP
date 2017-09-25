/**
 * $File: JCSNetP_LinkingContext.cpp $
 * $Date: 2017-04-15 02:05:23 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */

#include "../JCSNetP.h"


NS_JCS_BEGIN

JCSNetP_LinkingContext::JCSNetP_LinkingContext()
	: m_nextNetworkId(1)
{

}

JCSNetP_LinkingContext::~JCSNetP_LinkingContext()
{

}

// 
uint32 JCSNetP_LinkingContext::GetNetworkId(ClientObject* inClientObject, bool inShouldCreateIfNotFound)
{
	auto it = m_clientObjectToNetworkIdMap.find(inClientObject);
	if (it != m_clientObjectToNetworkIdMap.end())
	{
		return it->second;
	}
	else if (inShouldCreateIfNotFound)
	{
		uint32 newNetworkId = ++m_nextNetworkId;
		AddClientObject(inClientObject, newNetworkId);
		return newNetworkId;
	}
	else
	{
		return 0;
	}
}

// Find out the client object by network unique id.
ClientObject* JCSNetP_LinkingContext::GetClientObject(uint32 inNetworkId) const
{
	auto it = m_networkIdToClientObjectMap.find(inNetworkId);
	if (it != m_networkIdToClientObjectMap.end())
	{
		return it->second;
	}
	else
	{
		return nullptr;
	}
}

// 
void JCSNetP_LinkingContext::AddClientObject(ClientObject* inClientObject, uint32 inNetworkId)
{
	m_networkIdToClientObjectMap[inNetworkId] = inClientObject;
	m_clientObjectToNetworkIdMap[inClientObject] = inNetworkId;
}

// Remove the client object from the server list.
void JCSNetP_LinkingContext::RemoveClientObject(ClientObject *inClientObject)
{
	uint32_t networkId = m_clientObjectToNetworkIdMap[inClientObject];
	m_clientObjectToNetworkIdMap.erase(inClientObject);
	m_networkIdToClientObjectMap.erase(networkId);
}

NS_JCS_END
