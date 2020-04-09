#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

TEST_CASE("mat4 construction and Getters")
{
	mat4 A = Mat4Diagonal(3.f);
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX1(A, 3.f);

	A = Mat4Diagonal(1.f, 2.f, 3.f, 4.f); 
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(A, 1.f, 2.f, 3.f, 4.f);

	v4 Diagonal = V4(1.f, 2.f, 3.f, 4.f);
	A = Mat4Diagonal(Diagonal);
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(A, 1.f, 2.f, 3.f, 4.f);

	v4 Row1 = V4(1.f, 2.f, 3.f, 4.f);
	v4 Row2 = V4(5.f, 6.f, 7.f, 8.f);
	v4 Row3 = V4(9.f, 10.f, 11.f, 12.f);
	v4 Row4 = V4(13.f, 14.f, 15.f, 16.f);
	A = Mat4FromRows(Row1, Row2, Row3, Row4);
	CHECK_ALL_MATRIX_ENTRIES(A,
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);

	A = Mat4FromRows(
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

	CHECK_VECTOR4(A.GetColumn(0), 1.f, 5.f, 9.f, 13.f);
	CHECK_VECTOR4(A.GetColumn(1), 2.f, 6.f, 10.f, 14.f);
	CHECK_VECTOR4(A.GetColumn(2), 3.f, 7.f, 11.f, 15.f);
	CHECK_VECTOR4(A.GetColumn(3), 4.f, 8.f, 12.f, 16.f);

	CHECK_VECTOR4(A.GetRow(0), 1.f, 2.f, 3.f, 4.f);
	CHECK_VECTOR4(A.GetRow(1), 5.f, 6.f, 7.f, 8.f);
	CHECK_VECTOR4(A.GetRow(2), 9.f, 10.f, 11.f, 12.f);
	CHECK_VECTOR4(A.GetRow(3), 13.f, 14.f, 15.f, 16.f);

	CHECK_VECTOR4(A.GetMainDiagonal(), 1.f, 6.f, 11.f, 16.f);

	v4 Col1 = V4(1.f, 2.f, 3.f, 4.f);
	v4 Col2 = V4(5.f, 6.f, 7.f, 8.f);
	v4 Col3 = V4(9.f, 10.f, 11.f, 12.f);
	v4 Col4 = V4(13.f, 14.f, 15.f, 16.f);
	A = Mat4FromColumns(Col1, Col2, Col3, Col4);
	CHECK_ALL_MATRIX_ENTRIES(A,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);

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

	float* P = ptr(A);
	CHECK(*P == 1.f);
}

TEST_CASE("mat4 setters and Swaps")
{
	mat4 M = Mat4();

	M.SetRow(0, V4(1.f, 2.f, 3.f, 4.f));
	M.SetRow(1, 1.f, 2.f, 3.f, 4.f);

	CHECK_ALL_MATRIX_ENTRIES(M,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		0.f, 0.f, 0.f, 0.f, 
		0.f, 0.f, 0.f, 0.f
	);

	M.SetColumn(2, V4(1.f, 2.f, 3.f, 4.f));
	M.SetColumn(3, 5.f, 6.f, 7.f, 8.f);

	CHECK_ALL_MATRIX_ENTRIES(M,
		1.f, 2.f, 1.f, 5.f,
		1.f, 2.f, 2.f, 6.f,
		0.f, 0.f, 3.f, 7.f, 
		0.f, 0.f, 4.f, 8.f
	);

	M.SwapRows(0, 1);

	CHECK_ALL_MATRIX_ENTRIES(M,
		1.f, 2.f, 2.f, 6.f,
		1.f, 2.f, 1.f, 5.f,
		0.f, 0.f, 3.f, 7.f, 
		0.f, 0.f, 4.f, 8.f
	);

	M.SwapColumns(2, 3);

	CHECK_ALL_MATRIX_ENTRIES(M,
		1.f, 2.f, 6.f, 2.f, 
		1.f, 2.f, 5.f, 1.f, 
		0.f, 0.f, 7.f, 3.f, 
		0.f, 0.f, 8.f, 4.f 
	);

	M.SetMainDiagonal(8.f, 9.f, 10.f, 11.f);

	CHECK_ALL_MATRIX_ENTRIES(M,
		8.f, 2.f, 6.f, 2.f, 
		1.f, 9.f, 5.f, 1.f, 
		0.f, 0.f, 10.f, 3.f, 
		0.f, 0.f, 8.f, 11.f 
	);

	M.SetMainDiagonal(V4(0.f, 2.f, 5.f, 1.f));

	CHECK_ALL_MATRIX_ENTRIES(M,
		0.f, 2.f, 6.f, 2.f, 
		1.f, 2.f, 5.f, 1.f, 
		0.f, 0.f, 5.f, 3.f, 
		0.f, 0.f, 8.f, 1.f 
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

	v4 V = V4(1.f, 2.f, 3.f, 4.f);
	CHECK_VECTOR4(A * V, 30.f, 70.f, 110.f, 150.f);

	mat4 TransposedA = Transpose(A);
	CHECK_ALL_MATRIX_ENTRIES(TransposedA,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);
}

TEST_CASE("mat4 Transformations")
{
	v4 V0 = V4(0.f, 0.f, 0.f, 1.f);
	v4 V1 = V4(1.f);
	v4 V123 = V4(1.f, 2.f, 3.f, 1.f);
	mat4 Trans, Scal, Rot, She;

	// Translate
	Trans = Mat4Translation(1.f, 2.f, 3.f);
	CHECK_VECTOR4(Trans * V0, 1.f, 2.f, 3.f, 1.f);

	Trans = Mat4Translation(V3(1.f, 2.f, 3.f));
	CHECK_VECTOR4(Trans * V0, 1.f, 2.f, 3.f, 1.f);

	Trans = Translate(Trans, -5.f, -3.f, 0.f);
	CHECK_VECTOR4(Trans * V0, -4.f, -1.f, 3.f, 1.f);

	Trans = Translate(Trans, V3(5.f, 3.f, 0.f));
	CHECK_VECTOR4(Trans * V0, 1.f, 2.f, 3.f, 1.f);

	// Scale
	Scal = Mat4Scale(5.f);
	CHECK_VECTOR4(Scal * V1, 5.f, 5.f, 5.f, 1.f);

	Scal = Mat4Scale(5.f, 4.f, 3.f);
	CHECK_VECTOR4(Scal * V1, 5.f, 4.f, 3.f, 1.f);

	Scal = Scale(Scal, 2.f);
	CHECK_VECTOR4(Scal * V1, 10.f, 8.f, 6.f, 1.f);

	Scal = Scale(Scal, 0.5f, 0.25f, 1.f);
	CHECK_VECTOR4(Scal * V1, 5.f, 2.f, 6.f, 1.f);

	Scal = Scale(Scal, V3(-1.f, 2.f, 3.f));
	CHECK_VECTOR4(Scal * V1;, -5.f, 4.f, 18.f, 1.f);

	// Rotate
	Rot = Mat4RotationDegrees(90.f, 1.f, 0.f, 0.f);
	CHECK_VECTOR4_APPROX(Rot * V1, 1.f, -1.f, 1.f, 1.f);

	Rot = Mat4RotationDegrees(90.f, V3(1.f, 0.f, 0.f)); 
	CHECK_VECTOR4_APPROX(Rot * V1, 1.f, -1.f, 1.f, 1.f);

	Rot = Mat4RotationAroundXAxisDegrees(90.f);
	CHECK_VECTOR4_APPROX(Rot * V1, 1.f, -1.f, 1.f, 1.f);


	Rot = Mat4RotationDegrees(90.f, 0.f, 1.f, 0.f);
	CHECK_VECTOR4_APPROX(Rot * V1, 1.f, 1.f, -1.f, 1.f);

	Rot = Mat4RotationDegrees(90.f, V3(0.f, 1.f, 0.f)); 
	CHECK_VECTOR4_APPROX(Rot * V1, 1.f, 1.f, -1.f, 1.f);

	Rot = Mat4RotationAroundYAxisDegrees(90.f);
	CHECK_VECTOR4_APPROX(Rot * V1, 1.f, 1.f, -1.f, 1.f);


	Rot = Mat4RotationDegrees(90.f, 0.f, 0.f, 1.f);
	CHECK_VECTOR4_APPROX(Rot * V1, -1.f, 1.f, 1.f, 1.f);

	Rot = Mat4RotationDegrees(90.f, V3(0.f, 0.f, 1.f)); 
	CHECK_VECTOR4_APPROX(Rot * V1, -1.f, 1.f, 1.f, 1.f);

	Rot = Mat4RotationAroundZAxisDegrees(90.f);
	CHECK_VECTOR4_APPROX(Rot * V1, -1.f, 1.f, 1.f, 1.f);

	// Shear
	She = Mat4ShearXAxis(3.f, 1.f);
	CHECK_VECTOR4(She * V123, 1.f, 5.f, 4.f, 1.f);

	She = Mat4ShearYAxis(3.f, 1.f);
	CHECK_VECTOR4(She * V123, 7.f, 2.f, 5.f, 1.f);

	She = Mat4ShearZAxis(3.f, 1.f);
	CHECK_VECTOR4(She * V123, 10.f, 5.f, 3.f, 1.f);

	She = Mat4Shear(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
	CHECK_VECTOR4(She * V123, 22.f, 21.f, 13.f, 1.f);
	
	She = Mat4FromRows(
		1.f, -1.f, 0.f, 2.f,
		1.f, 1.f, 0.f, 3.f,
		0.f, 1.f, 1.f, 4.f,
		0.f, 0.f, 0.f, 1.f);

	She = ShearXAxis(She, 1.f, 2.f);
	CHECK_VECTOR4(She * V123, 0.f, 7.f, 12.f, 1.f);

	She = ShearYAxis(She, 3.f, 4.f);
	CHECK_VECTOR4(She * V123, 0.f, 19.f, 38.f, 1.f);

	She = ShearZAxis(She, 5.f, 6.f);
	CHECK_VECTOR4(She * V123, -18.f, 175.f, 335.f, 1.f);

	She = Shear(She, -1.f, -2.f, -3.f, 1.f, 2.f, 3.f);
	CHECK_VECTOR4(She * V123, -26.f, 231.f, 447.f, 1.f);
}

TEST_CASE("mat4 Orthographic projection")
{
	mat4 Ortho = Mat4Orthographic(-10.f, 10.f, -5.f, 5.f, 0.f, -10.f);
	v4 V = V4(5.f, 5.f, -5.f, 1.f);
	CHECK_VECTOR4_APPROX(Ortho * V, 0.5f, 1.f, -2.f, 1.f);
}

TEST_CASE("mat4 Perspective projection")
{
	mat4 Persp = Mat4Perspective(90.0f, 2.0f, 5.0f, 15.0f);

	v4 V = V4(5.0f, 5.0f, -15.0f, 1.f);
	CHECK_VECTOR4(Persp * V, 2.5f, 5.f, 15.f, 15.f);

	V = V4(5.0f, 5.0f, -5.0f, 1.f);
	CHECK_VECTOR4(Persp * V, 2.5f, 5.f, -5.f, 5.f);
}
