#ifndef FAST_MATH_H
#define FAST_MATH_H

#include <emmintrin.h>

#define FAST_MATH_INLINE __forceinline

namespace fm {

union vec2
{
	vec2(float x, float y) : x(x), y(y) {}
	vec2(float a) : x(a), y(a) {}
	vec2() : x(0.f), y(0.f) {} 

	struct {
		float x, y;
	};
	struct {
		float u, v;
	};
	struct {
		float left, top;
	};
	struct {
		float width, height;
	};
	float elements[2];
};

vec2 operator+(vec2 a, vec2 b);
vec2 operator-(vec2 a, vec2 b);
vec2 operator*(vec2 v, float scalar);
vec2 operator*(float scalar, vec2 v);
vec2 operator/(vec2 v, float scalar);
vec2 hadamardMul(vec2 a, vec2 b);
vec2 hadamardDiv(vec2 a, vec2 b);
float dot(vec2 a, vec2 b);
float lenght(vec2 v);
vec2 normalize(vec2 v);


struct vec2d
{
	FAST_MATH_INLINE explicit vec2d(const double* v) { _mm_set_pd(v[1], v[0]); } 
	FAST_MATH_INLINE explicit vec2d(double x, double y) { m = _mm_set_pd(y, x); } 
	FAST_MATH_INLINE explicit vec2d(double a) { m = _mm_set1_pd(a); } 
	FAST_MATH_INLINE explicit vec2d(__m128d m) : m(m) {}
	FAST_MATH_INLINE vec2d() {}

	FAST_MATH_INLINE double __vectorcall x() const { return _mm_cvtsd_f64(m); }
	FAST_MATH_INLINE double __vectorcall y() const { return _mm_cvtsd_f64(_mm_shuffle_pd(m, m, _MM_SHUFFLE(1, 1, 1, 1))); }
	FAST_MATH_INLINE double __vectorcall u() const { return x(); }
	FAST_MATH_INLINE double __vectorcall v() const { return y(); }
	FAST_MATH_INLINE double __vectorcall width() const { return x(); }
	FAST_MATH_INLINE double __vectorcall height() const { return y(); }
	FAST_MATH_INLINE double __vectorcall left() const { return x(); }
	FAST_MATH_INLINE double __vectorcall top() const { return y(); }

	// TODO: Add swizzles
	// TODO: Add store()
	// TODO: Add setters
	// TODO: Add array style access

	__m128d m;
};
FAST_MATH_INLINE vec2d __vectorcall operator+(vec2d a, vec2d b) { a.m = _mm_add_pd(a.m, b.m); return a; }
FAST_MATH_INLINE vec2d __vectorcall operator-(vec2d a, vec2d b) { a.m = _mm_sub_pd(a.m, b.m); return a; }
FAST_MATH_INLINE vec2d __vectorcall hadamardMul(vec2d a, vec2d b) { a.m = _mm_mul_pd(a.m, b.m); return a; }
FAST_MATH_INLINE vec2d __vectorcall hadamardDiv(vec2d a, vec2d b) { a.m = _mm_div_pd(a.m, b.m); return a; }
FAST_MATH_INLINE vec2d __vectorcall operator*(vec2d v, double scalar) { v.m = _mm_mul_pd(v.m, _mm_set1_pd(scalar)); return v; }
FAST_MATH_INLINE vec2d __vectorcall operator*(double scalar, vec2d v) { v.m = _mm_mul_pd(v.m, _mm_set1_pd(scalar)); return v; } 
FAST_MATH_INLINE vec2d __vectorcall operator/(vec2d v, double scalar) { v.m = _mm_div_pd(v.m, _mm_set1_pd(scalar)); return v; }
// TODO: Add more operators

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
// vec2 functions no simd  ////
///////////////////////////////
vec2 operator+(vec2 a, vec2 b)
{
	return vec2(a.x + b.x, a.y + b.y);
}

vec2 operator-(vec2 a, vec2 b)
{
	return vec2(a.x - b.x, a.y - b.y);
}

vec2 operator*(vec2 v, float scalar)
{
	return vec2(v.x * scalar, v.y * scalar);
}

vec2 operator*(float scalar, vec2 v)
{
	return vec2(v.x * scalar, v.y * scalar);
}

vec2 operator/(vec2 v, float scalar)
{
	return vec2(v.x / scalar, v.y / scalar);
}

vec2 hadamardMul(vec2 a, vec2 b)
{
	return vec2(a.x * b.x, a.y * b.y);
}

vec2 hadamardDiv(vec2 a, vec2 b)
{
	return vec2(a.x / b.x, a.y / b.y);
}

float dot(vec2 a, vec2 b)
{
	return a.x * b.x + a.y * b.y;
}

float length(vec2 v)
{
	return sqrt(v.x * v.x + v.y * v.y);	
}

vec2 normalize(vec2 v)
{
	return v / length(v);
}

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

