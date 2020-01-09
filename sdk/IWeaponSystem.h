#pragma once

#include "../utilities/utilities.h"

// https://www.unknowncheats.me/forum/counterstrike-global-offensive/231080-getting-wpndata-vtable-indexes.html

struct CCSWeaponData {
	char _pad0[ 0x4 ];
	char* console_name;
	char _pad1[ 0xc ];
	int max_clip1;
	int max_clip2;
	int default_clip1;
	int default_clip2;
	int primary_reserve_ammo_max;
	int secondary_reserve_ammo_max;
	char* world_model;
	char* view_model;
	char* dropped_model;
	char _pad2[ 0x50 ];
	char* hud_name;
	char* weapon_name;
};

class IWeaponSystem {
	virtual void unused0( ) = 0;
	virtual void unused1( ) = 0;
public:
	virtual CCSWeaponData* get_weapon_data( unsigned index ) const = 0;
};