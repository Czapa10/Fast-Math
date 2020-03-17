#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#define FAST_MATH_IMPLEMENTATION
#include "../../FastMath.h"

using namespace fm;

#define benchmark(name, expression, result) bench.run(name, [&]{result = expression;}).doNotOptimizeAway(result);

int main() 
{
	ankerl::nanobench::Bench bench;

	vec2 a(1.f, 2.f);
	vec2 b(-5.f, 10.f);
	vec2 res;

	benchmark("vec2 addition", a + b, res);
	benchmark("vec2 subtraction", a - b, res);
	benchmark("vec2 scalar multiplication", a * 5.f, res);
	benchmark("vec2 scalar division", a / 5.f, res);
	benchmark("vec2 hadamard multiplication", hadamardMul(a, b), res);
	benchmark("vec2 hadamard division", hadamardDiv(a, b), res);
	benchmark("vec2 dot product", dot(a, b), res);
	benchmark("vec2 length", length(b), res);
	benchmark("vec2 normalize", normalize(b), res);
}


