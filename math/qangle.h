#pragma once

#include <cmath>
#include <algorithm>

struct qangle_t {
	float x, y, z;

	qangle_t( ) = default;

	qangle_t( const float _x, const float _y, const float _z ) {
		x = _x, y = _y, z = _z;
	}

	qangle_t operator+( const qangle_t& point ) {
		return qangle_t( x + point.x, y + point.y, z + point.z );
	}

	qangle_t operator-( const qangle_t& point ) {
		return qangle_t( x - point.x, y - point.y, z - point.z );
	}

	qangle_t operator*( const float point ) {
		return qangle_t( x * point, y * point, z * point );
	}

	qangle_t& operator=( const float array[ 3 ] ) {
		x = array[ 0 ];
		y = array[ 1 ];
		z = array[ 2 ];

		return *this;
	}

	qangle_t& operator+=( const qangle_t& point ) {
		x += point.x;
		y += point.y;
		z += point.z;

		return *this;
	}

	qangle_t& operator-=( const qangle_t& point ) {
		x -= point.x;
		y -= point.y;
		z -= point.z;

		return *this;
	}

	qangle_t& operator/=( const float division ) {
		x /= division;
		y /= division;
		z /= division;

		return *this;
	}
};