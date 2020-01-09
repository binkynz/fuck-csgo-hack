#include "netvar_manager.h"

#include "../interfaces/interfaces.h"

c_netvar_tree::c_netvar_tree( ) {

}

bool c_netvar_tree::initialize( void ) {
	if ( !n_interfaces::client )
		return false;

	ClientClass* client_class = n_interfaces::client->get_all_classes( );

	if ( !client_class )
		return false;

	std::ofstream output = std::ofstream( "netvars_dump.txt" );

	while ( client_class != nullptr ) {
		auto class_info = std::make_shared< node_t >( 0 );

		auto recv_table = client_class->table;

		populate_nodes( recv_table, &class_info->nodes, output );

		nodes.emplace( recv_table->net_table_name, class_info );

		client_class = client_class->next;
	}

	return true;
}

const char* c_netvar_tree::get_data_type_from_enum( int recv_type ) {
	switch ( recv_type ) {
	case 0:
		return "int";
	case 1:
		return "float";
	case 2:
		return "Vector";
	case 3:
		return "Vector2";
	case 4:
		return "const char*";
	default:
		return "void";
	}
}

void c_netvar_tree::populate_nodes( RecvTable* recv_table, map_type* map, std::ofstream& file ) {
	for ( auto i = 0; i < recv_table->props; i++ ) {
		RecvProp* prop = &recv_table->prop[ i ];

		auto prop_info = std::make_shared< node_t >( prop->offset );

		if ( prop->recv_type == 6 )
			populate_nodes( prop->data_table, &prop_info->nodes, file );

		map->emplace( prop->var_name, prop_info );

		//std::string string = prop->var_name;
		//std::string new_string;

		//for ( std::size_t i = 0; i < string.length( ); i++ ) { // yikes
		//	if ( string[ i ] == 'm' || string[ i ] == '_' )
		//		continue;

		//	if ( string[ i ] >= 'A' && string[ i ] <= 'Z' ) {
		//		string[ i ] = string[ i ] + 32;

		//		if ( i != 0 )
		//			new_string = new_string + "_";

		//		new_string = new_string + string[ i ];
		//	}
		//	else
		//		new_string = new_string + string[ i ];
		//}

		//file << "netvar_fn( get_" + new_string + "( ), " + std::string( get_data_type_from_enum( prop->recv_type ) ) + ", \"" + recv_table->net_table_name + "\", \"" + prop->var_name + "\" )" << std::endl;
	}
}

namespace n_netvar_tree {
	std::unique_ptr< c_netvar_tree > netvar_tree;

	bool initialize( void ) {
		netvar_tree = std::make_unique< c_netvar_tree >( );

		if ( !netvar_tree->initialize( ) )
			return false;

		return true;
	}
}