#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

TEST_CASE("vec3 construction and getters")
{
	vec3 A = Vec3(1.f, 5.f, -3.f);
	CHECK(A.X() == 1.f);
	CHECK(A.U() == 1.f);
	CHECK(A.R() == 1.f);
	CHECK(A.Y() == 5.f);
	CHECK(A.V() == 5.f);
	CHECK(A.G() == 5.f);
	CHECK(A.Z() == -3.f);
	CHECK(A.W() == -3.f);
	CHECK(A.B() == -3.f);

	float Storage[3];
	Store(Storage, A);
	CHECK(Storage[0] == 1.f);
	CHECK(Storage[1] == 5.f);
	CHECK(Storage[2] == -3.f);

	vec3 B = Vec3(2.f);
	CHECK(B.X() == 2.f);
	CHECK(B.Y() == 2.f);
	CHECK(B.Z() == 2.f);

	vec3 C = Vec3();
	CHECK(C.X() == 0.f);
	CHECK(C.Y() == 0.f);
	CHECK(C.Z() == 0.f);

	float Arr[3] = {1.f, 2.f, 3.f};
	vec3 D = Vec3FromMemory(Arr);
	REQUIRE(D.X() == 1.f);
	REQUIRE(D.Y() == 2.f);
	REQUIRE(D.Z() == 3.f);

	// NOTE: Accessing simd types directly (without intrinsics) is slow
	CHECK(*Ptr(D) == 1.f);
	CHECK(*PtrY(D) == 2.f);
	CHECK(*PtrZ(D) == 3.f);
	CHECK(D[0] == 1.f);
	CHECK(D[1] == 2.f);
	CHECK(D[2] == 3.f);
}

TEST_CASE("vec3 Setters")
{
	vec3 A;
	A.SetX(-1.f);
	A.SetY(2.f);
	A.SetZ(-3.f);
	CHECK(A.X() == -1.f);
	CHECK(A.Y() == 2.f);
	CHECK(A.Z() == -3.f);

	vec3 B;
	B.SetY(2.f);
	B.SetX(-1.f);
	B.SetZ(-3.f);
	CHECK(B.X() == -1.f);
	CHECK(B.Y() == 2.f);
	CHECK(B.Z() == -3.f);
}

TEST_CASE("vec3 operations")
{
	vec3 A = Vec3(2.f, 3.f, 4.f); 	
	vec3 B = Vec3(-2.f, 5.f, 1.f); 	

	CHECK_VEC3(A + B, 0.f, 8.f, 5.f);
	CHECK_VEC3(A - B, 4.f, -2.f, 3.f);
	CHECK_VEC3(A * 4.5f, 9.f, 13.5f, 18.f);
	CHECK_VEC3(4.5f * A, 9.f, 13.5f, 18.f);
	CHECK_VEC3(A / 2.f, 1.f, 1.5f, 2.f);
	CHECK_VEC3(HadamardMul(A, B), -4.f, 15.f, 4.f);
	CHECK_VEC3(HadamardDiv(A, B), -1.f, 0.6f, 4.f);
	CHECK_VEC3(-B, 2.f, -5.f, -1.f);
	CHECK_VEC3(Min(A, B), -2.f, 3.f, 1.f);
	CHECK_VEC3(Max(A, B), 2.f, 5.f, 4.f);
	CHECK_VEC3(Abs(B), 2.f, 5.f, 1.f);
	CHECK_VEC3_APPROX(Normalize(B), B.X() / sqrt(30), B.Y() / sqrt(30), B.Z() / sqrt(30));
	CHECK_VEC3(Cross(Vec3(1.f, 0.f, 0.f), Vec3(0.f, 1.f, 0.f)), 0.f, 0.f, 1.f);
	CHECK_VEC3(Cross(Vec3(2.f, 3.f, 4.f), Vec3(5.f, 6.f, 7.f)), -3.f, 6.f, -3.f);
	CHECK(Dot(A, B) == 15.f);
	CHECK(SumOfElements(B) == 4.f);
	CHECK(Length(B) == FloatCmp(sqrt(30.f)));
	CHECK(LengthSquared(B) == 30.f);
	CHECK_VEC3(Clamp(B, Vec3(-1.f, 7.f, -5.f), Vec3(4.f, 8.f, -1.f)), -1.f, 7.f, -1.f);
	CHECK_VEC3(Lerp(Vec3(0.f, 2.f, 3.f), Vec3(4.f, 5.f, 6.f), 0.5f), 2.f, 3.5f, 4.5f);
	CHECK_VEC3(Lerp(Vec3(4.f, 5.f, 6.f), Vec3(0.f, 2.f, 3.f), 0.5f), 2.f, 3.5f, 4.5f);

	auto C = A;
	C += B;
	CHECK_VEC3(C, 0.f, 8.f, 5.f);

	auto D = A;
	D -= B;
	CHECK_VEC3(D, 4.f, -2.f, 3.f);
	
	auto E = A;
	E *= 2.f;
	CHECK_VEC3(E, 4.f, 6.f, 8.f);

	auto F = A;
	F /= 2.f;
	CHECK_VEC3(F, 1.f, 1.5f, 2.f);

	vec3 J = Vec3();

	J.AddX(1.f);
	J.AddY(2.f);
	J.AddZ(-3.f);
	CHECK_VEC3(J, 1.f, 2.f, -3.f);

	J.SubX(3.f);
	J.SubY(1.f);
	J.SubZ(-6.f);
	CHECK_VEC3(J, -2.f, 1.f, 3.f);

	J.MulX(2.f);
	J.MulY(4.f);
	J.MulZ(-3.f);
	CHECK_VEC3(J, -4.f, 4.f, -9.f);

	J.DivX(2.f);
	J.DivY(-4.f);
	J.DivZ(-2.f);
	CHECK_VEC3(J, -2.f, -1.f, 4.5f);

	vec3 K = Vec3(-2.f, 5.f, 1.f); 	
	Normalize(&K);
	CHECK_VEC3_APPROX(Normalize(K), B.X() / sqrt(30), B.Y() / sqrt(30), B.Z() / sqrt(30));
}

TEST_CASE("vec3 Comparisons")
{
	vec3 A = Vec3(1.f, 2.f, 4.f);
	vec3 B = Vec3(1.f, 3.f, -5.f);

	CHECK(A == A);
	CHECK(A != B);

	auto EqMask = EqualsMask(A, B);
	CHECK((EqMask.X() && !EqMask.Y() && !EqMask.Z()));

	auto GTMask = GreaterMask(A, B);
	CHECK((!GTMask.X() && !GTMask.Y() && GTMask.Z()));

	auto GEMask = GreaterOrEqualMask(A, B);
	CHECK((GEMask.X() && !GEMask.Y() && GEMask.Z()));

	auto LTMask = LesserMask(A, B);
	CHECK((!LTMask.X() && LTMask.Y() && !LTMask.Z()));

	auto LEMask = LesserOrEqualMask(A, B);
	CHECK((LEMask.X() && LEMask.Y() && !LEMask.Z()));
}

