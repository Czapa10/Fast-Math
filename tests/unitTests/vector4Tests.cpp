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
	CHECK_VECTOR4(a, 1.f, 2.f, 3.f, 4.f);
	
	vec4 b;
	b.setZ(3.f);
	b.setX(1.f);
	b.setW(4.f);
	b.setY(2.f);
	CHECK_VECTOR4(b, 1.f, 2.f, 3.f, 4.f);
}

TEST_CASE("vec4 operations")
{
	vec4 a = makeVec4(1.f, 3.f, 5.f, -7.f);
	vec4 b = makeVec4(2.f, 4.f, -6.f, 8.f);

	vec4 addRes = a + b;
	CHECK_VECTOR4(addRes, 3.f, 7.f, -1.f, 1.f);

	vec4 subRes = a - b;
	CHECK_VECTOR4(subRes, -1.f, -1.f, 11.f, -15.f);

	vec4 addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK_VECTOR4(addAsignmentRes, 3.f, 7.f, -1.f, 1.f);
	CHECK(addAsignmentRes.x() == 3.f);
	CHECK(addAsignmentRes.y() == 7.f);
	CHECK(addAsignmentRes.z() == -1.f);
	CHECK(addAsignmentRes.w() == 1.f);

	vec4 subAssignmentRes = a;
	subAssignmentRes -= b;
	CHECK_VECTOR4(subAssignmentRes, -1.f, -1.f, 11.f, -15.f);

	vec4 scalarMulRes1 = a * 2.f;
	CHECK_VECTOR4(scalarMulRes1, 2.f, 6.f, 10.f, -14.f);

	vec4 scalarMulRes2 = 2.f * a;
	CHECK_VECTOR4(scalarMulRes2, 2.f, 6.f, 10.f, -14.f);

	vec4 scalarDivRes = a / 2.f;
	CHECK_VECTOR4(scalarDivRes, 0.5f, 1.5f, 2.5f, -3.5f);

	vec4 mulRes = hadamardMul(a, b);
	CHECK_VECTOR4(mulRes, 2.f, 12.f, -30.f, -56.f);

	vec4 divRes = hadamardDiv(a, b);
	CHECK_VECTOR4_APPROX(divRes, 0.5f, 0.75f, -0.83, -0.875);

	vec4 negatedB = -b;
	CHECK_VECTOR4(negatedB, -2.f, -4.f, 6.f, -8.f);

	vec4 minRes = min(a, b);
	CHECK_VECTOR4(minRes, 1.f, 3.f, -6.f, -7.f);

	vec4 maxRes = max(a, b);
	CHECK_VECTOR4(maxRes, 2.f, 4.f, 5.f, 8.f);

	vec4 absoluteB = abs(b);
	CHECK_VECTOR4(absoluteB, 2.f, 4.f, 6.f, 8.f);

	vec4 normalizedB = normalize(b);
	CHECK_VECTOR4_APPROX(normalizedB,
		b.x() / sqrt(120), b.y() / sqrt(120), b.z() / sqrt(120), b.w() / sqrt(120));

	CHECK(dot(a, b) == -72.f);
	CHECK(sumOfElements(b) == 8.f);
	CHECK(length(b) == floatCmp(sqrt(120.f)));
	CHECK(lengthSquared(b) == 120.f);

	vec4 c = makeVec4(1.f, 3.f, 5.f, -7.f);
	vec4 min = makeVec4(2.f, 2.f, 2.f, 2.f);
	vec4 max = makeVec4(5.f, 5.f, 3.f, 2.f);
	vec4 clampRes = clamp(c, min, max);
	CHECK_VECTOR4(clampRes, 2.f, 3.f, 3.f, 2.f);

	vec4 g = makeVec4(0.f, 2.f, 3.f, 0.f);
	vec4 h = makeVec4(4.f, 5.f, 6.f, 100.f);
	auto lerpRes = lerp(g, h, 0.5f);
	CHECK_VECTOR4(lerpRes, 2.f, 3.5f, 4.5f, 50.f);
	lerpRes = lerp(h, g, 0.5f);
	CHECK_VECTOR4(lerpRes, 2.f, 3.5f, 4.5f, 50.f);
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
