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

struct vec2
{
	__m128 m;

	FM_INLINE explicit vec2(const float* v); 
	FM_INLINE vec2(float x, float y);
	FM_INLINE explicit vec2(float a);
	FM_INLINE explicit vec2(__m128 m);
	FM_INLINE vec2();

	FM_INLINE void FM_CALL storeTo(float* mem);

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
// TODO: Add comparison functions, lerp and clamp  

struct vec2d
{
	__m128d m;

	FM_INLINE explicit vec2d(const double* v);
	FM_INLINE vec2d(double x, double y);
	FM_INLINE explicit vec2d(double a);
	FM_INLINE explicit vec2d(__m128d m);
	FM_INLINE vec2d();

	FM_INLINE void FM_CALL storeTo(double* mem);
	FM_INLINE void FM_CALL storeTo16ByteAligned(double* mem);

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
// TODO: Add comparison functions, lerp and clamp  

struct vec2i
{
	__m128i m;

	FM_INLINE explicit vec2i(const int* v);
	FM_INLINE vec2i(int x, int y);
	FM_INLINE explicit vec2i(int a); 
	FM_INLINE explicit vec2i(__m128i m); 
	FM_INLINE vec2i();

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

	FM_INLINE void FM_CALL storeTo(int* mem); 

	FM_INLINE void FM_CALL setX(int x);
	FM_INLINE void FM_CALL setY(int y);
};
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
// TODO: Add hadamardDiv() and operator/ - Maybe I can do that using cast instructions?
// TODO: Add more operators


struct vec2u
{
	__m128i m;

	FM_INLINE explicit vec2u(const unsigned* v); 
	FM_INLINE vec2u(unsigned x, unsigned y); 
	FM_INLINE explicit vec2u(unsigned a);
	FM_INLINE explicit vec2u(__m128i m);
	FM_INLINE vec2u();

	FM_INLINE void FM_CALL setX(unsigned x);
	FM_INLINE void FM_CALL setY(unsigned y);

	FM_INLINE void FM_CALL storeTo(unsigned* mem);

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
// TODO: Add hadamardDiv() and operator/
// TODO: Add more operators

struct vec3
{
	__m128 m;

	FM_INLINE explicit vec3(float* v);
	FM_INLINE vec3(float x, float y, float z);
	FM_INLINE explicit vec3(float a);
	FM_INLINE explicit vec3(__m128 m);
	FM_INLINE vec3();

	FM_INLINE void FM_CALL setX(float x);
	FM_INLINE void FM_CALL setY(float y);
	FM_INLINE void FM_CALL setZ(float z);

	FM_INLINE void FM_CALL storeTo(float* mem); 

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
// TODO: Add comparison functions, lerp and clamp  


struct vec4
{
	__m128 m;

	FM_INLINE explicit vec4(const float* v); 
	FM_INLINE vec4(float x, float y, float z, float w);
	FM_INLINE explicit vec4(float a);
	FM_INLINE explicit vec4(__m128 m);
	FM_INLINE vec4();

	FM_INLINE void FM_CALL storeTo(float* mem);
	FM_INLINE void FM_CALL storeTo16ByteAligned(float* mem);

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
namespace internal {
	FM_INLINE __m128 insertFloatY(__m128 m, float a) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(a));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 0));
		return _mm_move_ss(temp, m);
	}
	FM_INLINE __m128 insertFloatZ(__m128 m, float a) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(a));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 0, 1, 0));
		return _mm_move_ss(temp, m);
	}
	FM_INLINE __m128 insertFloatW(__m128 m, float a) {
		__m128 temp = _mm_move_ss(m, _mm_set_ss(a));
		temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(0, 2, 1, 0));
		return _mm_move_ss(temp, m);
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
// TODO: Do faster implementations of these 

///////////////
// vec2 impl //
///////////////
FM_INLINE vec2::vec2(const float* v) {
	m = _mm_set_ps(0.f, 0.f, v[1], v[0]); 
}  
FM_INLINE vec2::vec2(float x, float y) {
	m = _mm_set_ps(0.f, 0.f, y, x); 
} 
FM_INLINE vec2::vec2(float a) {
	m = _mm_set1_ps(a); 
}
FM_INLINE vec2::vec2(__m128 m) 
	:m(m) {}
FM_INLINE vec2::vec2() {
	m = _mm_setzero_ps(); 
} 
FM_INLINE float FM_CALL vec2::x() const { 
	return _mm_cvtss_f32(m); 
}
FM_INLINE float FM_CALL vec2::y() const {
	return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE vec2 FM_CALL vec2::yx() const {
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE vec2 FM_CALL vec2::xx() const {
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 0))); 
}
FM_INLINE vec2 FM_CALL vec2::yy() const {
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE void FM_CALL vec2::storeTo(float* mem) {
	mem[0] = x();
	mem[1] = y(); 
} 
FM_INLINE void FM_CALL vec2::setX(float x) {
	m = _mm_move_ss(m, _mm_set_ss(x)); 
}
FM_INLINE void FM_CALL vec2::setY(float y) { 
	m = internal::insertFloatY(m, y);
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
FM_INLINE vec2 FM_CALL min(vec2 a, vec2 b) {
	a.m = _mm_min_ps(a.m, b.m);
	return a;
}
FM_INLINE float FM_CALL dot(vec2 a, vec2 b) {
	return sumOfElements(hadamardMul(a, b));
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

////////////////
// vec2d impl //
////////////////
FM_INLINE vec2d::vec2d(const double* v) { 
	m = _mm_set_pd(v[1], v[0]); 
} 
FM_INLINE vec2d::vec2d(double x, double y) {
	m = _mm_set_pd(y, x); 
} 
FM_INLINE vec2d::vec2d(double a) {
	m = _mm_set1_pd(a);
} 
FM_INLINE vec2d::vec2d(__m128d m) 
	: m(m) {}
FM_INLINE vec2d::vec2d() { 
	m = _mm_setzero_pd(); 
}
FM_INLINE double FM_CALL vec2d::x() const {
	return _mm_cvtsd_f64(m);
}
FM_INLINE double FM_CALL vec2d::y() const { 
	return _mm_cvtsd_f64(_mm_shuffle_pd(m, m, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE vec2d FM_CALL vec2d::yx() const {
	return vec2d(_mm_shuffle_pd(m, m, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE vec2d FM_CALL vec2d::xx() const {
	return vec2d(_mm_unpacklo_pd(m, m));
}
FM_INLINE vec2d FM_CALL vec2d::yy() const {
	return vec2d(_mm_unpackhi_pd(m, m));
}
FM_INLINE void FM_CALL vec2d::storeTo(double* mem) { 
	_mm_storeu_pd(mem, m); 
} 
FM_INLINE void FM_CALL vec2d::storeTo16ByteAligned(double* mem) {
	_mm_store_pd(mem, m); 
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

////////////////
// vec2i impl //
////////////////
FM_INLINE vec2i::vec2i(const int* v) {
	m = _mm_set_epi32(0, 0, v[1], v[0]); 
}
FM_INLINE vec2i::vec2i(int x, int y) {
	m = _mm_set_epi32(0, 0, y, x); 
}
FM_INLINE vec2i::vec2i(int a) { 
	m = _mm_set1_epi32(a); 
}
FM_INLINE vec2i::vec2i(__m128i m) 
	:m(m) {}
FM_INLINE vec2i::vec2i() {
	m = _mm_setzero_si128();
}
FM_INLINE int FM_CALL vec2i::x() const { 
	return _mm_cvtsi128_si32(m); 
} 
FM_INLINE int FM_CALL vec2i::y() const {
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(m, _MM_SHUFFLE(1, 1, 1, 1))); 
} 
FM_INLINE vec2i FM_CALL vec2i::yx() const {
	return vec2i(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 0, 1)));
}
FM_INLINE vec2i FM_CALL vec2i::xx() const {
	return vec2i(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 0, 0)));
}
FM_INLINE vec2i FM_CALL vec2i::yy() const {
	return vec2i(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 1, 1)));
}
FM_INLINE void FM_CALL vec2i::storeTo(int* mem) {
	mem[0] = x();
	mem[1] = y();
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
FM_INLINE vec2u::vec2u(const unsigned* v) {
	m = _mm_set_epi32(0, 0, v[1], v[0]); 
}
FM_INLINE vec2u::vec2u(unsigned x, unsigned y) {
	m = _mm_set_epi32(0, 0, y, x); 
}
FM_INLINE vec2u::vec2u(unsigned a) {
	m = _mm_set1_epi32(a); 
} 
FM_INLINE vec2u::vec2u(__m128i m) 
	:m(m) {}
FM_INLINE vec2u::vec2u() {
	m = _mm_setzero_si128(); 
}
FM_INLINE unsigned FM_CALL vec2u::x() const {
	return (unsigned)_mm_cvtsi128_si32(m); 
} 
FM_INLINE unsigned FM_CALL vec2u::y() const { 
	return (unsigned)_mm_cvtsi128_si32(_mm_shuffle_epi32(m, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE vec2u FM_CALL vec2u::yx() const { 
	return vec2u(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 0, 1))); 
}
FM_INLINE vec2u FM_CALL vec2u::xx() const { 
	return vec2u(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 0, 0)));
}
FM_INLINE vec2u FM_CALL vec2u::yy() const { 
	return vec2u(_mm_shuffle_epi32(m, _MM_SHUFFLE(3, 2, 1, 1)));
}
FM_INLINE void FM_CALL vec2u::storeTo(unsigned* mem) {
	mem[0] = x();
	mem[1] = y();
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
FM_INLINE vec3::vec3(float* v) {
	m = _mm_set_ps(0, v[2], v[1], v[0]);
}
FM_INLINE vec3::vec3(float x, float y, float z) {
	m = _mm_set_ps(0, z, y, x); 
}
FM_INLINE vec3::vec3(float a) {
	m = _mm_set1_ps(a);
}
FM_INLINE vec3::vec3(__m128 m)
	:m(m) {}
FM_INLINE vec3::vec3() {
	m = _mm_setzero_ps();
}
FM_INLINE void FM_CALL vec3::setX(float x) {
	m = _mm_move_ss(m, _mm_set_ss(x));
}
FM_INLINE void FM_CALL vec3::setY(float y) {
	m = internal::insertFloatY(m, y);
}
FM_INLINE void FM_CALL vec3::setZ(float z) {
	m = internal::insertFloatZ(m, z);
}
FM_INLINE void FM_CALL vec3::storeTo(float* mem) {
	mem[0] = x();		
	mem[1] = y();		
	mem[2] = z();		
}
FM_INLINE float FM_CALL vec3::x() const {
	return _mm_cvtss_f32(m);
}
FM_INLINE float FM_CALL vec3::y() const {
	return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(1, 1, 1, 1)));
}
FM_INLINE float FM_CALL vec3::z() const {
	return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(2, 2, 2, 2)));
}
#ifndef FM_EXCLUDE_SWIZZLES
FM_INLINE vec2 FM_CALL vec3::xy() const {
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 0)));
}
FM_INLINE vec2 FM_CALL vec3::yx() const {
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 1)));
}
FM_INLINE vec2 FM_CALL vec3::yz() const {
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 1)));
}
FM_INLINE vec2 FM_CALL vec3::zy() const {
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 2)));
}
FM_INLINE vec2 FM_CALL vec3::xz() const {
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 0)));
}
FM_INLINE vec2 FM_CALL vec3::zx() const {
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 2)));
}
FM_INLINE vec2 FM_CALL vec3::xx() const {
	// TODO: Try to optimize it
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 0)));
}
FM_INLINE vec2 FM_CALL vec3::yy() const {
	// TODO: Try to optimize it
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 1)));
}
FM_INLINE vec2 FM_CALL vec3::zz() const {
	// TODO: Try to optimize it
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 2)));
}
FM_INLINE vec3 FM_CALL vec3::xyz() const {
	return *this;
}
FM_INLINE vec3 FM_CALL vec3::yzx() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 1)));
}
FM_INLINE vec3 FM_CALL vec3::zxy() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 0, 2)));
}
FM_INLINE vec3 FM_CALL vec3::zyx() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 2)));
}
FM_INLINE vec3 FM_CALL vec3::xzy() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 2, 0)));
}
FM_INLINE vec3 FM_CALL vec3::yxz() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 0, 1)));
}
FM_INLINE vec3 FM_CALL vec3::xxy() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 0, 0)));
}
FM_INLINE vec3 FM_CALL vec3::xxz() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 0, 0)));
}
FM_INLINE vec3 FM_CALL vec3::yyx() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 1)));
}
FM_INLINE vec3 FM_CALL vec3::yyz() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 1, 1)));
}
FM_INLINE vec3 FM_CALL vec3::zzx() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 2)));
}
FM_INLINE vec3 FM_CALL vec3::zzy() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 2, 2)));
}
FM_INLINE vec3 FM_CALL vec3::yxx() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 1)));
}
FM_INLINE vec3 FM_CALL vec3::zxx() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 2)));
}
FM_INLINE vec3 FM_CALL vec3::xyy() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 1, 0)));
}
FM_INLINE vec3 FM_CALL vec3::zyy() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 1, 2)));
}
FM_INLINE vec3 FM_CALL vec3::xzz() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 2, 0)));
}
FM_INLINE vec3 FM_CALL vec3::yzz() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 2, 1)));
}
FM_INLINE vec3 FM_CALL vec3::xyx() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 1, 0)));
}
FM_INLINE vec3 FM_CALL vec3::xzx() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 2, 0)));
}
FM_INLINE vec3 FM_CALL vec3::yxy() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 0, 1)));
}
FM_INLINE vec3 FM_CALL vec3::yzy() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 2, 1)));
}
FM_INLINE vec3 FM_CALL vec3::zxz() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 0, 2)));
}
FM_INLINE vec3 FM_CALL vec3::zyz() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 1, 2)));
}
FM_INLINE vec3 FM_CALL vec3::xxx() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 0)));
}
FM_INLINE vec3 FM_CALL vec3::yyy() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 1, 1, 1)));
}
FM_INLINE vec3 FM_CALL vec3::zzz() const {
	return vec3(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 2, 2, 2)));
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

///////////////
// vec4 impl //
///////////////
FM_INLINE vec4::vec4(const float* v) {
	m = _mm_set_ps(v[3], v[2], v[1], v[0]);	
} 
FM_INLINE vec4::vec4(float x, float y, float z, float w) {
	m = _mm_set_ps(w, z, y, x);
}
FM_INLINE vec4::vec4(float a) {
	m = _mm_set1_ps(a);
}
FM_INLINE vec4::vec4(__m128 m) 
	:m(m) {}
FM_INLINE vec4::vec4() {
	m = _mm_setzero_ps();
}
FM_INLINE void FM_CALL vec4::storeTo(float* mem) {
	_mm_storeu_ps(mem, m);
}
FM_INLINE void FM_CALL vec4::storeTo16ByteAligned(float* mem) {
	_mm_store_ps(mem, m);
}
FM_INLINE void FM_CALL vec4::setX(float x) {
	m = _mm_move_ss(m, _mm_set_ss(x));
}
FM_INLINE void FM_CALL vec4::setY(float y) {
	m = internal::insertFloatY(m, y);
} 
FM_INLINE void FM_CALL vec4::setZ(float z) {
	m = internal::insertFloatZ(m, z);
} 
FM_INLINE void FM_CALL vec4::setW(float w) {
	m = internal::insertFloatW(m, w);
} 
FM_INLINE float FM_CALL vec4::x() const {
	return _mm_cvtss_f32(m);
}
FM_INLINE float FM_CALL vec4::y() const {
	return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 1)));
}
FM_INLINE float FM_CALL vec4::z() const {
	return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 2)));
}
FM_INLINE float FM_CALL vec4::w() const {
	return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(3, 2, 1, 3)));
}

} // !namespace fm

#endif // FM_IMPLEMENTATION
#endif // FM_IMPLEMENTATION_ALREADY_DEFINED

