#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

#define CHECK4(a, b, c, d) CHECK(a); CHECK(b); CHECK(c); CHECK(d);

#define CHECK_ALL_ENTRIES_OF_DIAGONAL_MATRIX_ARRAY(arr, a, b, c, d, \
                                                        e, f, g, h, \
													    i, j, k, l,\
													    m, n, o, p) { \
	CHECK4(arr[0] == a, arr[1] == b, arr[2] == c, arr[3] == d); \
	CHECK4(arr[4] == e, arr[5] == f, arr[6] == g, arr[7] == h); \
	CHECK4(arr[8] == i, arr[9] == j, arr[10] == k, arr[11] == l); \
	CHECK4(arr[12] == m, arr[13] == n, arr[14] == o, arr[15] == p); }\

#define CHECK_ALL_ENTRIES_OF_DIAGONAL_MATRIX(mat, a, b, c, d, \
                                                    e, f, g, h, \
													i, j, k, l,\
													m, n, o, p) { \
	float* arr = (float*)(&mat); \
	CHECK4(arr[0] == a, arr[1] == b, arr[2] == c, arr[3] == d); \
	CHECK4(arr[4] == e, arr[5] == f, arr[6] == g, arr[7] == h); \
	CHECK4(arr[8] == i, arr[9] == j, arr[10] == k, arr[11] == l); \
	CHECK4(arr[12] == m, arr[13] == n, arr[14] == o, arr[15] == p); }\

#define CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(mat, a, b, c, d) {\
	float* arr = (float*)(&mat); \
	CHECK4(arr[0] == a, arr[1] == 0.f, arr[2] == 0.f, arr[3] == 0.f); \
	CHECK4(arr[4] == 0.f, arr[5] == b, arr[6] == 0.f, arr[7] == 0.f); \
	CHECK4(arr[8] == 0.f, arr[9] == 0.f, arr[10] == c, arr[11] == 0.f); \
	CHECK4(arr[12] == 0.f, arr[13] == 0.f, arr[14] == 0.f, arr[15] == d); }\

#define CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX1(mat, d) \
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(mat, d, d, d, d)

#define PRINT_MAT4(mat) \
	float* arr = (float*)(&mat); \
	INFO(arr[0] << ", " << arr[1] << ", " << arr[2] << ", " << arr[3]); \
    INFO(arr[4] << ", " << arr[5] << ", " << arr[6] << ", " << arr[7]); \
	INFO(arr[8] << ", " << arr[9] << ", " << arr[10] << ", " << arr[11]); \
    INFO(arr[12] << ", " << arr[13] << ", " << arr[14] << ", " << arr[15]); \

TEST_CASE("mat4 constructors and accessors")
{
	mat4 a(3.f);
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX1(a, 3.f);

	a = mat4(1.f, 2.f, 3.f, 4.f);
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(a, 1.f, 2.f, 3.f, 4.f);

	vec4 diagonal(1.f, 2.f, 3.f, 4.f);
	a = mat4(diagonal);
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(a, 1.f, 2.f, 3.f, 4.f);

	vec4 col1(1.f, 2.f, 3.f, 4.f);
	vec4 col2(5.f, 6.f, 7.f, 8.f);
	vec4 col3(9.f, 10.f, 11.f, 12.f);
	vec4 col4(13.f, 14.f, 15.f, 16.f);
	a = mat4(col1, col2, col3, col4);
	CHECK_ALL_ENTRIES_OF_DIAGONAL_MATRIX(a,
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);

	a = mat4(1.f, 2.f, 3.f, 4.f,
             5.f, 6.f, 7.f, 8.f,
             9.f, 10.f, 11.f, 12.f,
             13.f, 14.f, 15.f, 16.f);
	CHECK_ALL_ENTRIES_OF_DIAGONAL_MATRIX(a,
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);

	float storage[16];
	store(storage, a);
	CHECK_ALL_ENTRIES_OF_DIAGONAL_MATRIX_ARRAY(storage,
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);

	store16ByteAligned(storage, a);											   
	CHECK_ALL_ENTRIES_OF_DIAGONAL_MATRIX_ARRAY(storage,
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);
}
