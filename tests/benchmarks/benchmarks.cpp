#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

using namespace fm;

#define benchmark(name, expression, result) bench.run(name, [&]{result = expression;}).doNotOptimizeAway(result);
#define benchmarkNoAssign(name, expression, result) bench.run(name, [&]{expression;}).doNotOptimizeAway(result);

int main() 
{
	ankerl::nanobench::Bench bench;

	// utility functions
	{
		float aF = 5.f;
		float bF = -2.f;
		float resF;

		double aD = 5.0;
		double bD = -2.0;
		double resD;

		int aI = 5;
		int bI = -2;
		int resI;

		unsigned aU = 5;
		unsigned bU = 2;
		unsigned resU;

		benchmark("min float", min(aF, bF), resF);
		benchmark("max float", max(aF, bF), resF);
		benchmark("min double", min(aD, bD), resD);
		benchmark("max double", max(aD, bD), resD);
		benchmark("min int", min(aI, bI), resI);
		benchmark("max int", max(aI, bI), resI);
		benchmark("min unsigned", min(aU, bU), resU);
		benchmark("max unsigned", max(aU, bU), resU);
	}

	// vec2
	{
		vec2 a = makeVec2(1.f, 2.f);
		vec2 b = makeVec2(-5.f, 10.f);
		vec2 res;
		float res2;

		benchmarkNoAssign("vec2 setX", res.setX(5.f), res);
		benchmarkNoAssign("vec2 setY", res.setY(5.f), res);

		benchmark("vec2 x()", a.x(), res2);
		benchmark("vec2 u()", a.u(), res2);
		benchmark("vec2 y()", a.y(), res2);
		benchmark("vec2 v()", a.v(), res2);
		benchmark("vec2 yx()", a.yx(), res);
		benchmark("vec2 xx()", a.xx(), res);
		benchmark("vec2 yy()", a.yy(), res);

		float arr[2] = {1.f, 2.f};
		__m128 m = _mm_set1_ps(5.f);
		benchmark("makeVec2FromMemory", makeVec2FromMemory(arr), res);
		benchmark("makeVec2(x, y)", makeVec2(1.f, 2.f), res);
		benchmark("makeVec2(a)", makeVec2(5.f), res);
		benchmark("makeVec2(__m128)", makeVec2(m), res);
		benchmark("makeZeroVec2", makeZeroVec2(), res);

		float storage[2];
		benchmarkNoAssign("vec2 store", store(storage, a), storage);

		benchmark("vec2 addition", a + b, res);
		benchmark("vec2 subtraction", a - b, res);
		benchmark("vec2 addition with assignement", res += a, res);
		benchmark("vec2 subtraction with assignement", res -= a, res);
		benchmark("vec2 hadamard multiplication", hadamardMul(a, b), res);
		benchmark("vec2 hadamard division", hadamardDiv(a, b), res);
		benchmark("vec2 scalar multiplication", a * 5.f, res);
		benchmark("vec2 scalar division", a / 5.f, res);
		benchmark("vec2 negation", res = -a, res);
		benchmark("vec2 dot product", dot(a, b), res2);
		benchmark("vec2 min", min(a, b), res);
		benchmark("vec2 max", max(a, b), res);
		benchmark("vec2 abs", abs(a), res);
		benchmark("vec2 sumOfElements", abs(a), res);
		benchmark("vec2 length", length(a), res2);
		benchmark("vec2 lengthSquared", lengthSquared(a), res2);
		benchmark("vec2 normalize", normalize(a), res);
		benchmark("vec2 clamp", clamp(a, a, b), res);
		benchmark("vec2 lerp", lerp(a, b, 0.5f), res);

		bool res3;
		benchmark("vec2 ==", a == b, res3);
		benchmark("vec2 !=", a != b, res3);
		benchmark("vec2 equalsMask", equalsMask(a, b), res);
		benchmark("vec2 greaterMask", greaterMask(a, b), res);
		benchmark("vec2 greaterOrEqualMask", greaterOrEqualMask(a, b), res);
		benchmark("vec2 lesserMask", lesserMask(a, b), res);
		benchmark("vec2 lesserOrEqualMask", lesserOrEqualMask(a, b), res);
	}

	// vec2d
	{
		vec2d a = makeVec2d(1.0, 2.0);
		vec2d b = makeVec2d(-5.0, 10.0);
		vec2d res;
		double res2;

		benchmark("vec2d addition", a + b, res);
		benchmark("vec2d subtraction", a - b, res);
		benchmark("vec2d scalar multiplication", a * 5.0, res);
		benchmark("vec2d scalar division", a / 5.0, res);
		benchmark("vec2d hadamard multiplication", hadamardMul(a, b), res);
		benchmark("vec2d hadamard division", hadamardDiv(a, b), res);
	}

	// vec2i
	{
		vec2i a = makeVec2i(1, 2);
		vec2i b = makeVec2i(-5, 10);
		vec2i res;
		int res2;

		benchmark("vec2i addition", a + b, res);
		benchmark("vec2i subtraction", a - b, res);
		benchmark("vec2i scalar multiplication", a * 5.0, res);
		benchmark("vec2i hadamard multiplication", hadamardMul(a, b), res);
	}

	// vec2u
	{
		vec2u a = makeVec2u(1, 2);
		vec2u b = makeVec2u(5, 10);
		vec2u res;

		benchmark("vec2u addition", a + b, res);
		benchmark("vec2u subtraction", a - b, res);
		benchmark("vec2u scalar multiplication", a * 5.0, res);
		benchmark("vec2u hadamard multiplication", hadamardMul(a, b), res);
	}
}


