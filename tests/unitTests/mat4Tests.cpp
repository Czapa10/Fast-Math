#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

TEST_CASE("mat4 construction and getters")
{
	mat4 a = makeDiagonalMat4(3.f);
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX1(a, 3.f);

	a = makeDiagonalMat4(1.f, 2.f, 3.f, 4.f); 
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(a, 1.f, 2.f, 3.f, 4.f);

	vec4 diagonal = makeVec4(1.f, 2.f, 3.f, 4.f);
	a = makeDiagonalMat4(diagonal);
	CHECK_MAIN_DIAGONAL_OF_DIAGONAL_MATRIX(a, 1.f, 2.f, 3.f, 4.f);

	vec4 row1 = makeVec4(1.f, 2.f, 3.f, 4.f);
	vec4 row2 = makeVec4(5.f, 6.f, 7.f, 8.f);
	vec4 row3 = makeVec4(9.f, 10.f, 11.f, 12.f);
	vec4 row4 = makeVec4(13.f, 14.f, 15.f, 16.f);
	a = makeMat4FromRows(row1, row2, row3, row4);
	CHECK_ALL_MATRIX_ENTRIES(a,
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);

	a = makeMat4FromRows(
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);
	CHECK_ALL_MATRIX_ENTRIES(a,
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);

	CHECK_VECTOR4(a.getColumn(0), 1.f, 5.f, 9.f, 13.f);
	CHECK_VECTOR4(a.getColumn(1), 2.f, 6.f, 10.f, 14.f);
	CHECK_VECTOR4(a.getColumn(2), 3.f, 7.f, 11.f, 15.f);
	CHECK_VECTOR4(a.getColumn(3), 4.f, 8.f, 12.f, 16.f);

	CHECK_VECTOR4(a.getRow(0), 1.f, 2.f, 3.f, 4.f);
	CHECK_VECTOR4(a.getRow(1), 5.f, 6.f, 7.f, 8.f);
	CHECK_VECTOR4(a.getRow(2), 9.f, 10.f, 11.f, 12.f);
	CHECK_VECTOR4(a.getRow(3), 13.f, 14.f, 15.f, 16.f);

	CHECK_VECTOR4(a.getMainDiagonal(), 1.f, 6.f, 11.f, 16.f);

	vec4 col1 = makeVec4(1.f, 2.f, 3.f, 4.f);
	vec4 col2 = makeVec4(5.f, 6.f, 7.f, 8.f);
	vec4 col3 = makeVec4(9.f, 10.f, 11.f, 12.f);
	vec4 col4 = makeVec4(13.f, 14.f, 15.f, 16.f);
	a = makeMat4FromColumns(col1, col2, col3, col4);
	CHECK_ALL_MATRIX_ENTRIES(a,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);

	a = makeMat4FromColumns(
		1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f);
	CHECK_ALL_MATRIX_ENTRIES(a,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);

	float storage[16];
	store(storage, a);
	CHECK_ALL_MATRIX_ENTRIES(a,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);

	store16ByteAligned(storage, a);											   
	CHECK_ALL_MATRIX_ENTRIES(a,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);

	float* p = ptr(a);
	CHECK(*p == 1.f);
}

TEST_CASE("mat4 setters and swaps")
{
	mat4 m = makeZeroMat4();

	m.setRow(0, makeVec4(1.f, 2.f, 3.f, 4.f));
	m.setRow(1, 1.f, 2.f, 3.f, 4.f);

	CHECK_ALL_MATRIX_ENTRIES(m,
		1.f, 2.f, 3.f, 4.f,
		1.f, 2.f, 3.f, 4.f,
		0.f, 0.f, 0.f, 0.f, 
		0.f, 0.f, 0.f, 0.f
	);

	m.setColumn(2, makeVec4(1.f, 2.f, 3.f, 4.f));
	m.setColumn(3, 5.f, 6.f, 7.f, 8.f);

	CHECK_ALL_MATRIX_ENTRIES(m,
		1.f, 2.f, 1.f, 5.f,
		1.f, 2.f, 2.f, 6.f,
		0.f, 0.f, 3.f, 7.f, 
		0.f, 0.f, 4.f, 8.f
	);

	m.swapRows(0, 1);

	CHECK_ALL_MATRIX_ENTRIES(m,
		1.f, 2.f, 2.f, 6.f,
		1.f, 2.f, 1.f, 5.f,
		0.f, 0.f, 3.f, 7.f, 
		0.f, 0.f, 4.f, 8.f
	);

	m.swapColumns(2, 3);

	CHECK_ALL_MATRIX_ENTRIES(m,
		1.f, 2.f, 6.f, 2.f, 
		1.f, 2.f, 5.f, 1.f, 
		0.f, 0.f, 7.f, 3.f, 
		0.f, 0.f, 8.f, 4.f 
	);

	m.setMainDiagonal(8.f, 9.f, 10.f, 11.f);

	CHECK_ALL_MATRIX_ENTRIES(m,
		8.f, 2.f, 6.f, 2.f, 
		1.f, 9.f, 5.f, 1.f, 
		0.f, 0.f, 10.f, 3.f, 
		0.f, 0.f, 8.f, 11.f 
	);

	m.setMainDiagonal(makeVec4(0.f, 2.f, 5.f, 1.f));

	CHECK_ALL_MATRIX_ENTRIES(m,
		0.f, 2.f, 6.f, 2.f, 
		1.f, 2.f, 5.f, 1.f, 
		0.f, 0.f, 5.f, 3.f, 
		0.f, 0.f, 8.f, 1.f 
	);
}

TEST_CASE("mat4 operations")
{
	mat4 a = makeMat4FromRows(
		1.f, 2.f, 3.f, 4.f,
        5.f, 6.f, 7.f, 8.f,
        9.f, 10.f, 11.f, 12.f,
        13.f, 14.f, 15.f, 16.f);

	mat4 b = makeMat4FromRows(
		-1.f, -2.f, -3.f, -4.f,
         5.f, 6.f, 7.f, 8.f,
         2.f, 2.f, 2.f, 2.f,
         0.f, 0.f, 0.f, 0.f);

	CHECK_ALL_MATRIX_ENTRIES(a + b,
		0.f, 0.f, 0.f, 0.f,
		10.f, 12.f, 14.f, 16.f,
		11.f, 12.f, 13.f, 14.f,
		13.f, 14.f, 15.f, 16.f
	);

	CHECK_ALL_MATRIX_ENTRIES(a - b,
		2.f, 4.f, 6.f, 8.f,
		0.f, 0.f, 0.f, 0.f, 
		7.f, 8.f, 9.f, 10.f,
		13.f, 14.f, 15.f, 16.f
	);

	CHECK_ALL_MATRIX_ENTRIES(a * 2.f,
		2.f, 4.f, 6.f, 8.f,
		10.f, 12.f, 14.f, 16.f,
		18.f, 20.f, 22.f, 24.f,
		26.f, 28.f, 30.f, 32.f
	);

	CHECK_ALL_MATRIX_ENTRIES(a / 2.f,
		0.5f, 1.f, 1.5f, 2.f,
		2.5f, 3.f, 3.5f, 4.f,
		4.5f, 5.f, 5.5f, 6.f,
		6.5f, 7.f, 7.5f, 8.f
	);

	CHECK_ALL_MATRIX_ENTRIES(a * makeIdentityMat4(),
		1.f, 2.f, 3.f, 4.f,
		5.f, 6.f, 7.f, 8.f,
		9.f, 10.f, 11.f, 12.f,
		13.f, 14.f, 15.f, 16.f
	);

	CHECK_ALL_MATRIX_ENTRIES(a * b,
		15.f, 16.f, 17.f, 18.f,
		39.f, 40.f, 41.f, 42.f,
		63.f, 64.f, 65.f, 66.f,
		87.f, 88.f, 89.f, 90.f
	);

	vec4 v = makeVec4(1.f, 2.f, 3.f, 4.f);
	CHECK_VECTOR4(a * v, 30.f, 70.f, 110.f, 150.f);

	mat4 transposedA = transpose(a);
	CHECK_ALL_MATRIX_ENTRIES(transposedA,
		1.f, 5.f, 9.f,  13.f,
		2.f, 6.f, 10.f, 14.f,
		3.f, 7.f, 11.f, 15.f,
		4.f, 8.f, 12.f, 16.f
	);
}

TEST_CASE("mat4 transformations")
{
	vec4 v0 = makeVec4(0.f, 0.f, 0.f, 1.f);
	vec4 v1 = makeVec4(1.f);
	vec4 v123 = makeVec4(1.f, 2.f, 3.f, 1.f);
	mat4 trans, scal, rot, she;

	// translate
	trans = makeTranslationMat4(1.f, 2.f, 3.f);
	CHECK_VECTOR4(trans * v0, 1.f, 2.f, 3.f, 1.f);

	trans = makeTranslationMat4(makeVec3(1.f, 2.f, 3.f));
	CHECK_VECTOR4(trans * v0, 1.f, 2.f, 3.f, 1.f);

	trans = translate(trans, -5.f, -3.f, 0.f);
	CHECK_VECTOR4(trans * v0, -4.f, -1.f, 3.f, 1.f);

	trans = translate(trans, makeVec3(5.f, 3.f, 0.f));
	CHECK_VECTOR4(trans * v0, 1.f, 2.f, 3.f, 1.f);

	// scale
	scal = makeScaleMat4(5.f);
	CHECK_VECTOR4(scal * v1, 5.f, 5.f, 5.f, 1.f);

	scal = makeScaleMat4(5.f, 4.f, 3.f);
	CHECK_VECTOR4(scal * v1, 5.f, 4.f, 3.f, 1.f);

	scal = scale(scal, 2.f);
	CHECK_VECTOR4(scal * v1, 10.f, 8.f, 6.f, 1.f);

	scal = scale(scal, 0.5f, 0.25f, 1.f);
	CHECK_VECTOR4(scal * v1, 5.f, 2.f, 6.f, 1.f);

	scal = scale(scal, makeVec3(-1.f, 2.f, 3.f));
	CHECK_VECTOR4(scal * v1;, -5.f, 4.f, 18.f, 1.f);

	// rotate
	rot = makeRotationMat4Degrees(90.f, 1.f, 0.f, 0.f);
	CHECK_VECTOR4_APPROX(rot * v1, 1.f, -1.f, 1.f, 1.f);

	rot = makeRotationMat4Degrees(90.f, makeVec3(1.f, 0.f, 0.f)); 
	CHECK_VECTOR4_APPROX(rot * v1, 1.f, -1.f, 1.f, 1.f);

	rot = makeRotationAroundXAxisMat4Degrees(90.f);
	CHECK_VECTOR4_APPROX(rot * v1, 1.f, -1.f, 1.f, 1.f);


	rot = makeRotationMat4Degrees(90.f, 0.f, 1.f, 0.f);
	CHECK_VECTOR4_APPROX(rot * v1, 1.f, 1.f, -1.f, 1.f);

	rot = makeRotationMat4Degrees(90.f, makeVec3(0.f, 1.f, 0.f)); 
	CHECK_VECTOR4_APPROX(rot * v1, 1.f, 1.f, -1.f, 1.f);

	rot = makeRotationAroundYAxisMat4Degrees(90.f);
	CHECK_VECTOR4_APPROX(rot * v1, 1.f, 1.f, -1.f, 1.f);


	rot = makeRotationMat4Degrees(90.f, 0.f, 0.f, 1.f);
	CHECK_VECTOR4_APPROX(rot * v1, -1.f, 1.f, 1.f, 1.f);

	rot = makeRotationMat4Degrees(90.f, makeVec3(0.f, 0.f, 1.f)); 
	CHECK_VECTOR4_APPROX(rot * v1, -1.f, 1.f, 1.f, 1.f);

	rot = makeRotationAroundZAxisMat4Degrees(90.f);
	CHECK_VECTOR4_APPROX(rot * v1, -1.f, 1.f, 1.f, 1.f);

	// shear
	she = makeShearXAxisMat4(3.f, 1.f);
	CHECK_VECTOR4(she * v123, 1.f, 5.f, 4.f, 1.f);

	she = makeShearYAxisMat4(3.f, 1.f);
	CHECK_VECTOR4(she * v123, 7.f, 2.f, 5.f, 1.f);

	she = makeShearZAxisMat4(3.f, 1.f);
	CHECK_VECTOR4(she * v123, 10.f, 5.f, 3.f, 1.f);

	she = makeShearMat4(1.f, 2.f, 3.f, 4.f, 5.f, 6.f);
	CHECK_VECTOR4(she * v123, 22.f, 21.f, 13.f, 1.f);
	
	she = makeMat4FromRows(
		1.f, -1.f, 0.f, 2.f,
		1.f, 1.f, 0.f, 3.f,
		0.f, 1.f, 1.f, 4.f,
		0.f, 0.f, 0.f, 1.f);

	she = shearXAxisMat4(she, 1.f, 2.f);
	CHECK_VECTOR4(she * v123, 0.f, 7.f, 12.f, 1.f);

	she = shearYAxisMat4(she, 3.f, 4.f);
	CHECK_VECTOR4(she * v123, 0.f, 19.f, 38.f, 1.f);

	she = shearZAxisMat4(she, 5.f, 6.f);
	CHECK_VECTOR4(she * v123, -18.f, 175.f, 335.f, 1.f);

	she = shearMat4(she, -1.f, -2.f, -3.f, 1.f, 2.f, 3.f);
	CHECK_VECTOR4(she * v123, -26.f, 231.f, 447.f, 1.f);
}

TEST_CASE("mat4 orthographic projection")
{
	mat4 ortho = makeOrthographicMat4(-10.f, 10.f, -5.f, 5.f, 0.f, -10.f);
	vec4 v = makeVec4(5.f, 5.f, -5.f, 1.f);
	vec4 res = ortho * v;
	CHECK_VECTOR4_APPROX(res, 0.5f, 1.f, -2.f, 1.f);
}

TEST_CASE("mat4 perspective projection")
{
	mat4 persp = makePerspectiveMat4(90.0f, 2.0f, 5.0f, 15.0f);

	vec4 v = makeVec4(5.0f, 5.0f, -15.0f, 1.f);
	vec4 res = persp * v; 
	CHECK_VECTOR4(res, 2.5f, 5.f, 15.f, 15.f);

	v = makeVec4(5.0f, 5.0f, -5.0f, 1.f);
	res = persp * v; 
	CHECK_VECTOR4(res, 2.5f, 5.f, -5.f, 5.f);
}
