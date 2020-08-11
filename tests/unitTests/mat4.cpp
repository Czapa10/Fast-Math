
TEST_CASE("mat4 construction and getters")
{
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(Mat4Diagonal(3.f), 3.f, 3.f, 3.f, 3.f);
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(Mat4Diagonal(1.f, 2.f, 3.f, 4.f), 1.f, 2.f, 3.f, 4.f);
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(Mat4Diagonal(Vec4(1.f, 2.f, 3.f, 4.f)), 1.f, 2.f, 3.f, 4.f);
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(Mat4Diagonal(v4(1.f, 2.f, 3.f, 4.f)), 1.f, 2.f, 3.f, 4.f);

	{
		float Mem[] = {
			1.f, 2.f, 3.f, 4.f,
			5.f, 6.f, 7.f, 8.f,
			9.f, 10.f, 11.f, 12.f,
			13.f, 14.f, 15.f, 16.f
		}; 
		
		CHECK_ALL_MATRIX_ENTRIES(
			Mat4FromColumnMajorMemory(Mem),
			1.f, 5.f, 9.f,  13.f,
			2.f, 6.f, 10.f, 14.f,
			3.f, 7.f, 11.f, 15.f,
			4.f, 8.f, 12.f, 16.f
		);
		
		CHECK_ALL_MATRIX_ENTRIES(
			Mat4FromRowMajorMemory(Mem),
			1.f, 2.f, 3.f, 4.f,
			5.f, 6.f, 7.f, 8.f,
			9.f, 10.f, 11.f, 12.f,
			13.f, 14.f, 15.f, 16.f
		);
	}

	{
		v4 Row1(1.f, 2.f, 3.f, 4.f);
		v4 Row2(5.f, 6.f, 7.f, 8.f);
		v4 Row3(9.f, 10.f, 11.f, 12.f);
		v4 Row4(13.f, 14.f, 15.f, 16.f);
		CHECK_ALL_MATRIX_ENTRIES(
			Mat4FromRows(Row1, Row2, Row3, Row4),
			1.f, 2.f, 3.f, 4.f,
			5.f, 6.f, 7.f, 8.f,
			9.f, 10.f, 11.f, 12.f,
			13.f, 14.f, 15.f, 16.f
		);
	}

	{
		vec4 Row1 = Vec4(1.f, 2.f, 3.f, 4.f);
		vec4 Row2 = Vec4(5.f, 6.f, 7.f, 8.f);
		vec4 Row3 = Vec4(9.f, 10.f, 11.f, 12.f);
		vec4 Row4 = Vec4(13.f, 14.f, 15.f, 16.f);
		CHECK_ALL_MATRIX_ENTRIES(
			Mat4FromRows(Row1, Row2, Row3, Row4),
			1.f, 2.f, 3.f, 4.f,
			5.f, 6.f, 7.f, 8.f,
			9.f, 10.f, 11.f, 12.f,
			13.f, 14.f, 15.f, 16.f
		);
	}

	{
		vec3 Row1 = Vec3(1.f, 2.f, 3.f);
		vec3 Row2 = Vec3(4.f, 5.f, 6.f);
		vec3 Row3 = Vec3(7.f, 8.f, 9.f);
		vec3 Row4 = Vec3(10.f, 11.f, 12.f);
		CHECK_ALL_MATRIX_ENTRIES(
			Mat4FromRows(Row1, Row2, Row3, Row4),
			1.f, 2.f, 3.f, 0.f,
			4.f, 5.f, 6.f, 0.f,
			7.f, 8.f, 9.f, 0.f,
			10.f, 11.f, 12.f, 1.f
		);
	}

	mat4 A = Mat4FromRows(
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);
	CHECK_ALL_MATRIX_ENTRIES(A,
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);

	CHECK_V4(A.GetColumnV4(0), 1.f, 5.f, 9.f, 13.f);
	CHECK_V4(A.GetColumnV4(1), 2.f, 6.f, 10.f, 14.f);
	CHECK_V4(A.GetColumnV4(2), 3.f, 7.f, 11.f, 15.f);
	CHECK_V4(A.GetColumnV4(3), 4.f, 8.f, 12.f, 16.f);

	CHECK_V4(A.GetRowV4(0), 1.f, 2.f, 3.f, 4.f);
	CHECK_V4(A.GetRowV4(1), 5.f, 6.f, 7.f, 8.f);
	CHECK_V4(A.GetRowV4(2), 9.f, 10.f, 11.f, 12.f);
	CHECK_V4(A.GetRowV4(3), 13.f, 14.f, 15.f, 16.f);

	CHECK_V4(A.GetMainDiagonalV4(), 1.f, 6.f, 11.f, 16.f);


	CHECK_VEC4(A.GetColumnVec4(0), 1.f, 5.f, 9.f, 13.f);
	CHECK_VEC4(A.GetColumnVec4(1), 2.f, 6.f, 10.f, 14.f);
	CHECK_VEC4(A.GetColumnVec4(2), 3.f, 7.f, 11.f, 15.f);
	CHECK_VEC4(A.GetColumnVec4(3), 4.f, 8.f, 12.f, 16.f);

	CHECK_VEC4(A.GetRowVec4(0), 1.f, 2.f, 3.f, 4.f);
	CHECK_VEC4(A.GetRowVec4(1), 5.f, 6.f, 7.f, 8.f);
	CHECK_VEC4(A.GetRowVec4(2), 9.f, 10.f, 11.f, 12.f);
	CHECK_VEC4(A.GetRowVec4(3), 13.f, 14.f, 15.f, 16.f);

	CHECK_VEC4(A.GetMainDiagonalVec4(), 1.f, 6.f, 11.f, 16.f);

	{
		vec4 Col1 = Vec4(1.f, 2.f, 3.f, 4.f);
		vec4 Col2 = Vec4(5.f, 6.f, 7.f, 8.f);
		vec4 Col3 = Vec4(9.f, 10.f, 11.f, 12.f);
		vec4 Col4 = Vec4(13.f, 14.f, 15.f, 16.f);
		CHECK_ALL_MATRIX_ENTRIES(
			Mat4FromColumns(Col1, Col2, Col3, Col4),
			1.f, 5.f, 9.f,  13.f,
			2.f, 6.f, 10.f, 14.f,
			3.f, 7.f, 11.f, 15.f,
			4.f, 8.f, 12.f, 16.f
		);
	}
	{
		v4 Col1(1.f, 2.f, 3.f, 4.f);
		v4 Col2(5.f, 6.f, 7.f, 8.f);
		v4 Col3(9.f, 10.f, 11.f, 12.f);
		v4 Col4(13.f, 14.f, 15.f, 16.f);
		CHECK_ALL_MATRIX_ENTRIES(
			Mat4FromColumns(Col1, Col2, Col3, Col4),
			1.f, 5.f, 9.f,  13.f,
			2.f, 6.f, 10.f, 14.f,
			3.f, 7.f, 11.f, 15.f,
			4.f, 8.f, 12.f, 16.f
		);
	}

	{
		vec3 Col1 = Vec3(1.f, 2.f, 3.f);
		vec3 Col2 = Vec3(5.f, 6.f, 7.f);
		vec3 Col3 = Vec3(9.f, 10.f, 11.f);
		vec3 Col4 = Vec3(13.f, 14.f, 15.f);
		CHECK_ALL_MATRIX_ENTRIES(
			Mat4FromColumns(Col1, Col2, Col3, Col4),
			1.f, 5.f, 9.f,  13.f,
			2.f, 6.f, 10.f, 14.f,
			3.f, 7.f, 11.f, 15.f,
			0.f, 0.f, 0.f, 1.f
		);
	}
	{
		v3 Col1(1, 2, 3);
		v3 Col2(5, 6, 7);
		v3 Col3(9, 10, 11);
		v3 Col4(13, 14, 15);
		CHECK_ALL_MATRIX_ENTRIES(
			Mat4FromColumns(Col1, Col2, Col3, Col4),
			1.f, 5.f, 9.f,  13.f,
			2.f, 6.f, 10.f, 14.f,
			3.f, 7.f, 11.f, 15.f,
			0.f, 0.f, 0.f, 1.f
		);
	}

	A = Mat4FromColumns(
		1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f);

	CHECK_ALL_MATRIX_ENTRIES(A,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);

	float Storage[16];
	Store(Storage, A);
	CHECK_ALL_MATRIX_ENTRIES(A,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);

	Store16ByteAligned(Storage, A);											   
	CHECK_ALL_MATRIX_ENTRIES(A,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);

	// NOTE: Accessing simd types directly (without intrinsics) is slow
	CHECK(*Ptr(A) == 1.f);
	CHECK(A[0] == 1.f);
	CHECK(A[1] == 2.f);
	CHECK(A[4] == 5.f);
	CHECK(A[5] == 6.f);
}

TEST_CASE("mat4 setters and swaps")
{
	mat4 M = Mat4();

	M.SetRow(0, v4(1.f, 2.f, 3.f, 4.f));
	M.SetRow(1, Vec4(1.f, 2.f, 3.f, 4.f));
	M.SetRow(2, 1.f, 2.f, 3.f, 4.f);

	CHECK_ALL_MATRIX_ENTRIES(M,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		0.f, 0.f, 0.f, 0.f
	);

	M.SetColumn(1, v4(0.f, 1.f, 0.f, 1.f));
	M.SetColumn(2, Vec4(1.f, 2.f, 3.f, 4.f));
	M.SetColumn(3, 5.f, 6.f, 7.f, 8.f);

	CHECK_ALL_MATRIX_ENTRIES(M,
		1.f, 0.f, 1.f, 5.f,
		1.f, 1.f, 2.f, 6.f,
		1.f, 0.f, 3.f, 7.f,
		0.f, 1.f, 4.f, 8.f
	);

	M.SwapRows(0, 1);

	CHECK_ALL_MATRIX_ENTRIES(M,
		1.f, 1.f, 2.f, 6.f,
		1.f, 0.f, 1.f, 5.f,
		1.f, 0.f, 3.f, 7.f,
		0.f, 1.f, 4.f, 8.f
	);

	M.SwapColumns(2, 3);

	CHECK_ALL_MATRIX_ENTRIES(M,
		1.f, 1.f, 6.f, 2.f,
		1.f, 0.f, 5.f, 1.f,
		1.f, 0.f, 7.f, 3.f,
		0.f, 1.f, 8.f, 4.f
	);

	M.SetMainDiagonal(8.f, 9.f, 10.f, 11.f);

	CHECK_ALL_MATRIX_ENTRIES(M,
		8.f, 1.f, 6.f, 2.f,
		1.f, 9.f, 5.f, 1.f,
		1.f, 0.f, 10.f,3.f,
		0.f, 1.f, 8.f, 11.f
	);

	M.SetMainDiagonal(Vec4(0.f, 2.f, 5.f, 1.f));

	CHECK_ALL_MATRIX_ENTRIES(M,
		0.f, 1.f, 6.f, 2.f,
		1.f, 2.f, 5.f, 1.f,
		1.f, 0.f, 5.f, 3.f,
		0.f, 1.f, 8.f, 1.f
	);

	M.SetMainDiagonal(v4(5.f, 3.f, 2.f, 5.f));

	CHECK_ALL_MATRIX_ENTRIES(M,
		5.f, 1.f, 6.f, 2.f,
		1.f, 3.f, 5.f, 1.f,
		1.f, 0.f, 2.f, 3.f,
		0.f, 1.f, 8.f, 5.f
	);
}

TEST_CASE("mat4 operations")
{
	mat4 A = Mat4FromRows(
		1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f);

	mat4 B = Mat4FromRows(
		-1.f, -2.f, -3.f, -4.f,
         5.f, 6.f, 7.f, 8.f,
         2.f, 2.f, 2.f, 2.f,
         0.f, 0.f, 0.f, 0.f);

	CHECK_ALL_MATRIX_ENTRIES(A + B,
		0.f, 0.f, 0.f, 0.f,
		10.f, 12.f, 14.f, 16.f,
		11.f, 12.f, 13.f, 14.f,
		13.f, 14.f, 15.f, 16.f
	);

	CHECK_ALL_MATRIX_ENTRIES(A - B,
		2.f, 4.f, 6.f, 8.f,
		0.f, 0.f, 0.f, 0.f, 
		7.f, 8.f, 9.f, 10.f,
		13.f, 14.f, 15.f, 16.f
	);

	CHECK_ALL_MATRIX_ENTRIES(A * 2.f,
		2.f, 4.f, 6.f, 8.f,
		10.f, 12.f, 14.f, 16.f,
		18.f, 20.f, 22.f, 24.f,
		26.f, 28.f, 30.f, 32.f
	);

	CHECK_ALL_MATRIX_ENTRIES(A / 2.f,
		0.5f, 1.f, 1.5f, 2.f,
		2.5f, 3.f, 3.5f, 4.f,
		4.5f, 5.f, 5.5f, 6.f,
		6.5f, 7.f, 7.5f, 8.f
	);

	CHECK_ALL_MATRIX_ENTRIES(A * Mat4Identity(),
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);

	CHECK_ALL_MATRIX_ENTRIES(A * B,
		15.f, 16.f, 17.f, 18.f,
		39.f, 40.f, 41.f, 42.f,
		63.f, 64.f, 65.f, 66.f,
		87.f, 88.f, 89.f, 90.f
	);

	CHECK_VEC4(A * Vec4(1.f, 2.f, 3.f, 4.f), 30.f, 70.f, 110.f, 150.f);
	CHECK_V4(A * v4(1.f, 2.f, 3.f, 4.f), 30.f, 70.f, 110.f, 150.f);

	mat4 C = A;
	C *= 2.f;
	CHECK_ALL_MATRIX_ENTRIES(C,
		2.f, 4.f, 6.f, 8.f,
		10.f, 12.f, 14.f, 16.f,
		18.f, 20.f, 22.f, 24.f,
		26.f, 28.f, 30.f, 32.f
	);

	mat4 D = A;
	D /= 2.f;
	CHECK_ALL_MATRIX_ENTRIES(D,
		0.5f, 1.f, 1.5f, 2.f,
		2.5f, 3.f, 3.5f, 4.f,
		4.5f, 5.f, 5.5f, 6.f,
		6.5f, 7.f, 7.5f, 8.f
	);

	mat4 E = A;
	Transpose(&E);
	CHECK_ALL_MATRIX_ENTRIES(E,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);

	CHECK_ALL_MATRIX_ENTRIES(
		HadamardMul(A, B),
		-1.f, -4.f, -9.f, -16.f,
		25.f, 36.f, 49.f, 64.f,
		18.f, 20.f, 22.f, 24.f,
		 0.f,  0.f,  0.f,  0.f
	);

	mat4 G = Mat4FromRows(
		-1.f, -2.f, -3.f, -4.f,
         5.f, 6.f, 7.f, 8.f,
         2.f, 2.f, 2.f, 2.f,
		 1.f, 1.f, 1.f, 1.f);

	CHECK_ALL_MATRIX_ENTRIES(
		HadamardDiv(A, G),
		-1.f, -1.f, -1.f, -1.f,
		 1.f,  1.f,  1.f,  1.f,
		 4.5f, 5.f, 5.5f, 6.f,
        13.f, 14.f, 15.f, 16.f
	);

	CHECK(A == A);
	CHECK(A != B);
}

TEST_CASE("mat4 Transformations")
{
	v4 V0(0.f, 0.f, 0.f, 1.f);
	v4 V1(1.f);
	v4 V123(1.f, 2.f, 3.f, 1.f);
	mat4 Trans, Scal, Rot, She;

	// Translate
	Trans = Mat4Translation(1.f, 2.f, 3.f);
	CHECK_V4(Trans * V0, 1.f, 2.f, 3.f, 1.f);

	Trans = Mat4Translation(3.f);
	CHECK_V4(Trans * V0, 3.f, 3.f, 3.f, 1.f);

	Trans = Mat4Translation(Vec3(1.f, 2.f, 3.f));
	CHECK_V4(Trans * V0, 1.f, 2.f, 3.f, 1.f);

	Translate(&Trans, -5.f, -3.f, 0.f);
	CHECK_V4(Trans * V0, -4.f, -1.f, 3.f, 1.f);

	Translate(&Trans, Vec3(5.f, 3.f, 0.f));
	CHECK_V4(Trans * V0, 1.f, 2.f, 3.f, 1.f);

	Translate(&Trans, 5.f);
	CHECK_V4(Trans * V0, 6.f, 7.f, 8.f, 1.f);

	// Scale
	Scal = Mat4Scale(5.f);
	CHECK_V4(Scal * V1, 5.f, 5.f, 5.f, 1.f);

	Scal = Mat4Scale(5.f, 4.f, 3.f);
	CHECK_V4(Scal * V1, 5.f, 4.f, 3.f, 1.f);

	Scale(&Scal, 2.f);
	CHECK_V4(Scal * V1, 10.f, 8.f, 6.f, 1.f);

	Scale(&Scal, 0.5f, 0.25f, 1.f);
	CHECK_V4(Scal * V1, 5.f, 2.f, 6.f, 1.f);

	Scale(&Scal, Vec3(-1.f, 2.f, 3.f));
	CHECK_V4(Scal * V1;, -5.f, 4.f, 18.f, 1.f);

	// Rotate
	Rot = Mat4RotationDegrees(90.f, 1.f, 0.f, 0.f);
	CHECK_V4_APPROX(Rot * V1, 1.f, -1.f, 1.f, 1.f);

	Rot = Mat4RotationDegrees(90.f, Vec3(1.f, 0.f, 0.f)); 
	CHECK_V4_APPROX(Rot * V1, 1.f, -1.f, 1.f, 1.f);

	Rot = Mat4RotationAroundXAxisDegrees(90.f);
	CHECK_V4_APPROX(Rot * V1, 1.f, -1.f, 1.f, 1.f);


	Rot = Mat4RotationDegrees(90.f, 0.f, 1.f, 0.f);
	CHECK_V4_APPROX(Rot * V1, 1.f, 1.f, -1.f, 1.f);

	Rot = Mat4RotationDegrees(90.f, Vec3(0.f, 1.f, 0.f)); 
	CHECK_V4_APPROX(Rot * V1, 1.f, 1.f, -1.f, 1.f);

	Rot = Mat4RotationAroundYAxisDegrees(90.f);
	CHECK_V4_APPROX(Rot * V1, 1.f, 1.f, -1.f, 1.f);


	Rot = Mat4RotationDegrees(90.f, 0.f, 0.f, 1.f);
	CHECK_V4_APPROX(Rot * V1, -1.f, 1.f, 1.f, 1.f);

	Rot = Mat4RotationDegrees(90.f, Vec3(0.f, 0.f, 1.f)); 
	CHECK_V4_APPROX(Rot * V1, -1.f, 1.f, 1.f, 1.f);

	Rot = Mat4RotationAroundZAxisDegrees(90.f);
	CHECK_V4_APPROX(Rot * V1, -1.f, 1.f, 1.f, 1.f);


	Rot = Mat4RotationAroundAllAxesDegrees(90.f);
	CHECK_V4_APPROX(Rot * V1, 1.f, 1.f, 1.f, 1.f);

	
	// TODO: Rotate tests are missing

	// Shear
	She = Mat4ShearXAxis(3.f, 1.f);
	CHECK_V4(She * V123, 1.f, 5.f, 4.f, 1.f);

	She = Mat4ShearYAxis(3.f, 1.f);
	CHECK_V4(She * V123, 7.f, 2.f, 5.f, 1.f);

	She = Mat4ShearZAxis(3.f, 1.f);
	CHECK_V4(She * V123, 10.f, 5.f, 3.f, 1.f);

	She = Mat4Shear(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
	CHECK_V4(She * V123, 22.f, 21.f, 13.f, 1.f);
	
	She = Mat4FromRows(
		1.f, -1.f, 0.f, 2.f,
		1.f, 1.f, 0.f, 3.f,
		0.f, 1.f, 1.f, 4.f,
		0.f, 0.f, 0.f, 1.f);

	ShearXAxis(&She, 1.f, 2.f);
	CHECK_V4(She * V123, 0.f, 7.f, 12.f, 1.f);

	ShearYAxis(&She, 3.f, 4.f);
	CHECK_V4(She * V123, 0.f, 19.f, 38.f, 1.f);

	ShearZAxis(&She, 5.f, 6.f);
	CHECK_V4(She * V123, -18.f, 175.f, 335.f, 1.f);

	Shear(&She, -1.f, -2.f, -3.f, 1.f, 2.f, 3.f);
	CHECK_V4(She * V123, -26.f, 231.f, 447.f, 1.f);

	// TODO: Combined affine transformation tests are missing
}

TEST_CASE("mat4 Orthographic projection")
{
	mat4 Ortho = Mat4Orthographic(-10.f, 10.f, -5.f, 5.f, 0.f, -10.f);
	v4 P(5.f, 5.f, -5.f, 1.f);
	CHECK_V4_APPROX(Ortho * P, 0.5f, 1.f, -2.f, 1.f);

	// TODO: Add Mat4OrthographicTopDown and Mat4OrthographicBottomUp
}

TEST_CASE("mat4 Perspective projection")
{
	mat4 Persp = Mat4Perspective(90.0f, 2.0f, 5.0f, 15.0f);

	vec4 P1 = Vec4(5.0f, 5.0f, -15.0f, 1.f);
	CHECK_VEC4(Persp * P1, 2.5f, 5.f, 15.f, 15.f);

	v4 P2(5.0f, 5.0f, -5.0f, 1.f);
	CHECK_V4(Persp * P2, 2.5f, 5.f, -5.f, 5.f);
}

TEST_CASE("mat4 look at")
{
	mat4 ViewMat = Mat4LookAt(Vec3(0.f), Vec3(0.f, 0.f, 5.f));
	CHECK_VEC4(ViewMat * Vec4(0.f, 2.f, 5.f, 1.f), 0.f, 2.f, -5.f, 1.f);

	ViewMat = Mat4LookAt(v3{}, v3(0, 0, 5));
	CHECK_V4(ViewMat * v4(0.f, 2.f, 5.f, 1.f), 0.f, 2.f, -5.f, 1.f);

	// TODO: Make more tests for look at function
}
