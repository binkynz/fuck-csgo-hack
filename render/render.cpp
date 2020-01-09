#include "render.h"

namespace n_render {
	namespace n_font {
		HFont main;

		bool initialize( void ) {
			auto create_font = [ ]( HFont& font, const char* name, const int size, const int weight, const int flags ) -> bool {
				font = n_interfaces::surface->create_font( );

				if ( !font )
					return false;

				n_interfaces::surface->set_font_glyph_set( font, name, size, weight, 0, 0, flags, 0, 0 );

				return true;
			};

			if ( !create_font( n_render::n_font::main, "Verdana", 12, 700, FONTFLAG_NONE ) )
				return false;

			return true;
		}
	}

	int screen_w, screen_h;

	bool initialize( void ) {
		n_interfaces::surface->get_screen_size( screen_w, screen_h );

		if ( !screen_w || !screen_h )
			return false;

		if ( !n_font::initialize( ) )
			return false;

		return true;
	}

	void filled_rect( const int x, const int y, const int w, const int h, const int r, const int g, const int b, const int a ) {
		n_interfaces::surface->draw_set_color( r, g, b, a );
		n_interfaces::surface->draw_filled_rect( x, y, x + w, y + h );
	}

	void outlined_rect( const int x, const int y, const int w, const int h, const int r, const int g, const int b, const int a ) {
		n_interfaces::surface->draw_set_color( r, g, b, a );
		n_interfaces::surface->draw_outlined_rect( x, y, x + w, y + h );
	}

	void line( const int x, const int y, const int w, const int h, const int r, const int g, const int b, const int a ) {
		n_interfaces::surface->draw_set_color( r, g, b, a );
		n_interfaces::surface->draw_line( x, y, x + w, y + h );
	}

	void text( const HFont& font, const std::string text, const int x, const int y, const bool centered, const int r, const int g, const int b, const int a ) {
		std::wstring converted_text = std::wstring( text.begin( ), text.end( ) );

		int width, height;
		n_interfaces::surface->get_text_size( font, converted_text.c_str( ), width, height );

		int _x = x, _y = y;

		if ( centered == true )
			_x -= width / 2;

		n_interfaces::surface->draw_set_text_color( r, g, b, a );
		n_interfaces::surface->draw_set_text_font( font );

		n_interfaces::surface->draw_set_text_pos( _x, _y );

		n_interfaces::surface->draw_print_text( converted_text.c_str( ), converted_text.length( ) );
	}
}