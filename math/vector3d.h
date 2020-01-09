#pragma once

#include <cmath>
#include <algorithm>

struct vector3d_t {
	float x, y, z;

	vector3d_t( ) = default;

	vector3d_t( const float _x, const float _y, const float _z ) {
		x = _x, y = _y, z = _z;
	}

	vector3d_t operator+( const vector3d_t& point ) {
		return vector3d_t( x + point.x, y + point.y, z + point.z );
	}

	vector3d_t operator-( const vector3d_t& point ) {
		return vector3d_t( x - point.x, y - point.y, z - point.z );
	}

	vector3d_t operator*( const float point ) {
		return vector3d_t( x * point, y * point, z * point );
	}

	vector3d_t& operator=( const float array[ 3 ] ) {
		x = array[ 0 ];
		y = array[ 1 ];
		z = array[ 2 ];

		return *this;
	}

	vector3d_t& operator+=( const vector3d_t& point ) {
		x += point.x;
		y += point.y;
		z += point.z;

		return *this;
	}

	vector3d_t& operator-=( const vector3d_t& point ) {
		x -= point.x;
		y -= point.y;
		z -= point.z;

		return *this;
	}

	vector3d_t& operator/=( const float division ) {
		x /= division;
		y /= division;
		z /= division;

		return *this;
	}

	float dot( const vector3d_t& point ) {
		return ( x * point.x + y * point.y + z * point.z );
	}

	float length( void ) {
		return std::sqrtf( x * x + y * y + z * z );
	}

	float length_sqr( void ) {
		return ( x * x + y * y + z * z );
	}

	float length_2d( void ) {
		return std::sqrt( x * x + y * y );
	}

	void zero( void ) {
		x = y = z = 0.0f;
	}

	void normalize( void ) {
		x = std::isfinite( x ) ? std::remainderf( x, 360.0f ) : 0.0f;
		y = std::isfinite( y ) ? std::remainderf( y, 360.0f ) : 0.0f;
		z = 0.0f;
	}

	void clamp( void ) {
		normalize( );

		x = std::clamp( x, -89.0f, 89.0f );
		y = std::clamp( y, -180.0f, 180.0f );
		z = 0.0f;
	}
};