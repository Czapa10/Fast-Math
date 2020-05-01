#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

#define CHECK_V3_ALL_ALIASES(_V, _X, _Y, _Z) {\
	auto V = _V; \
	CHECK3(V.X == _X, V.Y == _Y, V.Z == _Z); \
	CHECK3(V.U == _X, V.V == _Y, V.W == _Z); \
	CHECK3(V.R == _X, V.G == _Y, V.B == _Z); \
	CHECK_V2(V.XY, _X, _Y); \
	CHECK_V2(V.UV, _X, _Y); \
	CHECK_V2(V.RG, _X, _Y); \
	CHECK_V2(V.YZ, _Y, _Z); \
	CHECK_V2(V.VW, _Y, _Z); \
	CHECK_V2(V.GB, _Y, _Z); \
	CHECK3(V[0] == _X, V[1] == _Y, V[2] == _Z) };

TEST_CASE("v3 construction and getters")
{
	v3 A = V3(1.f, 2.f, 3.f);
	CHECK_V3_ALL_ALIASES(A, 1.f, 2.f, 3.f);

	float Arr[3];
	Store(Arr, A);
	CHECK_ARRAY3(Arr, 1.f, 2.f, 3.f);

	CHECK_V3(V3(1.f), 1.f, 1.f, 1.f);
	CHECK_V3(V3(), 0.f, 0.f, 0.f);

	float InitArr[] = {1.f, 2.f, 3.f};
	CHECK_V3(V3FromMemory(InitArr), 1.f, 2.f, 3.f);

	v3 P = V3(1.f, 2.f, 3.f);
	CHECK(*Ptr(P) == 1.f);
	CHECK(*PtrY(P) == 2.f);
	CHECK(*PtrZ(P) == 3.f);
}

TEST_CASE("v3 operations")
{
	v3 A = V3(2.f, 3.f, 4.f);
	v3 B = V3(-2.f, 5.f, 1.f);

	CHECK_V3(A + B, 0.f, 8.f, 5.f);
	CHECK_V3(A - B, 4.f, -2.f, 3.f);
	CHECK_V3(A * 3.f, 6.f, 9.f, 12.f);
	CHECK_V3(3.f * A, 6.f, 9.f, 12.f);
	CHECK_V3(A / 2.f, 1.f, 1.5f, 2.f);
	CHECK_V3(HadamardMul(A, B), -4.f, 15.f, 4.f);
	CHECK_V3(HadamardDiv(A, B), -1.f, 0.6f, 4.f);
	CHECK_V3(-B, 2.f, -5.f, -1.f);
	CHECK_V3(Min(A, B), -2.f, 3.f, 1.f);
	CHECK_V3(Max(A, B), 2.f, 5.f, 4.f);
	CHECK_V3(Abs(B), 2.f, 5.f, 1.f);
	CHECK_V3_APPROX(Normalize(B), B.X / sqrt(30.f), B.Y / sqrt(30.f), B.Z / sqrt(30.f));
	CHECK_V3(Cross(V3(1.f, 0.f, 0.f), V3(0.f, 1.f, 0.f)), 0.f, 0.f, 1.f);
	CHECK_V3(Cross(V3(2.f, 3.f, 4.f), V3(5.f, 6.f, 7.f)), -3.f, 6.f, -3.f);
	CHECK(Dot(A, B) == 15.f);
	CHECK(SumOfElements(B) == 4.f);
	CHECK(Length(B) == FloatCmp(sqrt(30.f)));
	CHECK(LengthSquared(B) == 30.f);
	CHECK_V3(Clamp(B, V3(-1.f, 7.f, -5.f), V3(4.f, 8.f, -1.f)), -1.f, 7.f, -1.f);
	CHECK_V3(Lerp(V3(0.f, 2.f, 3.f), V3(4.f, 5.f, 6.f), 0.5f), 2.f, 3.5f, 4.5f);
	CHECK_V3(Lerp(V3(4.f, 5.f, 6.f), V3(0.f, 2.f, 3.f), 0.5f), 2.f, 3.5f, 4.5f);
	CHECK(A == A);
	CHECK(A != B);
}
