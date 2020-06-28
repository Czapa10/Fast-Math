/*
FAST MATH
C++ single header math libary
https://github.com/Czapa10/Fast-Math

Written by Grzegorz "Czapa" Bednorz

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

static const float Pi = 3.14159265359f;
static const double Pi64 = 3.14159265358979323846;

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
	v2_base(t XY) :X(XY), Y(XY) {}
	v2_base(const t* Mem) :X(Mem[0]), Y(Mem[1]) {}
	v2_base() = default;

	template<class u>
	v2_base(v2_base<u> V) :X(static_cast<t>(V.X)), Y(static_cast<t>(V.Y)) {}

	FM_INL t& operator[](uint32_t Index); 
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

union v3
{
	struct {
		float X, Y, Z;
	};
	struct {
		float U, V, W;
	};
	struct {
		float R, G, B;
	};
	struct {
		v2 XY;
		float Placeholder1_;
	};
	struct {
		float Placeholder2_;
		v2 YZ;
	};
	struct {
		v2 UV;
		float Placeholder3_;
	};
	struct {
		float Placeholder4_;
		v2 VW;
	};
	struct {
		v2 RG;
		float Placeholder5_;
	};
	struct {
		float Placeholder6_;
		v2 GB;
	};
	float Elements[3];

	FM_INL float& operator[](uint32_t Index); 

	FM_INL v3 ZXY(); 
};

union v4
{
	struct 
	{
		union 
		{
			v3 XYZ;
			struct { float X, Y, Z; };
		};
		float W;
	};

	struct
	{
		union 
		{
			v3 RGB;
			struct { float R, G, B; };
		};
		float A;
	};

	struct {
		v2 XY;
		float Placeholder1_;
		float Placeholder2_;
	};

	struct {
		float Placeholder3_;
		v2 YZ;
		float Placeholder4_;
	};

	struct {
		float Placeholder5_;
		float Placeholder6_;
		v2 ZW;
	};

	float Elements[4];

	FM_INL float& operator[](uint32_t Index); 

	FM_INL v3 ZXY(); 
};

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

struct alignas(16) mat4
{
	__m128 Columns[4];

	FM_INL v4 FM_CALL GetColumnV4(uint32_t Index);
	FM_INL vec4 FM_CALL GetColumnVec4(uint32_t Index); 
	FM_INL void FM_CALL SetColumn(uint32_t Index, v4 Col);
	FM_INL void FM_CALL SetColumn(uint32_t Index, vec4 Col);
	FM_INL void FM_CALL SetColumn(uint32_t Index, float X, float Y, float Z, float W);
	FM_INL void FM_CALL SwapColumns(uint32_t Col1Index, uint32_t Col2Index); 

	v4 FM_CALL GetRowV4(uint32_t Index);
	vec4 FM_CALL GetRowVec4(uint32_t Index);
	void FM_CALL SetRow(uint32_t Index, v4 Row);
	void FM_CALL SetRow(uint32_t Index, vec4 Row);
	FM_INL void FM_CALL SetRow(uint32_t Index, float X, float Y, float Z, float W);
	FM_INL void FM_CALL SwapRows(uint32_t Row1Index, uint32_t Row2Index); 

	FM_INL v4 FM_CALL GetMainDiagonalV4();
	FM_INL vec4 FM_CALL GetMainDiagonalVec4();
	FM_INL void FM_CALL SetMainDiagonal(float X, float Y, float Z, float W); 
	FM_INL void FM_CALL SetMainDiagonal(v4);
	FM_INL void FM_CALL SetMainDiagonal(vec4);

	FM_INL float& operator[](uint32_t Index); 
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
template<class t>
FM_SINL t Min(t A, t B) {
	return A < B ? A : B; 
}
template<class t>
FM_SINL t Max(t A, t B) {
	return A > B ? A : B;
}
template<class t>
FM_SINL t Abs(t A) {
	return A < 0 ? -A : A;
}
template<class t>
FM_SINL void Abs(t* A) {
	*A = *A < 0 ? -(*A) : *A;
}
template<class t>
FM_SINL t Square(t A) {
	return A * A;
}
template<class t>
FM_SINL void Square(t* A) {
	*A = (*A) * (*A);
}
FM_SINL float RadiansToDegrees(float Radians) {
	return Radians * 180.f / Pi;
}
FM_SINL double RadiansToDegrees(double Radians) {
	return Radians * 180.f / Pi64;
}
FM_SINL float DegreesToRadians(float Degrees) {
	return Degrees * Pi / 180.f;
}
FM_SINL double DegreesToRadians(double Degrees) {
	return Degrees * Pi64 / 180.f;
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
template<class t>
FM_INL t& v2_base<t>::operator[](uint32_t Index) {
	FM_ASSERT(Index == 0 || Index == 1);
	return Elements[Index];
}
template<class t>
FM_SINL t* Ptr(v2_base<t>& V) {
	return &V.X; 
}
template<class t> 
FM_SINL t* PtrY(v2_base<t>& V) {
	return &V.Y; 
}
template<class t>
FM_SINL void Store(t* Mem, v2_base<t> V) {
	Mem[0] = V.X;
	Mem[1] = V.Y;
}
template<class t>
FM_SINL v2_base<t> operator+(v2_base<t> A, v2_base<t> B) {
	v2_base<t> R;
	R.X = A.X + B.X;
	R.Y = A.Y + B.Y;
	return R;
}
template<class t>
FM_SINL v2_base<t> operator-(v2_base<t> A, v2_base<t> B) {
	v2_base<t> R;
	R.X = A.X - B.X;
	R.Y = A.Y - B.Y;
	return R;
}
template<class t>
FM_SINL v2_base<t>& operator+=(v2_base<t>& A, v2_base<t> B) {
	A.X += B.X;
	A.Y += B.Y;
	return A;
}
template<class t>
FM_SINL v2_base<t>& operator-=(v2_base<t>& A, v2_base<t> B) {
	A.X -= B.X;
	A.Y -= B.Y;
	return A;
}
template<class t>
FM_SINL v2_base<t> HadamardMul(v2_base<t> A, v2_base<t> B) {
	v2_base<t> R;
	R.X = A.X * B.X;
	R.Y = A.Y * B.Y;
	return R;
} 
template<class t>
FM_SINL v2_base<t> HadamardDiv(v2_base<t> A, v2_base<t> B) {
	v2_base<t> R;
	R.X = A.X / B.X;
	R.Y = A.Y / B.Y;
	return R;
}
template<class t>
FM_SINL v2_base<t> operator*(v2_base<t> V, t Scalar) {
	V.X *= Scalar;
	V.Y *= Scalar;
	return V;
}
template<class t>
FM_SINL v2_base<t> operator*(t Scalar, v2_base<t> V) {
	return V * Scalar;
}
template<class t>
FM_SINL v2_base<t>& operator*=(v2_base<t>& V, t Scalar) {
	V = V * Scalar;	
	return V;
}
template<class t>
FM_SINL v2_base<t> operator/(v2_base<t> V, t Scalar) {
	V.X /= Scalar;
	V.Y /= Scalar;
	return V;
}
template<class t>
FM_SINL v2_base<t>& operator/=(v2_base<t>& V, t Scalar) {
	V = V / Scalar;
	return V;
} 
template<class t>
FM_SINL v2_base<t> operator-(v2_base<t> V) {
	V.X = -V.X;
	V.Y = -V.Y;
	return V;
} 
template<class t>
FM_SINL t Dot(v2_base<t> A, v2_base<t> B) {
	return A.X * B.X + A.Y * B.Y;
} 
template<class t>
FM_SINL v2_base<t> Min(v2_base<t> A, v2_base<t> B) {
	v2_base<t> R;
	R.X = Min(A.X, B.X);	
	R.Y = Min(A.Y, B.Y);	
	return R;
}
template<class t>
FM_SINL v2_base<t> Max(v2_base<t> A, v2_base<t> B) {
	v2_base<t> R;
	R.X = Max(A.X, B.X);
	R.Y = Max(A.Y, B.Y);
	return R;
} 
template<class t>
FM_SINL v2_base<t> Abs(v2_base<t> V) {
	v2_base<t> R;
	R.X = Abs(V.X);
	R.Y = Abs(V.Y);
	return R;
} 
template<class t>
FM_SINL t SumOfElements(v2_base<t> V) {
	return V.X + V.Y;
}
template<class t>
FM_SINL t Length(v2_base<t> V) {
	return static_cast<t>(sqrt(V.X * V.X + V.Y * V.Y));
}
template<class t>
FM_SINL t LengthSquared(v2_base<t> V) {
	return V.X * V.X + V.Y * V.Y;
} 
template<class t>
FM_SINL v2_base<t> Normalize(v2_base<t> V) {
	return V / Length(V);
}
template<class t>
FM_SINL void Normalize(v2_base<t>* V) {
	*V = *V / Length(*V);
}
template<class t>
FM_SINL v2_base<t> Clamp(v2_base<t> V, v2_base<t> MinV, v2_base<t> MaxV) {
	return Min(Max(V, MinV), MaxV);
}
template<class t>
FM_SINL v2_base<t> Lerp(v2_base<t> A, v2_base<t> B, float T) {
	v2 fA = static_cast<v2>(A);
	v2 fB = static_cast<v2>(B);
	return static_cast<v2_base<t>>(fA + (fB - fA)*T);
}
template<class t>
FM_SINL bool operator==(v2_base<t> A, v2_base<t> B) {
	return A.X == B.X && A.Y == B.Y;
}
template<class t>
FM_SINL bool operator!=(v2_base<t> A, v2_base<t> B) {
	return A.X != B.X || A.X != B.X;
}

//////////////////
// v3 functions //
//////////////////
FM_SINL v3 V3FromMemory(float* Mem) {
	v3 R;
	R.X = Mem[0];
	R.Y = Mem[1];
	R.Z = Mem[2];
	return R;
}
FM_SINL v3 V3(float X, float Y, float Z) {
	v3 R;
	R.X = X;
	R.Y = Y;
	R.Z = Z;
	return R;
}
FM_SINL v3 V3(float XYZ) {
	return V3(XYZ, XYZ, XYZ);
}
FM_SINL v3 V3() {
	return {};
}
FM_INL v3 v3::ZXY() { 
	return V3(Z, X, Y); 
}
FM_INL float& v3::operator[](uint32_t Index) {
	FM_ASSERT(Index >= 0 && Index <= 2);
	return Elements[Index];
}
FM_SINL void Store(float* Mem, v3 V) {
	Mem[0] = V.X;
	Mem[1] = V.Y;
	Mem[2] = V.Z;
}
FM_SINL float* Ptr(v3& V) {
	return &V.X; 
}
FM_SINL float* PtrY(v3& V) {
	return &V.Y; 
}
FM_SINL float* PtrZ(v3& V) {
	return &V.Z; 
}
FM_SINL v3 operator+(v3 A, v3 B) {
	v3 R;
	R.X = A.X + B.X;
	R.Y = A.Y + B.Y;
	R.Z = A.Z + B.Z;
	return R;
}
FM_SINL v3 operator-(v3 A, v3 B) {
	v3 R;
	R.X = A.X - B.X;
	R.Y = A.Y - B.Y;
	R.Z = A.Z - B.Z;
	return R;
}
FM_SINL v3& operator+=(v3& A, v3 B) {
	A = A + B;
	return A;
}
FM_SINL v3& operator-=(v3& A, v3 B) {
	A = A - B;
	return A;
}
FM_SINL v3 HadamardMul(v3 A, v3 B) {
	v3 R;
	R.X = A.X * B.X;
	R.Y = A.Y * B.Y;
	R.Z = A.Z * B.Z;
	return R;
}
FM_SINL v3 HadamardDiv(v3 A, v3 B) {
	v3 R;
	R.X = A.X / B.X;
	R.Y = A.Y / B.Y;
	R.Z = A.Z / B.Z;
	return R;
}
FM_SINL v3 operator*(v3 V, float Scalar) {
	V.X *= Scalar;
	V.Y *= Scalar;
	V.Z *= Scalar;
	return V;
}
FM_SINL v3 operator*(float Scalar, v3 V) {
	return V * Scalar;
}
FM_SINL v3& operator*=(v3& V, float Scalar) {
	V = V * Scalar;
	return V;
}
FM_SINL v3 operator/(v3 V, float Scalar) {
	V.X /= Scalar;
	V.Y /= Scalar;
	V.Z /= Scalar;
	return V;
}
FM_SINL v3& operator/=(v3& V, float Scalar) {
	V = V / Scalar;
	return V;
}
FM_SINL v3 operator-(v3 V) {
	V.X = -V.X;
	V.Y = -V.Y;
	V.Z = -V.Z;
	return V;
}
FM_SINL v3 Cross(v3 A, v3 B) {
	return v3(HadamardMul(A.ZXY(), B) - HadamardMul(A, B.ZXY())).ZXY();
}
FM_SINL float Dot(v3 A, v3 B) {
	return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
}
FM_SINL v3 Min(v3 A, v3 B) {
	v3 R;
	R.X = Min(A.X, B.X);
	R.Y = Min(A.Y, B.Y);
	R.Z = Min(A.Z, B.Z);
	return R;
}
FM_SINL v3 Max(v3 A, v3 B) {
	v3 R;
	R.X = Max(A.X, B.X);
	R.Y = Max(A.Y, B.Y);
	R.Z = Max(A.Z, B.Z);
	return R;
} 
FM_SINL v3 Abs(v3 V) {
	V.X = Abs(V.X);
	V.Y = Abs(V.Y);
	V.Z = Abs(V.Z);
	return V;
}
FM_SINL float SumOfElements(v3 V) {
	return V.X + V.Y + V.Z;
}
FM_SINL float Length(v3 V) {
	return sqrtf(V.X * V.X + V.Y * V.Y + V.Z * V.Z);
}
FM_SINL float LengthSquared(v3 V) {
	return V.X * V.X + V.Y * V.Y + V.Z * V.Z;
} 
FM_SINL v3 Normalize(v3 V) {
	return V / Length(V);
}
FM_SINL void Normalize(v3* V) {
	*V = *V / Length(*V);
}
FM_SINL v3 Clamp(v3 V, v3 MinV, v3 MaxV) {
	return Min(Max(V, MinV), MaxV);	
} 
FM_SINL v3 Lerp(v3 A, v3 B, float T) {
	return A + (B - A) * T;
}
FM_SINL bool operator==(v3 A, v3 B) {
	return A.X == B.X && A.Y == B.Y && A.Z == B.Z;
}
FM_SINL bool operator!=(v3 A, v3 B) {
	return !(A == B);
}

//////////////////
// v4 functions //
//////////////////
FM_SINL v4 V4FromMemory(float* Mem) {
	v4 R;
	R[0] = Mem[0];
	R[1] = Mem[1];
	R[2] = Mem[2];
	R[3] = Mem[3];
	return R;
}
FM_SINL v4 V4(float X, float Y, float Z, float W) {
	v4 R;
	R.X = X;
	R.Y = Y;
	R.Z = Z;
	R.W = W;
	return R;
}
FM_SINL v4 V4(v3 XYZ, float W) {
	v4 R;
	R.X = XYZ.X;
	R.Y = XYZ.Y;
	R.Z = XYZ.Z;
	R.W = W;
	return R;
}
FM_SINL v4 V4(float XYZW) {
	v4 R;
	R.X = XYZW;
	R.Y = XYZW;
	R.Z = XYZW;
	R.W = XYZW;
	return R;
}
FM_SINL v4 V4() {
	return {};
}
float& v4::operator[](uint32_t Index) {
	FM_ASSERT(Index >= 0 && Index <= 3);
	return Elements[Index];
}
FM_SINL float* Ptr(v4& V) {
	return &V.X; 
}
FM_SINL float* PtrY(v4& V) {
	return &V.Y; 
}
FM_SINL float* PtrZ(v4& V) {
	return &V.Z; 
}
FM_SINL float* PtrW(v4& V) {
	return &V.W; 
}
FM_SINL void Store(float* Mem, v4 V) {
	Mem[0] = V.X;
	Mem[1] = V.Y;
	Mem[2] = V.Z;
	Mem[3] = V.W;
}
FM_SINL v4 operator+(v4 A, v4 B) {
	v4 R;
	R.X = A.X + B.X;
	R.Y = A.Y + B.Y;
	R.Z = A.Z + B.Z;
	R.W = A.W + B.W;
	return R;
} 
FM_SINL v4 operator-(v4 A, v4 B) {
	v4 R;
	R.X = A.X - B.X;
	R.Y = A.Y - B.Y;
	R.Z = A.Z - B.Z;
	R.W = A.W - B.W;
	return R;
}
FM_SINL v4& operator+=(v4& A, v4 B) {
	A = A + B;
	return A;
}
FM_SINL v4& operator-=(v4& A, v4 B) {
	A = A - B;
	return A;
}
FM_SINL v4 HadamardMul(v4 A, v4 B) {
	v4 R;
	R.X = A.X * B.X;
	R.Y = A.Y * B.Y;
	R.Z = A.Z * B.Z;
	R.W = A.W * B.W;
	return R;
}
FM_SINL v4 HadamardDiv(v4 A, v4 B) {
	v4 R;
	R.X = A.X / B.X;
	R.Y = A.Y / B.Y;
	R.Z = A.Z / B.Z;
	R.W = A.W / B.W;
	return R;
}
FM_SINL v4 operator*(v4 V, float  Scalar) {
	V.X *= Scalar;
	V.Y *= Scalar;
	V.Z *= Scalar;
	V.W *= Scalar;
	return V;
}
FM_SINL v4 operator*(float Scalar, v4 V) {
	return V * Scalar;
}
FM_SINL v4& operator*=(v4& V, float Scalar) {
	V = V * Scalar;
	return V;
}
FM_SINL v4 operator/(v4 V, float Scalar) {
	V.X /= Scalar;
	V.Y /= Scalar;
	V.Z /= Scalar;
	V.W /= Scalar;
	return V;
}
FM_SINL v4& operator/=(v4& V, float Scalar) {
	V = V / Scalar;
	return V;
}
FM_SINL v4 operator-(v4 V) {
	V.X = -V.X;
	V.Y = -V.Y;
	V.Z = -V.Z;
	V.W = -V.W;
	return V;
} 
FM_SINL float Dot(v4 A, v4 B) {
	return A.X * B.X + A.Y * B.Y + A.Z * B.Z + A.W * B.W;
} 
FM_SINL v4 Min(v4 A, v4 B) {
	v4 R;
	R.X = Min(A.X, B.X);
	R.Y = Min(A.Y, B.Y);
	R.Z = Min(A.Z, B.Z);
	R.W = Min(A.W, B.W);
	return R;
} 
FM_SINL v4 Max(v4 A, v4 B) {
	v4 R;
	R.X = Max(A.X, B.X);
	R.Y = Max(A.Y, B.Y);
	R.Z = Max(A.Z, B.Z);
	R.W = Max(A.W, B.W);
	return R;
}
FM_SINL v4 Abs(v4 V) {
	V.X = Abs(V.X);
	V.Y = Abs(V.Y);
	V.Z = Abs(V.Z);
	V.W = Abs(V.W);
	return V;
}
FM_SINL float SumOfElements(v4 V) {
	return V.X + V.Y + V.Z + V.W;
}
FM_SINL float Length(v4 V) {
	return sqrtf(Dot(V, V));
}
FM_SINL float LengthSquared(v4 V) {
	return Dot(V, V);
} 
FM_SINL v4 Normalize(v4 V) {
	return V / Length(V);
}
FM_SINL void Normalize(v4* V) {
	*V = *V / Length(*V);
}
FM_SINL v4 Clamp(v4 V, v4 MinV, v4 MaxV) {
	return Min(Max(V, MinV), MaxV);
} 
FM_SINL v4 Lerp(v4 A, v4 B, float T) {
	return A + (B - A) * T;
}
FM_SINL bool operator==(v4 A, v4 B) {
	return A.X == B.X && A.Y == B.Y && A.Z == B.Z && A.W == B.W;
} 
FM_SINL bool operator!=(v4 A, v4 B) {
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
FM_SINL v2 FM_CALL CastToV2(vec2 V) {
	v2 R;
	R.X = V.X();
	R.Y = V.Y();
	return R;
}
FM_SINL v3 FM_CALL CastToV3(vec3 V) {
	v3 R;
	R.X = V.X();
	R.Y = V.Y();
	R.Z = V.Z();
	return R;
}
FM_SINL v4 FM_CALL CastToV4(vec4 V) {
	v4 R;
	Store(R.Elements, V);
	return R;
}
FM_SINL vec2 FM_CALL CastToVec2(v2 V) {
	return Vec2FromMemory(V.Elements);
}
FM_SINL vec3 FM_CALL CastToVec3(v3 V) {
	return Vec3FromMemory(V.Elements);
}
FM_SINL vec4 FM_CALL CastToVec4(v4 V) {
	return Vec4FromMemory(V.Elements);
}

///////////////////////////////////////////
// headers of not inlined mat4 functions //
///////////////////////////////////////////
mat4 FM_CALL operator*(mat4 A, mat4 B); 
mat4 Mat4Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far);
mat4 Mat4Perspective(float FOV, float AspectRatio, float near, float Far);
mat4 Mat4LookAt(vec3 Eye, vec3 At, vec3 Up = Vec3(0.f, 1.f, 0.f));
mat4 Mat4LookAt(v3 Eye, v3 At, v3 Up = V3(0.f, 1.f, 0.f));

////////////////////
// mat4 functions //
////////////////////
FM_INL float& mat4::operator[](uint32_t Index) {
	FM_ASSERT(Index >= 0 && Index <= 15);
	return *((float*)(Columns) + Index);
}
FM_INL vec4 FM_CALL mat4::GetColumnVec4(uint32_t Index) {
	FM_ASSERT(Index >= 0 && Index <= 3);
	return Vec4(Columns[Index]);
}
FM_INL v4 FM_CALL mat4::GetColumnV4(uint32_t Index) {
	return CastToV4(GetColumnVec4(Index));
}
FM_INL void FM_CALL mat4::SetColumn(uint32_t Index, vec4 Col) {
	FM_ASSERT(Index >= 0 && Index <= 3);
	Columns[Index] = Col.M;
}
FM_INL void FM_CALL mat4::SetColumn(uint32_t Index, v4 Col) {
	SetColumn(Index, CastToVec4(Col));
}
FM_INL void FM_CALL mat4::SetColumn(uint32_t Index, float X, float Y, float Z, float W) {
	FM_ASSERT(Index >= 0 && Index <= 3);
	Columns[Index] = _mm_set_ps(W, Z, Y, X);
}
FM_INL void FM_CALL mat4::SwapColumns(uint32_t Col1Index, uint32_t Col2Index) {
	FM_ASSERT(Col1Index >= 0 && Col1Index <= 3 && Col1Index >= 0 && Col1Index <= 3);
	__m128 Temp = Columns[Col1Index];
	Columns[Col1Index] = Columns[Col2Index];
	Columns[Col2Index] = Temp;
}
FM_INL vec4 FM_CALL mat4::GetRowVec4(uint32_t Index) {
	return CastToVec4(GetRowV4(Index));
}
FM_INL void FM_CALL mat4::SetRow(uint32_t Index, float X, float Y, float Z, float W) {
	SetRow(Index, V4(X, Y, Z, W));
}
FM_INL void FM_CALL mat4::SetRow(uint32_t Index, vec4 V) {
	SetRow(Index, CastToV4(V));
}
FM_INL void FM_CALL mat4::SwapRows(uint32_t Row1Index, uint32_t Row2Index) {
	FM_ASSERT(Row1Index >= 0 && Row2Index <= 3 && Row1Index >= 0 && Row2Index <= 3);
	v4 Row1 = GetRowV4(Row1Index);
	v4 Row2 = GetRowV4(Row2Index);
	SetRow(Row2Index, Row1);
	SetRow(Row1Index, Row2);
}
FM_INL v4 FM_CALL mat4::GetMainDiagonalV4() {
	v4 R;
	R.X = priv::GetX(Columns[0]);
	R.Y = priv::GetY(Columns[1]);
	R.Z = priv::GetZ(Columns[2]);
	R.W = priv::GetW(Columns[3]);
	return R;
}
FM_INL vec4 FM_CALL mat4::GetMainDiagonalVec4() {
	return CastToVec4(GetMainDiagonalV4());
}
FM_INL void FM_CALL mat4::SetMainDiagonal(float X, float Y, float Z, float W) {
	Columns[0] = priv::SetX(Columns[0], X);
	Columns[1] = priv::SetY(Columns[1], Y);
	Columns[2] = priv::SetZ(Columns[2], Z);
	Columns[3] = priv::SetW(Columns[3], W);
}
FM_INL void FM_CALL mat4::SetMainDiagonal(v4 V) {
	SetMainDiagonal(V.X, V.Y, V.Z, V.W);
}
FM_INL void FM_CALL mat4::SetMainDiagonal(vec4 V) {
	SetMainDiagonal(CastToV4(V));
}
FM_SINL mat4 FM_CALL Mat4FromColumnMajorMemory(float* Mem) {
	mat4 R;
	for(int32_t i = 0; i < 4; ++i)
		R.Columns[i] = _mm_load_ps(Mem + i*4);
	return R;
}
FM_SINL mat4 FM_CALL Mat4FromRowMajorMemory(float* Mem) {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Mem[0], Mem[4], Mem[8], Mem[12]);
	R.Columns[1] = _mm_setr_ps(Mem[1], Mem[5], Mem[9], Mem[13]);
	R.Columns[2] = _mm_setr_ps(Mem[2], Mem[6], Mem[10], Mem[14]);
	R.Columns[3] = _mm_setr_ps(Mem[3], Mem[7], Mem[11], Mem[15]);
	return R;
}
FM_SINL mat4 FM_CALL Mat4() {
	mat4 R;
	R.Columns[0] = _mm_setzero_ps();
	R.Columns[1] = _mm_setzero_ps();
	R.Columns[2] = _mm_setzero_ps();
	R.Columns[3] = _mm_setzero_ps();
	return R;
}
FM_SINL mat4 FM_CALL Mat4Diagonal(float Diag) {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Diag, 0.f, 0.f, 0.f);
	R.Columns[1] = _mm_setr_ps(0.f, Diag, 0.f, 0.f);
	R.Columns[2] = _mm_setr_ps(0.f, 0.f, Diag, 0.f);
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, Diag);
	return R;
}
FM_SINL mat4 FM_CALL Mat4Diagonal(float DiagX, float DiagY, float DiagZ, float DiagW) {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(DiagX, 0.f, 0.f, 0.f);
	R.Columns[1] = _mm_setr_ps(0.f, DiagY, 0.f, 0.f);
	R.Columns[2] = _mm_setr_ps(0.f, 0.f, DiagZ, 0.f);
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, DiagW);
	return R;
}
FM_SINL mat4 FM_CALL Mat4Diagonal(v4 Diag) {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Diag.X, 0.f, 0.f, 0.f);
	R.Columns[1] = _mm_setr_ps(0.f, Diag.Y, 0.f, 0.f);
	R.Columns[2] = _mm_setr_ps(0.f, 0.f, Diag.Z, 0.f);
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, Diag.W);
	return R;
}
FM_SINL mat4 FM_CALL Mat4Diagonal(vec4 Diag) {
	return Mat4Diagonal(CastToV4(Diag));
}
FM_SINL mat4 FM_CALL Mat4Identity() {
	return Mat4Diagonal(1.f);
}
FM_SINL mat4 FM_CALL Mat4FromColumns(vec4 Col1, vec4 Col2, vec4 Col3, vec4 Col4) {
	mat4 R;
	R.Columns[0] = Col1.M;
	R.Columns[1] = Col2.M;
	R.Columns[2] = Col3.M;
	R.Columns[3] = Col4.M;
	return R;
}
FM_SINL mat4 FM_CALL Mat4FromColumns(v4 Col1, v4 Col2, v4 Col3, v4 Col4) {
	return Mat4FromColumns(CastToVec4(Col1), CastToVec4(Col2), CastToVec4(Col3), CastToVec4(Col4));
}
FM_SINL mat4 FM_CALL Mat4FromColumns(vec3 Col1, vec3 Col2, vec3 Col3, vec3 Col4) {
	mat4 R;
	R.Columns[0] = Col1.M;
	R.Columns[1] = Col2.M;
	R.Columns[2] = Col3.M;
	R.Columns[3] = Col4.M;
	R.SetRow(3, 0.f, 0.f, 0.f, 1.f);
	return R;
}
FM_SINL mat4 FM_CALL Mat4FromColumns(v3 Col1, v3 Col2, v3 Col3, v3 Col4) {
	return Mat4FromColumns(CastToVec3(Col1), CastToVec3(Col2), CastToVec3(Col3), CastToVec3(Col4));
}
FM_SINL mat4 FM_CALL Mat4FromColumns(
	float E11, float E21, float E31, float E41,
    float E12, float E22, float E32, float E42,
    float E13, float E23, float E33, float E43,
    float E14, float E24, float E34, float E44) 
{
	mat4 R;
	R.Columns[0] = _mm_setr_ps(E11, E21, E31, E41);
	R.Columns[1] = _mm_setr_ps(E12, E22, E32, E42);
	R.Columns[2] = _mm_setr_ps(E13, E23, E33, E43);
	R.Columns[3] = _mm_setr_ps(E14, E24, E34, E44);
	return R;
}
FM_SINL mat4 FM_CALL Mat4FromRows(vec4 Row1, vec4 Row2, vec4 Row3, vec4 Row4) {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Row1.X(), Row2.X(), Row3.X(), Row4.X());
	R.Columns[1] = _mm_setr_ps(Row1.Y(), Row2.Y(), Row3.Y(), Row4.Y());
	R.Columns[2] = _mm_setr_ps(Row1.Z(), Row2.Z(), Row3.Z(), Row4.Z());
	R.Columns[3] = _mm_setr_ps(Row1.W(), Row2.W(), Row3.W(), Row4.W());
	return R;
}
FM_SINL mat4 FM_CALL Mat4FromRows(v4 Row1, v4 Row2, v4 Row3, v4 Row4) {
	return Mat4FromRows(CastToVec4(Row1), CastToVec4(Row2), CastToVec4(Row3), CastToVec4(Row4));
}
FM_SINL mat4 FM_CALL Mat4FromRows(
	float E11, float E12, float E13, float E14,
    float E21, float E22, float E23, float E24,
    float E31, float E32, float E33, float E34,
    float E41, float E42, float E43, float E44)
{
	mat4 R;
	R.Columns[0] = _mm_setr_ps(E11, E21, E31, E41);
	R.Columns[1] = _mm_setr_ps(E12, E22, E32, E42);
	R.Columns[2] = _mm_setr_ps(E13, E23, E33, E43);
	R.Columns[3] = _mm_setr_ps(E14, E24, E34, E44);
	return R;
}
FM_SINL mat4 FM_CALL Mat4FromRows(vec3 Row1, vec3 Row2, vec3 Row3, vec3 Row4) {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Row1.X(), Row2.X(), Row3.X(), Row4.X());
	R.Columns[1] = _mm_setr_ps(Row1.Y(), Row2.Y(), Row3.Y(), Row4.Y());
	R.Columns[2] = _mm_setr_ps(Row1.Z(), Row2.Z(), Row3.Z(), Row4.Z());
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, 1.f);
	return R;
}
FM_SINL mat4 FM_CALL Mat4FromRows(v3 Row1, v3 Row2, v3 Row3, v3 Row4) {
	return Mat4FromRows(CastToVec3(Row1), CastToVec3(Row2), CastToVec3(Row3), CastToVec3(Row4));
}
FM_SINL float* Ptr(const mat4& V) {
	return (float*)(&V);
}
FM_SINL void FM_CALL Store(float* Mem, mat4 Mat) {
	for(int32_t Col = 0; Col < 4; ++Col)
		_mm_storeu_ps(Mem + Col*4, Mat.Columns[Col]);
}
FM_SINL void FM_CALL Store16ByteAligned(float* Mem, mat4 Mat) {
	FM_ASSERT(Mem % 16 == 0);
	for(int32_t Col = 0; Col < 4; ++Col)
		_mm_store_ps(Mem + Col*4, Mat.Columns[Col]);
}
FM_SINL mat4 FM_CALL operator+(mat4 A, mat4 B) {
	for(int32_t Col = 0; Col < 4; ++Col)
		A.Columns[Col] = _mm_add_ps(A.Columns[Col], B.Columns[Col]);
	return A;
}
FM_SINL mat4 FM_CALL operator-(mat4 A, mat4 B) {
	for(int32_t Col = 0; Col < 4; ++Col)
		A.Columns[Col] = _mm_sub_ps(A.Columns[Col], B.Columns[Col]);
	return A;
}
FM_SINL vec4 FM_CALL operator*(mat4 M, vec4 V) {
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
FM_SINL v4 FM_CALL operator*(mat4 M, v4 V) {
	// TODO: Try to implement the logic in v4 function and make vec4 version call it. 
	//       Maybe just make separate implementations. Profile it!
	return CastToV4(M * CastToVec4(V));
}
FM_SINL mat4 FM_CALL operator*(mat4 M, float Scalar) {
	__m128 ScalarM = _mm_set1_ps(Scalar);
	for(uint32_t Col = 0; Col < 4; ++Col)
		M.Columns[Col] = _mm_mul_ps(M.Columns[Col], ScalarM);
	return M;
}
FM_SINL mat4 FM_CALL HadamardMul(mat4 A, mat4 B) {
	for(uint32_t Col = 0; Col < 4; ++Col)
		A.Columns[Col] = _mm_mul_ps(A.Columns[Col], B.Columns[Col]);
	return A;
}
FM_SINL mat4 FM_CALL HadamardDiv(mat4 A, mat4 B) {
	for(uint32_t Col = 0; Col < 4; ++Col)
		A.Columns[Col] = _mm_div_ps(A.Columns[Col], B.Columns[Col]);
	return A;
}
FM_SINL mat4 FM_CALL operator*(float Scalar, mat4 M) {
	return M * Scalar;
}
FM_SINL mat4& FM_CALL operator*=(mat4& M, float Scalar) {
	M = M * Scalar;	
	return M;
}
FM_SINL mat4 FM_CALL operator/(mat4 M, float Scalar) {
	__m128 ScalarM = _mm_set1_ps(Scalar);
	for(uint32_t Col = 0; Col < 4; ++Col)
		M.Columns[Col] = _mm_div_ps(M.Columns[Col], ScalarM);
	return M;
}
FM_SINL mat4& FM_CALL operator/=(mat4& M, float Scalar) {
	M = M / Scalar;
	return M;
}
FM_SINL bool FM_CALL operator==(mat4 A, mat4 B) {
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
FM_SINL bool FM_CALL operator!=(mat4 A, mat4 B) {
	return !(A == B);
}
FM_SINL void FM_CALL Transpose(mat4* M) {
	_MM_TRANSPOSE4_PS(M->Columns[0], M->Columns[1], M->Columns[2], M->Columns[3]);
}
FM_SINL mat4 FM_CALL Transpose(mat4 M) {
	_MM_TRANSPOSE4_PS(M.Columns[0], M.Columns[1], M.Columns[2], M.Columns[3]);
	return M;
}
FM_SINL mat4 FM_CALL Mat4Translation(float X, float Y, float Z) {
	return Mat4FromRows(
		1.f, 0.f, 0.f, X,
		0.f, 1.f, 0.f, Y,
		0.f, 0.f, 1.f, Z,
		0.f, 0.f, 0.f, 1.f);
}
FM_SINL mat4 FM_CALL Mat4Translation(v3 Translation) {
	return Mat4FromRows(
		1.f, 0.f, 0.f, Translation.X,
		0.f, 1.f, 0.f, Translation.Y,
		0.f, 0.f, 1.f, Translation.Z,
		0.f, 0.f, 0.f, 1.f);
}
FM_SINL mat4 FM_CALL Mat4Translation(vec3 Translation) {
	return Mat4Translation(CastToV3(Translation));
}
FM_SINL mat4 FM_CALL Mat4Translation(float Translation) {
	return Mat4FromRows(
		1.f, 0.f, 0.f, Translation,
		0.f, 1.f, 0.f, Translation,
		0.f, 0.f, 1.f, Translation,
		0.f, 0.f, 0.f, 1.f);
}
FM_SINL void FM_CALL Translate(mat4* M, float X, float Y, float Z) {
	M->Columns[3] = _mm_add_ps(M->Columns[3], _mm_set_ps(0.f, Z, Y, X));
}
FM_SINL void FM_CALL Translate(mat4* M, vec3 Trans) {
	M->Columns[3] = _mm_add_ps(M->Columns[3], Trans.M);
}
FM_SINL void FM_CALL Translate(mat4* M, v3 Trans) {
	Translate(M, CastToVec3(Trans));
}
FM_SINL void FM_CALL Translate(mat4* M, float Trans) {
	M->Columns[3] = _mm_add_ps(M->Columns[3], _mm_set_ps(0.f, Trans, Trans, Trans));
}
FM_SINL mat4 FM_CALL Mat4Scale(float Scalar) {
	return Mat4Diagonal(Scalar, Scalar, Scalar, 1.f);
} 
FM_SINL mat4 FM_CALL Mat4Scale(float ScalarX, float ScalarY, float ScalarZ) {
	return Mat4Diagonal(ScalarX, ScalarY, ScalarZ, 1.f);
} 
FM_SINL mat4 FM_CALL Mat4Scale(v3 Scalar) {
	return Mat4Diagonal(Scalar.X, Scalar.Y, Scalar.Z, 1.f); 
}
FM_SINL mat4 FM_CALL Mat4Scale(vec3 Scalar) {
	return Mat4Diagonal(Scalar.X(), Scalar.Y(), Scalar.Z(), 1.f); 
}
FM_SINL void FM_CALL Scale(mat4* M, float X, float Y, float Z) {
	// TODO: Try to Cast to vec and v back and forth and Profile!
	v4 MainDiag = M->GetMainDiagonalV4();
	v4 ScalarVec = V4(X, Y, Z, 1.f);
	MainDiag = HadamardMul(MainDiag, ScalarVec);
	M->SetMainDiagonal(MainDiag);
}
FM_SINL void FM_CALL Scale(mat4* M, float Scalar) {
	Scale(M, Scalar, Scalar, Scalar);
}
FM_SINL void FM_CALL Scale(mat4* M, vec3 Scalar) {
	// TODO: Try to Cast to vec and v back and forth and Profile!
	vec4 MainDiag = M->GetMainDiagonalVec4();
	MainDiag.M = _mm_mul_ps(MainDiag.M, Scalar.M);
	MainDiag.M = priv::SetW(MainDiag.M, 1.f);
	M->SetMainDiagonal(MainDiag);
}
FM_SINL void FM_CALL Scale(mat4* M, v3 Scalar) {
	return Scale(M, CastToVec3(Scalar));
}
FM_SINL mat4 FM_CALL Mat4RotationRadians(float Radians, float AxisX, float AxisY, float AxisZ) {
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
FM_SINL mat4 FM_CALL Mat4RotationRadians(float Radians, v3 Axis) {
	return Mat4RotationRadians(Radians, Axis.X, Axis.Y, Axis.Z);
}
FM_SINL mat4 FM_CALL Mat4RotationRadians(float Radians, vec3 Axis) {
	return Mat4RotationRadians(Radians, Axis.X(), Axis.Y(), Axis.Z());
}
FM_SINL mat4 FM_CALL Mat4RotationAroundXAxisRadians(float R) {
	return Mat4FromRows(
		1.f, 0.f, 0.f, 0.f,
		0.f, cosf(R), -sinf(R), 0.f,
		0.f, sinf(R), cosf(R), 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_SINL mat4 FM_CALL Mat4RotationAroundYAxisRadians(float R) {
	return Mat4FromRows(
		cosf(R), 0.f, sinf(R), 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sinf(R), 0.f, cosf(R), 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_SINL mat4 FM_CALL Mat4RotationAroundZAxisRadians(float R) {
	return Mat4FromRows(
		cosf(R), -sinf(R), 0.f, 0.f,
		sinf(R), cosf(R), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_SINL mat4 FM_CALL Mat4RotationAroundAllAxesRadians(float R) {
	return Mat4RotationRadians(R, 1.f, 1.f, 1.f);
}
FM_SINL void FM_CALL RotateRadians(mat4* M, float Radians, float AxisX, float AxisY, float AxisZ) {
	*M = *M * Mat4RotationRadians(Radians, AxisX, AxisY, AxisZ);
}
FM_SINL void FM_CALL RotateRadians(mat4* M, float Radians, vec3 Axes) {
	*M = *M * Mat4RotationRadians(Radians, Axes);
}
FM_SINL void FM_CALL RotateRadians(mat4* M, float Radians, v3 Axes) {
	*M = *M * Mat4RotationRadians(Radians, Axes);
}
FM_SINL void FM_CALL RotateAroundXAxisRadians(mat4* M, float Radians) {
	*M = *M * Mat4RotationAroundXAxisRadians(Radians);	
}
FM_SINL void FM_CALL RotateAroundYAxisRadians(mat4* M, float Radians) {
	*M = *M * Mat4RotationAroundYAxisRadians(Radians);
}
FM_SINL void FM_CALL RotateAroundZAxisRadians(mat4* M, float Radians) {
	*M = *M * Mat4RotationAroundZAxisRadians(Radians);
}
FM_SINL void FM_CALL RotateAroundAllAxesRadians(mat4* M, float Radians) {
	*M = *M * Mat4RotationAroundAllAxesRadians(Radians);
}
FM_SINL mat4 FM_CALL Mat4RotationDegrees(float Degrees, float AxisX, float AxisY, float AxisZ) {
	return Mat4RotationRadians(DegreesToRadians(Degrees), AxisX, AxisY, AxisZ);
} 
FM_SINL mat4 FM_CALL Mat4RotationDegrees(float Degrees, v3 Axis) {
	return Mat4RotationRadians(DegreesToRadians(Degrees), Axis);
}
FM_SINL mat4 FM_CALL Mat4RotationDegrees(float Degrees, vec3 Axis) {
	return Mat4RotationRadians(DegreesToRadians(Degrees), Axis);
}
FM_SINL mat4 FM_CALL Mat4RotationAroundXAxisDegrees(float Degrees) {
	return Mat4RotationAroundXAxisRadians(DegreesToRadians(Degrees));
}
FM_SINL mat4 FM_CALL Mat4RotationAroundYAxisDegrees(float Degrees) {
	return Mat4RotationAroundYAxisRadians(DegreesToRadians(Degrees));
}
FM_SINL mat4 FM_CALL Mat4RotationAroundZAxisDegrees(float Degrees) {
	return Mat4RotationAroundZAxisRadians(DegreesToRadians(Degrees));
}
FM_SINL mat4 FM_CALL Mat4RotationAroundAllAxesDegrees(float Degrees) {
	return Mat4RotationAroundAllAxesRadians(DegreesToRadians(Degrees));
}
FM_SINL void FM_CALL RotateDegrees(mat4* M, float Degrees, float AxisX, float AxisY, float AxisZ) {
	RotateRadians(M, DegreesToRadians(Degrees), AxisX, AxisY, AxisZ);
} 
FM_SINL void FM_CALL RotateDegrees(mat4* M, float Degrees, v3 Axis) {
	RotateRadians(M, DegreesToRadians(Degrees), Axis);
}
FM_SINL void FM_CALL RotateDegrees(mat4* M, float Degrees, vec3 Axis) {
	RotateRadians(M, DegreesToRadians(Degrees), Axis);
}
FM_SINL void FM_CALL RotateAroundXAxisDegrees(mat4* M, float Degrees) {
	RotateAroundXAxisRadians(M, DegreesToRadians(Degrees));
}
FM_SINL void FM_CALL RotateAroundYAxisDegrees(mat4* M, float Degrees) {
	RotateAroundYAxisRadians(M, DegreesToRadians(Degrees));
}
FM_SINL void FM_CALL RotateAroundZAxisDegrees(mat4* M, float Degrees) {
	RotateAroundZAxisRadians(M, DegreesToRadians(Degrees));
}
FM_SINL void FM_CALL RotateAroundAllAxesDegrees(mat4* M, float Degrees) {
	RotateAroundAllAxesRadians(M, DegreesToRadians(Degrees));
}
FM_SINL mat4 FM_CALL Mat4ShearXAxis(float Y, float Z) {
	return Mat4FromRows(
		1.f, 0.f, 0.f, 0.f,
		Y,   1.f, 0.f, 0.f,
		Z,   0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_SINL mat4 FM_CALL Mat4ShearYAxis(float X, float Z) {
	return Mat4FromRows(
		1.f, X,   0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, Z,   1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_SINL mat4 FM_CALL Mat4ShearZAxis(float X, float Y) {
	return Mat4FromRows(
		1.f, 0.f, X,   0.f,
		0.f, 1.f, Y,   0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_SINL mat4 FM_CALL Mat4Shear(float XY, float XZ, float YX, float YZ, float ZX, float ZY) {
	return Mat4FromRows(
		1.f, YX, ZX, 0.f,
		XY, 1.f, ZY, 0.f,
		XZ, YZ, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_SINL void FM_CALL ShearXAxis(mat4* M, float Y, float Z) {
	*M = *M * Mat4ShearXAxis(Y, Z);
}
FM_SINL void FM_CALL ShearYAxis(mat4* M, float X, float Z) {
	*M = *M * Mat4ShearYAxis(X, Z);
} 
FM_SINL void FM_CALL ShearZAxis(mat4* M, float X, float Y) {
	*M = *M * Mat4ShearZAxis(X, Y);
} 
FM_SINL void FM_CALL Shear(mat4* M, float XY, float XZ, float YX, float YZ, float ZX, float ZY) {
	*M = *M * Mat4Shear(XY, XZ, YX, YZ, ZX, ZY);
}
FM_SINL mat4 FM_CALL Mat4TranslationScaleRotationRadians(v3 Translation, v3 Scale, float Rotation, v3 RotationAxes) {
	mat4 R = Mat4Scale(Scale);
	RotateRadians(&R, Rotation, RotationAxes);
	Translate(&R, Translation);
	return R;
}
FM_SINL mat4 FM_CALL Mat4TranslationScaleRotationRadians(vec3 Translation, vec3 Scale, float Rotation, vec3 RotationAxes) {
	mat4 R = Mat4Scale(Scale);
	RotateRadians(&R, Rotation, RotationAxes);
	Translate(&R, Translation);
	return R;
}
FM_SINL mat4 FM_CALL Mat4TranslationScaleRotationDegrees(v3 Translation, v3 Scale, float Rotation, v3 RotationAxes) {
	return Mat4TranslationScaleRotationRadians(Translation, Scale, DegreesToRadians(Rotation), RotationAxes);
}
FM_SINL mat4 FM_CALL Mat4TranslationScaleRotationDegrees(vec3 Translation, vec3 Scale, float Rotation, vec3 RotationAxes) {
	return Mat4TranslationScaleRotationRadians(Translation, Scale, DegreesToRadians(Rotation), RotationAxes);
}
FM_SINL mat4 FM_CALL Mat4TranslationScale(v3 Translation, v3 Scale) {
	mat4 R = Mat4Scale(Scale);
	Translate(&R, Translation);
	return R;
}
FM_SINL mat4 FM_CALL Mat4TranslationScale(vec3 Translation, vec3 Scale) {
	mat4 R = Mat4Scale(Scale);
	Translate(&R, Translation);
	return R;
}
FM_SINL mat4 FM_CALL Mat4TranslationRotationRadians(v3 Translation, float Rotation, v3 RotationAxes) {
	mat4 R = Mat4RotationRadians(Rotation, RotationAxes);
	Translate(&R, Translation);
	return R;
}
FM_SINL mat4 FM_CALL Mat4TranslationRotationRadians(vec3 Translation, float Rotation, vec3 RotationAxes) {
	mat4 R = Mat4RotationRadians(Rotation, RotationAxes);
	Translate(&R, Translation);
	return R;
}
FM_SINL mat4 FM_CALL Mat4TranslationRotationDegrees(v3 Translation, float Rotation, v3 RotationAxes) {
	return Mat4TranslationRotationRadians(Translation, DegreesToRadians(Rotation), RotationAxes);
}
FM_SINL mat4 FM_CALL Mat4TranslationRotationDegrees(vec3 Translation, float Rotation, vec3 RotationAxes) {
	return Mat4TranslationRotationRadians(Translation, DegreesToRadians(Rotation), RotationAxes);
}
FM_SINL mat4 FM_CALL Mat4ScaleRotationRadians(v3 Scale, float Rotation, v3 RotationAxes) {
	mat4 R = Mat4Scale(Scale);
	RotateRadians(&R, Rotation, RotationAxes);
	return R;
}
FM_SINL mat4 FM_CALL Mat4ScaleRotationRadians(vec3 Scale, float Rotation, vec3 RotationAxes) {
	mat4 R = Mat4Scale(Scale);
	RotateRadians(&R, Rotation, RotationAxes);
	return R;
}
FM_SINL mat4 FM_CALL Mat4ScaleRotationDegrees(v3 Scale, float Rotation, v3 RotationAxes) {
	return Mat4ScaleRotationRadians(Scale, DegreesToRadians(Rotation), RotationAxes);
}
FM_SINL mat4 FM_CALL Mat4ScaleRotationDegrees(vec3 Scale, float Rotation, vec3 RotationAxes) {
	return Mat4ScaleRotationRadians(Scale, DegreesToRadians(Rotation), RotationAxes);
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
mat4 FM_CALL operator*(mat4 A, mat4 B) {
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
mat4 Mat4Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far) {
	float RL = Right - Left;
	float TB = Top - Bottom;
	float FN = Far - Near; 
		
	return Mat4FromRows(
		2.f / RL, 0.f, 0.f, -((Right + Left) / RL),
		0.f, 2.f / TB, 0.f, -((Top + Bottom) / TB),
		0.f, 0.f, -2.f / FN, -((Far + Near) / FN),
		0.f, 0.f, 0.f, 1.f);
}
mat4 Mat4Perspective(float Fov, float AspectRatio, float Near, float Far) {
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
mat4 Mat4LookAt(vec3 Eye, vec3 At, vec3 Up) {
	vec3 Forward = Normalize(At - Eye);
	vec3 Right = Cross(Forward, Up); // TODO(docs): We assume that Up is normalized
	Up = Cross(Right, Forward);
	return Mat4FromColumns(
		Right, Up, -Forward,
		Vec3(-Dot(Right, Eye), -Dot(Up, Eye), Dot(Forward, Eye)));
}
mat4 Mat4LookAt(v3 Eye, v3 At, v3 Up) {
	v3 Forward = Normalize(At - Eye);
	v3 Right = Cross(Forward, Up); // TODO(docs): We assume that Up is normalized
	Up = Cross(Right, Forward);
	return Mat4FromColumns(
		Right, Up, -Forward,
		V3(-Dot(Right, Eye), -Dot(Up, Eye), Dot(Forward, Eye)));
}
v4 FM_CALL mat4::GetRowV4(uint32_t Index) {
	FM_ASSERT(Index >= 0 && Index <= 3);
	switch(Index)
	{
		case 0: {
			return V4(
				priv::GetX(Columns[0]), priv::GetX(Columns[1]),
				priv::GetX(Columns[2]), priv::GetX(Columns[3]));
		} break;
		
		case 1: {
			return V4(
				priv::GetY(Columns[0]), priv::GetY(Columns[1]),
				priv::GetY(Columns[2]), priv::GetY(Columns[3]));
		} break;
	
		case 2: {
			return V4(
				priv::GetZ(Columns[0]), priv::GetZ(Columns[1]),
				priv::GetZ(Columns[2]), priv::GetZ(Columns[3]));
		} break;
	
		case 3: {
			return V4(
				priv::GetW(Columns[0]), priv::GetW(Columns[1]),
				priv::GetW(Columns[2]), priv::GetW(Columns[3]));
		} break;
		
		default: {
			FM_ERROR(); // Index has to be in range from 0 to 3
		}
	}
}
void FM_CALL mat4::SetRow(uint32_t Index, v4 Row) {
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

