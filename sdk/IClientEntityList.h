#pragma once

#include "../utilities/utilities.h"
#include "UtlVector.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/icliententitylist.h

class C_BaseEntity;
class CBaseHandle;

class IClientEntityListener {
public:
	virtual void on_entity_created( C_BaseEntity* ent ) { }
	virtual void on_entity_deleted( C_BaseEntity* ent ) { }
};

class IClientEntityList {
public:
	// get IClientNetworkable interface for specified entity
	virtual void* get_client_networkable( int ent_num ) = 0;
	virtual void* get_client_networkable_from_handle( CBaseHandle ent ) = 0;
	virtual void* get_client_unknown_from_handle( CBaseHandle ent ) = 0;

	// note: this function is only a convenience wrapper.
	// it returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual void* get_client_entity( int ent_num ) = 0;
	virtual void* get_client_entity_from_handle( CBaseHandle ent ) = 0;

	// returns number of entities currently in use
	virtual int	number_of_entities( bool include_non_networkable ) = 0;

	// returns highest index actually used
	virtual int	get_highest_entity_index( void ) = 0;

	// sizes entity list to specified size
	virtual void set_max_entities( int max_ents ) = 0;
	virtual int	get_max_entities( ) = 0;

	void add_listener_entity( IClientEntityListener* listener ) {
		entity_listeners.add_to_tail( listener );
	}

	void remove_listener_entity( IClientEntityListener* listener ) {
		entity_listeners.find_and_remove( listener );
	}

private:
	CUtlVector< IClientEntityListener* > entity_listeners;
};