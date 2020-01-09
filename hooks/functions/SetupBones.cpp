#include "../hooks.h"

#include "../../entities/animations/animations.h"

#include <string>

namespace n_hooks {
	bool __fastcall n_functions::SetupBones( std::uintptr_t ecx, std::uintptr_t edx, void* bone_to_world_out, int max_bones, int bone_mask, float current_time ) {

		C_CSPlayer* player = reinterpret_cast < C_CSPlayer* >( std::uintptr_t( ecx ) - 0x4 );

		auto original_fn = g_animations.track[ player->networkable( )->ent_index( ) ].renderable->get_original_function< decltype( &SetupBones ) >( 13 );

		if ( player && player->is_alive( ) ) {
			//if ( bone_to_world_out != nullptr ) {
			//	static float last_real_time = 0.f;

			//	if ( n_interfaces::global_vars_base->real_time >= last_real_time + 1.f )
			//		last_real_time = n_interfaces::global_vars_base->real_time;
			//}

			//bone_mask = bone_mask | 0x80000;

			//if ( *reinterpret_cast< std::uint32_t* >(reinterpret_cast< std::uint32_t >( ecx ) + 0x28B8 ) != -1 )
			//	return false;

			//if ( bone_mask == -1 )
			//	bone_mask = *reinterpret_cast< std::uint32_t* >( reinterpret_cast< std::uint32_t >( ecx ) + 0x2698 ); // m_iPrevBoneMask

			///*if ( ( void*** )dword_10D20F3C == &off_10D20F20 )
			//	v16 = ( unsigned int )&off_10D20F20 ^ dword_10D20F50;
			//else
			//	v16 = (*(int (**)(void))(*( _DWORD* )dword_10D20F3C + 52))();*/

			//bone_mask = bone_mask | 0xFFF00;

			///*if ( !v16 )
			//	bone_mask_2 = bone_mask_1;*/

			//if ( !*reinterpret_cast< std::uint32_t* >( reinterpret_cast< std::uint32_t >( ecx ) + 0x2698 ) )
			//	bone_mask = bone_mask;
		}

		return original_fn( ecx, edx, bone_to_world_out, max_bones, bone_mask, current_time );
	}
}