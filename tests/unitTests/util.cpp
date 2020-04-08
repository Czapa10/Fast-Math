#ifndef TESTS_UTIL
#define TESTS_UTIL

#include <string>
#include <cmath>
#include "doctest.h"

using uint32 = uint32_t;
using int32 = int32_t;
using bool32 = int;

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

#define CHECK_VECTOR4(_v, _x, _y, _z, _w) {\
	vec4 _res = _v; \
	CHECK4(_res.x() == _x, _res.y() == _y, _res.z() == _z, _res.w() == _w) };

#define CHECK_VECTOR4_APPROX(_v, _x, _y, _z, _w) { \
	vec4 _res = _v; \
	CHECK4(_res.x() == floatCmp(_x), _res.y() == floatCmp(_y), _res.z() == floatCmp(_z), _res.w() == floatCmp(_w)); }

#define CHECK_VECTOR4_1(v, a) \
	CHECK4(v.x() == a, v.y() == a, v.z() == a, v.w() == a);

#define CHECK_VECTOR4_ARRAY(arr, _x, _y, _z, _w) \
	CHECK4(arr[0] == _x, arr[1] == _y, arr[2] == _z, arr[3] == _w);

#define CHECK_VECTOR4_WITH_XYZW_AND_RGBA_GETTERS(v, _x, _y, _z, _w) \
	CHECK4(v.x() == _x, v.y() == _y, v.z() == _z, v.w() == _w); \
	CHECK4(v.r() == _x, v.g() == _y, v.b() == _z, v.a() == _w);

#define CHECK_ALL_MATRIX_ARRAY_ENTRIES(arr, a, b, c, d, \
                                            e, f, g, h, \
                                            i, j, k, l,\
                                            m, n, o, p) { \
	CHECK4(arr[0] == a, arr[1] == e, arr[2] == i, arr[3] == m); \
	CHECK4(arr[4] == b, arr[5] == f, arr[6] == j, arr[7] == n); \
	CHECK4(arr[8] == c, arr[9] == g, arr[10] == k, arr[11] == o); \
	CHECK4(arr[12] == d, arr[13] == h, arr[14] == l, arr[15] == p); }\

#define CHECK_ALL_MATRIX_ENTRIES(mat, a, b, c, d, \
                                      e, f, g, h, \
                                      i, j, k, l,\
                                      m, n, o, p) { \
	mat4 _mat = mat; \
	float* arr = (float*)(&_mat); \
	CHECK4(arr[0] == a, arr[1] == e, arr[2] == i, arr[3] == m); \
	CHECK4(arr[4] == b, arr[5] == f, arr[6] == j, arr[7] == n); \
	CHECK4(arr[8] == c, arr[9] == g, arr[10] == k, arr[11] == o); \
	CHECK4(arr[12] == d, arr[13] == h, arr[14] == l, arr[15] == p); }\

#define CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(mat, a, b, c, d) {\
	mat4 _mat = mat; \
	float* arr = (float*)(&_mat); \
	CHECK4(arr[0] == a,   arr[5] == b, arr[10] == c,  arr[15] == d);} \

#define CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX1(mat, d) \
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(mat, d, d, d, d)

#define PRINT_MAT4(mat) \
	mat4 _mat = mat; \
	float* arr = (float*)(&_mat); \
	INFO(arr[0] << ", " << arr[4] << ", " << arr[8] << ", " << arr[12]); \
    INFO(arr[1] << ", " << arr[5] << ", " << arr[9] << ", " << arr[13]); \
	INFO(arr[2] << ", " << arr[6] << ", " << arr[10] << ", " << arr[14]); \
    INFO(arr[3] << ", " << arr[7] << ", " << arr[11] << ", " << arr[15]); \




#endif // TESTS_UTIL
