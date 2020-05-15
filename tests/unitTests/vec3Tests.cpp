#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_CHECKS 
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

	vec2 E;

	E = D.XY();
	CHECK(E.X() == 1.f);
	CHECK(E.Y() == 2.f);
	E = D.UV();
	CHECK(E.X() == 1.f);
	CHECK(E.Y() == 2.f);
	E = D.RG();
	CHECK(E.X() == 1.f);
	CHECK(E.Y() == 2.f);

	E = D.YX();
	CHECK(E.X() == 2.f);
	CHECK(E.Y() == 1.f);
	E = D.VU();
	CHECK(E.X() == 2.f);
	CHECK(E.Y() == 1.f);
	E = D.GR();
	CHECK(E.X() == 2.f);
	CHECK(E.Y() == 1.f);

	E = D.YZ();
	CHECK(E.X() == 2.f);
	CHECK(E.Y() == 3.f);
	E = D.VW();
	CHECK(E.X() == 2.f);
	CHECK(E.Y() == 3.f);
	E = D.GB();
	CHECK(E.X() == 2.f);
	CHECK(E.Y() == 3.f);

	E = D.ZY();
	CHECK(E.X() == 3.f);
	CHECK(E.Y() == 2.f);
	E = D.WV();
	CHECK(E.X() == 3.f);
	CHECK(E.Y() == 2.f);
	E = D.BG();
	CHECK(E.X() == 3.f);
	CHECK(E.Y() == 2.f);

	E = D.XZ();
	CHECK(E.X() == 1.f);
	CHECK(E.Y() == 3.f);
	E = D.UW();
	CHECK(E.X() == 1.f);
	CHECK(E.Y() == 3.f);
	E = D.RB();
	CHECK(E.X() == 1.f);
	CHECK(E.Y() == 3.f);

	E = D.ZX();
	CHECK(E.X() == 3.f);
	CHECK(E.Y() == 1.f);
	E = D.WU();
	CHECK(E.X() == 3.f);
	CHECK(E.Y() == 1.f);
	E = D.BR();
	CHECK(E.X() == 3.f);
	CHECK(E.Y() == 1.f);

	E = D.XX();
	CHECK(E.X() == 1.f);
	CHECK(E.Y() == 1.f);
	E = D.UU();
	CHECK(E.X() == 1.f);
	CHECK(E.Y() == 1.f);
	E = D.RR();
	CHECK(E.X() == 1.f);
	CHECK(E.Y() == 1.f);

	E = D.YY();
	CHECK(E.X() == 2.f);
	CHECK(E.Y() == 2.f);
	E = D.VV();
	CHECK(E.X() == 2.f);
	CHECK(E.Y() == 2.f);
	E = D.GG();
	CHECK(E.X() == 2.f);
	CHECK(E.Y() == 2.f);

	E = D.ZZ();
	CHECK(E.X() == 3.f);
	CHECK(E.Y() == 3.f);
	E = D.WW();
	CHECK(E.X() == 3.f);
	CHECK(E.Y() == 3.f);
	E = D.BB();
	CHECK(E.X() == 3.f);
	CHECK(E.Y() == 3.f);

	vec3 F;

	F = D.XYZ();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 3.f);
	F = D.UVW();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 3.f);
	/* F = D.RGB();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 3.f); */

	F = D.YZX();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 1.f);
	F = D.VWU();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 1.f);
	F = D.GBR();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 1.f);

	F = D.ZXY();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 2.f);
	F = D.WUV();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 2.f);
	F = D.BRG();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 2.f);

	F = D.ZYX();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 1.f);
	F = D.WVU();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 1.f);
	F = D.BGR();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 1.f);

	F = D.XZY();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 2.f);
	F = D.UWV();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 2.f);
	F = D.RBG();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 2.f);

	F = D.YXZ();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 3.f);
	F = D.VUW();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 3.f);
	F = D.GRB();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 3.f);

	F = D.XXY();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 2.f);
	F = D.UUV();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 2.f);
	F = D.RRG();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 2.f);
	
	F = D.XXZ();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 3.f);
	F = D.UUW();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 3.f);
	F = D.RRB();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 3.f);

	F = D.YYX();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 1.f);
	F = D.VVU();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 1.f);
	F = D.GGR();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 1.f);

	F = D.YYZ();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 3.f);
	F = D.VVW();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 3.f);
	F = D.GGB();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 3.f);

	F = D.ZZX();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 1.f);
	F = D.WWU();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 1.f);
	F = D.BBR();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 1.f);

	F = D.ZZY();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 2.f);
	F = D.WWV();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 2.f);
	F = D.BBG();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 2.f);

	F = D.YXX();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 1.f);
	F = D.VUU();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 1.f);
	F = D.GRR();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 1.f);

	F = D.ZXX();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 1.f);
	F = D.WUU();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 1.f);
	F = D.BRR();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 1.f);

	F = D.XYY();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 2.f);
	F = D.UVV();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 2.f);
	F = D.RGG();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 2.f);

	F = D.ZYY();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 2.f);
	F = D.WVV();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 2.f);
	F = D.BGG();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 2.f);

	F = D.XZZ();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 3.f);
	F = D.UWW();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 3.f);
	F = D.RBB();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 3.f);

	F = D.YZZ();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 3.f);
	F = D.VWW();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 3.f);
	F = D.GBB();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 3.f);

	F = D.XYX();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 1.f);
	F = D.UVU();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 1.f);
	F = D.RGR();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 1.f);

	F = D.XZX();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 1.f);
	F = D.UWU();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 1.f);
	F = D.RBR();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 1.f);

	F = D.YXY();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 2.f);
	F = D.VUV();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 2.f);
	F = D.GRG();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 2.f);

	F = D.YZY();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 2.f);
	F = D.VWV();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 2.f);
	F = D.GBG();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 2.f);

	F = D.ZXZ();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 3.f);
	F = D.WUW();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 3.f);
	F = D.BRB();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 3.f);

	F = D.ZYZ();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 3.f);
	F = D.WVW();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 3.f);
	F = D.BGB();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 3.f);

	F = D.XXX();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 1.f);
	F = D.UUU();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 1.f);
	F = D.RRR();
	CHECK(F.X() == 1.f);
	CHECK(F.Y() == 1.f);
	CHECK(F.Z() == 1.f);

	F = D.YYY();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 2.f);
	F = D.VVV();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 2.f);
	F = D.GGG();
	CHECK(F.X() == 2.f);
	CHECK(F.Y() == 2.f);
	CHECK(F.Z() == 2.f);

	F = D.ZZZ();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 3.f);
	F = D.WWW();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 3.f);
	F = D.BBB();
	CHECK(F.X() == 3.f);
	CHECK(F.Y() == 3.f);
	CHECK(F.Z() == 3.f);
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

	auto AddRes = A + B;
	CHECK(AddRes.X() == 0.f);
	CHECK(AddRes.Y() == 8.f);
	CHECK(AddRes.Z() == 5.f);

	auto SubRes = A - B;
	CHECK(SubRes.X() == 4.f);
	CHECK(SubRes.Y() == -2.f);
	CHECK(SubRes.Z() == 3.f);

	auto AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK(AddAsignmentRes.X() == 0.f);
	CHECK(AddAsignmentRes.Y() == 8.f);
	CHECK(AddAsignmentRes.Z() == 5.f);

	auto SubAsignmentRes = A;
	SubAsignmentRes -= B;
	CHECK(SubAsignmentRes.X() == 4.f);
	CHECK(SubAsignmentRes.Y() == -2.f);
	CHECK(SubAsignmentRes.Z() == 3.f);

	auto ScalarMulRes1 = A * 4.5f;
	CHECK(ScalarMulRes1.X() == 9.f);
	CHECK(ScalarMulRes1.Y() == 13.5f);
	CHECK(ScalarMulRes1.Z() == 18.f);

	auto ScalarMulRes2 = 4.5f * A;
	CHECK(ScalarMulRes2.X() == 9.f);
	CHECK(ScalarMulRes2.Y() == 13.5f);
	CHECK(ScalarMulRes2.Z() == 18.f);

	auto ScalarDivRes = A / 2.f;
	CHECK(ScalarDivRes.X() == 1.f);
	CHECK(ScalarDivRes.Y() == 1.5f);
	CHECK(ScalarDivRes.Z() == 2.f);

	auto HadamardMulRes = HadamardMul(A, B); 
	CHECK(HadamardMulRes.X() == -4.f);
	CHECK(HadamardMulRes.Y() == 15.f);
	CHECK(HadamardMulRes.Z() == 4.f);

	auto HadamardDivRes = HadamardDiv(A, B); 
	CHECK(HadamardDivRes.X() == -1.f);
	CHECK(HadamardDivRes.Y() == 0.6f);
	CHECK(HadamardDivRes.Z() == 4.f);

	auto NegatedB = -B;
	CHECK(NegatedB.X() == 2.f);
	CHECK(NegatedB.Y() == -5.f);
	CHECK(NegatedB.Z() == -1.f);

	auto MinRes = Min(A, B);
	CHECK(MinRes.X() == -2.f);
	CHECK(MinRes.Y() == 3.f);
	CHECK(MinRes.Z() == 1.f);

	auto MaxRes = Max(A, B);
	CHECK(MaxRes.X() == 2.f);
	CHECK(MaxRes.Y() == 5.f);
	CHECK(MaxRes.Z() == 4.f);

	auto AbsoluteB = Abs(B);
	CHECK(AbsoluteB.X() == 2);
	CHECK(AbsoluteB.Y() == 5);
	CHECK(AbsoluteB.Z() == 1);

	auto NormalizedB = Normalize(B);
	CHECK(NormalizedB.X() == FloatCmp(B.X() / sqrt(30)));
	CHECK(NormalizedB.Y() == FloatCmp(B.Y() / sqrt(30)));
	CHECK(NormalizedB.Z() == FloatCmp(B.Z() / sqrt(30)));
	
	vec3 C = Vec3(1.f, 0.f, 0.f);
	vec3 D = Vec3(0.f, 1.f, 0.f);
	auto CrossRes = Cross(C, D);
	CHECK(CrossRes.X() == 0.f);
	CHECK(CrossRes.Y() == 0.f);
	CHECK(CrossRes.Z() == 1.f);

	vec3 E = Vec3(2,3,4);
	vec3 F = Vec3(5,6,7);
	auto CrossRes2 = Cross(E, F);
	CHECK(CrossRes2.X() == -3.f);
	CHECK(CrossRes2.Y() == 6.f);
	CHECK(CrossRes2.Z() == -3.f);

	CHECK(Dot(A, B) == 15.f);
	CHECK(SumOfElements(B) == 4.f);
	CHECK(Length(B) == FloatCmp(sqrt(30.f)));
	CHECK(LengthSquared(B) == 30.f);

	vec3 Min = Vec3(-1.f, 7.f, -5.f);
	vec3 Max = Vec3(4.f, 8.f, -1.f);
	vec3 ClampRes = Clamp(B, Min, Max);
	CHECK(ClampRes.X() == -1.f);
	CHECK(ClampRes.Y() == 7.f);
	CHECK(ClampRes.Z() == -1.f);

	vec3 G = Vec3(0.f, 2.f, 3.f);
	vec3 H = Vec3(4.f, 5.f, 6.f);
	auto LerpRes = Lerp(G, H, 0.5f);
	CHECK(LerpRes.X() == 2.f);
	CHECK(LerpRes.Y() == 3.5f);
	CHECK(LerpRes.Z() == 4.5f);
	LerpRes = Lerp(H, G, 0.5f);
	CHECK(LerpRes.X() == 2.f);
	CHECK(LerpRes.Y() == 3.5f);
	CHECK(LerpRes.Z() == 4.5f);

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

