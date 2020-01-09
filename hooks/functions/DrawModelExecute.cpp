#include "../hooks.h"

namespace n_hooks {
	void __fastcall n_functions::DrawModelExecute( std::uintptr_t ecx, std::uintptr_t edx, void* context, void* state, ModelRenderInfo_t& info, void* custom_bone_to_world ) {
		static auto original_fn = n_hooks::model_render->get_original_function< decltype( &DrawModelExecute ) >( 21 );

		C_CSPlayer* model_entity = reinterpret_cast< C_CSPlayer* >( n_interfaces::entity_list->get_client_entity( info.entity_index ) );

		const char* const model_name = n_interfaces::model_info->get_model_name( info.model );

		// this will be moved to its own file if/when this cpp file becomes more clustered
		// there is by all means not a GOOD way to do what i have done. its just an example.
		auto player_chams = [ &ecx, &edx, &context, &state, &info, &custom_bone_to_world ]( C_CSPlayer* model_entity, ModelRenderInfo_t& info, const char* const model_name ) {
			if ( !std::strstr( model_name, "models/player" ) )
				return;

			if ( !model_entity || !model_entity->is_alive( ) || !info.model )
				return;

			/* first cham layer */
			static IMaterial* material_body = n_interfaces::material_system->get_material( "debug/debugdrawflat", "Model textures" );

			if ( !material_body )
				return;

			material_body->set_material_var_flag( MATERIAL_VAR_IGNOREZ, true );

			material_body->color_modulate( 0.f, 0.f, 0.f );
			material_body->alpha_modulate( 0.8f );

			n_interfaces::model_render->forced_material_override( material_body );
			original_fn( ecx, edx, context, state, info, custom_bone_to_world );

			/* second cham layer ( overlay ) */
			static IMaterial* material_overlay = n_interfaces::material_system->get_material( "models/inventory_items/cologne_prediction/cologne_prediction_glass", "Other textures" );

			if ( !material_overlay )
				return;

			material_overlay->set_material_var_flag( MATERIAL_VAR_IGNOREZ, true );

			bool found_vmt_var = false;
			IMaterialVar* material_var = material_overlay->find_var( "$envmaptint", &found_vmt_var );

			const int health = model_entity->get_health( );
			const float r = ( 255.f - health * 2.55f ) / 255.f;
			const float g = health * 2.55f / 255.f;
			const float b = 0.f;

			if ( found_vmt_var )
				material_var->set_vec_value( r, g, b );

			n_interfaces::model_render->forced_material_override( material_overlay );
		};

		player_chams( model_entity, info, model_name );

		original_fn( ecx, edx, context, state, info, custom_bone_to_world );
		n_interfaces::model_render->forced_material_override( nullptr );
	}
}