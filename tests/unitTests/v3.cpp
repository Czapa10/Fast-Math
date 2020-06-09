
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
	CHECK(P[0] == 1.f);
	CHECK(P[1] == 2.f);
	CHECK(P[2] == 3.f);
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

	v3 C = A;
	C += B;
	CHECK_V3(C, 0.f, 8.f, 5.f); 

	v3 D = A;
	D -= B;
	CHECK_V3(D, 4.f, -2.f, 3.f); 

	v3 E = V3(2.f, 3.f, -4.f);
	E *= 2.f;
	CHECK_V3(E, 4.f, 6.f, -8.f);

	v3 G = V3(3.f, 2.f, -1.f);
	G /= 2.f;
	CHECK_V3(G, 1.5f, 1.f, -0.5f);

	v3 F = V3(-2.f, 5.f, 1.f);
	Normalize(&F);
	CHECK_V3_APPROX(F, F.X / Length(F), F.Y / Length(F), F.Z / Length(F));
}
