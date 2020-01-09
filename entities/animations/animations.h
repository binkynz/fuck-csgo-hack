#pragma once

#include "../../hooks/hooks.h"

#include <array>

struct entity_container_t {
	entity_container_t( ) { }
	entity_container_t( C_BaseEntity* ent ) {
		index = ent->networkable( )->ent_index( );

		vmt = std::make_unique< c_vmt >( );
		renderable = std::make_unique< c_vmt >( );

		if ( vmt->initialize( ent ) ) {

		}

		if ( renderable->initialize( ent->renderable( ) ) ) {
			renderable->hook_function( 13, n_hooks::n_functions::SetupBones );
		}

		hooked = true;
	}

	std::unique_ptr< c_vmt > vmt;
	std::unique_ptr< c_vmt > renderable;
	int index;
	bool hooked = false;
};

class c_animations : public IClientEntityListener {
public:
	void on_entity_created( C_BaseEntity* ent ) override;
	void on_entity_deleted( C_BaseEntity* ent ) override;

	void initialize( void );
	void unload( void );

	std::array<entity_container_t, 65> track;
};

extern c_animations g_animations;