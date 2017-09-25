#ifndef __JCSNETP_LINKINGCONTEXT_H__
/**
 * $File: JCSNetP_LinkingContext.h $
 * $Date: 2017-04-15 02:05:26 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __JCSNETP_LINKINGCONTEXT_H__


NS_JCS_BEGIN


class ClientObject;


/**
 * @class JCSNetP_LinkingContext
 * @brief Handle each client or overlap client object.
 */
class JCSNetP_LinkingContext
{
private:
	std::unordered_map<uint32, ClientObject*> m_networkIdToClientObjectMap;
	std::unordered_map<const ClientObject*, uint32> m_clientObjectToNetworkIdMap;

	uint32 m_nextNetworkId;

public:
	JCSNetP_LinkingContext();
	~JCSNetP_LinkingContext();

	/**
	 * @func GetNetworkId
	 * @brief Get the network id by passing the client object.
	 * @param inClientObject : client object use to find out the network id.
	 * @param inShouldCreateIfNotFound : boolean to trigger create the new network id.
	 * @return uint32 : network uniqure Id.
	 */
	uint32 GetNetworkId(ClientObject* inClientObject, bool inShouldCreateIfNotFound);

	/**
	 * @func GetClientObject
	 * @brief Find out the client object by network unique id.
	 * @param inNetworkId : network id to find the client object.
	 * @return ClientObject* : 
	 */
	ClientObject* GetClientObject(uint32 inNetworkId) const;

	/**
	 * @func AddClientObject
	 * @brief Add the client object to the server list.
	 * @param inClientObject : client object to be added.
	 * @param inNetwordId : network uniqure id.
	 */
	void AddClientObject(ClientObject* inClientObject, uint32 inNetworkId);

	/**
	 * @func RemoveClientObject
	 * @brief Remove the client object from the server list.
	 * @param inClientObject : client object to be remove from the list.
	 */
	void RemoveClientObject(ClientObject* inClientObject);

	/* setter */

	/* getter */

};

NS_JCS_END

typedef JCSNetP::JCSNetP_LinkingContext JCSNetP_LinkingContext;

#endif /* __JCSNETP_LINKINGCONTEXT_H__ */
