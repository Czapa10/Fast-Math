#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"

using namespace fm;

TEST_CASE("vec4 constructors and getters") 
{
	vec4 a(1.f, 2.f, 3.f, 4.f);		
	CHECK(a.x() == 1.f);
	CHECK(a.r() == 1.f);
	CHECK(a.y() == 2.f);
	CHECK(a.g() == 2.f);
	CHECK(a.z() == 3.f);
	CHECK(a.b() == 3.f);
	CHECK(a.w() == 4.f);
	CHECK(a.a() == 4.f);

	float storage[4];
	a.storeTo(storage);
	CHECK(storage[0] == 1.f);
	CHECK(storage[1] == 2.f);
	CHECK(storage[2] == 3.f);
	CHECK(storage[3] == 4.f);
	a.storeTo(storage);
	CHECK(storage[0] == 1.f);
	CHECK(storage[1] == 2.f);
	CHECK(storage[2] == 3.f);
	CHECK(storage[3] == 4.f);

	vec4 b(5.f);
	CHECK(b.x() == 5.f);
	CHECK(b.y() == 5.f);
	CHECK(b.z() == 5.f);
	CHECK(b.w() == 5.f);

	vec4 c;
	CHECK(c.x() == 0.f);
	CHECK(c.y() == 0.f);
	CHECK(c.z() == 0.f);
	CHECK(c.w() == 0.f);

	float arr[4] = {1.f, 2.f, 3.f, 4.f};
	vec4 d(arr);
	REQUIRE(d.x() == 1.f);
	REQUIRE(d.y() == 2.f);
	REQUIRE(d.z() == 3.f);
	REQUIRE(d.w() == 4.f);
}
