#pragma once

#include "../utilities/utilities.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/mp/src/public/materialsystem/imaterialvar.h

class IMaterialVar {
public:
	// self explanatory
	virtual_fn( set_float_value( float val ), 4, void( __thiscall* )(void*, float), val ); // 4
	virtual_fn( set_int_value( int val ), 5, void( __thiscall* )(void*, int), val ); // 5
	virtual_fn( set_string_value( const char* val ), 6, void( __thiscall* )(void*, const char*), val ); // 6

	// vec ( dim 2-4 )
	virtual_fn( set_vec_value( float x, float y, float z ), 11, void( __thiscall* )(void*, float, float, float), x, y, z ); // 11
};