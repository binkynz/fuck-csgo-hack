#include "../hooks.h"

namespace n_hooks {
	float __fastcall n_functions::GetViewModelFOV( std::uintptr_t ecx, std::uintptr_t edx ) {

		return 100.f;
	}
}