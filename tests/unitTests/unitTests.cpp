#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include <string>
#include <cmath>

using namespace fm;

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

#define CHECK2(A, B) CHECK(A); CHECK(B);
#define CHECK3(A, B, C) CHECK(A); CHECK(B); CHECK(C);
#define CHECK4(A, B, C, D) CHECK(A); CHECK(B); CHECK(C); CHECK(D);

#define CHECK_ARRAY2(Arr, _X, _Y) \
	CHECK2(Arr[0] == _X, Arr[1] == _Y);

#define CHECK_ARRAY3(Arr, _X, _Y, _Z) \
	CHECK3(Arr[0] == _X, Arr[1] == _Y, Arr[2] == _Z);

#define CHECK_ARRAY4(Arr, _X, _Y, _Z, _W) \
	CHECK4(Arr[0] == _X, Arr[1] == _Y, Arr[2] == _Z, Arr[3] == _W);

#define CHECK_V2(_V, _X, _Y) {\
	auto _R = _V; \
	CHECK2(_R.X == _X, _R.Y == _Y); }

#define CHECK_V2_APPROX(_V, _X, _Y) {\
	auto R = _V; \
	CHECK2(R.X == FloatCmp(_X), R.Y == FloatCmp(_Y)); }

#define CHECK_V2_ALL_ALIASES(_V, _X, _Y) {\
	auto R = _V; \
	CHECK2(R.X == _X, R.Y == _Y); \
	CHECK2(R.U == _X, R.V == _Y); \
	CHECK2(R.Left == _X, R.Top == _Y); \
	CHECK2(R.Left == _X, R.Right == _Y); \
	CHECK2(R.Width == _X, R.Height == _Y); \
	CHECK2(R.W == _X, R.H == _Y); \
	CHECK2(R[0] == _X, R[1] == _Y); }

#define CHECK_V3(_V, _X, _Y, _Z) {\
	auto R = _V; \
	CHECK3(R.X == _X, R.Y == _Y, R.Z == _Z); }

#define CHECK_V3_APPROX(_V, _X, _Y, _Z) {\
	auto R = _V; \
	CHECK3(R.X == FloatCmp(_X), R.Y == FloatCmp(_Y), R.Z == FloatCmp(_Z)); }

#define CHECK_V3_ALL_ALIASES(_V, _X, _Y, _Z) {\
	auto V = _V; \
	CHECK3(V.X == _X, V.Y == _Y, V.Z == _Z); \
	CHECK3(V.U == _X, V.V == _Y, V.W == _Z); \
	CHECK3(V.R == _X, V.G == _Y, V.B == _Z); \
	CHECK_V2(V.XY, _X, _Y); \
	CHECK_V2(V.UV, _X, _Y); \
	CHECK_V2(V.RG, _X, _Y); \
	CHECK_V2(V.YZ, _Y, _Z); \
	CHECK_V2(V.VW, _Y, _Z); \
	CHECK_V2(V.GB, _Y, _Z); \
	CHECK3(V[0] == _X, V[1] == _Y, V[2] == _Z) };

#define CHECK_V4(_V, _X, _Y, _Z, _W) {\
	auto R = _V; \
	CHECK4(R.X == _X, R.Y == _Y, R.Z == _Z, R.W == _W); }

#define CHECK_V4_APPROX(_V, _X, _Y, _Z, _W) {\
	auto R = _V; \
	CHECK4(R.X == FloatCmp(_X), R.Y == FloatCmp(_Y), R.Z == FloatCmp(_Z), R.W == FloatCmp(_W)); }

#define CHECK_V4_APPROX_EXPERIMENTAL(_V, _X, _Y, _Z, _W) {\
	CHECK4(_V.X == FloatCmp(_X), _V.Y == FloatCmp(_Y), _V.Z == FloatCmp(_Z), _V.W == FloatCmp(_W)); }

#define CHECK_V4_ALL_ALIASES(V, _X, _Y, _Z, _W) {\
	CHECK4(V.X == _X, V.Y == _Y, V.Z == _Z, V.W == _W); \
	CHECK_V3(V.XYZ, _X, _Y, _Z); \
	CHECK4(V.R == _X, V.G == _Y, V.B == _Z, V.A == _W); \
	CHECK_V3(V.RGB, _X, _Y, _Z); \
	CHECK_V2(V.XY, _X, _Y); \
	CHECK_V2(V.YZ, _Y, _Z); \
	CHECK_V2(V.ZW, _Z, _W); \
	CHECK4(V.Elements[0] == _X, V.Elements[1] == _Y, V.Elements[2] == _Z, V.Elements[3] == _W); }

#define LOG_VEC2(V) \
	INFO("(" << V.X() << ", " << V.Y() << ")");

#define CHECK_VEC2(_V, _X, _Y) {\
	auto R = _V; \
	CHECK2(R.X() == _X, R.Y() == _Y); }

#define CHECK_VEC2_APPROX(_V, _X, _Y) {\
	auto R = _V; \
	CHECK2(R.X() == FloatCmp(_X), R.Y() == FloatCmp(_Y)); }

#define CHECK_VEC2_ALL_ALIASES(_V, _X, _Y) { \
	auto R = _V; \
	CHECK2(R.X() == _X, R.Y() == _Y); \
	CHECK2(R.U() == _X, R.V() == _Y); \
	CHECK2(R.Left() == _X, R.Top() == _Y); \
	CHECK2(R.Width() == _X, R.Height() == _Y); }

#define CHECK_VEC3(_V, _X, _Y, _Z) {\
	auto _Res = _V; \
	CHECK3(_Res.X() == _X, _Res.Y() == _Y, _Res.Z() == _Z) };

#define CHECK_VEC3_APPROX(_V, _X, _Y, _Z) { \
	auto _Res = _V; \
	CHECK3(_Res.X() == FloatCmp(_X), _Res.Y() == FloatCmp(_Y), _Res.Z() == FloatCmp(_Z)); }

#define CHECK_VEC4(_V, _X, _Y, _Z, _W) {\
	auto _Res = _V; \
	CHECK4(_Res.X() == _X, _Res.Y() == _Y, _Res.Z() == _Z, _Res.W() == _W) };

#define CHECK_VEC4_APPROX(_V, _X, _Y, _Z, _W) { \
	auto _Res = _V; \
	CHECK4(_Res.X() == FloatCmp(_X), _Res.Y() == FloatCmp(_Y), _Res.Z() == FloatCmp(_Z), _Res.W() == FloatCmp(_W)); }

#define CHECK_VEC4_1(V, A) \
	CHECK4(V.X() == A, V.Y() == A, V.Z() == A, V.W() == A);

#define CHECK_VEC4_WITH_XYZW_AND_RGBA_GETTERS(V, _X, _Y, _Z, _W) \
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
	CHECK4(_Mat[0] == A, _Mat[1] == E, _Mat[2] == I, _Mat[3] == M); \
	CHECK4(_Mat[4] == B, _Mat[5] == F, _Mat[6] == J, _Mat[7] == N); \
	CHECK4(_Mat[8] == C, _Mat[9] == G, _Mat[10] == K, _Mat[11] == O); \
	CHECK4(_Mat[12] == D, _Mat[13] == H, _Mat[14] == L, _Mat[15] == P); }\

#define CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(Mat, A, B, C, D) {\
	mat4 _Mat = Mat; \
	CHECK4(_Mat[0] == A,   _Mat[5] == B, _Mat[10] == C,  _Mat[15] == D);} \

#define PRINT_MAT4(Mat) \
	mat4 _Mat = Mat; \
	INFO(_Mat[0] << ", " << _Mat[4] << ", " << _Mat[8] << ", " << _Mat[12]); \
    INFO(_Mat[1] << ", " << _Mat[5] << ", " << _Mat[9] << ", " << _Mat[13]); \
	INFO(_Mat[2] << ", " << _Mat[6] << ", " << _Mat[10] << ", " << _Mat[14]); \
    INFO(_Mat[3] << ", " << _Mat[7] << ", " << _Mat[11] << ", " << _Mat[15]); \


#include "utilityFunctions.cpp"
#include "vec2.cpp"
#include "vec3.cpp"
#include "vec4.cpp"
#include "v2.cpp"
#include "v3.cpp"
#include "v4.cpp"
#include "vectorCasting.cpp"
#include "mat4.cpp"


