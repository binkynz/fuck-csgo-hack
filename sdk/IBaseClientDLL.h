#pragma once

#include "../utilities/utilities.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/cdll_int.h

class ClientClass;

class IBaseClientDLL {
public:
	// request a pointer to the list of client datatable classes
	virtual_fn( get_all_classes( ), 8, ClientClass* ( __thiscall* )( void* ) );
};