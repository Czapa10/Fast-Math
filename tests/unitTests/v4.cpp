
// TODO: AllComponents... and OnlyOneComponent...

TEST_CASE_TEMPLATE("v4_construction and getters", t, NUMERICAL_TYPES) 
{
	CHECK_V4_ALL_ALIASES(v4_base<t>(1, 2, 3, 4), 1, 2, 3, 4);
	CHECK_V4(v4_base<t>(v2_base<t>(1, 2), v2_base<t>(3, 4)), 1, 2, 3, 4);
	CHECK_V4(v4_base<t>(v3_base<t>(1, 2, 3), 4), 1, 2, 3, 4);
	CHECK_V4(v4_base<t>(1, v3_base<t>(2, 3, 4)), 1, 2, 3, 4);
	CHECK_V4(v4_base<t>(5), 5, 5, 5, 5);
	CHECK_V4(v4_base<t>(v3_base<t>(1, 2, 3), 4), 1, 2, 3, 4);
	CHECK_V4(v4_base<t>{}, 0, 0, 0, 0);

	t Arr[4] = {1, 2, 3, 4};
	CHECK_V4(v4_base<t>(Arr), 1, 2, 3, 4);

	Store(Arr, v4_base<t>(5, 6, 7, 8));
	CHECK_ARRAY4(Arr, 5, 6, 7, 8);

	v4_base<t> P = {1, 2, 3, 4};
	CHECK(*Ptr(P) == 1);
	CHECK(*PtrY(P) == 2);
	CHECK(*PtrZ(P) == 3);
	CHECK(*PtrW(P) == 4);
	CHECK(P[0] == 1);
	CHECK(P[1] == 2);
	CHECK(P[2] == 3);
	CHECK(P[3] == 4);
}

TEST_CASE("v4 cast constructors")
{
	CHECK_V4(v4(v4i(1, 2, 3, 4)), 1, 2, 3, 4);
	CHECK_V4(v4(uint32_t(1)), 1, 1, 1, 1);
}

TEST_CASE_TEMPLATE("v4_base some operations", t, NUMERICAL_TYPES)
{
	v4_base<t> A(1, 2, 3, 4);
	v4_base<t> B(5, 6, 7, 8);

	CHECK_V4(A + B, 6, 8, 10, 12);
	CHECK_V4(B - A, 4, 4, 4, 4);
	CHECK_V4(HadamardMul(A, B), 5, 12, 21, 32);
}

TEST_CASE("v4 operations")
{
	v4 A(1, 3, 5, -7);
	v4 B(2, 4, -6, 8);

	CHECK_V4(A + B, 3, 7, -1, 1);
	CHECK_V4(A - B, -1, -1, 11, -15);
	CHECK_V4(AddX(A, 2.f), 3, 3, 5, -7);
	CHECK_V4(AddY(A, 2.f), 1, 5, 5, -7);
	CHECK_V4(AddZ(A, -2.f), 1, 3, 3, -7);
	CHECK_V4(AddW(A, 2.f), 1, 3, 5, -5);
	CHECK_V4(MulX(A, 2.f), 2, 3, 5, -7);
	CHECK_V4(MulY(A, 2.f), 1, 6, 5, -7);
	CHECK_V4(MulZ(A, -2.f), 1, -6, 5, -7);
	CHECK_V4(MulW(A, 2.f), 1, 3, 5, -14);
	CHECK_V4(DivX(A, 2.f), 0.5f, 3, 5, -7);
	CHECK_V4(DivY(A, 3.f), 1, 1, 5, -7);
	CHECK_V4(DivZ(A, -2.f), 1, 3, -2.5f, -7);
	CHECK_V4(DivW(A, -7.f), 1, 3, 5, 1);
	CHECK_V4(A * 2.f, 2, 6, 10, -14);
	CHECK_V4(2.f * A, 2, 6, 10, -14);
	CHECK_V4(A / 2.f, 0.5f, 1.5f, 2.5f, -3.5f);
	CHECK_V4(HadamardMul(A, B), 2, 12, -30, -56);
	CHECK_V4(HadamardDiv(A, B), 0.5f, 0.75f, 5.f/-6.f, -7.f/8.f);
	CHECK_V4(SafeHadamardDivN(A, B, v4(5)), 0.5f, 0.75f, 5.f/-6.f, -7.f/8.f);
	CHECK_V4(SafeHadamardDivN(A, v4(1, 0, 0, 1), v4(5)), 1, 5, 5, -7.f);
	CHECK_V4(SafeHadamardDivN(A, v4(0, 1, 1, 0), v4(5)), 5, 3, 5, 5);
	CHECK_V4(SafeHadamardDivN(A, v4(0.f), v4(11, 10, 9, 8)), 11, 10, 9, 8);
	CHECK_V4(SafeHadamardDiv1(A, B), 0.5f, 0.75f, 5.f/-6.f, -7.f/8.f);
	CHECK_V4(SafeHadamardDiv1(A, v4(0.f)), 1, 1, 1, 1);
	CHECK_V4(SafeHadamardDiv0(A, B), 0.5f, 0.75f, 5.f/-6.f, -7.f/8.f);
	CHECK_V4(SafeHadamardDiv0(A, v4(0.f)), 0, 0, 0, 0);
	CHECK_V4(-B, -2, -4, 6, -8);
	CHECK_V4(Min(A, B), 1, 3, -6, -7);
	CHECK_V4(Max(A, B), 2, 4, 5, 8);
	CHECK_V4(Abs(B), 2, 4, 6, 8);
	CHECK_V4_APPROX(Normalize(B), B.X / sqrt(120), B.Y / sqrt(120), B.Z / sqrt(120), B.W / sqrt(120));

	CHECK(Dot(A, B) == -72);
	CHECK(SumOfElements(B) == 8);
	CHECK(Length(B) == FloatCmp(sqrt(120)));
	CHECK(LengthSquared(B) == 120);

	CHECK(A == A);
	CHECK(A != B);

	v4 C(1, 3, 5, -7);
	v4 Min(2, 2, 2, 2);
	v4 Max(5, 5, 3, 2);
	CHECK_V4(Clamp(C, Min, Max), 2, 3, 3, 2);

	v4 G(0, 2, 3, 0);
	v4 H(4, 5, 6, 100);
	CHECK_V4(Lerp(G, H, 0.5f), 2, 3.5f, 4.5f, 50);
	CHECK_V4(Lerp(H, G, 0.5f), 2, 3.5f, 4.5f, 50);

	v4 I = A;
	I += B;
	CHECK_V4(I, 3, 7, -1, 1);

	v4 J = A;
	J -= B;
	CHECK_V4(J, -1, -1, 11, -15);

	v4 K(2, 3, -4, -5);
	K *= 2.f;
	CHECK_V4(K, 4, 6, -8, -10);

	v4 L(3, 2, -1, -0.5f);
	L /= 2.f;
	CHECK_V4(L, 1.5f, 1, -0.5f, -0.25f);

	v4 M(2, 4, -6, 8);
	Normalize(&M);
	CHECK_V4_APPROX(M, M.X / Length(M), M.Y / Length(M), M.Z / Length(M), M.W / Length(M));
}

