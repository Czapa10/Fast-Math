
TEST_CASE("utility functions")
{
	{
		CHECK(5.f == Min(5.f, 10.f));
		CHECK(5.f == Max(5.f, -1.f));
		CHECK(5.0 == Min(5.0, 10.0));
		CHECK(5.0 == Max(5.0, -1.0));
		CHECK(5 == Min(5, 10));
		CHECK(5 == Max(5, -1));
		CHECK(5u == Min(5u, 10u));
		CHECK(5u == Max(5u, 0u));
	}

	{
		CHECK(5.f == Abs(5.f));
		CHECK(5.f == Abs(-5.f));
		CHECK(5.0 == Abs(5.0));
		CHECK(5.0 == Abs(-5.0));
		CHECK(5 == Abs(5));
		CHECK(5 == Abs(-5));

		float A = 5.f;
		Abs(&A);
		CHECK(A == 5.f);

		float B = -5.f;
		Abs(&B);
		CHECK(B == 5.f);

		double C = 5.0;
		Abs(&C);
		CHECK(C == 5.0);

		double D = -5.0;
		Abs(&D);
		CHECK(D == 5.0);

		int32_t E = 5;
		Abs(&E);
		CHECK(E == 5);

		int32_t F = -5;
		Abs(&F);
		CHECK(F == 5);
	}

	{
		CHECK(Square(2.f) == 4.f);
		CHECK(Square(-2.0) == 4.0);
		CHECK(Square(-2) == 4);
		CHECK(Square(2u + 2u) == 16u);

		float A = 5.f;
		Square(&A);
		CHECK(A == 25.f);

		double B = -3.0;
		Square(&B);
		CHECK(B == 9.0);

		int32_t C = 4;
		Square(&C);
		CHECK(C == 16);

		uint32_t D = 6;
		Square(&D);
		CHECK(D == 36);
	}

	{
		CHECK(IsWithinRange(1, 2, 3));
		CHECK(!IsWithinRange(5u, 2u, 3u));
		CHECK(!IsWithinRange(10.f, 12.f, 11.f));
		CHECK(!IsWithinRange(15.f, 10.f, 5.f));
	}

	{
		CHECK(DegreesToRadians(30.f) == FloatCmp(0.5235f));
		CHECK(DegreesToRadians(30.0) == FloatCmp(0.5235));
		CHECK(RadiansToDegrees(0.5235f) == FloatCmp(30.f));
		CHECK(RadiansToDegrees(0.5235) == FloatCmp(30.0));
	}

	{
		CHECK(SafeDivN(1.f, 0.f, 5.f) == 5.f);
		CHECK(SafeDivN(1.f, 2.f, 5.f) == 0.5f);
		CHECK(SafeDivN(4, 0, 5) == 5);
		CHECK(SafeDivN(4, 2, 5) == 2);

		CHECK(SafeDiv1(4.f, 0.f) == 1.f);
		CHECK(SafeDiv1(1.f, 2.f) == 0.5f);
		CHECK(SafeDiv1(4, 0) == 1);
		CHECK(SafeDiv1(4, 2) == 2);

		CHECK(SafeDiv0(4.f, 0.f) == 0.f);
		CHECK(SafeDiv0(1.f, 2.f) == 0.5f);
		CHECK(SafeDiv0(4, 0) == 0);
		CHECK(SafeDiv0(4, 2) == 2);
	}

	{
		f32 F = 5;
		Negate(&F);
		CHECK(F == -5);
		Negate(&F);
		CHECK(F == 5);

		i32 I = -22;
		Negate(&I);
		CHECK(I == 22);
		Negate(&I);
		CHECK(I == -22);

		v2 V(-5, 10);
		Negate(&V);
		CHECK_V2(V, 5, -10);
		Negate(&V);
		CHECK_V2(V, -5, 10);
	}
}
