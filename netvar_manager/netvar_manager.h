#pragma once

#include "../sdk.h"

#include <unordered_map>
#include <fstream>

// https://www.unknowncheats.me/forum/counterstrike-global-offensive/342222-netvar-manager-dumper.html

class c_netvar_tree {
	struct node_t;

	using map_type = std::unordered_map< std::string, std::shared_ptr< node_t > >;

	struct node_t {
		node_t( int offset ) : offset( offset ) { }

		map_type nodes;

		int offset;
	};

	map_type nodes{ };
public:
	c_netvar_tree( );

	bool initialize( void );

	template < typename... T > int get_offset( const char* name, T ... args ) {
		auto& node = nodes[ name ];

		return get_offset_recursive( node->nodes, node->offset, args... );
	}

private:
	const char* get_data_type_from_enum( int recv_type );

	void populate_nodes( RecvTable* recv_table, map_type* map, std::ofstream& file );

	static int get_offset_recursive( map_type& map, int acc, const char* name ) {
		return acc + map[ name ]->offset;
	}

	template < typename... T > int get_offset_recursive( map_type& map, int acc, const char* name, T ... args ) {
		auto& node = map[ name ];

		return get_offset_recursive( node->nodes, acc + node->offset, args... );
	}
};

namespace n_netvar_tree {
	extern std::unique_ptr< c_netvar_tree > netvar_tree;

	bool initialize( void );
}

#define netvar_fn( function_name, type, ... ) \
	type& function_name { \
		return *reinterpret_cast< type* >( reinterpret_cast< std::uintptr_t >( this ) + n_netvar_tree::netvar_tree->get_offset( __VA_ARGS__ ) ); \
	};

#define offset_fn( function_name, type, offset ) \
	type& function_name { \
		return *reinterpret_cast< type* >( std::uintptr_t( this ) + offset ); \
	};