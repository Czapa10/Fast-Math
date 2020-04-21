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

#define LogRegisterOf(V, Name) \
	_mm_store_ps((float*)(&VElements), V.M); \
	for(int Bit = 0; Bit < 128; ++Bit) \
	{ \
		BinaryOutput[i] = (VElements >> i) & 1 ? '1' : '0'; \
	} \
	INFO(name << " (binary): " << std::string(BinaryOutput)); 

#define LogIntRegisterOf(V, Name) \
	_mm_store_si128((__m128i*)(&VElements), V.M); \
	for(int Bit = 0; Bit < 128; ++Bit) \
	{ \
		BinaryOutput[Bit] = (VElements >> Bit) & 1 ? '1' : '0'; \
	} \
	INFO(Name << " (binary): " << std::string(BinaryOutput)); 

#define FloatCmp(x) doctest::Approx(x).epsilon(0.01)

#define CHECK4(A, B, C, D) CHECK(A); CHECK(B); CHECK(C); CHECK(D);
#define CHECK3(A, B, C) CHECK(A); CHECK(B); CHECK(C);

#define LOG_V2(V) \
	INFO("a == (" << V.X() << ", " << V.Y() << ")");

#define CHECK_V2(_V, _X, _Y) {\
	auto R = _V; \
	CHECK(R.X() == _X); CHECK(R.Y() == _Y); }

#define CHECK_V2_APPROX(_V, _X, _Y) {\
	auto R = _V; \
	CHECK(R.X() == FloatCmp(_X)); CHECK(R.Y() == FloatCmp(_Y)); }

#define CHECK_V2_ARRAY(Arr, _X, _Y) \
	CHECK(Arr[0] == _X); CHECK(Arr[1] == _Y);

#define CHECK_V2_ALL_ALIASES(_V, _X, _Y) { \
	auto R = _V; \
	CHECK(R.X() == _X); CHECK(R.Y() == _Y); \
	CHECK(R.U() == _X); CHECK(R.V() == _Y); \
	CHECK(R.Left() == _X); CHECK(R.Top() == _Y); \
	CHECK(R.Width() == _X); CHECK(R.Height() == _Y); }

#define CHECK_V3(_V, _X, _Y, _Z) {\
	auto _Res = _V; \
	CHECK3(_Res.X() == _X, _Res.Y() == _Y, _Res.Z() == _Z) };

#define CHECK_V3_APPROX(_V, _X, _Y, _Z) { \
	auto _Res = _V; \
	CHECK3(_Res.X() == FloatCmp(_X), _Res.Y() == FloatCmp(_Y), _Res.Z() == FloatCmp(_Z)); }

#define CHECK_VECTOR4(_V, _X, _Y, _Z, _W) {\
	auto _Res = _V; \
	CHECK4(_Res.X() == _X, _Res.Y() == _Y, _Res.Z() == _Z, _Res.W() == _W) };

#define CHECK_VECTOR4_APPROX(_V, _X, _Y, _Z, _W) { \
	auto _Res = _V; \
	CHECK4(_Res.X() == FloatCmp(_X), _Res.Y() == FloatCmp(_Y), _Res.Z() == FloatCmp(_Z), _Res.W() == FloatCmp(_W)); }

#define CHECK_VECTOR4_1(V, A) \
	CHECK4(V.X() == A, V.Y() == A, V.Z() == A, V.W() == A);

#define CHECK_VECTOR4_ARRAY(Arr, _X, _Y, _Z, _W) \
	CHECK4(Arr[0] == _X, Arr[1] == _Y, Arr[2] == _Z, Arr[3] == _W);

#define CHECK_VECTOR4_WITH_XYZW_AND_RGBA_GETTERS(V, _X, _Y, _Z, _W) \
	CHECK4(V.X() == _X, V.Y() == _Y, V.Z() == _Z, V.W() == _W); \
	CHECK4(V.R() == _X, V.G() == _Y, V.B() == _Z, V.A() == _W);

#define CHECK_ALL_MATRIX_ARRAY_ENTRIES(Arr, A, B, C, D, \
                                            E, F, G, H, \
                                            I, J, K, L,\
                                            M, N, O, P) { \
	CHECK4(Arr[0] == A, Arr[1] == E, Arr[2] == I, Arr[3] == M); \
	CHECK4(Arr[4] == B, Arr[5] == F, Arr[6] == J, Arr[7] == N); \
	CHECK4(Arr[8] == C, Arr[9] == G, Arr[10] == K, Arr[11] == O); \
	CHECK4(Arr[12] == D, Arr[13] == H, Arr[14] == L, Arr[15] == P); }\

#define CHECK_ALL_MATRIX_ENTRIES(Mat, A, B, C, D, \
                                      E, F, G, H, \
                                      I, J, K, L,\
                                      M, N, O, P) { \
	mat4 _Mat = Mat; \
	float* Arr = (float*)(&_Mat); \
	CHECK4(Arr[0] == A, Arr[1] == E, Arr[2] == I, Arr[3] == M); \
	CHECK4(Arr[4] == B, Arr[5] == F, Arr[6] == J, Arr[7] == N); \
	CHECK4(Arr[8] == C, Arr[9] == G, Arr[10] == K, Arr[11] == O); \
	CHECK4(Arr[12] == D, Arr[13] == H, Arr[14] == L, Arr[15] == P); }\

#define CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(Mat, A, B, C, D) {\
	mat4 _Mat = Mat; \
	float* Arr = (float*)(&_Mat); \
	CHECK4(Arr[0] == A,   Arr[5] == B, Arr[10] == C,  Arr[15] == D);} \

#define CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX1(Mat, D) \
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(Mat, D, D, D, D)

#define PRINT_MAT4(Mat) \
	mat4 _Mat = Mat; \
	float* Arr = (float*)(&_Mat); \
	INFO(Arr[0] << ", " << Arr[4] << ", " << Arr[8] << ", " << Arr[12]); \
    INFO(Arr[1] << ", " << Arr[5] << ", " << Arr[9] << ", " << Arr[13]); \
	INFO(Arr[2] << ", " << Arr[6] << ", " << Arr[10] << ", " << Arr[14]); \
    INFO(Arr[3] << ", " << Arr[7] << ", " << Arr[11] << ", " << Arr[15]); \




#endif // TESTS_UTIL
