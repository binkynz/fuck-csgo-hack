#pragma once
#include "../common_includes.h"

#include <cstdint>
#include <memory>

class c_vmt {
public:
	// class initializer
	c_vmt( );

	// sets up hook and replaces the vtable with new one
	bool initialize( void* base );

	// hook a specific index ( all index are shifted by one because of rtti )
	bool hook_function( const std::uint16_t index, void* function );

	// unhook specific index
	bool unhook_function( const std::uint16_t index );

	// restore old vtables ( unhook all function )
	bool unhook( void );

	// get a pointer to the original function given an index
	template <typename T = void*> T get_original_function( const std::uint16_t index ) {
		return reinterpret_cast< T >(original_vmt[ index ]);
	}

private:
	// calculates the length of the table
	std::uint32_t get_vtable_length( std::uintptr_t* table );

	std::uintptr_t** vmt_base = nullptr;
	std::uint16_t table_length = 0;
	std::uintptr_t* original_vmt = nullptr;
	std::unique_ptr<uintptr_t[ ]> replace_vmt = nullptr;
	DWORD old_protection{ };
};
