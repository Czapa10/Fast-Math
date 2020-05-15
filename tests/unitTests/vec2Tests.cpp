#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

TEST_CASE("vec2 construction and getters") 
{
	vec2 A = Vec2(-3.f, 4.5f);
	CHECK_VEC2_ALL_ALIASES(A, -3.f, 4.5f);

	float Arr[2];
	Store(Arr, A);
	CHECK_ARRAY2(Arr, -3.f, 4.5f);

	CHECK_VEC2(Vec2(1.f), 1.f, 1.f);
	CHECK_VEC2(Vec2(), 0.f, 0.f);

	float InitArr[] = {-1.f, 2.f};	
	CHECK_VEC2(Vec2FromMemory(InitArr), -1.f, 2.f);

	CHECK(A.YX().X() == 4.5f);
	CHECK(A.YX().Y() == -3.f);
	CHECK(A.VU().U() == 4.5f);
	CHECK(A.VU().V() == -3.f);

	CHECK(A.XX().X() == -3.f);
	CHECK(A.XX().Y() == -3.f);
	CHECK(A.UU().U() == -3.f);
	CHECK(A.UU().V() == -3.f);

	CHECK(A.YY().X() == 4.5f);
	CHECK(A.YY().Y() == 4.5f);
	CHECK(A.VV().U() == 4.5f);
	CHECK(A.VV().V() == 4.5f);

	// NOTE: Accessing simd types directly (without intrinsics) is slow
	vec2 P = Vec2(-1.f, 2.f);
	CHECK(*Ptr(P) == -1.f);
	CHECK(*PtrY(P) == 2.f);

	CHECK(P[0] == -1.f);
	CHECK(P[1] == 2.f);
}

TEST_CASE("vec2 setters")
{
	vec2 A;
	A.SetX(4.f);
	A.SetY(-2.5f);
	CHECK_VEC2(A, 4.f, -2.5f);

	vec2 B;
	B.SetY(-2.5f);
	B.SetX(4.f);
	CHECK_VEC2(B, 4.f, -2.5f);
}

TEST_CASE("vec2 operations")
{
	vec2 A = Vec2(2.f, 4.f);	
	vec2 B = Vec2(-5.f, 3.f);	

	vec2 AddRes = A + B; 
	CHECK_VEC2(AddRes, -3.f, 7.f);

	vec2 SubRes = A - B;
	CHECK_VEC2(SubRes, 7.f, 1.f);

	vec2 AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK_VEC2(AddAsignmentRes, -3.f, 7.f);

	vec2 SubAsignmentRes = A;
	SubAsignmentRes -= B;
	CHECK_VEC2(SubAsignmentRes, 7.f, 1.f);

	vec2 ScalarMulRes1 = A * 4.5f;
	CHECK_VEC2(ScalarMulRes1, 9.f, 18.f);

	vec2 ScalarMulRes2 = 4.5f * A;
	CHECK_VEC2(ScalarMulRes2, 9.f, 18.f);

	vec2 ScalarDivRes = A / 2.f;
	CHECK_VEC2(ScalarDivRes, 1.f, 2.f);

	vec2 HadamardMulRes = HadamardMul(A, B);
	CHECK_VEC2(HadamardMulRes, -10.f, 12.f);

	vec2 HadamardDivRes = HadamardDiv(A, B);
	CHECK_VEC2(HadamardDivRes, 2.f / -5.f, 4.f / 3.f);

	vec2 NegatedB = -B;
	CHECK_VEC2(NegatedB, 5.f, -3.f); 

	vec2 MinRes = Min(A, B);
	CHECK_VEC2(MinRes, -5.f, 3.f); 

	vec2 MaxRes = Max(A, B);
	CHECK_VEC2(MaxRes, 2.f, 4.f); 

	vec2 AbsoluteB = Abs(B);
	CHECK_VEC2(AbsoluteB, 5.f, 3.f); 

	vec2 NormalizedB = Normalize(B);
	CHECK_VEC2_APPROX(NormalizedB, B.X() / sqrt(34.f), B.Y() / sqrt(34.f)); 

	CHECK(Dot(A, B) == 2.f);
	CHECK(SumOfElements(B) == -2.f);
	CHECK(Length(B) == FloatCmp(sqrt(34.f)));
	CHECK(LengthSquared(B) == 34.f);

	vec2 Min = Vec2(0.f, 0.f);
	vec2 Max = Vec2(5.f, 2.f);
	vec2 ClampBRes = Clamp(B, Min, Max);
	CHECK_VEC2(ClampBRes, 0.f, 2.f);

	vec2 C = Vec2(0.f, 0.f);
	vec2 D = Vec2(2.f, 4.f);
	vec2 LerpRes = Lerp(C, D, 0.5f);
	CHECK_VEC2(LerpRes, 1.f, 2.f);

	LerpRes = Lerp(D, C, 0.5f);
	CHECK_VEC2(LerpRes, 1.f, 2.f);

	vec2 E = Vec2();

	E.AddX(2.f);
	E.AddY(-4.f);
	CHECK_VEC2(E, 2.f, -4.f);
	
	E.SubX(4.f);
	E.SubY(-5.f);
	CHECK_VEC2(E, -2.f, 1.f);
	
	E.MulX(2.f);
	E.MulY(-3.f);
	CHECK_VEC2(E, -4.f, -3.f);
	
	E.DivX(4.f);
	E.DivY(-2.f);
	CHECK_VEC2(E, -1.f, 1.5f);
}

TEST_CASE("vec2 Comparisons")
{
	vec2 A = Vec2(5.f, 5.f);
	vec2 B = Vec2(3.f, 5.f);
	vec2 C = Vec2(-2.f, 6.f);

	CHECK(A == A);
	CHECK(A != B);

	vec2 EqMask = EqualsMask(A, A);
	CHECK((EqMask.X() && EqMask.Y()));
	EqMask = EqualsMask(A, B);
	CHECK((!EqMask.X() && EqMask.Y()));

	vec2 GTMask = GreaterMask(A, B);
	CHECK((GTMask.X() && !GTMask.Y()));

	vec2 GEMask = GreaterOrEqualMask(A, B);
	CHECK((GEMask.X() && GEMask.Y()));
	GEMask = GreaterOrEqualMask(C, A);
	CHECK((!GEMask.X() && GEMask.Y()));

	vec2 LTMask = LesserMask(C, B);
	CHECK((LTMask.X() && !LTMask.Y()));

	vec2 LEMask = LesserOrEqualMask(B, A);
	CHECK((LEMask.X() && LEMask.Y()));
	LEMask = LesserOrEqualMask(C, B);
	CHECK((LEMask.X() && !LEMask.Y()));
}

TEST_CASE("vec2d constructors and getters") 
{
	vec2d A = Vec2d(-3.0, 4.0);

	CHECK_VEC2_ALL_ALIASES(A, -3.0, 4.0);

	CHECK(A.YX().X() == 4.0);
	CHECK(A.YX().Y() == -3.0);
	CHECK(A.VU().U() == 4.0);
	CHECK(A.VU().V() == -3.0);

	CHECK(A.XX().X() == -3.0);
	CHECK(A.XX().Y() == -3.0);
	CHECK(A.UU().U() == -3.0);
	CHECK(A.UU().V() == -3.0);

	CHECK(A.YY().X() == 4.0);
	CHECK(A.YY().Y() == 4.0);
	CHECK(A.VV().U() == 4.0);
	CHECK(A.VV().V() == 4.0);

	double Arr[2];
	Store16ByteAligned(Arr, A);
	CHECK_ARRAY2(Arr, -3.0, 4.0);
	Store(Arr, A);
	CHECK_ARRAY2(Arr, -3.0, 4.0);

	vec2d B = Vec2d(1.0);
	CHECK_VEC2(B, 1.0, 1.0);

	vec2d C = Vec2d();
	CHECK_VEC2(C, 0.0, 0.0);

	double InitArr[] = {-1.0, 2.0};	
	vec2d D = Vec2dFromMemory(InitArr);
	CHECK_VEC2(D, -1.0, 2.0);

	double* PX = Ptr(D);
	double* PY = PtrY(D);
	CHECK(*PX == -1.0);
	CHECK(*PY == 2.0);
}

TEST_CASE("vec2d Setters")
{
	vec2d A;
	A.SetX(4.0);
	A.SetY(-2.5);
	CHECK_VEC2(A, 4.0, -2.5);

	vec2d B;
	B.SetY(-2.5);
	B.SetX(4.0);
	CHECK_VEC2(B, 4.0, -2.5);
}

TEST_CASE("vec2d operations")
{
	vec2d A = Vec2d(2.0, 4.0);	
	vec2d B = Vec2d(-5.0, 3.0);	

	vec2d AddRes = A + B; 
	CHECK_VEC2(AddRes, -3.0, 7.0);

	vec2d SubRes = A - B;
	CHECK_VEC2(SubRes, 7.0, 1.0);

	vec2d AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK_VEC2(AddAsignmentRes, -3.0, 7.0);

	vec2d SubAsignmentRes = A;
	SubAsignmentRes -= B;
	CHECK_VEC2(SubAsignmentRes, 7.0, 1.0);

	vec2d ScalarMulRes1 = A * 4.5;
	CHECK_VEC2(ScalarMulRes1, 9.0, 18.0);

	vec2d ScalarMulRes2 = 4.5 * A;
	CHECK_VEC2(ScalarMulRes2, 9.0, 18.0);

	vec2d ScalarDivRes = A / 2.0;
	CHECK_VEC2(ScalarDivRes, 1.0, 2.0);

	vec2d HadamardMulRes = HadamardMul(A, B);
	CHECK_VEC2(HadamardMulRes, -10.0, 12.0);
	
	vec2d HadamardDivRes = HadamardDiv(A, B);
	CHECK_VEC2_APPROX(HadamardDivRes, 2.0 / -5.0, 4.0 / 3.0);

	vec2d NegatedB = -B;
	CHECK_VEC2(NegatedB, 5.0, -3.0);

	vec2d MinRes = Min(A, B);
	CHECK_VEC2(MinRes, -5.0, 3.0);

	vec2d MaxRes = Max(A, B);
	CHECK_VEC2(MaxRes, 2.0, 4.0);

	vec2d AbsoluteB = Abs(B);
	CHECK_VEC2(AbsoluteB, 5.0, 3.0);

	vec2d NormalizedB = Normalize(B);
	CHECK_VEC2_APPROX(NormalizedB, B.X() / sqrt(34), B.Y() / sqrt(34));

	CHECK(Dot(A, B) == 2.0);
	CHECK(SumOfElements(B) == -2.0);
	CHECK(Length(B) == FloatCmp(sqrt(34.0)));
	CHECK(LengthSquared(B) == 34.0);

	vec2d Min = Vec2d(0.0, 0.0);
	vec2d Max = Vec2d(5.0, 7.0);
	vec2d ClampRes = Clamp(Vec2d(-1.0, 8.0), Min, Max);
	CHECK_VEC2(ClampRes, 0.0, 7.0);

	vec2d C = Vec2d(0.0, 0.0);
	vec2d D = Vec2d(2.0, 4.0);
	vec2d LerpRes = Lerp(C, D, 0.5f);
	CHECK_VEC2(LerpRes, 1.0, 2.0);
	LerpRes = Lerp(D, C, 0.5);
	CHECK_VEC2(LerpRes, 1.0, 2.0);

	vec2d E = Vec2d();

	E.AddX(2.0);
	E.AddY(-4.0);
	CHECK_VEC2(E, 2.0, -4.0);
	
	E.SubX(4.0);
	E.SubY(-5.0);
	CHECK_VEC2(E, -2.0, 1.0);
	
	E.MulX(2.0);
	E.MulY(-3.0);
	CHECK_VEC2(E, -4.0, -3.0);
	
	E.DivX(4.0);
	E.DivY(-2.0);
	CHECK_VEC2(E, -1.0, 1.5);
}

TEST_CASE("vec2d comparisons")
{
	vec2d A = Vec2d(5.0, 5.0);
	vec2d B = Vec2d(3.0, 5.0);
	vec2d C = Vec2d(-2.0, 6.0);

	CHECK(A == A);
	CHECK(A != B);

	vec2d EqMask = EqualsMask(A, A);
	CHECK((EqMask.X() && EqMask.Y()));
	EqMask = EqualsMask(A, B);
	CHECK((!EqMask.X() && EqMask.Y()));

	vec2d GTMask = GreaterMask(A, B);
	CHECK((GTMask.X() && !GTMask.Y()));

	vec2d GEMask = GreaterOrEqualMask(A, B);
	CHECK((GEMask.X() && GEMask.Y()));
	GEMask = GreaterOrEqualMask(C, A);
	CHECK((!GEMask.X() && GEMask.Y()));

	vec2d LTMask = LesserMask(C, B);
	CHECK((LTMask.X() && !LTMask.Y()));

	vec2d LEMask = LesserOrEqualMask(B, A);
	CHECK((LEMask.X() && LEMask.Y()));
	LEMask = LesserOrEqualMask(C, B);
	CHECK((LEMask.X() && !LEMask.Y()));
}

TEST_CASE("vec2i constructors and getters") 
{
	vec2i A = Vec2i(-3, 4);

	CHECK_VEC2_ALL_ALIASES(A, -3, 4);

	CHECK(A.YX().X() == 4);
	CHECK(A.YX().Y() == -3);
	CHECK(A.VU().U() == 4);
	CHECK(A.VU().V() == -3);

	CHECK(A.XX().X() == -3);
	CHECK(A.XX().Y() == -3);
	CHECK(A.UU().U() == -3);
	CHECK(A.UU().V() == -3);

	CHECK(A.YY().X() == 4);
	CHECK(A.YY().Y() == 4);
	CHECK(A.VV().U() == 4);
	CHECK(A.VV().V() == 4);

	int32 Arr[2];
	Store(Arr, A);
	CHECK_ARRAY2(Arr, -3, 4);

	vec2i B = Vec2i(1);
	CHECK_VEC2(B, 1, 1);

	vec2i C = Vec2i();
	CHECK_VEC2(C, 0, 0);

	int32 InitArr[] = {-1, 2};	
	vec2i D = Vec2iFromMemory(InitArr);
	CHECK_VEC2(D, -1, 2);

	int32* PX = Ptr(D);
	int32* PY = PtrY(D);
	CHECK(*PX == -1);
	CHECK(*PY == 2);
}

TEST_CASE("vec2i Setters")
{
	vec2i A;
	A.SetX(4);
	A.SetY(-2);
	CHECK_VEC2(A, 4, -2);

	vec2d B;
	B.SetY(-2);
	B.SetX(4);
	CHECK_VEC2(B, 4, -2);
}

TEST_CASE("vec2i operations")
{
	vec2i A = Vec2i(2, 4);
	vec2i B = Vec2i(-5, 3);

	LOG_VEC2(A);
	LOG_VEC2(B);
	
	vec2i AddRes = A + B;
	CHECK_VEC2(AddRes, -3, 7);
	
	vec2i SubRes = A - B;
	CHECK_VEC2(SubRes, 7, 1);

	vec2i AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK_VEC2(AddAsignmentRes, -3, 7);

	vec2i SubAsignmentRes = A;
	SubAsignmentRes -= B;
	CHECK_VEC2(SubAsignmentRes, 7, 1);
	
	vec2i ScalarMulRes1 = A * -5;
	CHECK_VEC2(ScalarMulRes1, -10, -20);
	
	vec2i ScalarMulRes2 = -5 * A;
	CHECK_VEC2(ScalarMulRes2, -10, -20);
	
	vec2i HadamardMulRes = HadamardMul(A, B); 
	CHECK_VEC2(HadamardMulRes, -10, 12);

	vec2i NegatedB = -B;
	CHECK_VEC2(NegatedB, 5, -3);

	vec2i MinRes = Min(A, B);
	CHECK_VEC2(MinRes, -5, 3);

	vec2i MaxRes = Max(A, B);
	CHECK_VEC2(MaxRes, 2, 4);

	vec2i AbsoluteB = Abs(B);
	CHECK_VEC2(AbsoluteB, 5, 3);

	CHECK(SumOfElements(B) == -2);
	CHECK(Length(B) == (int32)sqrt(34));
	CHECK(LengthSquared(B) == 34);

	vec2i Min = Vec2i(0, 0);
	vec2i Max = Vec2i(5, 2);
	vec2i ClampBRes = Clamp(B, Min, Max);
	CHECK_VEC2(ClampBRes, 0, 2);

	vec2i E = Vec2i();

	E.AddX(2);
	E.AddY(-4);
	CHECK_VEC2(E, 2, -4);
	
	E.SubX(4);
	E.SubY(-6);
	CHECK_VEC2(E, -2, 2);
	
	E.MulX(2);
	E.MulY(-3);
	CHECK_VEC2(E, -4, -6);
	
	E.DivX(4);
	E.DivY(-2);
	CHECK_VEC2(E, -1, 3);
}

TEST_CASE("vec2i comparisons")
{
	vec2i A = Vec2i(5, 5);
	vec2i B = Vec2i(3, 5);
	vec2i C = Vec2i(-2, 6);

	CHECK(A == A);
	CHECK(A != B);

	vec2i EqMask = EqualsMask(A, A);
	CHECK((EqMask.X() && EqMask.Y()));
	EqMask = EqualsMask(A, B);
	CHECK((!EqMask.X() && EqMask.Y()));

	vec2i GTMask = GreaterMask(A, B);
	CHECK((GTMask.X() && !GTMask.Y()));

	vec2i GEMask = GreaterOrEqualMask(A, B);
	CHECK((GEMask.X() && GEMask.Y()));
	GEMask = GreaterOrEqualMask(C, A);
	CHECK((!GEMask.X() && GEMask.Y()));

	vec2i LTMask = LesserMask(C, B);
	CHECK(LTMask.X());
	CHECK(!LTMask.Y());

	vec2i LEMask = LesserOrEqualMask(B, A);
	CHECK((LEMask.X() && LEMask.Y()));
	LEMask = LesserOrEqualMask(C, B);
	CHECK((LEMask.X() && !LEMask.Y()));
}

TEST_CASE("vec2u constructors and getters") 
{
	vec2u A = Vec2u(3, 4);

	CHECK_VEC2_ALL_ALIASES(A, 3, 4);

	CHECK(A.YX().X() == 4);
	CHECK(A.YX().Y() == 3);
	CHECK(A.VU().U() == 4);
	CHECK(A.VU().V() == 3);

	CHECK(A.XX().X() == 3);
	CHECK(A.XX().Y() == 3);
	CHECK(A.UU().U() == 3);
	CHECK(A.UU().V() == 3);

	CHECK(A.YY().X() == 4);
	CHECK(A.YY().Y() == 4);
	CHECK(A.VV().U() == 4);
	CHECK(A.VV().V() == 4);

	vec2u B = Vec2u(1);
	CHECK_VEC2(B, 1, 1);

	uint32 Arr[2];
	Store(Arr, A);
	CHECK_ARRAY2(Arr, 3, 4);

	vec2u C = Vec2u(-2, 3);
	CHECK_VEC2(C, -2, 3);

	vec2u D = Vec2u();
	CHECK_VEC2(D, 0, 0);

	uint32 InitArr[] = {1, 2};	
	vec2u E = Vec2uFromMemory(InitArr);
	CHECK_VEC2(E, 1, 2);

	uint32* PX = Ptr(E);
	uint32* PY = PtrY(E);
	CHECK(*PX == 1);
	CHECK(*PY == 2);
}

TEST_CASE("vec2u Setters")
{
	vec2u A;
	A.SetX(4);
	A.SetY(2);
	CHECK_VEC2(A, 4, 2);

	vec2u B;
	B.SetY(2);
	B.SetX(4);
	CHECK_VEC2(B, 4, 2);
}

TEST_CASE("vec2u operations")
{
	vec2u A = Vec2u(5, 4);
	vec2u B = Vec2u(1, 3);

	vec2u AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK_VEC2(AddAsignmentRes, 6, 7);

	vec2u SubAsignmentRes = A;
	SubAsignmentRes -= B;
	CHECK_VEC2(SubAsignmentRes, 4, 1);
	
	vec2u ScalarMulRes1 = A * 5;
	CHECK_VEC2(ScalarMulRes1, 25, 20);
	
	vec2u ScalarMulRes2 = 5 * A;
	CHECK_VEC2(ScalarMulRes2, 25, 20);
	
	vec2u HadamardMulRes = HadamardMul(A, B); 
	CHECK_VEC2(HadamardMulRes, 5, 12);

	vec2u MinRes = Min(A, B);
	CHECK_VEC2(MinRes, 1, 3);

	vec2u MaxRes = Max(A, B);
	CHECK_VEC2(MaxRes, 5, 4);

	CHECK(SumOfElements(B) == 4);
	CHECK(Length(B) == (uint32)sqrt(10));
	CHECK(LengthSquared(B) == 10);

	vec2u Min = Vec2u(2, 0);
	vec2u Max = Vec2u(5, 3);
	vec2u ClampBRes = Clamp(B, Min, Max);
	CHECK_VEC2(ClampBRes, 2, 3);
	
	vec2u E = Vec2u();

	E.AddX(2);
	E.AddY(4);
	CHECK_VEC2(E, 2, 4);
	
	E.SubX(1);
	E.SubY(2);
	CHECK_VEC2(E, 1, 2);
	
	E.MulX(2);
	E.MulY(3);
	CHECK_VEC2(E, 2, 6);
	
	E.DivX(2);
	E.DivY(3);
	CHECK_VEC2(E, 1, 2);
}

TEST_CASE("vec2u comparisons")
{
	vec2u A = Vec2u(5, 5);
	vec2u B = Vec2u(3, 5);
	vec2u C = Vec2u(-2, 6);

	CHECK(A == A);
	CHECK(A != B);

	vec2u EqMask = EqualsMask(A, A);
	CHECK((EqMask.X() && EqMask.Y()));
	EqMask = EqualsMask(A, B);
	CHECK((!EqMask.X() && EqMask.Y()));

	vec2u GTMask = GreaterMask(A, B);
	CHECK((GTMask.X() && !GTMask.Y()));

	vec2u GEMask = GreaterOrEqualMask(A, B);
	CHECK((GEMask.X() && GEMask.Y()));
	GEMask = GreaterOrEqualMask(C, A);
	CHECK((!GEMask.X() && GEMask.Y()));

	vec2u LTMask = LesserMask(C, B);
	CHECK(LTMask.X());
	CHECK(!LTMask.Y());

	vec2u LEMask = LesserOrEqualMask(B, A);
	CHECK((LEMask.X() && LEMask.Y()));
	LEMask = LesserOrEqualMask(C, B);
	CHECK((LEMask.X() && !LEMask.Y()));
}


