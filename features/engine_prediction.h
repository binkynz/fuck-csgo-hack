#pragma once

#include "../entities/entity.h"

namespace n_engine_prediction {
	extern float old_current_time;
	extern float old_frame_time;
	extern void* move_data;
	extern int* prediction_random_seed;
	extern int* prediction_player;

	void initialize( C_CSPlayer* player, CUserCmd* cmd );
	void unload( C_CSPlayer* player );
}