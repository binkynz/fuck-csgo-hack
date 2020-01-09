#pragma once

#include "../interfaces/interfaces.h"

#include <string>

namespace n_render {
	namespace n_font {
		extern HFont main;

		bool initialize( void );
	}

	extern int screen_w, screen_h;

	void filled_rect( const int x, const int y, const int w, const int h, const int r, const int g, const int b, const int a );
	void outlined_rect( const int x, const int y, const int w, const int h, const int r, const int g, const int b, const int a );
	void line( const int x, const int y, const int w, const int h, const int r, const int g, const int b, const int a );
	void text( const HFont& font, const std::string text, const int x, const int y, const bool centered, const int r, const int g, const int b, const int a );

	bool initialize( void );
}