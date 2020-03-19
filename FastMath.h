#ifndef FAST_MATH_H
#define FAST_MATH_H

#include <emmintrin.h>

// TODO: make FM_INLINE work on all compilers

#define FM_INLINE __forceinline
#define FM_CALL __vectorcall

namespace fm {

struct vec2
{
	FM_INLINE vec2(const float* v) { m = _mm_set_ps(0.f, 0.f, v[1], v[0]); }  
	FM_INLINE vec2(float x, float y) { m = _mm_set_ps(0.f, 0.f, y, x); } 
	FM_INLINE vec2(float a) { m = _mm_set1_ps(a); }
	FM_INLINE vec2(__m128 m) : m(m) {}
	FM_INLINE vec2() {} 

	FM_INLINE float FM_CALL x() const { return _mm_cvtss_f32(m); }
	FM_INLINE float FM_CALL u() const { return x(); } 
	FM_INLINE float FM_CALL left() const { return x(); } 
	FM_INLINE float FM_CALL width() const { return x(); } 

	FM_INLINE float FM_CALL y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(1, 1, 1, 1))); }
	FM_INLINE float FM_CALL v() const { return y(); } 
	FM_INLINE float FM_CALL top() const { return y(); } 
	FM_INLINE float FM_CALL height() const { return y(); } 

	// TODO: Add swizzles
	// TODO: Add store()
	// TODO: Add setters
	// TODO: Add array style access

	__m128 m;
};
FM_INLINE vec2 FM_CALL operator+(vec2 a, vec2 b) { a.m = _mm_add_ps(a.m, b.m); return a; }
FM_INLINE vec2 FM_CALL operator-(vec2 a, vec2 b) { a.m = _mm_sub_ps(a.m, b.m); return a; }
FM_INLINE vec2 FM_CALL hadamardMul(vec2 a, vec2 b) { a.m = _mm_mul_ps(a.m, b.m); return a; }
FM_INLINE vec2 FM_CALL hadamardDiv(vec2 a, vec2 b) { a.m = _mm_div_ps(a.m, b.m); return a; }
FM_INLINE vec2 FM_CALL operator*(vec2 v, float scalar) { v.m = _mm_mul_ps(v.m, _mm_set1_ps(scalar)); return v; }
FM_INLINE vec2 FM_CALL operator*(float scalar, vec2 v) { v.m = _mm_mul_ps(v.m, _mm_set1_ps(scalar)); return v; }
FM_INLINE vec2 FM_CALL operator/(vec2 v, float scalar) { v.m = _mm_div_ps(v.m, _mm_set1_ps(scalar)); return v; }
// TODO: Add more operators, dot, length, normalize

struct vec2d
{
	FM_INLINE explicit vec2d(const double* v) { _mm_set_pd(v[1], v[0]); } 
	FM_INLINE explicit vec2d(double x, double y) { m = _mm_set_pd(y, x); } 
	FM_INLINE explicit vec2d(double a) { m = _mm_set1_pd(a); } 
	FM_INLINE explicit vec2d(__m128d m) : m(m) {}
	FM_INLINE vec2d() {}

	FM_INLINE double FM_CALL x() const { return _mm_cvtsd_f64(m); }
	FM_INLINE double FM_CALL u() const { return x(); }
	FM_INLINE double FM_CALL left() const { return x(); }
	FM_INLINE double FM_CALL width() const { return x(); }

	FM_INLINE double FM_CALL y() const { return _mm_cvtsd_f64(_mm_shuffle_pd(m, m, _MM_SHUFFLE(1, 1, 1, 1))); }
	FM_INLINE double FM_CALL v() const { return y(); }
	FM_INLINE double FM_CALL height() const { return y(); }
	FM_INLINE double FM_CALL top() const { return y(); }

	// TODO: Add swizzles
	// TODO: Add store()
	// TODO: Add setters
	// TODO: Add array style access

	__m128d m;
};
FM_INLINE vec2d FM_CALL operator+(vec2d a, vec2d b) { a.m = _mm_add_pd(a.m, b.m); return a; }
FM_INLINE vec2d FM_CALL operator-(vec2d a, vec2d b) { a.m = _mm_sub_pd(a.m, b.m); return a; }
FM_INLINE vec2d FM_CALL hadamardMul(vec2d a, vec2d b) { a.m = _mm_mul_pd(a.m, b.m); return a; }
FM_INLINE vec2d FM_CALL hadamardDiv(vec2d a, vec2d b) { a.m = _mm_div_pd(a.m, b.m); return a; }
FM_INLINE vec2d FM_CALL operator*(vec2d v, double scalar) { v.m = _mm_mul_pd(v.m, _mm_set1_pd(scalar)); return v; }
FM_INLINE vec2d FM_CALL operator*(double scalar, vec2d v) { v.m = _mm_mul_pd(v.m, _mm_set1_pd(scalar)); return v; } 
FM_INLINE vec2d FM_CALL operator/(vec2d v, double scalar) { v.m = _mm_div_pd(v.m, _mm_set1_pd(scalar)); return v; }
// TODO: Add more operators, dot, length, normalize

union vec2i
{
	vec2i(int x, int y) : x(x), y(y) {}
	vec2i(int a) : x(a), y(a) {}
	vec2i() : x(0.f), y(0.f) {} 

	struct {
		int x, y;
	};
	struct {
		int u, v;
	};
	struct {
		int left, top;
	};
	struct {
		int width, height;
	};
	int elements[2];
};

vec2i operator+(vec2i a, vec2i b);
vec2i operator-(vec2i a, vec2i b);
vec2i operator*(vec2i v, int scalar);
vec2i operator*(int scalar, vec2i v);
vec2i operator/(vec2i v, int scalar);
vec2i hadamardMul(vec2i a, vec2i b);
vec2i hadamardDiv(vec2i a, vec2i b);


union vec2u
{
	vec2u(unsigned x, unsigned y) : x(x), y(y) {}
	vec2u(unsigned a) : x(a), y(a) {}
	vec2u() : x(0.f), y(0.f) {} 

	struct {
		unsigned x, y;
	};
	struct {
		unsigned u, v;
	};
	struct {
		unsigned left, top;
	};
	struct {
		unsigned width, height;
	};
	unsigned elements[2];
};

vec2u operator+(vec2u a, vec2u b);
vec2u operator-(vec2u a, vec2u b);
vec2u operator*(vec2u v, unsigned scalar);
vec2u operator*(unsigned scalar, vec2u v);
vec2u operator/(vec2u v, unsigned scalar);
vec2u hadamardMul(vec2u a, vec2u b);
vec2u hadamardDiv(vec2u a, vec2u b);


}

#endif // FAST_MATH_H


#ifdef FAST_MATH_IMPLEMENTATION

#include <math.h>

namespace fm {

///////////////////////////////
// vec2i functions no simd ////
///////////////////////////////
vec2i operator+(vec2i a, vec2i b)
{
	return vec2i(a.x + b.x, a.y + b.y);
}

vec2i operator-(vec2i a, vec2i b)
{
	return vec2i(a.x - b.x, a.y - b.y);
}

vec2i operator*(vec2i v, int scalar)
{
	return vec2i(v.x * scalar, v.y * scalar);
}

vec2i operator*(int scalar, vec2i v)
{
	return vec2i(v.x * scalar, v.y * scalar);
}

vec2i operator/(vec2i v, int scalar)
{
	return vec2i(v.x / scalar, v.y / scalar);
}

vec2i hadamardMul(vec2i a, vec2i b)
{
	return vec2i(a.x * b.x, a.y * b.y);
}

vec2i hadamardDiv(vec2i a, vec2i b)
{
	return vec2i(a.x / b.x, a.y / b.y);
}

///////////////////////////////
// vec2u functions no simd ////
///////////////////////////////
vec2u operator+(vec2u a, vec2u b)
{
	return vec2u(a.x + b.x, a.y + b.y);
}

vec2u operator-(vec2u a, vec2u b)
{
	return vec2u(a.x - b.x, a.y - b.y);
}

vec2u operator*(vec2u v, unsigned scalar)
{
	return vec2u(v.x * scalar, v.y * scalar);
}

vec2u operator*(unsigned scalar, vec2u v)
{
	return vec2u(v.x * scalar, v.y * scalar);
}

vec2u operator/(vec2u v, unsigned scalar)
{
	return vec2u(v.x / scalar, v.y / scalar);
}

vec2u hadamardMul(vec2u a, vec2u b)
{
	return vec2u(a.x * b.x, a.y * b.y);
}

vec2u hadamardDiv(vec2u a, vec2u b)
{
	return vec2u(a.x / b.x, a.y / b.y);
}

}

#endif FAST_MATH_IMPLEMENTATION

