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
vec2d operator/(vec2d v, double scalar);
vec2d hadamardMul(vec2d a, vec2d b);
vec2d hadamardDiv(vec2d a, vec2d b);
double dot(vec2d a, vec2d b);
double lenght(vec2d v);
vec2d normalize(vec2d v);

}

#endif // FAST_MATH_H


#ifdef FAST_MATH_IMPLEMENTATION

#include <math.h>

namespace fm {

//////////////////////
// vec2 functions ////
//////////////////////
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

///////////////////////
// vec2d functions ////
///////////////////////
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



}

#endif FAST_MATH_IMPLEMENTATION

