#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

TEST_CASE("vec4 constructors and getters") 
{
	vec4 a = makeVec4(1.f, 2.f, 3.f, 4.f);		
	CHECK_VECTOR4_WITH_XYZW_AND_RGBA_GETTERS(a, 1.f, 2.f, 3.f, 4.f);

	float storage[4];
	store(storage, a);
	CHECK_VECTOR4_ARRAY(storage, 1.f, 2.f, 3.f, 4.f);
	store16ByteAligned(storage, a);
	CHECK_VECTOR4_ARRAY(storage, 1.f, 2.f, 3.f, 4.f);

	vec4 b = makeVec4(5.f);
	CHECK_VECTOR4(b, 5.f, 5.f, 5.f, 5.f); 

	vec4 c = makeZeroVec4();
	CHECK_VECTOR4(c, 0.f, 0.f, 0.f, 0.f); 

	float arr[4] = {1.f, 2.f, 3.f, 4.f};
	vec4 d = makeVec4FromMemory(arr);
	CHECK_VECTOR4(d, 1.f, 2.f, 3.f, 4.f);

	vec4 e = makeVec4(makeVec3(1.f, 2.f, 3.f), 4.f);
	CHECK_VECTOR4(e, 1.f, 2.f, 3.f, 4.f);

	float* px = ptr(e);
	float* py = ptrY(e);
	float* pz = ptrZ(e);
	float* pw = ptrW(e);
	CHECK(*px == 1.f);
	CHECK(*py == 2.f);
	CHECK(*pz == 3.f);
	CHECK(*pw == 4.f);
}

TEST_CASE("vec4 setters")
{
	vec4 a;
	a.setX(1.f);
	a.setY(2.f);
	a.setZ(3.f);
	a.setW(4.f);
	CHECK(a.x() == 1.f);
	CHECK(a.y() == 2.f);
	CHECK(a.z() == 3.f);
	CHECK(a.w() == 4.f);
	
	vec4 b;
	b.setZ(3.f);
	b.setX(1.f);
	b.setW(4.f);
	CHECK(b.x() == 1.f);
	CHECK(b.y() == 0.f);
	CHECK(b.z() == 3.f);
	CHECK(b.w() == 4.f);
}

TEST_CASE("vec4 operations")
{
	vec4 a = makeVec4(1.f, 3.f, 5.f, -7.f);
	vec4 b = makeVec4(2.f, 4.f, -6.f, 8.f);

	vec4 addRes = a + b;
	CHECK(addRes.x() == 3.f);
	CHECK(addRes.y() == 7.f);
	CHECK(addRes.z() == -1.f);
	CHECK(addRes.w() == 1.f);

	vec4 subRes = a - b;
	CHECK(subRes.x() == -1.f);
	CHECK(subRes.y() == -1.f);
	CHECK(subRes.z() == 11.f);
	CHECK(subRes.w() == -15.f);

	vec4 addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK(addAsignmentRes.x() == 3.f);
	CHECK(addAsignmentRes.y() == 7.f);
	CHECK(addAsignmentRes.z() == -1.f);
	CHECK(addAsignmentRes.w() == 1.f);

	vec4 subAsignmentRes = a;
	subAsignmentRes -= b;
	CHECK(subAsignmentRes.x() == -1.f);
	CHECK(subAsignmentRes.y() == -1.f);
	CHECK(subAsignmentRes.z() == 11.f);
	CHECK(subAsignmentRes.w() == -15.f);

	vec4 scalarMulRes1 = a * 2.f;
	CHECK(scalarMulRes1.x() == 2.f);
	CHECK(scalarMulRes1.y() == 6.f);
	CHECK(scalarMulRes1.z() == 10.f);
	CHECK(scalarMulRes1.w() == -14.f);

	vec4 scalarMulRes2 = 2.f * a;
	CHECK(scalarMulRes2.x() == 2.f);
	CHECK(scalarMulRes2.y() == 6.f);
	CHECK(scalarMulRes2.z() == 10.f);
	CHECK(scalarMulRes2.w() == -14.f);

	vec4 scalarDivRes = a / 2.f;
	CHECK(scalarDivRes.x() == 0.5f);
	CHECK(scalarDivRes.y() == 1.5f);
	CHECK(scalarDivRes.z() == 2.5f);
	CHECK(scalarDivRes.w() == -3.5f);

	vec4 mulRes = hadamardMul(a, b);
	CHECK(mulRes.x() == 2.f);
	CHECK(mulRes.y() == 12.f);
	CHECK(mulRes.z() == -30.f);
	CHECK(mulRes.w() == -56.f);

	vec4 divRes = hadamardDiv(a, b);
	CHECK(divRes.x() == 0.5f);
	CHECK(divRes.y() == 0.75f);
	CHECK(divRes.z() == floatCmp(-0.83f));
	CHECK(divRes.w() == -0.875f);

	vec4 negatedB = -b;
	CHECK(negatedB.x() == -2.f);
	CHECK(negatedB.y() == -4.f);
	CHECK(negatedB.z() == 6.f);
	CHECK(negatedB.w() == -8.f);

	vec4 minRes = min(a, b);
	CHECK(minRes.x() == 1.f);
	CHECK(minRes.y() == 3.f);
	CHECK(minRes.z() == -6.f);
	CHECK(minRes.w() == -7.f);

	vec4 maxRes = max(a, b);
	CHECK(maxRes.x() == 2.f);
	CHECK(maxRes.y() == 4.f);
	CHECK(maxRes.z() == 5.f);
	CHECK(maxRes.w() == 8.f);

	vec4 absoluteB = abs(b);
	CHECK(absoluteB.x() == 2.f);
	CHECK(absoluteB.y() == 4.f);
	CHECK(absoluteB.z() == 6.f);
	CHECK(absoluteB.w() == 8.f);

	vec4 normalizedB = normalize(b);
	CHECK(normalizedB.x() == floatCmp(b.x() / sqrt(120)));
	CHECK(normalizedB.y() == floatCmp(b.y() / sqrt(120)));
	CHECK(normalizedB.z() == floatCmp(b.z() / sqrt(120)));
	CHECK(normalizedB.w() == floatCmp(b.w() / sqrt(120)));

	CHECK(dot(a, b) == -72.f);
	CHECK(sumOfElements(b) == 8.f);
	CHECK(length(b) == floatCmp(sqrt(120.f)));
	CHECK(lengthSquared(b) == 120.f);

	vec4 c = makeVec4(1.f, 3.f, 5.f, -7.f);
	vec4 min = makeVec4(2.f, 2.f, 2.f, 2.f);
	vec4 max = makeVec4(5.f, 5.f, 3.f, 2.f);
	vec4 clampRes = clamp(c, min, max);
	CHECK(clampRes.x() == 2.f);
	CHECK(clampRes.y() == 3.f);
	CHECK(clampRes.z() == 3.f);
	CHECK(clampRes.w() == 2.f);

	vec4 g = makeVec4(0.f, 2.f, 3.f, 0.f);
	vec4 h = makeVec4(4.f, 5.f, 6.f, 100.f);
	auto lerpRes = lerp(g, h, 0.5f);
	CHECK(lerpRes.x() == 2.f);
	CHECK(lerpRes.y() == 3.5f);
	CHECK(lerpRes.z() == 4.5f);
	CHECK(lerpRes.w() == 50.f);
	lerpRes = lerp(h, g, 0.5f);
	CHECK(lerpRes.x() == 2.f);
	CHECK(lerpRes.y() == 3.5f);
	CHECK(lerpRes.z() == 4.5f);
	CHECK(lerpRes.w() == 50.f);
}

TEST_CASE("vec4 comparisons")
{
	vec4 a = makeVec4(1.f, 2.f, 4.f, 5.f);
	vec4 b = makeVec4(1.f, 3.f, -5.f, 5.f);

	CHECK(a == a);
	CHECK(a != b);

	auto eqMask = equalsMask(a, b);
	CHECK((eqMask.x() && !eqMask.y() && !eqMask.z() && eqMask.w()));

	auto gtMask = greaterMask(a, b);
	CHECK((!gtMask.x() && !gtMask.y() && gtMask.z() && !gtMask.w()));

	auto geMask = greaterOrEqualMask(a, b);
	CHECK((geMask.x() && !geMask.y() && geMask.z() && geMask.w()));

	auto ltMask = lesserMask(a, b);
	CHECK((!ltMask.x() && ltMask.y() && !ltMask.z() && !ltMask.w()));

	auto leMask = lesserOrEqualMask(a, b);
	CHECK((leMask.x() && leMask.y() && !leMask.z() && leMask.w()));
}
