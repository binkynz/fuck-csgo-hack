#pragma once

#include "../utilities/utilities.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/game/shared/imovehelper.h

class C_BasePlayer;

class IMoveHelper {
public:
	// selects the host to target
	virtual_fn( set_host( C_BasePlayer* player ), 1, void( __thiscall* )(void*, C_BasePlayer*), player );

	// adds the trace result to touch list, if contact is not already in list.
	virtual_fn( process_impacts( void ), 4, void( __thiscall* )(void*) ); // 4
};