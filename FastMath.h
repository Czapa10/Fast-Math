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

// TODO: make FM_INLINE work on all compilers

#define FM_INLINE __forceinline
#define FM_CALL __vectorcall

#define FM_PI32 3.14159265359f
#define FM_PI64 3.14159265358979323846

namespace fm {

FM_INLINE float min(float a, float b);
FM_INLINE float max(float a, float b);
FM_INLINE double min(double a, double b);
FM_INLINE double max(double a, double b);
FM_INLINE int min(int a, int b);
FM_INLINE int max(int a, int b);
FM_INLINE unsigned min(unsigned a, unsigned b);
FM_INLINE unsigned max(unsigned a, unsigned b);

FM_INLINE float abs(float a); 
FM_INLINE double abs(double a); 
FM_INLINE int abs(int a);

FM_INLINE float radiansToDegrees(float radians);
FM_INLINE double radiansToDegrees(double radians);
FM_INLINE float degreesToRadians(float degrees);
FM_INLINE double degreesToRadians(double degrees);

struct vec2
{
	__m128 m;

	FM_INLINE void FM_CALL setX(float x);
	FM_INLINE void FM_CALL setY(float y); 

	FM_INLINE float FM_CALL x() const;
	FM_INLINE float FM_CALL u() const { return x(); }
	FM_INLINE float FM_CALL left() const { return x(); }
	FM_INLINE float FM_CALL width() const { return x(); }

	FM_INLINE float FM_CALL y() const;
	FM_INLINE float FM_CALL v() const { return y(); }
	FM_INLINE float FM_CALL top() const { return y(); }
	FM_INLINE float FM_CALL height() const { return y(); }

	FM_INLINE vec2 FM_CALL yx() const;
	FM_INLINE vec2 FM_CALL xx() const;
	FM_INLINE vec2 FM_CALL yy() const;

#ifndef FM_EXCLUDE_TEX_COORD_SWIZZLES
	FM_INLINE vec2 FM_CALL vu() const { return yx(); }
	FM_INLINE vec2 FM_CALL uu() const { return xx(); }
	FM_INLINE vec2 FM_CALL vv() const { return yy(); }
#endif
};

FM_INLINE vec2 FM_CALL makeVec2FromMemory(const float* v); 
FM_INLINE vec2 FM_CALL makeVec2(float x, float y);
FM_INLINE vec2 FM_CALL makeVec2(float a);
FM_INLINE vec2 FM_CALL makeVec2(__m128 m);
FM_INLINE vec2 FM_CALL makeZeroVec2();

FM_INLINE void FM_CALL store(float* mem, vec2 v);

FM_INLINE vec2 FM_CALL operator+(vec2 a, vec2 b);
FM_INLINE vec2 FM_CALL operator-(vec2 a, vec2 b);
FM_INLINE vec2& FM_CALL operator+=(vec2& a, vec2 b);
FM_INLINE vec2& FM_CALL operator-=(vec2& a, vec2 b);
FM_INLINE vec2 FM_CALL hadamardMul(vec2 a, vec2 b);
FM_INLINE vec2 FM_CALL hadamardDiv(vec2 a, vec2 b);
FM_INLINE vec2 FM_CALL operator*(vec2 v, float scalar);
FM_INLINE vec2 FM_CALL operator*(float scalar, vec2 v);
FM_INLINE vec2 FM_CALL operator/(vec2 v, float scalar); 
FM_INLINE vec2 FM_CALL operator-(vec2 v); 
FM_INLINE float FM_CALL dot(vec2 a, vec2 b); 
FM_INLINE vec2 FM_CALL min(vec2 a, vec2 b); 
FM_INLINE vec2 FM_CALL max(vec2 a, vec2 b); 
FM_INLINE vec2 FM_CALL abs(vec2 v); 
FM_INLINE float FM_CALL sumOfElements(vec2 v);
FM_INLINE float FM_CALL length(vec2 v);
FM_INLINE float FM_CALL lengthSquared(vec2 v); 
FM_INLINE vec2 FM_CALL normalize(vec2 v);
FM_INLINE vec2 FM_CALL clamp(vec2 v, vec2 min, vec2 max);
FM_INLINE vec2 FM_CALL lerp(vec2 a, vec2 b, float t);

FM_INLINE bool FM_CALL operator==(vec2 a, vec2 b); 
FM_INLINE bool FM_CALL operator!=(vec2 a, vec2 b); 
FM_INLINE vec2 FM_CALL equalsMask(vec2 a, vec2 b);
FM_INLINE vec2 FM_CALL greaterMask(vec2 a, vec2 b);
FM_INLINE vec2 FM_CALL greaterOrEqualMask(vec2 a, vec2 b);
FM_INLINE vec2 FM_CALL lesserMask(vec2 a, vec2 b);
FM_INLINE vec2 FM_CALL lesserOrEqualMask(vec2 a, vec2 b);

struct vec2d
{
	__m128d m;

	FM_INLINE void FM_CALL setX(double x);
	FM_INLINE void FM_CALL setY(double y);

	FM_INLINE double FM_CALL x() const;
	FM_INLINE double FM_CALL u() const { return x(); }
	FM_INLINE double FM_CALL left() const { return x(); }
	FM_INLINE double FM_CALL width() const { return x(); }

	FM_INLINE double FM_CALL y() const;
	FM_INLINE double FM_CALL v() const { return y(); }
	FM_INLINE double FM_CALL height() const { return y(); }
	FM_INLINE double FM_CALL top() const { return y(); }

	FM_INLINE vec2d FM_CALL yx() const;
	FM_INLINE vec2d FM_CALL xx() const;
	FM_INLINE vec2d FM_CALL yy() const;

	FM_INLINE vec2d FM_CALL vu() const { return yx(); }
	FM_INLINE vec2d FM_CALL uu() const { return xx(); }
	FM_INLINE vec2d FM_CALL vv() const { return yy(); }
};

FM_INLINE vec2d FM_CALL makeVec2dFromMemory(const double* v);
FM_INLINE vec2d FM_CALL makeVec2d(double x, double y);
FM_INLINE vec2d FM_CALL makeVec2d(double a);
FM_INLINE vec2d FM_CALL makeVec2d (__m128d m);
FM_INLINE vec2d FM_CALL makeZeroVec2d();

FM_INLINE void FM_CALL store(double* mem, vec2d v);
FM_INLINE void FM_CALL store16ByteAligned(double* mem, vec2d v);

FM_INLINE vec2d FM_CALL operator+(vec2d a, vec2d b); 
FM_INLINE vec2d FM_CALL operator-(vec2d a, vec2d b);
FM_INLINE vec2d& FM_CALL operator+=(vec2d& a, vec2d b);
FM_INLINE vec2d& FM_CALL operator-=(vec2d& a, vec2d b);
FM_INLINE vec2d FM_CALL hadamardMul(vec2d a, vec2d b);
FM_INLINE vec2d FM_CALL hadamardDiv(vec2d a, vec2d b);
FM_INLINE vec2d FM_CALL operator*(vec2d v, double scalar);
FM_INLINE vec2d FM_CALL operator*(double scalar, vec2d v);
FM_INLINE vec2d FM_CALL operator/(vec2d v, double scalar);
FM_INLINE vec2d FM_CALL operator-(vec2d v); 
FM_INLINE double FM_CALL dot(vec2d a, vec2d b); 
FM_INLINE vec2d FM_CALL min(vec2d a, vec2d b); 
FM_INLINE vec2d FM_CALL max(vec2d a, vec2d b); 
FM_INLINE vec2d FM_CALL normalize(vec2d v);
FM_INLINE vec2d FM_CALL abs(vec2d v);
FM_INLINE double FM_CALL sumOfElements(vec2d v);
FM_INLINE double FM_CALL length(vec2d v);
FM_INLINE double FM_CALL lengthSquared(vec2d v); 
FM_INLINE vec2d FM_CALL clamp(vec2d v, vec2d min, vec2d max); 
FM_INLINE vec2d FM_CALL lerp(vec2d a, vec2d b, double t);

FM_INLINE bool FM_CALL operator==(vec2d a, vec2d b); 
FM_INLINE bool FM_CALL operator!=(vec2d a, vec2d b); 
FM_INLINE vec2d FM_CALL equalsMask(vec2d a, vec2d b);
FM_INLINE vec2d FM_CALL greaterMask(vec2d a, vec2d b);
FM_INLINE vec2d FM_CALL greaterOrEqualMask(vec2d a, vec2d b);
FM_INLINE vec2d FM_CALL lesserMask(vec2d a, vec2d b);
FM_INLINE vec2d FM_CALL lesserOrEqualMask(vec2d a, vec2d b);

struct vec2i
{
	__m128i m;

	FM_INLINE int FM_CALL x() const;
	FM_INLINE int FM_CALL u() const { return x(); }
	FM_INLINE int FM_CALL left() const { return x(); }
	FM_INLINE int FM_CALL width() const { return x(); }

	FM_INLINE int FM_CALL y() const;
	FM_INLINE int FM_CALL v() const { return y(); }
	FM_INLINE int FM_CALL top() const { return y(); }
	FM_INLINE int FM_CALL height() const { return y(); }

	FM_INLINE vec2i FM_CALL yx() const;
	FM_INLINE vec2i FM_CALL xx() const;
	FM_INLINE vec2i FM_CALL yy() const;

	FM_INLINE vec2i FM_CALL vu() const { return yx(); }
	FM_INLINE vec2i FM_CALL uu() const { return xx(); }
	FM_INLINE vec2i FM_CALL vv() const { return yy(); }

	FM_INLINE void FM_CALL setX(int x);
	FM_INLINE void FM_CALL setY(int y);
};
FM_INLINE vec2i FM_CALL makeVec2iFromMemory(const int* v);
FM_INLINE vec2i FM_CALL makeVec2i(int x, int y);
FM_INLINE vec2i FM_CALL makeVec2i(int a); 
FM_INLINE vec2i FM_CALL makeVec2i(__m128i m); 
FM_INLINE vec2i FM_CALL makeZeroVec2i();

FM_INLINE void FM_CALL store(int* mem, vec2i v); 

FM_INLINE vec2i FM_CALL operator+(vec2i a, vec2i b);
FM_INLINE vec2i FM_CALL operator-(vec2i a, vec2i b); 
FM_INLINE vec2i& FM_CALL operator+=(vec2i& a, vec2i b);
FM_INLINE vec2i& FM_CALL operator-=(vec2i& a, vec2i b);
FM_INLINE vec2i FM_CALL hadamardMul(vec2i a, vec2i b);
FM_INLINE vec2i FM_CALL operator*(vec2i v, int scalar); 
FM_INLINE vec2i FM_CALL operator*(int scalar, vec2i v);
FM_INLINE vec2i FM_CALL operator-(vec2i v); 
FM_INLINE vec2i FM_CALL min(vec2i a, vec2i b); 
FM_INLINE vec2i FM_CALL max(vec2i a, vec2i b); 
FM_INLINE vec2i FM_CALL abs(vec2i v); 
FM_INLINE int FM_CALL sumOfElements(vec2i v);
FM_INLINE int FM_CALL length(vec2i v);
FM_INLINE int FM_CALL lengthSquared(vec2i v); 
FM_INLINE vec2i FM_CALL clamp(vec2i v, vec2i min, vec2i max); 

FM_INLINE bool FM_CALL operator==(vec2i a, vec2i b); 
FM_INLINE bool FM_CALL operator!=(vec2i a, vec2i b); 
FM_INLINE vec2i FM_CALL equalsMask(vec2i a, vec2i b);
FM_INLINE vec2i FM_CALL greaterMask(vec2i a, vec2i b);
FM_INLINE vec2i FM_CALL greaterOrEqualMask(vec2i a, vec2i b);
FM_INLINE vec2i FM_CALL lesserMask(vec2i a, vec2i b);
FM_INLINE vec2i FM_CALL lesserOrEqualMask(vec2i a, vec2i b);
// TODO: Add hadamardDiv() and operator/ - Maybe I can do that using cast instructions?

struct vec2u
{
	__m128i m;

	FM_INLINE void FM_CALL setX(unsigned x);
	FM_INLINE void FM_CALL setY(unsigned y);

	FM_INLINE unsigned FM_CALL x() const;
	FM_INLINE unsigned FM_CALL u() const { return x(); }
	FM_INLINE unsigned FM_CALL left() const { return x(); }
	FM_INLINE unsigned FM_CALL width() const { return x(); }

	FM_INLINE unsigned FM_CALL y() const;
	FM_INLINE unsigned FM_CALL v() const { return y(); }
	FM_INLINE unsigned FM_CALL top() const { return y(); }
	FM_INLINE unsigned FM_CALL height() const { return y(); }

	FM_INLINE vec2u FM_CALL yx() const;
	FM_INLINE vec2u FM_CALL xx() const;
	FM_INLINE vec2u FM_CALL yy() const;

	FM_INLINE vec2u FM_CALL vu() const { return yx(); }
	FM_INLINE vec2u FM_CALL uu() const { return xx(); }
	FM_INLINE vec2u FM_CALL vv() const { return yy(); }
};

FM_INLINE vec2u FM_CALL makeVec2uFromMemory(const unsigned* v); 
FM_INLINE vec2u FM_CALL makeVec2u(unsigned x, unsigned y); 
FM_INLINE vec2u FM_CALL makeVec2u(unsigned a);
FM_INLINE vec2u FM_CALL makeVec2u(__m128i m);
FM_INLINE vec2u FM_CALL makeZeroVec2u();

FM_INLINE void FM_CALL store(unsigned* mem, vec2u v);

FM_INLINE vec2u FM_CALL operator+(vec2u a, vec2u b);
FM_INLINE vec2u FM_CALL operator-(vec2u a, vec2u b);
FM_INLINE vec2u& FM_CALL operator+=(vec2u& a, vec2u b);
FM_INLINE vec2u& FM_CALL operator-=(vec2u& a, vec2u b);
FM_INLINE vec2u FM_CALL hadamardMul(vec2u a, vec2u b);
FM_INLINE vec2u FM_CALL operator*(vec2u v, unsigned scalar); 
FM_INLINE vec2u FM_CALL operator*(unsigned scalar, vec2u v);
FM_INLINE vec2u FM_CALL min(vec2u a, vec2u b); 
FM_INLINE vec2u FM_CALL max(vec2u a, vec2u b); 
FM_INLINE unsigned FM_CALL sumOfElements(vec2u v);
FM_INLINE unsigned FM_CALL length(vec2u v);
FM_INLINE unsigned FM_CALL lengthSquared(vec2u v); 
FM_INLINE vec2u FM_CALL clamp(vec2u v, vec2u min, vec2u max); 

FM_INLINE bool FM_CALL operator==(vec2u a, vec2u b); 
FM_INLINE bool FM_CALL operator!=(vec2u a, vec2u b); 
FM_INLINE vec2u FM_CALL equalsMask(vec2u a, vec2u b);
FM_INLINE vec2u FM_CALL greaterMask(vec2u a, vec2u b);
FM_INLINE vec2u FM_CALL greaterOrEqualMask(vec2u a, vec2u b);
FM_INLINE vec2u FM_CALL lesserMask(vec2u a, vec2u b);
FM_INLINE vec2u FM_CALL lesserOrEqualMask(vec2u a, vec2u b);

// TODO: Add hadamardDiv() and operator/

struct vec3
{
	__m128 m;

	FM_INLINE void FM_CALL setX(float x);
	FM_INLINE void FM_CALL setY(float y);
	FM_INLINE void FM_CALL setZ(float z);

	FM_INLINE float FM_CALL x() const;
	FM_INLINE float FM_CALL u() const { return x(); }
	FM_INLINE float FM_CALL r() const { return x(); }

	FM_INLINE float FM_CALL y() const;
	FM_INLINE float FM_CALL v() const { return y(); }
	FM_INLINE float FM_CALL g() const { return y(); }

	FM_INLINE float FM_CALL z() const;
	FM_INLINE float FM_CALL w() const { return z(); }
	FM_INLINE float FM_CALL b() const { return z(); }

	FM_INLINE vec2 FM_CALL xy() const;
	FM_INLINE vec2 FM_CALL yx() const;
	FM_INLINE vec2 FM_CALL yz() const;
	FM_INLINE vec2 FM_CALL zy() const;
	FM_INLINE vec2 FM_CALL xz() const;
	FM_INLINE vec2 FM_CALL zx() const;
	FM_INLINE vec2 FM_CALL xx() const;
	FM_INLINE vec2 FM_CALL yy() const;
	FM_INLINE vec2 FM_CALL zz() const;

#ifndef FM_EXCLUDE_TEX_COORD_SWIZZLES
	FM_INLINE vec2 FM_CALL uv() const { return xy(); }
	FM_INLINE vec2 FM_CALL vu() const { return yx(); }
	FM_INLINE vec2 FM_CALL vw() const { return yz(); }
	FM_INLINE vec2 FM_CALL wv() const { return zy(); }
	FM_INLINE vec2 FM_CALL uw() const { return xz(); }
	FM_INLINE vec2 FM_CALL wu() const { return zx(); }
	FM_INLINE vec2 FM_CALL uu() const { return xx(); }
	FM_INLINE vec2 FM_CALL vv() const { return yy(); }
	FM_INLINE vec2 FM_CALL ww() const { return zz(); }
#endif

#ifndef FM_EXCLUDE_COLOR_SWIZZLES
	FM_INLINE vec2 FM_CALL rg() const { return xy(); }
	FM_INLINE vec2 FM_CALL gr() const { return yx(); }
	FM_INLINE vec2 FM_CALL gb() const { return yz(); }
	FM_INLINE vec2 FM_CALL bg() const { return zy(); }
	FM_INLINE vec2 FM_CALL rb() const { return xz(); }
	FM_INLINE vec2 FM_CALL br() const { return zx(); }
	FM_INLINE vec2 FM_CALL rr() const { return xx(); }
	FM_INLINE vec2 FM_CALL gg() const { return yy(); }
	FM_INLINE vec2 FM_CALL bb() const { return zz(); }
#endif

	FM_INLINE vec3 FM_CALL xyz() const;
	FM_INLINE vec3 FM_CALL yzx() const;
	FM_INLINE vec3 FM_CALL zxy() const;
	FM_INLINE vec3 FM_CALL zyx() const;
	FM_INLINE vec3 FM_CALL xzy() const;
	FM_INLINE vec3 FM_CALL yxz() const;
	FM_INLINE vec3 FM_CALL xxy() const;
	FM_INLINE vec3 FM_CALL xxz() const;
	FM_INLINE vec3 FM_CALL yyx() const;
	FM_INLINE vec3 FM_CALL yyz() const;
	FM_INLINE vec3 FM_CALL zzx() const;
	FM_INLINE vec3 FM_CALL zzy() const;
	FM_INLINE vec3 FM_CALL yxx() const;
	FM_INLINE vec3 FM_CALL zxx() const;
	FM_INLINE vec3 FM_CALL xyy() const;
	FM_INLINE vec3 FM_CALL zyy() const;
	FM_INLINE vec3 FM_CALL xzz() const;
	FM_INLINE vec3 FM_CALL yzz() const;
	FM_INLINE vec3 FM_CALL xyx() const;
	FM_INLINE vec3 FM_CALL xzx() const;
	FM_INLINE vec3 FM_CALL yxy() const;
	FM_INLINE vec3 FM_CALL yzy() const;
	FM_INLINE vec3 FM_CALL zxz() const;
	FM_INLINE vec3 FM_CALL zyz() const;
	FM_INLINE vec3 FM_CALL xxx() const;
	FM_INLINE vec3 FM_CALL yyy() const;
	FM_INLINE vec3 FM_CALL zzz() const;

#ifndef FM_EXCLUDE_TEX_COORD_SWIZZLES
	FM_INLINE vec3 FM_CALL uvw() const { return xyz(); }
	FM_INLINE vec3 FM_CALL vwu() const { return yzx(); }
	FM_INLINE vec3 FM_CALL wuv() const { return zxy(); }
	FM_INLINE vec3 FM_CALL wvu() const { return zyx(); }
	FM_INLINE vec3 FM_CALL uwv() const { return xzy(); }
	FM_INLINE vec3 FM_CALL vuw() const { return yxz(); }
	FM_INLINE vec3 FM_CALL uuv() const { return xxy(); }
	FM_INLINE vec3 FM_CALL uuw() const { return xxz(); }
	FM_INLINE vec3 FM_CALL vvu() const { return yyx(); }
	FM_INLINE vec3 FM_CALL vvw() const { return yyz(); }
	FM_INLINE vec3 FM_CALL wwu() const { return zzx(); }
	FM_INLINE vec3 FM_CALL wwv() const { return zzy(); }
	FM_INLINE vec3 FM_CALL vuu() const { return yxx(); }
	FM_INLINE vec3 FM_CALL wuu() const { return zxx(); }
	FM_INLINE vec3 FM_CALL uvv() const { return xyy(); }
	FM_INLINE vec3 FM_CALL wvv() const { return zyy(); }
	FM_INLINE vec3 FM_CALL uww() const { return xzz(); }
	FM_INLINE vec3 FM_CALL vww() const { return yzz(); }
	FM_INLINE vec3 FM_CALL uvu() const { return xyx(); }
	FM_INLINE vec3 FM_CALL uwu() const { return xzx(); }
	FM_INLINE vec3 FM_CALL vuv() const { return yxy(); }
	FM_INLINE vec3 FM_CALL vwv() const { return yzy(); }
	FM_INLINE vec3 FM_CALL wuw() const { return zxz(); }
	FM_INLINE vec3 FM_CALL wvw() const { return zyz(); }
	FM_INLINE vec3 FM_CALL uuu() const { return xxx(); }
	FM_INLINE vec3 FM_CALL vvv() const { return yyy(); }
	FM_INLINE vec3 FM_CALL www() const { return zzz(); }
#endif

#ifndef FM_EXCLUDE_COLOR_SWIZZLES
	FM_INLINE vec3 FM_CALL rgb() const { return xyz(); }
	FM_INLINE vec3 FM_CALL gbr() const { return yzx(); }
	FM_INLINE vec3 FM_CALL brg() const { return zxy(); }
	FM_INLINE vec3 FM_CALL bgr() const { return zyx(); }
	FM_INLINE vec3 FM_CALL rbg() const { return xzy(); }
	FM_INLINE vec3 FM_CALL grb() const { return yxz(); }
	FM_INLINE vec3 FM_CALL rrg() const { return xxy(); }
	FM_INLINE vec3 FM_CALL rrb() const { return xxz(); }
	FM_INLINE vec3 FM_CALL ggr() const { return yyx(); }
	FM_INLINE vec3 FM_CALL ggb() const { return yyz(); }
	FM_INLINE vec3 FM_CALL bbr() const { return zzx(); }
	FM_INLINE vec3 FM_CALL bbg() const { return zzy(); }
	FM_INLINE vec3 FM_CALL grr() const { return yxx(); }
	FM_INLINE vec3 FM_CALL brr() const { return zxx(); }
	FM_INLINE vec3 FM_CALL rgg() const { return xyy(); }
	FM_INLINE vec3 FM_CALL bgg() const { return zyy(); }
	FM_INLINE vec3 FM_CALL rbb() const { return xzz(); }
	FM_INLINE vec3 FM_CALL gbb() const { return yzz(); }
	FM_INLINE vec3 FM_CALL rgr() const { return xyx(); }
	FM_INLINE vec3 FM_CALL rbr() const { return xzx(); }
	FM_INLINE vec3 FM_CALL grg() const { return yxy(); }
	FM_INLINE vec3 FM_CALL gbg() const { return yzy(); }
	FM_INLINE vec3 FM_CALL brb() const { return zxz(); }
	FM_INLINE vec3 FM_CALL bgb() const { return zyz(); }
	FM_INLINE vec3 FM_CALL rrr() const { return xxx(); }
	FM_INLINE vec3 FM_CALL ggg() const { return yyy(); }
	FM_INLINE vec3 FM_CALL bbb() const { return zzz(); }
#endif
};
FM_INLINE vec3 FM_CALL makeVec3FromMemory(float* v);
FM_INLINE vec3 FM_CALL makeVec3(float x, float y, float z);
FM_INLINE vec3 FM_CALL makeVec3(float a);
FM_INLINE vec3 FM_CALL makeVec3(__m128 m);
FM_INLINE vec3 FM_CALL makeZeroVec3();

FM_INLINE void FM_CALL store(float* mem, vec3 v); 

FM_INLINE vec3 FM_CALL operator+(vec3 a, vec3 b); 
FM_INLINE vec3 FM_CALL operator-(vec3 a, vec3 b);
FM_INLINE vec3& FM_CALL operator+=(vec3& a, vec3 b);
FM_INLINE vec3& FM_CALL operator-=(vec3& a, vec3 b);
FM_INLINE vec3 FM_CALL hadamardMul(vec3 a, vec3 b);
FM_INLINE vec3 FM_CALL hadamardDiv(vec3 a, vec3 b);
FM_INLINE vec3 FM_CALL operator*(vec3 v, float  scalar);
FM_INLINE vec3 FM_CALL operator*(float scalar, vec3 v);
FM_INLINE vec3 FM_CALL operator/(vec3 v, float scalar);
FM_INLINE vec3 FM_CALL operator-(vec3 v); 
FM_INLINE vec3 FM_CALL cross(vec3 a, vec3 b); 
FM_INLINE float FM_CALL dot(vec3 a, vec3 b); 
FM_INLINE vec3 FM_CALL min(vec3 a, vec3 b); 
FM_INLINE vec3 FM_CALL max(vec3 a, vec3 b); 
FM_INLINE vec3 FM_CALL normalize(vec3 v);
FM_INLINE vec3 FM_CALL abs(vec3 v);
FM_INLINE float FM_CALL sumOfElements(vec3 v);
FM_INLINE float FM_CALL length(vec3 v);
FM_INLINE float FM_CALL lengthSquared(vec3 v); 
FM_INLINE vec3 FM_CALL clamp(vec3 v, vec3 min, vec3 max); 
FM_INLINE vec3 FM_CALL lerp(vec3 a, vec3 b, float t);

FM_INLINE bool FM_CALL operator==(vec3 a, vec3 b); 
FM_INLINE bool FM_CALL operator!=(vec3 a, vec3 b); 
FM_INLINE vec3 FM_CALL equalsMask(vec3 a, vec3 b);
FM_INLINE vec3 FM_CALL greaterMask(vec3 a, vec3 b);
FM_INLINE vec3 FM_CALL greaterOrEqualMask(vec3 a, vec3 b);
FM_INLINE vec3 FM_CALL lesserMask(vec3 a, vec3 b);
FM_INLINE vec3 FM_CALL lesserOrEqualMask(vec3 a, vec3 b);

struct vec4
{
	__m128 m;

	FM_INLINE void FM_CALL setX(float x);
	FM_INLINE void FM_CALL setY(float y); 
	FM_INLINE void FM_CALL setZ(float z); 
	FM_INLINE void FM_CALL setW(float w); 

	FM_INLINE float FM_CALL x() const;
	FM_INLINE float FM_CALL y() const;
	FM_INLINE float FM_CALL z() const;
	FM_INLINE float FM_CALL w() const;

	FM_INLINE float FM_CALL r() const { return x(); }
	FM_INLINE float FM_CALL g() const { return y(); }
	FM_INLINE float FM_CALL b() const { return z(); }
	FM_INLINE float FM_CALL a() const { return w(); }
};
FM_INLINE vec4 FM_CALL makeVec4FromMemory(const float* v); 
FM_INLINE vec4 FM_CALL makeVec4ForTransformation(float a); 
FM_INLINE vec4 FM_CALL makeVec4ForTransformation(float x, float y, float z);
FM_INLINE vec4 FM_CALL makeVec4ForTransformation(vec3 v);
FM_INLINE vec4 FM_CALL makeVec4(float x, float y, float z, float w);
FM_INLINE vec4 FM_CALL makeVec4(float a);
FM_INLINE vec4 FM_CALL makeVec4(__m128 m);
FM_INLINE vec4 FM_CALL makeZeroVec4();

FM_INLINE void FM_CALL store(float* mem, vec4 v);
FM_INLINE void FM_CALL store16ByteAligned(float* mem, vec4 v);

FM_INLINE vec4 FM_CALL operator+(vec4 a, vec4 b); 
FM_INLINE vec4 FM_CALL operator-(vec4 a, vec4 b);
FM_INLINE vec4& FM_CALL operator+=(vec4& a, vec4 b);
FM_INLINE vec4& FM_CALL operator-=(vec4& a, vec4 b);
FM_INLINE vec4 FM_CALL hadamardMul(vec4 a, vec4 b);
FM_INLINE vec4 FM_CALL hadamardDiv(vec4 a, vec4 b);
FM_INLINE vec4 FM_CALL operator*(vec4 v, float  scalar);
FM_INLINE vec4 FM_CALL operator*(float scalar, vec4 v);
FM_INLINE vec4 FM_CALL operator/(vec4 v, float scalar);
FM_INLINE vec4 FM_CALL operator-(vec4 v); 
FM_INLINE vec4 FM_CALL cross(vec4 a, vec4 b); 
FM_INLINE float FM_CALL dot(vec4 a, vec4 b); 
FM_INLINE vec4 FM_CALL min(vec4 a, vec4 b); 
FM_INLINE vec4 FM_CALL max(vec4 a, vec4 b); 
FM_INLINE vec4 FM_CALL normalize(vec4 v);
FM_INLINE vec4 FM_CALL abs(vec4 v);
FM_INLINE float FM_CALL sumOfElements(vec4 v);
FM_INLINE float FM_CALL length(vec4 v);
FM_INLINE float FM_CALL lengthSquared(vec4 v); 
FM_INLINE vec4 FM_CALL clamp(vec4 v, vec4 min, vec4 max); 
FM_INLINE vec4 FM_CALL lerp(vec4 a, vec4 b, float t);

FM_INLINE bool FM_CALL operator==(vec4 a, vec4 b); 
FM_INLINE bool FM_CALL operator!=(vec4 a, vec4 b); 
FM_INLINE vec4 FM_CALL equalsMask(vec4 a, vec4 b);
FM_INLINE vec4 FM_CALL greaterMask(vec4 a, vec4 b);
FM_INLINE vec4 FM_CALL greaterOrEqualMask(vec4 a, vec4 b);
FM_INLINE vec4 FM_CALL lesserMask(vec4 a, vec4 b);
FM_INLINE vec4 FM_CALL lesserOrEqualMask(vec4 a, vec4 b);


struct mat4
{
	__m128 columns[4];

	FM_INLINE vec4 FM_CALL getColumn(unsigned index);
	FM_INLINE void FM_CALL setColumn(unsigned index, vec4 col);
	FM_INLINE void FM_CALL setColumn(unsigned index, float x, float y, float z, float w);
	FM_INLINE void FM_CALL swapColumns(unsigned col1Index, unsigned col2Index); 

	vec4 FM_CALL getRow(unsigned index);
	void FM_CALL setRow(unsigned index, vec4 row);
	FM_INLINE void FM_CALL setRow(unsigned index, float x, float y, float z, float w);
	FM_INLINE void FM_CALL swapRows(unsigned row1Index, unsigned row2Index); 

	FM_INLINE vec4 FM_CALL getMainDiagonal();
	FM_INLINE void FM_CALL setMainDiagonal(float x, float y, float z, float w); 
	FM_INLINE void FM_CALL setMainDiagonal(vec4 v);
};

FM_INLINE mat4 FM_CALL makeMat4FromColumnMajorMemory(float* mem); 
FM_INLINE mat4 FM_CALL makeZeroMat4(); 
FM_INLINE mat4 FM_CALL makeIdentityMat4(); 
FM_INLINE mat4 FM_CALL makeDiagonalMat4(float diag); 
FM_INLINE mat4 FM_CALL makeDiagonalMat4(float diagX, float diagY, float diagZ, float diagW); 
FM_INLINE mat4 FM_CALL makeDiagonalMat4(vec4 diag); 
FM_INLINE mat4 FM_CALL makeMat4FromColumns(vec4 col1, vec4 col2, vec4 col3, vec4 col4); 
FM_INLINE mat4 FM_CALL makeMat4FromColumns(
	float e11, float e21, float e31, float e41,
    float e12, float e22, float e32, float e42,
    float e13, float e23, float e33, float e43,
    float e14, float e24, float e34, float e44);
FM_INLINE mat4 FM_CALL makeMat4FromRows(vec4 row1, vec4 row2, vec4 row3, vec4 row4); 
FM_INLINE mat4 FM_CALL makeMat4FromRows(
	float e11, float e12, float e13, float e14,
    float e21, float e22, float e23, float e24,
    float e31, float e32, float e33, float e34,
    float e41, float e42, float e43, float e44);

FM_INLINE void FM_CALL store(float* mem, mat4 mat);
FM_INLINE void FM_CALL store16ByteAligned(float* mem, mat4 mat);

FM_INLINE mat4 FM_CALL operator+(mat4 a, mat4 b);
FM_INLINE mat4 FM_CALL operator-(mat4 a, mat4 b);
FM_INLINE mat4 FM_CALL operator*(mat4 a, mat4 b);
FM_INLINE vec4 FM_CALL operator*(mat4 m, vec4 v);
FM_INLINE mat4 FM_CALL operator*(mat4 m, float scalar);
FM_INLINE mat4 FM_CALL operator*(float scalar, mat4 m);
FM_INLINE mat4 FM_CALL operator/(mat4 m, float scalar);
FM_INLINE mat4 FM_CALL transpose(mat4 m);
FM_INLINE mat4 FM_CALL swapColumns(mat4 m, unsigned col1Index, unsigned col2Index);
FM_INLINE mat4 FM_CALL swapRows(mat4 m, unsigned row1Index, unsigned row2Index);

FM_INLINE mat4 FM_CALL makeTranslationMat4(float x, float y, float z); 
FM_INLINE mat4 FM_CALL makeTranslationMat4(vec3 translation);
FM_INLINE mat4 FM_CALL translate(mat4 m, float x, float y, float z); 
FM_INLINE mat4 FM_CALL translate(mat4 m, vec3 translation);

FM_INLINE mat4 FM_CALL makeScaleMat4(float scalar); 
FM_INLINE mat4 FM_CALL makeScaleMat4(float scalarX, float scalarY, float scalarZ); 
FM_INLINE mat4 FM_CALL makeScaleMat4(vec3 scalar);
FM_INLINE mat4 FM_CALL scale(mat4 m, float scalar); 
FM_INLINE mat4 FM_CALL scale(mat4 m, float x, float y, float z); 
FM_INLINE mat4 FM_CALL scale(mat4 m, vec3 scalar);

FM_INLINE mat4 FM_CALL makeRotationMat4Degrees(float degrees, float axisX, float axisY, float axisZ); 
FM_INLINE mat4 FM_CALL makeRotationMat4Degrees(float degrees, vec3 axis);
FM_INLINE mat4 FM_CALL makeRotationAroundXAxisMat4Degrees(float degrees);
FM_INLINE mat4 FM_CALL makeRotationAroundYAxisMat4Degrees(float degrees);
FM_INLINE mat4 FM_CALL makeRotationAroundZAxisMat4Degrees(float degrees);
FM_INLINE mat4 FM_CALL rotateDegrees(mat4 m, float degrees, float axisX, float axisY, float axisZ); 
FM_INLINE mat4 FM_CALL rotateDegrees(mat4 m, float degrees, vec3 axis);
FM_INLINE mat4 FM_CALL rotateAroundXAxisDegrees(mat4 m, float degrees);
FM_INLINE mat4 FM_CALL rotateAroundYAxisDegrees(mat4 m, float degrees);
FM_INLINE mat4 FM_CALL rotateAroundZAxisDegrees(mat4 m, float degrees);
FM_INLINE mat4 FM_CALL makeRotationMat4Radians(float radians, float axisX, float axisY, float axisZ); 
FM_INLINE mat4 FM_CALL makeRotationMat4Radians(float radians, vec3 axis);
FM_INLINE mat4 FM_CALL makeRotationAroundXAxisMat4Radians(float radians);
FM_INLINE mat4 FM_CALL makeRotationAroundYAxisMat4Radians(float radians);
FM_INLINE mat4 FM_CALL makeRotationAroundZAxisMat4Radians(float radians);
FM_INLINE mat4 FM_CALL rotateRadians(mat4 m, float radians, float axisX, float axisY, float axisZ); 
FM_INLINE mat4 FM_CALL rotateRadians(mat4 m, float radians, vec3 axis);
FM_INLINE mat4 FM_CALL rotateAroundXAxisRadians(mat4 m, float radians);
FM_INLINE mat4 FM_CALL rotateAroundYAxisRadians(mat4 m, float radians);
FM_INLINE mat4 FM_CALL rotateAroundZAxisRadians(mat4 m, float radians);

mat4 makeOrthographicMat4(float left, float right, float bottom, float top, float near, float far);
mat4 makePerspectiveMat4(float fov, float aspectRatio, float near, float far);

/* TODO:
shear
reflect
matrix hadamard
lookAt()
frustum()
project()
determinant
inverse
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

namespace fm {

/////////////////////////////////////////
// fast math internal helper functions //
/////////////////////////////////////////
namespace priv {
	FM_INLINE __m128 FM_CALL setX(__m128 m, float x) {
		return _mm_move_ss(m, _mm_set_ss(x));
	}
	FM_INLINE __m128 FM_CALL setY(__m128 m, float y) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(y));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 0));
		return _mm_move_ss(temp, m);
	}
	FM_INLINE __m128 FM_CALL setZ(__m128 m, float z) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(z));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 0, 1, 0));
		return _mm_move_ss(temp, m);
	}
	FM_INLINE __m128 FM_CALL setW(__m128 m, float w) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(w));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(0, 2, 1, 0));
		return _mm_move_ss(temp, m);
	}
	FM_INLINE float FM_CALL getX(__m128 m) {
		return _mm_cvtss_f32(m);
	}
	FM_INLINE float FM_CALL getY(__m128 m) {
		return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 1)));
	}
	FM_INLINE float FM_CALL getZ(__m128 m) {
		return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 2)));
	}
	FM_INLINE float FM_CALL getW(__m128 m) {
		return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 3)));
	}
	FM_INLINE float FM_CALL sumOfElements(__m128 m) {
		return getX(m) + getY(m) + getZ(m) + getW(m);
	}
}

////////////////////////////
// utility functions impl //
////////////////////////////
FM_INLINE float min(float a, float b) {
	return a < b ? a : b; 
}
FM_INLINE float max(float a, float b) {
	return a > b ? a : b;
}
FM_INLINE double min(double a, double b) {
	return a < b ? a : b; 
}
FM_INLINE double max(double a, double b) {
	return a > b ? a : b;
}
FM_INLINE int min(int a, int b) {
	return a < b ? a : b; 
}
FM_INLINE int max(int a, int b) {
	return a > b ? a : b;
}
FM_INLINE unsigned min(unsigned a, unsigned b) {
	return a < b ? a : b; 
}
FM_INLINE unsigned max(unsigned a, unsigned b) {
	return a > b ? a : b;
}
FM_INLINE float abs(float a) {
	return a < 0 ? -a : a;
}
FM_INLINE double abs(double a) {
	return a < 0 ? -a : a;
}
FM_INLINE int abs(int a) {
	return a < 0 ? -a : a;
}
FM_INLINE float radiansToDegrees(float radians) {
	return radians * 180.f / FM_PI32;
}
FM_INLINE double radiansToDegrees(double radians) {
	return radians * 180.f / FM_PI64;
}
FM_INLINE float degreesToRadians(float degrees) {
	return degrees * FM_PI32 / 180.f;
}
FM_INLINE double degreesToRadians(double degrees) {
	return degrees * FM_PI64 / 180.f;
}
// TODO: Do faster implementations of these 

///////////////
// vec2 impl //
///////////////
FM_INLINE vec2 FM_CALL makeVec2FromMemory(const float* v) {
	vec2 res;
	res.m = _mm_set_ps(0.f, 0.f, v[1], v[0]); 
	return res;
} 
FM_INLINE vec2 FM_CALL makeVec2(float x, float y) {
	vec2 res;
	res.m = _mm_set_ps(0.f, 0.f, y, x); 
	return res;
}
FM_INLINE vec2 FM_CALL makeVec2(float a) {
	vec2 res;
	res.m = _mm_set1_ps(a); 
	return res;
}
FM_INLINE vec2 FM_CALL makeVec2 (__m128 m) {
	vec2 res;
	res.m = m;
	return res;
}
FM_INLINE vec2 FM_CALL makeZeroVec2() {
	vec2 res;
	res.m = _mm_setzero_ps(); 
	return res;
}
FM_INLINE float FM_CALL vec2::x() const { 
	return priv::getX(m); 
}
FM_INLINE float FM_CALL vec2::y() const {
	return priv::getY(m); 
}
FM_INLINE vec2 FM_CALL vec2::yx() const {
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE vec2 FM_CALL vec2::xx() const {
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 0))); 
}
FM_INLINE vec2 FM_CALL vec2::yy() const {
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE void FM_CALL vec2::setX(float x) {
	m = priv::setX(m, x); 
}
FM_INLINE void FM_CALL vec2::setY(float y) { 
	m = priv::setY(m, y);
}  
FM_INLINE void FM_CALL store(float* mem, vec2 v) {
	mem[0] = v.x();
	mem[1] = v.y(); 
} 
FM_INLINE vec2 FM_CALL operator+(vec2 a, vec2 b) {
	a.m = _mm_add_ps(a.m, b.m);
	return a; 
}
FM_INLINE vec2 FM_CALL operator-(vec2 a, vec2 b) {
	a.m = _mm_sub_ps(a.m, b.m);
	return a; 
}
FM_INLINE vec2& FM_CALL operator+=(vec2& a, vec2 b) {
	a.m = _mm_add_ps(a.m, b.m);
	return a; 
}
FM_INLINE vec2& FM_CALL operator-=(vec2& a, vec2 b) {
	a.m = _mm_sub_ps(a.m, b.m);
	return a; 
}
FM_INLINE vec2 FM_CALL hadamardMul(vec2 a, vec2 b) {
	a.m = _mm_mul_ps(a.m, b.m);
	return a;
}
FM_INLINE vec2 FM_CALL hadamardDiv(vec2 a, vec2 b) {
	a.m = _mm_div_ps(a.m, b.m);
	return a; 
}
FM_INLINE vec2 FM_CALL operator*(vec2 v, float scalar) {
	v.m = _mm_mul_ps(v.m, _mm_set1_ps(scalar)); 
	return v; 
}
FM_INLINE vec2 FM_CALL operator*(float scalar, vec2 v) { 
	v.m = _mm_mul_ps(v.m, _mm_set1_ps(scalar));
	return v; 
}
FM_INLINE vec2 FM_CALL operator/(vec2 v, float scalar) {
	v.m = _mm_div_ps(v.m, _mm_set1_ps(scalar));
	return v; 
}
FM_INLINE vec2 FM_CALL operator-(vec2 v) {
	// TODO: Maybe do that with static sign mask
	v.m = _mm_sub_ps(_mm_setzero_ps(), v.m);
	return v;
}
FM_INLINE float FM_CALL dot(vec2 a, vec2 b) {
	return sumOfElements(hadamardMul(a, b));
}
FM_INLINE vec2 FM_CALL min(vec2 a, vec2 b) {
	a.m = _mm_min_ps(a.m, b.m);
	return a;
}
FM_INLINE vec2 FM_CALL max(vec2 a, vec2 b) {
	a.m = _mm_max_ps(a.m, b.m);
	return a;
}
FM_INLINE vec2 FM_CALL abs(vec2 v) {
	__m128 signMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000)); 
	v.m = _mm_andnot_ps(signMask, v.m);
	return v;
}
FM_INLINE float FM_CALL sumOfElements(vec2 v) {
	return v.x() + v.y();
}
FM_INLINE float FM_CALL length(vec2 v) {
	return sqrt(dot(v, v));
}
FM_INLINE float FM_CALL lengthSquared(vec2 v) {
	return dot(v, v);
}
FM_INLINE vec2 FM_CALL normalize(vec2 v) {
	return v / length(v);
}
FM_INLINE vec2 FM_CALL clamp(vec2 v, vec2 minV, vec2 maxV) {
	return min(max(v, minV), maxV);
}
FM_INLINE vec2 FM_CALL lerp(vec2 a, vec2 b, float t) {
	return a + (b-a)*t;
}
FM_INLINE bool FM_CALL operator==(vec2 a, vec2 b) {
	vec2 eqMask = equalsMask(a, b);
	return eqMask.x() && eqMask.y();
} 
FM_INLINE bool FM_CALL operator!=(vec2 a, vec2 b) {
	vec2 eqMask = equalsMask(a, b);
	return !(eqMask.x() && eqMask.y());
}
FM_INLINE vec2 FM_CALL equalsMask(vec2 a, vec2 b) {
	a.m = _mm_cmpeq_ps(a.m, b.m);
	return a;
}
FM_INLINE vec2 FM_CALL greaterMask(vec2 a, vec2 b) {
	a.m = _mm_cmpgt_ps(a.m, b.m);
	return a;
}
FM_INLINE vec2 FM_CALL greaterOrEqualMask(vec2 a, vec2 b) {
	a.m = _mm_cmpge_ps(a.m, b.m);
	return a;
}
FM_INLINE vec2 FM_CALL lesserMask(vec2 a, vec2 b) {
	a.m = _mm_cmplt_ps(a.m, b.m);
	return a;
}
FM_INLINE vec2 FM_CALL lesserOrEqualMask(vec2 a, vec2 b) {
	a.m = _mm_cmple_ps(a.m, b.m);
	return a;
}

////////////////
// vec2d impl //
////////////////
FM_INLINE vec2d FM_CALL makeVec2dFromMemory(const double* v) {
	vec2d res;
	res.m = _mm_set_pd(v[1], v[0]); 
	return res;
}
FM_INLINE vec2d FM_CALL makeVec2d(double x, double y) {
	vec2d res;
	res.m = _mm_set_pd(y, x); 
	return res;
}
FM_INLINE vec2d FM_CALL makeVec2d(double a) {
	vec2d res;
	res.m = _mm_set1_pd(a);
	return res;
}
FM_INLINE vec2d FM_CALL makeVec2d(__m128d m) {
	vec2d res;
	res.m = m;
	return res;
}
FM_INLINE vec2d FM_CALL makeZeroVec2d() {
	vec2d res;
	res.m = _mm_setzero_pd(); 
	return res;
}
FM_INLINE double FM_CALL vec2d::x() const {
	return _mm_cvtsd_f64(m);
}
FM_INLINE double FM_CALL vec2d::y() const { 
	return _mm_cvtsd_f64(_mm_shuffle_pd(m, m, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE vec2d FM_CALL vec2d::yx() const {
	return makeVec2d(_mm_shuffle_pd(m, m, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE vec2d FM_CALL vec2d::xx() const {
	return makeVec2d(_mm_unpacklo_pd(m, m));
}
FM_INLINE vec2d FM_CALL vec2d::yy() const {
	return makeVec2d(_mm_unpackhi_pd(m, m));
}
FM_INLINE void FM_CALL store(double* mem, vec2d v) { 
	_mm_storeu_pd(mem, v.m); 
} 
FM_INLINE void FM_CALL store16ByteAligned(double* mem, vec2d v) {
	_mm_store_pd(mem, v.m); 
}
FM_INLINE void FM_CALL vec2d::setX(double x) {
	m = _mm_move_sd(m, _mm_set_sd(x)); 
}
FM_INLINE void FM_CALL vec2d::setY(double y) {
	m = _mm_unpacklo_pd(m, _mm_set_sd(y)); 
}
FM_INLINE vec2d FM_CALL operator+(vec2d a, vec2d b) {
	a.m = _mm_add_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d FM_CALL operator-(vec2d a, vec2d b) {
	a.m = _mm_sub_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d& FM_CALL operator+=(vec2d& a, vec2d b) {
	a.m = _mm_add_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d& FM_CALL operator-=(vec2d& a, vec2d b) {
	a.m = _mm_sub_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d FM_CALL hadamardMul(vec2d a, vec2d b) {
	a.m = _mm_mul_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d FM_CALL hadamardDiv(vec2d a, vec2d b) {
	a.m = _mm_div_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d FM_CALL operator*(vec2d v, double scalar) {
	v.m = _mm_mul_pd(v.m, _mm_set1_pd(scalar));
	return v; 
}
FM_INLINE vec2d FM_CALL operator*(double scalar, vec2d v) {
	v.m = _mm_mul_pd(v.m, _mm_set1_pd(scalar));
	return v; 
} 
FM_INLINE vec2d FM_CALL operator/(vec2d v, double scalar) {
	v.m = _mm_div_pd(v.m, _mm_set1_pd(scalar));
	return v; 
}
FM_INLINE vec2d FM_CALL operator-(vec2d v) {
	v.m = _mm_sub_pd(_mm_setzero_pd(), v.m);
	return v;
}
FM_INLINE double FM_CALL dot(vec2d a, vec2d b) {
	return sumOfElements(hadamardMul(a, b));
}
FM_INLINE vec2d FM_CALL min(vec2d a, vec2d b) {
	a.m = _mm_min_pd(a.m, b.m);
	return a;
}
FM_INLINE vec2d FM_CALL max(vec2d a, vec2d b) {
	a.m = _mm_max_pd(a.m, b.m);
	return a;
}
FM_INLINE vec2d FM_CALL abs(vec2d v) {
	__m128d signBits = _mm_castsi128_pd(_mm_set1_epi32(0x80000000));
	v.m = _mm_andnot_pd(signBits, v.m);
	return v;
}
FM_INLINE double FM_CALL sumOfElements(vec2d v) {
	return v.x() + v.y();
}
FM_INLINE double FM_CALL length(vec2d v) {
	return sqrt(dot(v, v));
}
FM_INLINE double FM_CALL lengthSquared(vec2d v) {
	return dot(v, v);
}
FM_INLINE vec2d FM_CALL normalize(vec2d v) {
	return v / length(v);
}
FM_INLINE vec2d FM_CALL clamp(vec2d v, vec2d minV, vec2d maxV) {
	return min(max(v, minV), maxV);
} 
FM_INLINE vec2d FM_CALL lerp(vec2d a, vec2d b, double t) {
	return a + (b-a)*t;
}
FM_INLINE bool FM_CALL operator==(vec2d a, vec2d b) {
	vec2d eqMask = equalsMask(a, b);
	return eqMask.x() && eqMask.y();
} 
FM_INLINE bool FM_CALL operator!=(vec2d a, vec2d b) {
	vec2d eqMask = equalsMask(a, b);
	return !(eqMask.x() && eqMask.y());
}
FM_INLINE vec2d FM_CALL equalsMask(vec2d a, vec2d b) {
	a.m = _mm_cmpeq_pd(a.m, b.m);
	return a;
}
FM_INLINE vec2d FM_CALL greaterMask(vec2d a, vec2d b) {
	a.m = _mm_cmpgt_pd(a.m, b.m);
	return a;
}
FM_INLINE vec2d FM_CALL greaterOrEqualMask(vec2d a, vec2d b) {
	a.m = _mm_cmpge_pd(a.m, b.m);
	return a;
}
FM_INLINE vec2d FM_CALL lesserMask(vec2d a, vec2d b) {
	a.m = _mm_cmplt_pd(a.m, b.m);
	return a;
}
FM_INLINE vec2d FM_CALL lesserOrEqualMask(vec2d a, vec2d b) {
	a.m = _mm_cmple_pd(a.m, b.m);
	return a;
}

////////////////
// vec2i impl //
////////////////
FM_INLINE vec2i FM_CALL makeVec2iFromMemory(const int* v) {
	vec2i res;
	res.m = _mm_set_epi32(0, 0, v[1], v[0]); 
	return res;
}
FM_INLINE vec2i FM_CALL makeVec2i(int x, int y) {
	vec2i res;
	res.m = _mm_set_epi32(0, 0, y, x); 
	return res;
}
FM_INLINE vec2i FM_CALL makeVec2i(int a) { 
	vec2i res;
	res.m = _mm_set1_epi32(a); 
	return res;
}
FM_INLINE vec2i FM_CALL makeVec2i(__m128i m) {
	vec2i res;
	res.m = m;
	return res;
}
FM_INLINE vec2i FM_CALL makeZeroVec2i() {
	vec2i res;
	res.m = _mm_setzero_si128();
	return res;
}
FM_INLINE int FM_CALL vec2i::x() const { 
	return _mm_cvtsi128_si32(m); 
} 
FM_INLINE int FM_CALL vec2i::y() const {
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(m, _MM_SHUFFLE(1, 1, 1, 1))); 
} 
FM_INLINE vec2i FM_CALL vec2i::yx() const {
	return makeVec2i(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 0, 1)));
}
FM_INLINE vec2i FM_CALL vec2i::xx() const {
	return makeVec2i(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 0, 0)));
}
FM_INLINE vec2i FM_CALL vec2i::yy() const {
	return makeVec2i(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 1, 1)));
}
FM_INLINE void FM_CALL store(int* mem, vec2i v) {
	mem[0] = v.x();
	mem[1] = v.y();
} 
FM_INLINE vec2i FM_CALL operator+(vec2i a, vec2i b) {
	a.m = _mm_add_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2i FM_CALL operator-(vec2i a, vec2i b) {
	a.m = _mm_sub_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2i& FM_CALL operator+=(vec2i& a, vec2i b) {
	a.m = _mm_add_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2i& FM_CALL operator-=(vec2i& a, vec2i b) {
	a.m = _mm_sub_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2i FM_CALL operator-(vec2i v) {
	v.m = _mm_sub_epi32(_mm_setzero_si128(), v.m);
	return v;
}
FM_INLINE int FM_CALL sumOfElements(vec2i v) {
	return v.x() + v.y();
}
FM_INLINE int FM_CALL length(vec2i v) {
	int x = v.x();
	int y = v.y();
	return (int)sqrt(x*x + y*y);
}
FM_INLINE int FM_CALL lengthSquared(vec2i v) {
	int x = v.x();
	int y = v.y();
	return x*x + y*y;
}
FM_INLINE bool FM_CALL operator==(vec2i a, vec2i b) {
	vec2i eqMask = equalsMask(a, b);
	return eqMask.x() && eqMask.y();
} 
FM_INLINE bool FM_CALL operator!=(vec2i a, vec2i b) {
	vec2i eqMask = equalsMask(a, b);
	return !(eqMask.x() && eqMask.y());
} 
FM_INLINE vec2i FM_CALL equalsMask(vec2i a, vec2i b) {
	a.m = _mm_cmpeq_epi32(a.m, b.m);
	return a;
}
FM_INLINE vec2i FM_CALL greaterMask(vec2i a, vec2i b) {
	a.m = _mm_cmpgt_epi32(a.m, b.m);
	return a;
}
FM_INLINE vec2i FM_CALL greaterOrEqualMask(vec2i a, vec2i b) {
	__m128i gt = _mm_cmpgt_epi32(a.m, b.m);
	__m128i eq = _mm_cmpeq_epi32(a.m, b.m);
	a.m = _mm_or_si128(gt, eq);
	return a;
}
FM_INLINE vec2i FM_CALL lesserMask(vec2i a, vec2i b) {
	a.m = _mm_cmplt_epi32(a.m, b.m);
	return a;
}
FM_INLINE vec2i FM_CALL lesserOrEqualMask(vec2i a, vec2i b) {
	__m128i lt = _mm_cmplt_epi32(a.m, b.m);
	__m128i eq = _mm_cmpeq_epi32(a.m, b.m);
	a.m = _mm_or_si128(lt, eq);
	return a;
}
#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INLINE void FM_CALL vec2i::setX(int x) {
	m = _mm_insert_epi32(m, x, 0);
}
FM_INLINE void FM_CALL vec2i::setY(int y) {
	m = _mm_insert_epi32(m, y, 1);
}
FM_INLINE vec2i FM_CALL operator*(vec2i v, int scalar) {
	v.m = _mm_mullo_epi32(v.m, _mm_set1_epi32(scalar));
	return v; 
}
FM_INLINE vec2i FM_CALL operator*(int scalar, vec2i v) {
	v.m =_mm_mullo_epi32(v.m, _mm_set1_epi32(scalar)); 
	return v; 
}
FM_INLINE vec2i FM_CALL hadamardMul(vec2i a, vec2i b) {
	a.m = _mm_mullo_epi32(a.m, b.m); 
	return a; 
}
FM_INLINE vec2i FM_CALL min(vec2i a, vec2i b) {
	a.m = _mm_min_epi32(a.m, b.m);
	return a;
}
FM_INLINE vec2i FM_CALL max(vec2i a, vec2i b) {
	a.m = _mm_max_epi32(a.m, b.m);
	return a;
}
FM_INLINE vec2i FM_CALL abs(vec2i v) {
	v.m = _mm_abs_epi32(v.m);
	return v;
}
FM_INLINE vec2i FM_CALL clamp(vec2i v, vec2i minV, vec2i maxV) {
	return min(max(v, minV), maxV);
} 
#else // SSE 2 implementations 
FM_INLINE void FM_CALL vec2i::setX(int x) {
	int arr[4];
	_mm_store_si128((__m128i*)arr, m);
	arr[0] = x;
	m = _mm_load_si128((__m128i*)arr);
}
FM_INLINE void FM_CALL vec2i::setY(int y) {
	int arr[4];
	_mm_store_si128((__m128i*)arr, m);
	arr[1] = y;
	m = _mm_load_si128((__m128i*)arr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_INLINE vec2i FM_CALL hadamardMul(vec2i a, vec2i b) {
	int aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = aArr[0] * bArr[0]; 
	aArr[1] = aArr[1] * bArr[1]; 
	return vec2i(aArr);
}
FM_INLINE vec2i FM_CALL operator*(vec2i v, int scalar) {
	int vArr[4];
	_mm_store_si128((__m128i*)vArr, v.m);
	vArr[0] *= scalar;
	vArr[1] *= scalar;
	return vec2i(vArr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_INLINE vec2i FM_CALL operator*(int scalar, vec2i v) {
	return v * scalar; 
}
FM_INLINE vec2i FM_CALL min(vec2i a, vec2i b) {
	int aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = min(aArr[0], bArr[0]);
	aArr[1] = min(aArr[1], bArr[1]);
	return vec2i(aArr);
}
FM_INLINE vec2i FM_CALL max(vec2i a, vec2i b) {
	int aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = max(aArr[0], bArr[0]);
	aArr[1] = max(aArr[1], bArr[1]);
	return vec2i(aArr);
	// TODO: This code is repeated. Make helper function or write it somehow using SSE2!
}
FM_INLINE vec2i FM_CALL abs(vec2i v) {
	int vArr[4];
	_mm_store_si128((__m128i*)vArr, v.m);
	vArr[0] = abs(vArr[0]);
	vArr[1] = abs(vArr[1]);
	return vec2i(vArr);
}
#endif

////////////////
// vec2u impl //
////////////////
FM_INLINE vec2u FM_CALL makeVec2uFromMemory(const unsigned* v) {
	vec2u res;
	res.m = _mm_set_epi32(0, 0, v[1], v[0]); 
	return res;
}
FM_INLINE vec2u FM_CALL makeVec2u(unsigned x, unsigned y) {
	vec2u res;
	res.m = _mm_set_epi32(0, 0, y, x); 
	return res;
}
FM_INLINE vec2u FM_CALL makeVec2u(unsigned a) {
	vec2u res;
	res.m = _mm_set1_epi32(a); 
	return res;
} 
FM_INLINE vec2u FM_CALL makeVec2u(__m128i m) {
	vec2u res;
	res.m = m;
	return res;
} 
FM_INLINE vec2u FM_CALL makeZeroVec2u() {
	vec2u res;
	res.m = _mm_setzero_si128(); 
	return res;
}
FM_INLINE unsigned FM_CALL vec2u::x() const {
	return (unsigned)_mm_cvtsi128_si32(m); 
} 
FM_INLINE unsigned FM_CALL vec2u::y() const { 
	return (unsigned)_mm_cvtsi128_si32(_mm_shuffle_epi32(m, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE vec2u FM_CALL vec2u::yx() const { 
	return makeVec2u(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 0, 1))); 
}
FM_INLINE vec2u FM_CALL vec2u::xx() const { 
	return makeVec2u(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 0, 0)));
}
FM_INLINE vec2u FM_CALL vec2u::yy() const { 
	return makeVec2u(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 1, 1)));
}
FM_INLINE void FM_CALL store(unsigned* mem, vec2u v) {
	mem[0] = v.x();
	mem[1] = v.y();
} 
FM_INLINE vec2u FM_CALL operator+(vec2u a, vec2u b) {
	a.m = _mm_add_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2u FM_CALL operator-(vec2u a, vec2u b) {
	a.m = _mm_sub_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2u& FM_CALL operator+=(vec2u& a, vec2u b) {
	a.m = _mm_add_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2u& FM_CALL operator-=(vec2u& a, vec2u b) {
	a.m = _mm_sub_epi32(a.m, b.m);
	return a; 
}
FM_INLINE unsigned FM_CALL sumOfElements(vec2u v) {
	return v.x() + v.y();
}
FM_INLINE unsigned FM_CALL length(vec2u v) {
	unsigned x = v.x();
	unsigned y = v.y();
	return (unsigned)sqrt(x*x + y*y);
}
FM_INLINE unsigned FM_CALL lengthSquared(vec2u v) {
	unsigned x = v.x();
	unsigned y = v.y();
	return x*x + y*y;	
}
FM_INLINE vec2u FM_CALL clamp(vec2u v, vec2u minV, vec2u maxV) {
	return min(max(v, minV), maxV);
} 
FM_INLINE bool FM_CALL operator==(vec2u a, vec2u b) {
	vec2u eqMask = equalsMask(a, b);
	return eqMask.x() && eqMask.y();
} 
FM_INLINE bool FM_CALL operator!=(vec2u a, vec2u b) {
	vec2u eqMask = equalsMask(a, b);
	return !(eqMask.x() && eqMask.y());
} 
FM_INLINE vec2u FM_CALL equalsMask(vec2u a, vec2u b) {
	a.m = _mm_cmpeq_epi32(a.m, b.m);
	return a;
}
FM_INLINE vec2u FM_CALL greaterMask(vec2u a, vec2u b) {
	a.m = _mm_cmpgt_epi32(a.m, b.m);
	return a;
}
FM_INLINE vec2u FM_CALL greaterOrEqualMask(vec2u a, vec2u b) {
	__m128i gt = _mm_cmpgt_epi32(a.m, b.m);
	__m128i eq = _mm_cmpeq_epi32(a.m, b.m);
	a.m = _mm_or_si128(gt, eq);
	return a;
}
FM_INLINE vec2u FM_CALL lesserMask(vec2u a, vec2u b) {
	a.m = _mm_cmplt_epi32(a.m, b.m);
	return a;
}
FM_INLINE vec2u FM_CALL lesserOrEqualMask(vec2u a, vec2u b) {
	__m128i lt = _mm_cmplt_epi32(a.m, b.m);
	__m128i eq = _mm_cmpeq_epi32(a.m, b.m);
	a.m = _mm_or_si128(lt, eq);
	return a;
}
#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INLINE void FM_CALL vec2u::setX(unsigned x) {
	m = _mm_insert_epi32(m, (int)x, 0);
}
FM_INLINE void FM_CALL vec2u::setY(unsigned y) {
	m = _mm_insert_epi32(m, (int)y, 1);
}
FM_INLINE vec2u FM_CALL operator*(vec2u v, unsigned scalar) {
	v.m = _mm_mullo_epi32(v.m, _mm_set1_epi32(scalar)); 
	return v; 
}
FM_INLINE vec2u FM_CALL operator*(unsigned scalar, vec2u v) {
	v.m =_mm_mullo_epi32(v.m, _mm_set1_epi32(scalar));
	return v; 
}
FM_INLINE vec2u FM_CALL hadamardMul(vec2u a, vec2u b) {
	a.m = _mm_mullo_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2u FM_CALL min(vec2u a, vec2u b) {
	a.m = _mm_min_epu32(a.m, b.m);
	return a;
}
FM_INLINE vec2u FM_CALL max(vec2u a, vec2u b) {
	a.m = _mm_max_epu32(a.m, b.m);
	return a;
}
#else // SSE 2 implementations
FM_INLINE void FM_CALL vec2u::setX(unsigned x) {
	unsigned arr[4];
	_mm_store_si128((__m128i*)arr, m);
	arr[0] = x;
	m = _mm_load_si128((__m128i*)arr);
}
FM_INLINE void FM_CALL vec2u::setY(unsigned y) {
	unsigned arr[4];
	_mm_store_si128((__m128i*)arr, m);
	arr[1] = y;
	m = _mm_load_si128((__m128i*)arr);
	// TODO: This code is repeated. Make utility function!
}
FM_INLINE vec2u FM_CALL hadamardMul(vec2u a, vec2u b) {
	unsigned aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = aArr[0] * bArr[0]; 
	aArr[1] = aArr[1] * bArr[1]; 
	return vec2u(aArr);
}
FM_INLINE vec2u FM_CALL operator*(vec2u v, unsigned scalar) {
	unsigned vArr[4];
	_mm_store_si128((__m128i*)vArr, v.m);
	vArr[0] *= scalar;
	vArr[1] *= scalar;
	return vec2u(vArr);
}
FM_INLINE vec2u FM_CALL operator*(unsigned scalar, vec2u v) {
	return v * scalar;
}
FM_INLINE vec2u FM_CALL min(vec2u a, vec2u b) {
	unsigned aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = min(aArr[0], bArr[0]);
	aArr[1] = min(aArr[1], bArr[1]);
	return vec2u(aArr);
}
FM_INLINE vec2u FM_CALL max(vec2u a, vec2u b) {
	unsigned aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = max(aArr[0], bArr[0]);
	aArr[1] = max(aArr[1], bArr[1]);
	return vec2u(aArr);
}
#endif

///////////////
// vec3 impl //
///////////////
FM_INLINE vec3 FM_CALL makeVec3FromMemory(float* v) {
	vec3 res;
	res.m = _mm_set_ps(0, v[2], v[1], v[0]);
	return res;
}
FM_INLINE vec3 FM_CALL makeVec3(float x, float y, float z) {
	vec3 res;
	res.m = _mm_set_ps(0, z, y, x); 
	return res;
}
FM_INLINE vec3 FM_CALL makeVec3(float a) {
	vec3 res;
	res.m = _mm_set1_ps(a);
	return res;
}
FM_INLINE vec3 FM_CALL makeVec3(__m128 m) {
	vec3 res;
	res.m = m;
	return res;
}
FM_INLINE vec3 FM_CALL makeZeroVec3() {
	vec3 res;
	res.m = _mm_setzero_ps();
	return res;
}
FM_INLINE void FM_CALL vec3::setX(float x) {
	m = priv::setX(m, x); 
}
FM_INLINE void FM_CALL vec3::setY(float y) {
	m = priv::setY(m, y);
}
FM_INLINE void FM_CALL vec3::setZ(float z) {
	m = priv::setZ(m, z);
}
FM_INLINE void FM_CALL store(float* mem, vec3 v) {
	mem[0] = v.x();
	mem[1] = v.y();
	mem[2] = v.z();
}
FM_INLINE float FM_CALL vec3::x() const {
	return priv::getX(m); 
}
FM_INLINE float FM_CALL vec3::y() const {
	return priv::getY(m); 
}
FM_INLINE float FM_CALL vec3::z() const {
	return priv::getZ(m); 
}
#ifndef FM_EXCLUDE_SWIZZLES
FM_INLINE vec2 FM_CALL vec3::xy() const {
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 0)));
}
FM_INLINE vec2 FM_CALL vec3::yx() const {
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 1)));
}
FM_INLINE vec2 FM_CALL vec3::yz() const {
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 1)));
}
FM_INLINE vec2 FM_CALL vec3::zy() const {
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 2)));
}
FM_INLINE vec2 FM_CALL vec3::xz() const {
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 0)));
}
FM_INLINE vec2 FM_CALL vec3::zx() const {
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 2)));
}
FM_INLINE vec2 FM_CALL vec3::xx() const {
	// TODO: Try to optimize it
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 0)));
}
FM_INLINE vec2 FM_CALL vec3::yy() const {
	// TODO: Try to optimize it
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 1)));
}
FM_INLINE vec2 FM_CALL vec3::zz() const {
	// TODO: Try to optimize it
	return makeVec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 2)));
}
FM_INLINE vec3 FM_CALL vec3::xyz() const {
	return *this;
}
FM_INLINE vec3 FM_CALL vec3::yzx() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 1)));
}
FM_INLINE vec3 FM_CALL vec3::zxy() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 0, 2)));
}
FM_INLINE vec3 FM_CALL vec3::zyx() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 2)));
}
FM_INLINE vec3 FM_CALL vec3::xzy() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 2, 0)));
}
FM_INLINE vec3 FM_CALL vec3::yxz() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 0, 1)));
}
FM_INLINE vec3 FM_CALL vec3::xxy() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 0, 0)));
}
FM_INLINE vec3 FM_CALL vec3::xxz() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 0, 0)));
}
FM_INLINE vec3 FM_CALL vec3::yyx() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 1)));
}
FM_INLINE vec3 FM_CALL vec3::yyz() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 1, 1)));
}
FM_INLINE vec3 FM_CALL vec3::zzx() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 2)));
}
FM_INLINE vec3 FM_CALL vec3::zzy() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 2, 2)));
}
FM_INLINE vec3 FM_CALL vec3::yxx() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 1)));
}
FM_INLINE vec3 FM_CALL vec3::zxx() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 2)));
}
FM_INLINE vec3 FM_CALL vec3::xyy() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 1, 0)));
}
FM_INLINE vec3 FM_CALL vec3::zyy() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 1, 2)));
}
FM_INLINE vec3 FM_CALL vec3::xzz() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 2, 0)));
}
FM_INLINE vec3 FM_CALL vec3::yzz() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 2, 1)));
}
FM_INLINE vec3 FM_CALL vec3::xyx() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 0)));
}
FM_INLINE vec3 FM_CALL vec3::xzx() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 0)));
}
FM_INLINE vec3 FM_CALL vec3::yxy() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 0, 1)));
}
FM_INLINE vec3 FM_CALL vec3::yzy() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 2, 1)));
}
FM_INLINE vec3 FM_CALL vec3::zxz() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 0, 2)));
}
FM_INLINE vec3 FM_CALL vec3::zyz() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 1, 2)));
}
FM_INLINE vec3 FM_CALL vec3::xxx() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 0)));
}
FM_INLINE vec3 FM_CALL vec3::yyy() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 1, 1)));
}
FM_INLINE vec3 FM_CALL vec3::zzz() const {
	return makeVec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 2, 2)));
}
#endif
FM_INLINE vec3 FM_CALL operator+(vec3 a, vec3 b) {
	a.m = _mm_add_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3 FM_CALL operator-(vec3 a, vec3 b) {
	a.m = _mm_sub_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3& FM_CALL operator+=(vec3& a, vec3 b) {
	a.m = _mm_add_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3& FM_CALL operator-=(vec3& a, vec3 b) {
	a.m = _mm_sub_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3 FM_CALL hadamardMul(vec3 a, vec3 b) {
	a.m = _mm_mul_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3 FM_CALL hadamardDiv(vec3 a, vec3 b) {
	a.m = _mm_div_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3 FM_CALL operator*(vec3 v, float scalar) {
	v.m = _mm_mul_ps(v.m, _mm_set1_ps(scalar));
	return v;
}
FM_INLINE vec3 FM_CALL operator*(float scalar, vec3 v) {
	return v * scalar;
}
FM_INLINE vec3 FM_CALL operator/(vec3 v, float scalar) {
	v.m = _mm_div_ps(v.m, _mm_set1_ps(scalar));
	return v;
}
FM_INLINE vec3 FM_CALL operator-(vec3 v) {
	v.m = _mm_sub_ps(_mm_setzero_ps(), v.m);
	return v;
}
FM_INLINE vec3 FM_CALL cross(vec3 a, vec3 b) {
	return vec3(hadamardMul(a.zxy(), b) - hadamardMul(a, b.zxy())).zxy(); 
}
FM_INLINE float FM_CALL dot(vec3 a, vec3 b) {
	return sumOfElements(hadamardMul(a, b));
}
FM_INLINE vec3 FM_CALL min(vec3 a, vec3 b) {
	a.m = _mm_min_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3 FM_CALL max(vec3 a, vec3 b) {
	a.m = _mm_max_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3 FM_CALL normalize(vec3 v) {
	return v / length(v);
}
FM_INLINE vec3 FM_CALL abs(vec3 v) {
	__m128 signMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	v.m = _mm_andnot_ps(signMask, v.m);
	return v;
}
FM_INLINE float FM_CALL sumOfElements(vec3 v) {
	return v.x() + v.y() + v.z();
}
FM_INLINE float FM_CALL length(vec3 v) {
	return sqrt(dot(v, v));
}
FM_INLINE float FM_CALL lengthSquared(vec3 v) {
	return dot(v, v);
}
FM_INLINE vec3 FM_CALL clamp(vec3 v, vec3 minV, vec3 maxV) {
	return min(max(v, minV), maxV);
}
FM_INLINE vec3 FM_CALL lerp(vec3 a, vec3 b, float t) {
	return a + (b-a)*t;
} 
FM_INLINE bool FM_CALL operator==(vec3 a, vec3 b) {
	vec3 eqMask = equalsMask(a, b);
	return eqMask.x() && eqMask.y() && eqMask.z();
} 
FM_INLINE bool FM_CALL operator!=(vec3 a, vec3 b) {
	vec3 eqMask = equalsMask(a, b);
	return !(eqMask.x() && eqMask.y() && eqMask.z());
}
FM_INLINE vec3 FM_CALL equalsMask(vec3 a, vec3 b) {
	a.m = _mm_cmpeq_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3 FM_CALL greaterMask(vec3 a, vec3 b) {
	a.m = _mm_cmpgt_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3 FM_CALL greaterOrEqualMask(vec3 a, vec3 b) {
	a.m = _mm_cmpge_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3 FM_CALL lesserMask(vec3 a, vec3 b) {
	a.m = _mm_cmplt_ps(a.m, b.m);
	return a;
}
FM_INLINE vec3 FM_CALL lesserOrEqualMask(vec3 a, vec3 b) {
	a.m = _mm_cmple_ps(a.m, b.m);
	return a;
}

///////////////
// vec4 impl //
///////////////
FM_INLINE vec4 FM_CALL makeVec4FromMemory(const float* v) {
	vec4 res;
	res.m = _mm_set_ps(v[3], v[2], v[1], v[0]);	
	return res;
} 
FM_INLINE vec4 FM_CALL makeVec4ForTransformation(float a) {
	vec4 res;
	res.m = _mm_set_ps(1.f, a, a, a);
	return res;
}
FM_INLINE vec4 FM_CALL makeVec4ForTransformation(float x, float y, float z) {
	vec4 res;
	res.m = _mm_set_ps(1.f, z, y, x);
	return res;
}
FM_INLINE vec4 FM_CALL makeVec4ForTransformation(vec3 v) {
	vec4 res;
	v.m = _mm_shuffle_ps(v.m, v.m, _MM_SHUFFLE(2, 1, 0, 0));
	res.m = _mm_move_ss(v.m, _mm_set_ss(1.f));
	res.m = _mm_shuffle_ps(res.m, res.m, _MM_SHUFFLE(0, 3, 2, 1));
	return res;
}
FM_INLINE vec4 FM_CALL makeVec4(float x, float y, float z, float w) {
	vec4 res;
	res.m = _mm_set_ps(w, z, y, x);
	return res;
}
FM_INLINE vec4 FM_CALL makeVec4(float a) {
	vec4 res;
	res.m = _mm_set1_ps(a);
	return res;
}
FM_INLINE vec4 FM_CALL makeVec4(__m128 m) {
	vec4 res;
	res.m = m;
	return res;
} 
FM_INLINE vec4 FM_CALL makeZeroVec4() {
	vec4 res;
	res.m = _mm_setzero_ps();
	return res;
}
FM_INLINE void FM_CALL vec4::setX(float x) {
	m = priv::setX(m, x); 
}
FM_INLINE void FM_CALL vec4::setY(float y) {
	m = priv::setY(m, y);
} 
FM_INLINE void FM_CALL vec4::setZ(float z) {
	m = priv::setZ(m, z);
} 
FM_INLINE void FM_CALL vec4::setW(float w) {
	m = priv::setW(m, w);
} 
FM_INLINE float FM_CALL vec4::x() const {
	return _mm_cvtss_f32(m);
}
FM_INLINE float FM_CALL vec4::y() const {
	return priv::getY(m); 
}
FM_INLINE float FM_CALL vec4::z() const {
	return priv::getZ(m); 
}
FM_INLINE float FM_CALL vec4::w() const {
	return priv::getW(m); 
}
FM_INLINE void FM_CALL store(float* mem, vec4 v) {
	_mm_storeu_ps(mem, v.m);
}
FM_INLINE void FM_CALL store16ByteAligned(float* mem, vec4 v) {
	_mm_store_ps(mem, v.m);
}
FM_INLINE vec4 FM_CALL operator+(vec4 a, vec4 b) {
	a.m = _mm_add_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4 FM_CALL operator-(vec4 a, vec4 b) {
	a.m = _mm_sub_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4& FM_CALL operator+=(vec4& a, vec4 b) {
	a.m = _mm_add_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4& FM_CALL operator-=(vec4& a, vec4 b) {
	a.m = _mm_sub_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4 FM_CALL hadamardMul(vec4 a, vec4 b) {
	a.m = _mm_mul_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4 FM_CALL hadamardDiv(vec4 a, vec4 b) {
	a.m = _mm_div_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4 FM_CALL operator*(vec4 v, float scalar) {
	v.m = _mm_mul_ps(v.m, _mm_set1_ps(scalar));
	return v;
}
FM_INLINE vec4 FM_CALL operator*(float scalar, vec4 v) {
	return v * scalar;
}
FM_INLINE vec4 FM_CALL operator/(vec4 v, float scalar) {
	v.m = _mm_div_ps(v.m, _mm_set1_ps(scalar));
	return v;
}
FM_INLINE vec4 FM_CALL operator-(vec4 v) {
	v.m = _mm_sub_ps(_mm_setzero_ps(), v.m);
	return v;
}
FM_INLINE float FM_CALL dot(vec4 a, vec4 b) {
	return sumOfElements(hadamardMul(a, b));
}
FM_INLINE vec4 FM_CALL min(vec4 a, vec4 b) {
	a.m = _mm_min_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4 FM_CALL max(vec4 a, vec4 b) {
	a.m = _mm_max_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4 FM_CALL abs(vec4 v) {
	__m128 signMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
	v.m = _mm_andnot_ps(signMask, v.m);
	return v;
}
FM_INLINE float FM_CALL sumOfElements(vec4 v) {
	return v.x() + v.y() + v.z() + v.w();
}
FM_INLINE float FM_CALL length(vec4 v) {
	return sqrt(dot(v, v));
}
FM_INLINE float FM_CALL lengthSquared(vec4 v) {
	return dot(v, v);
}
FM_INLINE vec4 FM_CALL normalize(vec4 v) {
	return v / length(v);
}
FM_INLINE vec4 FM_CALL clamp(vec4 v, vec4 minV, vec4 maxV) {
	return min(max(v, minV), maxV);
}
FM_INLINE vec4 FM_CALL lerp(vec4 a, vec4 b, float t) {
	return a + (b-a)*t;
} 
FM_INLINE bool FM_CALL operator==(vec4 a, vec4 b) {
	vec4 eqMask = equalsMask(a, b);
	return eqMask.x() && eqMask.y() && eqMask.z();
} 
FM_INLINE bool FM_CALL operator!=(vec4 a, vec4 b) {
	vec4 eqMask = equalsMask(a, b);
	return !(eqMask.x() && eqMask.y() && eqMask.z());
}
FM_INLINE vec4 FM_CALL equalsMask(vec4 a, vec4 b) {
	a.m = _mm_cmpeq_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4 FM_CALL greaterMask(vec4 a, vec4 b) {
	a.m = _mm_cmpgt_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4 FM_CALL greaterOrEqualMask(vec4 a, vec4 b) {
	a.m = _mm_cmpge_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4 FM_CALL lesserMask(vec4 a, vec4 b) {
	a.m = _mm_cmplt_ps(a.m, b.m);
	return a;
}
FM_INLINE vec4 FM_CALL lesserOrEqualMask(vec4 a, vec4 b) {
	a.m = _mm_cmple_ps(a.m, b.m);
	return a;
}

///////////////
// mat4 impl //
///////////////
FM_INLINE vec4 FM_CALL mat4::getColumn(unsigned index) {
	return makeVec4(columns[index]);
}
FM_INLINE void FM_CALL mat4::setColumn(unsigned index, vec4 col) {
	columns[index] = col.m;
}
FM_INLINE void FM_CALL mat4::setColumn(unsigned index, float x, float y, float z, float w) {
	columns[index] = _mm_set_ps(w, z, y, x);
}
FM_INLINE void FM_CALL mat4::swapColumns(unsigned col1Index, unsigned col2Index) {
	__m128 temp = columns[col1Index];
	columns[col1Index] = columns[col2Index];
	columns[col2Index] = temp;
}
vec4 FM_CALL mat4::getRow(unsigned index) {
	vec4 row;
	switch(index)
	{
		case 0: {
			row = makeVec4(
				priv::getX(columns[0]), priv::getX(columns[1]),
				priv::getX(columns[2]), priv::getX(columns[3]));
		} break;
		
		case 1: {
			row = makeVec4(
				priv::getY(columns[0]), priv::getY(columns[1]),
				priv::getY(columns[2]), priv::getY(columns[3]));
		} break;
	
		case 2: {
			row = makeVec4(
				priv::getZ(columns[0]), priv::getZ(columns[1]),
				priv::getZ(columns[2]), priv::getZ(columns[3]));
		} break;
	
		case 3: {
			row = makeVec4(
				priv::getW(columns[0]), priv::getW(columns[1]),
				priv::getW(columns[2]), priv::getW(columns[3]));
		} break;
	
		default: {
			// TODO assert
		}
	}
	return row;
}
void FM_CALL mat4::setRow(unsigned index, vec4 row) {
	switch(index)
	{
		case 0: {
				columns[0] = priv::setX(columns[0], row.x());
				columns[1] = priv::setX(columns[1], row.y());
				columns[2] = priv::setX(columns[2], row.z());
				columns[3] = priv::setX(columns[3], row.w());
		} break;
	
		case 1: {
				columns[0] = priv::setY(columns[0], row.x());
				columns[1] = priv::setY(columns[1], row.y());
				columns[2] = priv::setY(columns[2], row.z());
				columns[3] = priv::setY(columns[3], row.w());
		} break;
	
		case 2: {
				columns[0] = priv::setZ(columns[0], row.x());
				columns[1] = priv::setZ(columns[1], row.y());
				columns[2] = priv::setZ(columns[2], row.z());
				columns[3] = priv::setZ(columns[3], row.w());
		} break;
	
		case 3: {
				columns[0] = priv::setW(columns[0], row.x());
				columns[1] = priv::setW(columns[1], row.y());
				columns[2] = priv::setW(columns[2], row.z());
				columns[3] = priv::setW(columns[3], row.w());
		} break;
	
		default: {
			// TODO assert
		}
	}	
}
FM_INLINE void FM_CALL mat4::setRow(unsigned index, float x, float y, float z, float w) {
	setRow(index, makeVec4(x, y, z, w));
}
FM_INLINE void FM_CALL mat4::swapRows(unsigned row1Index, unsigned row2Index) {
	vec4 row1 = getRow(row1Index);
	vec4 row2 = getRow(row2Index);
	setRow(row2Index, row1);
	setRow(row1Index, row2);
}
FM_INLINE vec4 FM_CALL mat4::getMainDiagonal() {
	vec4 res;
	res.setX(priv::getX(columns[0]));
	res.setY(priv::getY(columns[1]));
	res.setZ(priv::getZ(columns[2]));
	res.setW(priv::getW(columns[3]));
	return res;
}
FM_INLINE void FM_CALL mat4::setMainDiagonal(float x, float y, float z, float w) {
	columns[0] = priv::setX(columns[0], x);
	columns[1] = priv::setY(columns[1], y);
	columns[2] = priv::setZ(columns[2], z);
	columns[3] = priv::setW(columns[3], w);
}
FM_INLINE void FM_CALL mat4::setMainDiagonal(vec4 v) {
	setMainDiagonal(v.x(), v.y(), v.z(), v.w());
}
FM_INLINE mat4 FM_CALL makeMat4FromColumnMajorMemory(float* mem) {
	mat4 res;
	for(int i = 0; i < 4; ++i)
		res.columns[i] = _mm_load_ps(mem + i*4);
	return res;
}
FM_INLINE mat4 FM_CALL makeZeroMat4() {
	mat4 res;
	res.columns[0] = _mm_setzero_ps();
	res.columns[1] = _mm_setzero_ps();
	res.columns[2] = _mm_setzero_ps();
	res.columns[3] = _mm_setzero_ps();
	return res;
}
FM_INLINE mat4 FM_CALL makeIdentityMat4() {
	return makeDiagonalMat4(1.f);
}
FM_INLINE mat4 FM_CALL makeDiagonalMat4(float diag) {
	mat4 res;
	res.columns[0] = _mm_setr_ps(diag, 0.f, 0.f, 0.f);
	res.columns[1] = _mm_setr_ps(0.f, diag, 0.f, 0.f);
	res.columns[2] = _mm_setr_ps(0.f, 0.f, diag, 0.f);
	res.columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, diag);
	return res;
}
FM_INLINE mat4 FM_CALL makeDiagonalMat4(float diagX, float diagY, float diagZ, float diagW) {
	mat4 res;
	res.columns[0] = _mm_setr_ps(diagX, 0.f, 0.f, 0.f);
	res.columns[1] = _mm_setr_ps(0.f, diagY, 0.f, 0.f);
	res.columns[2] = _mm_setr_ps(0.f, 0.f, diagZ, 0.f);
	res.columns[3] = _mm_setr_ps(0.f, 0.f, 0.f, diagW);
	return res;
}
FM_INLINE mat4 FM_CALL makeDiagonalMat4(vec4 diag) {
	// TODO: What is going on with diag.x() diag.y()... 
	mat4 res;
	float* v = (float*)(&diag);
	res.columns[0] = _mm_set_ps(0.f, 0.f, 0.f, v[0]);
	res.columns[1] = _mm_set_ps(0.f, 0.f, v[1], 0.f);
	res.columns[2] = _mm_set_ps(0.f, v[2], 0.f, 0.f);
	res.columns[3] = _mm_set_ps(v[3], 0.f, 0.f, 0.f);
	return res;
}
FM_INLINE mat4 FM_CALL makeMat4FromColumns(vec4 col1, vec4 col2, vec4 col3, vec4 col4) {
	mat4 res;
	res.columns[0] = col1.m;
	res.columns[1] = col2.m;
	res.columns[2] = col3.m;
	res.columns[3] = col4.m;
	return res;
}
FM_INLINE mat4 FM_CALL makeMat4FromColumns(
	float e11, float e21, float e31, float e41,
    float e12, float e22, float e32, float e42,
    float e13, float e23, float e33, float e43,
    float e14, float e24, float e34, float e44) 
{
	mat4 res;
	res.columns[0] = _mm_setr_ps(e11, e21, e31, e41);
	res.columns[1] = _mm_setr_ps(e12, e22, e32, e42);
	res.columns[2] = _mm_setr_ps(e13, e23, e33, e43);
	res.columns[3] = _mm_setr_ps(e14, e24, e34, e44);
	return res;
}
FM_INLINE mat4 FM_CALL makeMat4FromRows(vec4 row1, vec4 row2, vec4 row3, vec4 row4) {
	mat4 res;
	res.columns[0] = _mm_setr_ps(row1.x(), row2.x(), row3.x(), row4.x());
	res.columns[1] = _mm_setr_ps(row1.y(), row2.y(), row3.y(), row4.y());
	res.columns[2] = _mm_setr_ps(row1.z(), row2.z(), row3.z(), row4.z());
	res.columns[3] = _mm_setr_ps(row1.w(), row2.w(), row3.w(), row4.w());
	return res;
}
FM_INLINE mat4 FM_CALL makeMat4FromRows(
	float e11, float e12, float e13, float e14,
    float e21, float e22, float e23, float e24,
    float e31, float e32, float e33, float e34,
    float e41, float e42, float e43, float e44)
{
	mat4 res;
	res.columns[0] = _mm_setr_ps(e11, e21, e31, e41);
	res.columns[1] = _mm_setr_ps(e12, e22, e32, e42);
	res.columns[2] = _mm_setr_ps(e13, e23, e33, e43);
	res.columns[3] = _mm_setr_ps(e14, e24, e34, e44);
	return res;
}
FM_INLINE void FM_CALL store(float* mem, mat4 mat) {
	for(int col = 0; col < 4; ++col)
		_mm_storeu_ps(mem + col*4, mat.columns[col]);
}
FM_INLINE void FM_CALL store16ByteAligned(float* mem, mat4 mat) {
	for(int col = 0; col < 4; ++col)
		_mm_store_ps(mem + col*4, mat.columns[col]);
}
FM_INLINE mat4 FM_CALL operator+(mat4 a, mat4 b) {
	for(int col = 0; col < 4; ++col)
		a.columns[col] = _mm_add_ps(a.columns[col], b.columns[col]);
	return a;
}
FM_INLINE mat4 FM_CALL operator-(mat4 a, mat4 b) {
	for(int col = 0; col < 4; ++col)
		a.columns[col] = _mm_sub_ps(a.columns[col], b.columns[col]);
	return a;
}
FM_INLINE mat4 FM_CALL operator*(mat4 a, mat4 b) {
	__m128 row;
		
	row = _mm_setr_ps(priv::getX(a.columns[0]), priv::getX(a.columns[1]),
	                  priv::getX(a.columns[2]), priv::getX(a.columns[3]));
	float res11 = priv::sumOfElements(_mm_mul_ps(row, b.columns[0]));
	float res12 = priv::sumOfElements(_mm_mul_ps(row, b.columns[1]));
	float res13 = priv::sumOfElements(_mm_mul_ps(row, b.columns[2]));
	float res14 = priv::sumOfElements(_mm_mul_ps(row, b.columns[3]));
		
	row = _mm_setr_ps(priv::getY(a.columns[0]), priv::getY(a.columns[1]),
	                  priv::getY(a.columns[2]), priv::getY(a.columns[3]));
	float res21 = priv::sumOfElements(_mm_mul_ps(row, b.columns[0]));
	float res22 = priv::sumOfElements(_mm_mul_ps(row, b.columns[1]));
	float res23 = priv::sumOfElements(_mm_mul_ps(row, b.columns[2]));
	float res24 = priv::sumOfElements(_mm_mul_ps(row, b.columns[3]));
		
	row = _mm_setr_ps(priv::getZ(a.columns[0]), priv::getZ(a.columns[1]),
	                  priv::getZ(a.columns[2]), priv::getZ(a.columns[3]));
	float res31 = priv::sumOfElements(_mm_mul_ps(row, b.columns[0]));
	float res32 = priv::sumOfElements(_mm_mul_ps(row, b.columns[1]));
	float res33 = priv::sumOfElements(_mm_mul_ps(row, b.columns[2]));
	float res34 = priv::sumOfElements(_mm_mul_ps(row, b.columns[3]));
		
	row = _mm_setr_ps(priv::getW(a.columns[0]), priv::getW(a.columns[1]),
	                  priv::getW(a.columns[2]), priv::getW(a.columns[3]));
	float res41 = priv::sumOfElements(_mm_mul_ps(row, b.columns[0]));
	float res42 = priv::sumOfElements(_mm_mul_ps(row, b.columns[1]));
	float res43 = priv::sumOfElements(_mm_mul_ps(row, b.columns[2]));
	float res44 = priv::sumOfElements(_mm_mul_ps(row, b.columns[3]));
		
	return makeMat4FromColumns(
		res11, res21, res31, res41,
	    res12, res22, res32, res42,
		res13, res23, res33, res43,
		res14, res24, res34, res44);
}
FM_INLINE vec4 FM_CALL operator*(mat4 m, vec4 v) {
	__m128 row1 = _mm_setr_ps(priv::getX(m.columns[0]), priv::getX(m.columns[1]),
	                          priv::getX(m.columns[2]), priv::getX(m.columns[3]));
	__m128 row2 = _mm_setr_ps(priv::getY(m.columns[0]), priv::getY(m.columns[1]),
	                          priv::getY(m.columns[2]), priv::getY(m.columns[3]));
	__m128 row3 = _mm_setr_ps(priv::getZ(m.columns[0]), priv::getZ(m.columns[1]),
	                          priv::getZ(m.columns[2]), priv::getZ(m.columns[3]));
	__m128 row4 = _mm_setr_ps(priv::getW(m.columns[0]), priv::getW(m.columns[1]),
	                          priv::getW(m.columns[2]), priv::getW(m.columns[3]));
	float resX = priv::sumOfElements(_mm_mul_ps(row1, v.m)); 
	float resY = priv::sumOfElements(_mm_mul_ps(row2, v.m)); 
	float resZ = priv::sumOfElements(_mm_mul_ps(row3, v.m)); 
	float resW = priv::sumOfElements(_mm_mul_ps(row4, v.m));
	return makeVec4(resX, resY, resZ, resW);
}
FM_INLINE mat4 FM_CALL operator*(mat4 m, float scalar) {
	__m128 scalarM = _mm_set1_ps(scalar);
	for(int col = 0; col < 4; ++col)
		m.columns[col] = _mm_mul_ps(m.columns[col], scalarM);
	return m;
}
FM_INLINE mat4 FM_CALL operator*(float scalar, mat4 m) {
	return m * scalar;
}
FM_INLINE mat4 FM_CALL operator/(mat4 m, float scalar) {
	__m128 scalarM = _mm_set1_ps(scalar);
	for(int col = 0; col < 4; ++col)
		m.columns[col] = _mm_div_ps(m.columns[col], scalarM);
	return m;
}
FM_INLINE mat4 FM_CALL transpose(mat4 m) {
	_MM_TRANSPOSE4_PS(m.columns[0], m.columns[1], m.columns[2], m.columns[3]);
	return m;
}
FM_INLINE mat4 FM_CALL makeTranslationMat4(float x, float y, float z) {
	return makeMat4FromRows(
		1.f, 0.f, 0.f, x,
		0.f, 1.f, 0.f, y,
		0.f, 0.f, 1.f, z,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL makeTranslationMat4(vec3 translation) {
	return makeMat4FromRows(
		1.f, 0.f, 0.f, translation.x(),
		0.f, 1.f, 0.f, translation.y(),
		0.f, 0.f, 1.f, translation.z(),
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL translate(mat4 m, float x, float y, float z) {
	m.columns[3] = _mm_add_ps(m.columns[3], _mm_set_ps(0.f, z, y, x));
	return m;
}
FM_INLINE mat4 FM_CALL translate(mat4 m, vec3 translation) {
	m.columns[3] = _mm_add_ps(m.columns[3], translation.m);
	return m;
}
FM_INLINE mat4 FM_CALL makeScaleMat4(float scalar) {
	return makeDiagonalMat4(scalar, scalar, scalar, 1.f);
} 
FM_INLINE mat4 FM_CALL makeScaleMat4(float scalarX, float scalarY, float scalarZ) {
	return makeDiagonalMat4(scalarX, scalarY, scalarZ, 1.f);
} 
FM_INLINE mat4 FM_CALL makeScaleMat4(vec3 scalar) {
	return makeDiagonalMat4(scalar.x(), scalar.y(), scalar.z(), 1.f); 
}
FM_INLINE mat4 FM_CALL scale(mat4 m, float scalar) {
	return scale(m, scalar, scalar, scalar);
}
FM_INLINE mat4 FM_CALL scale(mat4 m, float x, float y, float z) {
	vec4 mainDiag = m.getMainDiagonal();
	vec4 scalarVec = makeVec4(x, y, z, 1.f);
	mainDiag = hadamardMul(mainDiag, scalarVec);
	m.setMainDiagonal(mainDiag);
	return m;
}
FM_INLINE mat4 FM_CALL scale(mat4 m, vec3 scalar) {
	// TODO: Try to optimize this 
	return scale(m, scalar.x(), scalar.y(), scalar.z());
}
FM_INLINE mat4 FM_CALL makeRotationMat4Degrees(float degrees, float axisX, float axisY, float axisZ) {
	float r = degreesToRadians(degrees);
	return makeRotationMat4Radians(r, axisX, axisY, axisZ);
} 
FM_INLINE mat4 FM_CALL makeRotationMat4Degrees(float degrees, vec3 axis) {
	float r = degreesToRadians(degrees);
	return makeRotationMat4Radians(r, axis);
}
FM_INLINE mat4 FM_CALL makeRotationAroundXAxisMat4Degrees(float degrees) {
	float r = degreesToRadians(degrees);
	return makeRotationAroundXAxisMat4Radians(r);
}
FM_INLINE mat4 FM_CALL makeRotationAroundYAxisMat4Degrees(float degrees) {
	float r = degreesToRadians(degrees);
	return makeRotationAroundYAxisMat4Radians(r);
}
FM_INLINE mat4 FM_CALL makeRotationAroundZAxisMat4Degrees(float degrees) {
	float r = degreesToRadians(degrees);
	return makeRotationAroundZAxisMat4Radians(r);
}
FM_INLINE mat4 FM_CALL rotateDegrees(mat4 m, float degrees, float axisX, float axisY, float axisZ) {
	float r = degreesToRadians(degrees);
	return rotateRadians(m, r, axisX, axisY, axisZ);
} 
FM_INLINE mat4 FM_CALL rotateDegrees(mat4 m, float degrees, vec3 axis) {
	float r = degreesToRadians(degrees);
	return rotateRadians(m, r, axis);
}
FM_INLINE mat4 FM_CALL rotateAroundXAxisDegrees(mat4 m, float degrees) {
	float r = degreesToRadians(degrees);
	return rotateAroundXAxisRadians(m, r);
}
FM_INLINE mat4 FM_CALL rotateAroundYAxisDegrees(mat4 m, float degrees) {
	float r = degreesToRadians(degrees);
	return rotateAroundYAxisRadians(m, r);
}
FM_INLINE mat4 FM_CALL rotateAroundZAxisDegrees(mat4 m, float degrees) {
	float r = degreesToRadians(degrees);
	return rotateAroundZAxisRadians(m, r);
}
FM_INLINE mat4 FM_CALL makeRotationMat4Radians(float radians, float axisX, float axisY, float axisZ) {
	vec3 normalized = normalize(makeVec3(axisX, axisY, axisZ));
	axisX = normalized.x();
	axisY = normalized.y();
	axisZ = normalized.z();
	float sinTheta = sin(radians);
	float cosTheta = cos(radians);
	float cosVal = 1.f - cosTheta;
	return makeMat4FromColumns(
		(axisX * axisX * cosVal) + cosTheta,
		(axisX * axisY * cosVal) + (axisZ * sinTheta),
		(axisX * axisZ * cosVal) - (axisY * sinTheta),
		0.f,
		(axisY * axisX * cosVal) - (axisZ * sinTheta),
		(axisY * axisY * cosVal) + cosTheta,
		(axisY * axisZ * cosVal) + (axisX * sinTheta),
		0.f,
		(axisZ * axisX * cosVal) + (axisY * sinTheta),
		(axisZ * axisY * cosVal) - (axisX * sinTheta),
		(axisZ * axisZ * cosVal) + cosTheta,
		0.f,
		0.f, 0.f, 0.f, 1.f);
} 
FM_INLINE mat4 FM_CALL makeRotationMat4Radians(float radians, vec3 axis) {
	return makeRotationMat4Radians(radians, axis.x(), axis.y(), axis.z());
}
FM_INLINE mat4 FM_CALL makeRotationAroundXAxisMat4Radians(float r) {
	return makeMat4FromRows(
		1.f, 0.f, 0.f, 0.f,
		0.f, cos(r), -sin(r), 0.f,
		0.f, sin(r), cos(r), 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL makeRotationAroundYAxisMat4Radians(float r) {
	return makeMat4FromRows(
		cos(r), 0.f, sin(r), 0.f,
		0.f, 1.f, 0.f, 0.f,
		-sin(r), 0.f, cos(r), 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL makeRotationAroundZAxisMat4Radians(float r) {
	return makeMat4FromRows(
		cos(r), -sin(r), 0.f, 0.f,
		sin(r), cos(r), 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
FM_INLINE mat4 FM_CALL rotateRadians(mat4 m, float radians, float axisX, float axisY, float axisZ) {
	mat4 rotMat = makeRotationMat4Radians(radians, axisX, axisY, axisZ);
	return m * rotMat;
}
FM_INLINE mat4 FM_CALL rotateRadians(mat4 m, float radians, vec3 axis) {
	mat4 rotMat = makeRotationMat4Radians(radians, axis);
	return m * rotMat;
}
FM_INLINE mat4 FM_CALL rotateAroundXAxisRadians(mat4 m, float radians) {
	mat4 rotMat = makeRotationAroundXAxisMat4Radians(radians);
	return m * rotMat;	
}
FM_INLINE mat4 FM_CALL rotateAroundYAxisRadians(mat4 m, float radians) {
	mat4 rotMat = makeRotationAroundYAxisMat4Radians(radians);
	return m * rotMat;
}
FM_INLINE mat4 FM_CALL rotateAroundZAxisRadians(mat4 m, float radians) {
	mat4 rotMat = makeRotationAroundZAxisMat4Radians(radians);
	return m * rotMat;
}
mat4 makeOrthographicMat4(float left, float right, float bottom, float top, float nearValue, float farValue) {
	float rl = right - left;
	float tb = top - bottom;
	float fn = farValue - nearValue; 
		
	return makeMat4FromRows(
		2.f / rl, 0.f, 0.f, -((right + left) / rl),
		0.f, 2.f / tb, 0.f, -((top + bottom) / tb),
		0.f, 0.f, -2.f / fn, -((farValue + nearValue) / fn),
		0.f, 0.f, 0.f, 1.f
	);
}
mat4 makePerspectiveMat4(float fov, float aspectRatio, float nearValue, float farValue)
{
	float cotangent = 1.f / tanf(fov * FM_PI32 / 360.f);
	float nf = nearValue - farValue;
		
	return makeMat4FromRows(
		cotangent / aspectRatio, 0.f, 0.f, 0.f,
		0.f, cotangent, 0.f, 0.f,
		0.f, 0.f, 
		(nearValue + farValue) / nf,
		(2 * nearValue * farValue) / nf,
		0.f, 0.f, -1.f, 0.f);
}

} // !namespace fm

#endif // FM_IMPLEMENTATION
#endif // FM_IMPLEMENTATION_ALREADY_DEFINED

