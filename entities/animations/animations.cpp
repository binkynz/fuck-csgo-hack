#include "animations.h"

void c_animations::initialize( void ) {
	n_interfaces::entity_list->add_listener_entity( this );
}

void c_animations::unload( void ) {
	n_interfaces::entity_list->remove_listener_entity( this );

	for ( int index = 1; index <= 64; index++ ) {
		if ( track.at( index ).hooked ) {
			track.at( index ).vmt->unhook( );
			track.at( index ).renderable->unhook( );
		}
	}
}

void c_animations::on_entity_created( C_BaseEntity* entity ) {
	if ( !entity )
		return;

	int index = entity->networkable( )->ent_index( );

	if ( index <= 0 )
		return;

	ClientClass* client_class = entity->networkable( )->get_client_class( );

	if ( !client_class )
		return;

	switch ( client_class->class_id ) {
	case 40:
		if ( !track.at( index ).hooked ) // prevents double hooking
			track.at( index ) = entity_container_t( entity );

		break;

	default:

		break;
	}
}

void c_animations::on_entity_deleted( C_BaseEntity* entity ) {
	if ( !entity )
		return;

	int index = entity->networkable( )->ent_index( );

	if ( index <= 0 )
		return;

	auto it = std::find_if( track.begin( ), track.end( ), [ & ]( const entity_container_t& data ) {
		return data.index == index;
		} );

	if ( it == track.end( ) )
		return;

	if ( track.at( it->index ).hooked ) {
		track.at( it->index ).vmt->unhook( );
		track.at( it->index ).renderable->unhook( );
		track.at( it->index ).hooked = false;
	}
}

c_animations g_animations;