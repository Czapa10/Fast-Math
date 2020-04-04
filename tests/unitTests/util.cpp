#ifndef TESTS_UTIL
#define TESTS_UTIL

#include <string>
#include <cmath>
#include "doctest.h"

static long long vElements;
static char binaryOutput[128];

#define logRegisterOf(v, name) \
	_mm_store_ps((float*)(&vElements), v.m); \
	for(int i = 0; i < 128; ++i) \
	{ \
		binaryOutput[i] = (vElements >> i) & 1 ? '1' : '0'; \
	} \
	INFO(name << " (binary): " << std::string(binaryOutput)); 

#define logIntRegisterOf(v, name) \
	_mm_store_si128((__m128i*)(&vElements), v.m); \
	for(int i = 0; i < 128; ++i) \
	{ \
		binaryOutput[i] = (vElements >> i) & 1 ? '1' : '0'; \
	} \
	INFO(name << " (binary): " << std::string(binaryOutput)); 

#define floatCmp(x) doctest::Approx(x).epsilon(0.01)

#define CHECK4(a, b, c, d) CHECK(a); CHECK(b); CHECK(c); CHECK(d);

#define LOG_VECTOR2(v) \
	INFO("a == (" << v.x() << ", " << v.y() << ")");

#define CHECK_VECTOR2(v, _x, _y) \
	CHECK(v.x() == _x); CHECK(v.y() == _y);

#define CHECK_VECTOR2_APPROX(v, _x, _y) \
	CHECK(v.x() == floatCmp(_x)); CHECK(v.y() == floatCmp(_y));

#define CHECK_VECTOR2_ARRAY(arr, _x, _y) \
	CHECK(arr[0] == _x); CHECK(arr[1] == _y);

#define CHECK_VECTOR2_ALL_ALIASES(_v, _x, _y) \
	CHECK(_v.x() == _x); CHECK(_v.y() == _y); \
	CHECK(_v.u() == _x); CHECK(_v.v() == _y); \
	CHECK(_v.left() == _x); CHECK(_v.top() == _y); \
	CHECK(_v.width() == _x); CHECK(_v.height() == _y);

#define CHECK_VECTOR4(v, _x, _y, _z, _w) \
	CHECK4(v.x() == _x, v.y() == _y, v.z() == _z, v.w() == _w);

#define CHECK_VECTOR4_APPROX(v, _x, _y, _z, _w) \
	CHECK4(v.x() == floatCmp(_x), v.y() == floatCmp(_y), v.z() == floatCmp(_z), v.w() == floatCmp(_w));

#define CHECK_VECTOR4_1(v, a) \
	CHECK4(v.x() == a, v.y() == a, v.z() == a, v.w() == a);

#define CHECK_VECTOR4_ARRAY(arr, _x, _y, _z, _w) \
	CHECK4(arr[0] == _x, arr[1] == _y, arr[2] == _z, arr[3] == _w);

#define CHECK_VECTOR4_WITH_XYZW_AND_RGBA_GETTERS(v, _x, _y, _z, _w) \
	CHECK4(v.x() == _x, v.y() == _y, v.z() == _z, v.w() == _w); \
	CHECK4(v.r() == _x, v.g() == _y, v.b() == _z, v.a() == _w);


#endif // TESTS_UTIL
