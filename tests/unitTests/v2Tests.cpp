#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

TEST_CASE("v2 construction and getters")
{
	v2 A = V2(-3.f, 4.5f);
	CHECK_V2_ALL_ALIASES(A, -3.f, 4.5f);

	float Arr[2];
	Store(Arr, A);
	CHECK_ARRAY2(Arr, -3.f, 4.5f);

	CHECK_V2(V2(1.f), 1.f, 1.f);
	CHECK_V2(V2(), 0.f, 0.f);

	float InitArr[] = {-1.f, 2.f};	
	CHECK_V2(V2FromMemory(InitArr), -1.f, 2.f);

	v2 P = V2(-1.f, 2.f);
	CHECK(*Ptr(P) == -1.f);
	CHECK(*PtrY(P) == 2.f);
}

TEST_CASE("v2 operations")
{
	v2 A = V2(2.f, 4.f);
	v2 B = V2(-5.f, 3.f);

	CHECK_V2(A + B, -3.f, 7.f);
	CHECK_V2(A - B, 7.f, 1.f);
	CHECK_V2(A * 2.f, 4.f, 8.f);
	CHECK_V2(2.f * A, 4.f, 8.f);
	CHECK_V2(A / 2.f, 1.f, 2.f);
	CHECK_V2(HadamardMul(A, B), -10.f, 12.f);
	CHECK_V2(HadamardDiv(A, B), 2.f / -5.f, 4.f / 3.f);
	CHECK_V2(-B, 5.f, -3.f);
	CHECK_V2(Min(A, B), -5.f, 3.f);
	CHECK_V2(Max(A, B), 2.f, 4.f);
	CHECK_V2(Abs(B), 5.f, 3.f);
	CHECK_V2(Normalize(B), B.X / sqrt(34.f), B.Y / sqrt(34.f));
	CHECK_V2(Clamp(B, V2(), V2(5.f, 2.f)), 0.f, 2.f);
	CHECK_V2(Lerp(V2(), V2(2.f, 4.f), 0.5f), 1.f, 2.f);
	CHECK_V2(Lerp(V2(2.f, 4.f), V2(), 0.5f), 1.f, 2.f);
	CHECK(Dot(A, B) == 2.f);
	CHECK(SumOfElements(B) == -2.f);
	CHECK(Length(B) == FloatCmp(sqrt(34.f)));
	CHECK(LengthSquared(B) == 34.f);
	CHECK(A == A);
	CHECK(A != B);

	v2 AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK_V2(AddAsignmentRes, -3.f, 7.f);

	v2 SubAsignmentRes = A;
	SubAsignmentRes -= B;
	CHECK_V2(SubAsignmentRes, 7.f, 1.f);
}