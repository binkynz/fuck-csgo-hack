#pragma once

#include "../utilities/utilities.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/engine/ivmodelinfo.h

class IVModelInfo {
public:
	// returns name of model
	virtual_fn( get_model_name( const void* model ), 3, const char* ( __thiscall* )( void*, const void* ), model ); // 3
};