#pragma once

#include "../math/vector3d.h"

class CUserCmd {
public:
	char _pad0[ 0x4 ]; // 0
	int command_number; // 4
	int tick_count; // 8
	vector3d_t view_angles; // 12
	vector3d_t aim_direction; // 24
	float forward_move; // 36
	float side_move; // 40
	float up_move; // 44
	int buttons; // 48
	int impulse; // 52
	int weapon_select; // 56
	int weapon_sub_type; // 60
	int random_seed;
	short moused_x;
	short moused_y;
	bool has_been_predicted;
};