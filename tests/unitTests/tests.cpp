#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS 
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FAST_MATH_IMPLEMENTATION
#include "../../FastMath.h"

using namespace fm;

#define floatCmp(x) doctest::Approx(x).epsilon(0.01)

TEST_CASE("min max functions")
{
	CHECK(5.f == min(5.f, 10.f));
	CHECK(5.f == max(5.f, -1.f));
	CHECK(5.0 == min(5.0, 10.0));
	CHECK(5.0 == max(5.0, -1.0));
	CHECK(5 == min(5, 10));
	CHECK(5 == max(5, -1));
	CHECK(5u == min(5u, 10u));
	CHECK(5u == max(5u, 0u));
}

TEST_CASE("vec2 constructors and getters") 
{
	vec2 a(-3.f, 4.5f);

	CHECK(a.x() == -3.f);
 	CHECK(a.u() == -3.f);
 	CHECK(a.left() == -3.f);
 	CHECK(a.width() == -3.f);

	CHECK(a.y() == 4.5f);
	CHECK(a.v() == 4.5f);
	CHECK(a.top() == 4.5f);
	CHECK(a.height() == 4.5f);

	CHECK(a.yx().x() == 4.5f);
	CHECK(a.yx().y() == -3.f);
	CHECK(a.vu().u() == 4.5f);
	CHECK(a.vu().v() == -3.f);

	float arr[2];
	a.storeTo(arr);
	CHECK(arr[0] == -3.f);
	CHECK(arr[1] == 4.5f);

	vec2 b(1.f);
	CHECK(b.x() == 1.f);
	CHECK(b.y() == 1.f);

	vec2 c;
	CHECK(c.x() == 0.f);
	CHECK(c.y() == 0.f);

	float initArr[] = {-1.f, 2.f};	
	vec2 d(initArr);
	CHECK(d.x() == -1.f);
	CHECK(d.y() == 2.f);
}

TEST_CASE("vec2 setters")
{
	vec2 a;
	a.setX(4.f);
	a.setY(-2.5f);
	CHECK(a.x() == 4.f);
	CHECK(a.y() == -2.5f);

	vec2 b;
	b.setY(-2.5f);
	b.setX(4.f);
	CHECK(a.x() == 4.f);
	CHECK(a.y() == -2.5f);
}

TEST_CASE("vec2 operations")
{
	vec2 a(2.f, 4.f);	
	vec2 b(-5.f, 3.f);	

	vec2 addRes = a + b; 
	CHECK(addRes.x() == -3.f);
	CHECK(addRes.y() == 7.f);

	vec2 subRes = a - b;
	CHECK(subRes.x() == 7.f);
	CHECK(subRes.y() == 1.f);

	vec2 scalarMulRes1 = a * 4.5f;
	CHECK(scalarMulRes1.x() == 9.f);
	CHECK(scalarMulRes1.y() == 18.f);

	vec2 scalarMulRes2 = 4.5f * a;
	CHECK(scalarMulRes2.x() == 9.f);
	CHECK(scalarMulRes2.y() == 18.f);

	vec2 scalarDivRes = a / 2.f;
	CHECK(scalarDivRes.x() == 1.f);
	CHECK(scalarDivRes.y() == 2.f);

	vec2 hadamardMulRes = hadamardMul(a, b);
	CHECK(hadamardMulRes.x() == -10.f);
	CHECK(hadamardMulRes.y() == 12.f);
	
	vec2 hadamardDivRes = hadamardDiv(a, b);
	CHECK(hadamardDivRes.x() == 2.f / -5.f);
	CHECK(hadamardDivRes.y() == 4.f / 3.f);

	vec2 minRes = min(a, b);
	CHECK(minRes.x() == -5.f);
	CHECK(minRes.y() == 3.f);

	vec2 maxRes = max(a, b);
	CHECK(maxRes.x() == 2.f);
	CHECK(maxRes.y() == 4.f);
}


TEST_CASE("vec2d constructors and getters") 
{
	vec2d a(-3.0, 4.0);

	CHECK(a.x() == -3.0);
	CHECK(a.u() == -3.0);
	CHECK(a.left() == -3.0);
	CHECK(a.width() == -3.0);

	CHECK(a.y() == 4.0);
	CHECK(a.v() == 4.0);
	CHECK(a.top() == 4.0);
	CHECK(a.height() == 4.0);

	CHECK(a.yx().x() == 4.0);
	CHECK(a.yx().y() == -3.0);
	CHECK(a.vu().u() == 4.0);
	CHECK(a.vu().v() == -3.0);

	double arr[2];
	a.storeTo16ByteAligned(arr);
	CHECK(arr[0] == -3.0);
	CHECK(arr[1] == 4.0);
	a.storeTo(arr);
	CHECK(arr[0] == -3.0);
	CHECK(arr[1] == 4.0);

	vec2d b(1.0);
	CHECK(b.x() == 1.0); 
	CHECK(b.y() == 1.0); 

	vec2d c;
	CHECK(c.x() == 0.0);
	CHECK(c.y() == 0.0);

	double initArr[] = {-1.0, 2.0};	
	vec2d d(initArr);
	CHECK(d.x() == -1.0);
	CHECK(d.y() == 2.0);
}

TEST_CASE("vec2d setters")
{
	vec2d a;
	a.setX(4.0);
	a.setY(-2.5);
	CHECK(a.x() == 4.0);
	CHECK(a.y() == -2.5);

	vec2d b;
	b.setY(-2.5);
	b.setX(4.0);
	CHECK(a.x() == 4.0);
	CHECK(a.y() == -2.5);
}


TEST_CASE("vec2d operations")
{
	vec2d a(2.0, 4.0);	
	vec2d b(-5.0, 3.0);	

	vec2d addRes = a + b; 
	CHECK(addRes.x() == -3.0);
	CHECK(addRes.y() == 7.0);

	vec2d subRes = a - b;
	CHECK(subRes.x() == 7.0);
	CHECK(subRes.y() == 1.0);

	vec2d scalarMulRes1 = a * 4.5;
	CHECK(scalarMulRes1.x() == 9.0);
	CHECK(scalarMulRes1.y() == 18.0);

	vec2d scalarMulRes2 = 4.5 * a;
	CHECK(scalarMulRes2.x() == 9.0);
	CHECK(scalarMulRes2.y() == 18.0);

	vec2d scalarDivRes = a / 2.0;
	CHECK(scalarDivRes.x() == 1.0);
	CHECK(scalarDivRes.y() == 2.0);

	vec2d hadamardMulRes = hadamardMul(a, b);
	CHECK(hadamardMulRes.x() == -10.0);
	CHECK(hadamardMulRes.y() == 12.0);
	
	vec2d hadamardDivRes = hadamardDiv(a, b);
	CHECK(hadamardDivRes.x() == floatCmp(2.0 / -5.0));
	CHECK(hadamardDivRes.y() == floatCmp(4.0 / 3.0));

	vec2d minRes = min(a, b);
	CHECK(minRes.x() == -5.0);
	CHECK(minRes.y() == 3.0);

	vec2d maxRes = max(a, b);
	CHECK(maxRes.x() == 2.0);
	CHECK(maxRes.y() == 4.0);
}

TEST_CASE("vec2i constructors and getters") 
{
	vec2i a(-3, 4);

	CHECK(a.x() == -3);
 	CHECK(a.u() == -3);
 	CHECK(a.left() == -3);
 	CHECK(a.width() == -3);

	CHECK(a.y() == 4);
	CHECK(a.v() == 4);
	CHECK(a.height() == 4);
	CHECK(a.top() == 4);

	CHECK(a.yx().x() == 4);
	CHECK(a.yx().y() == -3);
	CHECK(a.vu().u() == 4);
	CHECK(a.vu().v() == -3);

	int arr[2];
	a.storeTo(arr);
	CHECK(arr[0] == -3);
	CHECK(arr[1] == 4);

	vec2i b(1);
	CHECK(b.x() == 1);
	CHECK(b.y() == 1);

	vec2i c;
	CHECK(c.x() == 0);
	CHECK(c.y() == 0);

	int initArr[] = {-1, 2};	
	vec2i d(initArr);
	CHECK(d.x() == -1);
	CHECK(d.y() == 2);
}

TEST_CASE("vec2i setters")
{
	vec2i a;
	a.setX(4);
	a.setY(-2);
	CHECK(a.x() == 4);
	CHECK(a.y() == -2);

	vec2d b;
	b.setY(-2);
	b.setX(4);
	CHECK(a.x() == 4);
	CHECK(a.y() == -2);
}

TEST_CASE("vec2i operations")
{
	vec2i a(2, 4);
	vec2i b(-5, 3);
	
	vec2i addRes = a + b;
	CHECK(addRes.x() == -3);
	CHECK(addRes.y() == 7);
	
	vec2i subRes = a - b;
	CHECK(subRes.x() == 7);
	CHECK(subRes.y() == 1);
	
	vec2i scalarMulRes1 = a * -5;
	CHECK(scalarMulRes1.x() == -10);
	CHECK(scalarMulRes1.y() == -20);
	
	vec2i scalarMulRes2 = -5 * a;
	CHECK(scalarMulRes1.x() == -10);
	CHECK(scalarMulRes1.y() == -20);
	
	vec2i hadamardMulRes = hadamardMul(a, b); 
	CHECK(hadamardMulRes.x() == -10);
	CHECK(hadamardMulRes.y() == 12);

	vec2i minRes = min(a, b);
	CHECK(minRes.x() == -5);
	CHECK(minRes.y() == 3);

	vec2i maxRes = max(a, b);
	CHECK(maxRes.x() == 2);
	CHECK(maxRes.y() == 4);
}

TEST_CASE("vec2u constructors and getters") 
{
	vec2u a(3, 4);
	CHECK(a.x() == 3);
 	CHECK(a.u() == 3);
 	CHECK(a.left() == 3);
 	CHECK(a.width() == 3);

	CHECK(a.y() == 4);
	CHECK(a.v() == 4);
	CHECK(a.top() == 4);
	CHECK(a.height() == 4);

	CHECK(a.yx().x() == 4);
	CHECK(a.yx().y() == 3);
	CHECK(a.vu().u() == 4);
	CHECK(a.vu().v() == 3);

	vec2u b(1);
	CHECK(b.x() == 1);
	CHECK(b.y() == 1);

	unsigned arr[2];
	a.storeTo(arr);
	CHECK(arr[0] == 3);
	CHECK(arr[1] == 4);

	vec2u c(-2, 3);
	CHECK(c.x() == -2);
	CHECK(c.y() == 3);

	vec2u d;
	CHECK(d.x() == 0);
	CHECK(d.y() == 0);

	unsigned initArr[] = {1, 2};	
	vec2u e(initArr);
	CHECK(e.x() == 1);
	CHECK(e.y() == 2);
}

TEST_CASE("vec2u setters")
{
	vec2u a;
	a.setX(4);
	a.setY(2);
	CHECK(a.x() == 4);
	CHECK(a.y() == 2);

	vec2u b;
	b.setY(2);
	b.setX(4);
	CHECK(a.x() == 4);
	CHECK(a.y() == 2);
}

TEST_CASE("vec2u operations")
{
	vec2u a(5, 4);
	vec2u b(1, 3);

	INFO("a == (" << a.x() << ", " << a.y() << ")");
	INFO("b == (" << b.x() << ", " << b.y() << ")");
	
	vec2u addRes = a + b;
	CHECK(addRes.x() == 6);
	CHECK(addRes.y() == 7);
	
	vec2u subRes = a - b;
	CHECK(subRes.x() == 4);
	CHECK(subRes.y() == 1);
	
	vec2u scalarMulRes1 = a * 5;
	CHECK(scalarMulRes1.x() == 25);
	CHECK(scalarMulRes1.y() == 20);
	
	vec2u scalarMulRes2 = 5 * a;
	CHECK(scalarMulRes1.x() == 25);
	CHECK(scalarMulRes1.y() == 20);
	
	vec2u hadamardMulRes = hadamardMul(a, b); 
	CHECK(hadamardMulRes.x() == 5);
	CHECK(hadamardMulRes.y() == 12);

	vec2u minRes = min(a, b);
	CHECK(minRes.x() == 1);
	CHECK(minRes.y() == 3);

	vec2u maxRes = max(a, b);
	CHECK(maxRes.x() == 5);
	CHECK(maxRes.y() == 4);
}

