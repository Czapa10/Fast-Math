#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

TEST_CASE("v2 Constructors and getters") 
{
	v2 A = V2(-3.f, 4.5f);
	CHECK_VECTOR2_ALL_ALIASES(A, -3.f, 4.5f);

	float Arr[2];
	Store(Arr, A);
	CHECK_VECTOR2_ARRAY(Arr, -3.f, 4.5f);

	v2 B = V2(1.f);
	CHECK_VECTOR2(B, 1.f, 1.f);

	v2 C = V2();
	CHECK_VECTOR2(C, 0.f, 0.f);

	float InitArr[] = {-1.f, 2.f};	
	v2 D = V2FromMemory(InitArr);
	CHECK_VECTOR2(D, -1.f, 2.f);

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

	float* PX = Ptr(D);
	float* PY = PtrY(D);
	CHECK(*PX == -1.f);
	CHECK(*PY == 2.f);
}

TEST_CASE("v2 Setters")
{
	v2 A;
	A.SetX(4.f);
	A.SetY(-2.5f);
	CHECK_VECTOR2(A, 4.f, -2.5f);

	v2 B;
	B.SetY(-2.5f);
	B.SetX(4.f);
	CHECK_VECTOR2(B, 4.f, -2.5f);
}

TEST_CASE("v2 operations")
{
	v2 A = V2(2.f, 4.f);	
	v2 B = V2(-5.f, 3.f);	

	v2 AddRes = A + B; 
	CHECK_VECTOR2(AddRes, -3.f, 7.f);

	v2 SubRes = A - B;
	CHECK_VECTOR2(SubRes, 7.f, 1.f);

	v2 AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK_VECTOR2(AddAsignmentRes, -3.f, 7.f);

	v2 SubAsignmentRes = A;
	SubAsignmentRes -= B;
	CHECK_VECTOR2(SubAsignmentRes, 7.f, 1.f);

	v2 ScalarMulRes1 = A * 4.5f;
	CHECK_VECTOR2(ScalarMulRes1, 9.f, 18.f);

	v2 ScalarMulRes2 = 4.5f * A;
	CHECK_VECTOR2(ScalarMulRes2, 9.f, 18.f);

	v2 ScalarDivRes = A / 2.f;
	CHECK_VECTOR2(ScalarDivRes, 1.f, 2.f);

	v2 HadamardMulRes = HadamardMul(A, B);
	CHECK_VECTOR2(HadamardMulRes, -10.f, 12.f);
	
	v2 HadamardDivRes = HadamardDiv(A, B);
	CHECK_VECTOR2(HadamardDivRes, 2.f / -5.f, 4.f / 3.f);

	v2 NegatedB = -B;
	CHECK_VECTOR2(NegatedB, 5.f, -3.f); 

	v2 MinRes = Min(A, B);
	CHECK_VECTOR2(MinRes, -5.f, 3.f); 

	v2 MaxRes = Max(A, B);
	CHECK_VECTOR2(MaxRes, 2.f, 4.f); 

	v2 AbsoluteB = Abs(B);
	CHECK_VECTOR2(AbsoluteB, 5.f, 3.f); 

	v2 NormalizedB = Normalize(B);
	CHECK_VECTOR2_APPROX(NormalizedB, B.X() / sqrt(34.f), B.Y() / sqrt(34.f)); 

	CHECK(Dot(A, B) == 2.f);
	CHECK(SumOfElements(B) == -2.f);
	CHECK(Length(B) == FloatCmp(sqrt(34.f)));
	CHECK(LengthSquared(B) == 34.f);

	v2 Min = V2(0.f, 0.f);
	v2 Max = V2(5.f, 2.f);
	v2 ClampBRes = Clamp(B, Min, Max);
	CHECK_VECTOR2(ClampBRes, 0.f, 2.f);

	v2 C = V2(0.f, 0.f);
	v2 D = V2(2.f, 4.f);
	v2 LerpRes = Lerp(C, D, 0.5f);
	CHECK_VECTOR2(LerpRes, 1.f, 2.f);

	LerpRes = Lerp(D, C, 0.5f);
	CHECK_VECTOR2(LerpRes, 1.f, 2.f);
}

TEST_CASE("v2 Comparisons")
{
	v2 A = V2(5.f, 5.f);
	v2 B = V2(3.f, 5.f);
	v2 C = V2(-2.f, 6.f);

	CHECK(A == A);
	CHECK(A != B);

	v2 EqMask = EqualsMask(A, A);
	CHECK((EqMask.X() && EqMask.Y()));
	EqMask = EqualsMask(A, B);
	CHECK((!EqMask.X() && EqMask.Y()));

	v2 GTMask = GreaterMask(A, B);
	CHECK((GTMask.X() && !GTMask.Y()));

	v2 GEMask = GreaterOrEqualMask(A, B);
	CHECK((GEMask.X() && GEMask.Y()));
	GEMask = GreaterOrEqualMask(C, A);
	CHECK((!GEMask.X() && GEMask.Y()));

	v2 LTMask = LesserMask(C, B);
	CHECK((LTMask.X() && !LTMask.Y()));

	v2 LEMask = LesserOrEqualMask(B, A);
	CHECK((LEMask.X() && LEMask.Y()));
	LEMask = LesserOrEqualMask(C, B);
	CHECK((LEMask.X() && !LEMask.Y()));
}

TEST_CASE("v2d constructors and getters") 
{
	v2d A = V2d(-3.0, 4.0);

	CHECK_VECTOR2_ALL_ALIASES(A, -3.0, 4.0);

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
	CHECK_VECTOR2_ARRAY(Arr, -3.0, 4.0);
	Store(Arr, A);
	CHECK_VECTOR2_ARRAY(Arr, -3.0, 4.0);

	v2d B = V2d(1.0);
	CHECK_VECTOR2(B, 1.0, 1.0);

	v2d C = V2d();
	CHECK_VECTOR2(C, 0.0, 0.0);

	double InitArr[] = {-1.0, 2.0};	
	v2d D = V2dFromMemory(InitArr);
	CHECK_VECTOR2(D, -1.0, 2.0);

	double* PX = Ptr(D);
	double* PY = PtrY(D);
	CHECK(*PX == -1.0);
	CHECK(*PY == 2.0);
}

TEST_CASE("v2d Setters")
{
	v2d A;
	A.SetX(4.0);
	A.SetY(-2.5);
	CHECK_VECTOR2(A, 4.0, -2.5);

	v2d B;
	B.SetY(-2.5);
	B.SetX(4.0);
	CHECK_VECTOR2(B, 4.0, -2.5);
}

TEST_CASE("v2d operations")
{
	v2d A = V2d(2.0, 4.0);	
	v2d B = V2d(-5.0, 3.0);	

	v2d AddRes = A + B; 
	CHECK_VECTOR2(AddRes, -3.0, 7.0);

	v2d SubRes = A - B;
	CHECK_VECTOR2(SubRes, 7.0, 1.0);

	v2d AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK_VECTOR2(AddAsignmentRes, -3.0, 7.0);

	v2d SubAsignmentRes = A;
	SubAsignmentRes -= B;
	CHECK_VECTOR2(SubAsignmentRes, 7.0, 1.0);

	v2d ScalarMulRes1 = A * 4.5;
	CHECK_VECTOR2(ScalarMulRes1, 9.0, 18.0);

	v2d ScalarMulRes2 = 4.5 * A;
	CHECK_VECTOR2(ScalarMulRes2, 9.0, 18.0);

	v2d ScalarDivRes = A / 2.0;
	CHECK_VECTOR2(ScalarDivRes, 1.0, 2.0);

	v2d HadamardMulRes = HadamardMul(A, B);
	CHECK_VECTOR2(HadamardMulRes, -10.0, 12.0);
	
	v2d HadamardDivRes = HadamardDiv(A, B);
	CHECK_VECTOR2_APPROX(HadamardDivRes, 2.0 / -5.0, 4.0 / 3.0);

	v2d NegatedB = -B;
	CHECK_VECTOR2(NegatedB, 5.0, -3.0);

	v2d MinRes = Min(A, B);
	CHECK_VECTOR2(MinRes, -5.0, 3.0);

	v2d MaxRes = Max(A, B);
	CHECK_VECTOR2(MaxRes, 2.0, 4.0);

	v2d AbsoluteB = Abs(B);
	CHECK_VECTOR2(AbsoluteB, 5.0, 3.0);

	v2d NormalizedB = Normalize(B);
	CHECK_VECTOR2_APPROX(NormalizedB, B.X() / sqrt(34), B.Y() / sqrt(34));

	CHECK(Dot(A, B) == 2.0);
	CHECK(SumOfElements(B) == -2.0);
	CHECK(Length(B) == FloatCmp(sqrt(34.0)));
	CHECK(LengthSquared(B) == 34.0);

	v2d Min = V2d(0.0, 0.0);
	v2d Max = V2d(5.0, 7.0);
	v2d ClampRes = Clamp(V2d(-1.0, 8.0), Min, Max);
	CHECK_VECTOR2(ClampRes, 0.0, 7.0);

	v2d C = V2d(0.0, 0.0);
	v2d D = V2d(2.0, 4.0);
	v2d LerpRes = Lerp(C, D, 0.5f);
	CHECK_VECTOR2(LerpRes, 1.0, 2.0);
	LerpRes = Lerp(D, C, 0.5);
	CHECK_VECTOR2(LerpRes, 1.0, 2.0);
}

TEST_CASE("v2d comparisons")
{
	v2d A = V2d(5.0, 5.0);
	v2d B = V2d(3.0, 5.0);
	v2d C = V2d(-2.0, 6.0);

	CHECK(A == A);
	CHECK(A != B);

	v2d EqMask = EqualsMask(A, A);
	CHECK((EqMask.X() && EqMask.Y()));
	EqMask = EqualsMask(A, B);
	CHECK((!EqMask.X() && EqMask.Y()));

	v2d GTMask = GreaterMask(A, B);
	CHECK((GTMask.X() && !GTMask.Y()));

	v2d GEMask = GreaterOrEqualMask(A, B);
	CHECK((GEMask.X() && GEMask.Y()));
	GEMask = GreaterOrEqualMask(C, A);
	CHECK((!GEMask.X() && GEMask.Y()));

	v2d LTMask = LesserMask(C, B);
	CHECK((LTMask.X() && !LTMask.Y()));

	v2d LEMask = LesserOrEqualMask(B, A);
	CHECK((LEMask.X() && LEMask.Y()));
	LEMask = LesserOrEqualMask(C, B);
	CHECK((LEMask.X() && !LEMask.Y()));
}

TEST_CASE("v2i constructors and getters") 
{
	v2i A = V2i(-3, 4);

	CHECK_VECTOR2_ALL_ALIASES(A, -3, 4);

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
	CHECK_VECTOR2_ARRAY(Arr, -3, 4);

	v2i B = V2i(1);
	CHECK_VECTOR2(B, 1, 1);

	v2i C = V2i();
	CHECK_VECTOR2(C, 0, 0);

	int32 InitArr[] = {-1, 2};	
	v2i D = V2iFromMemory(InitArr);
	CHECK_VECTOR2(D, -1, 2);

	int32* PX = Ptr(D);
	int32* PY = PtrY(D);
	CHECK(*PX == -1);
	CHECK(*PY == 2);
}

TEST_CASE("v2i Setters")
{
	v2i A;
	A.SetX(4);
	A.SetY(-2);
	CHECK_VECTOR2(A, 4, -2);

	v2d B;
	B.SetY(-2);
	B.SetX(4);
	CHECK_VECTOR2(B, 4, -2);
}

TEST_CASE("v2i operations")
{
	v2i A = V2i(2, 4);
	v2i B = V2i(-5, 3);

	LOG_VECTOR2(A);
	LOG_VECTOR2(B);
	
	v2i AddRes = A + B;
	CHECK_VECTOR2(AddRes, -3, 7);
	
	v2i SubRes = A - B;
	CHECK_VECTOR2(SubRes, 7, 1);

	v2i AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK_VECTOR2(AddAsignmentRes, -3, 7);

	v2i SubAsignmentRes = A;
	SubAsignmentRes -= B;
	CHECK_VECTOR2(SubAsignmentRes, 7, 1);
	
	v2i ScalarMulRes1 = A * -5;
	CHECK_VECTOR2(ScalarMulRes1, -10, -20);
	
	v2i ScalarMulRes2 = -5 * A;
	CHECK_VECTOR2(ScalarMulRes2, -10, -20);
	
	v2i HadamardMulRes = HadamardMul(A, B); 
	CHECK_VECTOR2(HadamardMulRes, -10, 12);

	v2i NegatedB = -B;
	CHECK_VECTOR2(NegatedB, 5, -3);

	v2i MinRes = Min(A, B);
	CHECK_VECTOR2(MinRes, -5, 3);

	v2i MaxRes = Max(A, B);
	CHECK_VECTOR2(MaxRes, 2, 4);

	v2i AbsoluteB = Abs(B);
	CHECK_VECTOR2(AbsoluteB, 5, 3);

	CHECK(SumOfElements(B) == -2);
	CHECK(Length(B) == (int32)sqrt(34));
	CHECK(LengthSquared(B) == 34);

	v2i Min = V2i(0, 0);
	v2i Max = V2i(5, 2);
	v2i ClampBRes = Clamp(B, Min, Max);
	CHECK_VECTOR2(ClampBRes, 0, 2);
}

TEST_CASE("v2i comparisons")
{
	v2i A = V2i(5, 5);
	v2i B = V2i(3, 5);
	v2i C = V2i(-2, 6);

	CHECK(A == A);
	CHECK(A != B);

	v2i EqMask = EqualsMask(A, A);
	CHECK((EqMask.X() && EqMask.Y()));
	EqMask = EqualsMask(A, B);
	CHECK((!EqMask.X() && EqMask.Y()));

	v2i GTMask = GreaterMask(A, B);
	CHECK((GTMask.X() && !GTMask.Y()));

	v2i GEMask = GreaterOrEqualMask(A, B);
	CHECK((GEMask.X() && GEMask.Y()));
	GEMask = GreaterOrEqualMask(C, A);
	CHECK((!GEMask.X() && GEMask.Y()));

	v2i LTMask = LesserMask(C, B);
	CHECK(LTMask.X());
	CHECK(!LTMask.Y());

	v2i LEMask = LesserOrEqualMask(B, A);
	CHECK((LEMask.X() && LEMask.Y()));
	LEMask = LesserOrEqualMask(C, B);
	CHECK((LEMask.X() && !LEMask.Y()));
}

TEST_CASE("v2u constructors and getters") 
{
	v2u A = V2u(3, 4);

	CHECK_VECTOR2_ALL_ALIASES(A, 3, 4);

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

	v2u B = V2u(1);
	CHECK_VECTOR2(B, 1, 1);

	uint32 Arr[2];
	Store(Arr, A);
	CHECK_VECTOR2_ARRAY(Arr, 3, 4);

	v2u C = V2u(-2, 3);
	CHECK_VECTOR2(C, -2, 3);

	v2u D = V2u();
	CHECK_VECTOR2(D, 0, 0);

	uint32 InitArr[] = {1, 2};	
	v2u E = V2uFromMemory(InitArr);
	CHECK_VECTOR2(E, 1, 2);

	uint32* PX = Ptr(E);
	uint32* PY = PtrY(E);
	CHECK(*PX == 1);
	CHECK(*PY == 2);
}

TEST_CASE("v2u Setters")
{
	v2u A;
	A.SetX(4);
	A.SetY(2);
	CHECK_VECTOR2(A, 4, 2);

	v2u B;
	B.SetY(2);
	B.SetX(4);
	CHECK_VECTOR2(B, 4, 2);
}

TEST_CASE("v2u operations")
{
	v2u A = V2u(5, 4);
	v2u B = V2u(1, 3);

	v2u AddAsignmentRes = A;
	AddAsignmentRes += B;
	CHECK_VECTOR2(AddAsignmentRes, 6, 7);

	v2u SubAsignmentRes = A;
	SubAsignmentRes -= B;
	CHECK_VECTOR2(SubAsignmentRes, 4, 1);
	
	v2u ScalarMulRes1 = A * 5;
	CHECK_VECTOR2(ScalarMulRes1, 25, 20);
	
	v2u ScalarMulRes2 = 5 * A;
	CHECK_VECTOR2(ScalarMulRes2, 25, 20);
	
	v2u HadamardMulRes = HadamardMul(A, B); 
	CHECK_VECTOR2(HadamardMulRes, 5, 12);

	v2u MinRes = Min(A, B);
	CHECK_VECTOR2(MinRes, 1, 3);

	v2u MaxRes = Max(A, B);
	CHECK_VECTOR2(MaxRes, 5, 4);

	CHECK(SumOfElements(B) == 4);
	CHECK(Length(B) == (uint32)sqrt(10));
	CHECK(LengthSquared(B) == 10);

	v2u Min = V2u(2, 0);
	v2u Max = V2u(5, 3);
	v2u ClampBRes = Clamp(B, Min, Max);
	CHECK_VECTOR2(ClampBRes, 2, 3);
}

TEST_CASE("v2u comparisons")
{
	v2u A = V2u(5, 5);
	v2u B = V2u(3, 5);
	v2u C = V2u(-2, 6);

	CHECK(A == A);
	CHECK(A != B);

	v2u EqMask = EqualsMask(A, A);
	CHECK((EqMask.X() && EqMask.Y()));
	EqMask = EqualsMask(A, B);
	CHECK((!EqMask.X() && EqMask.Y()));

	v2u GTMask = GreaterMask(A, B);
	CHECK((GTMask.X() && !GTMask.Y()));

	v2u GEMask = GreaterOrEqualMask(A, B);
	CHECK((GEMask.X() && GEMask.Y()));
	GEMask = GreaterOrEqualMask(C, A);
	CHECK((!GEMask.X() && GEMask.Y()));

	v2u LTMask = LesserMask(C, B);
	CHECK(LTMask.X());
	CHECK(!LTMask.Y());

	v2u LEMask = LesserOrEqualMask(B, A);
	CHECK((LEMask.X() && LEMask.Y()));
	LEMask = LesserOrEqualMask(C, B);
	CHECK((LEMask.X() && !LEMask.Y()));
}


