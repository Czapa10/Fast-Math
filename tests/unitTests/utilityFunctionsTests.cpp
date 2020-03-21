TEST_CASE("utility functions")
{
	CHECK(5.f == fm::min(5.f, 10.f));
	CHECK(5.f == fm::max(5.f, -1.f));
	CHECK(5.0 == fm::min(5.0, 10.0));
	CHECK(5.0 == fm::max(5.0, -1.0));
	CHECK(5 == fm::min(5, 10));
	CHECK(5 == fm::max(5, -1));
	CHECK(5u == fm::min(5u, 10u));
	CHECK(5u == fm::max(5u, 0u));

	CHECK(5.f == fm::abs(5.f));
	CHECK(5.f == fm::abs(-5.f));
	CHECK(5.0 == fm::abs(5.0));
	CHECK(5.0 == fm::abs(-5.0));
	CHECK(5 == fm::abs(5));
	CHECK(5 == fm::abs(-5));
}
