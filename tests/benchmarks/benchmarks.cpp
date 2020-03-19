#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#define FAST_MATH_IMPLEMENTATION
#include "../../FastMath.h"

using namespace fm;

#define benchmark(name, expression, result) bench.run(name, [&]{result = expression;}).doNotOptimizeAway(result);

int main() 
{
	ankerl::nanobench::Bench bench;

	// vec2
	{
		vec2 a(1.f, 2.f);
		vec2 b(-5.f, 10.f);
		vec2 res;
		float res2;

		benchmark("vec2 addition", a + b, res);
		benchmark("vec2 subtraction", a - b, res);
		benchmark("vec2 scalar multiplication", a * 5.f, res);
		benchmark("vec2 scalar division", a / 5.f, res);
		benchmark("vec2 hadamard multiplication", hadamardMul(a, b), res);
		benchmark("vec2 hadamard division", hadamardDiv(a, b), res);
	}

	// vec2d
	{
		vec2d a(1.0, 2.0);
		vec2d b(-5.0, 10.0);
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
		vec2i a(1, 2);
		vec2i b(-5, 10);
		vec2i res;
		int res2;

		benchmark("vec2i addition", a + b, res);
		benchmark("vec2i subtraction", a - b, res);
		benchmark("vec2i scalar multiplication", a * 5.0, res);
		//benchmark("vec2i scalar division", a / 5.0, res); // TODO
		benchmark("vec2i hadamard multiplication", hadamardMul(a, b), res);
		//benchmark("vec2i hadamard division", hadamardDiv(a, b), res); TODO
	}

	// vec2u
	{
		vec2u a(1, 2);
		vec2u b(5, 10);
		vec2u res;

		benchmark("vec2u addition", a + b, res);
		benchmark("vec2u subtraction", a - b, res);
		benchmark("vec2u scalar multiplication", a * 5.0, res);
		//benchmark("vec2u scalar division", a / 5.0, res); TODO
		benchmark("vec2u hadamard multiplication", hadamardMul(a, b), res);
		//benchmark("vec2u hadamard division", hadamardDiv(a, b), res); TODO
	}
}


