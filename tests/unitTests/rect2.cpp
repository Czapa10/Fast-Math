
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

	CHECK_RECT2(Rect2DimMax(v2(5.5f, 2.5f), v2(3, 4)), -2.5f, 1.5f, 3, 4);
	CHECK_RECT2(Rect2iDimMax(v2i(1, 2), v2i(3, 4)), 2, 2, 3, 4);

	CHECK_RECT2(Rect2CenterRadius(v2(5, 3), 2), 3, 1, 7, 5);
	CHECK_RECT2(Rect2iCenterRadius(v2i(5, 3), 2), 3, 1, 7, 5);

	CHECK_RECT2(Rect2CenterRadius(v2(5, 3), v2(2, 1)), 3, 2, 7, 4);
	CHECK_RECT2(Rect2iCenterRadius(v2i(5, 3), v2i(2, 1)), 3, 2, 7, 4);

	CHECK_RECT2(Rect2CenterDim(v2(5, 3), 1), 4.5f, 2.5f, 5.5f, 3.5f);
	CHECK_RECT2(Rect2iCenterDim(v2i(5, 3), 2), 4, 2, 6, 4);

	CHECK_RECT2(Rect2CenterDim(v2(5, 3), v2(2, 1)), 4, 2.5f, 6, 3.5f);
	CHECK_RECT2(Rect2iCenterDim(v2i(5, 3), v2i(4, 2)), 3, 2, 7, 4);

	CHECK_RECT2(Rect2Dim(v2(5, 3.2f)), 0, 0, 5, 3.2f);
	CHECK_RECT2(Rect2iDim(v2i(5, 3)), 0, 0, 5, 3);
}

TEST_CASE_TEMPLATE("rect2_base getters", t, NUMERICAL_TYPES_MIN_16_BYTES)
{
	auto R = Rect2BaseMinDim<t>(10, 5, 10, 20);
	CHECK(GetWidth(R) == 10);
	CHECK(GetHeight(R) == 20);
	CHECK(GetW(R) == 10);
	CHECK(GetH(R) == 20);
	CHECK_V2(GetDim(R), 10, 20);
	CHECK(GetArea(R) == 200);
	CHECK_V2(GetCenter(R), 15, 15);
	CHECK_V2(GetMaxXMinY(R), 20, 5);
	CHECK_V2(GetMinXMaxY(R), 10, 25);
	CHECK_V2(GetMinYCenter(R), 15, 5);
	CHECK_V2(GetMaxYCenter(R), 15, 25);
	CHECK_V2(GetMinXCenter(R), 10, 15);
	CHECK_V2(GetMaxXCenter(R), 20, 15);
	CHECK(Ptr(R) == (t*)(&R));
	CHECK_ARRAY4(Ptr(R), 10, 5, 20, 25);
	CHECK_ARRAY2(PtrMax(R), 20, 25);

	auto R2 = Rect2BaseMinDim<t>(1, 4, 0, 0);
	auto R3 = Rect2BaseMinDim<t>(2, 3, 4, 0);
	auto R4 = Rect2BaseMinMax<t>(12, 13, 2, 3);
	CHECK(HasArea(R));
	CHECK(!HasArea(R2));
	CHECK(!HasArea(R3));
	CHECK(!HasArea(R4));
	CHECK(HasAreaFlipAllowed(R));
	CHECK(!HasAreaFlipAllowed(R2));
	CHECK(!HasAreaFlipAllowed(R3));
	CHECK(HasAreaFlipAllowed(R4));

	FM_Rect2ToMinMax(R, Min, Max);
	CHECK_V2(Min, 10, 5);
	CHECK_V2(Max, 20, 25);

	FM_Rect2ToMinDim(R, Min2, Dim);
	CHECK_V2(Min2, 10, 5);
	CHECK_V2(Dim, 10, 20);
}

TEST_CASE_TEMPLATE("rect2_base setters", t, NUMERICAL_TYPES)
{
	auto A = Rect2BaseMinMax<t>(5, 0, 15, 30);
	CHECK_RECT2(SetCenter(A, (t)15, (t)15), 10, 0, 20, 30);
	SetCenter(&A, (t)15, (t)15);
	CHECK_RECT2(A, 10, 0, 20, 30);

	auto B = Rect2BaseMinMax<t>(20, 20, 30, 30);
	CHECK_RECT2(SetCenter(B, v2_base<t>(10, 10)), 5, 5, 15, 15);
	SetCenter(&B, v2_base<t>(10, 10));
	CHECK_RECT2(B, 5, 5, 15, 15);

	auto C = Rect2BaseMinMax<t>(10, 10, 20, 20);

	C = SetDimWithFixedCenter(C, (t)20, (t)20);
	CHECK_RECT2(C, 5, 5, 25, 25);

	C = SetDimWithFixedMin(C, (t)15, (t)15);
	CHECK_RECT2(C, 5, 5, 20, 20);

	C = SetDimWithFixedMax(C, (t)10, (t)10);
	CHECK_RECT2(C, 10, 10, 20, 20);
	C = SetDimWithFixedMax(C, v2_base<t>(5, 5));
	CHECK_RECT2(C, 15, 15, 20, 20);

	C = MoveRect(C, v2_base<t>(10, 10));
	CHECK_RECT2(C, 25, 25, 30, 30);

	C = Rect2BaseMinMax<t>(10, 10, 20, 20);

	SetDimWithFixedCenter(&C, (t)20, (t)20);
	CHECK_RECT2(C, 5, 5, 25, 25);

	SetDimWithFixedMin(&C, (t)15, (t)15);
	CHECK_RECT2(C, 5, 5, 20, 20);

	SetDimWithFixedMax(&C, (t)10, (t)10);
	CHECK_RECT2(C, 10, 10, 20, 20);
	SetDimWithFixedMax(&C, v2_base<t>(5, 5));
	CHECK_RECT2(C, 15, 15, 20, 20);

	MoveRect(&C, v2_base<t>(30, 30));
	CHECK_RECT2(C, 45, 45, 50, 50);
}

TEST_CASE_TEMPLATE("rect2_base operations", t, NUMERICAL_TYPES_MIN_16_BYTES)
{
	rect2_base<t> A = Rect2BaseMinMax<t>(2, 3, 4, 5);

	A = A * (t)2;
	CHECK_RECT2(A, 4, 6, 8, 10);

	A = A / (t)2;
	CHECK_RECT2(A, 2, 3, 4, 5);


	rect2_base<t> B = Rect2BaseMinDim<t>(10, 20, 2, 4);

	CHECK_RECT2(ScaleWithFixedMin(B, (t)2), 10, 20, 14, 28);
	CHECK_RECT2(ScaleWithFixedMax(B, (t)2), 8, 16, 12, 24);
	CHECK_RECT2(ScaleWithFixedCenter(B, (t)2), 9, 18, 13, 26);

	CHECK_RECT2(ScaleWithFixedMin(B, v2_base<t>(2, 3)), 10, 20, 14, 32);
	CHECK_RECT2(ScaleWithFixedMax(B, v2_base<t>(2, 3)), 8, 12, 12, 24);
	CHECK_RECT2(ScaleWithFixedCenter(B, v2_base<t>(2, 3)), 9, 16, 13, 28);


	rect2_base<t> C = Rect2BaseMinDim<t>(v2_base<t>(130), v2_base<t>(2));

	ScaleWithFixedMin(&C, (t)2);
	CHECK_RECT2(C, 130, 130, 134, 134);

	ScaleWithFixedMax(&C, (t)2);
	CHECK_RECT2(C, 126, 126, 134, 134);

	ScaleWithFixedCenter(&C, (t)3);
	CHECK_RECT2(C, 118, 118, 142, 142);


	ScaleWithFixedMin(&C, v2_base<t>(1, 2));
	CHECK_RECT2(C, 118, 118, 142, 166);

	ScaleWithFixedMax(&C, v2_base<t>(2, 1));
	CHECK_RECT2(C, 94, 118, 142, 166);

	ScaleWithFixedCenter(&C, v2_base<t>(2, 3));
	CHECK_RECT2(C, 70, 70, 166, 214);


	CHECK(HasNegativeDim(Rect2BaseMinMax<t>(4, 5, 2, 3)));
	CHECK(!HasNegativeDim(Rect2BaseMinMax<t>(5, 10, 20, 10)));
	CHECK(!HasNegativeDim(Rect2BaseMinMax<t>(20, 20, 30, 50)));
	CHECK_RECT2(MakeRectNotHaveNegativeDim(Rect2BaseMinMax<t>(4, 5, 2, 3)), 2, 3, 4, 5);
	CHECK_RECT2(MakeRectNotHaveNegativeDim(Rect2BaseMinMax<t>(20, 10, 5, 10)), 5, 10, 20, 10);
	CHECK_RECT2(MakeRectNotHaveNegativeDim(Rect2BaseMinMax<t>(20, 20, 30, 50)), 20, 20, 30, 50);

	rect2_base<t> D = Rect2BaseMinMax<t>(4, 5, 2, 3);
	MakeRectNotHaveNegativeDim(&D);
	CHECK_RECT2(D, 2, 3, 4, 5);

	D = Rect2BaseMinMax<t>(20, 10, 5, 10);
	MakeRectNotHaveNegativeDim(&D);
	CHECK_RECT2(D, 5, 10, 20, 10);

	D = Rect2BaseMinMax<t>(20, 20, 30, 50);
	MakeRectNotHaveNegativeDim(&D);
	CHECK_RECT2(D, 20, 20, 30, 50);

	CHECK_RECT2(Union(Rect2BaseMinMax<t>(10, 5, 20, 15), Rect2BaseMinMax<t>(15, 10, 25, 30)), 
	            10, 5, 25, 30);

	CHECK_V2(ClampToRect(v2(3, 6), Rect2MinMax(4, 4, 5, 5)), 4, 5);

	rect2_base<t> E = Rect2BaseMinMax<t>(5, 6, 10, 12);
	CHECK_RECT2(AddRadius(E, (t)2), 3, 4, 12, 14);
	CHECK_RECT2(AddRadius(E, v2_base<t>(1, 2)), 4, 4, 11, 14);

	AddRadius(&E, (t)2);
	CHECK_RECT2(E, 3, 4, 12, 14);

	AddRadius(&E, v2_base<t>(1, 2));
	CHECK_RECT2(E, 2, 2, 13, 16);
}

TEST_CASE("rect2 FitRectInsideBounds")
{
	rect2 Bounds = Rect2Dim(10, 5);
	CHECK_RECT2(FitRectInsideBounds(Rect2MinDim(-5, -5, 2, 4), Bounds), 0, 0, 2, 4); // top left
	CHECK_RECT2(FitRectInsideBounds(Rect2MinDim(-5, 2, 5, 3), Bounds), 0, 2, 5, 5); // left
	CHECK_RECT2(FitRectInsideBounds(Rect2MinDim(-5, 10, 1, 2), Bounds), 0, 3, 1, 5); // bottom left
	CHECK_RECT2(FitRectInsideBounds(Rect2MinDim(3, 10, 5, 2), Bounds), 3, 3, 8, 5); // bottom
	CHECK_RECT2(FitRectInsideBounds(Rect2MinDim(8, 10, 3, 3), Bounds), 7, 2, 10, 5); // bottom right
	CHECK_RECT2(FitRectInsideBounds(Rect2MinDim(12, 0, 5, 4), Bounds), 5, 0, 10, 4); // right
	MoveRect(&Bounds, v2(-3, 3));
	CHECK_RECT2(FitRectInsideBounds(Rect2MinDim(10, -2, 2, 2), Bounds), 5, 3, 7, 5); // top right
	CHECK_RECT2(FitRectInsideBounds(Rect2MinDim(0, 0, 2, 5), Bounds), 0, 3, 2, 8); // top crossing
	CHECK_RECT2(FitRectInsideBounds(Rect2MinDim(-2, 5, 2, 2), Bounds), -2, 5, 0, 7); // center
	CHECK_RECT2(FitRectInsideBounds(Rect2MinDim(-3, 3, 10, 5), Bounds), -3, 3, 7, 8); // center full 
}

TEST_CASE_TEMPLATE("rect2_base intersections and comparisons", t, NUMERICAL_TYPES)
{
	auto A = Rect2BaseMinMax<t>(0, 0, 10, 10);
	auto B = Rect2BaseMinMax<t>(5, 5, 10, 15);
	auto C = Rect2BaseMinDim<t>(20, 5, 10, 10);
	auto D = Rect2BaseMinDim<t>(25, 10, 2, 2);
	auto E = Rect2BaseMinMax<t>(10, 12, 5, 8);
	auto F = Rect2BaseMinMax<t>(12, 12, 10, 8);
	auto G = Rect2BaseMinMax<t>(12, 12, 3, 5);

	auto P = v2_base<t>(4, 6);

	CHECK(Intersect(A, B));
	CHECK(!Intersect(A, C));
	CHECK(!Intersect(B, C));

	CHECK(Intersect(A, P));
	CHECK(!Intersect(B, P));
	CHECK(!Intersect(C, P));

	CHECK(Intersect(C, C));
	CHECK(FullyIntersectOrTouch(C, C));
	CHECK(Intersect(C, D));
	CHECK(FullyIntersect(C, D));

	CHECK(IntersectOrTouchFlipAllowed(E, F));
	CHECK(!FullyIntersectFlipAllowed(E, F));
	
	rect2_base<t> Intersection;

	CHECK(IntersectionRect(A, B, &Intersection));
	CHECK_RECT2(Intersection, 5, 5, 10, 10);

	CHECK(IntersectionRect(C, D, &Intersection));
	CHECK_RECT2(Intersection, 25, 10, 27, 12);

	CHECK(!IntersectionRect(A, D, &Intersection));

	CHECK(IntersectFlipAllowed(G, P));
	CHECK(IntersectFlipAllowed(A, P));
	CHECK(!IntersectFlipAllowed(E, P));

	CHECK(A != B);
	CHECK(C == C);
	CHECK(C != D);
}

TEST_CASE("rect2 cast constructor")
{
	rect2 A = Rect2MinMax(10, 20, 20, 30);
	rect2i B(A);
	CHECK_RECT2(B, 10, 20, 20, 30);
}

