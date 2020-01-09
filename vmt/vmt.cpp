#include "vmt.h"

c_vmt::c_vmt( ) {

}

bool c_vmt::initialize( void* base ) {
	// something has gone wrong :(
	if ( !base )
		return false;

	// original vtable
	vmt_base = static_cast< std::uintptr_t** >(base);

	if ( !vmt_base )
		return false;

	// storing the original table
	original_vmt = *vmt_base;

	// this isn't really necessary but i'm doing it anyways
	if ( !original_vmt )
		return false;

	// make pages able to be read and wrote to
	VirtualProtect( vmt_base, sizeof( std::uintptr_t ), PAGE_READWRITE, &old_protection );

	// get the length of the table
	table_length = get_vtable_length( original_vmt );

	// if there was no table to something went wrong
	if ( !table_length )
		return false;

	// allocating a new vtable ( +1 for RTTI )
	replace_vmt = std::make_unique<std::uintptr_t[ ]>( table_length + 1 );

	// if something went wrong
	if ( !replace_vmt )
		return false;

	// initiate all values w/ 0
	std::memset( replace_vmt.get( ), 0, table_length * sizeof( std::uintptr_t ) + sizeof( std::uintptr_t ) );

	// copy old table and skip first 4 bytes to insert rtti
	std::memcpy( &replace_vmt[ 1 ], original_vmt, table_length * sizeof( std::uintptr_t ) );

	// copy rtti
	std::memcpy( replace_vmt.get( ), &original_vmt[ -1 ], sizeof( std::uintptr_t ) );

	// applying the new vtable ( skiping 4 bytes since that's where rtti is located )
	*vmt_base = &replace_vmt[ 1 ];

	return true;
}

bool c_vmt::hook_function( const std::uint16_t index, void* function ) {
	// if there has been an error in initialization ro the index is out of bounds
	if ( !replace_vmt || index < 0 || index > table_length )
		return false;

	replace_vmt[ index + 1 ] = reinterpret_cast< std::uintptr_t >(function);

	return true;
}

bool c_vmt::unhook_function( const std::uint16_t index ) {
	// if there has been an error in initialization ro the index is out of bounds
	if ( !original_vmt || !replace_vmt || index < 0 || index > table_length )
		return false;

	replace_vmt[ index + 1 ] = original_vmt[ index ];

	return true;
}

bool c_vmt::unhook( void ) {
	// check if the table was already restored
	if ( !original_vmt )
		return false;

	// revert page protection
	VirtualProtect( vmt_base, sizeof( std::uintptr_t ), PAGE_READWRITE, &old_protection );

	*vmt_base = original_vmt;

	// prevent double unhook
	original_vmt = nullptr;

	return true;
}

std::uint32_t c_vmt::get_vtable_length( std::uintptr_t* table ) {
	std::uintptr_t length = std::uintptr_t{ };

	// walk through every function until it is no longer valid
	for ( length = 0; table[ length ]; length++ )
		if ( IS_INTRESOURCE( table[ length ] ) )
			break;

	return length;
}