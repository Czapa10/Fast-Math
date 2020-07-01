
TEST_CASE("vector casting")
{
	CHECK_V2(CastToV2(Vec2(1, 2)), 1, 2);	
	CHECK_V3(CastToV3(Vec3(1, 2, 3)), 1, 2, 3);	
	CHECK_V4(CastToV4(Vec4(1, 2, 3, 4)), 1, 2, 3, 4);	

	CHECK_VEC2(CastToVec2(v2(1, 2)), 1, 2);	
	CHECK_VEC3(CastToVec3(v3(1, 2, 3)), 1, 2, 3);	
	CHECK_VEC4(CastToVec4(v4(1, 2, 3, 4)), 1, 2, 3, 4);	
}
