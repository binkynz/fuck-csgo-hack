#pragma once

#include "../netvar_manager/netvar_manager.h"
#include "../utilities/utilities.h"
#include "../interfaces/interfaces.h"
#include "../math/vector3d.h"
#include "../math/matrix.h"

class C_BaseEntity {
public:
	IClientRenderable* renderable( ) {
		return reinterpret_cast< IClientRenderable* >( reinterpret_cast< std::uintptr_t >( this ) + 0x4 );
	}

	IClientNetworkable* networkable( ) {
		return reinterpret_cast< IClientNetworkable* >( reinterpret_cast< std::uintptr_t >( this ) + 0x8 );
	}

	netvar_fn( get_simulation_time( ), int, "DT_BaseEntity", "m_flSimulationTime" );
	netvar_fn( get_vec_origin( ), vector3d_t, "DT_BaseEntity", "m_vecOrigin" );

	virtual_fn( is_player( void ), 157, bool( __thiscall* )( void* ) ); // unk
};

class C_BaseCombatCharacter : public C_BaseEntity {
public:
	netvar_fn( get_h_active_weapon( ), CBaseHandle, "DT_BaseCombatCharacter", "m_hActiveWeapon" );
};

class C_BasePlayer : public C_BaseCombatCharacter {
public:
	netvar_fn( get_h_vehicle( ), CBaseHandle, "DT_BasePlayer", "m_hVehicle" );
	netvar_fn( get_health( ), int, "DT_BasePlayer", "m_iHealth" );
	netvar_fn( get_life_state( ), int, "DT_BasePlayer", "m_lifeState" );
	netvar_fn( get_flags( ), int, "DT_BasePlayer", "m_fFlags" );

	offset_fn( get_tick_base( ), int, 0x342C );

	virtual_fn( think( void ), 138, void( __thiscall* )( void* ) ); // 8B C1 8B 50 40
	virtual_fn( pre_think( void ), 317, void( __thiscall* )( void* ) ); // 55 8B EC 83 E4 F8 51 56 8B F1 8B 06
	virtual_fn( post_think( void ), 318, void( __thiscall* )( void* ) ); // 56 8B 35 ? ? ? ? 57 8B F9 8B CE 8B 06 FF 90 ? ? ? ? 8B 07
	virtual_fn( set_local_view_angles( vector3d_t& angle ), 372, void( __thiscall* )( void*, vector3d_t& ), angle ); // unk

	bool using_standard_weapons_in_vechile( void ) {
		static auto using_standard_weapons_in_vechile_fn = reinterpret_cast< bool( __thiscall* )( void* ) >( n_utilities::find_pattern( "client_panorama.dll", "56 57 8B F9 8B 97 ? ? ? ? 83 FA FF 74 41" ) );
		return using_standard_weapons_in_vechile_fn( this );
	}

	bool physics_run_think( int index ) {
		static auto physics_run_think_fn = reinterpret_cast< bool( __thiscall* )( void*, int ) >( n_utilities::find_pattern( "client_panorama.dll", "55 8B EC 83 EC 10 53 56 57 8B F9 8B 87" ) );
		return physics_run_think_fn( this, index );
	}

	void select_item( const char* string, int sub_type = 0 ) {
		static auto select_item_fn = reinterpret_cast< void( __thiscall* )( void*, const char*, int ) >( n_utilities::find_pattern( "client_panorama.dll", "55 8B EC 56 8B F1 ? ? ? 85 C9 74 71 8B 06" ) );
		select_item_fn( this, string, sub_type );
	}
};

class C_BaseAnimating : public C_BasePlayer {
public:
	offset_fn( get_model_ptr( ), void*, 0x294C );

	int get_bone_id( const char* name ) {
		static auto lookup_bone_fn = reinterpret_cast< int( __thiscall* )( void*, const char* ) >( n_utilities::find_pattern( "client_panorama.dll", "55 8B EC 53 56 8B F1 57 83 BE ? ? ? ? ? 75" ) );
		return lookup_bone_fn( this, name );
	}

	vector3d_t get_bone_position( int bone_id ) { // found this old post when looking for this func - https://www.unknowncheats.me/forum/counterstrike-global-offensive/169553-bones-dyanimically.html
		vector3d_t position{ }, rotation{ };

		static auto get_bone_position_fn = reinterpret_cast< void( __thiscall* )( void*, int, vector3d_t*, vector3d_t* ) >( n_utilities::find_pattern( "client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 30 8D" ) );
		get_bone_position_fn( this, bone_id, &position, &rotation );

		return position;
	}
};

class C_BaseCombatWeapon {
public:
	offset_fn( get_item_definition_index( ), int, 0x2FAA );

	CCSWeaponData* get_weapon_data( void ) {
		return n_interfaces::weapon_system->get_weapon_data( this->get_item_definition_index( ) );
	}
};

class C_CSPlayer : public C_BaseAnimating {
public:
	vector3d_t get_eye_position( void ) {
		vector3d_t vector{ };

		static auto weapon_shoot_position_fn = reinterpret_cast< float* ( __thiscall* )( void*, vector3d_t* ) >( n_utilities::find_pattern( "client_panorama.dll", "55 8B EC 56 8B 75 08 57 8B F9 56 8B 07 FF 90" ) );
		weapon_shoot_position_fn( this, &vector );

		return vector;
	}

	C_BaseCombatWeapon* get_active_weapon( void ) {
		return reinterpret_cast< C_BaseCombatWeapon* >( n_interfaces::entity_list->get_client_entity_from_handle( this->get_h_active_weapon( ) ) );
	}

	bool is_alive( void ) {
		return ( ( this->get_health( ) > 0 ) && ( this->get_life_state( ) == 0 ) );
	}
};