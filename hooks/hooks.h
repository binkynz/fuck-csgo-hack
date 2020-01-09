#pragma once

#include "../vmt/vmt.h"
#include "../entities/entity.h"

namespace n_hooks {
	extern std::unique_ptr< c_vmt > client_mode;
	extern std::unique_ptr< c_vmt > engine_vgui;
	extern std::unique_ptr< c_vmt > bsp_query;
	extern std::unique_ptr< c_vmt > model_render;

	bool initialize( void );

	namespace n_functions {
		bool __fastcall CreateMove( std::uintptr_t ecx, std::uintptr_t edx, float input_sample_time, CUserCmd* cmd );
		float __fastcall GetViewModelFOV( std::uintptr_t ecx, std::uintptr_t edx );
		void __fastcall Paint( std::uintptr_t ecx, std::uintptr_t edx, int mode );
		bool __fastcall SetupBones( std::uintptr_t ecx, std::uintptr_t edx, void* bone_to_world_out, int max_bones, int bone_mask, float current_time );
		int __fastcall ListLeavesInBox( std::uintptr_t ecx, std::uintptr_t edx, vector3d_t& mins, vector3d_t& maxs, unsigned short* list, int list_max );
		void __fastcall DrawModelExecute( std::uintptr_t ecx, std::uintptr_t edx, void* render_context, void* state, ModelRenderInfo_t& info, void* custom_bone_to_world );
	}

	bool unload( void );
}