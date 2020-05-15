#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

TEST_CASE("vec4 construction and getters") 
{
	vec4 A = Vec4(1.f, 2.f, 3.f, 4.f);
	CHECK_VEC4_WITH_XYZW_AND_RGBA_GETTERS(A, 1.f, 2.f, 3.f, 4.f);

	float Storage[4];
	Store(Storage, A);
	CHECK_ARRAY4(Storage, 1.f, 2.f, 3.f, 4.f);
	Store16ByteAligned(Storage, A);
	CHECK_ARRAY4(Storage, 1.f, 2.f, 3.f, 4.f);

	CHECK_VEC4(Vec4(5.f), 5.f, 5.f, 5.f, 5.f); 
	CHECK_VEC4(Vec4(), 0.f, 0.f, 0.f, 0.f); 

	float Arr[4] = {1.f, 2.f, 3.f, 4.f};
	CHECK_VEC4(Vec4FromMemory(Arr), 1.f, 2.f, 3.f, 4.f);

	vec4 B = Vec4(Vec3(1.f, 2.f, 3.f), 4.f);
	CHECK_VEC4(B, 1.f, 2.f, 3.f, 4.f);

	// NOTE: Accessing simd types directly (without intrinsics) is slow
	CHECK(*Ptr(B) == 1.f);
	CHECK(*PtrY(B) == 2.f);
	CHECK(*PtrZ(B) == 3.f);
	CHECK(*PtrW(B) == 4.f);
	CHECK(B[0] == 1.f);
	CHECK(B[1] == 2.f);
	CHECK(B[2] == 3.f);
	CHECK(B[3] == 4.f);
}

TEST_CASE("vec4 setters")
{
	vec4 A;
	A.SetX(1.f);
	A.SetY(2.f);
	A.SetZ(3.f);
	A.SetW(4.f);
	CHECK_VEC4(A, 1.f, 2.f, 3.f, 4.f);
	
	vec4 B;
	B.SetZ(3.f);
	B.SetX(1.f);
	B.SetW(4.f);
	B.SetY(2.f);
	CHECK_VEC4(B, 1.f, 2.f, 3.f, 4.f);
}

TEST_CASE("vec4 operations")
{
	vec4 A = Vec4(1.f, 3.f, 5.f, -7.f);
	vec4 B = Vec4(2.f, 4.f, -6.f, 8.f);

	vec4 AddRes = A + B;
	CHECK_VEC4(AddRes, 3.f, 7.f, -1.f, 1.f);

	vec4 SubRes = A - B;
	CHECK_VEC4(SubRes, -1.f, -1.f, 11.f, -15.f);

	vec4 AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK_VEC4(AddAsignmentRes, 3.f, 7.f, -1.f, 1.f);

	vec4 SubAssignmentRes = A;
	SubAssignmentRes -= B;
	CHECK_VEC4(SubAssignmentRes, -1.f, -1.f, 11.f, -15.f);

	vec4 ScalarMulRes1 = A * 2.f;
	CHECK_VEC4(ScalarMulRes1, 2.f, 6.f, 10.f, -14.f);

	vec4 ScalarMulRes2 = 2.f * A;
	CHECK_VEC4(ScalarMulRes2, 2.f, 6.f, 10.f, -14.f);

	vec4 ScalarDivRes = A / 2.f;
	CHECK_VEC4(ScalarDivRes, 0.5f, 1.5f, 2.5f, -3.5f);

	vec4 MulRes = HadamardMul(A, B);
	CHECK_VEC4(MulRes, 2.f, 12.f, -30.f, -56.f);

	vec4 DivRes = HadamardDiv(A, B);
	CHECK_VEC4_APPROX(DivRes, 0.5f, 0.75f, -0.83, -0.875);

	vec4 NegatedB = -B;
	CHECK_VEC4(NegatedB, -2.f, -4.f, 6.f, -8.f);

	vec4 MinRes = Min(A, B);
	CHECK_VEC4(MinRes, 1.f, 3.f, -6.f, -7.f);

	vec4 MaxRes = Max(A, B);
	CHECK_VEC4(MaxRes, 2.f, 4.f, 5.f, 8.f);

	vec4 AbsoluteB = Abs(B);
	CHECK_VEC4(AbsoluteB, 2.f, 4.f, 6.f, 8.f);

	vec4 NormalizedB = Normalize(B);
	CHECK_VEC4_APPROX(NormalizedB,
		B.X() / sqrt(120), B.Y() / sqrt(120), B.Z() / sqrt(120), B.W() / sqrt(120));

	CHECK(Dot(A, B) == -72.f);
	CHECK(SumOfElements(B) == 8.f);
	CHECK(Length(B) == FloatCmp(sqrt(120.f)));
	CHECK(LengthSquared(B) == 120.f);

	vec4 C = Vec4(1.f, 3.f, 5.f, -7.f);
	vec4 Min = Vec4(2.f, 2.f, 2.f, 2.f);
	vec4 Max = Vec4(5.f, 5.f, 3.f, 2.f);
	vec4 ClampRes = Clamp(C, Min, Max);
	CHECK_VEC4(ClampRes, 2.f, 3.f, 3.f, 2.f);

	vec4 G = Vec4(0.f, 2.f, 3.f, 0.f);
	vec4 H = Vec4(4.f, 5.f, 6.f, 100.f);
	auto LerpRes = Lerp(G, H, 0.5f);
	CHECK_VEC4(LerpRes, 2.f, 3.5f, 4.5f, 50.f);
	LerpRes = Lerp(H, G, 0.5f);
	CHECK_VEC4(LerpRes, 2.f, 3.5f, 4.5f, 50.f);

	vec4 J = Vec4();

	J.AddX(1.f);
	J.AddY(2.f);
	J.AddZ(-3.f);
	J.AddW(-4.f);
	CHECK_VEC4(J, 1.f, 2.f, -3.f, -4.f);

	J.SubX(3.f);
	J.SubY(1.f);
	J.SubZ(-6.f);
	J.SubW(2.f);
	CHECK_VEC4(J, -2.f, 1.f, 3.f, -6.f);

	J.MulX(2.f);
	J.MulY(4.f);
	J.MulZ(-3.f);
	J.MulW(0.5f);
	CHECK_VEC4(J, -4.f, 4.f, -9.f, -3.f);

	J.DivX(2.f);
	J.DivY(-4.f);
	J.DivZ(-2.f);
	J.DivW(3.f);
	CHECK_VEC4(J, -2.f, -1.f, 4.5f, -1.f);
}

TEST_CASE("vec4 Comparisons")
{
	vec4 A = Vec4(1.f, 2.f, 4.f, 5.f);
	vec4 B = Vec4(1.f, 3.f, -5.f, 5.f);

	CHECK(A == A);
	CHECK(A != B);

	auto EqMask = EqualsMask(A, B);
	CHECK((EqMask.X() && !EqMask.Y() && !EqMask.Z() && EqMask.W()));

	auto GTMask = GreaterMask(A, B);
	CHECK((!GTMask.X() && !GTMask.Y() && GTMask.Z() && !GTMask.W()));

	auto GEMask = GreaterOrEqualMask(A, B);
	CHECK((GEMask.X() && !GEMask.Y() && GEMask.Z() && GEMask.W()));

	auto LTMask = LesserMask(A, B);
	CHECK((!LTMask.X() && LTMask.Y() && !LTMask.Z() && !LTMask.W()));

	auto LEMask = LesserOrEqualMask(A, B);
	CHECK((LEMask.X() && LEMask.Y() && !LEMask.Z() && LEMask.W()));
}
