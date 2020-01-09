#pragma once

#include "../utilities/utilities.h"
#include "../math/matrix.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/iclientrenderable.h

class IClientUnknown;

class IClientRenderable {
public:
	// gets at the containing class...
	virtual_fn( get_client_unknown( void ), 0, IClientUnknown* ( __thiscall* )( void* ) ); // 0

	// call this to get the current bone transforms for the model.
	// currentTime parameter will affect interpolation
	// nMaxBones specifies how many matrices pBoneToWorldOut can hold. (Should be greater than or
	// equal to studiohdr_t::numbones. Use MAXSTUDIOBONES to be safe.)
	virtual_fn( setup_bones( matrix3x4_t* bone_to_world_out, int max_bones, int bone_mask, float current_time ), 13, bool( __thiscall* )( void*, matrix3x4_t*, int, int, float ), bone_to_world_out, max_bones, bone_mask, current_time ); // 13
};