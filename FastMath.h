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

}

#endif // FAST_MATH_H


#ifdef FAST_MATH_IMPLEMENTATION

#include <math.h>

namespace fm {

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

}

#endif FAST_MATH_IMPLEMENTATION

