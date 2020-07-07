
TEST_CASE("rect2 construction")
{
	rect2 Rf32 = Rect2MinMax(-1.5f, 2.5f, 3, 4);
	rect2d Rf64 = Rect2dMinMax(-1.5, 2.5, 3, 4);
	rect2i Ri32 = Rect2iMinMax(-1, 2, 3, 4);
	rect2u Ru32 = Rect2uMinMax(1, 2, 3, 4);
	rect2i64 Ri64 = Rect2i64MinMax(-1, 2, 3, 4);
	rect2u64 Ru64 = Rect2u64MinMax(1, 2, 3, 4);
	rect2i16 Ri16 = Rect2i16MinMax(-1, 2, 3, 4);
	rect2u16 Ru16 = Rect2u16MinMax(1, 2, 3, 4);
	rect2i8 Ri8 = Rect2i8MinMax(-1, 2, 3, 4);
	rect2u8 Ru8 = Rect2u8MinMax(1, 2, 3, 4);

	CHECK_RECT2(Rf32, -1.5f, 2.5f, 3.f, 4.f);
	CHECK_RECT2(Rf64, -1.5, 2.5, 3.0, 4.0);
	CHECK_RECT2(Ri32, -1, 2, 3, 4);
	CHECK_RECT2(Ru32, 1, 2, 3, 4);
	CHECK_RECT2(Ri64, -1, 2, 3, 4);
	CHECK_RECT2(Ru64, 1, 2, 3, 4);
	CHECK_RECT2(Ri16, -1, 2, 3, 4);
	CHECK_RECT2(Ru16, 1, 2, 3, 4);
	CHECK_RECT2(Ri8, -1, 2, 3, 4);
	CHECK_RECT2(Ru8, 1, 2, 3, 4);

	CHECK_RECT2(Rect2MinMax(v2(-1.5f, 2.5f), v2(3, 4)), -1.5f, 2.5f, 3, 4);
	CHECK_RECT2(Rect2iMinMax(v2i(-1, 2), v2i(3, 4)), -1, 2, 3, 4);

	CHECK_RECT2(Rect2MinDim(-1.5f, 2.5f, 3, 4), -1.5f, 2.5f, 1.5f, 6.5f);
	CHECK_RECT2(Rect2iMinDim(-1, 2, 3, 4), -1, 2, 2, 6);

	CHECK_RECT2(Rect2MinDim(v2(-1.5f, 2.5f), v2(3, 4)), -1.5f, 2.5f, 1.5f, 6.5f);
	CHECK_RECT2(Rect2iMinDim(v2i(-1, 2), v2i(3, 4)), -1, 2, 2, 6);
}

TEST_CASE_TEMPLATE("rect2_base getters", t, NUMERICAL_TYPES)
{
	auto R = Rect2BaseMinDim<t>(10, 5, 10, 20);
	CHECK(R.Width() == 10);
	CHECK(R.Height() == 20);
	CHECK(R.W() == 10);
	CHECK(R.H() == 20);
	CHECK_V2(R.Dim(), 10, 20);
	CHECK_V2(R.Center(), 15, 15);
	CHECK_V2(R.MaxXMinY(), 20, 5);
	CHECK_V2(R.MinXMaxY(), 10, 25);
	CHECK_V2(R.MinYCenter(), 15, 5);
	CHECK_V2(R.MaxYCenter(), 15, 25);
	CHECK_V2(R.MinXCenter(), 10, 15);
	CHECK_V2(R.MaxXCenter(), 20, 15);
}

TEST_CASE_TEMPLATE("rect2_base setters", t, NUMERICAL_TYPES)
{
	auto A = Rect2BaseMinMax<t>(5, 0, 15, 30);
	A.SetCenter(15, 15);
	CHECK_RECT2(A, 10, 0, 20, 30);

	auto B = Rect2BaseMinMax<t>(20, 20, 30, 30);
	B.SetCenter(v2_base<t>(10, 10));
	CHECK_RECT2(B, 5, 5, 15, 15);

	auto C = Rect2BaseMinMax<t>(10, 10, 20, 20);

	C.SetSizeWithFixedCenter(20, 20);
	CHECK_RECT2(C, 5, 5, 25, 25);

	C.SetSizeWithFixedMin(15, 15);
	CHECK_RECT2(C, 5, 5, 20, 20);

	C.SetSizeWithFixedMax(10, 10);
	CHECK_RECT2(C, 10, 10, 20, 20);
	C.SetSizeWithFixedMax(v2_base<t>(5, 5));
	CHECK_RECT2(C, 15, 15, 20, 20);

	C = Offset(C, v2_base<t>(10, 10));
	CHECK_RECT2(C, 25, 25, 30, 30);
	Offset(&C, v2_base<t>(20, 20));
	CHECK_RECT2(C, 45, 45, 50, 50);
}

TEST_CASE_TEMPLATE("rect2_base intersections and comparisons", t, NUMERICAL_TYPES)
{
	auto A = Rect2BaseMinMax<t>(0, 0, 10, 10);
	auto B = Rect2BaseMinMax<t>(5, 5, 10, 15);
	auto C = Rect2BaseMinDim<t>(20, 5, 10, 10);
	auto C2 = Rect2BaseMinDim<t>(20, 5, 10, 10);
	auto C3 = Rect2BaseMinDim<t>(25, 10, 2, 2);

	auto P = v2_base<t>(4, 6);

	CHECK(Intersect(A, B));
	CHECK(!Intersect(A, C));
	CHECK(!Intersect(B, C));

	CHECK(Intersect(A, P));
	CHECK(!Intersect(B, P));
	CHECK(!Intersect(C, P));

	CHECK(Intersect(C, C2));
	CHECK(FullyIntersect(C, C2));
	CHECK(Intersect(C, C3));
	CHECK(FullyIntersect(C, C3));

	CHECK(A != B);
	CHECK(C == C2);
	CHECK(C != C3);
}

