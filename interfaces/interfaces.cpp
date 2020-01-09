#include "interfaces.h"

#include "../utilities/utilities.h"

#include <cstdint>

namespace n_interfaces {
	IBaseClientDLL* client = nullptr;
	IClientMode* client_mode = nullptr;
	IVEngineClient* engine = nullptr;
	IClientEntityList* entity_list = nullptr;
	IVEngineVGui* engine_vgui = nullptr;
	ISurface* surface = nullptr;
	CGlobalVarsBase* global_vars_base = nullptr;
	IPrediction* prediction = nullptr;
	IMoveHelper* move_helper = nullptr;
	IGameMovement* game_movement = nullptr;
	IWeaponSystem* weapon_system = nullptr;
	IMDLCache* model_cache = nullptr;
	IVModelRender* model_render = nullptr;
	IMaterialSystem* material_system = nullptr;
	IVModelInfo* model_info = nullptr;
	IVDebugOverlay* debug_overlay = nullptr;

	bool initialize( void ) {
		client = reinterpret_cast< IBaseClientDLL* >( n_utilities::capture_interface( "client_panorama.dll", "VClient018" ) );

		if ( !client )
			return false;

		client_mode = **reinterpret_cast< IClientMode*** >( ( *reinterpret_cast< std::uintptr_t** >( client ) )[ 10 ] + 5 );

		if ( !client_mode )
			return false;

		engine = reinterpret_cast< IVEngineClient* >( n_utilities::capture_interface( "engine.dll", "VEngineClient014" ) );

		if ( !engine )
			return false;

		entity_list = reinterpret_cast< IClientEntityList* >( n_utilities::capture_interface( "client_panorama.dll", "VClientEntityList003" ) );

		if ( !entity_list )
			return false;

		engine_vgui = reinterpret_cast< IVEngineVGui* >( n_utilities::capture_interface( "engine.dll", "VEngineVGui001" ) );

		if ( !engine_vgui )
			return false;

		surface = reinterpret_cast< ISurface* >( n_utilities::capture_interface( "vguimatsurface.dll", "VGUI_Surface031" ) );

		if ( !surface )
			return false;

		global_vars_base = **reinterpret_cast< CGlobalVarsBase*** >( ( *reinterpret_cast< std::uintptr_t** >( client ) )[ 11 ] + 10 );

		if ( !global_vars_base )
			return false;

		prediction = reinterpret_cast< IPrediction* >( n_utilities::capture_interface( "client_panorama.dll", "VClientPrediction001" ) );

		if ( !prediction )
			return false;

		move_helper = **reinterpret_cast< IMoveHelper*** >( n_utilities::find_pattern( "client_panorama.dll", "8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01" ) + 0x2 );

		if ( !move_helper )
			return false;

		game_movement = reinterpret_cast< IGameMovement* >( n_utilities::capture_interface( "client_panorama.dll", "GameMovement001" ) );

		if ( !game_movement )
			return false;

		weapon_system = *reinterpret_cast< IWeaponSystem** >( n_utilities::find_pattern( "client_panorama.dll", "8B 35 ? ? ? ? FF 10 0F B7 C0" ) + 0x2 );

		if ( !weapon_system )
			return false;

		model_cache = reinterpret_cast< IMDLCache* >( n_utilities::capture_interface( "datacache.dll", "MDLCache004" ) );

		if ( !model_cache )
			return false;

		model_render = reinterpret_cast< IVModelRender* >( n_utilities::capture_interface( "engine.dll", "VEngineModel016" ) );

		if ( !model_render )
			return false;

		material_system = reinterpret_cast< IMaterialSystem* >( n_utilities::capture_interface( "materialsystem.dll", "VMaterialSystem080" ) );

		if ( !material_system )
			return false;

		model_info = reinterpret_cast< IVModelInfo* >( n_utilities::capture_interface( "engine.dll", "VModelInfoClient004" ) );

		if ( !model_info )
			return false;

		debug_overlay = reinterpret_cast< IVDebugOverlay* >( n_utilities::capture_interface( "engine.dll", "VDebugOverlay004" ) );

		if ( !debug_overlay )
			return false;

		return true;
	}
}