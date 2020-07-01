
TEST_CASE("v4 construction and getters") 
{
	v4 A = V4(1.f, 2.f, 3.f, 4.f);
	CHECK_V4_ALL_ALIASES(A, 1.f, 2.f, 3.f, 4.f);

	float Storage[4];
	Store(Storage, A);
	CHECK_ARRAY4(Storage, 1.f, 2.f, 3.f, 4.f);

	CHECK_V4(V4(5.f), 5.f, 5.f, 5.f, 5.f); 
	CHECK_V4(V4(), 0.f, 0.f, 0.f, 0.f); 

	float Arr[4] = {1.f, 2.f, 3.f, 4.f};
	CHECK_V4(V4FromMemory(Arr), 1.f, 2.f, 3.f, 4.f);

	v4 B = V4(v3(1, 2, 3), 4.f);
	CHECK_V4(B, 1.f, 2.f, 3.f, 4.f);

	CHECK(*Ptr(B) == 1.f);
	CHECK(*PtrY(B) == 2.f);
	CHECK(*PtrZ(B) == 3.f);
	CHECK(*PtrW(B) == 4.f);
	CHECK(B[0] == 1.f);
	CHECK(B[1] == 2.f);
	CHECK(B[2] == 3.f);
	CHECK(B[3] == 4.f);
}

TEST_CASE("v4 operations")
{
	v4 A = V4(1.f, 3.f, 5.f, -7.f);
	v4 B = V4(2.f, 4.f, -6.f, 8.f);

	CHECK_V4(A + B, 3.f, 7.f, -1.f, 1.f);
	CHECK_V4(A - B, -1.f, -1.f, 11.f, -15.f);

	CHECK_V4(A * 2.f, 2.f, 6.f, 10.f, -14.f);
	CHECK_V4(2.f * A, 2.f, 6.f, 10.f, -14.f);
	CHECK_V4(A / 2.f, 0.5f, 1.5f, 2.5f, -3.5f);
	CHECK_V4(HadamardMul(A, B), 2.f, 12.f, -30.f, -56.f);
	CHECK_V4_APPROX(HadamardDiv(A, B), 0.5f, 0.75f, -0.83, -0.875);
	CHECK_V4(-B, -2.f, -4.f, 6.f, -8.f);
	CHECK_V4(Min(A, B), 1.f, 3.f, -6.f, -7.f);
	CHECK_V4(Max(A, B), 2.f, 4.f, 5.f, 8.f);
	CHECK_V4(Abs(B), 2.f, 4.f, 6.f, 8.f);
	CHECK_V4_APPROX(Normalize(B), B.X / sqrt(120), B.Y / sqrt(120), B.Z / sqrt(120), B.W / sqrt(120));

	CHECK(Dot(A, B) == -72.f);
	CHECK(SumOfElements(B) == 8.f);
	CHECK(Length(B) == FloatCmp(sqrt(120.f)));
	CHECK(LengthSquared(B) == 120.f);

	CHECK(A == A);
	CHECK(A != B);

	v4 C = V4(1.f, 3.f, 5.f, -7.f);
	v4 Min = V4(2.f, 2.f, 2.f, 2.f);
	v4 Max = V4(5.f, 5.f, 3.f, 2.f);
	CHECK_V4(Clamp(C, Min, Max), 2.f, 3.f, 3.f, 2.f);

	v4 G = V4(0.f, 2.f, 3.f, 0.f);
	v4 H = V4(4.f, 5.f, 6.f, 100.f);
	CHECK_V4(Lerp(G, H, 0.5f), 2.f, 3.5f, 4.5f, 50.f);
	CHECK_V4(Lerp(H, G, 0.5f), 2.f, 3.5f, 4.5f, 50.f);

	v4 I = A;
	I += B;
	CHECK_V4(I, 3.f, 7.f, -1.f, 1.f);

	v4 J = A;
	J -= B;
	CHECK_V4(J, -1.f, -1.f, 11.f, -15.f);

	v4 K = V4(2.f, 3.f, -4.f, -5.f);
	K *= 2.f;
	CHECK_V4(K, 4.f, 6.f, -8.f, -10.f);

	v4 L = V4(3.f, 2.f, -1.f, -0.5f);
	L /= 2.f;
	CHECK_V4(L, 1.5f, 1.f, -0.5f, -0.25f);

	v4 M = V4(2.f, 4.f, -6.f, 8.f);
	Normalize(&M);
	CHECK_V4_APPROX(M, M.X / Length(M), M.Y / Length(M), M.Z / Length(M), M.W / Length(M));
}

