
TEST_CASE_TEMPLATE("v3 construction and getters", t, NUMERICAL_TYPES)
{
	CHECK_V3_ALL_ALIASES(v3_base<t>(1, 2, 3), 1, 2, 3);
	CHECK_V3(v3_base<t>(2), 2, 2, 2);
	CHECK_V3(v3_base<t>{}, 0, 0, 0);

	t Arr[3] = {1, 2, 3};
	CHECK_V3(v3_base<t>(Arr), 1, 2, 3);

	Store(Arr, v3_base<t>(4, 5, 6));
	CHECK_ARRAY3(Arr, 4, 5, 6);

	v3_base<t> P = {1, 2, 3};
	CHECK(*Ptr(P) == 1);
	CHECK(*PtrY(P) == 2);
	CHECK(*PtrZ(P) == 3);
	CHECK(P[0] == 1);
	CHECK(P[1] == 2);
	CHECK(P[2] == 3);
}

TEST_CASE_TEMPLATE("v3 base some operations", t, NUMERICAL_TYPES)
{
	v3_base<t> A(1, 2, 3);
	v3_base<t> B(4, 5, 6);

	CHECK_V3(A + B, 5, 7, 9);
	CHECK_V3(B - A, 3, 3, 3);
	CHECK_V3(HadamardMul(A, B), 4, 10, 18);
}

TEST_CASE("v3 operations")
{
	v3 A(2, 3, 4);
	v3 B(-2, 5, 1);

	CHECK_V3(A + B, 0, 8, 5);
	CHECK_V3(A - B, 4, -2, 3);
	CHECK_V3(A * 3.f, 6, 9, 12);
	CHECK_V3(3.f * A, 6, 9, 12);
	CHECK_V3(A / 2.f, 1, 1.5f, 2);
	CHECK_V3(HadamardMul(A, B), -4, 15, 4);
	CHECK_V3(HadamardDiv(A, B), -1, 3.f/5.f, 4);
	CHECK_V3(-B, 2, -5, -1);
	CHECK_V3(Min(A, B), -2, 3, 1);
	CHECK_V3(Max(A, B), 2, 5, 4);
	CHECK_V3(Abs(B), 2, 5, 1);
	CHECK_V3_APPROX(Normalize(B), B.X / sqrt(30), B.Y / sqrt(30), B.Z / sqrt(30));
	CHECK_V3(Cross(v3(1, 0, 0), v3(0, 1, 0)), 0, 0, 1);
	CHECK_V3(Cross(v3(2, 3, 4), v3(5, 6, 7)), -3, 6, -3);
	CHECK(Dot(A, B) == 15);
	CHECK(SumOfElements(B) == 4);
	CHECK(Length(B) == FloatCmp(sqrt(30)));
	CHECK(LengthSquared(B) == 30);
	CHECK_V3(Clamp(B, v3(-1, 7, -5), v3(4, 8, -1)), -1, 7, -1);
	CHECK_V3(Lerp(v3(0, 2, 3), v3(4, 5, 6), 0.5f), 2, 3.5f, 4.5f);
	CHECK_V3(Lerp(v3(4, 5, 6), v3(0, 2, 3), 0.5f), 2, 3.5f, 4.5f);
	CHECK(A == A);
	CHECK(A != B);

	v3 C = A;
	C += B;
	CHECK_V3(C, 0, 8, 5); 

	v3 D = A;
	D -= B;
	CHECK_V3(D, 4, -2, 3); 

	v3 E(2, 3, -4);
	E *= 2.f;
	CHECK_V3(E, 4, 6, -8);

	v3 G(3, 2, -1);
	G /= 2.f;
	CHECK_V3(G, 1.5f, 1, -0.5f);

	v3 F(-2, 5, 1);
	Normalize(&F);
	CHECK_V3_APPROX(F, F.X / Length(F), F.Y / Length(F), F.Z / Length(F));
}

