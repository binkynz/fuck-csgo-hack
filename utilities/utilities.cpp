#include "utilities.h"

#include <stdio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <psapi.h>

namespace n_utilities {
	bool initialize_console( const char* window_name ) {
		if ( !AllocConsole( ) )
			return false;

		const auto in = freopen_s( reinterpret_cast< FILE** >(stdin), "CONIN$", "r", stdin );

		if ( in != 0 )
			return false;

		const auto out = freopen_s( reinterpret_cast< FILE** >(stdout), "CONOUT$", "w", stdout );

		if ( out != 0 )
			return false;

		if ( !SetConsoleTitleA( window_name ) )
			return false;

		return true;
	}

	bool unload_console( void ) {
		const auto in = fclose( reinterpret_cast< FILE* >(stdin) );

		if ( in != 0 )
			return false;

		const auto out = fclose( reinterpret_cast< FILE* >(stdout) );

		if ( out != 0 )
			return false;

		if ( !FreeConsole( ) )
			return false;

		return true;
	}

	void* capture_interface( const char* module_name, const char* interface_name ) {
		const auto module_handle = GetModuleHandleA( module_name );

		if ( !module_handle )
			return nullptr;

		const auto create_interface_fn = reinterpret_cast< void* (*)(const char*, int*) >(GetProcAddress( module_handle, "CreateInterface" ));

		if ( !create_interface_fn )
			return nullptr;

		const auto interface_address = create_interface_fn( interface_name, nullptr );

		if ( !interface_address )
			return nullptr;

#ifdef _DEBUG
		printf( "found %s at 0x%p\n", interface_name, interface_address );
#endif
		return interface_address;
	}

	std::uint8_t* find_pattern( const char* module_name, const char* signature ) {
		const auto module_handle = GetModuleHandleA( module_name );

		if ( !module_handle )
			return nullptr;

		static auto pattern_to_byte = [ ]( const char* pattern ) {
			auto bytes = std::vector< int >{ };
			auto start = const_cast< char* >(pattern);
			auto end = const_cast< char* >(pattern) + std::strlen( pattern );

			for ( auto current = start; current < end; ++current ) {
				if ( *current == '?' ) {
					++current;

					if ( *current == '?' )
						++current;

					bytes.push_back( -1 );
				}
				else {
					bytes.push_back( std::strtoul( current, &current, 16 ) );
				}
			}
			return bytes;
		};

		auto dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >(module_handle);
		auto nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS >(reinterpret_cast< std::uint8_t* >(module_handle) + dos_header->e_lfanew);

		auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
		auto pattern_bytes = pattern_to_byte( signature );
		auto scan_bytes = reinterpret_cast< std::uint8_t* >(module_handle);

		auto s = pattern_bytes.size( );
		auto d = pattern_bytes.data( );

		for ( auto i = 0ul; i < size_of_image - s; ++i ) {
			bool found = true;

			for ( auto j = 0ul; j < s; ++j ) {
				if ( scan_bytes[ i + j ] != d[ j ] && d[ j ] != -1 ) {
					found = false;
					break;
				}
			}

			if ( found )
				return &scan_bytes[ i ];
		}

		return nullptr;
	}
}