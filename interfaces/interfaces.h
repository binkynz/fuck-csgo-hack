#pragma once

#include "../sdk.h"

namespace n_interfaces {
	extern IBaseClientDLL* client;
	extern IClientMode* client_mode;
	extern IVEngineClient* engine;
	extern IClientEntityList* entity_list;
	extern IVEngineVGui* engine_vgui;
	extern ISurface* surface;
	extern CGlobalVarsBase* global_vars_base;
	extern IPrediction* prediction;
	extern IMoveHelper* move_helper;
	extern IGameMovement* game_movement;
	extern IWeaponSystem* weapon_system;
	extern IMDLCache* model_cache;
	extern IVModelRender* model_render;
	extern IMaterialSystem* material_system;
	extern IVModelInfo* model_info;
	extern IVDebugOverlay* debug_overlay;

	bool initialize( void );
}