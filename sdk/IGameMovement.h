#pragma once

#include "../utilities/utilities.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/game/shared/igamemovement.h

class C_BasePlayer;
class CMoveData;

class IGameMovement {
public:
	// process the current movement command
	virtual_fn( process_movement( C_BasePlayer* player, CMoveData* move ), 1, void( __thiscall* )(void*, C_BasePlayer*, CMoveData*), player, move ); // 1
	virtual_fn( reset( void ), 2, void( __thiscall* )(void*) ); // 2
	virtual_fn( start_track_prediction_errors( C_BasePlayer* player ), 3, void( __thiscall* )(void*, C_BasePlayer*), player ); // 3
	virtual_fn( finish_track_prediction_errors( C_BasePlayer* player ), 4, void( __thiscall* )(void*, C_BasePlayer*), player ); // 4
};