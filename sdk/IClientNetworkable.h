#pragma once

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/iclientnetworkable.h

class ClientClass;
class bf_read;

class IClientNetworkable {
public:
	// gets at the containing class...
	virtual void* get_client_unknown( ) = 0;

	// called by the engine when the server deletes the entity.
	virtual void release( ) = 0;

	// supplied automatically by the IMPLEMENT_CLIENTCLASS macros.
	virtual ClientClass* get_client_class( ) = 0;

	// this tells the entity what the server says for ShouldTransmit on this entity.
	// note: This used to be EntityEnteredPVS/EntityRemainedInPVS/EntityLeftPVS.
	virtual void notify_should_transmit( int state ) = 0;

	//
	// not for entity writers
	//
	// in 90% of the cases, you should hook OnPreDataChanged/OnDataChanged instead of 
	// PreDataUpdate/PostDataUpdate.
	//
	// rhe DataChanged events are only called once per frame whereas Pre/PostDataUpdate
	// are called once per packet (and sometimes multiple times per frame).
	//
	// OnDataChanged is called during simulation where entity origins are correct and 
	// attachments can be used. whereas PostDataUpdate is called while parsing packets
	// so attachments and other entity origins may not be valid yet.
	//
	virtual void on_pre_data_changed( int update_type ) = 0;
	virtual void on_data_changed( int update_type ) = 0;

	// called when data is being updated across the network.
	// only low-level entities should need to know about these.
	virtual void pre_data_update( int update_type ) = 0;
	virtual void post_data_update( int update_type ) = 0;

	virtual void __unkn( ) = 0;

	// objects become dormant on the client if they leave the PVS on the server.
	virtual bool is_dormant( ) = 0;

	// ent Index is the server handle used to reference this entity.
	// if the index is < 0, that indicates the entity is not known to the server
	virtual int ent_index( ) const = 0;

	// server to client entity message received
	virtual void receive_message( int classID, bf_read& msg ) = 0;

	// get the base pointer to the networked data that GetClientClass->m_pRecvTable starts at.
	// (this is usually just the "this" pointer).
	virtual void* get_data_table_base_ptr( ) = 0;

	// tells the entity that it's about to be destroyed due to the client receiving
	// an uncompressed update that's caused it to destroy all entities & recreate them.
	virtual void set_destroyed_on_recreate_entities( ) = 0;
};