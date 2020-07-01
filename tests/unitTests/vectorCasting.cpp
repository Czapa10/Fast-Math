
TEST_CASE("vector casting")
{
	CHECK_V2(CastToV2(Vec2(1.f, 2.f)), 1.f, 2.f);	
	CHECK_V3(CastToV3(Vec3(1.f, 2.f, 3.f)), 1.f, 2.f, 3.f);	
	CHECK_V4(CastToV4(Vec4(1.f, 2.f, 3.f, 4.f)), 1.f, 2.f, 3.f, 4.f);	

	CHECK_VEC2(CastToVec2(v2(1, 2)), 1, 2);	
	CHECK_VEC3(CastToVec3(v3(1, 2, 3)), 1, 2, 3);	
	CHECK_VEC4(CastToVec4(V4(1.f, 2.f, 3.f, 4.f)), 1.f, 2.f, 3.f, 4.f);	
}
