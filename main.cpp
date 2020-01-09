#include "common_includes.h"
#include "utilities/utilities.h"
#include "interfaces/interfaces.h"
#include "netvar_manager/netvar_manager.h"
#include "render/render.h"
#include "entities/animations/animations.h"
#include "hooks/hooks.h"

#include <thread>
#include <chrono>
#include <stdexcept>

bool unload( void ) {
#ifdef _DEBUG
	n_utilities::unload_console( );
#endif

	g_animations.unload( );

	if ( !n_hooks::unload( ) )
		return false;

	return true;
}

unsigned long __stdcall initialize_cheat( void* argument ) {
	try {
#ifdef _DEBUG
		if ( !n_utilities::initialize_console( "debug" ) )
			std::abort( );

		printf( "initializing cheat... \n" );

		if ( !n_interfaces::initialize( ) )
			throw std::runtime_error( "failed to initialize interfaces" );

		if ( !n_netvar_tree::initialize( ) )
			throw std::runtime_error( "failed to populate netvar tree" );

		if ( !n_render::initialize( ) )
			throw std::runtime_error( "failed to initialize renderer" );

		g_animations.initialize( );

		if ( !n_hooks::initialize( ) )
			throw std::runtime_error( "failed to initialize hooks" );
#endif
	}
	catch ( const std::runtime_error & exception ) {
#ifdef _DEBUG
		printf( exception.what( ) );

		std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
#endif
	}

	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 25 ) );

	if ( !unload( ) )
		return 0;

	FreeLibraryAndExitThread( static_cast< HMODULE >(argument), 0 );

	return 1;
}

int __stdcall DllMain( const HMODULE hinst_dll, const unsigned long reason_for_call, const void* reserved ) {
	if ( hinst_dll )
		DisableThreadLibraryCalls( hinst_dll );

	if ( reason_for_call == 1 ) {
		const auto cheat_thread = CreateThread( 0, 0, initialize_cheat, hinst_dll, 0, 0 );

		if ( !cheat_thread )
			return 0;

		CloseHandle( cheat_thread );
	}

	return 1;
}