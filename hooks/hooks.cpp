#include "hooks.h"

#include "../interfaces/interfaces.h"

namespace n_hooks {
	std::unique_ptr< c_vmt > client_mode;
	std::unique_ptr< c_vmt > engine_vgui;
	std::unique_ptr< c_vmt > bsp_query;
	std::unique_ptr< c_vmt > model_render;

	bool initialize( void ) {
		client_mode = std::make_unique< c_vmt >( );
		engine_vgui = std::make_unique< c_vmt >( );
		bsp_query = std::make_unique< c_vmt >( );
		model_render = std::make_unique< c_vmt >( );

		/* IClientMode */
		if ( !client_mode->initialize( n_interfaces::client_mode ) )
			return false;

		if ( !client_mode->hook_function( 24, n_functions::CreateMove ) )
			return false;

		if ( !client_mode->hook_function( 35, n_functions::GetViewModelFOV ) )
			return false;

		/* IVEngineVGui */
		if ( !engine_vgui->initialize( n_interfaces::engine_vgui ) )
			return false;

		if ( !engine_vgui->hook_function( 14, n_functions::Paint ) )
			return false;

		/* ISpatialQuery */
		if ( !bsp_query->initialize( n_interfaces::engine->get_bsp_tree_query( ) ) )
			return false;

		if ( !bsp_query->hook_function( 6, n_functions::ListLeavesInBox ) )
			return false;

		/* IVModelRender */
		if ( !model_render->initialize( n_interfaces::model_render ) )
			return false;

		if ( !model_render->hook_function( 21, n_functions::DrawModelExecute ) )
			return false;

		return true;
	}

	bool unload( void ) {
		/* IClientMode */
		if ( !client_mode->unhook( ) )
			return false;

		/* IVEngineVGui */
		if ( !engine_vgui->unhook( ) )
			return false;

		/* ISpatialQuery */
		if ( !bsp_query->unhook( ) )
			return false;

		/* IVModelRender */
		if ( !model_render->unhook( ) )
			return false;

		return true;
	}
}