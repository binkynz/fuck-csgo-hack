#pragma once

#include "../utilities/utilities.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/iprediction.h

class CUserCmd;
class C_BasePlayer;
class IMoveHelper;
class CMoveData;

class IPrediction {
public:
	// yes
	virtual_fn( in_prediction( void ), 14, bool( __thiscall* )( void* ) ); // 14

	// checks if the player is standing on a moving entity and adjusts velocity and basevelocity appropriately
	virtual_fn( check_moving_ground( C_BasePlayer* player, float frame_time ), 18, void( __thiscall* )( void*, C_BasePlayer*, double ), player, frame_time ); // 18

	// call the default SetupMove code.
	virtual_fn( setup_move( C_BasePlayer* player, CUserCmd* cmd, IMoveHelper* helper, CMoveData* move ), 20, void( __thiscall* )( void*, C_BasePlayer*, CUserCmd*, IMoveHelper*, CMoveData* ), player, cmd, helper, move ); // 20

	// call the default FinishMove code.
	virtual_fn( finish_move( C_BasePlayer* player, CUserCmd* cmd, CMoveData* move ), 21, void( __thiscall* )( void*, C_BasePlayer*, CUserCmd*, CMoveData* ), player, cmd, move ); // 21
};