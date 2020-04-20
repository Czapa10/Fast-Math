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

struct alignas(16) v2
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

	FM_INLINE v2 FM_CALL YX() const;
	FM_INLINE v2 FM_CALL XX() const;
	FM_INLINE v2 FM_CALL YY() const;

#ifndef FM_EXCLUDE_TEX_COORD_SWIZZLES
	FM_INLINE v2 FM_CALL VU() const { return YX(); }
	FM_INLINE v2 FM_CALL UU() const { return XX(); }
	FM_INLINE v2 FM_CALL VV() const { return YY(); }
#endif
};

FM_INLINE v2 FM_CALL V2FromMemory(const float*); 
FM_INLINE v2 FM_CALL V2(float X, float Y);
FM_INLINE v2 FM_CALL V2(float XY);
FM_INLINE v2 FM_CALL V2(__m128);
FM_INLINE v2 FM_CALL V2();

FM_INLINE void FM_CALL Store(float* Mem, v2 V);

FM_INLINE float* Ptr(const v2& V) { return (float*)(&V); }
FM_INLINE float* PtrY(const v2& V) { return (float*)(&V) + 1; }

FM_INLINE v2 FM_CALL operator+(v2, v2);
FM_INLINE v2 FM_CALL operator-(v2, v2);
FM_INLINE v2& FM_CALL operator+=(v2&, v2);
FM_INLINE v2& FM_CALL operator-=(v2&, v2);
FM_INLINE v2 FM_CALL HadamardMul(v2, v2);
FM_INLINE v2 FM_CALL HadamardDiv(v2, v2);
FM_INLINE v2 FM_CALL operator*(v2 V, float Scalar);
FM_INLINE v2 FM_CALL operator*(float Scalar, v2 V);
FM_INLINE v2 FM_CALL operator/(v2 V, float Scalar); 
FM_INLINE v2 FM_CALL operator-(v2); 
FM_INLINE float FM_CALL Dot(v2, v2); 
FM_INLINE v2 FM_CALL Min(v2, v2); 
FM_INLINE v2 FM_CALL Max(v2, v2); 
FM_INLINE v2 FM_CALL Abs(v2); 
FM_INLINE float FM_CALL SumOfElements(v2);
FM_INLINE float FM_CALL Length(v2);
FM_INLINE float FM_CALL LengthSquared(v2); 
FM_INLINE v2 FM_CALL Normalize(v2);
FM_INLINE v2 FM_CALL Clamp(v2 V, v2 Min, v2 Max);
FM_INLINE v2 FM_CALL Lerp(v2 A, v2 B, float T);

FM_INLINE bool FM_CALL operator==(v2, v2); 
FM_INLINE bool FM_CALL operator!=(v2, v2); 
FM_INLINE v2 FM_CALL EqualsMask(v2, v2);
FM_INLINE v2 FM_CALL GreaterMask(v2, v2);
FM_INLINE v2 FM_CALL GreaterOrEqualMask(v2, v2);
FM_INLINE v2 FM_CALL LesserMask(v2, v2);
FM_INLINE v2 FM_CALL LesserOrEqualMask(v2, v2);

struct alignas(16) v2d
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

	FM_INLINE v2d FM_CALL YX() const;
	FM_INLINE v2d FM_CALL XX() const;
	FM_INLINE v2d FM_CALL YY() const;

	FM_INLINE v2d FM_CALL VU() const { return YX(); }
	FM_INLINE v2d FM_CALL UU() const { return XX(); }
	FM_INLINE v2d FM_CALL VV() const { return YY(); }
};

FM_INLINE v2d FM_CALL V2dFromMemory(const double*);
FM_INLINE v2d FM_CALL V2d(double X, double Y);
FM_INLINE v2d FM_CALL V2d(double XY);
FM_INLINE v2d FM_CALL V2d (__m128d);
FM_INLINE v2d FM_CALL V2d();

FM_INLINE void FM_CALL Store(double* Mem, v2d V);
FM_INLINE void FM_CALL Store16ByteAligned(double* Mem, v2d V);

FM_INLINE double* Ptr(const v2d& V) { return (double*)(&V); }
FM_INLINE double* PtrY(const v2d& V) { return (double*)(&V) + 1; }

FM_INLINE v2d FM_CALL operator+(v2d, v2d); 
FM_INLINE v2d FM_CALL operator-(v2d, v2d);
FM_INLINE v2d& FM_CALL operator+=(v2d&, v2d);
FM_INLINE v2d& FM_CALL operator-=(v2d&, v2d);
FM_INLINE v2d FM_CALL HadamardMul(v2d, v2d);
FM_INLINE v2d FM_CALL HadamardDiv(v2d, v2d);
FM_INLINE v2d FM_CALL operator*(v2d V, double Scalar);
FM_INLINE v2d FM_CALL operator*(double Scalar, v2d V);
FM_INLINE v2d FM_CALL operator/(v2d V, double Scalar);
FM_INLINE v2d FM_CALL operator-(v2d); 
FM_INLINE double FM_CALL Dot(v2d, v2d); 
FM_INLINE v2d FM_CALL Min(v2d, v2d); 
FM_INLINE v2d FM_CALL Max(v2d, v2d); 
FM_INLINE v2d FM_CALL Normalize(v2d);
FM_INLINE v2d FM_CALL Abs(v2d);
FM_INLINE double FM_CALL SumOfElements(v2d);
FM_INLINE double FM_CALL Length(v2d);
FM_INLINE double FM_CALL LengthSquared(v2d); 
FM_INLINE v2d FM_CALL Clamp(v2d V, v2d Min, v2d Max); 
FM_INLINE v2d FM_CALL Lerp(v2d A, v2d B, double T);

FM_INLINE bool FM_CALL operator==(v2d, v2d); 
FM_INLINE bool FM_CALL operator!=(v2d, v2d); 
FM_INLINE v2d FM_CALL EqualsMask(v2d, v2d);
FM_INLINE v2d FM_CALL GreaterMask(v2d, v2d);
FM_INLINE v2d FM_CALL GreaterOrEqualMask(v2d, v2d);
FM_INLINE v2d FM_CALL LesserMask(v2d, v2d);
FM_INLINE v2d FM_CALL LesserOrEqualMask(v2d, v2d);

struct alignas(16) v2i
{
	__m128i M;

	FM_INLINE int32_t FM_CALL X() const;
	FM_INLINE int32_t FM_CALL U() const { return X(); }
	FM_INLINE int32_t FM_CALL Left() const { return X(); }
	FM_INLINE int32_t FM_CALL Width() const { return X(); }

	FM_INLINE int32_t FM_CALL Y() const;
	FM_INLINE int32_t FM_CALL V() const { return Y(); }
	FM_INLINE int32_t FM_CALL Top() const { return Y(); }
	FM_INLINE int32_t FM_CALL Height() const { return Y(); }

	FM_INLINE v2i FM_CALL YX() const;
	FM_INLINE v2i FM_CALL XX() const;
	FM_INLINE v2i FM_CALL YY() const;

	FM_INLINE v2i FM_CALL VU() const { return YX(); }
	FM_INLINE v2i FM_CALL UU() const { return XX(); }
	FM_INLINE v2i FM_CALL VV() const { return YY(); }

	FM_INLINE void FM_CALL SetX(int32_t);
	FM_INLINE void FM_CALL SetY(int32_t);
};
FM_INLINE v2i FM_CALL V2iFromMemory(const int32_t*);
FM_INLINE v2i FM_CALL V2i(int32_t X, int32_t Y);
FM_INLINE v2i FM_CALL V2i(int32_t XY); 
FM_INLINE v2i FM_CALL V2i(__m128i); 
FM_INLINE v2i FM_CALL V2i();

FM_INLINE void FM_CALL Store(int32_t* Mem, v2i V); 

FM_INLINE int32_t* Ptr(const v2i& V) { return (int32_t*)(&V); }
FM_INLINE int32_t* PtrY(const v2i& V) { return (int32_t*)(&V) + 1; }

FM_INLINE v2i FM_CALL operator+(v2i A, v2i B);
FM_INLINE v2i FM_CALL operator-(v2i A, v2i B); 
FM_INLINE v2i& FM_CALL operator+=(v2i& a, v2i B);
FM_INLINE v2i& FM_CALL operator-=(v2i& a, v2i B);
FM_INLINE v2i FM_CALL HadamardMul(v2i A, v2i B);
FM_INLINE v2i FM_CALL operator*(v2i v, int32_t Scalar); 
FM_INLINE v2i FM_CALL operator*(int32_t Scalar, v2i v);
FM_INLINE v2i FM_CALL operator-(v2i v); 
FM_INLINE v2i FM_CALL Min(v2i, v2i); 
FM_INLINE v2i FM_CALL Max(v2i, v2i); 
FM_INLINE v2i FM_CALL Abs(v2i); 
FM_INLINE int32_t FM_CALL SumOfElements(v2i);
FM_INLINE int32_t FM_CALL Length(v2i);
FM_INLINE int32_t FM_CALL LengthSquared(v2i); 
FM_INLINE v2i FM_CALL Clamp(v2i V, v2i Min, v2i Max); 

FM_INLINE bool FM_CALL operator==(v2i, v2i); 
FM_INLINE bool FM_CALL operator!=(v2i, v2i); 
FM_INLINE v2i FM_CALL EqualsMask(v2i, v2i);
FM_INLINE v2i FM_CALL GreaterMask(v2i, v2i);
FM_INLINE v2i FM_CALL GreaterOrEqualMask(v2i, v2i);
FM_INLINE v2i FM_CALL LesserMask(v2i, v2i);
FM_INLINE v2i FM_CALL LesserOrEqualMask(v2i, v2i);
// TODO: Add HadamardDiv() and operator/ - Maybe I can do that using cast instructions?

struct alignas(16) v2u
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

	FM_INLINE v2u FM_CALL YX() const;
	FM_INLINE v2u FM_CALL XX() const;
	FM_INLINE v2u FM_CALL YY() const;

	FM_INLINE v2u FM_CALL VU() const { return YX(); }
	FM_INLINE v2u FM_CALL UU() const { return XX(); }
	FM_INLINE v2u FM_CALL VV() const { return YY(); }
};

FM_INLINE v2u FM_CALL V2uFromMemory(const uint32_t*); 
FM_INLINE v2u FM_CALL V2u(uint32_t X, uint32_t Y); 
FM_INLINE v2u FM_CALL V2u(uint32_t XY);
FM_INLINE v2u FM_CALL V2u(__m128i);
FM_INLINE v2u FM_CALL V2u();

FM_INLINE void FM_CALL Store(uint32_t* Mem, v2u V);

FM_INLINE uint32_t* Ptr(const v2u& V) { return (uint32_t*)(&V); }
FM_INLINE uint32_t* PtrY(const v2u& V) { return (uint32_t*)(&V) + 1; }

FM_INLINE v2u FM_CALL operator+(v2u, v2u);
FM_INLINE v2u FM_CALL operator-(v2u, v2u);
FM_INLINE v2u& FM_CALL operator+=(v2u&, v2u);
FM_INLINE v2u& FM_CALL operator-=(v2u&, v2u);
FM_INLINE v2u FM_CALL HadamardMul(v2u, v2u);
FM_INLINE v2u FM_CALL operator*(v2u V, uint32_t Scalar); 
FM_INLINE v2u FM_CALL operator*(uint32_t Scalar, v2u V);
FM_INLINE v2u FM_CALL Min(v2u, v2u); 
FM_INLINE v2u FM_CALL Max(v2u, v2u); 
FM_INLINE uint32_t FM_CALL SumOfElements(v2u);
FM_INLINE uint32_t FM_CALL Length(v2u);
FM_INLINE uint32_t FM_CALL LengthSquared(v2u); 
FM_INLINE v2u FM_CALL Clamp(v2u v, v2u min, v2u Max); 

FM_INLINE bool FM_CALL operator==(v2u, v2u); 
FM_INLINE bool FM_CALL operator!=(v2u, v2u); 
FM_INLINE v2u FM_CALL EqualsMask(v2u, v2u);
FM_INLINE v2u FM_CALL GreaterMask(v2u, v2u);
FM_INLINE v2u FM_CALL GreaterOrEqualMask(v2u, v2u);
FM_INLINE v2u FM_CALL LesserMask(v2u, v2u);
FM_INLINE v2u FM_CALL LesserOrEqualMask(v2u, v2u);
// TODO: Add HadamardDiv() and operator/

struct alignas(16) v3
{
	__m128 M;

	FM_INLINE void FM_CALL SetX(float X);
	FM_INLINE void FM_CALL SetY(float Y);
	FM_INLINE void FM_CALL SetZ(float Z);

	FM_INLINE float FM_CALL X() const;
	FM_INLINE float FM_CALL U() const { return X(); }
	FM_INLINE float FM_CALL R() const { return X(); }

	FM_INLINE float FM_CALL Y() const;
	FM_INLINE float FM_CALL V() const { return Y(); }
	FM_INLINE float FM_CALL G() const { return Y(); }

	FM_INLINE float FM_CALL Z() const;
	FM_INLINE float FM_CALL W() const { return Z(); }
	FM_INLINE float FM_CALL B() const { return Z(); }

	FM_INLINE v2 FM_CALL XY() const;
	FM_INLINE v2 FM_CALL YX() const;
	FM_INLINE v2 FM_CALL YZ() const;
	FM_INLINE v2 FM_CALL ZY() const;
	FM_INLINE v2 FM_CALL XZ() const;
	FM_INLINE v2 FM_CALL ZX() const;
	FM_INLINE v2 FM_CALL XX() const;
	FM_INLINE v2 FM_CALL YY() const;
	FM_INLINE v2 FM_CALL ZZ() const;

#ifndef FM_EXCLUDE_TEX_COORD_SWIZZLES
	FM_INLINE v2 FM_CALL UV() const { return XY(); }
	FM_INLINE v2 FM_CALL VU() const { return YX(); }
	FM_INLINE v2 FM_CALL VW() const { return YZ(); }
	FM_INLINE v2 FM_CALL WV() const { return ZY(); }
	FM_INLINE v2 FM_CALL UW() const { return XZ(); }
	FM_INLINE v2 FM_CALL WU() const { return ZX(); }
	FM_INLINE v2 FM_CALL UU() const { return XX(); }
	FM_INLINE v2 FM_CALL VV() const { return YY(); }
	FM_INLINE v2 FM_CALL WW() const { return ZZ(); }
#endif

#ifndef FM_EXCLUDE_COLOR_SWIZZLES
	FM_INLINE v2 FM_CALL RG() const { return XY(); }
	FM_INLINE v2 FM_CALL GR() const { return YX(); }
	FM_INLINE v2 FM_CALL GB() const { return YZ(); }
	FM_INLINE v2 FM_CALL BG() const { return ZY(); }
	FM_INLINE v2 FM_CALL RB() const { return XZ(); }
	FM_INLINE v2 FM_CALL BR() const { return ZX(); }
	FM_INLINE v2 FM_CALL RR() const { return XX(); }
	FM_INLINE v2 FM_CALL GG() const { return YY(); }
	FM_INLINE v2 FM_CALL BB() const { return ZZ(); }
#endif

	FM_INLINE v3 FM_CALL XYZ() const;
	FM_INLINE v3 FM_CALL YZX() const;
	FM_INLINE v3 FM_CALL ZXY() const;
	FM_INLINE v3 FM_CALL ZYX() const;
	FM_INLINE v3 FM_CALL XZY() const;
	FM_INLINE v3 FM_CALL YXZ() const;
	FM_INLINE v3 FM_CALL XXY() const;
	FM_INLINE v3 FM_CALL XXZ() const;
	FM_INLINE v3 FM_CALL YYX() const;
	FM_INLINE v3 FM_CALL YYZ() const;
	FM_INLINE v3 FM_CALL ZZX() const;
	FM_INLINE v3 FM_CALL ZZY() const;
	FM_INLINE v3 FM_CALL YXX() const;
	FM_INLINE v3 FM_CALL ZXX() const;
	FM_INLINE v3 FM_CALL XYY() const;
	FM_INLINE v3 FM_CALL ZYY() const;
	FM_INLINE v3 FM_CALL XZZ() const;
	FM_INLINE v3 FM_CALL YZZ() const;
	FM_INLINE v3 FM_CALL XYX() const;
	FM_INLINE v3 FM_CALL XZX() const;
	FM_INLINE v3 FM_CALL YXY() const;
	FM_INLINE v3 FM_CALL YZY() const;
	FM_INLINE v3 FM_CALL ZXZ() const;
	FM_INLINE v3 FM_CALL ZYZ() const;
	FM_INLINE v3 FM_CALL XXX() const;
	FM_INLINE v3 FM_CALL YYY() const;
	FM_INLINE v3 FM_CALL ZZZ() const;

#ifndef FM_EXCLUDE_TEX_COORD_SWIZZLES
	FM_INLINE v3 FM_CALL UVW() const { return XYZ(); }
	FM_INLINE v3 FM_CALL VWU() const { return YZX(); }
	FM_INLINE v3 FM_CALL WUV() const { return ZXY(); }
	FM_INLINE v3 FM_CALL WVU() const { return ZYX(); }
	FM_INLINE v3 FM_CALL UWV() const { return XZY(); }
	FM_INLINE v3 FM_CALL VUW() const { return YXZ(); }
	FM_INLINE v3 FM_CALL UUV() const { return XXY(); }
	FM_INLINE v3 FM_CALL UUW() const { return XXZ(); }
	FM_INLINE v3 FM_CALL VVU() const { return YYX(); }
	FM_INLINE v3 FM_CALL VVW() const { return YYZ(); }
	FM_INLINE v3 FM_CALL WWU() const { return ZZX(); }
	FM_INLINE v3 FM_CALL WWV() const { return ZZY(); }
	FM_INLINE v3 FM_CALL VUU() const { return YXX(); }
	FM_INLINE v3 FM_CALL WUU() const { return ZXX(); }
	FM_INLINE v3 FM_CALL UVV() const { return XYY(); }
	FM_INLINE v3 FM_CALL WVV() const { return ZYY(); }
	FM_INLINE v3 FM_CALL UWW() const { return XZZ(); }
	FM_INLINE v3 FM_CALL VWW() const { return YZZ(); }
	FM_INLINE v3 FM_CALL UVU() const { return XYX(); }
	FM_INLINE v3 FM_CALL UWU() const { return XZX(); }
	FM_INLINE v3 FM_CALL VUV() const { return YXY(); }
	FM_INLINE v3 FM_CALL VWV() const { return YZY(); }
	FM_INLINE v3 FM_CALL WUW() const { return ZXZ(); }
	FM_INLINE v3 FM_CALL WVW() const { return ZYZ(); }
	FM_INLINE v3 FM_CALL UUU() const { return XXX(); }
	FM_INLINE v3 FM_CALL VVV() const { return YYY(); }
	FM_INLINE v3 FM_CALL WWW() const { return ZZZ(); }
#endif

#ifndef FM_EXCLUDE_COLOR_SWIZZLES
	//FM_INLINE v3 FM_CALL RGB() const { return XYZ(); }
	FM_INLINE v3 FM_CALL GBR() const { return YZX(); }
	FM_INLINE v3 FM_CALL BRG() const { return ZXY(); }
	FM_INLINE v3 FM_CALL BGR() const { return ZYX(); }
	FM_INLINE v3 FM_CALL RBG() const { return XZY(); }
	FM_INLINE v3 FM_CALL GRB() const { return YXZ(); }
	FM_INLINE v3 FM_CALL RRG() const { return XXY(); }
	FM_INLINE v3 FM_CALL RRB() const { return XXZ(); }
	FM_INLINE v3 FM_CALL GGR() const { return YYX(); }
	FM_INLINE v3 FM_CALL GGB() const { return YYZ(); }
	FM_INLINE v3 FM_CALL BBR() const { return ZZX(); }
	FM_INLINE v3 FM_CALL BBG() const { return ZZY(); }
	FM_INLINE v3 FM_CALL GRR() const { return YXX(); }
	FM_INLINE v3 FM_CALL BRR() const { return ZXX(); }
	FM_INLINE v3 FM_CALL RGG() const { return XYY(); }
	FM_INLINE v3 FM_CALL BGG() const { return ZYY(); }
	FM_INLINE v3 FM_CALL RBB() const { return XZZ(); }
	FM_INLINE v3 FM_CALL GBB() const { return YZZ(); }
	FM_INLINE v3 FM_CALL RGR() const { return XYX(); }
	FM_INLINE v3 FM_CALL RBR() const { return XZX(); }
	FM_INLINE v3 FM_CALL GRG() const { return YXY(); }
	FM_INLINE v3 FM_CALL GBG() const { return YZY(); }
	FM_INLINE v3 FM_CALL BRB() const { return ZXZ(); }
	FM_INLINE v3 FM_CALL BGB() const { return ZYZ(); }
	FM_INLINE v3 FM_CALL RRR() const { return XXX(); }
	FM_INLINE v3 FM_CALL GGG() const { return YYY(); }
	FM_INLINE v3 FM_CALL BBB() const { return ZZZ(); }
#endif
};
FM_INLINE v3 FM_CALL V3FromMemory(float*);
FM_INLINE v3 FM_CALL V3(float X, float Y, float Z);
FM_INLINE v3 FM_CALL V3(float XYZ);
FM_INLINE v3 FM_CALL V3(__m128);
FM_INLINE v3 FM_CALL V3();

FM_INLINE void FM_CALL Store(float* Mem, v3 V); 

FM_INLINE float* Ptr(const v3& V) { return (float*)(&V); }
FM_INLINE float* PtrY(const v3& V) { return (float*)(&V) + 1; }
FM_INLINE float* PtrZ(const v3& V) { return (float*)(&V) + 2; }

FM_INLINE v3 FM_CALL operator+(v3, v3); 
FM_INLINE v3 FM_CALL operator-(v3, v3);
FM_INLINE v3& FM_CALL operator+=(v3&, v3);
FM_INLINE v3& FM_CALL operator-=(v3&, v3);
FM_INLINE v3 FM_CALL HadamardMul(v3, v3);
FM_INLINE v3 FM_CALL HadamardDiv(v3, v3);
FM_INLINE v3 FM_CALL operator*(v3 V, float  Scalar);
FM_INLINE v3 FM_CALL operator*(float Scalar, v3 V);
FM_INLINE v3 FM_CALL operator/(v3 V, float Scalar);
FM_INLINE v3 FM_CALL operator-(v3); 
FM_INLINE v3 FM_CALL Cross(v3, v3); 
FM_INLINE float FM_CALL Dot(v3, v3); 
FM_INLINE v3 FM_CALL Min(v3, v3); 
FM_INLINE v3 FM_CALL Max(v3, v3); 
FM_INLINE v3 FM_CALL Normalize(v3);
FM_INLINE v3 FM_CALL Abs(v3);
FM_INLINE float FM_CALL SumOfElements(v3);
FM_INLINE float FM_CALL Length(v3);
FM_INLINE float FM_CALL LengthSquared(v3); 
FM_INLINE v3 FM_CALL Clamp(v3 V, v3 Min, v3 Max); 
FM_INLINE v3 FM_CALL Lerp(v3 A, v3 B, float T);

FM_INLINE bool FM_CALL operator==(v3, v3); 
FM_INLINE bool FM_CALL operator!=(v3, v3); 
FM_INLINE v3 FM_CALL EqualsMask(v3, v3);
FM_INLINE v3 FM_CALL GreaterMask(v3, v3);
FM_INLINE v3 FM_CALL GreaterOrEqualMask(v3, v3);
FM_INLINE v3 FM_CALL LesserMask(v3, v3);
FM_INLINE v3 FM_CALL LesserOrEqualMask(v3, v3);

struct alignas(16) v4
{
	__m128 M;

	FM_INLINE void FM_CALL SetX(float);
	FM_INLINE void FM_CALL SetY(float); 
	FM_INLINE void FM_CALL SetZ(float); 
	FM_INLINE void FM_CALL SetW(float); 

	FM_INLINE float FM_CALL X() const;
	FM_INLINE float FM_CALL Y() const;
	FM_INLINE float FM_CALL Z() const;
	FM_INLINE float FM_CALL W() const;

	FM_INLINE float FM_CALL R() const { return X(); }
	FM_INLINE float FM_CALL G() const { return Y(); }
	FM_INLINE float FM_CALL B() const { return Z(); }
	FM_INLINE float FM_CALL A() const { return W(); }
};
FM_INLINE v4 FM_CALL V4FromMemory(const float*); 
FM_INLINE v4 FM_CALL V4(v3 V, float W); 
FM_INLINE v4 FM_CALL V4(float X, float Y, float Z, float W);
FM_INLINE v4 FM_CALL V4(float XYZW);
FM_INLINE v4 FM_CALL V4(__m128);
FM_INLINE v4 FM_CALL V4();

FM_INLINE void FM_CALL Store(float* Mem, v4 V);
FM_INLINE void FM_CALL Store16ByteAligned(float* Mem, v4 V);

FM_INLINE float* Ptr(const v4& V) { return (float*)(&V); }
FM_INLINE float* PtrY(const v4& V) { return (float*)(&V) + 1; }
FM_INLINE float* PtrZ(const v4& V) { return (float*)(&V) + 2; }
FM_INLINE float* PtrW(const v4& V) { return (float*)(&V) + 3; }

FM_INLINE v4 FM_CALL operator+(v4, v4); 
FM_INLINE v4 FM_CALL operator-(v4, v4);
FM_INLINE v4& FM_CALL operator+=(v4&, v4);
FM_INLINE v4& FM_CALL operator-=(v4&, v4);
FM_INLINE v4 FM_CALL HadamardMul(v4, v4);
FM_INLINE v4 FM_CALL HadamardDiv(v4, v4);
FM_INLINE v4 FM_CALL operator*(v4 V, float Scalar);
FM_INLINE v4 FM_CALL operator*(float Scalar, v4 V);
FM_INLINE v4 FM_CALL operator/(v4 V, float Scalar);
FM_INLINE v4 FM_CALL operator-(v4); 
FM_INLINE v4 FM_CALL Cross(v4, v4); 
FM_INLINE float FM_CALL Dot(v4, v4); 
FM_INLINE v4 FM_CALL Min(v4, v4); 
FM_INLINE v4 FM_CALL Max(v4, v4); 
FM_INLINE v4 FM_CALL Normalize(v4);
FM_INLINE v4 FM_CALL Abs(v4);
FM_INLINE float FM_CALL SumOfElements(v4);
FM_INLINE float FM_CALL Length(v4);
FM_INLINE float FM_CALL LengthSquared(v4); 
FM_INLINE v4 FM_CALL Clamp(v4 V, v4 Min, v4 Max); 
FM_INLINE v4 FM_CALL Lerp(v4 A, v4 B, float T);

FM_INLINE bool FM_CALL operator==(v4, v4); 
FM_INLINE bool FM_CALL operator!=(v4, v4); 
FM_INLINE v4 FM_CALL EqualsMask(v4, v4);
FM_INLINE v4 FM_CALL GreaterMask(v4, v4);
FM_INLINE v4 FM_CALL GreaterOrEqualMask(v4, v4);
FM_INLINE v4 FM_CALL LesserMask(v4, v4);
FM_INLINE v4 FM_CALL LesserOrEqualMask(v4, v4);


struct alignas(16) mat4
{
	__m128 Columns[4];

	FM_INLINE v4 FM_CALL GetColumn(uint32_t Index);
	FM_INLINE void FM_CALL SetColumn(uint32_t Index, v4 Col);
	FM_INLINE void FM_CALL SetColumn(uint32_t Index, float X, float Y, float Z, float W);
	FM_INLINE void FM_CALL SwapColumns(uint32_t Col1Index, uint32_t Col2Index); 

	v4 FM_CALL GetRow(uint32_t Index);
	void FM_CALL SetRow(uint32_t Index, v4 Row);
	FM_INLINE void FM_CALL SetRow(uint32_t Index, float X, float Y, float Z, float W);
	FM_INLINE void FM_CALL SwapRows(uint32_t Row1Index, uint32_t Row2Index); 

	FM_INLINE v4 FM_CALL GetMainDiagonal();
	FM_INLINE void FM_CALL SetMainDiagonal(float X, float Y, float Z, float W); 
	FM_INLINE void FM_CALL SetMainDiagonal(v4);
};

FM_INLINE mat4 FM_CALL Mat4FromColumnMajorMemory(float*); 
// TODO: Mat4FromRowMajorMemory
FM_INLINE mat4 FM_CALL Mat4(); 
FM_INLINE mat4 FM_CALL Mat4Identity(); 
FM_INLINE mat4 FM_CALL Mat4Diagonal(float Diag); 
FM_INLINE mat4 FM_CALL Mat4Diagonal(float DiagX, float DiagY, float DiagZ, float DiagW); 
FM_INLINE mat4 FM_CALL Mat4Diagonal(v4 Diag); 
FM_INLINE mat4 FM_CALL Mat4FromColumns(v4 Col1, v4 Col2, v4 Col3, v4 Col4); 
FM_INLINE mat4 FM_CALL Mat4FromColumns(v3 Col1, v3 Col2, v3 Col3, v3 Col4); 
FM_INLINE mat4 FM_CALL Mat4FromColumns(
	float E11, float E21, float E31, float E41,
    float E12, float E22, float E32, float E42,
    float E13, float E23, float E33, float E43,
    float E14, float E24, float E34, float E44);
FM_INLINE mat4 FM_CALL Mat4FromRows(v4 Row1, v4 Row2, v4 Row3, v4 Row4); 
FM_INLINE mat4 FM_CALL Mat4FromRows(v3 Row1, v3 Row2, v3 Row3, v3 Row4); 
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
FM_INLINE v4 FM_CALL operator*(mat4, v4);
FM_INLINE mat4 FM_CALL operator*(mat4, float Scalar);
FM_INLINE mat4 FM_CALL operator*(float Scalar, mat4);
FM_INLINE mat4 FM_CALL operator/(mat4, float Scalar);
FM_INLINE mat4 FM_CALL Transpose(mat4);
FM_INLINE mat4 FM_CALL SwapColumns(mat4, uint32_t Col1Index, uint32_t Col2Index);
FM_INLINE mat4 FM_CALL SwapRows(mat4, uint32_t Row1Index, uint32_t Row2Index);

FM_INLINE mat4 FM_CALL Mat4Translation(float X, float Y, float Z); 
FM_INLINE mat4 FM_CALL Mat4Translation(v3 Translation);
FM_INLINE mat4 FM_CALL Translate(mat4, float X, float Y, float Z); 
FM_INLINE mat4 FM_CALL Translate(mat4, v3 Translation);

FM_INLINE mat4 FM_CALL Mat4Scale(float Scalar); 
FM_INLINE mat4 FM_CALL Mat4Scale(float ScalarX, float ScalarY, float ScalarZ); 
FM_INLINE mat4 FM_CALL Mat4Scale(v3 Scalar);
FM_INLINE mat4 FM_CALL Scale(mat4, float Scalar); 
FM_INLINE mat4 FM_CALL Scale(mat4, float X, float Y, float Z); 
FM_INLINE mat4 FM_CALL Scale(mat4, v3 Scalar);

FM_INLINE mat4 FM_CALL Mat4RotationDegrees(float Degrees, float AxisX, float AxisY, float AxisZ); 
FM_INLINE mat4 FM_CALL Mat4RotationDegrees(float Degrees, v3 Axis);
FM_INLINE mat4 FM_CALL Mat4RotationAroundXAxisDegrees(float Degrees);
FM_INLINE mat4 FM_CALL Mat4RotationAroundYAxisDegrees(float Degrees);
FM_INLINE mat4 FM_CALL Mat4RotationAroundZAxisDegrees(float Degrees);
FM_INLINE mat4 FM_CALL RotateDegrees(mat4, float Degrees, float AxisX, float AxisY, float AxisZ); 
FM_INLINE mat4 FM_CALL RotateDegrees(mat4, float Degrees, v3 Axis);
FM_INLINE mat4 FM_CALL RotateAroundXAxisDegrees(mat4, float Degrees);
FM_INLINE mat4 FM_CALL RotateAroundYAxisDegrees(mat4, float Degrees);
FM_INLINE mat4 FM_CALL RotateAroundZAxisDegrees(mat4, float Degrees);
FM_INLINE mat4 FM_CALL Mat4RotationRadians(float Radians, float AxisX, float AxisY, float AxisZ); 
FM_INLINE mat4 FM_CALL Mat4RotationRadians(float Radians, v3 Axis);
FM_INLINE mat4 FM_CALL Mat4RotationAroundXAxisRadians(float Radians);
FM_INLINE mat4 FM_CALL Mat4RotationAroundYAxisRadians(float Radians);
FM_INLINE mat4 FM_CALL Mat4RotationAroundZAxisRadians(float Radians);
FM_INLINE mat4 FM_CALL RotateRadians(mat4, float Radians, float AxisX, float AxisY, float AxisZ); 
FM_INLINE mat4 FM_CALL RotateRadians(mat4, float Radians, v3 Axis);
FM_INLINE mat4 FM_CALL RotateAroundXAxisRadians(mat4, float Radians);
FM_INLINE mat4 FM_CALL RotateAroundYAxisRadians(mat4, float Radians);
FM_INLINE mat4 FM_CALL RotateAroundZAxisRadians(mat4, float Radians);

FM_INLINE mat4 FM_CALL Mat4ShearXAxis(float Y, float Z); 
FM_INLINE mat4 FM_CALL Mat4ShearYAxis(float X, float Z);
FM_INLINE mat4 FM_CALL Mat4ShearZAxis(float X, float Y);
FM_INLINE mat4 FM_CALL Mat4Shear(float XY, float XZ, float YX, float YZ, float ZX, float ZY);
FM_INLINE mat4 FM_CALL ShearXAxis(mat4, float Y, float Z); 
FM_INLINE mat4 FM_CALL ShearYAxis(mat4, float X, float Z); 
FM_INLINE mat4 FM_CALL ShearZAxis(mat4, float X, float Y); 
FM_INLINE mat4 FM_CALL Shear(mat4, float XY, float XZ, float YX, float YZ, float ZX, float ZY);

mat4 Mat4Orthographic(float Left, float Right, float Bottom, float Top, float Near, float Far);
mat4 Mat4Perspective(float FOV, float AspectRatio, float near, float Far);
mat4 LookAt(v3 Eye, v3 At, v3 Up = V3(0.f, 1.f, 0.f));

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
// fast math int32_ternal helper functions //
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
FM_INLINE v2 FM_CALL V2FromMemory(const float* V) {
	v2 Res;
	Res.M = _mm_set_ps(0.f, 0.f, V[1], V[0]); 
	return Res;
} 
FM_INLINE v2 FM_CALL V2(float X, float Y) {
	v2 Res;
	Res.M = _mm_set_ps(0.f, 0.f, Y, X); 
	return Res;
}
FM_INLINE v2 FM_CALL V2(float XY) {
	v2 Res;
	Res.M = _mm_set1_ps(XY); 
	return Res;
}
FM_INLINE v2 FM_CALL V2(__m128 M) {
	v2 Res;
	Res.M = M;
	return Res;
}
FM_INLINE v2 FM_CALL V2() {
	v2 Res;
	Res.M = _mm_setzero_ps(); 
	return Res;
}
FM_INLINE float FM_CALL v2::X() const { 
	return priv::GetX(M); 
}
FM_INLINE float FM_CALL v2::Y() const {
	return priv::GetY(M); 
}
FM_INLINE v2 FM_CALL v2::YX() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE v2 FM_CALL v2::XX() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 0))); 
}
FM_INLINE v2 FM_CALL v2::YY() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE void FM_CALL v2::SetX(float X) {
	M = priv::SetX(M, X); 
}
FM_INLINE void FM_CALL v2::SetY(float Y) { 
	M = priv::SetY(M, Y);
}  
FM_INLINE void FM_CALL Store(float* Mem, v2 V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
} 
FM_INLINE v2 FM_CALL operator+(v2 A, v2 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A; 
}
FM_INLINE v2 FM_CALL operator-(v2 A, v2 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A; 
}
FM_INLINE v2& FM_CALL operator+=(v2& A, v2 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A; 
}
FM_INLINE v2& FM_CALL operator-=(v2& A, v2 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A; 
}
FM_INLINE v2 FM_CALL HadamardMul(v2 A, v2 B) {
	A.M = _mm_mul_ps(A.M, B.M);
	return A;
}
FM_INLINE v2 FM_CALL HadamardDiv(v2 A, v2 B) {
	A.M = _mm_div_ps(A.M, B.M);
	return A; 
}
FM_INLINE v2 FM_CALL operator*(v2 V, float Scalar) {
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar)); 
	return V; 
}
FM_INLINE v2 FM_CALL operator*(float Scalar, v2 V) { 
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar));
	return V; 
}
FM_INLINE v2 FM_CALL operator/(v2 V, float Scalar) {
	V.M = _mm_div_ps(V.M, _mm_set1_ps(Scalar));
	return V; 
}
FM_INLINE v2 FM_CALL operator-(v2 V) {
	V.M = _mm_sub_ps(_mm_setzero_ps(), V.M);
	return V;
}
FM_INLINE float FM_CALL Dot(v2 A, v2 B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_INLINE v2 FM_CALL Min(v2 A, v2 B) {
	A.M = _mm_min_ps(A.M, B.M);
	return A;
}
FM_INLINE v2 FM_CALL Max(v2 A, v2 B) {
	A.M = _mm_max_ps(A.M, B.M);
	return A;
}
FM_INLINE v2 FM_CALL Abs(v2 V) {
	__m128 SignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000)); 
	V.M = _mm_andnot_ps(SignMask, V.M);
	return V;
}
FM_INLINE float FM_CALL SumOfElements(v2 V) {
	return V.X() + V.Y();
}
FM_INLINE float FM_CALL Length(v2 V) {
	return sqrtf(Dot(V, V));
}
FM_INLINE float FM_CALL LengthSquared(v2 V) {
	return Dot(V, V);
}
FM_INLINE v2 FM_CALL Normalize(v2 V) {
	return V / Length(V);
}
FM_INLINE v2 FM_CALL Clamp(v2 V, v2 MinV, v2 MaxV) {
	return Min(Max(V, MinV), MaxV);
}
FM_INLINE v2 FM_CALL Lerp(v2 A, v2 B, float T) {
	return A + (B-A)*T;
}
FM_INLINE bool FM_CALL operator==(v2 A, v2 B) {
	v2 EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_INLINE bool FM_CALL operator!=(v2 A, v2 B) {
	v2 EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
}
FM_INLINE v2 FM_CALL EqualsMask(v2 A, v2 B) {
	A.M = _mm_cmpeq_ps(A.M, B.M);
	return A;
}
FM_INLINE v2 FM_CALL GreaterMask(v2 A, v2 B) {
	A.M = _mm_cmpgt_ps(A.M, B.M);
	return A;
}
FM_INLINE v2 FM_CALL GreaterOrEqualMask(v2 A, v2 B) {
	A.M = _mm_cmpge_ps(A.M, B.M);
	return A;
}
FM_INLINE v2 FM_CALL LesserMask(v2 A, v2 B) {
	A.M = _mm_cmplt_ps(A.M, B.M);
	return A;
}
FM_INLINE v2 FM_CALL LesserOrEqualMask(v2 A, v2 B) {
	A.M = _mm_cmple_ps(A.M, B.M);
	return A;
}

//////////////
// v2d impl //
//////////////
FM_INLINE v2d FM_CALL V2dFromMemory(const double* V) {
	v2d Res;
	Res.M = _mm_set_pd(V[1], V[0]); 
	return Res;
}
FM_INLINE v2d FM_CALL V2d(double X, double Y) {
	v2d Res;
	Res.M = _mm_set_pd(Y, X); 
	return Res;
}
FM_INLINE v2d FM_CALL V2d(double A) {
	v2d Res;
	Res.M = _mm_set1_pd(A);
	return Res;
}
FM_INLINE v2d FM_CALL V2d(__m128d M) {
	v2d Res;
	Res.M = M;
	return Res;
}
FM_INLINE v2d FM_CALL V2d() {
	v2d Res;
	Res.M = _mm_setzero_pd(); 
	return Res;
}
FM_INLINE double FM_CALL v2d::X() const {
	return _mm_cvtsd_f64(M);
}
FM_INLINE double FM_CALL v2d::Y() const { 
	return _mm_cvtsd_f64(_mm_shuffle_pd(M, M, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE v2d FM_CALL v2d::YX() const {
	return V2d(_mm_shuffle_pd(M, M, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE v2d FM_CALL v2d::XX() const {
	return V2d(_mm_unpacklo_pd(M, M));
}
FM_INLINE v2d FM_CALL v2d::YY() const {
	return V2d(_mm_unpackhi_pd(M, M));
}
FM_INLINE void FM_CALL Store(double* Mem, v2d V) { 
	_mm_storeu_pd(Mem, V.M); 
} 
FM_INLINE void FM_CALL Store16ByteAligned(double* Mem, v2d V) {
	_mm_store_pd(Mem, V.M); 
}
FM_INLINE void FM_CALL v2d::SetX(double X) {
	M = _mm_move_sd(M, _mm_set_sd(X)); 
}
FM_INLINE void FM_CALL v2d::SetY(double Y) {
	M = _mm_unpacklo_pd(M, _mm_set_sd(Y)); 
}
FM_INLINE v2d FM_CALL operator+(v2d A, v2d B) {
	A.M = _mm_add_pd(A.M, B.M);
	return A; 
}
FM_INLINE v2d FM_CALL operator-(v2d A, v2d B) {
	A.M = _mm_sub_pd(A.M, B.M);
	return A; 
}
FM_INLINE v2d& FM_CALL operator+=(v2d& A, v2d B) {
	A.M = _mm_add_pd(A.M, B.M);
	return A; 
}
FM_INLINE v2d& FM_CALL operator-=(v2d& A, v2d B) {
	A.M = _mm_sub_pd(A.M, B.M);
	return A; 
}
FM_INLINE v2d FM_CALL HadamardMul(v2d A, v2d B) {
	A.M = _mm_mul_pd(A.M, B.M);
	return A; 
}
FM_INLINE v2d FM_CALL HadamardDiv(v2d A, v2d B) {
	A.M = _mm_div_pd(A.M, B.M);
	return A; 
}
FM_INLINE v2d FM_CALL operator*(v2d V, double Scalar) {
	V.M = _mm_mul_pd(V.M, _mm_set1_pd(Scalar));
	return V; 
}
FM_INLINE v2d FM_CALL operator*(double Scalar, v2d V) {
	V.M = _mm_mul_pd(V.M, _mm_set1_pd(Scalar));
	return V; 
} 
FM_INLINE v2d FM_CALL operator/(v2d V, double Scalar) {
	V.M = _mm_div_pd(V.M, _mm_set1_pd(Scalar));
	return V; 
}
FM_INLINE v2d FM_CALL operator-(v2d V) {
	V.M = _mm_sub_pd(_mm_setzero_pd(), V.M);
	return V;
}
FM_INLINE double FM_CALL Dot(v2d A, v2d B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_INLINE v2d FM_CALL Min(v2d A, v2d B) {
	A.M = _mm_min_pd(A.M, B.M);
	return A;
}
FM_INLINE v2d FM_CALL Max(v2d A, v2d B) {
	A.M = _mm_max_pd(A.M, B.M);
	return A;
}
FM_INLINE v2d FM_CALL Abs(v2d V) {
	__m128d SignBits = _mm_castsi128_pd(_mm_set1_epi32(0x80000000));
	V.M = _mm_andnot_pd(SignBits, V.M);
	return V;
}
FM_INLINE double FM_CALL SumOfElements(v2d V) {
	return V.X() + V.Y();
}
FM_INLINE double FM_CALL Length(v2d V) {
	return sqrt(Dot(V, V));
}
FM_INLINE double FM_CALL LengthSquared(v2d V) {
	return Dot(V, V);
}
FM_INLINE v2d FM_CALL Normalize(v2d V) {
	return V / Length(V);
}
FM_INLINE v2d FM_CALL Clamp(v2d V, v2d MinV, v2d MaxV) {
	return Min(Max(V, MinV), MaxV);
} 
FM_INLINE v2d FM_CALL Lerp(v2d A, v2d B, double T) {
	return A + (B-A)*T;
}
FM_INLINE bool FM_CALL operator==(v2d A, v2d B) {
	v2d EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_INLINE bool FM_CALL operator!=(v2d A, v2d B) {
	v2d EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
}
FM_INLINE v2d FM_CALL EqualsMask(v2d A, v2d B) {
	A.M = _mm_cmpeq_pd(A.M, B.M);
	return A;
}
FM_INLINE v2d FM_CALL GreaterMask(v2d A, v2d B) {
	A.M = _mm_cmpgt_pd(A.M, B.M);
	return A;
}
FM_INLINE v2d FM_CALL GreaterOrEqualMask(v2d A, v2d B) {
	A.M = _mm_cmpge_pd(A.M, B.M);
	return A;
}
FM_INLINE v2d FM_CALL LesserMask(v2d A, v2d B) {
	A.M = _mm_cmplt_pd(A.M, B.M);
	return A;
}
FM_INLINE v2d FM_CALL LesserOrEqualMask(v2d A, v2d B) {
	A.M = _mm_cmple_pd(A.M, B.M);
	return A;
}

////////////////
// v2i impl //
////////////////
FM_INLINE v2i FM_CALL V2iFromMemory(const int32_t* V) {
	v2i Res;
	Res.M = _mm_set_epi32(0, 0, V[1], V[0]); 
	return Res;
}
FM_INLINE v2i FM_CALL V2i(int32_t X, int32_t Y) {
	v2i Res;
	Res.M = _mm_set_epi32(0, 0, Y, X); 
	return Res;
}
FM_INLINE v2i FM_CALL V2i(int32_t A) { 
	v2i Res;
	Res.M = _mm_set1_epi32(A); 
	return Res;
}
FM_INLINE v2i FM_CALL V2i(__m128i M) {
	v2i Res;
	Res.M = M;
	return Res;
}
FM_INLINE v2i FM_CALL V2i() {
	v2i Res;
	Res.M = _mm_setzero_si128();
	return Res;
}
FM_INLINE int32_t FM_CALL v2i::X() const { 
	return _mm_cvtsi128_si32(M); 
} 
FM_INLINE int32_t FM_CALL v2i::Y() const {
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(M, _MM_SHUFFLE(1, 1, 1, 1))); 
} 
FM_INLINE v2i FM_CALL v2i::YX() const {
	return V2i(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 0, 1)));
}
FM_INLINE v2i FM_CALL v2i::XX() const {
	return V2i(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 0, 0)));
}
FM_INLINE v2i FM_CALL v2i::YY() const {
	return V2i(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 1, 1)));
}
FM_INLINE void FM_CALL Store(int32_t* Mem, v2i V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
} 
FM_INLINE v2i FM_CALL operator+(v2i A, v2i B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_INLINE v2i FM_CALL operator-(v2i A, v2i B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_INLINE v2i& FM_CALL operator+=(v2i& A, v2i B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_INLINE v2i& FM_CALL operator-=(v2i& A, v2i B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_INLINE v2i FM_CALL operator-(v2i V) {
	V.M = _mm_sub_epi32(_mm_setzero_si128(), V.M);
	return V;
}
FM_INLINE int32_t FM_CALL SumOfElements(v2i V) {
	return V.X() + V.Y();
}
FM_INLINE int32_t FM_CALL Length(v2i V) {
	int32_t X = V.X();
	int32_t Y = V.Y();
	return (int32_t)sqrt(X*X + Y*Y);
}
FM_INLINE int32_t FM_CALL LengthSquared(v2i V) {
	int32_t X = V.X();
	int32_t Y = V.Y();
	return X*X + Y*Y;
}
FM_INLINE bool FM_CALL operator==(v2i A, v2i B) {
	v2i EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_INLINE bool FM_CALL operator!=(v2i A, v2i B) {
	v2i EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
} 
FM_INLINE v2i FM_CALL EqualsMask(v2i A, v2i B) {
	A.M = _mm_cmpeq_epi32(A.M, B.M);
	return A;
}
FM_INLINE v2i FM_CALL GreaterMask(v2i A, v2i B) {
	A.M = _mm_cmpgt_epi32(A.M, B.M);
	return A;
}
FM_INLINE v2i FM_CALL GreaterOrEqualMask(v2i A, v2i B) {
	__m128i GT = _mm_cmpgt_epi32(A.M, B.M);
	__m128i EQ = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(GT, EQ);
	return A;
}
FM_INLINE v2i FM_CALL LesserMask(v2i A, v2i B) {
	A.M = _mm_cmplt_epi32(A.M, B.M);
	return A;
}
FM_INLINE v2i FM_CALL LesserOrEqualMask(v2i A, v2i B) {
	__m128i LT = _mm_cmplt_epi32(A.M, B.M);
	__m128i EQ = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(LT, EQ);
	return A;
}
#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INLINE void FM_CALL v2i::SetX(int32_t X) {
	M = _mm_insert_epi32(M, X, 0);
}
FM_INLINE void FM_CALL v2i::SetY(int32_t Y) {
	M = _mm_insert_epi32(M, Y, 1);
}
FM_INLINE v2i FM_CALL operator*(v2i V, int32_t Scalar) {
	V.M = _mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar));
	return V; 
}
FM_INLINE v2i FM_CALL operator*(int32_t Scalar, v2i V) {
	V.M =_mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar)); 
	return V; 
}
FM_INLINE v2i FM_CALL HadamardMul(v2i A, v2i B) {
	A.M = _mm_mullo_epi32(A.M, B.M); 
	return A; 
}
FM_INLINE v2i FM_CALL Min(v2i A, v2i B) {
	A.M = _mm_min_epi32(A.M, B.M);
	return A;
}
FM_INLINE v2i FM_CALL Max(v2i A, v2i B) {
	A.M = _mm_max_epi32(A.M, B.M);
	return A;
}
FM_INLINE v2i FM_CALL Abs(v2i V) {
	V.M = _mm_abs_epi32(V.M);
	return V;
}
FM_INLINE v2i FM_CALL Clamp(v2i V, v2i MinV, v2i MaxV) {
	return Min(Max(V, MinV), MaxV);
} 
#else // SSE 2 implementations 
FM_INLINE void FM_CALL v2i::SetX(int32_t X) {
	int32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, M);
	Arr[0] = X;
	M = _mm_load_si128((__m128i*)Arr);
}
FM_INLINE void FM_CALL v2i::SetY(int32_t Y) {
	int32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, M);
	Arr[1] = Y;
	M = _mm_load_si128((__m128i*)Arr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_INLINE v2i FM_CALL HadamardMul(v2i A, v2i B) {
	int32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = AArr[0] * BArr[0]; 
	AArr[1] = AArr[1] * BArr[1]; 
	return V2i(AArr);
}
FM_INLINE v2i FM_CALL operator*(v2i V, int32_t Scalar) {
	int32_t VArr[4];
	_mm_store_si128((__m128i*)VArr, V.M);
	VArr[0] *= Scalar;
	VArr[1] *= Scalar;
	return V2i(VArr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_INLINE v2i FM_CALL operator*(int32_t Scalar, v2i v) {
	return V * Scalar; 
}
FM_INLINE v2i FM_CALL Min(v2i A, v2i B) {
	int32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Min(AArr[0], BArr[0]);
	AArr[1] = Min(AArr[1], BArr[1]);
	return V2i(AArr);
}
FM_INLINE v2i FM_CALL Max(v2i A, v2i B) {
	int32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Max(AArr[0], BArr[0]);
	AArr[1] = Max(AArr[1], BArr[1]);
	return V2i(AArr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_INLINE v2i FM_CALL abs(v2i v) {
	int32_t VArr[4];
	_mm_store_si128((__m128i*)VArr, V.M);
	VArr[0] = abs(VArr[0]);
	VArr[1] = abs(VArr[1]);
	return V2i(VArr);
}
#endif

////////////////
// v2u impl //
////////////////
FM_INLINE v2u FM_CALL V2uFromMemory(const uint32_t* V) {
	v2u Res;
	Res.M = _mm_set_epi32(0, 0, V[1], V[0]); 
	return Res;
}
FM_INLINE v2u FM_CALL V2u(uint32_t x, uint32_t y) {
	v2u Res;
	Res.M = _mm_set_epi32(0, 0, y, x); 
	return Res;
}
FM_INLINE v2u FM_CALL V2u(uint32_t a) {
	v2u Res;
	Res.M = _mm_set1_epi32(a); 
	return Res;
} 
FM_INLINE v2u FM_CALL V2u(__m128i m) {
	v2u Res;
	Res.M = m;
	return Res;
} 
FM_INLINE v2u FM_CALL V2u() {
	v2u Res;
	Res.M = _mm_setzero_si128(); 
	return Res;
}
FM_INLINE uint32_t FM_CALL v2u::X() const {
	return (uint32_t)_mm_cvtsi128_si32(M); 
} 
FM_INLINE uint32_t FM_CALL v2u::Y() const { 
	return (uint32_t)_mm_cvtsi128_si32(_mm_shuffle_epi32(M, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE v2u FM_CALL v2u::YX() const { 
	return V2u(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 0, 1))); 
}
FM_INLINE v2u FM_CALL v2u::XX() const { 
	return V2u(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 0, 0)));
}
FM_INLINE v2u FM_CALL v2u::YY() const { 
	return V2u(_mm_shuffle_epi32(M, _MM_SHUFFLE(3, 2, 1, 1)));
}
FM_INLINE void FM_CALL Store(uint32_t* Mem, v2u V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
} 
FM_INLINE v2u FM_CALL operator+(v2u A, v2u B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_INLINE v2u FM_CALL operator-(v2u A, v2u B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_INLINE v2u& FM_CALL operator+=(v2u& A, v2u B) {
	A.M = _mm_add_epi32(A.M, B.M);
	return A; 
}
FM_INLINE v2u& FM_CALL operator-=(v2u& A, v2u B) {
	A.M = _mm_sub_epi32(A.M, B.M);
	return A; 
}
FM_INLINE uint32_t FM_CALL SumOfElements(v2u V) {
	return V.X() + V.Y();
}
FM_INLINE uint32_t FM_CALL Length(v2u V) {
	uint32_t X = V.X();
	uint32_t Y = V.Y();
	return (uint32_t)sqrt(X*X + Y*Y);
}
FM_INLINE uint32_t FM_CALL LengthSquared(v2u V) {
	uint32_t X = V.X();
	uint32_t Y = V.Y();
	return X*X + Y*Y;	
}
FM_INLINE v2u FM_CALL Clamp(v2u V, v2u MinV, v2u MaxV) {
	return Min(Max(V, MinV), MaxV);
} 
FM_INLINE bool FM_CALL operator==(v2u A, v2u B) {
	v2u EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y();
} 
FM_INLINE bool FM_CALL operator!=(v2u A, v2u B) {
	v2u EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y());
} 
FM_INLINE v2u FM_CALL EqualsMask(v2u A, v2u B) {
	A.M = _mm_cmpeq_epi32(A.M, B.M);
	return A;
}
FM_INLINE v2u FM_CALL GreaterMask(v2u A, v2u B) {
	A.M = _mm_cmpgt_epi32(A.M, B.M);
	return A;
}
FM_INLINE v2u FM_CALL GreaterOrEqualMask(v2u A, v2u B) {
	__m128i gt = _mm_cmpgt_epi32(A.M, B.M);
	__m128i eq = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(gt, eq);
	return A;
}
FM_INLINE v2u FM_CALL LesserMask(v2u A, v2u B) {
	A.M = _mm_cmplt_epi32(A.M, B.M);
	return A;
}
FM_INLINE v2u FM_CALL LesserOrEqualMask(v2u A, v2u B) {
	__m128i lt = _mm_cmplt_epi32(A.M, B.M);
	__m128i eq = _mm_cmpeq_epi32(A.M, B.M);
	A.M = _mm_or_si128(lt, eq);
	return A;
}
#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INLINE void FM_CALL v2u::SetX(uint32_t X) {
	M = _mm_insert_epi32(M, (int32_t)X, 0);
}
FM_INLINE void FM_CALL v2u::SetY(uint32_t Y) {
	M = _mm_insert_epi32(M, (int32_t)Y, 1);
}
FM_INLINE v2u FM_CALL operator*(v2u V, uint32_t Scalar) {
	V.M = _mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar)); 
	return V; 
}
FM_INLINE v2u FM_CALL operator*(uint32_t Scalar, v2u V) {
	V.M =_mm_mullo_epi32(V.M, _mm_set1_epi32(Scalar));
	return V; 
}
FM_INLINE v2u FM_CALL HadamardMul(v2u A, v2u B) {
	A.M = _mm_mullo_epi32(A.M, B.M);
	return A; 
}
FM_INLINE v2u FM_CALL Min(v2u A, v2u B) {
	A.M = _mm_min_epu32(A.M, B.M);
	return A;
}
FM_INLINE v2u FM_CALL Max(v2u A, v2u B) {
	A.M = _mm_max_epu32(A.M, B.M);
	return A;
}
#else // SSE 2 implementations
FM_INLINE void FM_CALL v2u::SetX(uint32_t x) {
	uint32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, m);
	Arr[0] = x;
	m = _mm_load_si128((__m128i*)Arr);
}
FM_INLINE void FM_CALL v2u::SetY(uint32_t y) {
	uint32_t Arr[4];
	_mm_store_si128((__m128i*)Arr, m);
	Arr[1] = y;
	M = _mm_load_si128((__m128i*)Arr);
	// TODO: This code is repeated. Make utility function!
}
FM_INLINE v2u FM_CALL HadamardMul(v2u A, v2u B) {
	uint32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = AArr[0] * BArr[0]; 
	AArr[1] = AArr[1] * BArr[1]; 
	return V2u(AArr);
}
FM_INLINE v2u FM_CALL operator*(v2u V, uint32_t Scalar) {
	uint32_t VArr[4];
	_mm_store_si128((__m128i*)VArr, V.M);
	VArr[0] *= Scalar;
	VArr[1] *= Scalar;
	return V2u(VArr);
}
FM_INLINE v2u FM_CALL operator*(uint32_t Scalar, v2u V) {
	return V * Scalar;
}
FM_INLINE v2u FM_CALL Min(v2u A, v2u B) {
	uint32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Min(AArr[0], BArr[0]);
	AArr[1] = Min(AArr[1], BArr[1]);
	return V2u(AArr);
}
FM_INLINE v2u FM_CALL Max(v2u A, v2u B) {
	uint32_t AArr[4], BArr[4];
	_mm_store_si128((__m128i*)AArr, A.M);
	_mm_store_si128((__m128i*)BArr, B.M);
	AArr[0] = Max(AArr[0], BArr[0]);
	AArr[1] = Max(AArr[1], BArr[1]);
	return V2u(AArr);
}
#endif

///////////////
// v3 impl //
///////////////
FM_INLINE v3 FM_CALL V3FromMemory(float* V) {
	v3 Res;
	Res.M = _mm_set_ps(0, V[2], V[1], V[0]);
	return Res;
}
FM_INLINE v3 FM_CALL V3(float X, float Y, float Z) {
	v3 Res;
	Res.M = _mm_set_ps(0, Z, Y, X); 
	return Res;
}
FM_INLINE v3 FM_CALL V3(float A) {
	v3 Res;
	Res.M = _mm_set1_ps(A);
	return Res;
}
FM_INLINE v3 FM_CALL V3(__m128 M) {
	v3 Res;
	Res.M = M;
	return Res;
}
FM_INLINE v3 FM_CALL V3() {
	v3 Res;
	Res.M = _mm_setzero_ps();
	return Res;
}
FM_INLINE void FM_CALL v3::SetX(float X) {
	M = priv::SetX(M, X); 
}
FM_INLINE void FM_CALL v3::SetY(float Y) {
	M = priv::SetY(M, Y);
}
FM_INLINE void FM_CALL v3::SetZ(float Z) {
	M = priv::SetZ(M, Z);
}
FM_INLINE void FM_CALL Store(float* Mem, v3 V) {
	Mem[0] = V.X();
	Mem[1] = V.Y();
	Mem[2] = V.Z();
}
FM_INLINE float FM_CALL v3::X() const {
	return priv::GetX(M); 
}
FM_INLINE float FM_CALL v3::Y() const {
	return priv::GetY(M); 
}
FM_INLINE float FM_CALL v3::Z() const {
	return priv::GetZ(M); 
}
#ifndef FM_EXCLUDE_SWIZZLES
FM_INLINE v2 FM_CALL v3::XY() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 0)));
}
FM_INLINE v2 FM_CALL v3::YX() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 1)));
}
FM_INLINE v2 FM_CALL v3::YZ() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 1)));
}
FM_INLINE v2 FM_CALL v3::ZY() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 2)));
}
FM_INLINE v2 FM_CALL v3::XZ() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 0)));
}
FM_INLINE v2 FM_CALL v3::ZX() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 2)));
}
FM_INLINE v2 FM_CALL v3::XX() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 0)));
}
FM_INLINE v2 FM_CALL v3::YY() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 1)));
}
FM_INLINE v2 FM_CALL v3::ZZ() const {
	return V2(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 2)));
}
FM_INLINE v3 FM_CALL v3::XYZ() const {
	return *this;
}
FM_INLINE v3 FM_CALL v3::YZX() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 1)));
}
FM_INLINE v3 FM_CALL v3::ZXY() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 0, 2)));
}
FM_INLINE v3 FM_CALL v3::ZYX() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 2)));
}
FM_INLINE v3 FM_CALL v3::XZY() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 2, 0)));
}
FM_INLINE v3 FM_CALL v3::YXZ() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 0, 1)));
}
FM_INLINE v3 FM_CALL v3::XXY() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 0, 0)));
}
FM_INLINE v3 FM_CALL v3::XXZ() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 0, 0)));
}
FM_INLINE v3 FM_CALL v3::YYX() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 1)));
}
FM_INLINE v3 FM_CALL v3::YYZ() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 1, 1)));
}
FM_INLINE v3 FM_CALL v3::ZZX() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 2)));
}
FM_INLINE v3 FM_CALL v3::ZZY() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 2, 2)));
}
FM_INLINE v3 FM_CALL v3::YXX() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 1)));
}
FM_INLINE v3 FM_CALL v3::ZXX() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 2)));
}
FM_INLINE v3 FM_CALL v3::XYY() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 1, 0)));
}
FM_INLINE v3 FM_CALL v3::ZYY() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 1, 2)));
}
FM_INLINE v3 FM_CALL v3::XZZ() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 2, 0)));
}
FM_INLINE v3 FM_CALL v3::YZZ() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 2, 1)));
}
FM_INLINE v3 FM_CALL v3::XYX() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 1, 0)));
}
FM_INLINE v3 FM_CALL v3::XZX() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 2, 0)));
}
FM_INLINE v3 FM_CALL v3::YXY() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 0, 1)));
}
FM_INLINE v3 FM_CALL v3::YZY() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 2, 1)));
}
FM_INLINE v3 FM_CALL v3::ZXZ() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 0, 2)));
}
FM_INLINE v3 FM_CALL v3::ZYZ() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 1, 2)));
}
FM_INLINE v3 FM_CALL v3::XXX() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 0, 0, 0)));
}
FM_INLINE v3 FM_CALL v3::YYY() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 1, 1, 1)));
}
FM_INLINE v3 FM_CALL v3::ZZZ() const {
	return V3(_mm_shuffle_ps(M, M, _MM_SHUFFLE(0, 2, 2, 2)));
}
#endif
FM_INLINE v3 FM_CALL operator+(v3 A, v3 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_INLINE v3 FM_CALL operator-(v3 A, v3 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_INLINE v3& FM_CALL operator+=(v3& A, v3 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_INLINE v3& FM_CALL operator-=(v3& A, v3 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_INLINE v3 FM_CALL HadamardMul(v3 A, v3 B) {
	A.M = _mm_mul_ps(A.M, B.M);
	return A;
}
FM_INLINE v3 FM_CALL HadamardDiv(v3 A, v3 B) {
	A.M = _mm_div_ps(A.M, B.M);
	return A;
}
FM_INLINE v3 FM_CALL operator*(v3 V, float Scalar) {
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_INLINE v3 FM_CALL operator*(float Scalar, v3 V) {
	return V * Scalar;
}
FM_INLINE v3 FM_CALL operator/(v3 V, float Scalar) {
	V.M = _mm_div_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_INLINE v3 FM_CALL operator-(v3 V) {
	V.M = _mm_sub_ps(_mm_setzero_ps(), V.M);
	return V;
}
FM_INLINE v3 FM_CALL Cross(v3 A, v3 B) {
	return v3(HadamardMul(A.ZXY(), B) - HadamardMul(A, B.ZXY())).ZXY(); 
}
FM_INLINE float FM_CALL Dot(v3 A, v3 B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_INLINE v3 FM_CALL Min(v3 A, v3 B) {
	A.M = _mm_min_ps(A.M, B.M);
	return A;
}
FM_INLINE v3 FM_CALL Max(v3 A, v3 B) {
	A.M = _mm_max_ps(A.M, B.M);
	return A;
}
FM_INLINE v3 FM_CALL Normalize(v3 V) {
	return V / Length(V);
}
FM_INLINE v3 FM_CALL Abs(v3 V) {
	__m128 SignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	V.M = _mm_andnot_ps(SignMask, V.M);
	return V;
}
FM_INLINE float FM_CALL SumOfElements(v3 V) {
	return V.X() + V.Y() + V.Z();
}
FM_INLINE float FM_CALL Length(v3 V) {
	return sqrtf(Dot(V, V));
}
FM_INLINE float FM_CALL LengthSquared(v3 V) {
	return Dot(V, V);
}
FM_INLINE v3 FM_CALL Clamp(v3 V, v3 MinV, v3 MaxV) {
	return Min(Max(V, MinV), MaxV);
}
FM_INLINE v3 FM_CALL Lerp(v3 A, v3 B, float T) {
	return A + (B-A)*T;
} 
FM_INLINE bool FM_CALL operator==(v3 A, v3 B) {
	v3 EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y() && EqMask.Z();
} 
FM_INLINE bool FM_CALL operator!=(v3 A, v3 B) {
	v3 EqMask = EqualsMask(A, B);
	return !(EqMask.X() && EqMask.Y() && EqMask.Z());
}
FM_INLINE v3 FM_CALL EqualsMask(v3 A, v3 B) {
	A.M = _mm_cmpeq_ps(A.M, B.M);
	return A;
}
FM_INLINE v3 FM_CALL GreaterMask(v3 A, v3 B) {
	A.M = _mm_cmpgt_ps(A.M, B.M);
	return A;
}
FM_INLINE v3 FM_CALL GreaterOrEqualMask(v3 A, v3 B) {
	A.M = _mm_cmpge_ps(A.M, B.M);
	return A;
}
FM_INLINE v3 FM_CALL LesserMask(v3 A, v3 B) {
	A.M = _mm_cmplt_ps(A.M, B.M);
	return A;
}
FM_INLINE v3 FM_CALL LesserOrEqualMask(v3 A, v3 B) {
	A.M = _mm_cmple_ps(A.M, B.M);
	return A;
}

///////////////
// v4 impl //
///////////////
FM_INLINE v4 FM_CALL V4FromMemory(const float* V) {
	v4 Res;
	Res.M = _mm_set_ps(V[3], V[2], V[1], V[0]);	
	return Res;
} 
FM_INLINE v4 FM_CALL V4(v3 V, float W) {
	v4 Res;
	V.M = _mm_shuffle_ps(V.M, V.M, _MM_SHUFFLE(2, 1, 0, 0));
	Res.M = _mm_move_ss(V.M, _mm_set_ss(W));
	Res.M = _mm_shuffle_ps(Res.M, Res.M, _MM_SHUFFLE(0, 3, 2, 1));
	return Res;
}
FM_INLINE v4 FM_CALL V4(float X, float Y, float Z, float W) {
	v4 Res;
	Res.M = _mm_set_ps(W, Z, Y, X);
	return Res;
}
FM_INLINE v4 FM_CALL V4(float A) {
	v4 Res;
	Res.M = _mm_set1_ps(A);
	return Res;
}
FM_INLINE v4 FM_CALL V4(__m128 M) {
	v4 Res;
	Res.M = M;
	return Res;
} 
FM_INLINE v4 FM_CALL V4() {
	v4 Res;
	Res.M = _mm_setzero_ps();
	return Res;
}
FM_INLINE void FM_CALL v4::SetX(float X) {
	M = priv::SetX(M, X); 
}
FM_INLINE void FM_CALL v4::SetY(float Y) {
	M = priv::SetY(M, Y);
} 
FM_INLINE void FM_CALL v4::SetZ(float Z) {
	M = priv::SetZ(M, Z);
} 
FM_INLINE void FM_CALL v4::SetW(float W) {
	M = priv::SetW(M, W);
} 
FM_INLINE float FM_CALL v4::X() const {
	return _mm_cvtss_f32(M);
}
FM_INLINE float FM_CALL v4::Y() const {
	return priv::GetY(M); 
}
FM_INLINE float FM_CALL v4::Z() const {
	return priv::GetZ(M); 
}
FM_INLINE float FM_CALL v4::W() const {
	return priv::GetW(M); 
}
FM_INLINE void FM_CALL Store(float* Mem, v4 V) {
	_mm_storeu_ps(Mem, V.M);
}
FM_INLINE void FM_CALL Store16ByteAligned(float* Mem, v4 V) {
	_mm_store_ps(Mem, V.M);
}
FM_INLINE v4 FM_CALL operator+(v4 A, v4 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_INLINE v4 FM_CALL operator-(v4 A, v4 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_INLINE v4& FM_CALL operator+=(v4& A, v4 B) {
	A.M = _mm_add_ps(A.M, B.M);
	return A;
}
FM_INLINE v4& FM_CALL operator-=(v4& A, v4 B) {
	A.M = _mm_sub_ps(A.M, B.M);
	return A;
}
FM_INLINE v4 FM_CALL HadamardMul(v4 A, v4 B) {
	A.M = _mm_mul_ps(A.M, B.M);
	return A;
}
FM_INLINE v4 FM_CALL HadamardDiv(v4 A, v4 B) {
	A.M = _mm_div_ps(A.M, B.M);
	return A;
}
FM_INLINE v4 FM_CALL operator*(v4 V, float Scalar) {
	V.M = _mm_mul_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_INLINE v4 FM_CALL operator*(float Scalar, v4 V) {
	return V * Scalar;
}
FM_INLINE v4 FM_CALL operator/(v4 V, float Scalar) {
	V.M = _mm_div_ps(V.M, _mm_set1_ps(Scalar));
	return V;
}
FM_INLINE v4 FM_CALL operator-(v4 V) {
	V.M = _mm_sub_ps(_mm_setzero_ps(), V.M);
	return V;
}
FM_INLINE float FM_CALL Dot(v4 A, v4 B) {
	return SumOfElements(HadamardMul(A, B));
}
FM_INLINE v4 FM_CALL Min(v4 A, v4 B) {
	A.M = _mm_min_ps(A.M, B.M);
	return A;
}
FM_INLINE v4 FM_CALL Max(v4 A, v4 B) {
	A.M = _mm_max_ps(A.M, B.M);
	return A;
}
FM_INLINE v4 FM_CALL Abs(v4 V) {
	__m128 SignMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	V.M = _mm_andnot_ps(SignMask, V.M);
	return V;
}
FM_INLINE float FM_CALL SumOfElements(v4 V) {
	return V.X() + V.Y() + V.Z() + V.W();
}
FM_INLINE float FM_CALL Length(v4 V) {
	return sqrtf(Dot(V, V));
}
FM_INLINE float FM_CALL LengthSquared(v4 V) {
	return Dot(V, V);
}
FM_INLINE v4 FM_CALL Normalize(v4 V) {
	return V / Length(V);
}
FM_INLINE v4 FM_CALL Clamp(v4 V, v4 MinV, v4 MaxV) {
	return Min(Max(V, MinV), MaxV);
}
FM_INLINE v4 FM_CALL Lerp(v4 A, v4 B, float T) {
	return A + (B-A)*T;
} 
FM_INLINE bool FM_CALL operator==(v4 A, v4 B) {
	v4 EqMask = EqualsMask(A, B);
	return EqMask.X() && EqMask.Y() && EqMask.Z() && EqMask.W();
} 
FM_INLINE bool FM_CALL operator!=(v4 A, v4 B) {
	return !(A == B);
}
FM_INLINE v4 FM_CALL EqualsMask(v4 A, v4 B) {
	A.M = _mm_cmpeq_ps(A.M, B.M);
	return A;
}
FM_INLINE v4 FM_CALL GreaterMask(v4 A, v4 B) {
	A.M = _mm_cmpgt_ps(A.M, B.M);
	return A;
}
FM_INLINE v4 FM_CALL GreaterOrEqualMask(v4 A, v4 B) {
	A.M = _mm_cmpge_ps(A.M, B.M);
	return A;
}
FM_INLINE v4 FM_CALL LesserMask(v4 A, v4 B) {
	A.M = _mm_cmplt_ps(A.M, B.M);
	return A;
}
FM_INLINE v4 FM_CALL LesserOrEqualMask(v4 A, v4 B) {
	A.M = _mm_cmple_ps(A.M, B.M);
	return A;
}

///////////////
// mat4 impl //
///////////////
FM_INLINE v4 FM_CALL mat4::GetColumn(uint32_t Index) {
	return V4(Columns[Index]);
}
FM_INLINE void FM_CALL mat4::SetColumn(uint32_t Index, v4 Col) {
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
v4 FM_CALL mat4::GetRow(uint32_t Index) {
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
	SetRow(Index, V4(X, Y, Z, W));
}
FM_INLINE void FM_CALL mat4::SwapRows(uint32_t Row1Index, uint32_t Row2Index) {
	v4 Row1 = GetRow(Row1Index);
	v4 Row2 = GetRow(Row2Index);
	SetRow(Row2Index, Row1);
	SetRow(Row1Index, Row2);
}
FM_INLINE v4 FM_CALL mat4::GetMainDiagonal() {
	v4 Res;
	Res.SetX(priv::GetX(Columns[0]));
	Res.SetY(priv::GetY(Columns[1]));
	Res.SetZ(priv::GetZ(Columns[2]));
	Res.SetW(priv::GetW(Columns[3]));
	return Res;
}
FM_INLINE void FM_CALL mat4::SetMainDiagonal(float x, float y, float z, float w) {
	Columns[0] = priv::SetX(Columns[0], x);
	Columns[1] = priv::SetY(Columns[1], y);
	Columns[2] = priv::SetZ(Columns[2], z);
	Columns[3] = priv::SetW(Columns[3], w);
}
FM_INLINE void FM_CALL mat4::SetMainDiagonal(v4 V) {
	SetMainDiagonal(V.X(), V.Y(), V.Z(), V.W());
}
FM_INLINE mat4 FM_CALL Mat4FromColumnMajorMemory(float* Mem) {
	mat4 Res;
	for(int32_t i = 0; i < 4; ++i)
		Res.Columns[i] = _mm_load_ps(Mem + i*4);
	return Res;
}
FM_INLINE mat4 FM_CALL Mat4() {
	mat4 Res;
	Res.Columns[0] = _mm_setzero_ps();
	Res.Columns[1] = _mm_setzero_ps();
	Res.Columns[2] = _mm_setzero_ps();
	Res.Columns[3] = _mm_setzero_ps();
	return Res;
}
FM_INLINE mat4 FM_CALL Mat4Identity() {
	return Mat4Diagonal(1.f);
}
FM_INLINE mat4 FM_CALL Mat4Diagonal(float Diag) {
	mat4 Res;
	Res.Columns[0] = _mm_setr_ps(Diag, 0.f, 0.f, 0.f);
	Res.Columns[1] = _mm_setr_ps(0.f, Diag, 0.f, 0.f);
	Res.Columns[2] = _mm_setr_ps(0.f, 0.f, Diag, 0.f);
	Res.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, Diag);
	return Res;
}
FM_INLINE mat4 FM_CALL Mat4Diagonal(float DiagX, float DiagY, float DiagZ, float DiagW) {
	mat4 Res;
	Res.Columns[0] = _mm_setr_ps(DiagX, 0.f, 0.f, 0.f);
	Res.Columns[1] = _mm_setr_ps(0.f, DiagY, 0.f, 0.f);
	Res.Columns[2] = _mm_setr_ps(0.f, 0.f, DiagZ, 0.f);
	Res.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, DiagW);
	return Res;
}
FM_INLINE mat4 FM_CALL Mat4Diagonal(v4 Diag) {
	// TODO: What is going on with Diag.X() Diag.Y()... 
	mat4 Res;
	float* V = (float*)(&Diag);
	Res.Columns[0] = _mm_set_ps(0.f, 0.f, 0.f, V[0]);
	Res.Columns[1] = _mm_set_ps(0.f, 0.f, V[1], 0.f);
	Res.Columns[2] = _mm_set_ps(0.f, V[2], 0.f, 0.f);
	Res.Columns[3] = _mm_set_ps(V[3], 0.f, 0.f, 0.f);
	return Res;
}
FM_INLINE mat4 FM_CALL Mat4FromColumns(v4 Col1, v4 Col2, v4 Col3, v4 Col4) {
	mat4 Res;
	Res.Columns[0] = Col1.M;
	Res.Columns[1] = Col2.M;
	Res.Columns[2] = Col3.M;
	Res.Columns[3] = Col4.M;
	return Res;
}
FM_INLINE mat4 FM_CALL Mat4FromColumns(v3 Col1, v3 Col2, v3 Col3, v3 Col4) {
	mat4 Res;
	Res.Columns[0] = Col1.M;
	Res.Columns[1] = Col2.M;
	Res.Columns[2] = Col3.M;
	Res.Columns[3] = Col4.M;
	Res.SetRow(3, 0.f, 0.f, 0.f, 1.f);
	return Res;
}
FM_INLINE mat4 FM_CALL Mat4FromColumns(
	float E11, float E21, float E31, float E41,
    float E12, float E22, float E32, float E42,
    float E13, float E23, float E33, float E43,
    float E14, float E24, float E34, float E44) 
{
	mat4 Res;
	Res.Columns[0] = _mm_setr_ps(E11, E21, E31, E41);
	Res.Columns[1] = _mm_setr_ps(E12, E22, E32, E42);
	Res.Columns[2] = _mm_setr_ps(E13, E23, E33, E43);
	Res.Columns[3] = _mm_setr_ps(E14, E24, E34, E44);
	return Res;
}
FM_INLINE mat4 FM_CALL Mat4FromRows(v4 Row1, v4 Row2, v4 Row3, v4 Row4) {
	mat4 Res;
	Res.Columns[0] = _mm_setr_ps(Row1.X(), Row2.X(), Row3.X(), Row4.X());
	Res.Columns[1] = _mm_setr_ps(Row1.Y(), Row2.Y(), Row3.Y(), Row4.Y());
	Res.Columns[2] = _mm_setr_ps(Row1.Z(), Row2.Z(), Row3.Z(), Row4.Z());
	Res.Columns[3] = _mm_setr_ps(Row1.W(), Row2.W(), Row3.W(), Row4.W());
	return Res;
}
FM_INLINE mat4 FM_CALL Mat4FromRows(v3 Row1, v3 Row2, v3 Row3, v3 Row4) {
	mat4 Res;
	Res.Columns[0] = _mm_setr_ps(Row1.X(), Row2.X(), Row3.X(), Row4.X());
	Res.Columns[1] = _mm_setr_ps(Row1.Y(), Row2.Y(), Row3.Y(), Row4.Y());
	Res.Columns[2] = _mm_setr_ps(Row1.Z(), Row2.Z(), Row3.Z(), Row4.Z());
	Res.Columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, 1.f);
	return Res;
}
FM_INLINE mat4 FM_CALL Mat4FromRows(
	float E11, float E12, float E13, float E14,
    float E21, float E22, float E23, float E24,
    float E31, float E32, float E33, float E34,
    float E41, float E42, float E43, float E44)
{
	mat4 Res;
	Res.Columns[0] = _mm_setr_ps(E11, E21, E31, E41);
	Res.Columns[1] = _mm_setr_ps(E12, E22, E32, E42);
	Res.Columns[2] = _mm_setr_ps(E13, E23, E33, E43);
	Res.Columns[3] = _mm_setr_ps(E14, E24, E34, E44);
	return Res;
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
	float Res11 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[0]));
	float Res12 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[1]));
	float Res13 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[2]));
	float Res14 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[3]));
		
	Row = _mm_setr_ps(priv::GetY(A.Columns[0]), priv::GetY(A.Columns[1]),
	                  priv::GetY(A.Columns[2]), priv::GetY(A.Columns[3]));
	float Res21 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[0]));
	float Res22 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[1]));
	float Res23 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[2]));
	float Res24 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[3]));
		
	Row = _mm_setr_ps(priv::GetZ(A.Columns[0]), priv::GetZ(A.Columns[1]),
	                  priv::GetZ(A.Columns[2]), priv::GetZ(A.Columns[3]));
	float Res31 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[0]));
	float Res32 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[1]));
	float Res33 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[2]));
	float Res34 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[3]));
		
	Row = _mm_setr_ps(priv::GetW(A.Columns[0]), priv::GetW(A.Columns[1]),
	                  priv::GetW(A.Columns[2]), priv::GetW(A.Columns[3]));
	float Res41 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[0]));
	float Res42 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[1]));
	float Res43 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[2]));
	float Res44 = priv::SumOfElements(_mm_mul_ps(Row, B.Columns[3]));
		
	return Mat4FromColumns(
		Res11, Res21, Res31, Res41,
	    Res12, Res22, Res32, Res42,
		Res13, Res23, Res33, Res43,
		Res14, Res24, Res34, Res44);
}
FM_INLINE v4 FM_CALL operator*(mat4 M, v4 V) {
	__m128 Row1 = _mm_setr_ps(priv::GetX(M.Columns[0]), priv::GetX(M.Columns[1]),
	                          priv::GetX(M.Columns[2]), priv::GetX(M.Columns[3]));
	__m128 Row2 = _mm_setr_ps(priv::GetY(M.Columns[0]), priv::GetY(M.Columns[1]),
	                          priv::GetY(M.Columns[2]), priv::GetY(M.Columns[3]));
	__m128 Row3 = _mm_setr_ps(priv::GetZ(M.Columns[0]), priv::GetZ(M.Columns[1]),
	                          priv::GetZ(M.Columns[2]), priv::GetZ(M.Columns[3]));
	__m128 Row4 = _mm_setr_ps(priv::GetW(M.Columns[0]), priv::GetW(M.Columns[1]),
	                          priv::GetW(M.Columns[2]), priv::GetW(M.Columns[3]));
	float ResX = priv::SumOfElements(_mm_mul_ps(Row1, V.M)); 
	float ResY = priv::SumOfElements(_mm_mul_ps(Row2, V.M)); 
	float ResZ = priv::SumOfElements(_mm_mul_ps(Row3, V.M)); 
	float ResW = priv::SumOfElements(_mm_mul_ps(Row4, V.M));
	return V4(ResX, ResY, ResZ, ResW);
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
FM_INLINE mat4 FM_CALL Mat4Translation(v3 Translation) {
	return Mat4FromRows(
		1.f, 0.f, 0.f, Translation.X(),
		0.f, 1.f, 0.f, Translation.Y(),
		0.f, 0.f, 1.f, Translation.Z(),
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL Translate(mat4 M, float X, float Y, float Z) {
	M.Columns[3] = _mm_add_ps(M.Columns[3], _mm_set_ps(0.f, Z, Y, X));
	return M;
}
FM_INLINE mat4 FM_CALL Translate(mat4 M, v3 Translation) {
	M.Columns[3] = _mm_add_ps(M.Columns[3], Translation.M);
	return M;
}
FM_INLINE mat4 FM_CALL Mat4Scale(float Scalar) {
	return Mat4Diagonal(Scalar, Scalar, Scalar, 1.f);
} 
FM_INLINE mat4 FM_CALL Mat4Scale(float ScalarX, float ScalarY, float ScalarZ) {
	return Mat4Diagonal(ScalarX, ScalarY, ScalarZ, 1.f);
} 
FM_INLINE mat4 FM_CALL Mat4Scale(v3 Scalar) {
	return Mat4Diagonal(Scalar.X(), Scalar.Y(), Scalar.Z(), 1.f); 
}
FM_INLINE mat4 FM_CALL Scale(mat4 M, float Scalar) {
	return Scale(M, Scalar, Scalar, Scalar);
}
FM_INLINE mat4 FM_CALL Scale(mat4 M, float X, float Y, float Z) {
	v4 MainDiag = M.GetMainDiagonal();
	v4 ScalarVec = V4(X, Y, Z, 1.f);
	MainDiag = HadamardMul(MainDiag, ScalarVec);
	M.SetMainDiagonal(MainDiag);
	return M;
}
FM_INLINE mat4 FM_CALL Scale(mat4 M, v3 Scalar) {
	v4 MainDiag = M.GetMainDiagonal();
	MainDiag.M = _mm_mul_ps(MainDiag.M, Scalar.M);
	MainDiag.M = priv::SetW(MainDiag.M, 1.f);
	M.SetMainDiagonal(MainDiag);
	return M;
}
FM_INLINE mat4 FM_CALL Mat4RotationDegrees(float Degrees, float AxisX, float AxisY, float AxisZ) {
	float R = DegreesToRadians(Degrees);
	return Mat4RotationRadians(R, AxisX, AxisY, AxisZ);
} 
FM_INLINE mat4 FM_CALL Mat4RotationDegrees(float Degrees, v3 Axis) {
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
FM_INLINE mat4 FM_CALL RotateDegrees(mat4 M, float Degrees, float AxisX, float AxisY, float AxisZ) {
	float R = DegreesToRadians(Degrees);
	return RotateRadians(M, R, AxisX, AxisY, AxisZ);
} 
FM_INLINE mat4 FM_CALL RotateDegrees(mat4 M, float Degrees, v3 Axis) {
	float R = DegreesToRadians(Degrees);
	return RotateRadians(M, R, Axis);
}
FM_INLINE mat4 FM_CALL RotateAroundXAxisDegrees(mat4 M, float Degrees) {
	float r = DegreesToRadians(Degrees);
	return RotateAroundXAxisRadians(M, r);
}
FM_INLINE mat4 FM_CALL RotateAroundYAxisDegrees(mat4 M, float Degrees) {
	float r = DegreesToRadians(Degrees);
	return RotateAroundYAxisRadians(M, r);
}
FM_INLINE mat4 FM_CALL RotateAroundZAxisDegrees(mat4 M, float Degrees) {
	float r = DegreesToRadians(Degrees);
	return RotateAroundZAxisRadians(M, r);
}
FM_INLINE mat4 FM_CALL Mat4RotationRadians(float Radians, float AxisX, float AxisY, float AxisZ) {
	v3 Normalized = Normalize(V3(AxisX, AxisY, AxisZ));
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
FM_INLINE mat4 FM_CALL Mat4RotationRadians(float Radians, v3 Axis) {
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
FM_INLINE mat4 FM_CALL RotateRadians(mat4 M, float Radians, float AxisX, float AxisY, float AxisZ) {
	mat4 RotMat = Mat4RotationRadians(Radians, AxisX, AxisY, AxisZ);
	return M * RotMat;
}
FM_INLINE mat4 FM_CALL RotateRadians(mat4 M, float Radians, v3 Axis) {
	mat4 RotMat = Mat4RotationRadians(Radians, Axis);
	return M * RotMat;
}
FM_INLINE mat4 FM_CALL RotateAroundXAxisRadians(mat4 M, float Radians) {
	mat4 RotMat = Mat4RotationAroundXAxisRadians(Radians);
	return M * RotMat;	
}
FM_INLINE mat4 FM_CALL RotateAroundYAxisRadians(mat4 M, float Radians) {
	mat4 RotMat = Mat4RotationAroundYAxisRadians(Radians);
	return M * RotMat;
}
FM_INLINE mat4 FM_CALL RotateAroundZAxisRadians(mat4 M, float Radians) {
	mat4 RotMat = Mat4RotationAroundZAxisRadians(Radians);
	return M * RotMat;
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
FM_INLINE mat4 FM_CALL ShearXAxis(mat4 M, float Y, float Z) {
	mat4 ShearMat = Mat4ShearXAxis(Y, Z);
	return M * ShearMat;
}
FM_INLINE mat4 FM_CALL ShearYAxis(mat4 M, float X, float Z) {
	mat4 ShearMat = Mat4ShearYAxis(X, Z);
	return M * ShearMat;
} 
FM_INLINE mat4 FM_CALL ShearZAxis(mat4 M, float X, float Y) {
	mat4 ShearMat = Mat4ShearZAxis(X, Y);
	return M * ShearMat;
} 
FM_INLINE mat4 FM_CALL Shear(mat4 M, float XY, float XZ, float YX, float YZ, float ZX, float ZY) {
	mat4 ShearMat = Mat4Shear(XY, XZ, YX, YZ, ZX, ZY);
	return M * ShearMat;
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
mat4 LookAt(v3 Eye, v3 At, v3 Up) {
	v3 Forward = Normalize(Eye - At);
	v3 Right = Cross(Forward, Up); // TODO(docs): We assume that Up is normalized
	Up = Cross(Forward, Right);
	return Mat4FromColumns(Right, Up, Forward, Eye);
}

} // !namespace fm

#ifdef _MSC_VER
	#pragma warning(pop)
#endif

#endif // FM_IMPLEMENTATION
#endif // FM_IMPLEMENTATION_ALREADY_DEFINED

