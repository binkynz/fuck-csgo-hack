#pragma once

#include "../utilities/utilities.h"
#include "../math/vector3d.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/engine/ivdebugoverlay.h

class IVDebugOverlay {
public:
	virtual_fn( screen_position( vector3d_t& point, vector3d_t& screen ), 13, int( __thiscall* )(void*, vector3d_t&, vector3d_t&), point, screen );
};