#ifndef FAST_MATH_H
#define FAST_MATH_H

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


union vec2d
{
	vec2d(double x, double y) : x(x), y(y) {}
	vec2d(double a) : x(a), y(a) {}
	vec2d() : x(0.f), y(0.f) {} 

	struct {
		double x, y;
	};
	struct {
		double u, v;
	};
	struct {
		double left, top;
	};
	struct {
		double width, height;
	};
	double elements[2];
};

vec2d operator+(vec2d a, vec2d b);
vec2d operator-(vec2d a, vec2d b);
vec2d operator*(vec2d v, double scalar);
vec2d operator*(double scalar, vec2d v);
vec2d operator/(vec2d v, double scalar);
vec2d hadamardMul(vec2d a, vec2d b);
vec2d hadamardDiv(vec2d a, vec2d b);
double dot(vec2d a, vec2d b);
double lenght(vec2d v);
vec2d normalize(vec2d v);


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


#ifdef FAST_MATH_NO_SIMD 
///////////////////////////////
// vec2d functions no simd ////
///////////////////////////////
vec2d operator+(vec2d a, vec2d b)
{
	return vec2d(a.x + b.x, a.y + b.y);
}

vec2d operator-(vec2d a, vec2d b)
{
	return vec2d(a.x - b.x, a.y - b.y);
}

vec2d operator*(vec2d v, double scalar)
{
	return vec2d(v.x * scalar, v.y * scalar);
}

vec2d operator*(double scalar, vec2d v)
{
	return vec2d(v.x * scalar, v.y * scalar);
}

vec2d operator/(vec2d v, double scalar)
{
	return vec2d(v.x / scalar, v.y / scalar);
}

vec2d hadamardMul(vec2d a, vec2d b)
{
	return vec2d(a.x * b.x, a.y * b.y);
}

vec2d hadamardDiv(vec2d a, vec2d b)
{
	return vec2d(a.x / b.x, a.y / b.y);
}

double dot(vec2d a, vec2d b)
{
	return a.x * b.x + a.y * b.y;
}

double length(vec2d v)
{
	return sqrt(v.x * v.x + v.y * v.y);	
}

vec2d normalize(vec2d v)
{
	return v / length(v);
}
#endif

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

#ifndef FAST_MATH_NO_SIMD 

#include <emmintrin.h>

/////////////////////
// vec2d functions //
/////////////////////
vec2d operator+(vec2d a, vec2d b)
{
	__m128d sA = _mm_set_pd(a.y, a.x);
	__m128d sB = _mm_set_pd(b.y, b.x);
	__m128d sResult = _mm_add_pd(sA, sB);
	vec2d result;
	_mm_store_pd(reinterpret_cast<double*>(&result), sResult);
	return result;
}

vec2d operator-(vec2d a, vec2d b)
{
	__m128d sA = _mm_set_pd(a.y, a.x);
	__m128d sB = _mm_set_pd(b.y, b.x);
	__m128d sResult = _mm_sub_pd(sA, sB);
	vec2d result;
	_mm_store_pd(reinterpret_cast<double*>(&result), sResult);
	return result;
}

vec2d operator*(vec2d v, double scalar)
{
	__m128d sV = _mm_set_pd(v.y, v.x);
	__m128d sScalar = _mm_set1_pd(scalar);
	__m128d sResult = _mm_mul_pd(sV, sScalar);
	vec2d result;
	_mm_store_pd(reinterpret_cast<double*>(&result), sResult);
	return result;
}

vec2d operator*(double scalar, vec2d v)
{
	return v * scalar;
}

vec2d operator/(vec2d v, double scalar)
{
	__m128d sV = _mm_set_pd(v.y, v.x);
	__m128d sScalar = _mm_set1_pd(scalar);
	__m128d sResult = _mm_div_pd(sV, sScalar);
	vec2d result;
	_mm_store_pd(reinterpret_cast<double*>(&result), sResult);
	return result;
}

vec2d hadamardMul(vec2d a, vec2d b)
{
	__m128d sA = _mm_set_pd(a.y, a.x);
	__m128d sB = _mm_set_pd(b.y, b.x);
	__m128d sResult = _mm_mul_pd(sA, sB);
	vec2d result;
	_mm_store_pd(reinterpret_cast<double*>(&result), sResult);
	return result;
}

vec2d hadamardDiv(vec2d a, vec2d b)
{
	__m128d sA = _mm_set_pd(a.y, a.x);
	__m128d sB = _mm_set_pd(b.y, b.x);
	__m128d sResult = _mm_div_pd(sA, sB);
	vec2d result;
	_mm_store_pd(reinterpret_cast<double*>(&result), sResult);
	return result;
}

double dot(vec2d a, vec2d b)
{
	__m128d sA = _mm_set_pd(a.y, a.x);
	__m128d sB = _mm_set_pd(b.y, b.x);
	__m128d sMulRes = _mm_mul_pd(sA, sB);
	double mulRes[2];
	_mm_store_pd(mulRes, sMulRes);
	double result = mulRes[0] + mulRes[1];
	return result;
}

double length(vec2d v)
{
	__m128d sV = _mm_set_pd(v.y, v.x);
	__m128d sVSquared = _mm_mul_pd(sV, sV);
	double squaredV[2];
	_mm_store_pd(squaredV, sVSquared);
	double result = sqrt(squaredV[0] + squaredV[1]);
	return result;
}

vec2d normalize(vec2d v)
{
	return v / length(v);
}

#endif // ifndef FAST_MATH_NO_SIMD


}

#endif FAST_MATH_IMPLEMENTATION

