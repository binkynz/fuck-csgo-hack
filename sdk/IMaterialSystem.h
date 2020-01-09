#pragma once

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/materialsystem/imaterialsystem.h

class IMaterial;

class IMaterialSystem {
public:
	// returns a particular material
	virtual_fn( get_material( const char* material_name, const char* texture_group_name, bool complain = true, const char* complain_prefix = nullptr ), 84, IMaterial* ( __thiscall* )( void*, const char*, const char*, bool, const char* ), material_name, texture_group_name, complain, complain_prefix );
};