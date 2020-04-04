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
	vec2 a = makeVec2(-3.f, 4.5f);
	CHECK_VECTOR2_ALL_ALIASES(a, -3.f, 4.5f);

	float arr[2];
	store(arr, a);
	CHECK_VECTOR2_ARRAY(arr, -3.f, 4.5f);

	vec2 b = makeVec2(1.f);
	CHECK_VECTOR2(b, 1.f, 1.f);

	vec2 c = makeZeroVec2();
	CHECK_VECTOR2(c, 0.f, 0.f);

	float initArr[] = {-1.f, 2.f};	
	vec2 d = makeVec2FromMemory(initArr);
	CHECK_VECTOR2(d, -1.f, 2.f);

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
	CHECK_VECTOR2(a, 4.f, -2.5f);

	vec2 b;
	b.setY(-2.5f);
	b.setX(4.f);
	CHECK_VECTOR2(b, 4.f, -2.5f);
}

TEST_CASE("vec2 operations")
{
	vec2 a = makeVec2(2.f, 4.f);	
	vec2 b = makeVec2(-5.f, 3.f);	

	LOG_VECTOR2(a);
	LOG_VECTOR2(b);

	vec2 addRes = a + b; 
	CHECK_VECTOR2(addRes, -3.f, 7.f);

	vec2 subRes = a - b;
	CHECK_VECTOR2(subRes, 7.f, 1.f);

	vec2 addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK_VECTOR2(addAsignmentRes, -3.f, 7.f);

	vec2 subAsignmentRes = a;
	subAsignmentRes -= b;
	CHECK_VECTOR2(subAsignmentRes, 7.f, 1.f);

	vec2 scalarMulRes1 = a * 4.5f;
	CHECK_VECTOR2(scalarMulRes1, 9.f, 18.f);

	vec2 scalarMulRes2 = 4.5f * a;
	CHECK_VECTOR2(scalarMulRes2, 9.f, 18.f);

	vec2 scalarDivRes = a / 2.f;
	CHECK_VECTOR2(scalarDivRes, 1.f, 2.f);

	vec2 hadamardMulRes = hadamardMul(a, b);
	CHECK_VECTOR2(hadamardMulRes, -10.f, 12.f);
	
	vec2 hadamardDivRes = hadamardDiv(a, b);
	CHECK_VECTOR2(hadamardDivRes, 2.f / -5.f, 4.f / 3.f);

	vec2 negatedB = -b;
	CHECK_VECTOR2(negatedB, 5.f, -3.f); 

	vec2 minRes = min(a, b);
	CHECK_VECTOR2(minRes, -5.f, 3.f); 

	vec2 maxRes = max(a, b);
	CHECK_VECTOR2(maxRes, 2.f, 4.f); 

	vec2 absoluteB = abs(b);
	CHECK_VECTOR2(absoluteB, 5.f, 3.f); 

	vec2 normalizedB = normalize(b);
	CHECK_VECTOR2_APPROX(normalizedB, b.x() / sqrt(34.f), b.y() / sqrt(34.f)); 

	CHECK(dot(a, b) == 2.f);
	CHECK(sumOfElements(b) == -2.f);
	CHECK(length(b) == floatCmp(sqrt(34.f)));
	CHECK(lengthSquared(b) == 34.f);

	vec2 min = makeVec2(0.f, 0.f);
	vec2 max = makeVec2(5.f, 2.f);
	vec2 clampBRes = clamp(b, min, max);
	CHECK_VECTOR2(clampBRes, 0.f, 2.f);

	vec2 c = makeVec2(0.f, 0.f);
	vec2 d = makeVec2(2.f, 4.f);
	vec2 lerpRes = lerp(c, d, 0.5f);
	CHECK_VECTOR2(lerpRes, 1.f, 2.f);

	lerpRes = lerp(d, c, 0.5f);
	CHECK_VECTOR2(lerpRes, 1.f, 2.f);
}

TEST_CASE("vec2 comparisons")
{
	vec2 a = makeVec2(5.f, 5.f);
	vec2 b = makeVec2(3.f, 5.f);
	vec2 c = makeVec2(-2.f, 6.f);

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
	vec2d a = makeVec2d(-3.0, 4.0);

	CHECK_VECTOR2_ALL_ALIASES(a, -3.0, 4.0);

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
	CHECK_VECTOR2_ARRAY(arr, -3.0, 4.0);
	store(arr, a);
	CHECK_VECTOR2_ARRAY(arr, -3.0, 4.0);

	vec2d b = makeVec2d(1.0);
	CHECK_VECTOR2(b, 1.0, 1.0);

	vec2d c = makeZeroVec2d();
	CHECK_VECTOR2(c, 0.0, 0.0);

	double initArr[] = {-1.0, 2.0};	
	vec2d d = makeVec2dFromMemory(initArr);
	CHECK_VECTOR2(d, -1.0, 2.0);
}

TEST_CASE("vec2d setters")
{
	vec2d a;
	a.setX(4.0);
	a.setY(-2.5);
	CHECK_VECTOR2(a, 4.0, -2.5);

	vec2d b;
	b.setY(-2.5);
	b.setX(4.0);
	CHECK_VECTOR2(b, 4.0, -2.5);
}

TEST_CASE("vec2d operations")
{
	vec2d a = makeVec2d(2.0, 4.0);	
	vec2d b = makeVec2d(-5.0, 3.0);	

	INFO("a == (" << a.x() << ", " << a.y() << ")");
	INFO("b == (" << b.x() << ", " << b.y() << ")");

	vec2d addRes = a + b; 
	CHECK_VECTOR2(addRes, -3.0, 7.0);

	vec2d subRes = a - b;
	CHECK_VECTOR2(subRes, 7.0, 1.0);

	vec2d addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK_VECTOR2(addAsignmentRes, -3.0, 7.0);

	vec2d subAsignmentRes = a;
	subAsignmentRes -= b;
	CHECK_VECTOR2(subAsignmentRes, 7.0, 1.0);

	vec2d scalarMulRes1 = a * 4.5;
	CHECK_VECTOR2(scalarMulRes1, 9.0, 18.0);

	vec2d scalarMulRes2 = 4.5 * a;
	CHECK_VECTOR2(scalarMulRes2, 9.0, 18.0);

	vec2d scalarDivRes = a / 2.0;
	CHECK_VECTOR2(scalarDivRes, 1.0, 2.0);

	vec2d hadamardMulRes = hadamardMul(a, b);
	CHECK_VECTOR2(hadamardMulRes, -10.0, 12.0);
	
	vec2d hadamardDivRes = hadamardDiv(a, b);
	CHECK_VECTOR2_APPROX(hadamardDivRes, 2.0 / -5.0, 4.0 / 3.0);

	vec2d negatedB = -b;
	CHECK_VECTOR2(negatedB, 5.0, -3.0);

	vec2d minRes = min(a, b);
	CHECK_VECTOR2(minRes, -5.0, 3.0);

	vec2d maxRes = max(a, b);
	CHECK_VECTOR2(maxRes, 2.0, 4.0);

	vec2d absoluteB = abs(b);
	CHECK_VECTOR2(absoluteB, 5.0, 3.0);

	vec2d normalizedB = normalize(b);
	CHECK_VECTOR2_APPROX(normalizedB, b.x() / sqrt(34), b.y() / sqrt(34));

	CHECK(dot(a, b) == 2.0);
	CHECK(sumOfElements(b) == -2.0);
	CHECK(length(b) == floatCmp(sqrt(34.0)));
	CHECK(lengthSquared(b) == 34.0);

	vec2d min = makeVec2d(0.0, 0.0);
	vec2d max = makeVec2d(5.0, 7.0);
	vec2d clampRes = clamp(makeVec2d(-1.0, 8.0), min, max);
	CHECK_VECTOR2(clampRes, 0.0, 7.0);

	vec2d c = makeVec2d(0.0, 0.0);
	vec2d d = makeVec2d(2.0, 4.0);
	vec2d lerpRes = lerp(c, d, 0.5f);
	CHECK_VECTOR2(lerpRes, 1.0, 2.0);
	lerpRes = lerp(d, c, 0.5);
	CHECK_VECTOR2(lerpRes, 1.0, 2.0);
}

TEST_CASE("vec2d comparisons")
{
	vec2d a = makeVec2d(5.0, 5.0);
	vec2d b = makeVec2d(3.0, 5.0);
	vec2d c = makeVec2d(-2.0, 6.0);

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
	vec2i a = makeVec2i(-3, 4);

	CHECK_VECTOR2_ALL_ALIASES(a, -3, 4);

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
	CHECK_VECTOR2_ARRAY(arr, -3, 4);

	vec2i b = makeVec2i(1);
	CHECK_VECTOR2(b, 1, 1);

	vec2i c = makeZeroVec2i();
	CHECK_VECTOR2(c, 0, 0);

	int initArr[] = {-1, 2};	
	vec2i d = makeVec2iFromMemory(initArr);
	CHECK_VECTOR2(d, -1, 2);
}

TEST_CASE("vec2i setters")
{
	vec2i a;
	a.setX(4);
	a.setY(-2);
	CHECK_VECTOR2(a, 4, -2);

	vec2d b;
	b.setY(-2);
	b.setX(4);
	CHECK_VECTOR2(a, 4, -2);
}

TEST_CASE("vec2i operations")
{
	vec2i a = makeVec2i(2, 4);
	vec2i b = makeVec2i(-5, 3);

	LOG_VECTOR2(a);
	LOG_VECTOR2(b);
	
	vec2i addRes = a + b;
	CHECK_VECTOR2(addRes, -3, 7);
	
	vec2i subRes = a - b;
	CHECK_VECTOR2(subRes, 7, 1);

	vec2i addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK_VECTOR2(addAsignmentRes, -3, 7);

	vec2i subAsignmentRes = a;
	subAsignmentRes -= b;
	CHECK_VECTOR2(subAsignmentRes, 7, 1);
	
	vec2i scalarMulRes1 = a * -5;
	CHECK_VECTOR2(scalarMulRes1, -10, -20);
	
	vec2i scalarMulRes2 = -5 * a;
	CHECK_VECTOR2(scalarMulRes2, -10, -20);
	
	vec2i hadamardMulRes = hadamardMul(a, b); 
	CHECK_VECTOR2(hadamardMulRes, -10, 12);

	vec2i negatedB = -b;
	CHECK_VECTOR2(negatedB, 5, -3);

	vec2i minRes = min(a, b);
	CHECK_VECTOR2(minRes, -5, 3);

	vec2i maxRes = max(a, b);
	CHECK_VECTOR2(maxRes, 2, 4);

	vec2i absoluteB = abs(b);
	CHECK_VECTOR2(absoluteB, 5, 3);

	CHECK(sumOfElements(b) == -2);
	CHECK(length(b) == (int)sqrt(34));
	CHECK(lengthSquared(b) == 34);

	vec2i min = makeVec2i(0, 0);
	vec2i max = makeVec2i(5, 2);
	vec2i clampBRes = clamp(b, min, max);
	CHECK_VECTOR2(clampBRes, 0, 2);
}

TEST_CASE("vec2i comparisons")
{
	vec2i a = makeVec2i(5, 5);
	vec2i b = makeVec2i(3, 5);
	vec2i c = makeVec2i(-2, 6);

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
	vec2u a = makeVec2u(3, 4);

	CHECK_VECTOR2_ALL_ALIASES(a, 3, 4);

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

	vec2u b = makeVec2u(1);
	CHECK_VECTOR2(b, 1, 1);

	unsigned arr[2];
	store(arr, a);
	CHECK_VECTOR2_ARRAY(arr, 3, 4);

	vec2u c = makeVec2u(-2, 3);
	CHECK_VECTOR2(c, -2, 3);

	vec2u d = makeZeroVec2u();
	CHECK_VECTOR2(d, 0, 0);

	unsigned initArr[] = {1, 2};	
	vec2u e = makeVec2uFromMemory(initArr);
	CHECK_VECTOR2(e, 1, 2);
}

TEST_CASE("vec2u setters")
{
	vec2u a;
	a.setX(4);
	a.setY(2);
	CHECK_VECTOR2(a, 4, 2);

	vec2u b;
	b.setY(2);
	b.setX(4);
	CHECK_VECTOR2(b, 4, 2);
}

TEST_CASE("vec2u operations")
{
	vec2u a = makeVec2u(5, 4);
	vec2u b = makeVec2u(1, 3);

	LOG_VECTOR2(a);
	LOG_VECTOR2(b);
	
	vec2u addRes = a + b;
	CHECK_VECTOR2(addRes, 6, 7);
	
	vec2u subRes = a - b;
	CHECK_VECTOR2(subRes, 4, 1);

	vec2u addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK_VECTOR2(addAsignmentRes, 6, 7);

	vec2u subAsignmentRes = a;
	subAsignmentRes -= b;
	CHECK_VECTOR2(subAsignmentRes, 4, 1);
	
	vec2u scalarMulRes1 = a * 5;
	CHECK_VECTOR2(scalarMulRes1, 25, 20);
	
	vec2u scalarMulRes2 = 5 * a;
	CHECK_VECTOR2(scalarMulRes2, 25, 20);
	
	vec2u hadamardMulRes = hadamardMul(a, b); 
	CHECK_VECTOR2(hadamardMulRes, 5, 12);

	vec2u minRes = min(a, b);
	CHECK_VECTOR2(minRes, 1, 3);

	vec2u maxRes = max(a, b);
	CHECK_VECTOR2(maxRes, 5, 4);

	CHECK(sumOfElements(b) == 4);
	CHECK(length(b) == (unsigned)sqrt(10));
	CHECK(lengthSquared(b) == 10);

	vec2u min = makeVec2u(2, 0);
	vec2u max = makeVec2u(5, 3);
	vec2u clampBRes = clamp(b, min, max);
	CHECK_VECTOR2(clampBRes, 2, 3);
}

TEST_CASE("vec2u comparisons")
{
	vec2u a = makeVec2u(5, 5);
	vec2u b = makeVec2u(3, 5);
	vec2u c = makeVec2u(-2, 6);

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


