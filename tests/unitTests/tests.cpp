#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#define CATCH_CONFIG_DISABLE_MATCHERS 
#include "catch.hpp"

#define FAST_MATH_IMPLEMENTATION
#include "../../FastMath.h"

using namespace fm;

#define floatCmp(x) Approx(x).margin(0.01)

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


TEST_CASE("vec2d constructors and swizzling", "[vectors]" ) 
{
	vec2d a(-3.0, 4.0);
	CHECK((a.x == -3.0 && a.y == 4.0));
 	CHECK((a.u == -3.0 && a.v == 4.0));
 	CHECK((a.width == -3.0 && a.height == 4.0));
 	CHECK((a.left == -3.0 && a.top == 4.0));
 	CHECK((a.elements[0] == -3.0 && a.elements[1] == 4.0));

	vec2d b(1.0);
	CHECK((b.x == 1.0 && b.y == 1.0));

	vec2d c;
	CHECK((c.x == 0.0 && c.y == 0.0));
}

TEST_CASE("vec2d operations", "[vectors]")
{
	vec2d a(2.0, 4.0);	
	vec2d b(-5.0, 3.0);	

	vec2d addRes = a + b; 
	CHECK(addRes.x == -3.0);
	CHECK(addRes.y == 7.0);

	vec2d subRes = a - b;
	CHECK(subRes.x == 7.0);
	CHECK(subRes.y == 1.0);

	vec2d scalarMulRes1 = a * 4.5;
	CHECK(scalarMulRes1.x == 9.0);
	CHECK(scalarMulRes1.y == 18.0);

	vec2d scalarMulRes2 = 4.5 * a;
	CHECK(scalarMulRes2.x == 9.0);
	CHECK(scalarMulRes2.y == 18.0);

	vec2d scalarDivRes = a / 2.0;
	CHECK(scalarDivRes.x == 1.0);
	CHECK(scalarDivRes.y == 2.0);

	vec2d hadamardMulRes = hadamardMul(a, b);
	CHECK(hadamardMulRes.x == -10.0);
	CHECK(hadamardMulRes.y == 12.0);
	
	vec2d hadamardDivRes = hadamardDiv(a, b);
	CHECK(hadamardDivRes.x == floatCmp(2.0 / -5.0));
	CHECK(hadamardDivRes.y == floatCmp(4.0 / 3.0));

	double dotProduct = dot(a, b);
	CHECK(dotProduct == 2.0);

	double lengthA = length(a);
	CHECK(lengthA == floatCmp(4.47));

	vec2d normalizedA = normalize(a);
	CHECK(normalizedA.x == floatCmp(0.44));
	CHECK(normalizedA.y == floatCmp(0.89));
}

TEST_CASE("vec2i constructors and swizzling", "[vectors]" ) 
{
	vec2i a(-3, 4);
	CHECK((a.x == -3 && a.y == 4));
 	CHECK((a.u == -3 && a.v == 4));
 	CHECK((a.width == -3 && a.height == 4));
 	CHECK((a.left == -3 && a.top == 4));
 	CHECK((a.elements[0] == -3 && a.elements[1] == 4));

	vec2i b(1);
	CHECK((b.x == 1 && b.y == 1));

	vec2i c;
	CHECK((c.x == 0 && c.y == 0));
}

TEST_CASE("vec2i operations", "[vectors]")
{
	vec2i a(2, 4);
	vec2i b(-5, 3);
	
	vec2i addRes = a + b;
	CHECK(addRes.x == -3);
	CHECK(addRes.y == 7);
	
	vec2i subRes = a - b;
	CHECK(subRes.x == 7);
	CHECK(subRes.y == 1);
	
	vec2i scalarMulRes1 = a * -5;
	CHECK(scalarMulRes1.x == -10);
	CHECK(scalarMulRes1.y == -20);
	
	vec2i scalarMulRes2 = -5 * a;
	CHECK(scalarMulRes1.x == -10);
	CHECK(scalarMulRes1.y == -20);
	
	vec2i hadamardMulRes = hadamardMul(a, b); 
	CHECK(hadamardMulRes.x == -10);
	CHECK(hadamardMulRes.y == 12);

	vec2i hadamardDivRes = hadamardDiv(a, b); 
	CHECK(hadamardDivRes.x == 0);
	CHECK(hadamardDivRes.y == 1);
}

TEST_CASE("vec2u constructors and swizzling", "[vectors]" ) 
{
	vec2u a(3, 4);
	CHECK((a.x == 3 && a.y == 4));
 	CHECK((a.u == 3 && a.v == 4));
 	CHECK((a.width == 3 && a.height == 4));
 	CHECK((a.left == 3 && a.top == 4));
 	CHECK((a.elements[0] == 3 && a.elements[1] == 4));

	vec2u b(1);
	CHECK((b.x == 1 && b.y == 1));

	vec2u c;
	CHECK((c.x == 0 && c.y == 0));
}

TEST_CASE("vec2u operations", "[vectors]")
{
	vec2u a(5, 4);
	vec2u b(1, 3);
	
	vec2u addRes = a + b;
	CHECK(addRes.x == 6);
	CHECK(addRes.y == 7);
	
	vec2u subRes = a - b;
	CHECK(subRes.x == 4);
	CHECK(subRes.y == 1);
	
	vec2u scalarMulRes1 = a * 5;
	CHECK(scalarMulRes1.x == 25);
	CHECK(scalarMulRes1.y == 20);
	
	vec2u scalarMulRes2 = 5 * a;
	CHECK(scalarMulRes1.x == 25);
	CHECK(scalarMulRes1.y == 20);
	
	vec2u hadamardMulRes = hadamardMul(a, b); 
	CHECK(hadamardMulRes.x == 5);
	CHECK(hadamardMulRes.y == 12);

	vec2u hadamardDivRes = hadamardDiv(a, b); 
	CHECK(hadamardDivRes.x == 5);
	CHECK(hadamardDivRes.y == 1);
}

