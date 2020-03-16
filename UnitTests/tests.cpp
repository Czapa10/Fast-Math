#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define FAST_MATH_IMPLEMENTATION
#include "../FastMath.h"

using namespace fm;

#define floatCmp(x) Approx(x).margin(0.01f)

TEST_CASE("vec2 constructors and swizzling", "[vectors]" ) 
{
	vec2 a(-3.f, 4.5f);
	CHECK((a.x == -3.f && a.y == 4.5f));
 	CHECK((a.u == -3.f && a.v == 4.5f));
 	CHECK((a.width == -3.f && a.height == 4.5f));
 	CHECK((a.left == -3.f && a.top == 4.5f));
 	CHECK((a.elements[0] == -3.f && a.elements[1] == 4.5f));

	vec2 b(1.f);
	CHECK((b.x == 1.f && b.y == 1.f));

	vec2 c;
	CHECK((c.x == 0.f && c.y == 0.f));
}

TEST_CASE("vec2 operations", "[vectors]")
{
	vec2 a(2.f, 4.f);	
	vec2 b(-5.f, 3.f);	

	vec2 addRes = a + b; 
	CHECK(addRes.x == -3.f);
	CHECK(addRes.y == 7.f);

	vec2 subRes = a - b;
	CHECK(subRes.x == 7.f);
	CHECK(subRes.y == 1.f);

	vec2 scalarMulRes1 = a * 4.5f;
	CHECK(scalarMulRes1.x == 9.f);
	CHECK(scalarMulRes1.y == 18.f);

	vec2 scalarMulRes2 = 4.5f * a;
	CHECK(scalarMulRes2.x == 9.f);
	CHECK(scalarMulRes2.y == 18.f);

	vec2 scalarDivRes = a / 2.f;
	CHECK(scalarDivRes.x == 1.f);
	CHECK(scalarDivRes.y == 2.f);

	vec2 hadamardMulRes = hadamardMul(a, b);
	CHECK(hadamardMulRes.x == -10.f);
	CHECK(hadamardMulRes.y == 12.f);
	
	vec2 hadamardDivRes = hadamardDiv(a, b);
	CHECK(hadamardDivRes.x == 2.f / -5.f);
	CHECK(hadamardDivRes.y == 4.f / 3.f);

	float dotProduct = dot(a, b);
	CHECK(dotProduct == 2.f);

	float lengthA = length(a);
	CHECK(lengthA == floatCmp(4.47f));

	vec2 normalizedA = normalize(a);
	CHECK(normalizedA.x == floatCmp(0.44f));
	CHECK(normalizedA.y == floatCmp(0.89f));
}
