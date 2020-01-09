#pragma once

#include "IHandleEntity.h"

// https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/iclientunknown.h

class IClientNetworkable;
class IClientRenderable;
class C_BaseEntity;

class IClientUnknown : public IHandleEntity {
public:
	// everything here is very self explanatory 
	virtual void* get_collideable( void ) = 0;
	virtual IClientNetworkable* get_client_networkable( void ) = 0;
	virtual IClientRenderable* get_client_renderable( void ) = 0;
	virtual void* get_client_entity( void ) = 0;
	virtual C_BaseEntity* get_base_entity( void ) = 0;
	virtual void* get_client_thinkable( void ) = 0;
	virtual void* get_client_alpha_property( void ) = 0;
};