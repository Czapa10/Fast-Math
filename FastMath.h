/*
FAST MATH
C++ single header math libary
https://github.com/Czapa10/Fast-Math

Made by Grzegorz "Czapa" Bednorz

YOU HAVE TO
#define FM_IMPLEMENTATION
in one of C++ files that include this header, BEFORE the include, like this:

#define FM_IMPLEMENTATION
#include <FastMath.h>
*/

#ifndef FAST_MATH_H
#define FAST_MATH_H

#include <stdint.h>
#include <math.h>

#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
	#include <smmintrin.h>
#else
	#include <emmintrin.h>
#endif

#ifdef _MSC_VER
	__pragma(warning(push))
	__pragma(warning(disable : 4201))
	__pragma(warning(disable : 4146))
#endif

// TODO: make FM_SINL work on all compilers

#define FM_INL __forceinline
#define FM_SINL static __forceinline
#define FM_CALL __vectorcall

#define FM_FUN auto
#define FM_FUN_T template<t> auto
#define FM_FUN_I FM_INL auto
#define FM_FUN_C auto FM_CALL
#define FM_FUN_TI template<class t> FM_INL auto
#define FM_FUN_IC FM_INL auto FM_CALL
#define FM_FUN_SI static FM_INL auto
#define FM_FUN_TSI template<class t> static FM_INL auto
#define FM_FUN_2T template<class t> template<class u> auto
#define FM_FUN_SIC static FM_INL auto FM_CALL

#define FM_GENERIC_FUNCTION(Macro) \
	Macro(, float) Macro(d, double) \
	Macro(i, int32_t) Macro(u, uint32_t) \
	Macro(i64, int64_t) Macro(u64, uint64_t) \
	Macro(i16, int16_t) Macro(u16, uint16_t) \
	Macro(i8, int8_t) Macro(u8, uint8_t)

#ifdef NDEBUG
	#define FM_ASSERT(expression) if(!expression) (*(int32_t*)0 = 0);
	#define FM_ERROR() (*(int32_t*)0 = 0);
#else
	#define FM_ASSERT(expression) 
	#define FM_ERROR() 
#endif

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4715)
 #endif

namespace fm {

static constexpr uint8_t U8Max = 255;
static constexpr uint16_t U16Max = 65535;
static constexpr uint32_t U32Max = ((uint32_t)-1);
static constexpr uint64_t U64Max = ((uint64_t)-1);
static constexpr int32_t I32Min = ((int32_t)0x80000000);
static constexpr int32_t I32Max = ((int32_t)0x7fffffff);

static constexpr float Pi = 3.14159265359f;
static constexpr double Pi64 = 3.14159265358979323846;
static constexpr float Tau = Pi * 2;
static constexpr double Tau64 = Pi64 * 2;

//////////////////////
// type definitions //
//////////////////////

template<class t>
union v2_base
{
	struct { t X, Y; };
	struct { t U, V; };
	struct { t Width, Height; };
	struct { t W, H; };
	t Elements[2];

	v2_base(t X, t Y) :X(X), Y(Y) {}
	explicit v2_base(t XY) :X(XY), Y(XY) {}
	explicit v2_base(const t* Mem) :X(Mem[0]), Y(Mem[1]) {}
	v2_base() = default;

	template<class u> v2_base(v2_base<u> V)
		:X(static_cast<t>(V.X)), Y(static_cast<t>(V.Y)) {}

	FM_FUN_I operator[](uint32_t Index) -> t&; 
};
using v2 = v2_base<float>;
using v2d = v2_base<double>;
using v2i = v2_base<int32_t>;
using v2u = v2_base<uint32_t>;
using v2i64 = v2_base<int64_t>;
using v2u64 = v2_base<uint64_t>;
using v2i16 = v2_base<int16_t>;
using v2u16 = v2_base<uint16_t>;
using v2i8 = v2_base<int8_t>;
using v2u8 = v2_base<uint8_t>;

template<class t>
union v3_base
{
	struct { t X, Y, Z; };
	struct { t U, V, W; };
	struct { t R, G, B; };
	struct { v2_base<t> XY; t Placeholder1_; };
	struct { t Placeholder2_; v2_base<t> YZ; };
	struct { v2_base<t> UV; t Placeholder3_; };
	struct { t Placeholder4_; v2_base<t> VW; };
	struct { v2_base<t> RG; t Placeholder5_; };
	struct { t Placeholder6_; v2_base<t> GB; };
	t Elements[3];

	v3_base(t X, t Y, t Z) :X(X), Y(Y), Z(Z) {}
	v3_base(v2_base<t> XY, t Z) :XY(XY), Z(Z) {}
	v3_base(t X, v2_base<t> YZ) :X(X), YZ(YZ) {}
	explicit v3_base(t XYZ) :X(XYZ), Y(XYZ), Z(XYZ) {}
	explicit v3_base(const t* Mem) :X(Mem[0]), Y(Mem[1]), Z(Mem[2]) {}
	v3_base() = default;

	template<class u> v3_base(v3_base<u> V)
		:X(static_cast<t>(V.X)), Y(static_cast<t>(V.Y)), Z(static_cast<t>(V.Z)) {}

	FM_FUN_I operator[](uint32_t Index) -> t&; 

	FM_FUN_I ZXY() -> v3_base<t>; 
};
using v3 = v3_base<float>;
using v3d = v3_base<double>;
using v3i = v3_base<int32_t>;
using v3u = v3_base<uint32_t>;
using v3i64 = v3_base<int64_t>;
using v3u64 = v3_base<uint64_t>;
using v3i16 = v3_base<int16_t>;
using v3u16 = v3_base<uint16_t>;
using v3i8 = v3_base<int8_t>;
using v3u8 = v3_base<uint8_t>;

template<class t>
union v4_base
{
	struct 
	{
		union 
		{
			v3_base<t> XYZ;
			struct { t X, Y, Z; };
		};
		t W;
	};
	struct
	{
		union 
		{
			v3_base<t> RGB;
			struct { t R, G, B; };
		};
		t A;
	};
	struct {
		v2_base<t> XY;
		t Placeholder1_;
		t Placeholder2_;
	};
	struct {
		t Placeholder3_;
		v2_base<t> YZ;
		t Placeholder4_;
	};
	struct {
		t Placeholder5_;
		t Placeholder6_;
		v2_base<t> ZW;
	};
	t Elements[4];

	v4_base(t X, t Y, t Z, t W) :X(X), Y(Y), Z(Z), W(W) {}
	v4_base(v2_base<t> XY, v2_base<t> ZW) :XY(XY), ZW(ZW) {}
	v4_base(v3_base<t> XYZ, t W) :XYZ(XYZ), W(W) {}
	v4_base(t X, v3_base<t> YZW) :X(X), YZ(YZW.XY), W(YZW.Z) {}
	explicit v4_base(t XYZW) :X(XYZW), Y(XYZW), Z(XYZW), W(XYZW) {}
	explicit v4_base(const t* Mem) :X(Mem[0]), Y(Mem[1]), Z(Mem[2]), W(Mem[3]) {}
	v4_base() = default;

	template<class u> v4_base(v4_base<u> V)
		:X(static_cast<t>(V.X)), Y(static_cast<t>(V.Y)), Z(static_cast<t>(V.Z)), W(static_cast<t>(V.W)) {}

	FM_FUN_I operator[](uint32_t Index) -> t&; 
};
using v4 = v4_base<float>;
using v4d = v4_base<double>;
using v4i = v4_base<int32_t>;
using v4u = v4_base<uint32_t>;
using v4i64 = v4_base<int64_t>;
using v4u64 = v4_base<uint64_t>;
using v4i16 = v4_base<int16_t>;
using v4u16 = v4_base<uint16_t>;
using v4i8 = v4_base<int8_t>;
using v4u8 = v4_base<uint8_t>;

struct alignas(16) vec2
{
	__m128 M;

	FM_INL void FM_CALL SetX(float);
	FM_INL void FM_CALL SetY(float); 

	FM_INL float FM_CALL X() const;
	FM_INL float FM_CALL U() const { return X(); }
	FM_INL float FM_CALL Left() const { return X(); }
	FM_INL float FM_CALL Width() const { return X(); }

	FM_INL float FM_CALL Y() const;
	FM_INL float FM_CALL V() const { return Y(); }
	FM_INL float FM_CALL Top() const { return Y(); }
	FM_INL float FM_CALL Height() const { return Y(); }

	FM_INL vec2 FM_CALL YX() const;
	FM_INL vec2 FM_CALL XX() const;
	FM_INL vec2 FM_CALL YY() const;

	FM_INL void FM_CALL AddX(float);
	FM_INL void FM_CALL AddY(float);

	FM_INL void FM_CALL SubX(float);
	FM_INL void FM_CALL SubY(float);

	FM_INL void FM_CALL MulX(float);
	FM_INL void FM_CALL MulY(float);

	FM_INL void FM_CALL DivX(float);
	FM_INL void FM_CALL DivY(float);
	
	FM_INL float& operator[](uint32_t Index);
};

struct alignas(16) vec2d
{
	__m128d M;

	FM_INL void FM_CALL SetX(double X);
	FM_INL void FM_CALL SetY(double Y);

	FM_INL double FM_CALL X() const;
	FM_INL double FM_CALL U() const { return X(); }
	FM_INL double FM_CALL Left() const { return X(); }
	FM_INL double FM_CALL Width() const { return X(); }

	FM_INL double FM_CALL Y() const;
	FM_INL double FM_CALL V() const { return Y(); }
	FM_INL double FM_CALL Height() const { return Y(); }
	FM_INL double FM_CALL Top() const { return Y(); }

	FM_INL vec2d FM_CALL YX() const;
	FM_INL vec2d FM_CALL XX() const;
	FM_INL vec2d FM_CALL YY() const;

	FM_INL vec2d FM_CALL VU() const { return YX(); }
	FM_INL vec2d FM_CALL UU() const { return XX(); }
	FM_INL vec2d FM_CALL VV() const { return YY(); }

	FM_INL void FM_CALL AddX(double);
	FM_INL void FM_CALL AddY(double);

	FM_INL void FM_CALL SubX(double);
	FM_INL void FM_CALL SubY(double);

	FM_INL void FM_CALL MulX(double);
	FM_INL void FM_CALL MulY(double);

	FM_INL void FM_CALL DivX(double);
	FM_INL void FM_CALL DivY(double);
	
	FM_INL double& operator[](uint32_t Index);

	// TODO: Copy constructor and assign operator
};

struct alignas(16) vec2i
{
	__m128i M;

	FM_INL void FM_CALL SetX(int32_t);
	FM_INL void FM_CALL SetY(int32_t);

	FM_INL int32_t FM_CALL X() const;
	FM_INL int32_t FM_CALL U() const { return X(); }
	FM_INL int32_t FM_CALL Left() const { return X(); }
	FM_INL int32_t FM_CALL Width() const { return X(); }

	FM_INL int32_t FM_CALL Y() const;
	FM_INL int32_t FM_CALL V() const { return Y(); }
	FM_INL int32_t FM_CALL Top() const { return Y(); }
	FM_INL int32_t FM_CALL Height() const { return Y(); }

	FM_INL vec2i FM_CALL YX() const;
	FM_INL vec2i FM_CALL XX() const;
	FM_INL vec2i FM_CALL YY() const;

	FM_INL vec2i FM_CALL VU() const { return YX(); }
	FM_INL vec2i FM_CALL UU() const { return XX(); }
	FM_INL vec2i FM_CALL VV() const { return YY(); }

	FM_INL void FM_CALL AddX(int32_t);
	FM_INL void FM_CALL AddY(int32_t);

	FM_INL void FM_CALL SubX(int32_t);
	FM_INL void FM_CALL SubY(int32_t);

	FM_INL void FM_CALL MulX(int32_t);
	FM_INL void FM_CALL MulY(int32_t);

	FM_INL void FM_CALL DivX(int32_t);
	FM_INL void FM_CALL DivY(int32_t);
	
	FM_INL int32_t& operator[](uint32_t Index);

	// TODO: Copy constructor and assign operator
};

struct alignas(16) vec2u
{
	__m128i M;

	FM_INL void FM_CALL SetX(uint32_t);
	FM_INL void FM_CALL SetY(uint32_t);

	FM_INL uint32_t FM_CALL X() const;
	FM_INL uint32_t FM_CALL U() const { return X(); }
	FM_INL uint32_t FM_CALL Left() const { return X(); }
	FM_INL uint32_t FM_CALL Width() const { return X(); }

	FM_INL uint32_t FM_CALL Y() const;
	FM_INL uint32_t FM_CALL V() const { return Y(); }
	FM_INL uint32_t FM_CALL Top() const { return Y(); }
	FM_INL uint32_t FM_CALL Height() const { return Y(); }

	FM_INL vec2u FM_CALL YX() const;
	FM_INL vec2u FM_CALL XX() const;
	FM_INL vec2u FM_CALL YY() const;

	FM_INL vec2u FM_CALL VU() const { return YX(); }
	FM_INL vec2u FM_CALL UU() const { return XX(); }
	FM_INL vec2u FM_CALL VV() const { return YY(); }

	FM_INL void FM_CALL AddX(uint32_t);
	FM_INL void FM_CALL AddY(uint32_t);

	FM_INL void FM_CALL SubX(uint32_t);
	FM_INL void FM_CALL SubY(uint32_t);

	FM_INL void FM_CALL MulX(uint32_t);
	FM_INL void FM_CALL MulY(uint32_t);

	FM_INL void FM_CALL DivX(uint32_t);
	FM_INL void FM_CALL DivY(uint32_t);
	
	FM_INL uint32_t& operator[](uint32_t Index);

	// TODO: Copy constructor and assign operator
};

struct alignas(16) vec3
{
	__m128 M;

	FM_INL void FM_CALL SetX(float X);
	FM_INL void FM_CALL SetY(float Y);
	FM_INL void FM_CALL SetZ(float Z);

	FM_INL void FM_CALL AddX(float X);
	FM_INL void FM_CALL AddY(float Y);
	FM_INL void FM_CALL AddZ(float Z);

	FM_INL void FM_CALL SubX(float X);
	FM_INL void FM_CALL SubY(float Y);
	FM_INL void FM_CALL SubZ(float Z);

	FM_INL void FM_CALL MulX(float X);
	FM_INL void FM_CALL MulY(float Y);
	FM_INL void FM_CALL MulZ(float Z);

	FM_INL void FM_CALL DivX(float X);
	FM_INL void FM_CALL DivY(float Y);
	FM_INL void FM_CALL DivZ(float Z);

	FM_INL float FM_CALL X() const;
	FM_INL float FM_CALL U() const { return X(); }
	FM_INL float FM_CALL R() const { return X(); }

	FM_INL float FM_CALL Y() const;
	FM_INL float FM_CALL V() const { return Y(); }
	FM_INL float FM_CALL G() const { return Y(); }

	FM_INL float FM_CALL Z() const;
	FM_INL float FM_CALL W() const { return Z(); }
	FM_INL float FM_CALL B() const { return Z(); }

	FM_INL vec3 FM_CALL ZXY() const;

	FM_INL float& operator[](uint32_t Index); 
};

struct alignas(16) vec4
{
	__m128 M;

	FM_INL void FM_CALL SetX(float);
	FM_INL void FM_CALL SetY(float); 
	FM_INL void FM_CALL SetZ(float); 
	FM_INL void FM_CALL SetW(float); 

	FM_INL void FM_CALL AddX(float);
	FM_INL void FM_CALL AddY(float); 
	FM_INL void FM_CALL AddZ(float); 
	FM_INL void FM_CALL AddW(float); 

	FM_INL void FM_CALL SubX(float);
	FM_INL void FM_CALL SubY(float); 
	FM_INL void FM_CALL SubZ(float); 
	FM_INL void FM_CALL SubW(float); 

	FM_INL void FM_CALL MulX(float);
	FM_INL void FM_CALL MulY(float); 
	FM_INL void FM_CALL MulZ(float); 
	FM_INL void FM_CALL MulW(float); 

	FM_INL void FM_CALL DivX(float);
	FM_INL void FM_CALL DivY(float); 
	FM_INL void FM_CALL DivZ(float); 
	FM_INL void FM_CALL DivW(float); 

	FM_INL float FM_CALL X() const;
	FM_INL float FM_CALL Y() const;
	FM_INL float FM_CALL Z() const;
	FM_INL float FM_CALL W() const;

	FM_INL float FM_CALL R() const { return X(); }
	FM_INL float FM_CALL G() const { return Y(); }
	FM_INL float FM_CALL B() const { return Z(); }
	FM_INL float FM_CALL A() const { return W(); }

	FM_INL float& operator[](uint32_t Index);
};

template<class t>
struct rect2_base
{
	v2_base<t> Min, Max;

	rect2_base() = default;
	template<class u> rect2_base(rect2_base<u>); 
};
using rect2 = rect2_base<float>;
using rect2d = rect2_base<double>;
using rect2i = rect2_base<int32_t>;
using rect2u = rect2_base<uint32_t>;
using rect2i64 = rect2_base<int64_t>;
using rect2u64 = rect2_base<uint64_t>;
using rect2i16 = rect2_base<int16_t>;
using rect2u16 = rect2_base<uint16_t>;
using rect2i8 = rect2_base<int8_t>;
using rect2u8 = rect2_base<uint8_t>;

struct alignas(16) mat4
{
	__m128 Columns[4];

	FM_FUN_IC GetColumnV4(uint32_t Index) -> v4;
	FM_FUN_IC GetColumnVec4(uint32_t Index) -> vec4; 
	FM_FUN_IC SetColumn(uint32_t Index, v4 Col) -> void;
	FM_FUN_IC SetColumn(uint32_t Index, vec4 Col) -> void;
	FM_FUN_IC SetColumn(uint32_t Index, float X, float Y, float Z, float W) -> void;
	FM_FUN_IC SwapColumns(uint32_t Col1Index, uint32_t Col2Index) -> void; 

	FM_FUN_C GetRowV4(uint32_t Index) -> v4;
	FM_FUN_C GetRowVec4(uint32_t Index) -> vec4;
	FM_FUN_C SetRow(uint32_t Index, v4 Row) -> void;
	FM_FUN_C SetRow(uint32_t Index, vec4 Row) -> void;
	FM_FUN_IC SetRow(uint32_t Index, float X, float Y, float Z, float W) -> void;
	FM_FUN_IC SwapRows(uint32_t Row1Index, uint32_t Row2Index) -> void; 

	FM_FUN_IC GetMainDiagonalV4() -> v4;
	FM_FUN_IC GetMainDiagonalVec4() -> vec4;
	FM_FUN_IC SetMainDiagonal(float X, float Y, float Z, float W) -> void; 
	FM_FUN_IC SetMainDiagonal(v4) -> void;
	FM_FUN_IC SetMainDiagonal(vec4) -> void;

	FM_FUN_I operator[](uint32_t Index) -> float&; 
};

///////////////////////////////////
// forward function declarations //
///////////////////////////////////
FM_SINL void FM_CALL Store(float* Mem, vec2 V); 
FM_SINL void FM_CALL Store(float* Mem, vec3 V); 
FM_SINL void FM_CALL Store(float* Mem, vec4 V); 
FM_SINL vec2 FM_CALL Vec2(v2 V); 
FM_SINL vec3 FM_CALL Vec3(v3 V); 
FM_SINL vec4 FM_CALL Vec4(v4 V); 

///////////////////////
// utility functions //
///////////////////////
FM_FUN_TSI Min(t A, t B) -> t {
	return A < B ? A : B; 
}
FM_FUN_TSI Max(t A, t B) -> t {
	return A > B ? A : B;
}
FM_FUN_TSI Abs(t A) -> t {
	return A < 0 ? -A : A;
}
FM_FUN_TSI Abs(t* A) -> void {
	*A = *A < 0 ? -(*A) : *A;
}
FM_FUN_TSI Square(t A) -> t {
	return A * A;
}
FM_FUN_TSI Square(t* A) -> void {
	*A = (*A) * (*A);
}
FM_FUN_SI RadiansToDegrees(float Radians) -> float {
	return Radians * 180.f / Pi;
}
FM_FUN_SI RadiansToDegrees(double Radians) -> double {
	return Radians * 180.0 / Pi64;
}
FM_FUN_SI DegreesToRadians(float Degrees) -> float {
	return Degrees * Pi / 180.f;
}
FM_FUN_SI DegreesToRadians(double Degrees) -> double {
	return Degrees * Pi64 / 180.0;
}
FM_FUN_TSI SafeDivN(t Numerator, t Divisor, t N) -> t {
	if(Divisor != 0)
		return Numerator / Divisor;
	return N;
}
FM_FUN_TSI SafeDiv1(t Numerator, t Divisor) -> t {
	return SafeDivN<t>(Numerator, Divisor, 1);
}
FM_FUN_TSI SafeDiv0(t Numerator, t Divisor) -> t {
	return SafeDivN<t>(Numerator, Divisor, 0);
}

/////////////////////////////////////////
// fast math internal helper functions //
/////////////////////////////////////////
namespace priv {
	FM_SINL __m128 FM_CALL SetX(__m128 m, float x) {
		return _mm_move_ss(m, _mm_set_ss(x));
	}
	FM_SINL __m128 FM_CALL SetY(__m128 m, float y) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(y));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 0));
		return _mm_move_ss(temp, m);
	}
	FM_SINL __m128 FM_CALL SetZ(__m128 m, float z) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(z));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 0, 1, 0));
		return _mm_move_ss(temp, m);
	}
	FM_SINL __m128 FM_CALL SetW(__m128 m, float w) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(w));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(0, 2, 1, 0));
		return _mm_move_ss(temp, m);
	}
	FM_SINL float FM_CALL GetX(__m128 m) {
		return _mm_cvtss_f32(m);
	}
	FM_SINL float FM_CALL GetY(__m128 m) {
		return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 1)));
	}
	FM_SINL float FM_CALL GetZ(__m128 m) {
		return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 2)));
	}
	FM_SINL float FM_CALL GetW(__m128 m) {
		return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 3)));
	}
	FM_SINL float FM_CALL SumOfElements(__m128 m) {
		return GetX(m) + GetY(m) + GetZ(m) + GetW(m);
	}
}

//////////////////
// v2 functions //
//////////////////
FM_FUN_TI v2_base<t>::operator[](uint32_t Index) -> t& {
	FM_ASSERT(Index == 0 || Index == 1);
	return Elements[Index];
}
FM_FUN_TSI Ptr(v2_base<t>& V) -> t* {
	return &V.X; 
}
FM_FUN_TSI PtrY(v2_base<t>& V) -> t* {
	return &V.Y; 
}
FM_FUN_TSI Store(t* Mem, v2_base<t> V) -> void {
	Mem[0] = V.X;
	Mem[1] = V.Y;
}
FM_FUN_TSI operator+(v2_base<t> A, v2_base<t> B) -> v2_base<t> {
	v2_base<t> R;
	R.X = A.X + B.X;
	R.Y = A.Y + B.Y;
	return R;
}
FM_FUN_TSI operator-(v2_base<t> A, v2_base<t> B) -> v2_base<t> {
	v2_base<t> R;
	R.X = A.X - B.X;
	R.Y = A.Y - B.Y;
	return R;
}
FM_FUN_TSI operator+=(v2_base<t>& A, v2_base<t> B) -> v2_base<t> {
	A.X += B.X;
	A.Y += B.Y;
	return A;
}
FM_FUN_TSI operator-=(v2_base<t>& A, v2_base<t> B) -> v2_base<t> {
	A.X -= B.X;
	A.Y -= B.Y;
	return A;
}
FM_FUN_TSI HadamardMul(v2_base<t> A, v2_base<t> B) -> v2_base<t> {
	v2_base<t> R;
	R.X = A.X * B.X;
	R.Y = A.Y * B.Y;
	return R;
} 
FM_FUN_TSI HadamardDiv(v2_base<t> A, v2_base<t> B) -> v2_base<t> {
	v2_base<t> R;
	R.X = A.X / B.X;
	R.Y = A.Y / B.Y;
	return R;
}
FM_FUN_TSI SafeHadamardDivN(v2_base<t> A, v2_base<t> B, v2_base<t> N) -> v2_base<t> {
	v2_base<t> R;
	R.X = B.X != 0 ? A.X / B.X : N.X;
	R.Y = B.Y != 0 ? A.Y / B.Y : N.Y;
	return R;
}
FM_FUN_TSI SafeHadamardDiv1(v2_base<t> A, v2_base<t> B) -> v2_base<t> {
	return SafeHadamardDivN<t>(A, B, v2_base<t>((t)1));
}
FM_FUN_TSI SafeHadamardDiv0(v2_base<t> A, v2_base<t> B) -> v2_base<t> {
	return SafeHadamardDivN<t>(A, B, v2_base<t>((t)0));
}
FM_FUN_TSI operator*(v2_base<t> V, t Scalar) -> v2_base<t> {
	V.X *= Scalar;
	V.Y *= Scalar;
	return V;
}
FM_FUN_TSI operator*(t Scalar, v2_base<t> V) -> v2_base<t> {
	return V * Scalar;
}
FM_FUN_TSI operator*=(v2_base<t>& V, t Scalar) -> v2_base<t>& {
	V = V * Scalar;	
	return V;
}
FM_FUN_TSI operator/(v2_base<t> V, t Scalar) -> v2_base<t> {
	V.X /= Scalar;
	V.Y /= Scalar;
	return V;
}
FM_FUN_TSI operator/=(v2_base<t>& V, t Scalar) -> v2_base<t>& {
	V = V / Scalar;
	return V;
} 
FM_FUN_TSI operator-(v2_base<t> V) -> v2_base<t> {
	V.X = -V.X;
	V.Y = -V.Y;
	return V;
} 
FM_FUN_TSI Dot(v2_base<t> A, v2_base<t> B) -> t {
	return A.X * B.X + A.Y * B.Y;
} 
FM_FUN_TSI Min(v2_base<t> A, v2_base<t> B) -> v2_base<t> {
	v2_base<t> R;
	R.X = Min(A.X, B.X);	
	R.Y = Min(A.Y, B.Y);	
	return R;
}
FM_FUN_TSI Max(v2_base<t> A, v2_base<t> B) -> v2_base<t> {
	v2_base<t> R;
	R.X = Max(A.X, B.X);
	R.Y = Max(A.Y, B.Y);
	return R;
} 
FM_FUN_TSI Abs(v2_base<t> V) -> v2_base<t> {
	v2_base<t> R;
	R.X = Abs(V.X);
	R.Y = Abs(V.Y);
	return R;
} 
FM_FUN_TSI SumOfElements(v2_base<t> V) -> t {
	return V.X + V.Y;
}
FM_FUN_TSI Length(v2_base<t> V) -> t {
	return static_cast<t>(sqrt(V.X * V.X + V.Y * V.Y));
}
FM_FUN_TSI LengthSquared(v2_base<t> V) -> t {
	return V.X * V.X + V.Y * V.Y;
} 
FM_FUN_TSI Normalize(v2_base<t> V) -> v2_base<t> {
	return V / Length(V);
}
FM_FUN_TSI Normalize(v2_base<t>* V) -> void {
	*V = *V / Length(*V);
}
FM_FUN_TSI Clamp(v2_base<t> V, v2_base<t> MinV, v2_base<t> MaxV) -> v2_base<t> {
	return Min(Max(V, MinV), MaxV);
}
FM_FUN_TSI Lerp(v2_base<t> A, v2_base<t> B, float T) -> v2_base<t> {
	v2 fA = static_cast<v2>(A);
	v2 fB = static_cast<v2>(B);
	return static_cast<v2_base<t>>(fA + (fB - fA)*T);
}
FM_FUN_TSI operator==(v2_base<t> A, v2_base<t> B) -> bool {
	return A.X == B.X && A.Y == B.Y;
}
FM_FUN_TSI operator!=(v2_base<t> A, v2_base<t> B) -> bool {
	return A.X != B.X || A.X != B.X;
}

//////////////////
// v3 functions //
//////////////////
FM_FUN_TI v3_base<t>::operator[](uint32_t Index) -> t& {
	FM_ASSERT(Index >= 0 && Index <= 2);
	return Elements[Index];
}
FM_FUN_TI v3_base<t>::ZXY() -> v3_base<t> { 
	return v3_base<t>(Z, X, Y); 
}
FM_FUN_TSI Store(t* Mem, v3_base<t> V) -> void {
	Mem[0] = V.X;
	Mem[1] = V.Y;
	Mem[2] = V.Z;
}
FM_FUN_TSI Ptr(v3_base<t>& V) -> t* {
	return &V.X; 
}
FM_FUN_TSI PtrY(v3_base<t>& V) -> t* {
	return &V.Y; 
}
FM_FUN_TSI PtrZ(v3_base<t>& V) -> t* {
	return &V.Z; 
}
FM_FUN_TSI operator+(v3_base<t> A, v3_base<t> B) -> v3_base<t> {
	v3_base<t> R;
	R.X = A.X + B.X;
	R.Y = A.Y + B.Y;
	R.Z = A.Z + B.Z;
	return R;
}
FM_FUN_TSI operator-(v3_base<t> A, v3_base<t> B) -> v3_base<t> {
	v3_base<t> R;
	R.X = A.X - B.X;
	R.Y = A.Y - B.Y;
	R.Z = A.Z - B.Z;
	return R;
}
FM_FUN_TSI operator+=(v3_base<t>& A, v3_base<t> B) -> v3_base<t>& {
	A = A + B;
	return A;
}
FM_FUN_TSI operator-=(v3_base<t>& A, v3_base<t> B) -> v3_base<t>& {
	A = A - B;
	return A;
}
FM_FUN_TSI HadamardMul(v3_base<t> A, v3_base<t> B) -> v3_base<t> {
	v3_base<t> R;
	R.X = A.X * B.X;
	R.Y = A.Y * B.Y;
	R.Z = A.Z * B.Z;
	return R;
}
FM_FUN_TSI HadamardDiv(v3_base<t> A, v3_base<t> B) -> v3_base<t> {
	v3_base<t> R;
	R.X = A.X / B.X;
	R.Y = A.Y / B.Y;
	R.Z = A.Z / B.Z;
	return R;
}
FM_FUN_TSI SafeHadamardDivN(v3_base<t> A, v3_base<t> B, v3_base<t> N) -> v3_base<t> {
	v3_base<t> R;
	R.X = B.X != 0 ? A.X / B.X : N.X;
	R.Y = B.Y != 0 ? A.Y / B.Y : N.Y;
	R.Z = B.Z != 0 ? A.Z / B.Z : N.Z;
	return R;
}
FM_FUN_TSI SafeHadamardDiv1(v3_base<t> A, v3_base<t> B) -> v3_base<t> {
	return SafeHadamardDivN<t>(A, B, v3_base<t>((t)1));
}
FM_FUN_TSI SafeHadamardDiv0(v3_base<t> A, v3_base<t> B) -> v3_base<t> {
	return SafeHadamardDivN<t>(A, B, v3_base<t>((t)0));
}
FM_FUN_TSI operator*(v3_base<t> V, t Scalar) -> v3_base<t> {
	V.X *= Scalar;
	V.Y *= Scalar;
	V.Z *= Scalar;
	return V;
}
FM_FUN_TSI operator*(t Scalar, v3_base<t> V) -> v3_base<t> {
	return V * Scalar;
}
FM_FUN_TSI operator*=(v3_base<t>& V, t Scalar) -> v3_base<t>& {
	V = V * Scalar;
	return V;
}
FM_FUN_TSI operator/(v3_base<t> V, t Scalar) -> v3_base<t> {
	V.X /= Scalar;
	V.Y /= Scalar;
	V.Z /= Scalar;
	return V;
}
FM_FUN_TSI operator/=(v3_base<t>& V, t Scalar) -> v3_base<t>& {
	V = V / Scalar;
	return V;
}
FM_FUN_TSI operator-(v3_base<t> V) -> v3_base<t> {
	V.X = -V.X;
	V.Y = -V.Y;
	V.Z = -V.Z;
	return V;
}
FM_FUN_TSI Cross(v3_base<t> A, v3_base<t> B) -> v3_base<t> {
	return v3_base<t>(HadamardMul(A.ZXY(), B) - HadamardMul(A, B.ZXY())).ZXY();
}
FM_FUN_TSI Dot(v3_base<t> A, v3_base<t> B) -> t {
	return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
}
FM_FUN_TSI Min(v3_base<t> A, v3_base<t> B) -> v3_base<t> {
	v3_base<t> R;
	R.X = Min(A.X, B.X);
	R.Y = Min(A.Y, B.Y);
	R.Z = Min(A.Z, B.Z);
	return R;
}
FM_FUN_TSI Max(v3_base<t> A, v3_base<t> B) -> v3_base<t> {
	v3_base<t> R;
	R.X = Max(A.X, B.X);
	R.Y = Max(A.Y, B.Y);
	R.Z = Max(A.Z, B.Z);
	return R;
} 
FM_FUN_TSI Abs(v3_base<t> V) -> v3_base<t> {
	V.X = Abs(V.X);
	V.Y = Abs(V.Y);
	V.Z = Abs(V.Z);
	return V;
}
FM_FUN_TSI SumOfElements(v3_base<t> V) -> t {
	return V.X + V.Y + V.Z;
}
FM_FUN_TSI Length(v3_base<t> V) -> t {
	return sqrtf(V.X * V.X + V.Y * V.Y + V.Z * V.Z);
}
FM_FUN_TSI LengthSquared(v3_base<t> V) -> t {
	return V.X * V.X + V.Y * V.Y + V.Z * V.Z;
} 
FM_FUN_TSI Normalize(v3_base<t> V) -> v3_base<t> {
	return V / Length(V);
}
FM_FUN_TSI Normalize(v3_base<t>* V) -> void {
	*V = *V / Length(*V);
}
FM_FUN_TSI Clamp(v3_base<t> V, v3_base<t> MinV, v3_base<t> MaxV) -> v3_base<t> {
	return Min(Max(V, MinV), MaxV);	
} 
FM_FUN_TSI Lerp(v3_base<t> A, v3_base<t> B, t T) -> v3_base<t> {
	return A + (B - A) * T;
}
FM_FUN_TSI operator==(v3_base<t> A, v3_base<t> B) -> bool {
	return A.X == B.X && A.Y == B.Y && A.Z == B.Z;
}
FM_FUN_TSI operator!=(v3_base<t> A, v3_base<t> B) -> bool {
	return !(A == B);
}

//////////////////
// v4 functions //
//////////////////
FM_FUN_TI v4_base<t>::operator[](uint32_t Index) -> t& {
	FM_ASSERT(Index >= 0 && Index <= 3);
	return Elements[Index];
}
FM_FUN_TSI Ptr(v4_base<t>& V) -> t* {
	return &V.X; 
}
FM_FUN_TSI PtrY(v4_base<t>& V) -> t* {
	return &V.Y; 
}
FM_FUN_TSI PtrZ(v4_base<t>& V) -> t* {
	return &V.Z; 
}
FM_FUN_TSI PtrW(v4_base<t>& V) -> t* {
	return &V.W; 
}
FM_FUN_TSI Store(t* Mem, v4_base<t> V) -> void {
	Mem[0] = V.X;
	Mem[1] = V.Y;
	Mem[2] = V.Z;
	Mem[3] = V.W;
}
FM_FUN_TSI operator+(v4_base<t> A, v4_base<t> B) -> v4_base<t> {
	v4_base<t> R;
	R.X = A.X + B.X;
	R.Y = A.Y + B.Y;
	R.Z = A.Z + B.Z;
	R.W = A.W + B.W;
	return R;
} 
FM_FUN_TSI operator-(v4_base<t> A, v4_base<t> B) -> v4_base<t> {
	v4_base<t> R;
	R.X = A.X - B.X;
	R.Y = A.Y - B.Y;
	R.Z = A.Z - B.Z;
	R.W = A.W - B.W;
	return R;
}
FM_FUN_TSI operator+=(v4_base<t>& A, v4_base<t> B) -> v4_base<t>& {
	A = A + B;
	return A;
}
FM_FUN_TSI operator-=(v4_base<t>& A, v4_base<t> B) -> v4_base<t>& {
	A = A - B;
	return A;
}
FM_FUN_TSI HadamardMul(v4_base<t> A, v4_base<t> B) -> v4_base<t> {
	v4_base<t> R;
	R.X = A.X * B.X;
	R.Y = A.Y * B.Y;
	R.Z = A.Z * B.Z;
	R.W = A.W * B.W;
	return R;
}
FM_FUN_TSI HadamardDiv(v4_base<t> A, v4_base<t> B) -> v4_base<t> {
	v4_base<t> R;
	R.X = A.X / B.X;
	R.Y = A.Y / B.Y;
	R.Z = A.Z / B.Z;
	R.W = A.W / B.W;
	return R;
}
FM_FUN_TSI SafeHadamardDivN(v4_base<t> A, v4_base<t> B, v4_base<t> N) -> v4_base<t> {
	v4_base<t> R;
	R.X = B.X != 0 ? A.X / B.X : N.X;
	R.Y = B.Y != 0 ? A.Y / B.Y : N.Y;
	R.Z = B.Z != 0 ? A.Z / B.Z : N.Z;
	R.W = B.W != 0 ? A.W / B.W : N.W;
	return R;
}
FM_FUN_TSI SafeHadamardDiv1(v4_base<t> A, v4_base<t> B) -> v4_base<t> {
	return SafeHadamardDivN<t>(A, B, v4_base<t>((t)1));
}
FM_FUN_TSI SafeHadamardDiv0(v4_base<t> A, v4_base<t> B) -> v4_base<t> {
	return SafeHadamardDivN<t>(A, B, v4_base<t>((t)0));
}
FM_FUN_TSI operator*(v4_base<t> V, t Scalar) -> v4_base<t> {
	V.X *= Scalar;
	V.Y *= Scalar;
	V.Z *= Scalar;
	V.W *= Scalar;
	return V;
}
FM_FUN_TSI operator*(t Scalar, v4_base<t> V) -> v4_base<t> {
	return V * Scalar;
}
FM_FUN_TSI operator*=(v4_base<t>& V, t Scalar) -> v4_base<t>& {
	V = V * Scalar;
	return V;
}
FM_FUN_TSI operator/(v4_base<t> V, t Scalar) -> v4_base<t> {
	V.X /= Scalar;
	V.Y /= Scalar;
	V.Z /= Scalar;
	V.W /= Scalar;
	return V;
}
FM_FUN_TSI operator/=(v4_base<t>& V, t Scalar) -> v4_base<t>& {
	V = V / Scalar;
	return V;
}
FM_FUN_TSI operator-(v4_base<t> V) -> v4_base<t> {
	V.X = -V.X;
	V.Y = -V.Y;
	V.Z = -V.Z;
	V.W = -V.W;
	return V;
} 
FM_FUN_TSI Dot(v4_base<t> A, v4_base<t> B) -> t {
	return A.X * B.X + A.Y * B.Y + A.Z * B.Z + A.W * B.W;
} 
FM_FUN_TSI Min(v4_base<t> A, v4_base<t> B) -> v4_base<t> {
	v4_base<t> R;
	R.X = Min(A.X, B.X);
	R.Y = Min(A.Y, B.Y);
	R.Z = Min(A.Z, B.Z);
	R.W = Min(A.W, B.W);
	return R;
} 
FM_FUN_TSI Max(v4_base<t> A, v4_base<t> B) -> v4_base<t> {
	v4_base<t> R;
	R.X = Max(A.X, B.X);
	R.Y = Max(A.Y, B.Y);
	R.Z = Max(A.Z, B.Z);
	R.W = Max(A.W, B.W);
	return R;
}
FM_FUN_TSI Abs(v4_base<t> V) -> v4_base<t> {
	V.X = Abs(V.X);
	V.Y = Abs(V.Y);
	V.Z = Abs(V.Z);
	V.W = Abs(V.W);
	return V;
}
FM_FUN_TSI SumOfElements(v4_base<t> V) -> t {
	return V.X + V.Y + V.Z + V.W;
}
FM_FUN_TSI Length(v4_base<t> V) -> t {
	return sqrtf(Dot(V, V));
}
FM_FUN_TSI LengthSquared(v4_base<t> V) -> t {
	return Dot(V, V);
} 
FM_FUN_TSI Normalize(v4_base<t> V) -> v4_base<t> {
	return V / Length(V);
}
FM_FUN_TSI Normalize(v4_base<t>* V) -> void {
	*V = *V / Length(*V);
}
FM_FUN_TSI Clamp(v4_base<t> V, v4_base<t> MinV, v4_base<t> MaxV) -> v4_base<t> {
	return Min(Max(V, MinV), MaxV);
} 
FM_FUN_TSI Lerp(v4_base<t> A, v4_base<t> B, t T) -> v4_base<t> {
	return A + (B - A) * T;
}
FM_FUN_TSI operator==(v4_base<t> A, v4_base<t> B) -> bool {
	return A.X == B.X && A.Y == B.Y && A.Z == B.Z && A.W == B.W;
} 
FM_FUN_TSI operator!=(v4_base<t> A, v4_base<t> B) -> bool {
	return !(A == B);
} 

////////////////////
// vec2 functions //
////////////////////
FM_SINL vec2 FM_CALL Vec2FromMemory(const float* V) {
	vec2 R;
	R.M = _mm_set_ps(0.f, 0.f, V[1], V[0]); 
	return R;
} 
FM_SINL vec2 FM_CALL Vec2(float X, float Y) {
	vec2 R;
	R.M = _mm_set_ps(0.f, 0.f, Y, X); 
	return R;
}
FM_SINL vec2 FM_CALL Vec2(float XY) {
	vec2 R;
	R.M = _mm_set1_ps(XY); 
	return R;
}
FM_SINL vec2 FM_CALL Vec2(__m128 M) {
	vec2 R;
	R.M = M;
	return R;
}
FM_SINL vec2 FM_CALL Vec2() {
	vec2 R;
	R.M = _mm_setzero_ps(); 
	return R;
}
FM_INL float& vec2::operator[](uint32_t Index) {
	FM_ASSERT(Index == 0 || Index == 1);
	return *((float*)(&M) + Index);
}
FM_INL void FM_CALL vec2::SetX(float X) {
	M = priv::SetX(M, X); 
}
FM_INL void FM_CALL vec2::SetY(float Y) { 
	M = priv::SetY(M, Y);
}
FM_INL float FM_CALL vec2::X() const { 
	return priv::GetX(M); 
}
FM_INL float FM_CALL vec2::Y() const {
	return priv::GetY(M); 
}
FM_INL void FM_CALL vec2::AddX(float X) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INL void FM_CALL vec2::AddY(float Y) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INL void FM_CALL vec2::SubX(float X) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INL void FM_CALL vec2::SubY(float Y) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INL void FM_CALL vec2::MulX(float X) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INL void FM_CALL vec2::MulY(float Y) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INL void FM_CALL vec2::DivX(float X) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INL void FM_CALL vec2::DivY(float Y) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_SINL float* Ptr(vec2& V) {
	return (float*)(&V); 
}
FM_SINL float* PtrY(vec2& V) {
	return (float*)(&V) + 1; 
}
FM_SINL void FM_CALL Store(float* Mem, vec2 V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
} 
FM_SINL void FM_CALL Store16ByteAligned(float* Mem, vec2 V) {
	FM_ASSERT(Mem % 16 == 0);
	_mm_store_ps(Mem, V.M);
}
FM_SINL vec2 FM_CALL operator+(vec2 A, vec2 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A; 
}
FM_SINL vec2 FM_CALL operator-(vec2 A, vec2 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A; 
}
FM_SINL vec2& FM_CALL operator+=(vec2& A, vec2 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A; 
}
FM_SINL vec2& FM_CALL operator-=(vec2& A, vec2 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A; 
}
FM_SINL vec2 FM_CALL HadamardMul(vec2 A, vec2 B) {
	A.M = _mm_mul_ps(A.M, B.M);
	return A;
}
FM_SINL vec2 FM_CALL HadamardDiv(vec2 A, vec2 B) {
	A.M = _mm_div_ps(A.M, B.M);
	return A; 
}
FM_SINL vec2 FM_CALL operator*(vec2 V, float Scalar) {
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar)); 
	return V; 
}
FM_SINL vec2 FM_CALL operator*(float Scalar, vec2 V) { 
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar));
	return V; 
}
FM_SINL vec2& FM_CALL operator*=(vec2& V, float Scalar) {
	V = V * Scalar;
	return V;
}
FM_SINL vec2 FM_CALL operator/(vec2 V, float Scalar) {
	V.M = _mm_div_ps(V.M, _mm_set1_ps(Scalar));
	return V; 
}
FM_SINL vec2& FM_CALL operator/=(vec2& V, float Scalar) {
	V = V / Scalar;
	return V;
} 
FM_SINL vec2 FM_CALL operator-(vec2 V) {
	V.M = _mm_sub_ps(_mm_setzero_ps(), V.M);
	return V;
}
FM_SINL float FM_CALL SumOfElements(vec2 V) {
	return V.X() + V.Y();
}
FM_SINL float FM_CALL Dot(vec2 A, vec2 B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_SINL vec2 FM_CALL Min(vec2 A, vec2 B) {
	A.M = _mm_min_ps(A.M, B.M);
	return A;
}
FM_SINL vec2 FM_CALL Max(vec2 A, vec2 B) {
	A.M = _mm_max_ps(A.M, B.M);
	return A;
}
FM_SINL vec2 FM_CALL Abs(vec2 V) {
	__m128 SignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000)); 
	V.M = _mm_andnot_ps(SignMask, V.M);
	return V;
}
FM_SINL float FM_CALL Length(vec2 V) {
	return sqrtf(Dot(V, V));
}
FM_SINL float FM_CALL LengthSquared(vec2 V) {
	return Dot(V, V);
}
FM_SINL vec2 FM_CALL Normalize(vec2 V) {
	return V / Length(V);
}
FM_SINL void Normalize(vec2* V) {
	*V = *V / Length(*V);
}
FM_SINL vec2 FM_CALL Clamp(vec2 V, vec2 MinV, vec2 MaxV) {
	return Min(Max(V, MinV), MaxV);
}
FM_SINL vec2 FM_CALL Lerp(vec2 A, vec2 B, float T) {
	return A + (B-A)*T;
}
FM_SINL vec2 FM_CALL EqualsMask(vec2 A, vec2 B) {
	A.M = _mm_cmpeq_ps(A.M, B.M);
	return A;
}
FM_SINL vec2 FM_CALL GreaterMask(vec2 A, vec2 B) {
	A.M = _mm_cmpgt_ps(A.M, B.M);
	return A;
}
FM_SINL vec2 FM_CALL GreaterOrEqualMask(vec2 A, vec2 B) {
	A.M = _mm_cmpge_ps(A.M, B.M);
	return A;
}
FM_SINL vec2 FM_CALL LesserMask(vec2 A, vec2 B) {
	A.M = _mm_cmplt_ps(A.M, B.M);
	return A;
}
FM_SINL vec2 FM_CALL LesserOrEqualMask(vec2 A, vec2 B) {
	A.M = _mm_cmple_ps(A.M, B.M);
	return A;
}
FM_SINL bool FM_CALL operator==(vec2 A, vec2 B) {
	vec2 EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_SINL bool FM_CALL operator!=(vec2 A, vec2 B) {
	vec2 EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
}

/////////////////////
// vec2d functions //
/////////////////////
FM_INL double& vec2d::operator[](uint32_t Index) {
	FM_ASSERT(Index == 0 || Index == 1);
	return *((double*)(&M) + Index); 
}
FM_SINL vec2d FM_CALL Vec2dFromMemory(const double* V) {
	vec2d R;
	R.M = _mm_set_pd(V[1], V[0]); 
	return R;
}
FM_SINL vec2d FM_CALL Vec2d(double X, double Y) {
	vec2d R;
	R.M = _mm_set_pd(Y, X); 
	return R;
}
FM_SINL vec2d FM_CALL Vec2d(double A) {
	vec2d R;
	R.M = _mm_set1_pd(A);
	return R;
}
FM_SINL vec2d FM_CALL Vec2d(__m128d M) {
	vec2d R;
	R.M = M;
	return R;
}
FM_SINL vec2d FM_CALL Vec2d() {
	vec2d R;
	R.M = _mm_setzero_pd(); 
	return R;
}
FM_INL void FM_CALL vec2d::SetX(double X) {
	M = _mm_move_sd(M, _mm_set_sd(X)); 
}
FM_INL void FM_CALL vec2d::SetY(double Y) {
	M = _mm_unpacklo_pd(M, _mm_set_sd(Y)); 
}
FM_INL double FM_CALL vec2d::X() const {
	return _mm_cvtsd_f64(M);
}
FM_INL double FM_CALL vec2d::Y() const { 
	return _mm_cvtsd_f64(_mm_shuffle_pd(M, M, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INL void FM_CALL vec2d::AddX(double X) {
	M = _mm_add_pd(M, _mm_set_pd(0.f, X));
}
FM_INL void FM_CALL vec2d::AddY(double Y) {
	M = _mm_add_pd(M, _mm_set_pd(Y, 0.f));
}
FM_INL void FM_CALL vec2d::SubX(double X) {
	M = _mm_sub_pd(M, _mm_set_pd(0.f, X));
}
FM_INL void FM_CALL vec2d::SubY(double Y) {
	M = _mm_sub_pd(M, _mm_set_pd(Y, 0.f));
}
FM_INL void FM_CALL vec2d::MulX(double X) {
	M = _mm_mul_pd(M, _mm_set_pd(1.f, X));
}
FM_INL void FM_CALL vec2d::MulY(double Y) {
	M = _mm_mul_pd(M, _mm_set_pd(Y, 1.f));
}
FM_INL void FM_CALL vec2d::DivX(double X) {
	M = _mm_div_pd(M, _mm_set_pd(1.f, X));
}
FM_INL void FM_CALL vec2d::DivY(double Y) {
	M = _mm_div_pd(M, _mm_set_pd(Y, 1.f));
}
FM_SINL double* Ptr(const vec2d& V) { 
	return (double*)(&V); 
}
FM_SINL double* PtrY(const vec2d& V) {
	return (double*)(&V) + 1; 
}
FM_SINL void FM_CALL Store(double* Mem, vec2d V) { 
	_mm_storeu_pd(Mem, V.M); 
} 
FM_SINL void FM_CALL Store16ByteAligned(double* Mem, vec2d V) {
	FM_ASSERT(Mem % 16 == 0);
	_mm_store_pd(Mem, V.M); 
}
FM_SINL vec2d FM_CALL operator+(vec2d A, vec2d B) {
	A.M = _mm_add_pd(A.M, B.M);
	return A; 
}
FM_SINL vec2d FM_CALL operator-(vec2d A, vec2d B) {
	A.M = _mm_sub_pd(A.M, B.M);
	return A; 
}
FM_SINL vec2d& FM_CALL operator+=(vec2d& A, vec2d B) {
	A.M = _mm_add_pd(A.M, B.M);
	return A; 
}
FM_SINL vec2d& FM_CALL operator-=(vec2d& A, vec2d B) {
	A.M = _mm_sub_pd(A.M, B.M);
	return A; 
}
FM_SINL vec2d FM_CALL HadamardMul(vec2d A, vec2d B) {
	A.M = _mm_mul_pd(A.M, B.M);
	return A; 
}
FM_SINL vec2d FM_CALL HadamardDiv(vec2d A, vec2d B) {
	A.M = _mm_div_pd(A.M, B.M);
	return A; 
}
FM_SINL vec2d FM_CALL operator*(vec2d V, double Scalar) {
	V.M = _mm_mul_pd(V.M, _mm_set1_pd(Scalar));
	return V; 
}
FM_SINL vec2d FM_CALL operator*(double Scalar, vec2d V) {
	V.M = _mm_mul_pd(V.M, _mm_set1_pd(Scalar));
	return V; 
} 
FM_SINL vec2d& FM_CALL operator*=(vec2d& V, double Scalar) {
	V = V * Scalar;
	return V;
}
FM_SINL vec2d FM_CALL operator/(vec2d V, double Scalar) {
	V.M = _mm_div_pd(V.M, _mm_set1_pd(Scalar));
	return V; 
}
FM_SINL vec2d& FM_CALL operator/=(vec2d& V, double Scalar) {
	V = V / Scalar;
	return V;
}
FM_SINL vec2d FM_CALL operator-(vec2d V) {
	V.M = _mm_sub_pd(_mm_setzero_pd(), V.M);
	return V;
}
FM_SINL double FM_CALL SumOfElements(vec2d V) {
	return V.X() + V.Y();
}
FM_SINL double FM_CALL Dot(vec2d A, vec2d B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_SINL vec2d FM_CALL Min(vec2d A, vec2d B) {
	A.M = _mm_min_pd(A.M, B.M);
	return A;
}
FM_SINL vec2d FM_CALL Max(vec2d A, vec2d B) {
	A.M = _mm_max_pd(A.M, B.M);
	return A;
}
FM_SINL vec2d FM_CALL Abs(vec2d V) {
	__m128d SignBits = _mm_castsi128_pd(_mm_set1_epi32(0x80000000));
	V.M = _mm_andnot_pd(SignBits, V.M);
	return V;
}
FM_SINL double FM_CALL Length(vec2d V) {
	return sqrt(Dot(V, V));
}
FM_SINL double FM_CALL LengthSquared(vec2d V) {
	return Dot(V, V);
}
FM_SINL vec2d FM_CALL Normalize(vec2d V) {
	return V / Length(V);
}
FM_SINL void Normalize(vec2d* V) {
	*V = *V / Length(*V);
}
FM_SINL vec2d FM_CALL Clamp(vec2d V, vec2d MinV, vec2d MaxV) {
	return Min(Max(V, MinV), MaxV);
} 
FM_SINL vec2d FM_CALL Lerp(vec2d A, vec2d B, double T) {
	return A + (B-A)*T;
}
FM_SINL vec2d FM_CALL EqualsMask(vec2d A, vec2d B) {
	A.M = _mm_cmpeq_pd(A.M, B.M);
	return A;
}
FM_SINL vec2d FM_CALL GreaterMask(vec2d A, vec2d B) {
	A.M = _mm_cmpgt_pd(A.M, B.M);
	return A;
}
FM_SINL vec2d FM_CALL GreaterOrEqualMask(vec2d A, vec2d B) {
	A.M = _mm_cmpge_pd(A.M, B.M);
	return A;
}
FM_SINL vec2d FM_CALL LesserMask(vec2d A, vec2d B) {
	A.M = _mm_cmplt_pd(A.M, B.M);
	return A;
}
FM_SINL vec2d FM_CALL LesserOrEqualMask(vec2d A, vec2d B) {
	A.M = _mm_cmple_pd(A.M, B.M);
	return A;
}
FM_SINL bool FM_CALL operator==(vec2d A, vec2d B) {
	vec2d EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_SINL bool FM_CALL operator!=(vec2d A, vec2d B) {
	vec2d EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
}

/////////////////////
// vec2i functions //
/////////////////////
FM_INL int32_t& vec2i::operator[](uint32_t Index) {
	FM_ASSERT(Index == 0 || Index == 1);
	return *((int32_t*)(&M) + Index); 
}
FM_SINL vec2i FM_CALL Vec2iFromMemory(const int32_t* V) {
	vec2i R;
	R.M = _mm_set_epi32(0, 0, V[1], V[0]); 
	return R;
}
FM_SINL vec2i FM_CALL Vec2i(int32_t X, int32_t Y) {
	vec2i R;
	R.M = _mm_set_epi32(0, 0, Y, X); 
	return R;
}
FM_SINL vec2i FM_CALL Vec2i(int32_t A) { 
	vec2i R;
	R.M = _mm_set1_epi32(A); 
	return R;
}
FM_SINL vec2i FM_CALL Vec2i(__m128i M) {
	vec2i R;
	R.M = M;
	return R;
}
FM_SINL vec2i FM_CALL Vec2i() {
	vec2i R;
	R.M = _mm_setzero_si128();
	return R;
}
FM_INL int32_t FM_CALL vec2i::X() const { 
	return _mm_cvtsi128_si32(M); 
} 
FM_INL int32_t FM_CALL vec2i::Y() const {
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(M, _MM_SHUFFLE(1, 1, 1, 1))); 
} 
FM_INL void FM_CALL vec2i::AddX(int32_t X) {
	M = _mm_add_epi32(M, _mm_set_epi32(0, 0, 0, X));
}
FM_INL void FM_CALL vec2i::AddY(int32_t Y) {
	M = _mm_add_epi32(M, _mm_set_epi32(0, 0, Y, 0));
}
FM_INL void FM_CALL vec2i::SubX(int32_t X) {
	M = _mm_sub_epi32(M, _mm_set_epi32(0, 0, 0, X));
}
FM_INL void FM_CALL vec2i::SubY(int32_t Y) {
	M = _mm_sub_epi32(M, _mm_set_epi32(0, 0, Y, 0));
}
FM_INL void FM_CALL vec2i::DivX(int32_t XDivider) {
	SetX(X() / XDivider);
}
FM_INL void FM_CALL vec2i::DivY(int32_t YDivider) {
	SetY(Y() / YDivider);
}
FM_SINL int32_t* Ptr(const vec2i& V) { 
	return (int32_t*)(&V); 
}
FM_SINL int32_t* PtrY(const vec2i& V) { 
	return (int32_t*)(&V) + 1; 
}
FM_SINL void FM_CALL Store(int32_t* Mem, vec2i V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
} 
FM_SINL vec2i FM_CALL operator+(vec2i A, vec2i B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_SINL vec2i FM_CALL operator-(vec2i A, vec2i B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_SINL vec2i& FM_CALL operator+=(vec2i& A, vec2i B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_SINL vec2i& FM_CALL operator-=(vec2i& A, vec2i B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_SINL vec2i FM_CALL operator-(vec2i V) {
	V.M = _mm_sub_epi32(_mm_setzero_si128(), V.M);
	return V;
}
FM_SINL int32_t FM_CALL SumOfElements(vec2i V) {
	return V.X() + V.Y();
}
FM_SINL int32_t FM_CALL Length(vec2i V) {
	int32_t X = V.X();
	int32_t Y = V.Y();
	return (int32_t)sqrt(X*X + Y*Y);
}
FM_SINL int32_t FM_CALL LengthSquared(vec2i V) {
	int32_t X = V.X();
	int32_t Y = V.Y();
	return X*X + Y*Y;
}
FM_SINL vec2i FM_CALL EqualsMask(vec2i A, vec2i B) {
	A.M = _mm_cmpeq_epi32(A.M, B.M);
	return A;
}
FM_SINL vec2i FM_CALL GreaterMask(vec2i A, vec2i B) {
	A.M = _mm_cmpgt_epi32(A.M, B.M);
	return A;
}
FM_SINL vec2i FM_CALL GreaterOrEqualMask(vec2i A, vec2i B) {
	__m128i GT = _mm_cmpgt_epi32(A.M, B.M);
	__m128i EQ = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(GT, EQ);
	return A;
}
FM_SINL vec2i FM_CALL LesserMask(vec2i A, vec2i B) {
	A.M = _mm_cmplt_epi32(A.M, B.M);
	return A;
}
FM_SINL vec2i FM_CALL LesserOrEqualMask(vec2i A, vec2i B) {
	__m128i LT = _mm_cmplt_epi32(A.M, B.M);
	__m128i EQ = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(LT, EQ);
	return A;
}
FM_SINL bool FM_CALL operator==(vec2i A, vec2i B) {
	vec2i EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_SINL bool FM_CALL operator!=(vec2i A, vec2i B) {
	vec2i EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
} 
#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INL void FM_CALL vec2i::SetX(int32_t X) {
	M = _mm_insert_epi32(M, X, 0);
}
FM_INL void FM_CALL vec2i::SetY(int32_t Y) {
	M = _mm_insert_epi32(M, Y, 1);
}
FM_SINL vec2i FM_CALL operator*(vec2i V, int32_t Scalar) {
	V.M = _mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar));
	return V; 
}
FM_SINL vec2i FM_CALL operator*(int32_t Scalar, vec2i V) {
	V.M =_mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar)); 
	return V; 
}
FM_INL void FM_CALL vec2i::MulX(int32_t X) {
	M = _mm_mullo_epi32(M, _mm_set_epi32(1, 1, 1, X));
}
FM_INL void FM_CALL vec2i::MulY(int32_t Y) {
	M = _mm_mullo_epi32(M, _mm_set_epi32(1, 1, Y, 1));
}
FM_INL vec2i FM_CALL HadamardMul(vec2i A, vec2i B) {
	A.M = _mm_mullo_epi32(A.M, B.M); 
	return A; 
}
FM_SINL vec2i FM_CALL Min(vec2i A, vec2i B) {
	A.M = _mm_min_epi32(A.M, B.M);
	return A;
}
FM_SINL vec2i FM_CALL Max(vec2i A, vec2i B) {
	A.M = _mm_max_epi32(A.M, B.M);
	return A;
}
FM_SINL vec2i FM_CALL Abs(vec2i V) {
	V.M = _mm_abs_epi32(V.M);
	return V;
}
FM_SINL vec2i FM_CALL Clamp(vec2i V, vec2i MinV, vec2i MaxV) {
	return Min(Max(V, MinV), MaxV);
} 
#else // SSE 2 implementations 
FM_SINL void FM_CALL vec2i::SetX(int32_t X) {
	int32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, M);
	Arr[0] = X;
	M = _mm_load_si128((__m128i*)Arr);
}
FM_SINL void FM_CALL vec2i::SetY(int32_t Y) {
	int32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, M);
	Arr[1] = Y;
	M = _mm_load_si128((__m128i*)Arr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_SINL vec2i FM_CALL HadamardMul(vec2i A, vec2i B) {
	int32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = AArr[0] * BArr[0]; 
	AArr[1] = AArr[1] * BArr[1]; 
	return Vec2i(AArr);
}
FM_SINL vec2i FM_CALL operator*(vec2i V, int32_t Scalar) {
	int32_t VArr[4];
	_mm_store_si128((__m128i*)VArr, V.M);
	VArr[0] *= Scalar;
	VArr[1] *= Scalar;
	return Vec2i(VArr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_SINL vec2i FM_CALL operator*(int32_t Scalar, vec2i v) {
	return V * Scalar; 
}
FM_SINL vec2i FM_CALL Min(vec2i A, vec2i B) {
	int32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Min(AArr[0], BArr[0]);
	AArr[1] = Min(AArr[1], BArr[1]);
	return Vec2i(AArr);
}
FM_SINL vec2i FM_CALL Max(vec2i A, vec2i B) {
	int32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Max(AArr[0], BArr[0]);
	AArr[1] = Max(AArr[1], BArr[1]);
	return Vec2i(AArr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_SINL vec2i FM_CALL abs(vec2i v) {
	int32_t VArr[4];
	_mm_store_si128((__m128i*)VArr, V.M);
	VArr[0] = abs(VArr[0]);
	VArr[1] = abs(VArr[1]);
	return Vec2i(VArr);
}
FM_SINL void FM_CALL vec2i::MulX(int32_t XMultiplier) {
	SetX(X() * XMultiplier);
}
FM_SINL void FM_CALL vec2i::MulY(int32_t YMultiplier) {
	SetY(Y() * YMultiplier);
}
#endif
FM_SINL vec2i& FM_CALL operator*=(vec2i& V, int32_t Scalar) {
	V = V * Scalar;
	return V;
} 

/////////////////////
// vec2u functions //
/////////////////////
FM_INL uint32_t& vec2u::operator[](uint32_t Index) {
	FM_ASSERT(Index == 0 || Index == 1);
	return *((uint32_t*)(&M) + Index);
}
FM_SINL vec2u FM_CALL Vec2uFromMemory(const uint32_t* V) {
	vec2u R;
	R.M = _mm_set_epi32(0, 0, V[1], V[0]); 
	return R;
}
FM_SINL vec2u FM_CALL Vec2u(uint32_t x, uint32_t y) {
	vec2u R;
	R.M = _mm_set_epi32(0, 0, y, x); 
	return R;
}
FM_SINL vec2u FM_CALL Vec2u(uint32_t a) {
	vec2u R;
	R.M = _mm_set1_epi32(a); 
	return R;
} 
FM_SINL vec2u FM_CALL Vec2u(__m128i m) {
	vec2u R;
	R.M = m;
	return R;
} 
FM_SINL vec2u FM_CALL Vec2u() {
	vec2u R;
	R.M = _mm_setzero_si128(); 
	return R;
}
FM_INL uint32_t FM_CALL vec2u::X() const {
	return (uint32_t)_mm_cvtsi128_si32(M); 
} 
FM_INL uint32_t FM_CALL vec2u::Y() const { 
	return (uint32_t)_mm_cvtsi128_si32(_mm_shuffle_epi32(M, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INL void FM_CALL vec2u::AddX(uint32_t X) {
	M = _mm_add_epi32(M, _mm_set_epi32(0, 0, 0, X));
}
FM_INL void FM_CALL vec2u::AddY(uint32_t Y) {
	M = _mm_add_epi32(M, _mm_set_epi32(0, 0, Y, 0));
}
FM_INL void FM_CALL vec2u::SubX(uint32_t X) {
	M = _mm_sub_epi32(M, _mm_set_epi32(0, 0, 0, X));
}
FM_INL void FM_CALL vec2u::SubY(uint32_t Y) {
	M = _mm_sub_epi32(M, _mm_set_epi32(0, 0, Y, 0));
}
FM_INL void FM_CALL vec2u::DivX(uint32_t XDivider) {
	SetX(X() / XDivider);
}
FM_INL void FM_CALL vec2u::DivY(uint32_t YDivider) {
	SetY(Y() / YDivider);
}
FM_SINL uint32_t* Ptr(const vec2u& V) {
	return (uint32_t*)(&V); 
}
FM_SINL uint32_t* PtrY(const vec2u& V) {
	return (uint32_t*)(&V) + 1; 
}
FM_SINL void FM_CALL Store(uint32_t* Mem, vec2u V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
} 
FM_SINL vec2u FM_CALL operator+(vec2u A, vec2u B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_SINL vec2u FM_CALL operator-(vec2u A, vec2u B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_SINL vec2u& FM_CALL operator+=(vec2u& A, vec2u B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_SINL vec2u& FM_CALL operator-=(vec2u& A, vec2u B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_SINL uint32_t FM_CALL SumOfElements(vec2u V) {
	return V.X() + V.Y();
}
FM_SINL uint32_t FM_CALL Length(vec2u V) {
	uint32_t X = V.X();
	uint32_t Y = V.Y();
	return (uint32_t)sqrt(X*X + Y*Y);
}
FM_SINL uint32_t FM_CALL LengthSquared(vec2u V) {
	uint32_t X = V.X();
	uint32_t Y = V.Y();
	return X*X + Y*Y;	
}
FM_SINL vec2u FM_CALL EqualsMask(vec2u A, vec2u B) {
	A.M = _mm_cmpeq_epi32(A.M, B.M);
	return A;
}
FM_SINL vec2u FM_CALL GreaterMask(vec2u A, vec2u B) {
	A.M = _mm_cmpgt_epi32(A.M, B.M);
	return A;
}
FM_SINL vec2u FM_CALL GreaterOrEqualMask(vec2u A, vec2u B) {
	__m128i gt = _mm_cmpgt_epi32(A.M, B.M);
	__m128i eq = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(gt, eq);
	return A;
}
FM_SINL vec2u FM_CALL LesserMask(vec2u A, vec2u B) {
	A.M = _mm_cmplt_epi32(A.M, B.M);
	return A;
}
FM_SINL vec2u FM_CALL LesserOrEqualMask(vec2u A, vec2u B) {
	__m128i lt = _mm_cmplt_epi32(A.M, B.M);
	__m128i eq = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(lt, eq);
	return A;
}
FM_SINL bool FM_CALL operator==(vec2u A, vec2u B) {
	vec2u EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_SINL bool FM_CALL operator!=(vec2u A, vec2u B) {
	vec2u EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
} 
FM_INL void FM_CALL vec2u::MulX(uint32_t XMultiplier) {
	SetX(X() * XMultiplier);
}
FM_INL void FM_CALL vec2u::MulY(uint32_t YMultiplier) {
	SetY(Y() * YMultiplier);
}
#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INL void FM_CALL vec2u::SetX(uint32_t X) {
	M = _mm_insert_epi32(M, (int32_t)X, 0);
}
FM_INL void FM_CALL vec2u::SetY(uint32_t Y) {
	M = _mm_insert_epi32(M, (int32_t)Y, 1);
}
FM_SINL vec2u FM_CALL operator*(vec2u V, uint32_t Scalar) {
	V.M = _mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar)); 
	return V; 
}
FM_SINL vec2u FM_CALL operator*(uint32_t Scalar, vec2u V) {
	V.M =_mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar));
	return V; 
}
FM_SINL vec2u FM_CALL HadamardMul(vec2u A, vec2u B) {
	A.M = _mm_mullo_epi32(A.M, B.M);
	return A; 
}
FM_SINL vec2u FM_CALL Min(vec2u A, vec2u B) {
	A.M = _mm_min_epu32(A.M, B.M);
	return A;
}
FM_SINL vec2u FM_CALL Max(vec2u A, vec2u B) {
	A.M = _mm_max_epu32(A.M, B.M);
	return A;
}
#else // SSE 2 implementations
FM_INL void FM_CALL vec2u::SetX(uint32_t x) {
	uint32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, m);
	Arr[0] = x;
	m = _mm_load_si128((__m128i*)Arr);
}
FM_INL void FM_CALL vec2u::SetY(uint32_t y) {
	uint32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, m);
	Arr[1] = y;
	M = _mm_load_si128((__m128i*)Arr);
	// TODO: This code is repeated. Make utility function!
}
FM_SINL vec2u FM_CALL HadamardMul(vec2u A, vec2u B) {
	uint32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = AArr[0] * BArr[0]; 
	AArr[1] = AArr[1] * BArr[1]; 
	return Vec2u(AArr);
}
FM_SINL vec2u FM_CALL operator*(vec2u V, uint32_t Scalar) {
	uint32_t VArr[4];
	_mm_store_si128((__m128i*)VArr, V.M);
	VArr[0] *= Scalar;
	VArr[1] *= Scalar;
	return Vec2u(VArr);
}
FM_SINL vec2u FM_CALL operator*(uint32_t Scalar, vec2u V) {
	return V * Scalar;
}
FM_SINL vec2u FM_CALL Min(vec2u A, vec2u B) {
	uint32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Min(AArr[0], BArr[0]);
	AArr[1] = Min(AArr[1], BArr[1]);
	return Vec2u(AArr);
}
FM_SINL vec2u FM_CALL Max(vec2u A, vec2u B) {
	uint32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Max(AArr[0], BArr[0]);
	AArr[1] = Max(AArr[1], BArr[1]);
	return Vec2u(AArr);
}
#endif
FM_SINL vec2u& FM_CALL operator*=(vec2u& V, uint32_t Scalar) {
	V = V * Scalar;
	return V;
} 
FM_SINL vec2u FM_CALL Clamp(vec2u V, vec2u MinV, vec2u MaxV) {
	return Min(Max(V, MinV), MaxV);
} 

////////////////////
// vec3 functions //
////////////////////
FM_SINL vec3 FM_CALL Vec3FromMemory(float* V) {
	vec3 R;
	R.M = _mm_set_ps(0, V[2], V[1], V[0]);
	return R;
}
FM_SINL vec3 FM_CALL Vec3(float X, float Y, float Z) {
	vec3 R;
	R.M = _mm_set_ps(0, Z, Y, X); 
	return R;
}
FM_SINL vec3 FM_CALL Vec3(float A) {
	vec3 R;
	R.M = _mm_set1_ps(A);
	return R;
}
FM_SINL vec3 FM_CALL Vec3(__m128 M) {
	vec3 R;
	R.M = M;
	return R;
}
FM_SINL vec3 FM_CALL Vec3() {
	vec3 R;
	R.M = _mm_setzero_ps();
	return R;
}
FM_INL float& vec3::operator[](uint32_t Index) {
	FM_ASSERT(Index >= 0 && Index <= 2);
	return *((float*)(&M) + Index);
}
FM_INL void FM_CALL vec3::SetX(float X) {
	M = priv::SetX(M, X); 
}
FM_INL void FM_CALL vec3::SetY(float Y) {
	M = priv::SetY(M, Y);
}
FM_INL void FM_CALL vec3::SetZ(float Z) {
	M = priv::SetZ(M, Z);
}
FM_INL void FM_CALL vec3::AddX(float X) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INL void FM_CALL vec3::AddY(float Y) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INL void FM_CALL vec3::AddZ(float Z) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, Z, 0.f, 0.f));
}
FM_INL void FM_CALL vec3::SubX(float X) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INL void FM_CALL vec3::SubY(float Y) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INL void FM_CALL vec3::SubZ(float Z) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, Z, 0.f, 0.f));
}
FM_INL void FM_CALL vec3::MulX(float X) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INL void FM_CALL vec3::MulY(float Y) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INL void FM_CALL vec3::MulZ(float Z) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, Z, 1.f, 1.f));
}
FM_INL void FM_CALL vec3::DivX(float X) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INL void FM_CALL vec3::DivY(float Y) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INL void FM_CALL vec3::DivZ(float Z) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, Z, 1.f, 1.f));
}
FM_SINL float* Ptr(vec3& V) {
	return (float*)(&V); 
}
FM_SINL float* PtrY(vec3& V) {
	return (float*)(&V) + 1; 
}
FM_SINL float* PtrZ(vec3& V) {
	return (float*)(&V) + 2; 
}
FM_SINL void FM_CALL Store(float* Mem, vec3 V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
	Mem[2] = V.Z();
}
FM_INL vec3 FM_CALL vec3::ZXY() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 0, 2)));
}
FM_INL float FM_CALL vec3::X() const {
	return priv::GetX(M); 
}
FM_INL float FM_CALL vec3::Y() const {
	return priv::GetY(M); 
}
FM_INL float FM_CALL vec3::Z() const {
	return priv::GetZ(M); 
}
FM_SINL vec3 FM_CALL operator+(vec3 A, vec3 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_SINL vec3 FM_CALL operator-(vec3 A, vec3 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_SINL vec3& FM_CALL operator+=(vec3& A, vec3 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_SINL vec3& FM_CALL operator-=(vec3& A, vec3 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_SINL vec3 FM_CALL HadamardMul(vec3 A, vec3 B) {
	A.M = _mm_mul_ps(A.M, B.M);
	return A;
}
FM_SINL vec3 FM_CALL HadamardDiv(vec3 A, vec3 B) {
	A.M = _mm_div_ps(A.M, B.M);
	return A;
}
FM_SINL vec3 FM_CALL operator*(vec3 V, float Scalar) {
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_SINL vec3 FM_CALL operator*(float Scalar, vec3 V) {
	return V * Scalar;
}
FM_SINL vec3& FM_CALL operator*=(vec3& V, float Scalar) {
	V = V * Scalar;
	return V;
}
FM_SINL vec3 FM_CALL operator/(vec3 V, float Scalar) {
	V.M = _mm_div_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_SINL vec3& FM_CALL operator/=(vec3& V, float Scalar) {
	V = V / Scalar;
	return V;
}
FM_SINL vec3 FM_CALL operator-(vec3 V) {
	V.M = _mm_sub_ps(_mm_setzero_ps(), V.M);
	return V;
}
FM_SINL float FM_CALL SumOfElements(vec3 V) {
	return V.X() + V.Y() + V.Z();
}
FM_SINL float FM_CALL Dot(vec3 A, vec3 B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_SINL vec3 FM_CALL Cross(vec3 A, vec3 B) {
	return vec3(HadamardMul(A.ZXY(), B) - HadamardMul(A, B.ZXY())).ZXY(); 
}
FM_SINL vec3 FM_CALL Min(vec3 A, vec3 B) {
	A.M = _mm_min_ps(A.M, B.M);
	return A;
}
FM_SINL vec3 FM_CALL Max(vec3 A, vec3 B) {
	A.M = _mm_max_ps(A.M, B.M);
	return A;
}
FM_SINL vec3 FM_CALL Abs(vec3 V) {
	__m128 SignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	V.M = _mm_andnot_ps(SignMask, V.M);
	return V;
}
FM_SINL float FM_CALL Length(vec3 V) {
	return sqrtf(Dot(V, V));
}
FM_SINL float FM_CALL LengthSquared(vec3 V) {
	return Dot(V, V);
}
FM_SINL vec3 FM_CALL Normalize(vec3 V) {
	return V / Length(V);
}
FM_SINL void Normalize(vec3* V) {
	*V = *V / Length(*V);
}
FM_SINL vec3 FM_CALL Clamp(vec3 V, vec3 MinV, vec3 MaxV) {
	return Min(Max(V, MinV), MaxV);
}
FM_SINL vec3 FM_CALL Lerp(vec3 A, vec3 B, float T) {
	return A + (B-A)*T;
} 
FM_SINL vec3 FM_CALL EqualsMask(vec3 A, vec3 B) {
	A.M = _mm_cmpeq_ps(A.M, B.M);
	return A;
}
FM_SINL vec3 FM_CALL GreaterMask(vec3 A, vec3 B) {
	A.M = _mm_cmpgt_ps(A.M, B.M);
	return A;
}
FM_SINL vec3 FM_CALL GreaterOrEqualMask(vec3 A, vec3 B) {
	A.M = _mm_cmpge_ps(A.M, B.M);
	return A;
}
FM_SINL vec3 FM_CALL LesserMask(vec3 A, vec3 B) {
	A.M = _mm_cmplt_ps(A.M, B.M);
	return A;
}
FM_SINL vec3 FM_CALL LesserOrEqualMask(vec3 A, vec3 B) {
	A.M = _mm_cmple_ps(A.M, B.M);
	return A;
}
FM_SINL bool FM_CALL operator==(vec3 A, vec3 B) {
	vec3 EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y() && EqMask.Z();
} 
FM_SINL bool FM_CALL operator!=(vec3 A, vec3 B) {
	vec3 EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y() && EqMask.Z());
}

////////////////////
// vec4 functions //
////////////////////
FM_SINL vec4 FM_CALL Vec4FromMemory(const float* V) {
	vec4 R;
	R.M = _mm_set_ps(V[3], V[2], V[1], V[0]);	
	return R;
} 
FM_SINL vec4 FM_CALL Vec4(vec3 V, float W) {
	vec4 R;
	V.M = _mm_shuffle_ps(V.M, V.M, _MM_SHUFFLE(2, 1, 0, 0));
	R.M = _mm_move_ss(V.M, _mm_set_ss(W));
	R.M = _mm_shuffle_ps(R.M, R.M, _MM_SHUFFLE(0, 3, 2, 1));
	return R;
}
FM_SINL vec4 FM_CALL Vec4(float X, float Y, float Z, float W) {
	vec4 R;
	R.M = _mm_set_ps(W, Z, Y, X);
	return R;
}
FM_SINL vec4 FM_CALL Vec4(float A) {
	vec4 R;
	R.M = _mm_set1_ps(A);
	return R;
}
FM_SINL vec4 FM_CALL Vec4(__m128 M) {
	vec4 R;
	R.M = M;
	return R;
} 
FM_SINL vec4 FM_CALL Vec4() {
	vec4 R;
	R.M = _mm_setzero_ps();
	return R;
}
FM_INL float& vec4::operator[](uint32_t Index) {
	FM_ASSERT(Index >= 0 && Index <= 3);
	return *((float*)(&M) + Index);
}
FM_INL void FM_CALL vec4::SetX(float X) {
	M = priv::SetX(M, X); 
}
FM_INL void FM_CALL vec4::SetY(float Y) {
	M = priv::SetY(M, Y);
} 
FM_INL void FM_CALL vec4::SetZ(float Z) {
	M = priv::SetZ(M, Z);
} 
FM_INL void FM_CALL vec4::SetW(float W) {
	M = priv::SetW(M, W);
} 
FM_INL void FM_CALL vec4::AddX(float X) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INL void FM_CALL vec4::AddY(float Y) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INL void FM_CALL vec4::AddZ(float Z) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, Z, 0.f, 0.f));
}
FM_INL void FM_CALL vec4::AddW(float W) {
	M = _mm_add_ps(M, _mm_set_ps(W, 0.f, 0.f, 0.f));
}
FM_INL void FM_CALL vec4::SubX(float X) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INL void FM_CALL vec4::SubY(float Y) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INL void FM_CALL vec4::SubZ(float Z) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, Z, 0.f, 0.f));
}
FM_INL void FM_CALL vec4::SubW(float W) {
	M = _mm_sub_ps(M, _mm_set_ps(W, 0.f, 0.f, 0.f));
}
FM_INL void FM_CALL vec4::MulX(float X) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INL void FM_CALL vec4::MulY(float Y) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INL void FM_CALL vec4::MulZ(float Z) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, Z, 1.f, 1.f));
}
FM_INL void FM_CALL vec4::MulW(float W) {
	M = _mm_mul_ps(M, _mm_set_ps(W, 1.f, 1.f, 1.f));
}
FM_INL void FM_CALL vec4::DivX(float X) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INL void FM_CALL vec4::DivY(float Y) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INL void FM_CALL vec4::DivZ(float Z) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, Z, 1.f, 1.f));
}
FM_INL void FM_CALL vec4::DivW(float W) {
	M = _mm_div_ps(M, _mm_set_ps(W, 1.f, 1.f, 1.f));
}
FM_INL float FM_CALL vec4::X() const {
	return _mm_cvtss_f32(M);
}
FM_INL float FM_CALL vec4::Y() const {
	return priv::GetY(M); 
}
FM_INL float FM_CALL vec4::Z() const {
	return priv::GetZ(M); 
}
FM_INL float FM_CALL vec4::W() const {
	return priv::GetW(M); 
}
FM_SINL float* Ptr(const vec4& V) {
	return (float*)(&V);
}
FM_SINL float* PtrY(const vec4& V) {
	return (float*)(&V) + 1; 
}
FM_SINL float* PtrZ(const vec4& V) {
	return (float*)(&V) + 2;
}
FM_SINL float* PtrW(const vec4& V) {
	return (float*)(&V) + 3; 
}
FM_SINL void FM_CALL Store(float* Mem, vec4 V) {
	_mm_storeu_ps(Mem, V.M);
}
FM_SINL void FM_CALL Store16ByteAligned(float* Mem, vec4 V) {
	FM_ASSERT(Mem % 16 == 0);
	_mm_store_ps(Mem, V.M);
}
FM_SINL vec4 FM_CALL operator+(vec4 A, vec4 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_SINL vec4 FM_CALL operator-(vec4 A, vec4 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_SINL vec4& FM_CALL operator+=(vec4& A, vec4 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_SINL vec4& FM_CALL operator-=(vec4& A, vec4 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_SINL vec4 FM_CALL HadamardMul(vec4 A, vec4 B) {
	A.M = _mm_mul_ps(A.M, B.M);
	return A;
}
FM_SINL vec4 FM_CALL HadamardDiv(vec4 A, vec4 B) {
	A.M = _mm_div_ps(A.M, B.M);
	return A;
}
FM_SINL vec4 FM_CALL operator*(vec4 V, float Scalar) {
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_SINL vec4 FM_CALL operator*(float Scalar, vec4 V) {
	return V * Scalar;
}
FM_SINL vec4& FM_CALL operator*=(vec4& V, float Scalar) {
	V = V * Scalar;
	return V;
}
FM_SINL vec4 FM_CALL operator/(vec4 V, float Scalar) {
	V.M = _mm_div_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_SINL vec4& FM_CALL operator/=(vec4& V, float Scalar) {
	V = V / Scalar;
	return V;
}
FM_SINL vec4 FM_CALL operator-(vec4 V) {
	V.M = _mm_sub_ps(_mm_setzero_ps(), V.M);
	return V;
}
FM_SINL float FM_CALL SumOfElements(vec4 V) {
	return V.X() + V.Y() + V.Z() + V.W();
}
FM_SINL float FM_CALL Dot(vec4 A, vec4 B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_SINL vec4 FM_CALL Min(vec4 A, vec4 B) {
	A.M = _mm_min_ps(A.M, B.M);
	return A;
}
FM_SINL vec4 FM_CALL Max(vec4 A, vec4 B) {
	A.M = _mm_max_ps(A.M, B.M);
	return A;
}
FM_SINL vec4 FM_CALL Abs(vec4 V) {
	__m128 SignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	V.M = _mm_andnot_ps(SignMask, V.M);
	return V;
}
FM_SINL float FM_CALL Length(vec4 V) {
	return sqrtf(Dot(V, V));
}
FM_SINL float FM_CALL LengthSquared(vec4 V) {
	return Dot(V, V);
}
FM_SINL vec4 FM_CALL Normalize(vec4 V) {
	return V / Length(V);
}
FM_SINL void Normalize(vec4* V) {
	*V = *V / Length(*V);
}
FM_SINL vec4 FM_CALL Clamp(vec4 V, vec4 MinV, vec4 MaxV) {
	return Min(Max(V, MinV), MaxV);
}
FM_SINL vec4 FM_CALL Lerp(vec4 A, vec4 B, float T) {
	return A + (B-A)*T;
} 
FM_SINL vec4 FM_CALL EqualsMask(vec4 A, vec4 B) {
	A.M = _mm_cmpeq_ps(A.M, B.M);
	return A;
}
FM_SINL vec4 FM_CALL GreaterMask(vec4 A, vec4 B) {
	A.M = _mm_cmpgt_ps(A.M, B.M);
	return A;
}
FM_SINL vec4 FM_CALL GreaterOrEqualMask(vec4 A, vec4 B) {
	A.M = _mm_cmpge_ps(A.M, B.M);
	return A;
}
FM_SINL vec4 FM_CALL LesserMask(vec4 A, vec4 B) {
	A.M = _mm_cmplt_ps(A.M, B.M);
	return A;
}
FM_SINL vec4 FM_CALL LesserOrEqualMask(vec4 A, vec4 B) {
	A.M = _mm_cmple_ps(A.M, B.M);
	return A;
}
FM_SINL bool FM_CALL operator==(vec4 A, vec4 B) {
	vec4 EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y() && EqMask.Z() && EqMask.W();
} 
FM_SINL bool FM_CALL operator!=(vec4 A, vec4 B) {
	return !(A == B);
}

//////////////////////////
// vector types casting //
//////////////////////////
FM_FUN_SIC CastToV2(vec2 V) -> v2 {
	return v2(V.X(), V.Y());
}
FM_FUN_SIC CastToV3(vec3 V) -> v3 {
	return v3(V.X(), V.Y(), V.Z());
}
FM_FUN_SIC CastToV4(vec4 V) -> v4 {
	v4 R;
	Store(R.Elements, V);
	return R;
}
FM_FUN_SIC CastToVec2(v2 V) -> vec2 {
	return Vec2FromMemory(V.Elements);
}
FM_FUN_SIC CastToVec3(v3 V) -> vec3 {
	return Vec3FromMemory(V.Elements);
}
FM_FUN_SIC CastToVec4(v4 V) -> vec4 {
	return Vec4FromMemory(V.Elements);
}

/////////////////////
// rect2 functions //
/////////////////////
template<class t> template<class u> rect2_base<t>::rect2_base(rect2_base<u> A) {
	Min = static_cast<v2_base<t>>(A.Min);
	Max = static_cast<v2_base<t>>(A.Max);
}
FM_FUN_TSI GetWidth(rect2_base<t> A) -> t {
	return A.Max.X - A.Min.X;
}
FM_FUN_TSI GetHeight(rect2_base<t> A) -> t {
	return A.Max.Y - A.Min.Y;
}
FM_FUN_TSI GetW(rect2_base<t> A) -> t {
	return GetWidth(A);
}
FM_FUN_TSI GetH(rect2_base<t> A) -> t {
	return GetHeight(A);
}
FM_FUN_TSI GetDim(rect2_base<t> A) -> v2_base<t> {
	return A.Max - A.Min;
}
FM_FUN_TSI GetRadius(rect2_base<t> A) -> v2_base<t> {
	return GetDim(A) / (t)2;
}
FM_FUN_TSI GetArea(rect2_base<t> A) -> t {
	auto Dim = GetDim(A);
	return Dim.W * Dim.H;
}
FM_FUN_TSI GetCenter(rect2_base<t> A) -> v2_base<t> {
	return v2_base<t>((A.Min + A.Max) / (t)2);
}
FM_FUN_TSI GetMaxXMinY(rect2_base<t> A) -> v2_base<t> {
	return v2_base<t>(A.Max.X, A.Min.Y);
}
FM_FUN_TSI GetMinXMaxY(rect2_base<t> A) -> v2_base<t> {
	return v2_base<t>(A.Min.X, A.Max.Y);
}
FM_FUN_TSI GetMinYCenter(rect2_base<t> A) -> v2_base<t> {
	return v2_base<t>(A.Min.X + GetWidth(A)/(t)2, A.Min.Y);
}
FM_FUN_TSI GetMaxYCenter(rect2_base<t> A) -> v2_base<t> {
	return v2_base<t>(A.Min.X + GetWidth(A)/(t)2, A.Max.Y);
}
FM_FUN_TSI GetMinXCenter(rect2_base<t> A) -> v2_base<t> {
	return v2_base<t>(A.Min.X, A.Min.Y + GetHeight(A)/(t)2);
}
FM_FUN_TSI GetMaxXCenter(rect2_base<t> A) -> v2_base<t> {
	return v2_base<t>(A.Max.X, A.Min.Y + GetHeight(A)/(t)2);
}
FM_FUN_TSI SetCenter(rect2_base<t> A, v2_base<t> Center) -> rect2_base<t> {
	auto Radius = GetRadius(A);
	A.Min = Center - Radius;
	A.Max = Center + Radius;
	return A;
}
FM_FUN_TSI SetCenter(rect2_base<t> A, t X, t Y) -> rect2_base<t> {
	return SetCenter(A, v2_base<t>(X, Y));
}
FM_FUN_TSI SetCenter(rect2_base<t>* A, v2_base<t> Center) -> void {
	*A = SetCenter(*A, Center);
}
FM_FUN_TSI SetCenter(rect2_base<t>* A, t X, t Y) -> void {
	*A = SetCenter(*A, X, Y);
}
FM_FUN_TSI SetDimWithFixedCenter(rect2_base<t> A, v2_base<t> Dim) -> rect2_base<t> {
	auto NewRadius = Dim / (t)2;
	auto Center = GetCenter(A);
	A.Min = Center - NewRadius;
	A.Max = Center + NewRadius;
	return A;
}
FM_FUN_TSI SetDimWithFixedCenter(rect2_base<t> A, t Width, t Height) -> rect2_base<t> {
	return SetDimWithFixedCenter(A, v2_base<t>(Width, Height));
}
FM_FUN_TSI SetDimWithFixedCenter(rect2_base<t>* A, t Width, t Height) -> void {
	*A = SetDimWithFixedCenter(*A, Width, Height);
}
FM_FUN_TSI SetDimWithFixedCenter(rect2_base<t>* A, v2_base<t> Dim) -> void {
	*A = SetDimWithFixedCenter(*A, Dim);
}
FM_FUN_TSI SetDimWithFixedMin(rect2_base<t> A, v2_base<t> Dim) -> rect2_base<t> {
	A.Max = A.Min + Dim;
	return A;
}
FM_FUN_TSI SetDimWithFixedMin(rect2_base<t> A, t Width, t Height) -> rect2_base<t> {
	return SetDimWithFixedMin(A, v2_base<t>(Width, Height));
}
FM_FUN_TSI SetDimWithFixedMin(rect2_base<t>* A, v2_base<t> Dim) -> void {
	*A = SetDimWithFixedMin(*A, Dim);
}
FM_FUN_TSI SetDimWithFixedMin(rect2_base<t>* A, t Width, t Height) -> void {
	*A = SetDimWithFixedMin(*A, v2_base<t>(Width, Height));
}
FM_FUN_TSI SetDimWithFixedMax(rect2_base<t> A, v2_base<t> Dim) -> rect2_base<t> {
	A.Min = A.Max - Dim;
	return A;
}
FM_FUN_TSI SetDimWithFixedMax(rect2_base<t> A, t Width, t Height) -> rect2_base<t> {
	return SetDimWithFixedMax(A, v2_base<t>(Width, Height));
}
FM_FUN_TSI SetDimWithFixedMax(rect2_base<t>* A, v2_base<t> Dim) -> void {
	*A = SetDimWithFixedMax(*A, Dim);
}
FM_FUN_TSI SetDimWithFixedMax(rect2_base<t>* A, t Width, t Height) -> void {
	*A = SetDimWithFixedMax(*A, v2_base<t>(Width, Height));
}
FM_FUN_TSI HasArea(rect2_base<t> A) -> bool {
	return A.Min.X < A.Max.X && A.Min.Y < A.Max.Y;
}
FM_FUN_TSI HasAreaFlipAllowed(rect2_base<t> A) -> bool {
	return A.Min.X != A.Max.X && A.Min.Y != A.Max.Y;
}
FM_FUN_TSI Rect2BaseMinMax(t MinX, t MinY, t MaxX, t MaxY) -> rect2_base<t> {
	rect2_base<t> R;
	R.Min.X = MinX;
	R.Min.Y = MinY;
	R.Max.X = MaxX;
	R.Max.Y = MaxY;
	return R;
}
FM_FUN_TSI Rect2BaseMinMax(v2_base<t> Min, v2_base<t> Max) -> rect2_base<t> {
	rect2_base<t> R;
	R.Min = Min;
	R.Max = Max;
	return R;
}
FM_FUN_TSI Rect2BaseMinDim(t MinX, t MinY, t Width, t Height) -> rect2_base<t> {
	rect2_base<t> R;
	R.Min.X = MinX;
	R.Min.Y = MinY;
	R.Max.X = MinX + Width;
	R.Max.Y = MinY + Height;
	return R;
}
FM_FUN_TSI Rect2BaseMinDim(v2_base<t> Min, v2_base<t> Dim) -> rect2_base<t> {
	rect2_base<t> R;
	R.Min = Min;
	R.Max = Min + Dim;
	return R;
}
FM_FUN_TSI Rect2BaseCenterRadius(v2_base<t> Center, t Radius) -> rect2_base<t> {
	rect2_base<t> R;
	R.Min.X = Center.X - Radius;
	R.Min.Y = Center.Y - Radius;
	R.Max.X = Center.X + Radius;
	R.Max.Y = Center.Y + Radius;
	return R;
}
FM_FUN_TSI Rect2BaseCenterRadius(v2_base<t> Center, v2_base<t> Radius) -> rect2_base<t> {
	rect2_base<t> R;
	R.Min = Center - Radius;
	R.Max = Center + Radius;
	return R;
}
FM_FUN_TSI Rect2BaseCenterDim(v2_base<t> Center, t Dim) -> rect2_base<t> {
	return Rect2BaseCenterRadius<t>(Center, Dim / (t)2);
}
FM_FUN_TSI Rect2BaseCenterDim(v2_base<t> Center, v2_base<t> Dim) -> rect2_base<t> {
	return Rect2BaseCenterRadius<t>(Center, Dim / (t)2);
}
FM_FUN_TSI Ptr(rect2_base<t>& A) -> t* {
	return &A.Min.X;
}
FM_FUN_TSI PtrMax(rect2_base<t>& A) -> t* {
	return &A.Max.X;
}
FM_FUN_TSI operator*(rect2_base<t> A, t Scalar) -> rect2_base<t> {
	A.Min *= Scalar;
	A.Max *= Scalar;
	return A;
}
FM_FUN_TSI operator/(rect2_base<t> A, t Scalar) -> rect2_base<t> {
	A.Min /= Scalar;
	A.Max /= Scalar;
	return A;
}
FM_FUN_TSI ScaleWithFixedMin(rect2_base<t> A, v2_base<t> Scalar) -> rect2_base<t> {
	auto NewDim = HadamardMul(GetDim(A), Scalar);
	return SetDimWithFixedMin(A, NewDim);
}
FM_FUN_TSI ScaleWithFixedMin(rect2_base<t> A, t Scalar) -> rect2_base<t> {
	return ScaleWithFixedMin(A, v2_base<t>(Scalar));
}
FM_FUN_TSI ScaleWithFixedMin(rect2_base<t>* A, v2_base<t> Scalar) -> void {
	*A = ScaleWithFixedMin(*A, Scalar);	
}
FM_FUN_TSI ScaleWithFixedMin(rect2_base<t>* A, t Scalar) -> void {
	*A = ScaleWithFixedMin(*A, v2_base<t>(Scalar));
}
FM_FUN_TSI ScaleWithFixedMax(rect2_base<t> A, v2_base<t> Scalar) -> rect2_base<t> {
	auto NewDim = HadamardMul(GetDim(A), Scalar);
	return SetDimWithFixedMax(A, NewDim);
}
FM_FUN_TSI ScaleWithFixedMax(rect2_base<t> A, t Scalar) -> rect2_base<t> {
	return ScaleWithFixedMax(A, v2_base<t>(Scalar));
}
FM_FUN_TSI ScaleWithFixedMax(rect2_base<t>* A, v2_base<t> Scalar) -> void {
	*A = ScaleWithFixedMax(*A, Scalar);	
}
FM_FUN_TSI ScaleWithFixedMax(rect2_base<t>* A, t Scalar) -> void {
	*A = ScaleWithFixedMax(*A, Scalar);	
}
FM_FUN_TSI ScaleWithFixedCenter(rect2_base<t> A, v2_base<t> Scalar) -> rect2_base<t> {
	auto NewDim = HadamardMul(GetDim(A), Scalar);
	return SetDimWithFixedCenter(A, NewDim);
}
FM_FUN_TSI ScaleWithFixedCenter(rect2_base<t> A, t Scalar) -> rect2_base<t> {
	return ScaleWithFixedCenter(A, v2_base<t>(Scalar));
}
FM_FUN_TSI ScaleWithFixedCenter(rect2_base<t>* A, v2_base<t> Scalar) -> void {
	*A = ScaleWithFixedCenter(*A, Scalar);	
}
FM_FUN_TSI ScaleWithFixedCenter(rect2_base<t>* A, t Scalar) -> void {
	*A = ScaleWithFixedCenter(*A, Scalar);	
}
FM_FUN_TSI AddRadius(rect2_base<t> A, v2_base<t> Radius) -> rect2_base<t> {
	A.Min -= Radius;
	A.Max += Radius;
	return A;
}
FM_FUN_TSI AddRadius(rect2_base<t> A, t Radius) -> rect2_base<t> {
	return AddRadius(A, v2_base<t>(Radius));
}
FM_FUN_TSI AddRadius(rect2_base<t>* A, v2_base<t> Radius) -> void {
	*A = AddRadius(*A, Radius);
}
FM_FUN_TSI AddRadius(rect2_base<t>* A, t Radius) -> void {
	*A = AddRadius(*A, Radius);
}
FM_FUN_TSI Offset(rect2_base<t> A, v2_base<t> Offset) -> rect2_base<t> {
	rect2_base<t> R;
	R.Min = A.Min + Offset;
	R.Max = A.Max + Offset;
	return R;
}
FM_FUN_TSI Offset(rect2_base<t>* A, v2_base<t> Offset) -> void {
	A->Min += Offset;
	A->Max += Offset;
}
FM_FUN_TSI MakeRectNotHaveNegativeDim(rect2_base<t> A) -> rect2_base<t> {
	rect2_base<t> R;
	R.Min = Min(A.Min, A.Max);
	R.Max = Max(A.Min, A.Max);
	return R;
}
FM_FUN_TSI MakeRectNotHaveNegativeDim(rect2_base<t>* A) -> void {
	*A = MakeRectNotHaveNegativeDim(*A);
}
FM_FUN_TSI MakeRectsNotHaveNegativeDim(rect2_base<t>* A, rect2_base<t>* B) -> void {
	MakeRectNotHaveNegativeDim(A);
	MakeRectNotHaveNegativeDim(B);
}
FM_FUN_TSI Intersect(rect2_base<t> Rect, v2_base<t> Point) -> bool {
	return Point.X >= Rect.Min.X && Point.X <= Rect.Max.X &&
	       Point.Y >= Rect.Min.Y && Point.Y <= Rect.Max.Y;
}
FM_FUN_TSI IntersectFlipAllowed(rect2_base<t> Rect, v2_base<t> Point) -> bool {
	MakeRectNotHaveNegativeDim(&Rect);
	return Intersect(Rect, Point);
}
FM_FUN_TSI Intersect(rect2_base<t> A, rect2_base<t> B) -> bool {
	return A.Max.X >= B.Min.X && A.Min.X <= B.Max.X &&
	       A.Max.Y >= B.Min.Y && A.Min.Y <= B.Max.Y;
}
FM_FUN_TSI FullyIntersect(rect2_base<t> A, rect2_base<t> B) -> bool {
	return Intersect(A, B.Min) && Intersect(A, B.Max) &&
	       Intersect(A, GetMaxXMinY(B)) && Intersect(A, GetMinXMaxY(B));
}
FM_FUN_TSI IntersectFlipAllowed(rect2_base<t> A, rect2_base<t> B) -> bool {
	MakeRectsNotHaveNegativeDim(&A, &B);
	return Intersect(A, B);
}
FM_FUN_TSI FullyIntersectFlipAllowed(rect2_base<t> A, rect2_base<t> B) -> bool {
	MakeRectsNotHaveNegativeDim(&A, &B);
	return FullyIntersect(A, B);
}
FM_FUN_TSI IntersectionRect(rect2_base<t> A, rect2_base<t> B, rect2_base<t>* Intersection) -> bool {
	auto RMin = Max(A.Min, B.Min);
	auto RMax = Min(A.Max, B.Max);
	if(RMin.X < RMax.X && RMin.Y < RMax.Y)
	{
		*Intersection = Rect2BaseMinMax<t>(RMin, RMax);
		return true;
	}
	else
	{
		return false;
	}
}
FM_FUN_TSI GetIntersectionRectFlipAllowed(rect2_base<t> A, rect2_base<t> B) -> rect2_base<t> {
	MakeRectNotHaveNegativeDim(&A, &B);
	return GetIntersectionRect(A, B);
}
FM_FUN_TSI Union(rect2_base<t> A, rect2_base<t> B) -> rect2_base<t> {
	rect2_base<t> R;
	R.Min = Min(A.Min, B.Min);
	R.Max = Max(A.Max, B.Max);
	return R;
}
FM_FUN_TSI operator==(rect2_base<t> A, rect2_base<t> B) -> bool {
	return A.Min == B.Min && A.Max == B.Max;
}
FM_FUN_TSI operator!=(rect2_base<t> A, rect2_base<t> B) -> bool {
	return !(A == B);
}
	
#define FM_RECT2_MIN_MAX(InsideName, T) \
	FM_FUN_SI Rect2##InsideName##MinMax(T Left, T Top, T Right, T Bottom) -> rect2_base<T>\
	{ return Rect2BaseMinMax<T>(Left, Top, Right, Bottom); }
FM_GENERIC_FUNCTION(FM_RECT2_MIN_MAX);
	
#define FM_RECT2_MIN_MAX_2(InsideName, T) \
	FM_FUN_SI Rect2##InsideName##MinMax(v2_base<T> Min, v2_base<T> Max) -> rect2_base<T>\
	{ return Rect2BaseMinMax<T>(Min, Max); }
FM_GENERIC_FUNCTION(FM_RECT2_MIN_MAX_2);
	
#define FM_RECT2_MIN_DIM(InsideName, T) \
	FM_FUN_SI Rect2##InsideName##MinDim(T Left, T Top, T Width, T Height) -> rect2_base<T>\
	{ return Rect2BaseMinDim<T>(Left, Top, Width, Height); }
FM_GENERIC_FUNCTION(FM_RECT2_MIN_DIM);
	
#define FM_RECT2_MIN_DIM_2(InsideName, T) \
	FM_FUN_SI Rect2##InsideName##MinDim(v2_base<T> Min, v2_base<T> Dim) -> rect2_base<T>\
	{ return Rect2BaseMinDim<T>(Min, Dim); }
FM_GENERIC_FUNCTION(FM_RECT2_MIN_DIM_2);
	
#define FM_RECT2_CENTER_RADIUS(InsideName, T) \
	FM_FUN_SI Rect2##InsideName##CenterRadius(v2_base<T> Center, T Radius) -> rect2_base<T>\
	{ return Rect2BaseCenterRadius<T>(Center, Radius); }
FM_GENERIC_FUNCTION(FM_RECT2_CENTER_RADIUS);
	
#define FM_RECT2_CENTER_RADIUS_2(InsideName, T) \
	FM_FUN_SI Rect2##InsideName##CenterRadius(v2_base<T> Center, v2_base<T> Radius) -> rect2_base<T>\
	{ return Rect2BaseCenterRadius<T>(Center, Radius); }
FM_GENERIC_FUNCTION(FM_RECT2_CENTER_RADIUS_2);
	
#define FM_RECT2_CENTER_DIM(InsideName, T) \
	FM_FUN_SI Rect2##InsideName##CenterDim(v2_base<T> Center, T Dim) -> rect2_base<T>\
	{ return Rect2BaseCenterDim<T>(Center, Dim); }
FM_GENERIC_FUNCTION(FM_RECT2_CENTER_DIM);
	
#define FM_RECT2_CENTER_DIM_2(InsideName, T) \
	FM_FUN_SI Rect2##InsideName##CenterDim(v2_base<T> Center, v2_base<T> Dim) -> rect2_base<T>\
	{ return Rect2BaseCenterDim<T>(Center, Dim); }
FM_GENERIC_FUNCTION(FM_RECT2_CENTER_DIM_2);
	
#define FM_Rect2ToMinMax(_Rect, _Min, _Max) \
	auto _Min = (_Rect).Min; \
	auto _Max = (_Rect).Max
	
#define FM_Rect2ToMinDim(_Rect, _Min, _Dim) \
	auto _Min = (_Rect).Min; \
	auto _Dim = GetDim(_Rect);

///////////////////////////////////////////
// headers of not inlined mat4 functions //
///////////////////////////////////////////
FM_FUN_C operator*(mat4 A, mat4 B) -> mat4; 
FM_FUN Mat4Orthographic(float Left, float Right, float Bottom, float Top, float Near = 0, float Far = 1) -> mat4;
FM_FUN Mat4Perspective(float FOV, float AspectRatio, float near, float Far) -> mat4;
FM_FUN Mat4LookAt(vec3 Eye, vec3 At, vec3 Up = Vec3(0.f, 1.f, 0.f)) -> mat4;
FM_FUN Mat4LookAt(v3 Eye, v3 At, v3 Up = {0.f, 1.f, 0.f}) -> mat4;

////////////////////
// mat4 functions //
////////////////////
FM_FUN_I mat4::operator[](uint32_t Index) -> float& {
	FM_ASSERT(Index >= 0 && Index <= 15);
	return *((float*)(Columns) + Index);
}
FM_FUN_IC mat4::GetColumnVec4(uint32_t Index) -> vec4 {
	FM_ASSERT(Index >= 0 && Index <= 3);
	return Vec4(Columns[Index]);
}
FM_FUN_IC mat4::GetColumnV4(uint32_t Index) -> v4 {
	return CastToV4(GetColumnVec4(Index));
}
FM_FUN_IC mat4::SetColumn(uint32_t Index, vec4 Col) -> void {
	FM_ASSERT(Index >= 0 && Index <= 3);
	Columns[Index] = Col.M;
}
FM_FUN_IC mat4::SetColumn(uint32_t Index, v4 Col) -> void {
	SetColumn(Index, CastToVec4(Col));
}
FM_FUN_IC mat4::SetColumn(uint32_t Index, float X, float Y, float Z, float W) -> void {
	FM_ASSERT(Index >= 0 && Index <= 3);
	Columns[Index] = _mm_set_ps(W, Z, Y, X);
}
FM_FUN_IC mat4::SwapColumns(uint32_t Col1Index, uint32_t Col2Index) -> void {
	FM_ASSERT(Col1Index >= 0 && Col1Index <= 3 && Col1Index >= 0 && Col1Index <= 3);
	__m128 Temp = Columns[Col1Index];
	Columns[Col1Index] = Columns[Col2Index];
	Columns[Col2Index] = Temp;
}
FM_FUN_IC mat4::GetRowVec4(uint32_t Index) -> vec4 {
	return CastToVec4(GetRowV4(Index));
}
FM_FUN_IC mat4::SetRow(uint32_t Index, float X, float Y, float Z, float W) -> void {
	SetRow(Index, v4(X, Y, Z, W));
}
FM_FUN_IC mat4::SetRow(uint32_t Index, vec4 V) -> void {
	SetRow(Index, CastToV4(V));
}
FM_FUN_IC mat4::SwapRows(uint32_t Row1Index, uint32_t Row2Index) -> void {
	FM_ASSERT(Row1Index >= 0 && Row2Index <= 3 && Row1Index >= 0 && Row2Index <= 3);
	v4 Row1 = GetRowV4(Row1Index);
	v4 Row2 = GetRowV4(Row2Index);
	SetRow(Row2Index, Row1);
	SetRow(Row1Index, Row2);
}
FM_FUN_IC mat4::GetMainDiagonalV4() -> v4 {
	v4 R;
	R.X = priv::GetX(Columns[0]);
	R.Y = priv::GetY(Columns[1]);
	R.Z = priv::GetZ(Columns[2]);
	R.W = priv::GetW(Columns[3]);
	return R;
}
FM_FUN_IC mat4::GetMainDiagonalVec4() -> vec4 {
	return CastToVec4(GetMainDiagonalV4());
}
FM_FUN_IC mat4::SetMainDiagonal(float X, float Y, float Z, float W) -> void {
	Columns[0] = priv::SetX(Columns[0], X);
	Columns[1] = priv::SetY(Columns[1], Y);
	Columns[2] = priv::SetZ(Columns[2], Z);
	Columns[3] = priv::SetW(Columns[3], W);
}
FM_FUN_IC mat4::SetMainDiagonal(v4 V) -> void {
	SetMainDiagonal(V.X, V.Y, V.Z, V.W);
}
FM_FUN_IC mat4::SetMainDiagonal(vec4 V) -> void {
	SetMainDiagonal(CastToV4(V));
}
FM_FUN_SIC Mat4FromColumnMajorMemory(float* Mem) -> mat4 {
	mat4 R;
	for(int32_t i = 0; i < 4; ++i)
		R.Columns[i] = _mm_load_ps(Mem + i*4);
	return R;
}
FM_FUN_SIC Mat4FromRowMajorMemory(float* Mem) -> mat4 {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Mem[0], Mem[4], Mem[8], Mem[12]);
	R.Columns[1] = _mm_setr_ps(Mem[1], Mem[5], Mem[9], Mem[13]);
	R.Columns[2] = _mm_setr_ps(Mem[2], Mem[6], Mem[10], Mem[14]);
	R.Columns[3] = _mm_setr_ps(Mem[3], Mem[7], Mem[11], Mem[15]);
	return R;
}
FM_FUN_SIC Mat4() -> mat4 {
	mat4 R;
	R.Columns[0] = _mm_setzero_ps();
	R.Columns[1] = _mm_setzero_ps();
	R.Columns[2] = _mm_setzero_ps();
	R.Columns[3] = _mm_setzero_ps();
	return R;
}
FM_FUN_SIC Mat4Diagonal(float Diag) -> mat4 {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Diag, 0.f, 0.f, 0.f);
	R.Columns[1] = _mm_setr_ps(0.f, Diag, 0.f, 0.f);
	R.Columns[2] = _mm_setr_ps(0.f, 0.f, Diag, 0.f);
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, Diag);
	return R;
}
FM_FUN_SIC Mat4Diagonal(float DiagX, float DiagY, float DiagZ, float DiagW) -> mat4 {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(DiagX, 0.f, 0.f, 0.f);
	R.Columns[1] = _mm_setr_ps(0.f, DiagY, 0.f, 0.f);
	R.Columns[2] = _mm_setr_ps(0.f, 0.f, DiagZ, 0.f);
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, DiagW);
	return R;
}
FM_FUN_SIC Mat4Diagonal(v4 Diag) -> mat4 {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Diag.X, 0.f, 0.f, 0.f);
	R.Columns[1] = _mm_setr_ps(0.f, Diag.Y, 0.f, 0.f);
	R.Columns[2] = _mm_setr_ps(0.f, 0.f, Diag.Z, 0.f);
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, Diag.W);
	return R;
}
FM_FUN_SIC Mat4Diagonal(vec4 Diag) -> mat4 {
	return Mat4Diagonal(CastToV4(Diag));
}
FM_FUN_SIC Mat4Identity() -> mat4 {
	return Mat4Diagonal(1.f);
}
FM_FUN_SIC Mat4FromColumns(vec4 Col1, vec4 Col2, vec4 Col3, vec4 Col4) -> mat4 {
	mat4 R;
	R.Columns[0] = Col1.M;
	R.Columns[1] = Col2.M;
	R.Columns[2] = Col3.M;
	R.Columns[3] = Col4.M;
	return R;
}
FM_FUN_SIC Mat4FromColumns(v4 Col1, v4 Col2, v4 Col3, v4 Col4) -> mat4 {
	return Mat4FromColumns(CastToVec4(Col1), CastToVec4(Col2), CastToVec4(Col3), CastToVec4(Col4));
}
FM_FUN_SIC Mat4FromColumns(vec3 Col1, vec3 Col2, vec3 Col3, vec3 Col4) -> mat4 {
	mat4 R;
	R.Columns[0] = Col1.M;
	R.Columns[1] = Col2.M;
	R.Columns[2] = Col3.M;
	R.Columns[3] = Col4.M;
	R.SetRow(3, 0.f, 0.f, 0.f, 1.f);
	return R;
}
FM_FUN_SIC Mat4FromColumns(v3 Col1, v3 Col2, v3 Col3, v3 Col4) -> mat4 {
	return Mat4FromColumns(CastToVec3(Col1), CastToVec3(Col2), CastToVec3(Col3), CastToVec3(Col4));
}
FM_FUN_SIC Mat4FromColumns(
	float E11, float E21, float E31, float E41,
    float E12, float E22, float E32, float E42,
    float E13, float E23, float E33, float E43,
    float E14, float E24, float E34, float E44) -> mat4
{
	mat4 R;
	R.Columns[0] = _mm_setr_ps(E11, E21, E31, E41);
	R.Columns[1] = _mm_setr_ps(E12, E22, E32, E42);
	R.Columns[2] = _mm_setr_ps(E13, E23, E33, E43);
	R.Columns[3] = _mm_setr_ps(E14, E24, E34, E44);
	return R;
}
FM_FUN_SIC Mat4FromRows(vec4 Row1, vec4 Row2, vec4 Row3, vec4 Row4) -> mat4 {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Row1.X(), Row2.X(), Row3.X(), Row4.X());
	R.Columns[1] = _mm_setr_ps(Row1.Y(), Row2.Y(), Row3.Y(), Row4.Y());
	R.Columns[2] = _mm_setr_ps(Row1.Z(), Row2.Z(), Row3.Z(), Row4.Z());
	R.Columns[3] = _mm_setr_ps(Row1.W(), Row2.W(), Row3.W(), Row4.W());
	return R;
}
FM_FUN_SIC Mat4FromRows(v4 Row1, v4 Row2, v4 Row3, v4 Row4) -> mat4 {
	return Mat4FromRows(CastToVec4(Row1), CastToVec4(Row2), CastToVec4(Row3), CastToVec4(Row4));
}
FM_FUN_SIC Mat4FromRows(
	float E11, float E12, float E13, float E14,
    float E21, float E22, float E23, float E24,
    float E31, float E32, float E33, float E34,
    float E41, float E42, float E43, float E44) -> mat4
{
	mat4 R;
	R.Columns[0] = _mm_setr_ps(E11, E21, E31, E41);
	R.Columns[1] = _mm_setr_ps(E12, E22, E32, E42);
	R.Columns[2] = _mm_setr_ps(E13, E23, E33, E43);
	R.Columns[3] = _mm_setr_ps(E14, E24, E34, E44);
	return R;
}
FM_FUN_SIC Mat4FromRows(vec3 Row1, vec3 Row2, vec3 Row3, vec3 Row4) -> mat4 {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Row1.X(), Row2.X(), Row3.X(), Row4.X());
	R.Columns[1] = _mm_setr_ps(Row1.Y(), Row2.Y(), Row3.Y(), Row4.Y());
	R.Columns[2] = _mm_setr_ps(Row1.Z(), Row2.Z(), Row3.Z(), Row4.Z());
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, 1.f);
	return R;
}
FM_FUN_SIC Mat4FromRows(v3 Row1, v3 Row2, v3 Row3, v3 Row4) -> mat4 {
	return Mat4FromRows(CastToVec3(Row1), CastToVec3(Row2), CastToVec3(Row3), CastToVec3(Row4));
}
FM_FUN_SI Ptr(const mat4& V) -> float* {
	return (float*)(&V);
}
FM_FUN_SIC Store(float* Mem, mat4 Mat) -> void {
	for(int32_t Col = 0; Col < 4; ++Col)
		_mm_storeu_ps(Mem + Col*4, Mat.Columns[Col]);
}
FM_FUN_SIC Store16ByteAligned(float* Mem, mat4 Mat) -> void {
	FM_ASSERT(Mem % 16 == 0);
	for(int32_t Col = 0; Col < 4; ++Col)
		_mm_store_ps(Mem + Col*4, Mat.Columns[Col]);
}
FM_FUN_SIC operator+(mat4 A, mat4 B) -> mat4 {
	for(int32_t Col = 0; Col < 4; ++Col)
		A.Columns[Col] = _mm_add_ps(A.Columns[Col], B.Columns[Col]);
	return A;
}
FM_FUN_SIC operator-(mat4 A, mat4 B) -> mat4 {
	for(int32_t Col = 0; Col < 4; ++Col)
		A.Columns[Col] = _mm_sub_ps(A.Columns[Col], B.Columns[Col]);
	return A;
}
FM_FUN_SIC operator*(mat4 M, vec4 V) -> vec4 {
	__m128 Row1 = _mm_setr_ps(priv::GetX(M.Columns[0]), priv::GetX(M.Columns[1]),
	                          priv::GetX(M.Columns[2]), priv::GetX(M.Columns[3]));
	__m128 Row2 = _mm_setr_ps(priv::GetY(M.Columns[0]), priv::GetY(M.Columns[1]),
	                          priv::GetY(M.Columns[2]), priv::GetY(M.Columns[3]));
	__m128 Row3 = _mm_setr_ps(priv::GetZ(M.Columns[0]), priv::GetZ(M.Columns[1]),
	                          priv::GetZ(M.Columns[2]), priv::GetZ(M.Columns[3]));
	__m128 Row4 = _mm_setr_ps(priv::GetW(M.Columns[0]), priv::GetW(M.Columns[1]),
	                          priv::GetW(M.Columns[2]), priv::GetW(M.Columns[3]));
	float X = priv::SumOfElements(_mm_mul_ps(Row1, V.M)); 
	float Y = priv::SumOfElements(_mm_mul_ps(Row2, V.M)); 
	float Z = priv::SumOfElements(_mm_mul_ps(Row3, V.M)); 
	float W = priv::SumOfElements(_mm_mul_ps(Row4, V.M));
	return Vec4(X, Y, Z, W);
}
FM_FUN_SIC operator*(mat4 M, v4 V) -> v4 {
	// TODO: Try to implement the logic in v4 function and make vec4 version call it. 
	//       Maybe just make separate implementations. Profile it!
	return CastToV4(M * CastToVec4(V));
}
FM_FUN_SIC operator*(mat4 M, float Scalar) -> mat4 {
	__m128 ScalarM = _mm_set1_ps(Scalar);
	for(uint32_t Col = 0; Col < 4; ++Col)
		M.Columns[Col] = _mm_mul_ps(M.Columns[Col], ScalarM);
	return M;
}
FM_FUN_SIC HadamardMul(mat4 A, mat4 B) -> mat4 {
	for(uint32_t Col = 0; Col < 4; ++Col)
		A.Columns[Col] = _mm_mul_ps(A.Columns[Col], B.Columns[Col]);
	return A;
}
FM_FUN_SIC HadamardDiv(mat4 A, mat4 B) -> mat4 {
	for(uint32_t Col = 0; Col < 4; ++Col)
		A.Columns[Col] = _mm_div_ps(A.Columns[Col], B.Columns[Col]);
	return A;
}
FM_FUN_SIC operator*(float Scalar, mat4 M) -> mat4 {
	return M * Scalar;
}
FM_FUN_SIC operator*=(mat4& M, float Scalar) -> mat4& {
	M = M * Scalar;	
	return M;
}
FM_FUN_SIC operator/(mat4 M, float Scalar) -> mat4 {
	__m128 ScalarM = _mm_set1_ps(Scalar);
	for(uint32_t Col = 0; Col < 4; ++Col)
		M.Columns[Col] = _mm_div_ps(M.Columns[Col], ScalarM);
	return M;
}
FM_FUN_SIC operator/=(mat4& M, float Scalar) -> mat4& {
	M = M / Scalar;
	return M;
}
FM_FUN_SIC operator==(mat4 A, mat4 B) -> bool {
	bool R = true;
	for(uint32_t Col = 0; Col < 4; ++Col)
	{
		if(Vec4(A.Columns[Col]) != Vec4(B.Columns[Col]))
		{
			R = false;
			break;
		}
	}
	return R;
}
FM_FUN_SIC operator!=(mat4 A, mat4 B) -> bool {
	return !(A == B);
}
FM_FUN_SIC Transpose(mat4* M) -> void {
	_MM_TRANSPOSE4_PS(M->Columns[0], M->Columns[1], M->Columns[2], M->Columns[3]);
}
FM_FUN_SIC Transpose(mat4 M) -> mat4 {
	_MM_TRANSPOSE4_PS(M.Columns[0], M.Columns[1], M.Columns[2], M.Columns[3]);
	return M;
}
FM_FUN_SIC Mat4Translation(float X, float Y, float Z) -> mat4 {
	return Mat4FromRows(
		1.f, 0.f, 0.f, X,
		0.f, 1.f, 0.f, Y,
		0.f, 0.f, 1.f, Z,
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN_SIC Mat4Translation(v3 Translation) -> mat4 {
	return Mat4FromRows(
		1.f, 0.f, 0.f, Translation.X,
		0.f, 1.f, 0.f, Translation.Y,
		0.f, 0.f, 1.f, Translation.Z,
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN_SIC Mat4Translation(vec3 Translation) -> mat4 {
	return Mat4Translation(CastToV3(Translation));
}
FM_FUN_SIC Mat4Translation(float Translation) -> mat4 {
	return Mat4FromRows(
		1.f, 0.f, 0.f, Translation,
		0.f, 1.f, 0.f, Translation,
		0.f, 0.f, 1.f, Translation,
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN_SIC Translate(mat4* M, float X, float Y, float Z) -> void {
	M->Columns[3] = _mm_add_ps(M->Columns[3], _mm_set_ps(0.f, Z, Y, X));
}
FM_FUN_SIC Translate(mat4* M, vec3 Trans) -> void {
	M->Columns[3] = _mm_add_ps(M->Columns[3], Trans.M);
}
FM_FUN_SIC Translate(mat4* M, v3 Trans) -> void {
	Translate(M, CastToVec3(Trans));
}
FM_FUN_SIC Translate(mat4* M, float Trans) -> void {
	M->Columns[3] = _mm_add_ps(M->Columns[3], _mm_set_ps(0.f, Trans, Trans, Trans));
}
FM_FUN_SIC Mat4Scale(float Scalar) -> mat4 {
	return Mat4Diagonal(Scalar, Scalar, Scalar, 1.f);
} 
FM_FUN_SIC Mat4Scale(float ScalarX, float ScalarY, float ScalarZ) -> mat4 {
	return Mat4Diagonal(ScalarX, ScalarY, ScalarZ, 1.f);
} 
FM_FUN_SIC Mat4Scale(v3 Scalar) -> mat4 {
	return Mat4Diagonal(Scalar.X, Scalar.Y, Scalar.Z, 1.f); 
}
FM_FUN_SIC Mat4Scale(vec3 Scalar) -> mat4 {
	return Mat4Diagonal(Scalar.X(), Scalar.Y(), Scalar.Z(), 1.f); 
}
FM_FUN_SIC Scale(mat4* M, float X, float Y, float Z) -> void {
	// TODO: Try to Cast to vec and v back and forth and Profile!
	v4 MainDiag = M->GetMainDiagonalV4();
	v4 ScalarVec(X, Y, Z, 1.f);
	MainDiag = HadamardMul(MainDiag, ScalarVec);
	M->SetMainDiagonal(MainDiag);
}
FM_FUN_SIC Scale(mat4* M, float Scalar) -> void {
	Scale(M, Scalar, Scalar, Scalar);
}
FM_FUN_SIC Scale(mat4* M, vec3 Scalar) -> void {
	// TODO: Try to Cast to vec and v back and forth and Profile!
	vec4 MainDiag = M->GetMainDiagonalVec4();
	MainDiag.M = _mm_mul_ps(MainDiag.M, Scalar.M);
	MainDiag.M = priv::SetW(MainDiag.M, 1.f);
	M->SetMainDiagonal(MainDiag);
}
FM_FUN_SIC Scale(mat4* M, v3 Scalar) -> void {
	return Scale(M, CastToVec3(Scalar));
}
FM_FUN_SIC Mat4RotationRadians(float Radians, float AxisX, float AxisY, float AxisZ) -> mat4 {
	vec3 Normalized = Normalize(Vec3(AxisX, AxisY, AxisZ));
	AxisX = Normalized.X();
	AxisY = Normalized.Y();
	AxisZ = Normalized.Z();
	float SinTheta = sinf(Radians);
	float CosTheta = cosf(Radians);
	float CosVal = 1.f - CosTheta;
	return Mat4FromColumns(
		(AxisX * AxisX * CosVal) + CosTheta,
		(AxisX * AxisY * CosVal) + (AxisZ * SinTheta),
		(AxisX * AxisZ * CosVal) - (AxisY * SinTheta),
		0.f,
		(AxisY * AxisX * CosVal) - (AxisZ * SinTheta),
		(AxisY * AxisY * CosVal) + CosTheta,
		(AxisY * AxisZ * CosVal) + (AxisX * SinTheta),
		0.f,
		(AxisZ * AxisX * CosVal) + (AxisY * SinTheta),
		(AxisZ * AxisY * CosVal) - (AxisX * SinTheta),
		(AxisZ * AxisZ * CosVal) + CosTheta,
		0.f,
		0.f, 0.f, 0.f, 1.f);
} 
FM_FUN_SIC Mat4RotationRadians(float Radians, v3 Axis) -> mat4 {
	return Mat4RotationRadians(Radians, Axis.X, Axis.Y, Axis.Z);
}
FM_FUN_SIC Mat4RotationRadians(float Radians, vec3 Axis) -> mat4 {
	return Mat4RotationRadians(Radians, Axis.X(), Axis.Y(), Axis.Z());
}
FM_FUN_SIC Mat4RotationAroundXAxisRadians(float R) -> mat4 {
	return Mat4FromRows(
		1.f, 0.f, 0.f, 0.f,
		0.f, cosf(R), -sinf(R), 0.f,
		0.f, sinf(R), cosf(R), 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN_SIC Mat4RotationAroundYAxisRadians(float R) -> mat4 {
	return Mat4FromRows(
		cosf(R), 0.f, sinf(R), 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sinf(R), 0.f, cosf(R), 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN_SIC Mat4RotationAroundZAxisRadians(float R) -> mat4 {
	return Mat4FromRows(
		cosf(R), -sinf(R), 0.f, 0.f,
		sinf(R), cosf(R), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN_SIC Mat4RotationAroundAllAxesRadians(float R) -> mat4 {
	return Mat4RotationRadians(R, 1.f, 1.f, 1.f);
}
FM_FUN_SIC RotateRadians(mat4* M, float Radians, float AxisX, float AxisY, float AxisZ) -> void {
	*M = *M * Mat4RotationRadians(Radians, AxisX, AxisY, AxisZ);
}
FM_FUN_SIC RotateRadians(mat4* M, float Radians, vec3 Axes) -> void {
	*M = *M * Mat4RotationRadians(Radians, Axes);
}
FM_FUN_SIC RotateRadians(mat4* M, float Radians, v3 Axes) -> void {
	*M = *M * Mat4RotationRadians(Radians, Axes);
}
FM_FUN_SIC RotateAroundXAxisRadians(mat4* M, float Radians) -> void {
	*M = *M * Mat4RotationAroundXAxisRadians(Radians);	
}
FM_FUN_SIC RotateAroundYAxisRadians(mat4* M, float Radians) -> void {
	*M = *M * Mat4RotationAroundYAxisRadians(Radians);
}
FM_FUN_SIC RotateAroundZAxisRadians(mat4* M, float Radians) -> void {
	*M = *M * Mat4RotationAroundZAxisRadians(Radians);
}
FM_FUN_SIC RotateAroundAllAxesRadians(mat4* M, float Radians) -> void {
	*M = *M * Mat4RotationAroundAllAxesRadians(Radians);
}
FM_FUN_SIC Mat4RotationDegrees(float Degrees, float AxisX, float AxisY, float AxisZ) -> mat4 {
	return Mat4RotationRadians(DegreesToRadians(Degrees), AxisX, AxisY, AxisZ);
} 
FM_FUN_SIC Mat4RotationDegrees(float Degrees, v3 Axis) -> mat4 {
	return Mat4RotationRadians(DegreesToRadians(Degrees), Axis);
}
FM_FUN_SIC Mat4RotationDegrees(float Degrees, vec3 Axis) -> mat4 {
	return Mat4RotationRadians(DegreesToRadians(Degrees), Axis);
}
FM_FUN_SIC Mat4RotationAroundXAxisDegrees(float Degrees) -> mat4 {
	return Mat4RotationAroundXAxisRadians(DegreesToRadians(Degrees));
}
FM_FUN_SIC Mat4RotationAroundYAxisDegrees(float Degrees) -> mat4 {
	return Mat4RotationAroundYAxisRadians(DegreesToRadians(Degrees));
}
FM_FUN_SIC Mat4RotationAroundZAxisDegrees(float Degrees) -> mat4 {
	return Mat4RotationAroundZAxisRadians(DegreesToRadians(Degrees));
}
FM_FUN_SIC Mat4RotationAroundAllAxesDegrees(float Degrees) -> mat4 {
	return Mat4RotationAroundAllAxesRadians(DegreesToRadians(Degrees));
}
FM_FUN_SIC RotateDegrees(mat4* M, float Degrees, float AxisX, float AxisY, float AxisZ) -> void {
	RotateRadians(M, DegreesToRadians(Degrees), AxisX, AxisY, AxisZ);
} 
FM_FUN_SIC RotateDegrees(mat4* M, float Degrees, v3 Axis) -> void {
	RotateRadians(M, DegreesToRadians(Degrees), Axis);
}
FM_FUN_SIC RotateDegrees(mat4* M, float Degrees, vec3 Axis) -> void {
	RotateRadians(M, DegreesToRadians(Degrees), Axis);
}
FM_FUN_SIC RotateAroundXAxisDegrees(mat4* M, float Degrees) -> void {
	RotateAroundXAxisRadians(M, DegreesToRadians(Degrees));
}
FM_FUN_SIC RotateAroundYAxisDegrees(mat4* M, float Degrees) -> void {
	RotateAroundYAxisRadians(M, DegreesToRadians(Degrees));
}
FM_FUN_SIC RotateAroundZAxisDegrees(mat4* M, float Degrees) -> void {
	RotateAroundZAxisRadians(M, DegreesToRadians(Degrees));
}
FM_FUN_SIC RotateAroundAllAxesDegrees(mat4* M, float Degrees) -> void {
	RotateAroundAllAxesRadians(M, DegreesToRadians(Degrees));
}
FM_FUN_SIC Mat4ShearXAxis(float Y, float Z) -> mat4 {
	return Mat4FromRows(
		1.f, 0.f, 0.f, 0.f,
		Y,   1.f, 0.f, 0.f,
		Z,   0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN_SIC Mat4ShearYAxis(float X, float Z) -> mat4 {
	return Mat4FromRows(
		1.f, X,   0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, Z,   1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN_SIC Mat4ShearZAxis(float X, float Y) -> mat4 {
	return Mat4FromRows(
		1.f, 0.f, X,   0.f,
		0.f, 1.f, Y,   0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN_SIC Mat4Shear(float XY, float XZ, float YX, float YZ, float ZX, float ZY) -> mat4 {
	return Mat4FromRows(
		1.f, YX, ZX, 0.f,
		XY, 1.f, ZY, 0.f,
		XZ, YZ, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN_SIC ShearXAxis(mat4* M, float Y, float Z) -> void {
	*M = *M * Mat4ShearXAxis(Y, Z);
}
FM_FUN_SIC ShearYAxis(mat4* M, float X, float Z) -> void {
	*M = *M * Mat4ShearYAxis(X, Z);
} 
FM_FUN_SIC ShearZAxis(mat4* M, float X, float Y) -> void {
	*M = *M * Mat4ShearZAxis(X, Y);
} 
FM_FUN_SIC Shear(mat4* M, float XY, float XZ, float YX, float YZ, float ZX, float ZY) -> void {
	*M = *M * Mat4Shear(XY, XZ, YX, YZ, ZX, ZY);
}
FM_FUN_SIC Mat4TranslationScaleRotationRadians(v3 Translation, v3 Scale, float Rotation, v3 RotationAxes) -> mat4 {
	mat4 R = Mat4Scale(Scale);
	RotateRadians(&R, Rotation, RotationAxes);
	Translate(&R, Translation);
	return R;
}
FM_FUN_SIC Mat4TranslationScaleRotationRadians(vec3 Translation, vec3 Scale, float Rotation, vec3 RotationAxes) -> mat4 {
	mat4 R = Mat4Scale(Scale);
	RotateRadians(&R, Rotation, RotationAxes);
	Translate(&R, Translation);
	return R;
}
FM_FUN_SIC Mat4TranslationScaleRotationDegrees(v3 Translation, v3 Scale, float Rotation, v3 RotationAxes) -> mat4 {
	return Mat4TranslationScaleRotationRadians(Translation, Scale, DegreesToRadians(Rotation), RotationAxes);
}
FM_FUN_SIC Mat4TranslationScaleRotationDegrees(vec3 Translation, vec3 Scale, float Rotation, vec3 RotationAxes) -> mat4 {
	return Mat4TranslationScaleRotationRadians(Translation, Scale, DegreesToRadians(Rotation), RotationAxes);
}
FM_FUN_SIC Mat4TranslationScale(v3 Translation, v3 Scale) -> mat4 {
	mat4 R = Mat4Scale(Scale);
	Translate(&R, Translation);
	return R;
}
FM_FUN_SIC Mat4TranslationScale(vec3 Translation, vec3 Scale) -> mat4 {
	mat4 R = Mat4Scale(Scale);
	Translate(&R, Translation);
	return R;
}
FM_FUN_SIC Mat4TranslationRotationRadians(v3 Translation, float Rotation, v3 RotationAxes) -> mat4 {
	mat4 R = Mat4RotationRadians(Rotation, RotationAxes);
	Translate(&R, Translation);
	return R;
}
FM_FUN_SIC Mat4TranslationRotationRadians(vec3 Translation, float Rotation, vec3 RotationAxes) -> mat4 {
	mat4 R = Mat4RotationRadians(Rotation, RotationAxes);
	Translate(&R, Translation);
	return R;
}
FM_FUN_SIC Mat4TranslationRotationDegrees(v3 Translation, float Rotation, v3 RotationAxes) -> mat4 {
	return Mat4TranslationRotationRadians(Translation, DegreesToRadians(Rotation), RotationAxes);
}
FM_FUN_SIC Mat4TranslationRotationDegrees(vec3 Translation, float Rotation, vec3 RotationAxes) -> mat4 {
	return Mat4TranslationRotationRadians(Translation, DegreesToRadians(Rotation), RotationAxes);
}
FM_FUN_SIC Mat4ScaleRotationRadians(v3 Scale, float Rotation, v3 RotationAxes) -> mat4 {
	mat4 R = Mat4Scale(Scale);
	RotateRadians(&R, Rotation, RotationAxes);
	return R;
}
FM_FUN_SIC Mat4ScaleRotationRadians(vec3 Scale, float Rotation, vec3 RotationAxes) -> mat4 {
	mat4 R = Mat4Scale(Scale);
	RotateRadians(&R, Rotation, RotationAxes);
	return R;
}
FM_FUN_SIC Mat4ScaleRotationDegrees(v3 Scale, float Rotation, v3 RotationAxes) -> mat4 {
	return Mat4ScaleRotationRadians(Scale, DegreesToRadians(Rotation), RotationAxes);
}
FM_FUN_SIC Mat4ScaleRotationDegrees(vec3 Scale, float Rotation, vec3 RotationAxes) -> mat4 {
	return Mat4ScaleRotationRadians(Scale, DegreesToRadians(Rotation), RotationAxes);
}
FM_FUN_SIC Mat4OrthographicTopDown(rect2 A) -> mat4 {
	FM_Rect2ToMinMax(A, Min, Max);
	return Mat4Orthographic(Min.X, Max.X, Max.Y, Min.Y);
}
FM_FUN_SIC Mat4OrthographicBottomUp(rect2 A) -> mat4 {
	FM_Rect2ToMinMax(A, Min, Max);
	return Mat4Orthographic(Min.X, Max.X, Min.Y, Max.Y);
}

}

#endif // FAST_MATH_H

#ifndef FM_IMPLEMENTATION_ALREADY_DEFINED
#ifdef FM_IMPLEMENTATION
#define FM_IMPLEMENTATION_ALREADY_DEFINED

namespace fm {

////////////////////////////////
// not inlined mat4 functions //
////////////////////////////////
FM_FUN_C operator*(mat4 A, mat4 B) -> mat4 {
	__m128 Row;
		
	Row = _mm_setr_ps(priv::GetX(A.Columns[0]), priv::GetX(A.Columns[1]),
	                  priv::GetX(A.Columns[2]), priv::GetX(A.Columns[3]));
	float R11 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[0]));
	float R12 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[1]));
	float R13 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[2]));
	float R14 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[3]));
		
	Row = _mm_setr_ps(priv::GetY(A.Columns[0]), priv::GetY(A.Columns[1]),
	                  priv::GetY(A.Columns[2]), priv::GetY(A.Columns[3]));
	float R21 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[0]));
	float R22 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[1]));
	float R23 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[2]));
	float R24 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[3]));
		
	Row = _mm_setr_ps(priv::GetZ(A.Columns[0]), priv::GetZ(A.Columns[1]),
	                  priv::GetZ(A.Columns[2]), priv::GetZ(A.Columns[3]));
	float R31 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[0]));
	float R32 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[1]));
	float R33 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[2]));
	float R34 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[3]));
		
	Row = _mm_setr_ps(priv::GetW(A.Columns[0]), priv::GetW(A.Columns[1]),
	                  priv::GetW(A.Columns[2]), priv::GetW(A.Columns[3]));
	float R41 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[0]));
	float R42 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[1]));
	float R43 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[2]));
	float R44 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[3]));
		
	return Mat4FromColumns(
		R11, R21, R31, R41,
	    R12, R22, R32, R42,
		R13, R23, R33, R43,
		R14, R24, R34, R44);
}
FM_FUN Mat4Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far) -> mat4 {
	float RL = Right - Left;
	float TB = Top - Bottom;
	float FN = Far - Near; 
		
	return Mat4FromRows(
		2.f / RL, 0.f, 0.f, -((Right + Left) / RL),
		0.f, 2.f / TB, 0.f, -((Top + Bottom) / TB),
		0.f, 0.f, -2.f / FN, -((Far + Near) / FN),
		0.f, 0.f, 0.f, 1.f);
}
FM_FUN Mat4Perspective(float Fov, float AspectRatio, float Near, float Far) -> mat4 {
	float Cotangent = 1.f / tanf(Fov * Pi / 360.f);
	float NF = Near - Far;
		
	return Mat4FromRows(
		Cotangent / AspectRatio, 0.f, 0.f, 0.f,
		0.f, Cotangent, 0.f, 0.f,
		0.f, 0.f, 
		(Near + Far) / NF,
		(2 * Near * Far) / NF,
		0.f, 0.f, -1.f, 0.f);
}
FM_FUN Mat4LookAt(vec3 Eye, vec3 At, vec3 Up) -> mat4 {
	vec3 Forward = Normalize(At - Eye);
	vec3 Right = Cross(Forward, Up); // TODO(docs): We assume that Up is normalized
	Up = Cross(Right, Forward);
	return Mat4FromColumns(
		Right, Up, -Forward,
		Vec3(-Dot(Right, Eye), -Dot(Up, Eye), Dot(Forward, Eye)));
}
FM_FUN Mat4LookAt(v3 Eye, v3 At, v3 Up) -> mat4 {
	v3 Forward = Normalize(At - Eye);
	v3 Right = Cross(Forward, Up); // TODO(docs): We assume that Up is normalized
	Up = Cross(Right, Forward);
	return Mat4FromColumns(
		Right, Up, -Forward,
		v3(-Dot(Right, Eye), -Dot(Up, Eye), Dot(Forward, Eye)));
}
FM_FUN_C mat4::GetRowV4(uint32_t Index) -> v4 {
	FM_ASSERT(Index >= 0 && Index <= 3);
	switch(Index)
	{
		case 0: {
			return v4(
				priv::GetX(Columns[0]), priv::GetX(Columns[1]),
				priv::GetX(Columns[2]), priv::GetX(Columns[3]));
		} break;
		
		case 1: {
			return v4(
				priv::GetY(Columns[0]), priv::GetY(Columns[1]),
				priv::GetY(Columns[2]), priv::GetY(Columns[3]));
		} break;
	
		case 2: {
			return v4(
				priv::GetZ(Columns[0]), priv::GetZ(Columns[1]),
				priv::GetZ(Columns[2]), priv::GetZ(Columns[3]));
		} break;
	
		case 3: {
			return v4(
				priv::GetW(Columns[0]), priv::GetW(Columns[1]),
				priv::GetW(Columns[2]), priv::GetW(Columns[3]));
		} break;
		
		default: {
			FM_ERROR(); // Index has to be in range from 0 to 3
		}
	}
}
FM_FUN_C mat4::SetRow(uint32_t Index, v4 Row) -> void {
	FM_ASSERT(Index >= 0 && Index <= 3);
	switch(Index)
	{
		case 0: {
			Columns[0] = priv::SetX(Columns[0], Row.X);
			Columns[1] = priv::SetX(Columns[1], Row.Y);
			Columns[2] = priv::SetX(Columns[2], Row.Z);
			Columns[3] = priv::SetX(Columns[3], Row.W);
		} break;
	
		case 1: {
			Columns[0] = priv::SetY(Columns[0], Row.X);
			Columns[1] = priv::SetY(Columns[1], Row.Y);
			Columns[2] = priv::SetY(Columns[2], Row.Z);
			Columns[3] = priv::SetY(Columns[3], Row.W);
		} break;
	
		case 2: {
			Columns[0] = priv::SetZ(Columns[0], Row.X);
			Columns[1] = priv::SetZ(Columns[1], Row.Y);
			Columns[2] = priv::SetZ(Columns[2], Row.Z);
			Columns[3] = priv::SetZ(Columns[3], Row.W);
		} break;
	
		case 3: {
			Columns[0] = priv::SetW(Columns[0], Row.X);
			Columns[1] = priv::SetW(Columns[1], Row.Y);
			Columns[2] = priv::SetW(Columns[2], Row.Z);
			Columns[3] = priv::SetW(Columns[3], Row.W);
		} break;
	
		default: {
			FM_ERROR(); // Index has to be in range from 0 to 3
		}
	}	
}

} // !namespace fm

#endif // FM_IMPLEMENTATION

#ifdef _MSC_VER
	#pragma warning(pop)
#endif

#endif // FM_IMPLEMENTATION_ALREADY_DEFINED

