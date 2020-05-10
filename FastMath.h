/*
FAST MATH
C++ single header math libary
https://github.com/Czapa10/Fast-Math

Written by Grzegorz "Czapa" Bednorz

YOU HAVE TO
#define FM_IMPLEMENTATION
one of C++ files that include this header, BEFORE the include, like this:

#define FM_IMPLEMENTATION
#include <FastMath.h>

If you don't need certain functionality you can also define some of these macros:
FM_EXCLUDE_TEX_COORD_SWIZZLES
FM_EXCLUDE_COLOR_SWIZZLES

like this:

#define FM_IMPLEMENTATION
#define FM_EXCLUDE_TEX_COORD_SWIZZLES
#define FM_EXCLUDE_COLOR_SWIZZLES
#include <FastMath.h>
*/

#ifndef FAST_MATH_H
#define FAST_MATH_H

#include <emmintrin.h>
#include <stdint.h>

#ifdef _MSC_VER
	__pragma(warning(push))
	__pragma(warning(disable : 4201))
#endif

// TODO:  FM_INLINE work on all compilers

#define FM_INLINE __forceinline
#define FM_CALL __vectorcall

#define FM_PI32 3.14159265359f
#define FM_PI64 3.14159265358979323846

namespace fm {

FM_INLINE float Min(float, float);
FM_INLINE float Max(float, float);
FM_INLINE double Min(double, double);
FM_INLINE double Max(double, double);
FM_INLINE int32_t Min(int32_t, int32_t);
FM_INLINE int32_t Max(int32_t, int32_t);
FM_INLINE uint32_t Min(uint32_t, uint32_t);
FM_INLINE uint32_t Max(uint32_t, uint32_t);

FM_INLINE float Abs(float); 
FM_INLINE double Abs(double); 
FM_INLINE int32_t Abs(int32_t);

FM_INLINE float RadiansToDegrees(float Radians);
FM_INLINE double RadiansToDegrees(double Radians);
FM_INLINE float DegreesToRadians(float Degrees);
FM_INLINE double DegreesToRadians(double Degrees);

union v2
{
	struct {
		float X, Y;
	};
	struct {
		float U, V;
	};
	struct {
		float Left;
		union {
			float Top, Right;
		};
	};
	struct {
		float Width, Height;
	};
	struct {
		float W, H;
	};
	float Elements[2];

	FM_INLINE float& operator[](const int& Index) {
		return Elements[Index];
	}
};

FM_INLINE v2 V2FromMemory(const float*);
FM_INLINE v2 V2(float X, float Y);
FM_INLINE v2 V2(float XY);
FM_INLINE v2 V2();

FM_INLINE void Store(float* Mem, v2 V);

FM_INLINE float* Ptr(v2& V) { return &V.X; }
FM_INLINE float* PtrY(v2& V) { return &V.Y; }

FM_INLINE v2 operator+(v2, v2);
FM_INLINE v2 operator-(v2, v2);
FM_INLINE v2& operator+=(v2&, v2);
FM_INLINE v2& operator-=(v2&, v2);
FM_INLINE v2 HadamardMul(v2, v2);
FM_INLINE v2 HadamardDiv(v2, v2);
FM_INLINE v2 operator*(v2 V, float Scalar);
FM_INLINE v2 operator*(float Scalar, v2 V);
FM_INLINE v2 operator/(v2 V, float Scalar); 
FM_INLINE v2 operator-(v2); 
FM_INLINE float Dot(v2, v2); 
FM_INLINE v2 Min(v2, v2); 
FM_INLINE v2 Max(v2, v2); 
FM_INLINE v2 Abs(v2); 
FM_INLINE float SumOfElements(v2);
FM_INLINE float Length(v2);
FM_INLINE float LengthSquared(v2); 
FM_INLINE v2 Normalize(v2);
FM_INLINE v2 Clamp(v2 V, v2 Min, v2 Max);
FM_INLINE v2 Lerp(v2 A, v2 B, float T);

FM_INLINE bool operator==(v2, v2); 
FM_INLINE bool operator!=(v2, v2); 


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

	FM_INLINE float& operator[](const int& Index) {
		return Elements[Index];
	}

	FM_INLINE v3 ZXY(); 
};

FM_INLINE v3 V3FromMemory(float*);
FM_INLINE v3 V3(float X, float Y, float Z);
FM_INLINE v3 V3(float XYZ);
FM_INLINE v3 V3();

FM_INLINE void Store(float* Mem, v3 V); 

FM_INLINE float* Ptr(v3& V) { return &V.X; }
FM_INLINE float* PtrY(v3& V) { return &V.Y; }
FM_INLINE float* PtrZ(v3& V) { return &V.Z; }

FM_INLINE v3 operator+(v3, v3); 
FM_INLINE v3 operator-(v3, v3);
FM_INLINE v3& operator+=(v3&, v3);
FM_INLINE v3& operator-=(v3&, v3);
FM_INLINE v3 HadamardMul(v3, v3);
FM_INLINE v3 HadamardDiv(v3, v3);
FM_INLINE v3 operator*(v3 V, float  Scalar);
FM_INLINE v3 operator*(float Scalar, v3 V);
FM_INLINE v3 operator/(v3 V, float Scalar);
FM_INLINE v3 operator-(v3); 
FM_INLINE v3 Cross(v3, v3); 
FM_INLINE float Dot(v3, v3); 
FM_INLINE v3 Min(v3, v3); 
FM_INLINE v3 Max(v3, v3); 
FM_INLINE v3 Normalize(v3);
FM_INLINE v3 Abs(v3);
FM_INLINE float SumOfElements(v3);
FM_INLINE float Length(v3);
FM_INLINE float LengthSquared(v3); 
FM_INLINE v3 Clamp(v3 V, v3 Min, v3 Max); 
FM_INLINE v3 Lerp(v3 A, v3 B, float T);

FM_INLINE bool operator==(v3, v3); 
FM_INLINE bool operator!=(v3, v3); 


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

	FM_INLINE float& operator[](const int& Index) {
		return Elements[Index];
	}

	FM_INLINE v3 ZXY(); 
};

FM_INLINE v4 V4FromMemory(float*);
FM_INLINE v4 V4(float X, float Y, float Z, float W);
FM_INLINE v4 V4(v3 XYZ, float W);
FM_INLINE v4 V4(float XYZW);
FM_INLINE v4 V4();

FM_INLINE void Store(float* Mem, v4 V); 

FM_INLINE float* Ptr(v4& V) { return &V.X; }
FM_INLINE float* PtrY(v4& V) { return &V.Y; }
FM_INLINE float* PtrZ(v4& V) { return &V.Z; }
FM_INLINE float* PtrW(v4& V) { return &V.W; }

FM_INLINE v4 operator+(v4, v4); 
FM_INLINE v4 operator-(v4, v4);
FM_INLINE v4& operator+=(v4&, v4);
FM_INLINE v4& operator-=(v4&, v4);
FM_INLINE v4 HadamardMul(v4, v4);
FM_INLINE v4 HadamardDiv(v4, v4);
FM_INLINE v4 operator*(v4 V, float  Scalar);
FM_INLINE v4 operator*(float Scalar, v4 V);
FM_INLINE v4 operator/(v4 V, float Scalar);
FM_INLINE v4 operator-(v4); 
FM_INLINE float Dot(v4, v4); 
FM_INLINE v4 Min(v4, v4); 
FM_INLINE v4 Max(v4, v4); 
FM_INLINE v4 Normalize(v4);
FM_INLINE v4 Abs(v4);
FM_INLINE float SumOfElements(v4);
FM_INLINE float Length(v4);
FM_INLINE float LengthSquared(v4); 
FM_INLINE v4 Clamp(v4 V, v4 Min, v4 Max); 
FM_INLINE v4 Lerp(v4 A, v4 B, float T);

FM_INLINE bool operator==(v4, v4); 
FM_INLINE bool operator!=(v4, v4); 


struct alignas(16) vec2
{
	__m128 M;

	FM_INLINE void FM_CALL SetX(float);
	FM_INLINE void FM_CALL SetY(float); 

	FM_INLINE float FM_CALL X() const;
	FM_INLINE float FM_CALL U() const { return X(); }
	FM_INLINE float FM_CALL Left() const { return X(); }
	FM_INLINE float FM_CALL Width() const { return X(); }

	FM_INLINE float FM_CALL Y() const;
	FM_INLINE float FM_CALL V() const { return Y(); }
	FM_INLINE float FM_CALL Top() const { return Y(); }
	FM_INLINE float FM_CALL Height() const { return Y(); }

	FM_INLINE vec2 FM_CALL YX() const;
	FM_INLINE vec2 FM_CALL XX() const;
	FM_INLINE vec2 FM_CALL YY() const;

#ifndef FM_EXCLUDE_TEX_COORD_SWIZZLES
	FM_INLINE vec2 FM_CALL VU() const { return YX(); }
	FM_INLINE vec2 FM_CALL UU() const { return XX(); }
	FM_INLINE vec2 FM_CALL VV() const { return YY(); }
#endif

	FM_INLINE void FM_CALL AddX(float);
	FM_INLINE void FM_CALL AddY(float);

	FM_INLINE void FM_CALL SubX(float);
	FM_INLINE void FM_CALL SubY(float);

	FM_INLINE void FM_CALL MulX(float);
	FM_INLINE void FM_CALL MulY(float);

	FM_INLINE void FM_CALL DivX(float);
	FM_INLINE void FM_CALL DivY(float);
};

FM_INLINE vec2 FM_CALL Vec2FromMemory(const float*); 
FM_INLINE vec2 FM_CALL Vec2(float X, float Y);
FM_INLINE vec2 FM_CALL Vec2(float XY);
FM_INLINE vec2 FM_CALL Vec2(__m128);
FM_INLINE vec2 FM_CALL Vec2();

FM_INLINE void FM_CALL Store(float* Mem, vec2 V);

FM_INLINE float* Ptr(vec2& V) { return (float*)(&V); }
FM_INLINE float* PtrY(vec2& V) { return (float*)(&V) + 1; }

FM_INLINE vec2 FM_CALL operator+(vec2, vec2);
FM_INLINE vec2 FM_CALL operator-(vec2, vec2);
FM_INLINE vec2& FM_CALL operator+=(vec2&, vec2);
FM_INLINE vec2& FM_CALL operator-=(vec2&, vec2);
FM_INLINE vec2 FM_CALL HadamardMul(vec2, vec2);
FM_INLINE vec2 FM_CALL HadamardDiv(vec2, vec2);
FM_INLINE vec2 FM_CALL operator*(vec2 V, float Scalar);
FM_INLINE vec2 FM_CALL operator*(float Scalar, vec2 V);
FM_INLINE vec2 FM_CALL operator/(vec2 V, float Scalar); 
FM_INLINE vec2 FM_CALL operator-(vec2); 
FM_INLINE float FM_CALL Dot(vec2, vec2); 
FM_INLINE vec2 FM_CALL Min(vec2, vec2); 
FM_INLINE vec2 FM_CALL Max(vec2, vec2); 
FM_INLINE vec2 FM_CALL Abs(vec2); 
FM_INLINE float FM_CALL SumOfElements(vec2);
FM_INLINE float FM_CALL Length(vec2);
FM_INLINE float FM_CALL LengthSquared(vec2); 
FM_INLINE vec2 FM_CALL Normalize(vec2);
FM_INLINE vec2 FM_CALL Clamp(vec2 V, vec2 Min, vec2 Max);
FM_INLINE vec2 FM_CALL Lerp(vec2 A, vec2 B, float T);

FM_INLINE bool FM_CALL operator==(vec2, vec2); 
FM_INLINE bool FM_CALL operator!=(vec2, vec2); 
FM_INLINE vec2 FM_CALL EqualsMask(vec2, vec2);
FM_INLINE vec2 FM_CALL GreaterMask(vec2, vec2);
FM_INLINE vec2 FM_CALL GreaterOrEqualMask(vec2, vec2);
FM_INLINE vec2 FM_CALL LesserMask(vec2, vec2);
FM_INLINE vec2 FM_CALL LesserOrEqualMask(vec2, vec2);


struct alignas(16) vec2d
{
	__m128d M;

	FM_INLINE void FM_CALL SetX(double X);
	FM_INLINE void FM_CALL SetY(double Y);

	FM_INLINE double FM_CALL X() const;
	FM_INLINE double FM_CALL U() const { return X(); }
	FM_INLINE double FM_CALL Left() const { return X(); }
	FM_INLINE double FM_CALL Width() const { return X(); }

	FM_INLINE double FM_CALL Y() const;
	FM_INLINE double FM_CALL V() const { return Y(); }
	FM_INLINE double FM_CALL Height() const { return Y(); }
	FM_INLINE double FM_CALL Top() const { return Y(); }

	FM_INLINE vec2d FM_CALL YX() const;
	FM_INLINE vec2d FM_CALL XX() const;
	FM_INLINE vec2d FM_CALL YY() const;

	FM_INLINE vec2d FM_CALL VU() const { return YX(); }
	FM_INLINE vec2d FM_CALL UU() const { return XX(); }
	FM_INLINE vec2d FM_CALL VV() const { return YY(); }

	FM_INLINE void FM_CALL AddX(double);
	FM_INLINE void FM_CALL AddY(double);

	FM_INLINE void FM_CALL SubX(double);
	FM_INLINE void FM_CALL SubY(double);

	FM_INLINE void FM_CALL MulX(double);
	FM_INLINE void FM_CALL MulY(double);

	FM_INLINE void FM_CALL DivX(double);
	FM_INLINE void FM_CALL DivY(double);
};

FM_INLINE vec2d FM_CALL Vec2dFromMemory(const double*);
FM_INLINE vec2d FM_CALL Vec2d(double X, double Y);
FM_INLINE vec2d FM_CALL Vec2d(double XY);
FM_INLINE vec2d FM_CALL Vec2d (__m128d);
FM_INLINE vec2d FM_CALL Vec2d();

FM_INLINE void FM_CALL Store(double* Mem, vec2d V);
FM_INLINE void FM_CALL Store16ByteAligned(double* Mem, vec2d V);

FM_INLINE double* Ptr(const vec2d& V) { return (double*)(&V); }
FM_INLINE double* PtrY(const vec2d& V) { return (double*)(&V) + 1; }

FM_INLINE vec2d FM_CALL operator+(vec2d, vec2d); 
FM_INLINE vec2d FM_CALL operator-(vec2d, vec2d);
FM_INLINE vec2d& FM_CALL operator+=(vec2d&, vec2d);
FM_INLINE vec2d& FM_CALL operator-=(vec2d&, vec2d);
FM_INLINE vec2d FM_CALL HadamardMul(vec2d, vec2d);
FM_INLINE vec2d FM_CALL HadamardDiv(vec2d, vec2d);
FM_INLINE vec2d FM_CALL operator*(vec2d V, double Scalar);
FM_INLINE vec2d FM_CALL operator*(double Scalar, vec2d V);
FM_INLINE vec2d FM_CALL operator/(vec2d V, double Scalar);
FM_INLINE vec2d FM_CALL operator-(vec2d); 
FM_INLINE double FM_CALL Dot(vec2d, vec2d); 
FM_INLINE vec2d FM_CALL Min(vec2d, vec2d); 
FM_INLINE vec2d FM_CALL Max(vec2d, vec2d); 
FM_INLINE vec2d FM_CALL Normalize(vec2d);
FM_INLINE vec2d FM_CALL Abs(vec2d);
FM_INLINE double FM_CALL SumOfElements(vec2d);
FM_INLINE double FM_CALL Length(vec2d);
FM_INLINE double FM_CALL LengthSquared(vec2d); 
FM_INLINE vec2d FM_CALL Clamp(vec2d V, vec2d Min, vec2d Max); 
FM_INLINE vec2d FM_CALL Lerp(vec2d A, vec2d B, double T);

FM_INLINE bool FM_CALL operator==(vec2d, vec2d); 
FM_INLINE bool FM_CALL operator!=(vec2d, vec2d); 
FM_INLINE vec2d FM_CALL EqualsMask(vec2d, vec2d);
FM_INLINE vec2d FM_CALL GreaterMask(vec2d, vec2d);
FM_INLINE vec2d FM_CALL GreaterOrEqualMask(vec2d, vec2d);
FM_INLINE vec2d FM_CALL LesserMask(vec2d, vec2d);
FM_INLINE vec2d FM_CALL LesserOrEqualMask(vec2d, vec2d);


struct alignas(16) vec2i
{
	__m128i M;

	FM_INLINE void FM_CALL SetX(int32_t);
	FM_INLINE void FM_CALL SetY(int32_t);

	FM_INLINE int32_t FM_CALL X() const;
	FM_INLINE int32_t FM_CALL U() const { return X(); }
	FM_INLINE int32_t FM_CALL Left() const { return X(); }
	FM_INLINE int32_t FM_CALL Width() const { return X(); }

	FM_INLINE int32_t FM_CALL Y() const;
	FM_INLINE int32_t FM_CALL V() const { return Y(); }
	FM_INLINE int32_t FM_CALL Top() const { return Y(); }
	FM_INLINE int32_t FM_CALL Height() const { return Y(); }

	FM_INLINE vec2i FM_CALL YX() const;
	FM_INLINE vec2i FM_CALL XX() const;
	FM_INLINE vec2i FM_CALL YY() const;

	FM_INLINE vec2i FM_CALL VU() const { return YX(); }
	FM_INLINE vec2i FM_CALL UU() const { return XX(); }
	FM_INLINE vec2i FM_CALL VV() const { return YY(); }

	FM_INLINE void FM_CALL AddX(int32_t);
	FM_INLINE void FM_CALL AddY(int32_t);

	FM_INLINE void FM_CALL SubX(int32_t);
	FM_INLINE void FM_CALL SubY(int32_t);

	FM_INLINE void FM_CALL MulX(int32_t);
	FM_INLINE void FM_CALL MulY(int32_t);

	FM_INLINE void FM_CALL DivX(int32_t);
	FM_INLINE void FM_CALL DivY(int32_t);
};
FM_INLINE vec2i FM_CALL Vec2iFromMemory(const int32_t*);
FM_INLINE vec2i FM_CALL Vec2i(int32_t X, int32_t Y);
FM_INLINE vec2i FM_CALL Vec2i(int32_t XY); 
FM_INLINE vec2i FM_CALL Vec2i(__m128i); 
FM_INLINE vec2i FM_CALL Vec2i();

FM_INLINE void FM_CALL Store(int32_t* Mem, vec2i V); 

FM_INLINE int32_t* Ptr(const vec2i& V) { return (int32_t*)(&V); }
FM_INLINE int32_t* PtrY(const vec2i& V) { return (int32_t*)(&V) + 1; }

FM_INLINE vec2i FM_CALL operator+(vec2i A, vec2i B);
FM_INLINE vec2i FM_CALL operator-(vec2i A, vec2i B); 
FM_INLINE vec2i& FM_CALL operator+=(vec2i& a, vec2i B);
FM_INLINE vec2i& FM_CALL operator-=(vec2i& a, vec2i B);
FM_INLINE vec2i FM_CALL HadamardMul(vec2i A, vec2i B);
FM_INLINE vec2i FM_CALL operator*(vec2i v, int32_t Scalar); 
FM_INLINE vec2i FM_CALL operator*(int32_t Scalar, vec2i v);
FM_INLINE vec2i FM_CALL operator-(vec2i v); 
FM_INLINE vec2i FM_CALL Min(vec2i, vec2i); 
FM_INLINE vec2i FM_CALL Max(vec2i, vec2i); 
FM_INLINE vec2i FM_CALL Abs(vec2i); 
FM_INLINE int32_t FM_CALL SumOfElements(vec2i);
FM_INLINE int32_t FM_CALL Length(vec2i);
FM_INLINE int32_t FM_CALL LengthSquared(vec2i); 
FM_INLINE vec2i FM_CALL Clamp(vec2i V, vec2i Min, vec2i Max); 

FM_INLINE bool FM_CALL operator==(vec2i, vec2i); 
FM_INLINE bool FM_CALL operator!=(vec2i, vec2i); 
FM_INLINE vec2i FM_CALL EqualsMask(vec2i, vec2i);
FM_INLINE vec2i FM_CALL GreaterMask(vec2i, vec2i);
FM_INLINE vec2i FM_CALL GreaterOrEqualMask(vec2i, vec2i);
FM_INLINE vec2i FM_CALL LesserMask(vec2i, vec2i);
FM_INLINE vec2i FM_CALL LesserOrEqualMask(vec2i, vec2i);
// TODO: Add HadamardDiv() and operator/ - Maybe I can do that using cast instructions?


struct alignas(16) vec2u
{
	__m128i M;

	FM_INLINE void FM_CALL SetX(uint32_t);
	FM_INLINE void FM_CALL SetY(uint32_t);

	FM_INLINE uint32_t FM_CALL X() const;
	FM_INLINE uint32_t FM_CALL U() const { return X(); }
	FM_INLINE uint32_t FM_CALL Left() const { return X(); }
	FM_INLINE uint32_t FM_CALL Width() const { return X(); }

	FM_INLINE uint32_t FM_CALL Y() const;
	FM_INLINE uint32_t FM_CALL V() const { return Y(); }
	FM_INLINE uint32_t FM_CALL Top() const { return Y(); }
	FM_INLINE uint32_t FM_CALL Height() const { return Y(); }

	FM_INLINE vec2u FM_CALL YX() const;
	FM_INLINE vec2u FM_CALL XX() const;
	FM_INLINE vec2u FM_CALL YY() const;

	FM_INLINE vec2u FM_CALL VU() const { return YX(); }
	FM_INLINE vec2u FM_CALL UU() const { return XX(); }
	FM_INLINE vec2u FM_CALL VV() const { return YY(); }

	FM_INLINE void FM_CALL AddX(uint32_t);
	FM_INLINE void FM_CALL AddY(uint32_t);

	FM_INLINE void FM_CALL SubX(uint32_t);
	FM_INLINE void FM_CALL SubY(uint32_t);

	FM_INLINE void FM_CALL MulX(uint32_t);
	FM_INLINE void FM_CALL MulY(uint32_t);

	FM_INLINE void FM_CALL DivX(uint32_t);
	FM_INLINE void FM_CALL DivY(uint32_t);
};

FM_INLINE vec2u FM_CALL Vec2uFromMemory(const uint32_t*); 
FM_INLINE vec2u FM_CALL Vec2u(uint32_t X, uint32_t Y); 
FM_INLINE vec2u FM_CALL Vec2u(uint32_t XY);
FM_INLINE vec2u FM_CALL Vec2u(__m128i);
FM_INLINE vec2u FM_CALL Vec2u();

FM_INLINE void FM_CALL Store(uint32_t* Mem, vec2u V);

FM_INLINE uint32_t* Ptr(const vec2u& V) { return (uint32_t*)(&V); }
FM_INLINE uint32_t* PtrY(const vec2u& V) { return (uint32_t*)(&V) + 1; }

FM_INLINE vec2u FM_CALL operator+(vec2u, vec2u);
FM_INLINE vec2u FM_CALL operator-(vec2u, vec2u);
FM_INLINE vec2u& FM_CALL operator+=(vec2u&, vec2u);
FM_INLINE vec2u& FM_CALL operator-=(vec2u&, vec2u);
FM_INLINE vec2u FM_CALL HadamardMul(vec2u, vec2u);
FM_INLINE vec2u FM_CALL operator*(vec2u V, uint32_t Scalar); 
FM_INLINE vec2u FM_CALL operator*(uint32_t Scalar, vec2u V);
FM_INLINE vec2u FM_CALL Min(vec2u, vec2u); 
FM_INLINE vec2u FM_CALL Max(vec2u, vec2u); 
FM_INLINE uint32_t FM_CALL SumOfElements(vec2u);
FM_INLINE uint32_t FM_CALL Length(vec2u);
FM_INLINE uint32_t FM_CALL LengthSquared(vec2u); 
FM_INLINE vec2u FM_CALL Clamp(vec2u v, vec2u min, vec2u Max); 

FM_INLINE bool FM_CALL operator==(vec2u, vec2u); 
FM_INLINE bool FM_CALL operator!=(vec2u, vec2u); 
FM_INLINE vec2u FM_CALL EqualsMask(vec2u, vec2u);
FM_INLINE vec2u FM_CALL GreaterMask(vec2u, vec2u);
FM_INLINE vec2u FM_CALL GreaterOrEqualMask(vec2u, vec2u);
FM_INLINE vec2u FM_CALL LesserMask(vec2u, vec2u);
FM_INLINE vec2u FM_CALL LesserOrEqualMask(vec2u, vec2u);
// TODO: Add HadamardDiv() and operator/


struct alignas(16) vec3
{
	__m128 M;

	FM_INLINE void FM_CALL SetX(float X);
	FM_INLINE void FM_CALL SetY(float Y);
	FM_INLINE void FM_CALL SetZ(float Z);

	FM_INLINE void FM_CALL AddX(float X);
	FM_INLINE void FM_CALL AddY(float Y);
	FM_INLINE void FM_CALL AddZ(float Z);

	FM_INLINE void FM_CALL SubX(float X);
	FM_INLINE void FM_CALL SubY(float Y);
	FM_INLINE void FM_CALL SubZ(float Z);

	FM_INLINE void FM_CALL MulX(float X);
	FM_INLINE void FM_CALL MulY(float Y);
	FM_INLINE void FM_CALL MulZ(float Z);

	FM_INLINE void FM_CALL DivX(float X);
	FM_INLINE void FM_CALL DivY(float Y);
	FM_INLINE void FM_CALL DivZ(float Z);

	FM_INLINE float FM_CALL X() const;
	FM_INLINE float FM_CALL U() const { return X(); }
	FM_INLINE float FM_CALL R() const { return X(); }

	FM_INLINE float FM_CALL Y() const;
	FM_INLINE float FM_CALL V() const { return Y(); }
	FM_INLINE float FM_CALL G() const { return Y(); }

	FM_INLINE float FM_CALL Z() const;
	FM_INLINE float FM_CALL W() const { return Z(); }
	FM_INLINE float FM_CALL B() const { return Z(); }

	FM_INLINE vec2 FM_CALL XY() const;
	FM_INLINE vec2 FM_CALL YX() const;
	FM_INLINE vec2 FM_CALL YZ() const;
	FM_INLINE vec2 FM_CALL ZY() const;
	FM_INLINE vec2 FM_CALL XZ() const;
	FM_INLINE vec2 FM_CALL ZX() const;
	FM_INLINE vec2 FM_CALL XX() const;
	FM_INLINE vec2 FM_CALL YY() const;
	FM_INLINE vec2 FM_CALL ZZ() const;

#ifndef FM_EXCLUDE_TEX_COORD_SWIZZLES
	FM_INLINE vec2 FM_CALL UV() const { return XY(); }
	FM_INLINE vec2 FM_CALL VU() const { return YX(); }
	FM_INLINE vec2 FM_CALL VW() const { return YZ(); }
	FM_INLINE vec2 FM_CALL WV() const { return ZY(); }
	FM_INLINE vec2 FM_CALL UW() const { return XZ(); }
	FM_INLINE vec2 FM_CALL WU() const { return ZX(); }
	FM_INLINE vec2 FM_CALL UU() const { return XX(); }
	FM_INLINE vec2 FM_CALL VV() const { return YY(); }
	FM_INLINE vec2 FM_CALL WW() const { return ZZ(); }
#endif

#ifndef FM_EXCLUDE_COLOR_SWIZZLES
	FM_INLINE vec2 FM_CALL RG() const { return XY(); }
	FM_INLINE vec2 FM_CALL GR() const { return YX(); }
	FM_INLINE vec2 FM_CALL GB() const { return YZ(); }
	FM_INLINE vec2 FM_CALL BG() const { return ZY(); }
	FM_INLINE vec2 FM_CALL RB() const { return XZ(); }
	FM_INLINE vec2 FM_CALL BR() const { return ZX(); }
	FM_INLINE vec2 FM_CALL RR() const { return XX(); }
	FM_INLINE vec2 FM_CALL GG() const { return YY(); }
	FM_INLINE vec2 FM_CALL BB() const { return ZZ(); }
#endif

	FM_INLINE vec3 FM_CALL XYZ() const;
	FM_INLINE vec3 FM_CALL YZX() const;
	FM_INLINE vec3 FM_CALL ZXY() const;
	FM_INLINE vec3 FM_CALL ZYX() const;
	FM_INLINE vec3 FM_CALL XZY() const;
	FM_INLINE vec3 FM_CALL YXZ() const;
	FM_INLINE vec3 FM_CALL XXY() const;
	FM_INLINE vec3 FM_CALL XXZ() const;
	FM_INLINE vec3 FM_CALL YYX() const;
	FM_INLINE vec3 FM_CALL YYZ() const;
	FM_INLINE vec3 FM_CALL ZZX() const;
	FM_INLINE vec3 FM_CALL ZZY() const;
	FM_INLINE vec3 FM_CALL YXX() const;
	FM_INLINE vec3 FM_CALL ZXX() const;
	FM_INLINE vec3 FM_CALL XYY() const;
	FM_INLINE vec3 FM_CALL ZYY() const;
	FM_INLINE vec3 FM_CALL XZZ() const;
	FM_INLINE vec3 FM_CALL YZZ() const;
	FM_INLINE vec3 FM_CALL XYX() const;
	FM_INLINE vec3 FM_CALL XZX() const;
	FM_INLINE vec3 FM_CALL YXY() const;
	FM_INLINE vec3 FM_CALL YZY() const;
	FM_INLINE vec3 FM_CALL ZXZ() const;
	FM_INLINE vec3 FM_CALL ZYZ() const;
	FM_INLINE vec3 FM_CALL XXX() const;
	FM_INLINE vec3 FM_CALL YYY() const;
	FM_INLINE vec3 FM_CALL ZZZ() const;

#ifndef FM_EXCLUDE_TEX_COORD_SWIZZLES
	FM_INLINE vec3 FM_CALL UVW() const { return XYZ(); }
	FM_INLINE vec3 FM_CALL VWU() const { return YZX(); }
	FM_INLINE vec3 FM_CALL WUV() const { return ZXY(); }
	FM_INLINE vec3 FM_CALL WVU() const { return ZYX(); }
	FM_INLINE vec3 FM_CALL UWV() const { return XZY(); }
	FM_INLINE vec3 FM_CALL VUW() const { return YXZ(); }
	FM_INLINE vec3 FM_CALL UUV() const { return XXY(); }
	FM_INLINE vec3 FM_CALL UUW() const { return XXZ(); }
	FM_INLINE vec3 FM_CALL VVU() const { return YYX(); }
	FM_INLINE vec3 FM_CALL VVW() const { return YYZ(); }
	FM_INLINE vec3 FM_CALL WWU() const { return ZZX(); }
	FM_INLINE vec3 FM_CALL WWV() const { return ZZY(); }
	FM_INLINE vec3 FM_CALL VUU() const { return YXX(); }
	FM_INLINE vec3 FM_CALL WUU() const { return ZXX(); }
	FM_INLINE vec3 FM_CALL UVV() const { return XYY(); }
	FM_INLINE vec3 FM_CALL WVV() const { return ZYY(); }
	FM_INLINE vec3 FM_CALL UWW() const { return XZZ(); }
	FM_INLINE vec3 FM_CALL VWW() const { return YZZ(); }
	FM_INLINE vec3 FM_CALL UVU() const { return XYX(); }
	FM_INLINE vec3 FM_CALL UWU() const { return XZX(); }
	FM_INLINE vec3 FM_CALL VUV() const { return YXY(); }
	FM_INLINE vec3 FM_CALL VWV() const { return YZY(); }
	FM_INLINE vec3 FM_CALL WUW() const { return ZXZ(); }
	FM_INLINE vec3 FM_CALL WVW() const { return ZYZ(); }
	FM_INLINE vec3 FM_CALL UUU() const { return XXX(); }
	FM_INLINE vec3 FM_CALL VVV() const { return YYY(); }
	FM_INLINE vec3 FM_CALL WWW() const { return ZZZ(); }
#endif

#ifndef FM_EXCLUDE_COLOR_SWIZZLES
	//FM_INLINE vec3 FM_CALL RGB() const { return XYZ(); }
	FM_INLINE vec3 FM_CALL GBR() const { return YZX(); }
	FM_INLINE vec3 FM_CALL BRG() const { return ZXY(); }
	FM_INLINE vec3 FM_CALL BGR() const { return ZYX(); }
	FM_INLINE vec3 FM_CALL RBG() const { return XZY(); }
	FM_INLINE vec3 FM_CALL GRB() const { return YXZ(); }
	FM_INLINE vec3 FM_CALL RRG() const { return XXY(); }
	FM_INLINE vec3 FM_CALL RRB() const { return XXZ(); }
	FM_INLINE vec3 FM_CALL GGR() const { return YYX(); }
	FM_INLINE vec3 FM_CALL GGB() const { return YYZ(); }
	FM_INLINE vec3 FM_CALL BBR() const { return ZZX(); }
	FM_INLINE vec3 FM_CALL BBG() const { return ZZY(); }
	FM_INLINE vec3 FM_CALL GRR() const { return YXX(); }
	FM_INLINE vec3 FM_CALL BRR() const { return ZXX(); }
	FM_INLINE vec3 FM_CALL RGG() const { return XYY(); }
	FM_INLINE vec3 FM_CALL BGG() const { return ZYY(); }
	FM_INLINE vec3 FM_CALL RBB() const { return XZZ(); }
	FM_INLINE vec3 FM_CALL GBB() const { return YZZ(); }
	FM_INLINE vec3 FM_CALL RGR() const { return XYX(); }
	FM_INLINE vec3 FM_CALL RBR() const { return XZX(); }
	FM_INLINE vec3 FM_CALL GRG() const { return YXY(); }
	FM_INLINE vec3 FM_CALL GBG() const { return YZY(); }
	FM_INLINE vec3 FM_CALL BRB() const { return ZXZ(); }
	FM_INLINE vec3 FM_CALL BGB() const { return ZYZ(); }
	FM_INLINE vec3 FM_CALL RRR() const { return XXX(); }
	FM_INLINE vec3 FM_CALL GGG() const { return YYY(); }
	FM_INLINE vec3 FM_CALL BBB() const { return ZZZ(); }
#endif
};

FM_INLINE vec3 FM_CALL Vec3FromMemory(float*);
FM_INLINE vec3 FM_CALL Vec3(float X, float Y, float Z);
FM_INLINE vec3 FM_CALL Vec3(float XYZ);
FM_INLINE vec3 FM_CALL Vec3(__m128);
FM_INLINE vec3 FM_CALL Vec3();

FM_INLINE void FM_CALL Store(float* Mem, vec3 V); 

FM_INLINE float* Ptr(vec3& V) { return (float*)(&V); }
FM_INLINE float* PtrY(vec3& V) { return (float*)(&V) + 1; }
FM_INLINE float* PtrZ(vec3& V) { return (float*)(&V) + 2; }

FM_INLINE vec3 FM_CALL operator+(vec3, vec3); 
FM_INLINE vec3 FM_CALL operator-(vec3, vec3);
FM_INLINE vec3& FM_CALL operator+=(vec3&, vec3);
FM_INLINE vec3& FM_CALL operator-=(vec3&, vec3);
FM_INLINE vec3 FM_CALL HadamardMul(vec3, vec3);
FM_INLINE vec3 FM_CALL HadamardDiv(vec3, vec3);
FM_INLINE vec3 FM_CALL operator*(vec3 V, float  Scalar);
FM_INLINE vec3 FM_CALL operator*(float Scalar, vec3 V);
FM_INLINE vec3 FM_CALL operator/(vec3 V, float Scalar);
FM_INLINE vec3 FM_CALL operator-(vec3); 
FM_INLINE vec3 FM_CALL Cross(vec3, vec3); 
FM_INLINE float FM_CALL Dot(vec3, vec3); 
FM_INLINE vec3 FM_CALL Min(vec3, vec3); 
FM_INLINE vec3 FM_CALL Max(vec3, vec3); 
FM_INLINE vec3 FM_CALL Normalize(vec3);
FM_INLINE vec3 FM_CALL Abs(vec3);
FM_INLINE float FM_CALL SumOfElements(vec3);
FM_INLINE float FM_CALL Length(vec3);
FM_INLINE float FM_CALL LengthSquared(vec3); 
FM_INLINE vec3 FM_CALL Clamp(vec3 V, vec3 Min, vec3 Max); 
FM_INLINE vec3 FM_CALL Lerp(vec3 A, vec3 B, float T);

FM_INLINE bool FM_CALL operator==(vec3, vec3); 
FM_INLINE bool FM_CALL operator!=(vec3, vec3); 
FM_INLINE vec3 FM_CALL EqualsMask(vec3, vec3);
FM_INLINE vec3 FM_CALL GreaterMask(vec3, vec3);
FM_INLINE vec3 FM_CALL GreaterOrEqualMask(vec3, vec3);
FM_INLINE vec3 FM_CALL LesserMask(vec3, vec3);
FM_INLINE vec3 FM_CALL LesserOrEqualMask(vec3, vec3);


struct alignas(16) vec4
{
	__m128 M;

	FM_INLINE void FM_CALL SetX(float);
	FM_INLINE void FM_CALL SetY(float); 
	FM_INLINE void FM_CALL SetZ(float); 
	FM_INLINE void FM_CALL SetW(float); 

	FM_INLINE void FM_CALL AddX(float);
	FM_INLINE void FM_CALL AddY(float); 
	FM_INLINE void FM_CALL AddZ(float); 
	FM_INLINE void FM_CALL AddW(float); 

	FM_INLINE void FM_CALL SubX(float);
	FM_INLINE void FM_CALL SubY(float); 
	FM_INLINE void FM_CALL SubZ(float); 
	FM_INLINE void FM_CALL SubW(float); 

	FM_INLINE void FM_CALL MulX(float);
	FM_INLINE void FM_CALL MulY(float); 
	FM_INLINE void FM_CALL MulZ(float); 
	FM_INLINE void FM_CALL MulW(float); 

	FM_INLINE void FM_CALL DivX(float);
	FM_INLINE void FM_CALL DivY(float); 
	FM_INLINE void FM_CALL DivZ(float); 
	FM_INLINE void FM_CALL DivW(float); 

	FM_INLINE float FM_CALL X() const;
	FM_INLINE float FM_CALL Y() const;
	FM_INLINE float FM_CALL Z() const;
	FM_INLINE float FM_CALL W() const;

	FM_INLINE float FM_CALL R() const { return X(); }
	FM_INLINE float FM_CALL G() const { return Y(); }
	FM_INLINE float FM_CALL B() const { return Z(); }
	FM_INLINE float FM_CALL A() const { return W(); }
};
FM_INLINE vec4 FM_CALL Vec4FromMemory(const float*); 
FM_INLINE vec4 FM_CALL Vec4(vec3 V, float W); 
FM_INLINE vec4 FM_CALL Vec4(float X, float Y, float Z, float W);
FM_INLINE vec4 FM_CALL Vec4(float XYZW);
FM_INLINE vec4 FM_CALL Vec4(__m128);
FM_INLINE vec4 FM_CALL Vec4();

FM_INLINE void FM_CALL Store(float* Mem, vec4 V);
FM_INLINE void FM_CALL Store16ByteAligned(float* Mem, vec4 V);

FM_INLINE float* Ptr(const vec4& V) { return (float*)(&V); }
FM_INLINE float* PtrY(const vec4& V) { return (float*)(&V) + 1; }
FM_INLINE float* PtrZ(const vec4& V) { return (float*)(&V) + 2; }
FM_INLINE float* PtrW(const vec4& V) { return (float*)(&V) + 3; }

FM_INLINE vec4 FM_CALL operator+(vec4, vec4); 
FM_INLINE vec4 FM_CALL operator-(vec4, vec4);
FM_INLINE vec4& FM_CALL operator+=(vec4&, vec4);
FM_INLINE vec4& FM_CALL operator-=(vec4&, vec4);
FM_INLINE vec4 FM_CALL HadamardMul(vec4, vec4);
FM_INLINE vec4 FM_CALL HadamardDiv(vec4, vec4);
FM_INLINE vec4 FM_CALL operator*(vec4 V, float Scalar);
FM_INLINE vec4 FM_CALL operator*(float Scalar, vec4 V);
FM_INLINE vec4 FM_CALL operator/(vec4 V, float Scalar);
FM_INLINE vec4 FM_CALL operator-(vec4); 
FM_INLINE vec4 FM_CALL Cross(vec4, vec4); 
FM_INLINE float FM_CALL Dot(vec4, vec4); 
FM_INLINE vec4 FM_CALL Min(vec4, vec4); 
FM_INLINE vec4 FM_CALL Max(vec4, vec4); 
FM_INLINE vec4 FM_CALL Normalize(vec4);
FM_INLINE vec4 FM_CALL Abs(vec4);
FM_INLINE float FM_CALL SumOfElements(vec4);
FM_INLINE float FM_CALL Length(vec4);
FM_INLINE float FM_CALL LengthSquared(vec4); 
FM_INLINE vec4 FM_CALL Clamp(vec4 V, vec4 Min, vec4 Max); 
FM_INLINE vec4 FM_CALL Lerp(vec4 A, vec4 B, float T);

FM_INLINE bool FM_CALL operator==(vec4, vec4); 
FM_INLINE bool FM_CALL operator!=(vec4, vec4); 
FM_INLINE vec4 FM_CALL EqualsMask(vec4, vec4);
FM_INLINE vec4 FM_CALL GreaterMask(vec4, vec4);
FM_INLINE vec4 FM_CALL GreaterOrEqualMask(vec4, vec4);
FM_INLINE vec4 FM_CALL LesserMask(vec4, vec4);
FM_INLINE vec4 FM_CALL LesserOrEqualMask(vec4, vec4);



struct alignas(16) mat4
{
	__m128 Columns[4];

	FM_INLINE vec4 FM_CALL GetColumn(uint32_t Index);
	FM_INLINE void FM_CALL SetColumn(uint32_t Index, vec4 Col);
	FM_INLINE void FM_CALL SetColumn(uint32_t Index, float X, float Y, float Z, float W);
	FM_INLINE void FM_CALL SwapColumns(uint32_t Col1Index, uint32_t Col2Index); 

	vec4 FM_CALL GetRow(uint32_t Index);
	void FM_CALL SetRow(uint32_t Index, vec4 Row);
	FM_INLINE void FM_CALL SetRow(uint32_t Index, float X, float Y, float Z, float W);
	FM_INLINE void FM_CALL SwapRows(uint32_t Row1Index, uint32_t Row2Index); 

	FM_INLINE vec4 FM_CALL GetMainDiagonal();
	FM_INLINE void FM_CALL SetMainDiagonal(float X, float Y, float Z, float W); 
	FM_INLINE void FM_CALL SetMainDiagonal(vec4);
};

FM_INLINE mat4 FM_CALL Mat4FromColumnMajorMemory(float*); 
// TODO: Mat4FromRowMajorMemory
FM_INLINE mat4 FM_CALL Mat4(); 
FM_INLINE mat4 FM_CALL Mat4Identity(); 
FM_INLINE mat4 FM_CALL Mat4Diagonal(float Diag); 
FM_INLINE mat4 FM_CALL Mat4Diagonal(float DiagX, float DiagY, float DiagZ, float DiagW); 
FM_INLINE mat4 FM_CALL Mat4Diagonal(vec4 Diag); 
FM_INLINE mat4 FM_CALL Mat4FromColumns(vec4 Col1, vec4 Col2, vec4 Col3, vec4 Col4); 
FM_INLINE mat4 FM_CALL Mat4FromColumns(vec3 Col1, vec3 Col2, vec3 Col3, vec3 Col4); 
FM_INLINE mat4 FM_CALL Mat4FromColumns(
	float E11, float E21, float E31, float E41,
    float E12, float E22, float E32, float E42,
    float E13, float E23, float E33, float E43,
    float E14, float E24, float E34, float E44);
FM_INLINE mat4 FM_CALL Mat4FromRows(vec4 Row1, vec4 Row2, vec4 Row3, vec4 Row4); 
FM_INLINE mat4 FM_CALL Mat4FromRows(vec3 Row1, vec3 Row2, vec3 Row3, vec3 Row4); 
FM_INLINE mat4 FM_CALL Mat4FromRows(
	float E11, float E12, float E13, float E14,
    float E21, float E22, float E23, float E24,
    float E31, float E32, float E33, float E34,
    float E41, float E42, float E43, float E44);

FM_INLINE void FM_CALL Store(float* Mem, mat4);
FM_INLINE void FM_CALL Store16ByteAligned(float* Mem, mat4);

FM_INLINE float* Ptr(const mat4& V) { return (float*)(&V); }

FM_INLINE mat4 FM_CALL operator+(mat4, mat4);
FM_INLINE mat4 FM_CALL operator-(mat4, mat4);
FM_INLINE mat4 FM_CALL operator*(mat4, mat4);
FM_INLINE vec4 FM_CALL operator*(mat4, vec4);
FM_INLINE mat4 FM_CALL operator*(mat4, float Scalar);
FM_INLINE mat4 FM_CALL operator*(float Scalar, mat4);
FM_INLINE mat4 FM_CALL operator/(mat4, float Scalar);
FM_INLINE void FM_CALL Transpose(mat4*);
FM_INLINE mat4 FM_CALL Transpose(mat4);
FM_INLINE mat4 FM_CALL SwapColumns(mat4, uint32_t Col1Index, uint32_t Col2Index);
FM_INLINE mat4 FM_CALL SwapRows(mat4, uint32_t Row1Index, uint32_t Row2Index);

FM_INLINE mat4 FM_CALL Mat4Translation(float X, float Y, float Z); 
FM_INLINE mat4 FM_CALL Mat4Translation(vec3 Translation);
FM_INLINE void FM_CALL Translate(mat4*, float X, float Y, float Z); 
FM_INLINE void FM_CALL Translate(mat4*, vec3 Translation);

FM_INLINE mat4 FM_CALL Mat4Scale(float Scalar); 
FM_INLINE mat4 FM_CALL Mat4Scale(float ScalarX, float ScalarY, float ScalarZ); 
FM_INLINE mat4 FM_CALL Mat4Scale(vec3 Scalar);
FM_INLINE void FM_CALL Scale(mat4*, float Scalar); 
FM_INLINE void FM_CALL Scale(mat4*, float X, float Y, float Z); 
FM_INLINE void FM_CALL Scale(mat4*, vec3 Scalar);

FM_INLINE mat4 FM_CALL Mat4RotationDegrees(float Degrees, float AxisX, float AxisY, float AxisZ); 
FM_INLINE mat4 FM_CALL Mat4RotationDegrees(float Degrees, vec3 Axis);
FM_INLINE mat4 FM_CALL Mat4RotationAroundXAxisDegrees(float Degrees);
FM_INLINE mat4 FM_CALL Mat4RotationAroundYAxisDegrees(float Degrees);
FM_INLINE mat4 FM_CALL Mat4RotationAroundZAxisDegrees(float Degrees);
FM_INLINE void FM_CALL RotateDegrees(mat4*, float Degrees, float AxisX, float AxisY, float AxisZ); 
FM_INLINE void FM_CALL RotateDegrees(mat4*, float Degrees, float AxisX, float AxisY, float AxisZ); 
FM_INLINE void FM_CALL RotateDegrees(mat4*, float Degrees, vec3 Axis);
FM_INLINE void FM_CALL RotateAroundXAxisDegrees(mat4*, float Degrees);
FM_INLINE void FM_CALL RotateAroundYAxisDegrees(mat4*, float Degrees);
FM_INLINE void FM_CALL RotateAroundZAxisDegrees(mat4*, float Degrees);
FM_INLINE mat4 FM_CALL Mat4RotationRadians(float Radians, float AxisX, float AxisY, float AxisZ); 
FM_INLINE mat4 FM_CALL Mat4RotationRadians(float Radians, vec3 Axis);
FM_INLINE mat4 FM_CALL Mat4RotationAroundXAxisRadians(float Radians);
FM_INLINE mat4 FM_CALL Mat4RotationAroundYAxisRadians(float Radians);
FM_INLINE mat4 FM_CALL Mat4RotationAroundZAxisRadians(float Radians);
FM_INLINE void FM_CALL RotateRadians(mat4*, float Radians, float AxisX, float AxisY, float AxisZ); 
FM_INLINE void FM_CALL RotateRadians(mat4*, float Radians, vec3 Axis);
FM_INLINE void FM_CALL RotateAroundXAxisRadians(mat4*, float Radians);
FM_INLINE void FM_CALL RotateAroundYAxisRadians(mat4*, float Radians);
FM_INLINE void FM_CALL RotateAroundZAxisRadians(mat4*, float Radians);

FM_INLINE mat4 FM_CALL Mat4ShearXAxis(float Y, float Z); 
FM_INLINE mat4 FM_CALL Mat4ShearYAxis(float X, float Z);
FM_INLINE mat4 FM_CALL Mat4ShearZAxis(float X, float Y);
FM_INLINE mat4 FM_CALL Mat4Shear(float XY, float XZ, float YX, float YZ, float ZX, float ZY);
FM_INLINE void FM_CALL ShearXAxis(mat4*, float Y, float Z); 
FM_INLINE void FM_CALL ShearYAxis(mat4*, float X, float Z); 
FM_INLINE void FM_CALL ShearZAxis(mat4*, float X, float Y); 
FM_INLINE void FM_CALL Shear(mat4*, float XY, float XZ, float YX, float YZ, float ZX, float ZY);

mat4 Mat4Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far);
mat4 Mat4Perspective(float FOV, float AspectRatio, float near, float Far);
mat4 Mat4LookAt(vec3 Eye, vec3 At, vec3 Up = Vec3(0.f, 1.f, 0.f));

/* TODO:
reflect
matrix Hadamard
lookAt()
frustum()
project()
determinant
inverse
operator == and !=
*/

}

#endif // FAST_MATH_H

#ifndef FM_IMPLEMENTATION_ALREADY_DEFINED
#ifdef FM_IMPLEMENTATION
#define FM_IMPLEMENTATION_ALREADY_DEFINED

#include <math.h>

#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
	#include <smmintrin.h>
#endif

#define FM_ASSERT(expression) if(!expression) (*(int32_t*)0 = 0);
#define FM_ERROR() (*(int32_t*)0 = 0);

#ifdef _MSC_VER
	#pragma warning(push)
	#pragma warning(disable : 4715)
#endif

namespace fm {

/////////////////////////////////////////
// fast math internal helper functions //
/////////////////////////////////////////
namespace priv {
	FM_INLINE __m128 FM_CALL SetX(__m128 m, float x) {
		return _mm_move_ss(m, _mm_set_ss(x));
	}
	FM_INLINE __m128 FM_CALL SetY(__m128 m, float y) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(y));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 0));
		return _mm_move_ss(temp, m);
	}
	FM_INLINE __m128 FM_CALL SetZ(__m128 m, float z) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(z));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 0, 1, 0));
		return _mm_move_ss(temp, m);
	}
	FM_INLINE __m128 FM_CALL SetW(__m128 m, float w) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(w));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(0, 2, 1, 0));
		return _mm_move_ss(temp, m);
	}
	FM_INLINE float FM_CALL GetX(__m128 m) {
		return _mm_cvtss_f32(m);
	}
	FM_INLINE float FM_CALL GetY(__m128 m) {
		return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 1)));
	}
	FM_INLINE float FM_CALL GetZ(__m128 m) {
		return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 2)));
	}
	FM_INLINE float FM_CALL GetW(__m128 m) {
		return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 3)));
	}
	FM_INLINE float FM_CALL SumOfElements(__m128 m) {
		return GetX(m) + GetY(m) + GetZ(m) + GetW(m);
	}
}

////////////////////////////
// utility functions impl //
////////////////////////////
FM_INLINE float Min(float A, float B) {
	return A < B ? A : B; 
}
FM_INLINE float Max(float A, float B) {
	return A > B ? A : B;
}
FM_INLINE double Min(double A, double B) {
	return A < B ? A : B; 
}
FM_INLINE double Max(double A, double B) {
	return A > B ? A : B;
}
FM_INLINE int32_t Min(int32_t A, int32_t B) {
	return A < B ? A : B; 
}
FM_INLINE int32_t Max(int32_t A, int32_t B) {
	return A > B ? A : B;
}
FM_INLINE uint32_t Min(uint32_t A, uint32_t B) {
	return A < B ? A : B; 
}
FM_INLINE uint32_t Max(uint32_t A, uint32_t B) {
	return A > B ? A : B;
}
FM_INLINE float Abs(float A) {
	return A < 0 ? -A : A;
}
FM_INLINE double Abs(double A) {
	return A < 0 ? -A : A;
}
FM_INLINE int32_t Abs(int32_t A) {
	return A < 0 ? -A : A;
}
FM_INLINE float RadiansToDegrees(float Radians) {
	return Radians * 180.f / FM_PI32;
}
FM_INLINE double RadiansToDegrees(double Radians) {
	return Radians * 180.f / FM_PI64;
}
FM_INLINE float DegreesToRadians(float Degrees) {
	return Degrees * FM_PI32 / 180.f;
}
FM_INLINE double DegreesToRadians(double Degrees) {
	return Degrees * FM_PI64 / 180.f;
}

/////////////
// v2 impl //
/////////////
FM_INLINE v2 V2FromMemory(const float* Mem) {
	v2 R;
	R.X = Mem[0];
	R.Y = Mem[1];
	return R;
}
FM_INLINE v2 V2(float X, float Y) {
	v2 R;
	R.X = X;
	R.Y = Y;
	return R;
}
FM_INLINE v2 V2(float XY) {
	v2 R;
	R.X = R.Y = XY;
	return R;
}
FM_INLINE v2 V2() {
	v2 R{};
	return R;
}
FM_INLINE void Store(float* Mem, v2 V) {
	Mem[0] = V.X;
	Mem[1] = V.Y;
}
FM_INLINE v2 operator+(v2 A, v2 B) {
	v2 R;
	R.X = A.X + B.X;
	R.Y = A.Y + B.Y;
	return R;
}
FM_INLINE v2 operator-(v2 A, v2 B) {
	v2 R;
	R.X = A.X - B.X;
	R.Y = A.Y - B.Y;
	return R;
}
FM_INLINE v2& operator+=(v2& A, v2 B) {
	A.X += B.X;
	A.Y += B.Y;
	return A;
}
FM_INLINE v2& operator-=(v2& A, v2 B) {
	A.X -= B.X;
	A.Y -= B.Y;
	return A;
}
FM_INLINE v2 HadamardMul(v2 A, v2 B) {
	v2 R;
	R.X = A.X * B.X;
	R.Y = A.Y * B.Y;
	return R;
} 
FM_INLINE v2 HadamardDiv(v2 A, v2 B) {
	v2 R;
	R.X = A.X / B.X;
	R.Y = A.Y / B.Y;
	return R;
}
FM_INLINE v2 operator*(v2 V, float Scalar) {
	V.X *= Scalar;
	V.Y *= Scalar;
	return V;
}
FM_INLINE v2 operator*(float Scalar, v2 V) {
	return V * Scalar;
}
FM_INLINE v2 operator/(v2 V, float Scalar) {
	V.X /= Scalar;
	V.Y /= Scalar;
	return V;
}
FM_INLINE v2 operator-(v2 V) {
	V.X = -V.X;
	V.Y = -V.Y;
	return V;
} 
FM_INLINE float Dot(v2 A, v2 B) {
	return A.X * B.X + A.Y * B.Y;
} 
FM_INLINE v2 Min(v2 A, v2 B) {
	v2 R;
	R.X = Min(A.X, B.X);	
	R.Y = Min(A.Y, B.Y);	
	return R;
}
FM_INLINE v2 Max(v2 A, v2 B) {
	v2 R;
	R.X = Max(A.X, B.X);
	R.Y = Max(A.Y, B.Y);
	return R;
} 
FM_INLINE v2 Abs(v2 V) {
	v2 R;
	R.X = Abs(V.X);
	R.Y = Abs(V.Y);
	return R;
} 
FM_INLINE float SumOfElements(v2 V) {
	return V.X + V.Y;
}
FM_INLINE float Length(v2 V) {
	return sqrtf(V.X * V.X + V.Y * V.Y);
}
FM_INLINE float LengthSquared(v2 V) {
	return V.X * V.X + V.Y * V.Y;
} 
FM_INLINE v2 Normalize(v2 V) {
	return V / Length(V);
}
FM_INLINE v2 Clamp(v2 V, v2 MinV, v2 MaxV) {
	return Min(Max(V, MinV), MaxV);
}
FM_INLINE v2 Lerp(v2 A, v2 B, float T) {
	return A + (B-A)*T;
}
FM_INLINE bool operator==(v2 A, v2 B) {
	return A.X == B.X && A.Y == B.Y;
}
FM_INLINE bool operator!=(v2 A, v2 B) {
	return A.X != B.X || A.X != B.X;
}

/////////////
// v3 impl //
/////////////
FM_INLINE v3 v3::ZXY() { 
	return V3(Z, X, Y); 
}
FM_INLINE v3 V3FromMemory(float* Mem) {
	return {Mem[0], Mem[1], Mem[2]};
}
FM_INLINE v3 V3(float X, float Y, float Z) {
	return {X, Y, Z};
}
FM_INLINE v3 V3(float XYZ) {
	return {XYZ, XYZ, XYZ};
}
FM_INLINE v3 V3() {
	return {};
}
FM_INLINE void Store(float* Mem, v3 V) {
	Mem[0] = V.X;
	Mem[1] = V.Y;
	Mem[2] = V.Z;
}
FM_INLINE v3 operator+(v3 A, v3 B) {
	v3 R;
	R.X = A.X + B.X;
	R.Y = A.Y + B.Y;
	R.Z = A.Z + B.Z;
	return R;
}
FM_INLINE v3 operator-(v3 A, v3 B) {
	v3 R;
	R.X = A.X - B.X;
	R.Y = A.Y - B.Y;
	R.Z = A.Z - B.Z;
	return R;
}
FM_INLINE v3& operator+=(v3& A, v3 B) {
	A = A + B;
	return A;
}
FM_INLINE v3& operator-=(v3& A, v3 B) {
	A = A - B;
	return A;
}
FM_INLINE v3 HadamardMul(v3 A, v3 B) {
	v3 R;
	R.X = A.X * B.X;
	R.Y = A.Y * B.Y;
	R.Z = A.Z * B.Z;
	return R;
}
FM_INLINE v3 HadamardDiv(v3 A, v3 B) {
	v3 R;
	R.X = A.X / B.X;
	R.Y = A.Y / B.Y;
	R.Z = A.Z / B.Z;
	return R;
}
FM_INLINE v3 operator*(v3 V, float Scalar) {
	V.X *= Scalar;
	V.Y *= Scalar;
	V.Z *= Scalar;
	return V;
}
FM_INLINE v3 operator*(float Scalar, v3 V) {
	return V * Scalar;
}
FM_INLINE v3 operator/(v3 V, float Scalar) {
	V.X /= Scalar;
	V.Y /= Scalar;
	V.Z /= Scalar;
	return V;
}
FM_INLINE v3 operator-(v3 V) {
	V.X = -V.X;
	V.Y = -V.Y;
	V.Z = -V.Z;
	return V;
}
FM_INLINE v3 Cross(v3 A, v3 B) {
	return v3(HadamardMul(A.ZXY(), B) - HadamardMul(A, B.ZXY())).ZXY();
}
FM_INLINE float Dot(v3 A, v3 B) {
	return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
}
FM_INLINE v3 Min(v3 A, v3 B) {
	v3 R;
	R.X = Min(A.X, B.X);
	R.Y = Min(A.Y, B.Y);
	R.Z = Min(A.Z, B.Z);
	return R;
}
FM_INLINE v3 Max(v3 A, v3 B) {
	v3 R;
	R.X = Max(A.X, B.X);
	R.Y = Max(A.Y, B.Y);
	R.Z = Max(A.Z, B.Z);
	return R;
} 
FM_INLINE v3 Normalize(v3 V) {
	return V / Length(V);
}
FM_INLINE v3 Abs(v3 V) {
	V.X = Abs(V.X);
	V.Y = Abs(V.Y);
	V.Z = Abs(V.Z);
	return V;
}
FM_INLINE float SumOfElements(v3 V) {
	return V.X + V.Y + V.Z;
}
FM_INLINE float Length(v3 V) {
	return sqrtf(V.X * V.X + V.Y * V.Y + V.Z * V.Z);
}
FM_INLINE float LengthSquared(v3 V) {
	return V.X * V.X + V.Y * V.Y + V.Z * V.Z;
} 
FM_INLINE v3 Clamp(v3 V, v3 MinV, v3 MaxV) {
	return Min(Max(V, MinV), MaxV);	
} 
FM_INLINE v3 Lerp(v3 A, v3 B, float T) {
	return A + (B - A) * T;
}
FM_INLINE bool operator==(v3 A, v3 B) {
	return A.X == B.X && A.Y == B.Y && A.Z == B.Z;
}
FM_INLINE bool operator!=(v3 A, v3 B) {
	return !(A == B);
}

/////////////
// v4 impl //
/////////////
FM_INLINE v4 V4FromMemory(float* Mem) {
	v4 R;
	R[0] = Mem[0];
	R[1] = Mem[1];
	R[2] = Mem[2];
	R[3] = Mem[3];
	return R;
}
FM_INLINE v4 V4(float X, float Y, float Z, float W) {
	v4 R;
	R.X = X;
	R.Y = Y;
	R.Z = Z;
	R.W = W;
	return R;
}
FM_INLINE v4 V4(v3 XYZ, float W) {
	v4 R;
	R.X = XYZ.X;
	R.Y = XYZ.Y;
	R.Z = XYZ.Z;
	R.W = W;
	return R;
}
FM_INLINE v4 V4(float XYZW) {
	v4 R;
	R.X = XYZW;
	R.Y = XYZW;
	R.Z = XYZW;
	R.W = XYZW;
	return R;
}
FM_INLINE v4 V4() {
	return {};
}
FM_INLINE void Store(float* Mem, v4 V) {
	Mem[0] = V.X;
	Mem[1] = V.Y;
	Mem[2] = V.Z;
	Mem[3] = V.W;
}
FM_INLINE v4 operator+(v4 A, v4 B) {
	v4 R;
	R.X = A.X + B.X;
	R.Y = A.Y + B.Y;
	R.Z = A.Z + B.Z;
	R.W = A.W + B.W;
	return R;
} 
FM_INLINE v4 operator-(v4 A, v4 B) {
	v4 R;
	R.X = A.X - B.X;
	R.Y = A.Y - B.Y;
	R.Z = A.Z - B.Z;
	R.W = A.W - B.W;
	return R;
}
FM_INLINE v4& operator+=(v4& A, v4 B) {
	A = A + B;
	return A;
}
FM_INLINE v4& operator-=(v4& A, v4 B) {
	A = A - B;
	return A;
}
FM_INLINE v4 HadamardMul(v4 A, v4 B) {
	v4 R;
	R.X = A.X * B.X;
	R.Y = A.Y * B.Y;
	R.Z = A.Z * B.Z;
	R.W = A.W * B.W;
	return R;
}
FM_INLINE v4 HadamardDiv(v4 A, v4 B) {
	v4 R;
	R.X = A.X / B.X;
	R.Y = A.Y / B.Y;
	R.Z = A.Z / B.Z;
	R.W = A.W / B.W;
	return R;
}
FM_INLINE v4 operator*(v4 V, float  Scalar) {
	V.X *= Scalar;
	V.Y *= Scalar;
	V.Z *= Scalar;
	V.W *= Scalar;
	return V;
}
FM_INLINE v4 operator*(float Scalar, v4 V) {
	return V * Scalar;
}
FM_INLINE v4 operator/(v4 V, float Scalar) {
	V.X /= Scalar;
	V.Y /= Scalar;
	V.Z /= Scalar;
	V.W /= Scalar;
	return V;
}
FM_INLINE v4 operator-(v4 V) {
	V.X = -V.X;
	V.Y = -V.Y;
	V.Z = -V.Z;
	V.W = -V.W;
	return V;
} 
FM_INLINE float Dot(v4 A, v4 B) {
	return A.X * B.X + A.Y * B.Y + A.Z * B.Z + A.W * B.W;
} 
FM_INLINE v4 Min(v4 A, v4 B) {
	v4 R;
	R.X = Min(A.X, B.X);
	R.Y = Min(A.Y, B.Y);
	R.Z = Min(A.Z, B.Z);
	R.W = Min(A.W, B.W);
	return R;
} 
FM_INLINE v4 Max(v4 A, v4 B) {
	v4 R;
	R.X = Max(A.X, B.X);
	R.Y = Max(A.Y, B.Y);
	R.Z = Max(A.Z, B.Z);
	R.W = Max(A.W, B.W);
	return R;
}
FM_INLINE v4 Normalize(v4 V) {
	return V / Length(V);
}
FM_INLINE v4 Abs(v4 V) {
	V.X = Abs(V.X);
	V.Y = Abs(V.Y);
	V.Z = Abs(V.Z);
	V.W = Abs(V.W);
	return V;
}
FM_INLINE float SumOfElements(v4 V) {
	return V.X + V.Y + V.Z + V.W;
}
FM_INLINE float Length(v4 V) {
	return sqrtf(Dot(V, V));
}
FM_INLINE float LengthSquared(v4 V) {
	return Dot(V, V);
} 
FM_INLINE v4 Clamp(v4 V, v4 MinV, v4 MaxV) {
	return Min(Max(V, MinV), MaxV);
} 
FM_INLINE v4 Lerp(v4 A, v4 B, float T) {
	return A + (B - A) * T;
}
FM_INLINE bool operator==(v4 A, v4 B) {
	return A.X == B.X && A.Y == B.Y && A.Z == B.Z && A.W == B.W;
} 
FM_INLINE bool operator!=(v4 A, v4 B) {
	return !(A == B);
} 

///////////////
// vec2 impl //
///////////////
FM_INLINE vec2 FM_CALL Vec2FromMemory(const float* V) {
	vec2 R;
	R.M = _mm_set_ps(0.f, 0.f, V[1], V[0]); 
	return R;
} 
FM_INLINE vec2 FM_CALL Vec2(float X, float Y) {
	vec2 R;
	R.M = _mm_set_ps(0.f, 0.f, Y, X); 
	return R;
}
FM_INLINE vec2 FM_CALL Vec2(float XY) {
	vec2 R;
	R.M = _mm_set1_ps(XY); 
	return R;
}
FM_INLINE vec2 FM_CALL Vec2(__m128 M) {
	vec2 R;
	R.M = M;
	return R;
}
FM_INLINE vec2 FM_CALL Vec2() {
	vec2 R;
	R.M = _mm_setzero_ps(); 
	return R;
}
FM_INLINE float FM_CALL vec2::X() const { 
	return priv::GetX(M); 
}
FM_INLINE float FM_CALL vec2::Y() const {
	return priv::GetY(M); 
}
FM_INLINE vec2 FM_CALL vec2::YX() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE vec2 FM_CALL vec2::XX() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 0))); 
}
FM_INLINE vec2 FM_CALL vec2::YY() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE void FM_CALL vec2::SetX(float X) {
	M = priv::SetX(M, X); 
}
FM_INLINE void FM_CALL vec2::SetY(float Y) { 
	M = priv::SetY(M, Y);
}
FM_INLINE void FM_CALL vec2::AddX(float X) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INLINE void FM_CALL vec2::AddY(float Y) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INLINE void FM_CALL vec2::SubX(float X) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INLINE void FM_CALL vec2::SubY(float Y) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INLINE void FM_CALL vec2::MulX(float X) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INLINE void FM_CALL vec2::MulY(float Y) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INLINE void FM_CALL vec2::DivX(float X) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INLINE void FM_CALL vec2::DivY(float Y) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INLINE void FM_CALL Store(float* Mem, vec2 V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
} 
FM_INLINE vec2 FM_CALL operator+(vec2 A, vec2 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A; 
}
FM_INLINE vec2 FM_CALL operator-(vec2 A, vec2 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A; 
}
FM_INLINE vec2& FM_CALL operator+=(vec2& A, vec2 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A; 
}
FM_INLINE vec2& FM_CALL operator-=(vec2& A, vec2 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A; 
}
FM_INLINE vec2 FM_CALL HadamardMul(vec2 A, vec2 B) {
	A.M = _mm_mul_ps(A.M, B.M);
	return A;
}
FM_INLINE vec2 FM_CALL HadamardDiv(vec2 A, vec2 B) {
	A.M = _mm_div_ps(A.M, B.M);
	return A; 
}
FM_INLINE vec2 FM_CALL operator*(vec2 V, float Scalar) {
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar)); 
	return V; 
}
FM_INLINE vec2 FM_CALL operator*(float Scalar, vec2 V) { 
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar));
	return V; 
}
FM_INLINE vec2 FM_CALL operator/(vec2 V, float Scalar) {
	V.M = _mm_div_ps(V.M, _mm_set1_ps(Scalar));
	return V; 
}
FM_INLINE vec2 FM_CALL operator-(vec2 V) {
	V.M = _mm_sub_ps(_mm_setzero_ps(), V.M);
	return V;
}
FM_INLINE float FM_CALL Dot(vec2 A, vec2 B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_INLINE vec2 FM_CALL Min(vec2 A, vec2 B) {
	A.M = _mm_min_ps(A.M, B.M);
	return A;
}
FM_INLINE vec2 FM_CALL Max(vec2 A, vec2 B) {
	A.M = _mm_max_ps(A.M, B.M);
	return A;
}
FM_INLINE vec2 FM_CALL Abs(vec2 V) {
	__m128 SignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000)); 
	V.M = _mm_andnot_ps(SignMask, V.M);
	return V;
}
FM_INLINE float FM_CALL SumOfElements(vec2 V) {
	return V.X() + V.Y();
}
FM_INLINE float FM_CALL Length(vec2 V) {
	return sqrtf(Dot(V, V));
}
FM_INLINE float FM_CALL LengthSquared(vec2 V) {
	return Dot(V, V);
}
FM_INLINE vec2 FM_CALL Normalize(vec2 V) {
	return V / Length(V);
}
FM_INLINE vec2 FM_CALL Clamp(vec2 V, vec2 MinV, vec2 MaxV) {
	return Min(Max(V, MinV), MaxV);
}
FM_INLINE vec2 FM_CALL Lerp(vec2 A, vec2 B, float T) {
	return A + (B-A)*T;
}
FM_INLINE bool FM_CALL operator==(vec2 A, vec2 B) {
	vec2 EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_INLINE bool FM_CALL operator!=(vec2 A, vec2 B) {
	vec2 EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
}
FM_INLINE vec2 FM_CALL EqualsMask(vec2 A, vec2 B) {
	A.M = _mm_cmpeq_ps(A.M, B.M);
	return A;
}
FM_INLINE vec2 FM_CALL GreaterMask(vec2 A, vec2 B) {
	A.M = _mm_cmpgt_ps(A.M, B.M);
	return A;
}
FM_INLINE vec2 FM_CALL GreaterOrEqualMask(vec2 A, vec2 B) {
	A.M = _mm_cmpge_ps(A.M, B.M);
	return A;
}
FM_INLINE vec2 FM_CALL LesserMask(vec2 A, vec2 B) {
	A.M = _mm_cmplt_ps(A.M, B.M);
	return A;
}
FM_INLINE vec2 FM_CALL LesserOrEqualMask(vec2 A, vec2 B) {
	A.M = _mm_cmple_ps(A.M, B.M);
	return A;
}

//////////////
// vec2d impl //
//////////////
FM_INLINE vec2d FM_CALL Vec2dFromMemory(const double* V) {
	vec2d R;
	R.M = _mm_set_pd(V[1], V[0]); 
	return R;
}
FM_INLINE vec2d FM_CALL Vec2d(double X, double Y) {
	vec2d R;
	R.M = _mm_set_pd(Y, X); 
	return R;
}
FM_INLINE vec2d FM_CALL Vec2d(double A) {
	vec2d R;
	R.M = _mm_set1_pd(A);
	return R;
}
FM_INLINE vec2d FM_CALL Vec2d(__m128d M) {
	vec2d R;
	R.M = M;
	return R;
}
FM_INLINE vec2d FM_CALL Vec2d() {
	vec2d R;
	R.M = _mm_setzero_pd(); 
	return R;
}
FM_INLINE double FM_CALL vec2d::X() const {
	return _mm_cvtsd_f64(M);
}
FM_INLINE double FM_CALL vec2d::Y() const { 
	return _mm_cvtsd_f64(_mm_shuffle_pd(M, M, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE vec2d FM_CALL vec2d::YX() const {
	return Vec2d(_mm_shuffle_pd(M, M, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE vec2d FM_CALL vec2d::XX() const {
	return Vec2d(_mm_unpacklo_pd(M, M));
}
FM_INLINE vec2d FM_CALL vec2d::YY() const {
	return Vec2d(_mm_unpackhi_pd(M, M));
}
FM_INLINE void FM_CALL vec2d::AddX(double X) {
	M = _mm_add_pd(M, _mm_set_pd(0.f, X));
}
FM_INLINE void FM_CALL vec2d::AddY(double Y) {
	M = _mm_add_pd(M, _mm_set_pd(Y, 0.f));
}
FM_INLINE void FM_CALL vec2d::SubX(double X) {
	M = _mm_sub_pd(M, _mm_set_pd(0.f, X));
}
FM_INLINE void FM_CALL vec2d::SubY(double Y) {
	M = _mm_sub_pd(M, _mm_set_pd(Y, 0.f));
}
FM_INLINE void FM_CALL vec2d::MulX(double X) {
	M = _mm_mul_pd(M, _mm_set_pd(1.f, X));
}
FM_INLINE void FM_CALL vec2d::MulY(double Y) {
	M = _mm_mul_pd(M, _mm_set_pd(Y, 1.f));
}
FM_INLINE void FM_CALL vec2d::DivX(double X) {
	M = _mm_div_pd(M, _mm_set_pd(1.f, X));
}
FM_INLINE void FM_CALL vec2d::DivY(double Y) {
	M = _mm_div_pd(M, _mm_set_pd(Y, 1.f));
}
FM_INLINE void FM_CALL Store(double* Mem, vec2d V) { 
	_mm_storeu_pd(Mem, V.M); 
} 
FM_INLINE void FM_CALL Store16ByteAligned(double* Mem, vec2d V) {
	_mm_store_pd(Mem, V.M); 
}
FM_INLINE void FM_CALL vec2d::SetX(double X) {
	M = _mm_move_sd(M, _mm_set_sd(X)); 
}
FM_INLINE void FM_CALL vec2d::SetY(double Y) {
	M = _mm_unpacklo_pd(M, _mm_set_sd(Y)); 
}
FM_INLINE vec2d FM_CALL operator+(vec2d A, vec2d B) {
	A.M = _mm_add_pd(A.M, B.M);
	return A; 
}
FM_INLINE vec2d FM_CALL operator-(vec2d A, vec2d B) {
	A.M = _mm_sub_pd(A.M, B.M);
	return A; 
}
FM_INLINE vec2d& FM_CALL operator+=(vec2d& A, vec2d B) {
	A.M = _mm_add_pd(A.M, B.M);
	return A; 
}
FM_INLINE vec2d& FM_CALL operator-=(vec2d& A, vec2d B) {
	A.M = _mm_sub_pd(A.M, B.M);
	return A; 
}
FM_INLINE vec2d FM_CALL HadamardMul(vec2d A, vec2d B) {
	A.M = _mm_mul_pd(A.M, B.M);
	return A; 
}
FM_INLINE vec2d FM_CALL HadamardDiv(vec2d A, vec2d B) {
	A.M = _mm_div_pd(A.M, B.M);
	return A; 
}
FM_INLINE vec2d FM_CALL operator*(vec2d V, double Scalar) {
	V.M = _mm_mul_pd(V.M, _mm_set1_pd(Scalar));
	return V; 
}
FM_INLINE vec2d FM_CALL operator*(double Scalar, vec2d V) {
	V.M = _mm_mul_pd(V.M, _mm_set1_pd(Scalar));
	return V; 
} 
FM_INLINE vec2d FM_CALL operator/(vec2d V, double Scalar) {
	V.M = _mm_div_pd(V.M, _mm_set1_pd(Scalar));
	return V; 
}
FM_INLINE vec2d FM_CALL operator-(vec2d V) {
	V.M = _mm_sub_pd(_mm_setzero_pd(), V.M);
	return V;
}
FM_INLINE double FM_CALL Dot(vec2d A, vec2d B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_INLINE vec2d FM_CALL Min(vec2d A, vec2d B) {
	A.M = _mm_min_pd(A.M, B.M);
	return A;
}
FM_INLINE vec2d FM_CALL Max(vec2d A, vec2d B) {
	A.M = _mm_max_pd(A.M, B.M);
	return A;
}
FM_INLINE vec2d FM_CALL Abs(vec2d V) {
	__m128d SignBits = _mm_castsi128_pd(_mm_set1_epi32(0x80000000));
	V.M = _mm_andnot_pd(SignBits, V.M);
	return V;
}
FM_INLINE double FM_CALL SumOfElements(vec2d V) {
	return V.X() + V.Y();
}
FM_INLINE double FM_CALL Length(vec2d V) {
	return sqrt(Dot(V, V));
}
FM_INLINE double FM_CALL LengthSquared(vec2d V) {
	return Dot(V, V);
}
FM_INLINE vec2d FM_CALL Normalize(vec2d V) {
	return V / Length(V);
}
FM_INLINE vec2d FM_CALL Clamp(vec2d V, vec2d MinV, vec2d MaxV) {
	return Min(Max(V, MinV), MaxV);
} 
FM_INLINE vec2d FM_CALL Lerp(vec2d A, vec2d B, double T) {
	return A + (B-A)*T;
}
FM_INLINE bool FM_CALL operator==(vec2d A, vec2d B) {
	vec2d EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_INLINE bool FM_CALL operator!=(vec2d A, vec2d B) {
	vec2d EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
}
FM_INLINE vec2d FM_CALL EqualsMask(vec2d A, vec2d B) {
	A.M = _mm_cmpeq_pd(A.M, B.M);
	return A;
}
FM_INLINE vec2d FM_CALL GreaterMask(vec2d A, vec2d B) {
	A.M = _mm_cmpgt_pd(A.M, B.M);
	return A;
}
FM_INLINE vec2d FM_CALL GreaterOrEqualMask(vec2d A, vec2d B) {
	A.M = _mm_cmpge_pd(A.M, B.M);
	return A;
}
FM_INLINE vec2d FM_CALL LesserMask(vec2d A, vec2d B) {
	A.M = _mm_cmplt_pd(A.M, B.M);
	return A;
}
FM_INLINE vec2d FM_CALL LesserOrEqualMask(vec2d A, vec2d B) {
	A.M = _mm_cmple_pd(A.M, B.M);
	return A;
}

////////////////
// vec2i impl //
////////////////
FM_INLINE vec2i FM_CALL Vec2iFromMemory(const int32_t* V) {
	vec2i R;
	R.M = _mm_set_epi32(0, 0, V[1], V[0]); 
	return R;
}
FM_INLINE vec2i FM_CALL Vec2i(int32_t X, int32_t Y) {
	vec2i R;
	R.M = _mm_set_epi32(0, 0, Y, X); 
	return R;
}
FM_INLINE vec2i FM_CALL Vec2i(int32_t A) { 
	vec2i R;
	R.M = _mm_set1_epi32(A); 
	return R;
}
FM_INLINE vec2i FM_CALL Vec2i(__m128i M) {
	vec2i R;
	R.M = M;
	return R;
}
FM_INLINE vec2i FM_CALL Vec2i() {
	vec2i R;
	R.M = _mm_setzero_si128();
	return R;
}
FM_INLINE int32_t FM_CALL vec2i::X() const { 
	return _mm_cvtsi128_si32(M); 
} 
FM_INLINE int32_t FM_CALL vec2i::Y() const {
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(M, _MM_SHUFFLE(1, 1, 1, 1))); 
} 
FM_INLINE vec2i FM_CALL vec2i::YX() const {
	return Vec2i(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 0, 1)));
}
FM_INLINE vec2i FM_CALL vec2i::XX() const {
	return Vec2i(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 0, 0)));
}
FM_INLINE vec2i FM_CALL vec2i::YY() const {
	return Vec2i(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 1, 1)));
}
FM_INLINE void FM_CALL vec2i::AddX(int32_t X) {
	M = _mm_add_epi32(M, _mm_set_epi32(0, 0, 0, X));
}
FM_INLINE void FM_CALL vec2i::AddY(int32_t Y) {
	M = _mm_add_epi32(M, _mm_set_epi32(0, 0, Y, 0));
}
FM_INLINE void FM_CALL vec2i::SubX(int32_t X) {
	M = _mm_sub_epi32(M, _mm_set_epi32(0, 0, 0, X));
}
FM_INLINE void FM_CALL vec2i::SubY(int32_t Y) {
	M = _mm_sub_epi32(M, _mm_set_epi32(0, 0, Y, 0));
}
FM_INLINE void FM_CALL vec2i::DivX(int32_t XDivider) {
	SetX(X() / XDivider);
}
FM_INLINE void FM_CALL vec2i::DivY(int32_t YDivider) {
	SetY(Y() / YDivider);
}
FM_INLINE void FM_CALL Store(int32_t* Mem, vec2i V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
} 
FM_INLINE vec2i FM_CALL operator+(vec2i A, vec2i B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_INLINE vec2i FM_CALL operator-(vec2i A, vec2i B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_INLINE vec2i& FM_CALL operator+=(vec2i& A, vec2i B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_INLINE vec2i& FM_CALL operator-=(vec2i& A, vec2i B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_INLINE vec2i FM_CALL operator-(vec2i V) {
	V.M = _mm_sub_epi32(_mm_setzero_si128(), V.M);
	return V;
}
FM_INLINE int32_t FM_CALL SumOfElements(vec2i V) {
	return V.X() + V.Y();
}
FM_INLINE int32_t FM_CALL Length(vec2i V) {
	int32_t X = V.X();
	int32_t Y = V.Y();
	return (int32_t)sqrt(X*X + Y*Y);
}
FM_INLINE int32_t FM_CALL LengthSquared(vec2i V) {
	int32_t X = V.X();
	int32_t Y = V.Y();
	return X*X + Y*Y;
}
FM_INLINE bool FM_CALL operator==(vec2i A, vec2i B) {
	vec2i EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_INLINE bool FM_CALL operator!=(vec2i A, vec2i B) {
	vec2i EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
} 
FM_INLINE vec2i FM_CALL EqualsMask(vec2i A, vec2i B) {
	A.M = _mm_cmpeq_epi32(A.M, B.M);
	return A;
}
FM_INLINE vec2i FM_CALL GreaterMask(vec2i A, vec2i B) {
	A.M = _mm_cmpgt_epi32(A.M, B.M);
	return A;
}
FM_INLINE vec2i FM_CALL GreaterOrEqualMask(vec2i A, vec2i B) {
	__m128i GT = _mm_cmpgt_epi32(A.M, B.M);
	__m128i EQ = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(GT, EQ);
	return A;
}
FM_INLINE vec2i FM_CALL LesserMask(vec2i A, vec2i B) {
	A.M = _mm_cmplt_epi32(A.M, B.M);
	return A;
}
FM_INLINE vec2i FM_CALL LesserOrEqualMask(vec2i A, vec2i B) {
	__m128i LT = _mm_cmplt_epi32(A.M, B.M);
	__m128i EQ = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(LT, EQ);
	return A;
}
#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INLINE void FM_CALL vec2i::SetX(int32_t X) {
	M = _mm_insert_epi32(M, X, 0);
}
FM_INLINE void FM_CALL vec2i::SetY(int32_t Y) {
	M = _mm_insert_epi32(M, Y, 1);
}
FM_INLINE vec2i FM_CALL operator*(vec2i V, int32_t Scalar) {
	V.M = _mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar));
	return V; 
}
FM_INLINE vec2i FM_CALL operator*(int32_t Scalar, vec2i V) {
	V.M =_mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar)); 
	return V; 
}
FM_INLINE void FM_CALL vec2i::MulX(int32_t X) {
	M = _mm_mullo_epi32(M, _mm_set_epi32(1, 1, 1, X));
}
FM_INLINE void FM_CALL vec2i::MulY(int32_t Y) {
	M = _mm_mullo_epi32(M, _mm_set_epi32(1, 1, Y, 1));
}
FM_INLINE vec2i FM_CALL HadamardMul(vec2i A, vec2i B) {
	A.M = _mm_mullo_epi32(A.M, B.M); 
	return A; 
}
FM_INLINE vec2i FM_CALL Min(vec2i A, vec2i B) {
	A.M = _mm_min_epi32(A.M, B.M);
	return A;
}
FM_INLINE vec2i FM_CALL Max(vec2i A, vec2i B) {
	A.M = _mm_max_epi32(A.M, B.M);
	return A;
}
FM_INLINE vec2i FM_CALL Abs(vec2i V) {
	V.M = _mm_abs_epi32(V.M);
	return V;
}
FM_INLINE vec2i FM_CALL Clamp(vec2i V, vec2i MinV, vec2i MaxV) {
	return Min(Max(V, MinV), MaxV);
} 
#else // SSE 2 implementations 
FM_INLINE void FM_CALL vec2i::SetX(int32_t X) {
	int32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, M);
	Arr[0] = X;
	M = _mm_load_si128((__m128i*)Arr);
}
FM_INLINE void FM_CALL vec2i::SetY(int32_t Y) {
	int32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, M);
	Arr[1] = Y;
	M = _mm_load_si128((__m128i*)Arr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_INLINE vec2i FM_CALL HadamardMul(vec2i A, vec2i B) {
	int32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = AArr[0] * BArr[0]; 
	AArr[1] = AArr[1] * BArr[1]; 
	return Vec2i(AArr);
}
FM_INLINE vec2i FM_CALL operator*(vec2i V, int32_t Scalar) {
	int32_t VArr[4];
	_mm_store_si128((__m128i*)VArr, V.M);
	VArr[0] *= Scalar;
	VArr[1] *= Scalar;
	return Vec2i(VArr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_INLINE vec2i FM_CALL operator*(int32_t Scalar, vec2i v) {
	return V * Scalar; 
}
FM_INLINE vec2i FM_CALL Min(vec2i A, vec2i B) {
	int32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Min(AArr[0], BArr[0]);
	AArr[1] = Min(AArr[1], BArr[1]);
	return Vec2i(AArr);
}
FM_INLINE vec2i FM_CALL Max(vec2i A, vec2i B) {
	int32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Max(AArr[0], BArr[0]);
	AArr[1] = Max(AArr[1], BArr[1]);
	return Vec2i(AArr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_INLINE vec2i FM_CALL abs(vec2i v) {
	int32_t VArr[4];
	_mm_store_si128((__m128i*)VArr, V.M);
	VArr[0] = abs(VArr[0]);
	VArr[1] = abs(VArr[1]);
	return Vec2i(VArr);
}
FM_INLINE void FM_CALL vec2i::MulX(int32_t XMultiplier) {
	SetX(X() * XMultiplier);
}
FM_INLINE void FM_CALL vec2i::MulY(int32_t YMultiplier) {
	SetY(Y() * YMultiplier);
}
#endif

////////////////
// vec2u impl //
////////////////
FM_INLINE vec2u FM_CALL Vec2uFromMemory(const uint32_t* V) {
	vec2u R;
	R.M = _mm_set_epi32(0, 0, V[1], V[0]); 
	return R;
}
FM_INLINE vec2u FM_CALL Vec2u(uint32_t x, uint32_t y) {
	vec2u R;
	R.M = _mm_set_epi32(0, 0, y, x); 
	return R;
}
FM_INLINE vec2u FM_CALL Vec2u(uint32_t a) {
	vec2u R;
	R.M = _mm_set1_epi32(a); 
	return R;
} 
FM_INLINE vec2u FM_CALL Vec2u(__m128i m) {
	vec2u R;
	R.M = m;
	return R;
} 
FM_INLINE vec2u FM_CALL Vec2u() {
	vec2u R;
	R.M = _mm_setzero_si128(); 
	return R;
}
FM_INLINE uint32_t FM_CALL vec2u::X() const {
	return (uint32_t)_mm_cvtsi128_si32(M); 
} 
FM_INLINE uint32_t FM_CALL vec2u::Y() const { 
	return (uint32_t)_mm_cvtsi128_si32(_mm_shuffle_epi32(M, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE vec2u FM_CALL vec2u::YX() const { 
	return Vec2u(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 0, 1))); 
}
FM_INLINE vec2u FM_CALL vec2u::XX() const { 
	return Vec2u(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 0, 0)));
}
FM_INLINE vec2u FM_CALL vec2u::YY() const { 
	return Vec2u(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 1, 1)));
}
FM_INLINE void FM_CALL vec2u::AddX(uint32_t X) {
	M = _mm_add_epi32(M, _mm_set_epi32(0, 0, 0, X));
}
FM_INLINE void FM_CALL vec2u::AddY(uint32_t Y) {
	M = _mm_add_epi32(M, _mm_set_epi32(0, 0, Y, 0));
}
FM_INLINE void FM_CALL vec2u::SubX(uint32_t X) {
	M = _mm_sub_epi32(M, _mm_set_epi32(0, 0, 0, X));
}
FM_INLINE void FM_CALL vec2u::SubY(uint32_t Y) {
	M = _mm_sub_epi32(M, _mm_set_epi32(0, 0, Y, 0));
}
FM_INLINE void FM_CALL vec2u::DivX(uint32_t XDivider) {
	SetX(X() / XDivider);
}
FM_INLINE void FM_CALL vec2u::DivY(uint32_t YDivider) {
	SetY(Y() / YDivider);
}
FM_INLINE void FM_CALL Store(uint32_t* Mem, vec2u V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
} 
FM_INLINE vec2u FM_CALL operator+(vec2u A, vec2u B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_INLINE vec2u FM_CALL operator-(vec2u A, vec2u B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_INLINE vec2u& FM_CALL operator+=(vec2u& A, vec2u B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_INLINE vec2u& FM_CALL operator-=(vec2u& A, vec2u B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_INLINE uint32_t FM_CALL SumOfElements(vec2u V) {
	return V.X() + V.Y();
}
FM_INLINE uint32_t FM_CALL Length(vec2u V) {
	uint32_t X = V.X();
	uint32_t Y = V.Y();
	return (uint32_t)sqrt(X*X + Y*Y);
}
FM_INLINE uint32_t FM_CALL LengthSquared(vec2u V) {
	uint32_t X = V.X();
	uint32_t Y = V.Y();
	return X*X + Y*Y;	
}
FM_INLINE vec2u FM_CALL Clamp(vec2u V, vec2u MinV, vec2u MaxV) {
	return Min(Max(V, MinV), MaxV);
} 
FM_INLINE bool FM_CALL operator==(vec2u A, vec2u B) {
	vec2u EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_INLINE bool FM_CALL operator!=(vec2u A, vec2u B) {
	vec2u EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
} 
FM_INLINE vec2u FM_CALL EqualsMask(vec2u A, vec2u B) {
	A.M = _mm_cmpeq_epi32(A.M, B.M);
	return A;
}
FM_INLINE vec2u FM_CALL GreaterMask(vec2u A, vec2u B) {
	A.M = _mm_cmpgt_epi32(A.M, B.M);
	return A;
}
FM_INLINE vec2u FM_CALL GreaterOrEqualMask(vec2u A, vec2u B) {
	__m128i gt = _mm_cmpgt_epi32(A.M, B.M);
	__m128i eq = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(gt, eq);
	return A;
}
FM_INLINE vec2u FM_CALL LesserMask(vec2u A, vec2u B) {
	A.M = _mm_cmplt_epi32(A.M, B.M);
	return A;
}
FM_INLINE vec2u FM_CALL LesserOrEqualMask(vec2u A, vec2u B) {
	__m128i lt = _mm_cmplt_epi32(A.M, B.M);
	__m128i eq = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(lt, eq);
	return A;
}
FM_INLINE void FM_CALL vec2u::MulX(uint32_t XMultiplier) {
	SetX(X() * XMultiplier);
}
FM_INLINE void FM_CALL vec2u::MulY(uint32_t YMultiplier) {
	SetY(Y() * YMultiplier);
}
#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INLINE void FM_CALL vec2u::SetX(uint32_t X) {
	M = _mm_insert_epi32(M, (int32_t)X, 0);
}
FM_INLINE void FM_CALL vec2u::SetY(uint32_t Y) {
	M = _mm_insert_epi32(M, (int32_t)Y, 1);
}
FM_INLINE vec2u FM_CALL operator*(vec2u V, uint32_t Scalar) {
	V.M = _mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar)); 
	return V; 
}
FM_INLINE vec2u FM_CALL operator*(uint32_t Scalar, vec2u V) {
	V.M =_mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar));
	return V; 
}
FM_INLINE vec2u FM_CALL HadamardMul(vec2u A, vec2u B) {
	A.M = _mm_mullo_epi32(A.M, B.M);
	return A; 
}
FM_INLINE vec2u FM_CALL Min(vec2u A, vec2u B) {
	A.M = _mm_min_epu32(A.M, B.M);
	return A;
}
FM_INLINE vec2u FM_CALL Max(vec2u A, vec2u B) {
	A.M = _mm_max_epu32(A.M, B.M);
	return A;
}
#else // SSE 2 implementations
FM_INLINE void FM_CALL vec2u::SetX(uint32_t x) {
	uint32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, m);
	Arr[0] = x;
	m = _mm_load_si128((__m128i*)Arr);
}
FM_INLINE void FM_CALL vec2u::SetY(uint32_t y) {
	uint32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, m);
	Arr[1] = y;
	M = _mm_load_si128((__m128i*)Arr);
	// TODO: This code is repeated. Make utility function!
}
FM_INLINE vec2u FM_CALL HadamardMul(vec2u A, vec2u B) {
	uint32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = AArr[0] * BArr[0]; 
	AArr[1] = AArr[1] * BArr[1]; 
	return Vec2u(AArr);
}
FM_INLINE vec2u FM_CALL operator*(vec2u V, uint32_t Scalar) {
	uint32_t VArr[4];
	_mm_store_si128((__m128i*)VArr, V.M);
	VArr[0] *= Scalar;
	VArr[1] *= Scalar;
	return Vec2u(VArr);
}
FM_INLINE vec2u FM_CALL operator*(uint32_t Scalar, vec2u V) {
	return V * Scalar;
}
FM_INLINE vec2u FM_CALL Min(vec2u A, vec2u B) {
	uint32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Min(AArr[0], BArr[0]);
	AArr[1] = Min(AArr[1], BArr[1]);
	return Vec2u(AArr);
}
FM_INLINE vec2u FM_CALL Max(vec2u A, vec2u B) {
	uint32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Max(AArr[0], BArr[0]);
	AArr[1] = Max(AArr[1], BArr[1]);
	return Vec2u(AArr);
}
#endif

///////////////
// vec3 impl //
///////////////
FM_INLINE vec3 FM_CALL Vec3FromMemory(float* V) {
	vec3 R;
	R.M = _mm_set_ps(0, V[2], V[1], V[0]);
	return R;
}
FM_INLINE vec3 FM_CALL Vec3(float X, float Y, float Z) {
	vec3 R;
	R.M = _mm_set_ps(0, Z, Y, X); 
	return R;
}
FM_INLINE vec3 FM_CALL Vec3(float A) {
	vec3 R;
	R.M = _mm_set1_ps(A);
	return R;
}
FM_INLINE vec3 FM_CALL Vec3(__m128 M) {
	vec3 R;
	R.M = M;
	return R;
}
FM_INLINE vec3 FM_CALL Vec3() {
	vec3 R;
	R.M = _mm_setzero_ps();
	return R;
}
FM_INLINE void FM_CALL vec3::SetX(float X) {
	M = priv::SetX(M, X); 
}
FM_INLINE void FM_CALL vec3::SetY(float Y) {
	M = priv::SetY(M, Y);
}
FM_INLINE void FM_CALL vec3::SetZ(float Z) {
	M = priv::SetZ(M, Z);
}
FM_INLINE void FM_CALL vec3::AddX(float X) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INLINE void FM_CALL vec3::AddY(float Y) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INLINE void FM_CALL vec3::AddZ(float Z) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, Z, 0.f, 0.f));
}
FM_INLINE void FM_CALL vec3::SubX(float X) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INLINE void FM_CALL vec3::SubY(float Y) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INLINE void FM_CALL vec3::SubZ(float Z) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, Z, 0.f, 0.f));
}
FM_INLINE void FM_CALL vec3::MulX(float X) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INLINE void FM_CALL vec3::MulY(float Y) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INLINE void FM_CALL vec3::MulZ(float Z) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, Z, 1.f, 1.f));
}
FM_INLINE void FM_CALL vec3::DivX(float X) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INLINE void FM_CALL vec3::DivY(float Y) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INLINE void FM_CALL vec3::DivZ(float Z) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, Z, 1.f, 1.f));
}
FM_INLINE void FM_CALL Store(float* Mem, vec3 V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
	Mem[2] = V.Z();
}
FM_INLINE float FM_CALL vec3::X() const {
	return priv::GetX(M); 
}
FM_INLINE float FM_CALL vec3::Y() const {
	return priv::GetY(M); 
}
FM_INLINE float FM_CALL vec3::Z() const {
	return priv::GetZ(M); 
}
#ifndef FM_EXCLUDE_SWIZZLES
FM_INLINE vec2 FM_CALL vec3::XY() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 0)));
}
FM_INLINE vec2 FM_CALL vec3::YX() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 1)));
}
FM_INLINE vec2 FM_CALL vec3::YZ() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 1)));
}
FM_INLINE vec2 FM_CALL vec3::ZY() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 2)));
}
FM_INLINE vec2 FM_CALL vec3::XZ() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 0)));
}
FM_INLINE vec2 FM_CALL vec3::ZX() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 2)));
}
FM_INLINE vec2 FM_CALL vec3::XX() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 0)));
}
FM_INLINE vec2 FM_CALL vec3::YY() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 1)));
}
FM_INLINE vec2 FM_CALL vec3::ZZ() const {
	return Vec2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 2)));
}
FM_INLINE vec3 FM_CALL vec3::XYZ() const {
	return *this;
}
FM_INLINE vec3 FM_CALL vec3::YZX() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 1)));
}
FM_INLINE vec3 FM_CALL vec3::ZXY() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 0, 2)));
}
FM_INLINE vec3 FM_CALL vec3::ZYX() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 2)));
}
FM_INLINE vec3 FM_CALL vec3::XZY() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 2, 0)));
}
FM_INLINE vec3 FM_CALL vec3::YXZ() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 0, 1)));
}
FM_INLINE vec3 FM_CALL vec3::XXY() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 0, 0)));
}
FM_INLINE vec3 FM_CALL vec3::XXZ() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 0, 0)));
}
FM_INLINE vec3 FM_CALL vec3::YYX() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 1)));
}
FM_INLINE vec3 FM_CALL vec3::YYZ() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 1, 1)));
}
FM_INLINE vec3 FM_CALL vec3::ZZX() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 2)));
}
FM_INLINE vec3 FM_CALL vec3::ZZY() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 2, 2)));
}
FM_INLINE vec3 FM_CALL vec3::YXX() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 1)));
}
FM_INLINE vec3 FM_CALL vec3::ZXX() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 2)));
}
FM_INLINE vec3 FM_CALL vec3::XYY() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 1, 0)));
}
FM_INLINE vec3 FM_CALL vec3::ZYY() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 1, 2)));
}
FM_INLINE vec3 FM_CALL vec3::XZZ() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 2, 0)));
}
FM_INLINE vec3 FM_CALL vec3::YZZ() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 2, 1)));
}
FM_INLINE vec3 FM_CALL vec3::XYX() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 0)));
}
FM_INLINE vec3 FM_CALL vec3::XZX() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 0)));
}
FM_INLINE vec3 FM_CALL vec3::YXY() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 0, 1)));
}
FM_INLINE vec3 FM_CALL vec3::YZY() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 2, 1)));
}
FM_INLINE vec3 FM_CALL vec3::ZXZ() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 0, 2)));
}
FM_INLINE vec3 FM_CALL vec3::ZYZ() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 1, 2)));
}
FM_INLINE vec3 FM_CALL vec3::XXX() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 0)));
}
FM_INLINE vec3 FM_CALL vec3::YYY() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 1, 1)));
}
FM_INLINE vec3 FM_CALL vec3::ZZZ() const {
	return Vec3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 2, 2)));
}
#endif
FM_INLINE vec3 FM_CALL operator+(vec3 A, vec3 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3 FM_CALL operator-(vec3 A, vec3 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3& FM_CALL operator+=(vec3& A, vec3 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3& FM_CALL operator-=(vec3& A, vec3 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3 FM_CALL HadamardMul(vec3 A, vec3 B) {
	A.M = _mm_mul_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3 FM_CALL HadamardDiv(vec3 A, vec3 B) {
	A.M = _mm_div_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3 FM_CALL operator*(vec3 V, float Scalar) {
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_INLINE vec3 FM_CALL operator*(float Scalar, vec3 V) {
	return V * Scalar;
}
FM_INLINE vec3 FM_CALL operator/(vec3 V, float Scalar) {
	V.M = _mm_div_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_INLINE vec3 FM_CALL operator-(vec3 V) {
	V.M = _mm_sub_ps(_mm_setzero_ps(), V.M);
	return V;
}
FM_INLINE vec3 FM_CALL Cross(vec3 A, vec3 B) {
	return vec3(HadamardMul(A.ZXY(), B) - HadamardMul(A, B.ZXY())).ZXY(); 
}
FM_INLINE float FM_CALL Dot(vec3 A, vec3 B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_INLINE vec3 FM_CALL Min(vec3 A, vec3 B) {
	A.M = _mm_min_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3 FM_CALL Max(vec3 A, vec3 B) {
	A.M = _mm_max_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3 FM_CALL Normalize(vec3 V) {
	return V / Length(V);
}
FM_INLINE vec3 FM_CALL Abs(vec3 V) {
	__m128 SignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	V.M = _mm_andnot_ps(SignMask, V.M);
	return V;
}
FM_INLINE float FM_CALL SumOfElements(vec3 V) {
	return V.X() + V.Y() + V.Z();
}
FM_INLINE float FM_CALL Length(vec3 V) {
	return sqrtf(Dot(V, V));
}
FM_INLINE float FM_CALL LengthSquared(vec3 V) {
	return Dot(V, V);
}
FM_INLINE vec3 FM_CALL Clamp(vec3 V, vec3 MinV, vec3 MaxV) {
	return Min(Max(V, MinV), MaxV);
}
FM_INLINE vec3 FM_CALL Lerp(vec3 A, vec3 B, float T) {
	return A + (B-A)*T;
} 
FM_INLINE bool FM_CALL operator==(vec3 A, vec3 B) {
	vec3 EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y() && EqMask.Z();
} 
FM_INLINE bool FM_CALL operator!=(vec3 A, vec3 B) {
	vec3 EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y() && EqMask.Z());
}
FM_INLINE vec3 FM_CALL EqualsMask(vec3 A, vec3 B) {
	A.M = _mm_cmpeq_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3 FM_CALL GreaterMask(vec3 A, vec3 B) {
	A.M = _mm_cmpgt_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3 FM_CALL GreaterOrEqualMask(vec3 A, vec3 B) {
	A.M = _mm_cmpge_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3 FM_CALL LesserMask(vec3 A, vec3 B) {
	A.M = _mm_cmplt_ps(A.M, B.M);
	return A;
}
FM_INLINE vec3 FM_CALL LesserOrEqualMask(vec3 A, vec3 B) {
	A.M = _mm_cmple_ps(A.M, B.M);
	return A;
}

///////////////
// vec4 impl //
///////////////
FM_INLINE vec4 FM_CALL Vec4FromMemory(const float* V) {
	vec4 R;
	R.M = _mm_set_ps(V[3], V[2], V[1], V[0]);	
	return R;
} 
FM_INLINE vec4 FM_CALL Vec4(vec3 V, float W) {
	vec4 R;
	V.M = _mm_shuffle_ps(V.M, V.M, _MM_SHUFFLE(2, 1, 0, 0));
	R.M = _mm_move_ss(V.M, _mm_set_ss(W));
	R.M = _mm_shuffle_ps(R.M, R.M, _MM_SHUFFLE(0, 3, 2, 1));
	return R;
}
FM_INLINE vec4 FM_CALL Vec4(float X, float Y, float Z, float W) {
	vec4 R;
	R.M = _mm_set_ps(W, Z, Y, X);
	return R;
}
FM_INLINE vec4 FM_CALL Vec4(float A) {
	vec4 R;
	R.M = _mm_set1_ps(A);
	return R;
}
FM_INLINE vec4 FM_CALL Vec4(__m128 M) {
	vec4 R;
	R.M = M;
	return R;
} 
FM_INLINE vec4 FM_CALL Vec4() {
	vec4 R;
	R.M = _mm_setzero_ps();
	return R;
}
FM_INLINE void FM_CALL vec4::SetX(float X) {
	M = priv::SetX(M, X); 
}
FM_INLINE void FM_CALL vec4::SetY(float Y) {
	M = priv::SetY(M, Y);
} 
FM_INLINE void FM_CALL vec4::SetZ(float Z) {
	M = priv::SetZ(M, Z);
} 
FM_INLINE void FM_CALL vec4::SetW(float W) {
	M = priv::SetW(M, W);
} 
FM_INLINE void FM_CALL vec4::AddX(float X) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INLINE void FM_CALL vec4::AddY(float Y) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INLINE void FM_CALL vec4::AddZ(float Z) {
	M = _mm_add_ps(M, _mm_set_ps(0.f, Z, 0.f, 0.f));
}
FM_INLINE void FM_CALL vec4::AddW(float W) {
	M = _mm_add_ps(M, _mm_set_ps(W, 0.f, 0.f, 0.f));
}
FM_INLINE void FM_CALL vec4::SubX(float X) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, 0.f, X));
}
FM_INLINE void FM_CALL vec4::SubY(float Y) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, 0.f, Y, 0.f));
}
FM_INLINE void FM_CALL vec4::SubZ(float Z) {
	M = _mm_sub_ps(M, _mm_set_ps(0.f, Z, 0.f, 0.f));
}
FM_INLINE void FM_CALL vec4::SubW(float W) {
	M = _mm_sub_ps(M, _mm_set_ps(W, 0.f, 0.f, 0.f));
}
FM_INLINE void FM_CALL vec4::MulX(float X) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INLINE void FM_CALL vec4::MulY(float Y) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INLINE void FM_CALL vec4::MulZ(float Z) {
	M = _mm_mul_ps(M, _mm_set_ps(1.f, Z, 1.f, 1.f));
}
FM_INLINE void FM_CALL vec4::MulW(float W) {
	M = _mm_mul_ps(M, _mm_set_ps(W, 1.f, 1.f, 1.f));
}
FM_INLINE void FM_CALL vec4::DivX(float X) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, 1.f, X));
}
FM_INLINE void FM_CALL vec4::DivY(float Y) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, 1.f, Y, 1.f));
}
FM_INLINE void FM_CALL vec4::DivZ(float Z) {
	M = _mm_div_ps(M, _mm_set_ps(1.f, Z, 1.f, 1.f));
}
FM_INLINE void FM_CALL vec4::DivW(float W) {
	M = _mm_div_ps(M, _mm_set_ps(W, 1.f, 1.f, 1.f));
}
FM_INLINE float FM_CALL vec4::X() const {
	return _mm_cvtss_f32(M);
}
FM_INLINE float FM_CALL vec4::Y() const {
	return priv::GetY(M); 
}
FM_INLINE float FM_CALL vec4::Z() const {
	return priv::GetZ(M); 
}
FM_INLINE float FM_CALL vec4::W() const {
	return priv::GetW(M); 
}
FM_INLINE void FM_CALL Store(float* Mem, vec4 V) {
	_mm_storeu_ps(Mem, V.M);
}
FM_INLINE void FM_CALL Store16ByteAligned(float* Mem, vec4 V) {
	_mm_store_ps(Mem, V.M);
}
FM_INLINE vec4 FM_CALL operator+(vec4 A, vec4 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4 FM_CALL operator-(vec4 A, vec4 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4& FM_CALL operator+=(vec4& A, vec4 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4& FM_CALL operator-=(vec4& A, vec4 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4 FM_CALL HadamardMul(vec4 A, vec4 B) {
	A.M = _mm_mul_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4 FM_CALL HadamardDiv(vec4 A, vec4 B) {
	A.M = _mm_div_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4 FM_CALL operator*(vec4 V, float Scalar) {
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_INLINE vec4 FM_CALL operator*(float Scalar, vec4 V) {
	return V * Scalar;
}
FM_INLINE vec4 FM_CALL operator/(vec4 V, float Scalar) {
	V.M = _mm_div_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_INLINE vec4 FM_CALL operator-(vec4 V) {
	V.M = _mm_sub_ps(_mm_setzero_ps(), V.M);
	return V;
}
FM_INLINE float FM_CALL Dot(vec4 A, vec4 B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_INLINE vec4 FM_CALL Min(vec4 A, vec4 B) {
	A.M = _mm_min_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4 FM_CALL Max(vec4 A, vec4 B) {
	A.M = _mm_max_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4 FM_CALL Abs(vec4 V) {
	__m128 SignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	V.M = _mm_andnot_ps(SignMask, V.M);
	return V;
}
FM_INLINE float FM_CALL SumOfElements(vec4 V) {
	return V.X() + V.Y() + V.Z() + V.W();
}
FM_INLINE float FM_CALL Length(vec4 V) {
	return sqrtf(Dot(V, V));
}
FM_INLINE float FM_CALL LengthSquared(vec4 V) {
	return Dot(V, V);
}
FM_INLINE vec4 FM_CALL Normalize(vec4 V) {
	return V / Length(V);
}
FM_INLINE vec4 FM_CALL Clamp(vec4 V, vec4 MinV, vec4 MaxV) {
	return Min(Max(V, MinV), MaxV);
}
FM_INLINE vec4 FM_CALL Lerp(vec4 A, vec4 B, float T) {
	return A + (B-A)*T;
} 
FM_INLINE bool FM_CALL operator==(vec4 A, vec4 B) {
	vec4 EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y() && EqMask.Z() && EqMask.W();
} 
FM_INLINE bool FM_CALL operator!=(vec4 A, vec4 B) {
	return !(A == B);
}
FM_INLINE vec4 FM_CALL EqualsMask(vec4 A, vec4 B) {
	A.M = _mm_cmpeq_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4 FM_CALL GreaterMask(vec4 A, vec4 B) {
	A.M = _mm_cmpgt_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4 FM_CALL GreaterOrEqualMask(vec4 A, vec4 B) {
	A.M = _mm_cmpge_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4 FM_CALL LesserMask(vec4 A, vec4 B) {
	A.M = _mm_cmplt_ps(A.M, B.M);
	return A;
}
FM_INLINE vec4 FM_CALL LesserOrEqualMask(vec4 A, vec4 B) {
	A.M = _mm_cmple_ps(A.M, B.M);
	return A;
}

///////////////
// mat4 impl //
///////////////
FM_INLINE vec4 FM_CALL mat4::GetColumn(uint32_t Index) {
	return Vec4(Columns[Index]);
}
FM_INLINE void FM_CALL mat4::SetColumn(uint32_t Index, vec4 Col) {
	Columns[Index] = Col.M;
}
FM_INLINE void FM_CALL mat4::SetColumn(uint32_t Index, float X, float Y, float Z, float W) {
	Columns[Index] = _mm_set_ps(W, Z, Y, X);
}
FM_INLINE void FM_CALL mat4::SwapColumns(uint32_t Col1Index, uint32_t Col2Index) {
	__m128 Temp = Columns[Col1Index];
	Columns[Col1Index] = Columns[Col2Index];
	Columns[Col2Index] = Temp;
}
vec4 FM_CALL mat4::GetRow(uint32_t Index) {
	switch(Index)
	{
		case 0: {
			return Vec4(
				priv::GetX(Columns[0]), priv::GetX(Columns[1]),
				priv::GetX(Columns[2]), priv::GetX(Columns[3]));
		} break;
		
		case 1: {
			return Vec4(
				priv::GetY(Columns[0]), priv::GetY(Columns[1]),
				priv::GetY(Columns[2]), priv::GetY(Columns[3]));
		} break;
	
		case 2: {
			return Vec4(
				priv::GetZ(Columns[0]), priv::GetZ(Columns[1]),
				priv::GetZ(Columns[2]), priv::GetZ(Columns[3]));
		} break;
	
		case 3: {
			return Vec4(
				priv::GetW(Columns[0]), priv::GetW(Columns[1]),
				priv::GetW(Columns[2]), priv::GetW(Columns[3]));
		} break;
		
		default: {
			FM_ERROR(); // Index has to be in range from 0 to 3
		}
	}
}
void FM_CALL mat4::SetRow(uint32_t Index, vec4 Row) {
	switch(Index)
	{
		case 0: {
				Columns[0] = priv::SetX(Columns[0], Row.X());
				Columns[1] = priv::SetX(Columns[1], Row.Y());
				Columns[2] = priv::SetX(Columns[2], Row.Z());
				Columns[3] = priv::SetX(Columns[3], Row.W());
		} break;
	
		case 1: {
				Columns[0] = priv::SetY(Columns[0], Row.X());
				Columns[1] = priv::SetY(Columns[1], Row.Y());
				Columns[2] = priv::SetY(Columns[2], Row.Z());
				Columns[3] = priv::SetY(Columns[3], Row.W());
		} break;
	
		case 2: {
				Columns[0] = priv::SetZ(Columns[0], Row.X());
				Columns[1] = priv::SetZ(Columns[1], Row.Y());
				Columns[2] = priv::SetZ(Columns[2], Row.Z());
				Columns[3] = priv::SetZ(Columns[3], Row.W());
		} break;
	
		case 3: {
				Columns[0] = priv::SetW(Columns[0], Row.X());
				Columns[1] = priv::SetW(Columns[1], Row.Y());
				Columns[2] = priv::SetW(Columns[2], Row.Z());
				Columns[3] = priv::SetW(Columns[3], Row.W());
		} break;
	
		default: {
			FM_ERROR(); // Index has to be in range from 0 to 3
		}
	}	
}
FM_INLINE void FM_CALL mat4::SetRow(uint32_t Index, float X, float Y, float Z, float W) {
	SetRow(Index, Vec4(X, Y, Z, W));
}
FM_INLINE void FM_CALL mat4::SwapRows(uint32_t Row1Index, uint32_t Row2Index) {
	vec4 Row1 = GetRow(Row1Index);
	vec4 Row2 = GetRow(Row2Index);
	SetRow(Row2Index, Row1);
	SetRow(Row1Index, Row2);
}
FM_INLINE vec4 FM_CALL mat4::GetMainDiagonal() {
	vec4 R;
	R.SetX(priv::GetX(Columns[0]));
	R.SetY(priv::GetY(Columns[1]));
	R.SetZ(priv::GetZ(Columns[2]));
	R.SetW(priv::GetW(Columns[3]));
	return R;
}
FM_INLINE void FM_CALL mat4::SetMainDiagonal(float x, float y, float z, float w) {
	Columns[0] = priv::SetX(Columns[0], x);
	Columns[1] = priv::SetY(Columns[1], y);
	Columns[2] = priv::SetZ(Columns[2], z);
	Columns[3] = priv::SetW(Columns[3], w);
}
FM_INLINE void FM_CALL mat4::SetMainDiagonal(vec4 V) {
	SetMainDiagonal(V.X(), V.Y(), V.Z(), V.W());
}
FM_INLINE mat4 FM_CALL Mat4FromColumnMajorMemory(float* Mem) {
	mat4 R;
	for(int32_t i = 0; i < 4; ++i)
		R.Columns[i] = _mm_load_ps(Mem + i*4);
	return R;
}
FM_INLINE mat4 FM_CALL Mat4() {
	mat4 R;
	R.Columns[0] = _mm_setzero_ps();
	R.Columns[1] = _mm_setzero_ps();
	R.Columns[2] = _mm_setzero_ps();
	R.Columns[3] = _mm_setzero_ps();
	return R;
}
FM_INLINE mat4 FM_CALL Mat4Identity() {
	return Mat4Diagonal(1.f);
}
FM_INLINE mat4 FM_CALL Mat4Diagonal(float Diag) {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Diag, 0.f, 0.f, 0.f);
	R.Columns[1] = _mm_setr_ps(0.f, Diag, 0.f, 0.f);
	R.Columns[2] = _mm_setr_ps(0.f, 0.f, Diag, 0.f);
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, Diag);
	return R;
}
FM_INLINE mat4 FM_CALL Mat4Diagonal(float DiagX, float DiagY, float DiagZ, float DiagW) {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(DiagX, 0.f, 0.f, 0.f);
	R.Columns[1] = _mm_setr_ps(0.f, DiagY, 0.f, 0.f);
	R.Columns[2] = _mm_setr_ps(0.f, 0.f, DiagZ, 0.f);
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, DiagW);
	return R;
}
FM_INLINE mat4 FM_CALL Mat4Diagonal(vec4 Diag) {
	// TODO: What is going on with Diag.X() Diag.Y()... 
	mat4 R;
	float* V = (float*)(&Diag);
	R.Columns[0] = _mm_set_ps(0.f, 0.f, 0.f, V[0]);
	R.Columns[1] = _mm_set_ps(0.f, 0.f, V[1], 0.f);
	R.Columns[2] = _mm_set_ps(0.f, V[2], 0.f, 0.f);
	R.Columns[3] = _mm_set_ps(V[3], 0.f, 0.f, 0.f);
	return R;
}
FM_INLINE mat4 FM_CALL Mat4FromColumns(vec4 Col1, vec4 Col2, vec4 Col3, vec4 Col4) {
	mat4 R;
	R.Columns[0] = Col1.M;
	R.Columns[1] = Col2.M;
	R.Columns[2] = Col3.M;
	R.Columns[3] = Col4.M;
	return R;
}
FM_INLINE mat4 FM_CALL Mat4FromColumns(vec3 Col1, vec3 Col2, vec3 Col3, vec3 Col4) {
	mat4 R;
	R.Columns[0] = Col1.M;
	R.Columns[1] = Col2.M;
	R.Columns[2] = Col3.M;
	R.Columns[3] = Col4.M;
	R.SetRow(3, 0.f, 0.f, 0.f, 1.f);
	return R;
}
FM_INLINE mat4 FM_CALL Mat4FromColumns(
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
FM_INLINE mat4 FM_CALL Mat4FromRows(vec4 Row1, vec4 Row2, vec4 Row3, vec4 Row4) {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Row1.X(), Row2.X(), Row3.X(), Row4.X());
	R.Columns[1] = _mm_setr_ps(Row1.Y(), Row2.Y(), Row3.Y(), Row4.Y());
	R.Columns[2] = _mm_setr_ps(Row1.Z(), Row2.Z(), Row3.Z(), Row4.Z());
	R.Columns[3] = _mm_setr_ps(Row1.W(), Row2.W(), Row3.W(), Row4.W());
	return R;
}
FM_INLINE mat4 FM_CALL Mat4FromRows(vec3 Row1, vec3 Row2, vec3 Row3, vec3 Row4) {
	mat4 R;
	R.Columns[0] = _mm_setr_ps(Row1.X(), Row2.X(), Row3.X(), Row4.X());
	R.Columns[1] = _mm_setr_ps(Row1.Y(), Row2.Y(), Row3.Y(), Row4.Y());
	R.Columns[2] = _mm_setr_ps(Row1.Z(), Row2.Z(), Row3.Z(), Row4.Z());
	R.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, 1.f);
	return R;
}
FM_INLINE mat4 FM_CALL Mat4FromRows(
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
FM_INLINE void FM_CALL Store(float* Mem, mat4 Mat) {
	for(int32_t Col = 0; Col < 4; ++Col)
		_mm_storeu_ps(Mem + Col*4, Mat.Columns[Col]);
}
FM_INLINE void FM_CALL Store16ByteAligned(float* Mem, mat4 Mat) {
	for(int32_t Col = 0; Col < 4; ++Col)
		_mm_store_ps(Mem + Col*4, Mat.Columns[Col]);
}
FM_INLINE mat4 FM_CALL operator+(mat4 A, mat4 B) {
	for(int32_t Col = 0; Col < 4; ++Col)
		A.Columns[Col] = _mm_add_ps(A.Columns[Col], B.Columns[Col]);
	return A;
}
FM_INLINE mat4 FM_CALL operator-(mat4 A, mat4 B) {
	for(int32_t Col = 0; Col < 4; ++Col)
		A.Columns[Col] = _mm_sub_ps(A.Columns[Col], B.Columns[Col]);
	return A;
}
FM_INLINE mat4 FM_CALL operator*(mat4 A, mat4 B) {
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
FM_INLINE vec4 FM_CALL operator*(mat4 M, vec4 V) {
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
FM_INLINE mat4 FM_CALL operator*(mat4 M, float Scalar) {
	__m128 ScalarM = _mm_set1_ps(Scalar);
	for(uint32_t Col = 0; Col < 4; ++Col)
		M.Columns[Col] = _mm_mul_ps(M.Columns[Col], ScalarM);
	return M;
}
FM_INLINE mat4 FM_CALL operator*(float Scalar, mat4 M) {
	return M * Scalar;
}
FM_INLINE mat4 FM_CALL operator/(mat4 M, float Scalar) {
	__m128 ScalarM = _mm_set1_ps(Scalar);
	for(uint32_t Col = 0; Col < 4; ++Col)
		M.Columns[Col] = _mm_div_ps(M.Columns[Col], ScalarM);
	return M;
}
FM_INLINE void FM_CALL Transpose(mat4* M) {
	_MM_TRANSPOSE4_PS(M->Columns[0], M->Columns[1], M->Columns[2], M->Columns[3]);
}
FM_INLINE mat4 FM_CALL Transpose(mat4 M) {
	_MM_TRANSPOSE4_PS(M.Columns[0], M.Columns[1], M.Columns[2], M.Columns[3]);
	return M;
}
FM_INLINE mat4 FM_CALL Mat4Translation(float X, float Y, float Z) {
	return Mat4FromRows(
		1.f, 0.f, 0.f, X,
		0.f, 1.f, 0.f, Y,
		0.f, 0.f, 1.f, Z,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL Mat4Translation(vec3 Translation) {
	return Mat4FromRows(
		1.f, 0.f, 0.f, Translation.X(),
		0.f, 1.f, 0.f, Translation.Y(),
		0.f, 0.f, 1.f, Translation.Z(),
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE void FM_CALL Translate(mat4* M, float X, float Y, float Z) {
	M->Columns[3] = _mm_add_ps(M->Columns[3], _mm_set_ps(0.f, Z, Y, X));
}
FM_INLINE void FM_CALL Translate(mat4* M, vec3 Translation) {
	M->Columns[3] = _mm_add_ps(M->Columns[3], Translation.M);
}
FM_INLINE mat4 FM_CALL Mat4Scale(float Scalar) {
	return Mat4Diagonal(Scalar, Scalar, Scalar, 1.f);
} 
FM_INLINE mat4 FM_CALL Mat4Scale(float ScalarX, float ScalarY, float ScalarZ) {
	return Mat4Diagonal(ScalarX, ScalarY, ScalarZ, 1.f);
} 
FM_INLINE mat4 FM_CALL Mat4Scale(vec3 Scalar) {
	return Mat4Diagonal(Scalar.X(), Scalar.Y(), Scalar.Z(), 1.f); 
}
FM_INLINE void FM_CALL Scale(mat4* M, float Scalar) {
	Scale(M, Scalar, Scalar, Scalar);
}
FM_INLINE void FM_CALL Scale(mat4* M, float X, float Y, float Z) {
	vec4 MainDiag = M->GetMainDiagonal();
	vec4 ScalarVec = Vec4(X, Y, Z, 1.f);
	MainDiag = HadamardMul(MainDiag, ScalarVec);
	M->SetMainDiagonal(MainDiag);
}
FM_INLINE void FM_CALL Scale(mat4* M, vec3 Scalar) {
	vec4 MainDiag = M->GetMainDiagonal();
	MainDiag.M = _mm_mul_ps(MainDiag.M, Scalar.M);
	MainDiag.M = priv::SetW(MainDiag.M, 1.f);
	M->SetMainDiagonal(MainDiag);
}
FM_INLINE mat4 FM_CALL Mat4RotationDegrees(float Degrees, float AxisX, float AxisY, float AxisZ) {
	float R = DegreesToRadians(Degrees);
	return Mat4RotationRadians(R, AxisX, AxisY, AxisZ);
} 
FM_INLINE mat4 FM_CALL Mat4RotationDegrees(float Degrees, vec3 Axis) {
	float R = DegreesToRadians(Degrees);
	return Mat4RotationRadians(R, Axis);
}
FM_INLINE mat4 FM_CALL Mat4RotationAroundXAxisDegrees(float Degrees) {
	float R = DegreesToRadians(Degrees);
	return Mat4RotationAroundXAxisRadians(R);
}
FM_INLINE mat4 FM_CALL Mat4RotationAroundYAxisDegrees(float Degrees) {
	float R = DegreesToRadians(Degrees);
	return Mat4RotationAroundYAxisRadians(R);
}
FM_INLINE mat4 FM_CALL Mat4RotationAroundZAxisDegrees(float Degrees) {
	float R = DegreesToRadians(Degrees);
	return Mat4RotationAroundZAxisRadians(R);
}
FM_INLINE void FM_CALL RotateDegrees(mat4* M, float Degrees, float AxisX, float AxisY, float AxisZ) {
	float R = DegreesToRadians(Degrees);
	RotateRadians(M, R, AxisX, AxisY, AxisZ);
} 
FM_INLINE void FM_CALL RotateDegrees(mat4* M, float Degrees, vec3 Axis) {
	float R = DegreesToRadians(Degrees);
	RotateRadians(M, R, Axis);
}
FM_INLINE void FM_CALL RotateAroundXAxisDegrees(mat4* M, float Degrees) {
	float R = DegreesToRadians(Degrees);
	RotateAroundXAxisRadians(M, R);
}
FM_INLINE void FM_CALL RotateAroundYAxisDegrees(mat4* M, float Degrees) {
	float R = DegreesToRadians(Degrees);
	RotateAroundYAxisRadians(M, R);
}
FM_INLINE void FM_CALL RotateAroundZAxisDegrees(mat4* M, float Degrees) {
	float R = DegreesToRadians(Degrees);
	RotateAroundZAxisRadians(M, R);
}
FM_INLINE mat4 FM_CALL Mat4RotationRadians(float Radians, float AxisX, float AxisY, float AxisZ) {
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
FM_INLINE mat4 FM_CALL Mat4RotationRadians(float Radians, vec3 Axis) {
	return Mat4RotationRadians(Radians, Axis.X(), Axis.Y(), Axis.Z());
}
FM_INLINE mat4 FM_CALL Mat4RotationAroundXAxisRadians(float R) {
	return Mat4FromRows(
		1.f, 0.f, 0.f, 0.f,
		0.f, cosf(R), -sinf(R), 0.f,
		0.f, sinf(R), cosf(R), 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL Mat4RotationAroundYAxisRadians(float R) {
	return Mat4FromRows(
		cosf(R), 0.f, sinf(R), 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sinf(R), 0.f, cosf(R), 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL Mat4RotationAroundZAxisRadians(float R) {
	return Mat4FromRows(
		cosf(R), -sinf(R), 0.f, 0.f,
		sinf(R), cosf(R), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE void FM_CALL RotateRadians(mat4* M, float Radians, float AxisX, float AxisY, float AxisZ) {
	*M = *M * Mat4RotationRadians(Radians, AxisX, AxisY, AxisZ);
}
FM_INLINE void FM_CALL RotateRadians(mat4* M, float Radians, vec3 Axis) {
	*M = *M * Mat4RotationRadians(Radians, Axis);
}
FM_INLINE void FM_CALL RotateAroundXAxisRadians(mat4* M, float Radians) {
	*M = *M * Mat4RotationAroundXAxisRadians(Radians);	
}
FM_INLINE void FM_CALL RotateAroundYAxisRadians(mat4* M, float Radians) {
	*M = *M * Mat4RotationAroundYAxisRadians(Radians);
}
FM_INLINE void FM_CALL RotateAroundZAxisRadians(mat4* M, float Radians) {
	*M = *M * Mat4RotationAroundZAxisRadians(Radians);
}
FM_INLINE mat4 FM_CALL Mat4ShearXAxis(float Y, float Z) {
	return Mat4FromRows(
		1.f, 0.f, 0.f, 0.f,
		Y,   1.f, 0.f, 0.f,
		Z,   0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL Mat4ShearYAxis(float X, float Z) {
	return Mat4FromRows(
		1.f, X,   0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, Z,   1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL Mat4ShearZAxis(float X, float Y) {
	return Mat4FromRows(
		1.f, 0.f, X,   0.f,
		0.f, 1.f, Y,   0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL Mat4Shear(float XY, float XZ, float YX, float YZ, float ZX, float ZY) {
	return Mat4FromRows(
		1.f, YX, ZX, 0.f,
		XY, 1.f, ZY, 0.f,
		XZ, YZ, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE void FM_CALL ShearXAxis(mat4* M, float Y, float Z) {
	*M = *M * Mat4ShearXAxis(Y, Z);
}
FM_INLINE void FM_CALL ShearYAxis(mat4* M, float X, float Z) {
	*M = *M * Mat4ShearYAxis(X, Z);
} 
FM_INLINE void FM_CALL ShearZAxis(mat4* M, float X, float Y) {
	*M = *M * Mat4ShearZAxis(X, Y);
} 
FM_INLINE void FM_CALL Shear(mat4* M, float XY, float XZ, float YX, float YZ, float ZX, float ZY) {
	*M = *M * Mat4Shear(XY, XZ, YX, YZ, ZX, ZY);
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
mat4 Mat4Perspective(float FOV, float AspectRatio, float Near, float Far) {
	float Cotangent = 1.f / tanf(FOV * FM_PI32 / 360.f);
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

} // !namespace fm

#ifdef _MSC_VER
	#pragma warning(pop)
#endif

#endif // FM_IMPLEMENTATION

#ifdef _MSC_VER
	__pragma(warning(pop))
#endif

#endif // FM_IMPLEMENTATION_ALREADY_DEFINED

