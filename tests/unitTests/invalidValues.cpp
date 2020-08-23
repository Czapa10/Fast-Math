
TEST_CASE("invalid values")
{
	CHECK(!IsValid(InvalidV2));
	CHECK(!IsValid(InvalidV3));
	CHECK(!IsValid(InvalidV4));
	CHECK(!IsValid(InvalidV2d));
	CHECK(!IsValid(InvalidV3d));
	CHECK(!IsValid(InvalidV4d));
	CHECK(!IsValid(InvalidV2i));
	CHECK(!IsValid(InvalidV3i));
	CHECK(!IsValid(InvalidV4i));
	CHECK(!IsValid(InvalidV2u));
	CHECK(!IsValid(InvalidV3u));
	CHECK(!IsValid(InvalidV4u));
	CHECK(!IsValid(InvalidV2u16));
	CHECK(!IsValid(InvalidV3u16));
	CHECK(!IsValid(InvalidV4u16));
	CHECK(!IsValid(InvalidV2u8));
	CHECK(!IsValid(InvalidV3u8));
	CHECK(!IsValid(InvalidV4u8));
	CHECK(!IsValid(InvalidRect2));
	CHECK(!IsValid(InvalidRect2d));
	CHECK(!IsValid(InvalidRect2i));
	CHECK(!IsValid(InvalidRect2u));
	CHECK(!IsValid(InvalidMat4));
}

