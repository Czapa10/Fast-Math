
TEST_CASE_TEMPLATE("v2_base constructors and getters", t, NUMERICAL_TYPES)
{
	CHECK_V2_ALL_ALIASES(v2_base<t>(3, 4), 3, 4);
	CHECK_V2(v2_base<t>(5), 5, 5);
	CHECK_V2(v2_base<t>{}, 0, 0);

	t Arr[2] = {1, 2};
	CHECK_V2(v2_base<t>(Arr), 1, 2);

	Store(Arr, v2_base<t>(1, 3));
	CHECK_ARRAY2(Arr, 1, 3);

	v2_base<t> P = {1, 2};
	CHECK(*Ptr(P) == 1.f);
	CHECK(*PtrY(P) == 2.f);
	CHECK(P[0] == 1);
	CHECK(P[1] == 2);
}

TEST_CASE("v2 cast constructors")
{
	CHECK_V2(v2(v2i(1, 2)), 1, 2);
	CHECK_V2(v2(uint32_t(1)), 1, 1);
}

TEST_CASE_TEMPLATE("v2_base some operations", t, NUMERICAL_TYPES)
{
	v2_base<t> A(1, 2);
	v2_base<t> B(3, 4);

	CHECK_V2(A + B, 4, 6);
	CHECK_V2(B - A, 2, 2);
	CHECK_V2(HadamardMul(A, B), 3, 8);
}

TEST_CASE("v2 operations")
{
	v2 A(2, 4);
	v2 B(-5, 3);

	CHECK_V2(A + B, -3, 7);
	CHECK_V2(A - B, 7, 1);
	CHECK_V2(A * 2.f, 4, 8);
	CHECK_V2(2.f * A, 4, 8);
	CHECK_V2(A / 2.f, 1, 2);
	CHECK_V2(HadamardMul(A, B), -10, 12);
	CHECK_V2(HadamardDiv(A, B), 2.f / -5.f, 4.f / 3.f);
	CHECK_V2(SafeHadamardDivN(A, B, v2(5)), 2.f / -5.f, 4.f / 3.f);
	CHECK_V2(SafeHadamardDivN(A, v2(1, 0), v2(5)), 2, 5);
	CHECK_V2(SafeHadamardDivN(A, v2(0, 1), v2(11, 5)), 11, 4);
	CHECK_V2(SafeHadamardDivN(A, v2(0.f), v2(11, 5)), 11, 5);
	CHECK_V2(SafeHadamardDiv1(A, B), 2.f / -5.f, 4.f / 3.f);
	CHECK_V2(SafeHadamardDiv1(A, v2(0.f)), 1, 1);
	CHECK_V2(SafeHadamardDiv0(A, B), 2.f / -5.f, 4.f / 3.f);
	CHECK_V2(SafeHadamardDiv0(A, v2(0.f)), 0, 0);
	CHECK_V2(-B, 5.f, -3.f);
	CHECK_V2(Min(A, B), -5.f, 3.f);
	CHECK_V2(Max(A, B), 2.f, 4.f);
	CHECK_V2(Abs(B), 5.f, 3.f);
	CHECK_V2(Normalize(B), B.X / sqrt(34.f), B.Y / sqrt(34.f));
	CHECK_V2(Clamp(B, v2(), v2(5.f, 2.f)), 0.f, 2.f);
	CHECK_V2(Lerp(v2(), v2(2.f, 4.f), 0.5f), 1.f, 2.f);
	CHECK_V2(Lerp(v2(2.f, 4.f), v2(), 0.5f), 1.f, 2.f);
	CHECK(Dot(A, B) == 2.f);
	CHECK(SumOfElements(B) == -2.f);
	CHECK(Length(B) == FloatCmp(sqrt(34.f)));
	CHECK(LengthSquared(B) == 34.f);
	CHECK(A == A);
	CHECK(A != B);

	v2 C = A;
	C += B;
	CHECK_V2(C, -3.f, 7.f);

	v2 D = A;
	D -= B;
	CHECK_V2(D, 7.f, 1.f);

	v2 E(2.f, -3.f);
	E *= 2.f;
	CHECK_V2(E, 4.f, -6.f);

	v2 G(3.f, -2.f);
	G /= 2.f;
	CHECK_V2(G, 1.5f, -1.f);

	v2 F(-5.f, 3.f);
	Normalize(&F);
	CHECK_V2(F, F.X / Length(F), F.Y / Length(F));
}

