#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanoBench.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

using namespace fm;

#define Benchmark(name, expRession, Result) Bench.run(name, [&]{Result = expRession;}).doNotOptimizeAway(Result);
#define BenchmarkNoAssign(name, expRession, Result) Bench.run(name, [&]{expRession;}).doNotOptimizeAway(Result);

int32_t main() 
{
	ankerl::nanobench::Bench Bench;

	// utility functions
	{
		float aF = 5.f;
		float bF = -2.f;
		float ResF;

		double aD = 5.0;
		double bD = -2.0;
		double ResD;

		int32_t aI = 5;
		int32_t bI = -2;
		int32_t ResI;

		uint32_t aU = 5;
		uint32_t bU = 2;
		uint32_t ResU;

		Benchmark("Min float", Min(aF, bF), ResF);
		Benchmark("Max float", Max(aF, bF), ResF);
		Benchmark("Min double", Min(aD, bD), ResD);
		Benchmark("Max double", Max(aD, bD), ResD);
		Benchmark("Min int32_t", Min(aI, bI), ResI);
		Benchmark("Max int32_t", Max(aI, bI), ResI);
		Benchmark("Min uint32_t", Min(aU, bU), ResU);
		Benchmark("Max uint32_t", Max(aU, bU), ResU);
	}

	// v2
	{
		vec2 A = Vec2(1.f, 2.f);
		vec2 B = Vec2(-5.f, 10.f);
		vec2 Res;
		float Res2;

		Benchmark("vec2 addition", A + B, Res);
		Benchmark("vec2 subtraction", A - B, Res);
		Benchmark("vec2 scalar multiplication", A * 5.f, Res);
		Benchmark("vec2 scalar division", A / 5.f, Res);
	}

	// v2
	{
		v2 A = V2(1.f, 2.f);
		v2 B = V2(-5.f, 10.f);
		v2 Res;
		float Res2;

		BenchmarkNoAssign("v2 SetX", Res.SetX(5.f), Res);
		BenchmarkNoAssign("v2 SetY", Res.SetY(5.f), Res);

		Benchmark("v2 x()", A.X(), Res2);
		Benchmark("v2 u()", A.U(), Res2);
		Benchmark("v2 y()", A.Y(), Res2);
		Benchmark("v2 v()", A.V(), Res2);
		Benchmark("v2 yx()", A.YX(), Res);
		Benchmark("v2 xx()", A.XX(), Res);
		Benchmark("v2 yy()", A.YY(), Res);

		float Arr[2] = {1.f, 2.f};
		__m128 M = _mm_set1_ps(5.f);
		Benchmark("V2FromMemory", V2FromMemory(Arr), Res);
		Benchmark("V2(x, y)", V2(1.f, 2.f), Res);
		Benchmark("V2(a)", V2(5.f), Res);
		Benchmark("V2(__m128)", V2(M), Res);
		Benchmark("V2()", V2(), Res);

		float Storage[2];
		BenchmarkNoAssign("v2 Store", Store(Storage, A), Storage);

		Benchmark("v2 addition", A + B, Res);
		Benchmark("v2 subtraction", A - B, Res);
		Benchmark("v2 addition with assignement", Res += A, Res);
		Benchmark("v2 subtraction with assignement", Res -= A, Res);
		Benchmark("v2 Hadamard multiplication", HadamardMul(A, B), Res);
		Benchmark("v2 Hadamard division", HadamardDiv(A, B), Res);
		Benchmark("v2 scalar multiplication", A * 5.f, Res);
		Benchmark("v2 scalar division", A / 5.f, Res);
		Benchmark("v2 negation", Res = -A, Res);
		Benchmark("v2 dot product", Dot(A, B), Res2);
		Benchmark("v2 Min", Min(A, B), Res);
		Benchmark("v2 Max", Max(A, B), Res);
		Benchmark("v2 Abs", Abs(A), Res);
		Benchmark("v2 SumOfElements", SumOfElements(A), Res2);
		Benchmark("v2 Length", Length(A), Res2);
		Benchmark("v2 LengthSquared", LengthSquared(A), Res2);
		Benchmark("v2 Normalize", Normalize(A), Res);
		Benchmark("v2 Clamp", Clamp(A, A, B), Res);
		Benchmark("v2 Lerp", Lerp(A, B, 0.5f), Res);

		bool Res3;
		Benchmark("v2 ==", A == B, Res3);
		Benchmark("v2 !=", A != B, Res3);
		Benchmark("v2 EqualsMask", EqualsMask(A, B), Res);
		Benchmark("v2 GreaterMask", GreaterMask(A, B), Res);
		Benchmark("v2 GreaterOrEqualMask", GreaterOrEqualMask(A, B), Res);
		Benchmark("v2 LesserMask", LesserMask(A, B), Res);
		Benchmark("v2 LesserOrEqualMask", LesserOrEqualMask(A, B), Res);
	}

	// v2d
	{
		v2d A = V2d(1.0, 2.0);
		v2d B = V2d(-5.0, 10.0);
		v2d Res;
		double Res2;

		Benchmark("v2d addition", A + B, Res);
		Benchmark("v2d subtraction", A - B, Res);
		Benchmark("v2d scalar multiplication", A * 5.0, Res);
		Benchmark("v2d scalar division", A / 5.0, Res);
		Benchmark("v2d Hadamard multiplication", HadamardMul(A, B), Res);
		Benchmark("v2d Hadamard division", HadamardDiv(A, B), Res);
	}

	// v2i
	{
		v2i A = V2i(1, 2);
		v2i B = V2i(-5, 10);
		v2i Res;
		int32_t Res2;

		Benchmark("v2i addition", A + B, Res);
		Benchmark("v2i subtraction", A - B, Res);
		Benchmark("v2i scalar multiplication", A * 5.0, Res);
		Benchmark("v2i Hadamard multiplication", HadamardMul(A, B), Res);
	}

	// v2u
	{
		v2u A = V2u(1, 2);
		v2u B = V2u(5, 10);
		v2u Res;

		Benchmark("v2u addition", A + B, Res);
		Benchmark("v2u subtraction", A - B, Res);
		Benchmark("v2u scalar multiplication", A * 5.0, Res);
		Benchmark("v2u Hadamard multiplication", HadamardMul(A, B), Res);
	}

	// mat4
	{
		mat4 I = Mat4Identity();
		BenchmarkNoAssign("RotateDegrees()", RotateDegrees(&I, 50.f, 1.f, 0.5f, 0.f), I);
	}
}


