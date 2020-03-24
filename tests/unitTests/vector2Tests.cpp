#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

using b32 = int;

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

	float arr[2];
	store(arr, a);
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

	CHECK(a.yx().x() == 4.5f);
	CHECK(a.yx().y() == -3.f);
	CHECK(a.vu().u() == 4.5f);
	CHECK(a.vu().v() == -3.f);

	CHECK(a.xx().x() == -3.f);
	CHECK(a.xx().y() == -3.f);
	CHECK(a.uu().u() == -3.f);
	CHECK(a.uu().v() == -3.f);

	CHECK(a.yy().x() == 4.5f);
	CHECK(a.yy().y() == 4.5f);
	CHECK(a.vv().u() == 4.5f);
	CHECK(a.vv().v() == 4.5f);
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

	INFO("a == (" << a.x() << ", " << a.y() << ")");
	INFO("b == (" << b.x() << ", " << b.y() << ")");

	vec2 addRes = a + b; 
	CHECK(addRes.x() == -3.f);
	CHECK(addRes.y() == 7.f);

	vec2 subRes = a - b;
	CHECK(subRes.x() == 7.f);
	CHECK(subRes.y() == 1.f);

	vec2 addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK(addAsignmentRes.x() == -3.f);
	CHECK(addAsignmentRes.y() == 7.f);

	vec2 subAsignmentRes = a;
	subAsignmentRes -= b;
	CHECK(subAsignmentRes.x() == 7.f);
	CHECK(subAsignmentRes.y() == 1.f);

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

	vec2 negatedB = -b;
	CHECK(negatedB.x() == 5.f);
	CHECK(negatedB.y() == -3.f);

	vec2 minRes = min(a, b);
	CHECK(minRes.x() == -5.f);
	CHECK(minRes.y() == 3.f);

	vec2 maxRes = max(a, b);
	CHECK(maxRes.x() == 2.f);
	CHECK(maxRes.y() == 4.f);

	vec2 absoluteB = abs(b);
	CHECK(absoluteB.x() == 5.f);
	CHECK(absoluteB.y() == 3.f);

	vec2 normalizedB = normalize(b);
	CHECK(normalizedB.x() == floatCmp(b.x() / sqrt(34.f)));
	CHECK(normalizedB.y() == floatCmp(b.y() / sqrt(34.f)));

	CHECK(dot(a, b) == 2.f);
	CHECK(sumOfElements(b) == -2.f);
	CHECK(length(b) == floatCmp(sqrt(34.f)));
	CHECK(lengthSquared(b) == 34.f);

	vec2 min(0.f, 0.f);
	vec2 max(5.f, 2.f);
	vec2 clampBRes = clamp(b, min, max);
	CHECK(clampBRes.x() == 0.f);
	CHECK(clampBRes.y() == 2.f);

	vec2 c(0.f, 0.f);
	vec2 d(2.f, 4.f);
	vec2 lerpRes = lerp(c, d, 0.5f);
	CHECK(lerpRes.x() == 1.f);
	CHECK(lerpRes.y() == 2.f);

	lerpRes = lerp(d, c, 0.5f);
	CHECK(lerpRes.x() == 1.f);
	CHECK(lerpRes.y() == 2.f);
}

TEST_CASE("vec2 comparisons")
{
	vec2 a(5.f, 5.f);
	vec2 b(3.f, 5.f);
	vec2 c(-2.f, 6.f);

	CHECK(a == a);
	CHECK(a != b);

	vec2 eqMask = equalsMask(a, a);
	CHECK((eqMask.x() && eqMask.y()));
	eqMask = equalsMask(a, b);
	CHECK((!eqMask.x() && eqMask.y()));

	vec2 gtMask = greaterMask(a, b);
	CHECK((gtMask.x() && !gtMask.y()));

	vec2 geMask = greaterOrEqualMask(a, b);
	CHECK((geMask.x() && geMask.y()));
	geMask = greaterOrEqualMask(c, a);
	CHECK((!geMask.x() && geMask.y()));

	vec2 ltMask = lesserMask(c, b);
	CHECK((ltMask.x() && !ltMask.y()));

	vec2 leMask = lesserOrEqualMask(b, a);
	CHECK((leMask.x() && leMask.y()));
	leMask = lesserOrEqualMask(c, b);
	CHECK((leMask.x() && !leMask.y()));
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

	CHECK(a.xx().x() == -3.0);
	CHECK(a.xx().y() == -3.0);
	CHECK(a.uu().u() == -3.0);
	CHECK(a.uu().v() == -3.0);

	CHECK(a.yy().x() == 4.0);
	CHECK(a.yy().y() == 4.0);
	CHECK(a.vv().u() == 4.0);
	CHECK(a.vv().v() == 4.0);

	double arr[2];
	store16ByteAligned(arr, a);
	CHECK(arr[0] == -3.0);
	CHECK(arr[1] == 4.0);
	store(arr, a);
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

	INFO("a == (" << a.x() << ", " << a.y() << ")");
	INFO("b == (" << b.x() << ", " << b.y() << ")");

	vec2d addRes = a + b; 
	CHECK(addRes.x() == -3.0);
	CHECK(addRes.y() == 7.0);

	vec2d subRes = a - b;
	CHECK(subRes.x() == 7.0);
	CHECK(subRes.y() == 1.0);

	vec2d addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK(addAsignmentRes.x() == -3.0);
	CHECK(addAsignmentRes.y() == 7.0);

	vec2d subAsignmentRes = a;
	subAsignmentRes -= b;
	CHECK(subAsignmentRes.x() == 7.0);
	CHECK(subAsignmentRes.y() == 1.0);

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

	vec2d negatedB = -b;
	CHECK(negatedB.x() == 5.0);
	CHECK(negatedB.y() == -3.0);

	vec2d minRes = min(a, b);
	CHECK(minRes.x() == -5.0);
	CHECK(minRes.y() == 3.0);

	vec2d maxRes = max(a, b);
	CHECK(maxRes.x() == 2.0);
	CHECK(maxRes.y() == 4.0);

	vec2d absoluteB = abs(b);
	CHECK(absoluteB.x() == 5);
	CHECK(absoluteB.y() == 3);

	vec2d normalizedB = normalize(b);
	CHECK(normalizedB.x() == floatCmp(b.x() / sqrt(34)));
	CHECK(normalizedB.y() == floatCmp(b.y() / sqrt(34)));

	CHECK(dot(a, b) == 2.0);
	CHECK(sumOfElements(b) == -2.0);
	CHECK(length(b) == floatCmp(sqrt(34.0)));
	CHECK(lengthSquared(b) == 34.0);

	vec2d min(0.0, 0.0);
	vec2d max(5.0, 7.0);
	vec2d clampRes = clamp(vec2d(-1.0, 8.0), min, max);
	CHECK(clampRes.x() == 0.0);
	CHECK(clampRes.y() == 7.0);

	vec2d c(0.0, 0.0);
	vec2d d(2.0, 4.0);
	vec2d lerpRes = lerp(c, d, 0.5f);
	CHECK(lerpRes.x() == 1.0);
	CHECK(lerpRes.y() == 2.0);

	lerpRes = lerp(d, c, 0.5);
	CHECK(lerpRes.x() == 1.0);
	CHECK(lerpRes.y() == 2.0);
}

TEST_CASE("vec2d comparisons")
{
	vec2d a(5.0, 5.0);
	vec2d b(3.0, 5.0);
	vec2d c(-2.0, 6.0);

	CHECK(a == a);
	CHECK(a != b);

	vec2d eqMask = equalsMask(a, a);
	CHECK((eqMask.x() && eqMask.y()));
	eqMask = equalsMask(a, b);
	CHECK((!eqMask.x() && eqMask.y()));

	vec2d gtMask = greaterMask(a, b);
	CHECK((gtMask.x() && !gtMask.y()));

	vec2d geMask = greaterOrEqualMask(a, b);
	CHECK((geMask.x() && geMask.y()));
	geMask = greaterOrEqualMask(c, a);
	CHECK((!geMask.x() && geMask.y()));

	vec2d ltMask = lesserMask(c, b);
	CHECK((ltMask.x() && !ltMask.y()));

	vec2d leMask = lesserOrEqualMask(b, a);
	CHECK((leMask.x() && leMask.y()));
	leMask = lesserOrEqualMask(c, b);
	CHECK((leMask.x() && !leMask.y()));
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

	CHECK(a.xx().x() == -3);
	CHECK(a.xx().y() == -3);
	CHECK(a.uu().u() == -3);
	CHECK(a.uu().v() == -3);

	CHECK(a.yy().x() == 4);
	CHECK(a.yy().y() == 4);
	CHECK(a.vv().u() == 4);
	CHECK(a.vv().v() == 4);

	int arr[2];
	store(arr, a);
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

	INFO("a == (" << a.x() << ", " << a.y() << ")");
	INFO("b == (" << b.x() << ", " << b.y() << ")");
	
	vec2i addRes = a + b;
	CHECK(addRes.x() == -3);
	CHECK(addRes.y() == 7);
	
	vec2i subRes = a - b;
	CHECK(subRes.x() == 7);
	CHECK(subRes.y() == 1);

	vec2i addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK(addAsignmentRes.x() == -3);
	CHECK(addAsignmentRes.y() == 7);

	vec2i subAsignmentRes = a;
	subAsignmentRes -= b;
	CHECK(subAsignmentRes.x() == 7);
	CHECK(subAsignmentRes.y() == 1);
	
	vec2i scalarMulRes1 = a * -5;
	CHECK(scalarMulRes1.x() == -10);
	CHECK(scalarMulRes1.y() == -20);
	
	vec2i scalarMulRes2 = -5 * a;
	CHECK(scalarMulRes1.x() == -10);
	CHECK(scalarMulRes1.y() == -20);
	
	vec2i hadamardMulRes = hadamardMul(a, b); 
	CHECK(hadamardMulRes.x() == -10);
	CHECK(hadamardMulRes.y() == 12);

	vec2i negatedB = -b;
	CHECK(negatedB.x() == 5);
	CHECK(negatedB.y() == -3);

	vec2i minRes = min(a, b);
	CHECK(minRes.x() == -5);
	CHECK(minRes.y() == 3);

	vec2i maxRes = max(a, b);
	CHECK(maxRes.x() == 2);
	CHECK(maxRes.y() == 4);

	vec2i absoluteB = abs(b);
	CHECK(absoluteB.x() == 5);
	CHECK(absoluteB.y() == 3);

	CHECK(sumOfElements(b) == -2);
	CHECK(length(b) == (int)sqrt(34));
	CHECK(lengthSquared(b) == 34);

	vec2i min(0, 0);
	vec2i max(5, 2);
	vec2i clampBRes = clamp(b, min, max);
	CHECK(clampBRes.x() == 0);
	CHECK(clampBRes.y() == 2);
}

TEST_CASE("vec2i comparisons")
{
	vec2i a(5, 5);
	vec2i b(3, 5);
	vec2i c(-2, 6);

	CHECK(a == a);
	CHECK(a != b);

	vec2i eqMask = equalsMask(a, a);
	CHECK((eqMask.x() && eqMask.y()));
	eqMask = equalsMask(a, b);
	CHECK((!eqMask.x() && eqMask.y()));

	vec2i gtMask = greaterMask(a, b);
	CHECK((gtMask.x() && !gtMask.y()));

	vec2i geMask = greaterOrEqualMask(a, b);
	CHECK((geMask.x() && geMask.y()));
	geMask = greaterOrEqualMask(c, a);
	CHECK((!geMask.x() && geMask.y()));

	vec2i ltMask = lesserMask(c, b);
	CHECK(ltMask.x());
	CHECK(!ltMask.y());

	vec2i leMask = lesserOrEqualMask(b, a);
	CHECK((leMask.x() && leMask.y()));
	leMask = lesserOrEqualMask(c, b);
	CHECK((leMask.x() && !leMask.y()));
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

	CHECK(a.xx().x() == 3);
	CHECK(a.xx().y() == 3);
	CHECK(a.uu().u() == 3);
	CHECK(a.uu().v() == 3);

	CHECK(a.yy().x() == 4);
	CHECK(a.yy().y() == 4);
	CHECK(a.vv().u() == 4);
	CHECK(a.vv().v() == 4);

	vec2u b(1);
	CHECK(b.x() == 1);
	CHECK(b.y() == 1);

	unsigned arr[2];
	store(arr, a);
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

	vec2u addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK(addAsignmentRes.x() == 6);
	CHECK(addAsignmentRes.y() == 7);

	vec2u subAsignmentRes = a;
	subAsignmentRes -= b;
	CHECK(subAsignmentRes.x() == 4);
	CHECK(subAsignmentRes.y() == 1);
	
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

	CHECK(sumOfElements(b) == 4);
	CHECK(length(b) == (unsigned)sqrt(10));
	CHECK(lengthSquared(b) == 10);

	vec2u min(2, 0);
	vec2u max(5, 3);
	vec2u clampBRes = clamp(b, min, max);
	CHECK(clampBRes.x() == 2);
	CHECK(clampBRes.y() == 3);
}

TEST_CASE("vec2u comparisons")
{
	vec2u a(5, 5);
	vec2u b(3, 5);
	vec2u c(-2, 6);

	CHECK(a == a);
	CHECK(a != b);

	vec2u eqMask = equalsMask(a, a);
	CHECK((eqMask.x() && eqMask.y()));
	eqMask = equalsMask(a, b);
	CHECK((!eqMask.x() && eqMask.y()));

	vec2u gtMask = greaterMask(a, b);
	CHECK((gtMask.x() && !gtMask.y()));

	vec2u geMask = greaterOrEqualMask(a, b);
	CHECK((geMask.x() && geMask.y()));
	geMask = greaterOrEqualMask(c, a);
	CHECK((!geMask.x() && geMask.y()));

	vec2u ltMask = lesserMask(c, b);
	CHECK(ltMask.x());
	CHECK(!ltMask.y());

	vec2u leMask = lesserOrEqualMask(b, a);
	CHECK((leMask.x() && leMask.y()));
	leMask = lesserOrEqualMask(c, b);
	CHECK((leMask.x() && !leMask.y()));
}


