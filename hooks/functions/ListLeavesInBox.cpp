#include "../hooks.h"

#include <intrin.h>

// https://www.unknowncheats.me/forum/counterstrike-global-offensive/330483-disable-model-occulusion.html

namespace n_hooks {
	int __fastcall n_functions::ListLeavesInBox( std::uintptr_t ecx, std::uintptr_t edx, vector3d_t& mins, vector3d_t& maxs, unsigned short* list, int list_max ) {
		static auto original_fn = n_hooks::bsp_query->get_original_function< decltype( &ListLeavesInBox ) >( 6 );

		// CClientLeafSystem::InsertIntoTree sig "55 8B EC 83 E4 F8 81 EC ? ? ? ? 8B 45 08 53 56 8B 75"
		// [...]
		// .text:1024D4D7                   call    dword ptr[ eax + 18h ]      // called here
		// .text:1024D4DA                   mov[ esp + 930h + leaf_count ], eax // return here ( so u should sig this one... )
		// .text:1024D4DE                   jmp     short loc_1024D4E8          // :)
		static auto insert_into_tree_call_list_leaves_in_box = reinterpret_cast< std::uintptr_t >( n_utilities::find_pattern( "client_panorama.dll", "89 44 24 14 EB 08 C7 44 24 ? ? ? ? ? 8B 45" ) );

		if ( reinterpret_cast< std::uintptr_t >( _ReturnAddress( ) ) != insert_into_tree_call_list_leaves_in_box )
			return original_fn( ecx, edx, mins, maxs, list, list_max );

		auto info = *reinterpret_cast< RenderableInfo_t** >( reinterpret_cast< std::uintptr_t >( _AddressOfReturnAddress( ) ) + 0x14 );

		if ( !info || !info->renderable )
			return original_fn( ecx, edx, mins, maxs, list, list_max );

		auto base_entity = info->renderable->get_client_unknown( )->get_base_entity( );

		if ( !base_entity || !base_entity->is_player( ) )
			return original_fn( ecx, edx, mins, maxs, list, list_max );

		info->flags &= ~0x100;
		info->flags2 |= 0xC0;

		constexpr float MAX_COORD_FLOAT = 16384.f;
		constexpr float MIN_COORD_FLOAT = -MAX_COORD_FLOAT;

		static vector3d_t map_min = vector3d_t( MIN_COORD_FLOAT, MIN_COORD_FLOAT, MIN_COORD_FLOAT );
		static vector3d_t map_max = vector3d_t( MAX_COORD_FLOAT, MAX_COORD_FLOAT, MAX_COORD_FLOAT );

		return original_fn( ecx, edx, map_min, map_max, list, list_max );
	}
}