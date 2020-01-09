#include "../hooks.h"

#include "../../features/engine_prediction.h"

#include <string>

namespace n_hooks {
	bool __fastcall n_functions::CreateMove( std::uintptr_t ecx, std::uintptr_t edx, float input_sample_time, CUserCmd* cmd ) {
		if ( !cmd || !cmd->command_number )
			return false;

		C_CSPlayer* local_player = reinterpret_cast< C_CSPlayer* >( n_interfaces::entity_list->get_client_entity( n_interfaces::engine->get_local_player( ) ) );

		if ( !local_player || !local_player->is_alive( ) )
			return false;

		cmd->buttons |= ( 1 << 22 ); // IN_BULLRUSH

		n_engine_prediction::initialize( local_player, cmd ); {

		}
		n_engine_prediction::unload( local_player );

		return false;
	}
}