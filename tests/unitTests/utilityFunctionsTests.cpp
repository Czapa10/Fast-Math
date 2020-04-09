#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

TEST_CASE("utility functions")
{
	CHECK(5.f == Min(5.f, 10.f));
	CHECK(5.f == Max(5.f, -1.f));
	CHECK(5.0 == Min(5.0, 10.0));
	CHECK(5.0 == Max(5.0, -1.0));
	CHECK(5 == Min(5, 10));
	CHECK(5 == Max(5, -1));
	CHECK(5u == Min(5u, 10u));
	CHECK(5u == Max(5u, 0u));

	CHECK(5.f == Abs(5.f));
	CHECK(5.f == Abs(-5.f));
	CHECK(5.0 == Abs(5.0));
	CHECK(5.0 == Abs(-5.0));
	CHECK(5 == Abs(5));
	CHECK(5 == Abs(-5));

	CHECK(DegreesToRadians(30.f) == FloatCmp(0.5235f));
	CHECK(DegreesToRadians(30.0) == FloatCmp(0.5235));
	CHECK(RadiansToDegrees(0.5235f) == FloatCmp(30.f));
	CHECK(RadiansToDegrees(0.5235) == FloatCmp(30.0));
}
