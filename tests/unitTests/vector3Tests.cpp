#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include "util.cpp"


using namespace fm;

TEST_CASE("vec3 constructors and getters")
{
	vec3 a(1.f, 5.f, -3.f);
	CHECK(a.x() == 1.f);
	CHECK(a.u() == 1.f);
	CHECK(a.r() == 1.f);
	CHECK(a.y() == 5.f);
	CHECK(a.v() == 5.f);
	CHECK(a.g() == 5.f);
	CHECK(a.z() == -3.f);
	CHECK(a.w() == -3.f);
	CHECK(a.b() == -3.f);

	float storage[3];
	a.storeTo(storage);
	CHECK(storage[0] == 1.f);
	CHECK(storage[1] == 5.f);
	CHECK(storage[2] == -3.f);

	vec3 b(2.f);
	CHECK(b.x() == 2.f);
	CHECK(b.y() == 2.f);
	CHECK(b.z() == 2.f);

	vec3 c;
	CHECK(c.x() == 0.f);
	CHECK(c.y() == 0.f);
	CHECK(c.z() == 0.f);

	float arr[3] = {1.f, 2.f, 3.f};
	vec3 d(arr);
	REQUIRE(d.x() == 1.f);
	REQUIRE(d.y() == 2.f);
	REQUIRE(d.z() == 3.f);

	vec2 e;

	e = d.xy();
	CHECK(e.x() == 1.f);
	CHECK(e.y() == 2.f);
	e = d.uv();
	CHECK(e.x() == 1.f);
	CHECK(e.y() == 2.f);
	e = d.rg();
	CHECK(e.x() == 1.f);
	CHECK(e.y() == 2.f);

	e = d.yx();
	CHECK(e.x() == 2.f);
	CHECK(e.y() == 1.f);
	e = d.vu();
	CHECK(e.x() == 2.f);
	CHECK(e.y() == 1.f);
	e = d.gr();
	CHECK(e.x() == 2.f);
	CHECK(e.y() == 1.f);

	e = d.yz();
	CHECK(e.x() == 2.f);
	CHECK(e.y() == 3.f);
	e = d.vw();
	CHECK(e.x() == 2.f);
	CHECK(e.y() == 3.f);
	e = d.gb();
	CHECK(e.x() == 2.f);
	CHECK(e.y() == 3.f);

	e = d.zy();
	CHECK(e.x() == 3.f);
	CHECK(e.y() == 2.f);
	e = d.wv();
	CHECK(e.x() == 3.f);
	CHECK(e.y() == 2.f);
	e = d.bg();
	CHECK(e.x() == 3.f);
	CHECK(e.y() == 2.f);

	e = d.xz();
	CHECK(e.x() == 1.f);
	CHECK(e.y() == 3.f);
	e = d.uw();
	CHECK(e.x() == 1.f);
	CHECK(e.y() == 3.f);
	e = d.rb();
	CHECK(e.x() == 1.f);
	CHECK(e.y() == 3.f);

	e = d.zx();
	CHECK(e.x() == 3.f);
	CHECK(e.y() == 1.f);
	e = d.wu();
	CHECK(e.x() == 3.f);
	CHECK(e.y() == 1.f);
	e = d.br();
	CHECK(e.x() == 3.f);
	CHECK(e.y() == 1.f);

	e = d.xx();
	CHECK(e.x() == 1.f);
	CHECK(e.y() == 1.f);
	e = d.uu();
	CHECK(e.x() == 1.f);
	CHECK(e.y() == 1.f);
	e = d.rr();
	CHECK(e.x() == 1.f);
	CHECK(e.y() == 1.f);

	e = d.yy();
	CHECK(e.x() == 2.f);
	CHECK(e.y() == 2.f);
	e = d.vv();
	CHECK(e.x() == 2.f);
	CHECK(e.y() == 2.f);
	e = d.gg();
	CHECK(e.x() == 2.f);
	CHECK(e.y() == 2.f);

	e = d.zz();
	CHECK(e.x() == 3.f);
	CHECK(e.y() == 3.f);
	e = d.ww();
	CHECK(e.x() == 3.f);
	CHECK(e.y() == 3.f);
	e = d.bb();
	CHECK(e.x() == 3.f);
	CHECK(e.y() == 3.f);

	vec3 f;

	f = d.xyz();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 3.f);
	f = d.uvw();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 3.f);
	f = d.rgb();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 3.f);

	f = d.yzx();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 1.f);
	f = d.vwu();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 1.f);
	f = d.gbr();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 1.f);

	f = d.zxy();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 2.f);
	f = d.wuv();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 2.f);
	f = d.brg();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 2.f);

	f = d.zyx();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 1.f);
	f = d.wvu();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 1.f);
	f = d.bgr();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 1.f);

	f = d.xzy();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 2.f);
	f = d.uwv();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 2.f);
	f = d.rbg();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 2.f);

	f = d.yxz();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 3.f);
	f = d.vuw();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 3.f);
	f = d.grb();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 3.f);

	f = d.xxy();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 2.f);
	f = d.uuv();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 2.f);
	f = d.rrg();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 2.f);
	
	f = d.xxz();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 3.f);
	f = d.uuw();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 3.f);
	f = d.rrb();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 3.f);

	f = d.yyx();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 1.f);
	f = d.vvu();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 1.f);
	f = d.ggr();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 1.f);

	f = d.yyz();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 3.f);
	f = d.vvw();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 3.f);
	f = d.ggb();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 3.f);

	f = d.zzx();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 1.f);
	f = d.wwu();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 1.f);
	f = d.bbr();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 1.f);

	f = d.zzy();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 2.f);
	f = d.wwv();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 2.f);
	f = d.bbg();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 2.f);

	f = d.yxx();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 1.f);
	f = d.vuu();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 1.f);
	f = d.grr();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 1.f);

	f = d.zxx();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 1.f);
	f = d.wuu();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 1.f);
	f = d.brr();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 1.f);

	f = d.xyy();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 2.f);
	f = d.uvv();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 2.f);
	f = d.rgg();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 2.f);

	f = d.zyy();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 2.f);
	f = d.wvv();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 2.f);
	f = d.bgg();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 2.f);

	f = d.xzz();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 3.f);
	f = d.uww();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 3.f);
	f = d.rbb();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 3.f);

	f = d.yzz();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 3.f);
	f = d.vww();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 3.f);
	f = d.gbb();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 3.f);

	f = d.xyx();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 1.f);
	f = d.uvu();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 1.f);
	f = d.rgr();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 1.f);

	f = d.xzx();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 1.f);
	f = d.uwu();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 1.f);
	f = d.rbr();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 1.f);

	f = d.yxy();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 2.f);
	f = d.vuv();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 2.f);
	f = d.grg();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 2.f);

	f = d.yzy();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 2.f);
	f = d.vwv();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 2.f);
	f = d.gbg();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 2.f);

	f = d.zxz();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 3.f);
	f = d.wuw();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 3.f);
	f = d.brb();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 3.f);

	f = d.zyz();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 3.f);
	f = d.wvw();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 3.f);
	f = d.bgb();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 3.f);

	f = d.xxx();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 1.f);
	f = d.uuu();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 1.f);
	f = d.rrr();
	CHECK(f.x() == 1.f);
	CHECK(f.y() == 1.f);
	CHECK(f.z() == 1.f);

	f = d.yyy();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 2.f);
	f = d.vvv();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 2.f);
	f = d.ggg();
	CHECK(f.x() == 2.f);
	CHECK(f.y() == 2.f);
	CHECK(f.z() == 2.f);

	f = d.zzz();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 3.f);
	f = d.www();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 3.f);
	f = d.bbb();
	CHECK(f.x() == 3.f);
	CHECK(f.y() == 3.f);
	CHECK(f.z() == 3.f);
}

TEST_CASE("vec3 setters")
{
	vec3 a;
	a.setX(-1.f);
	a.setY(2.f);
	a.setZ(-3.f);
	CHECK(a.x() == -1.f);
	CHECK(a.y() == 2.f);
	CHECK(a.z() == -3.f);

	vec3 b;
	b.setY(2.f);
	b.setX(-1.f);
	b.setZ(-3.f);
	CHECK(b.x() == -1.f);
	CHECK(b.y() == 2.f);
	CHECK(b.z() == -3.f);
}

TEST_CASE("vec3 operations")
{
	vec3 a(2.f, 3.f, 4.f); 	
	vec3 b(-2.f, 5.f, 1.f); 	

	INFO("a == (" << a.x() << ", " << a.y() << ", " << a.z() << ")");
	INFO("b == (" << b.x() << ", " << b.y() << ", " << b.z() << ")");

	auto addRes = a + b;
	CHECK(addRes.x() == 0.f);
	CHECK(addRes.y() == 8.f);
	CHECK(addRes.z() == 5.f);

	auto subRes = a - b;
	CHECK(subRes.x() == 4.f);
	CHECK(subRes.y() == -2.f);
	CHECK(subRes.z() == 3.f);

	auto addAsignmentRes = a;
	addAsignmentRes += b;
	CHECK(addAsignmentRes.x() == 0.f);
	CHECK(addAsignmentRes.y() == 8.f);
	CHECK(addAsignmentRes.z() == 5.f);

	auto subAsignmentRes = a;
	subAsignmentRes -= b;
	CHECK(subAsignmentRes.x() == 4.f);
	CHECK(subAsignmentRes.y() == -2.f);
	CHECK(subAsignmentRes.z() == 3.f);

	auto scalarMulRes1 = a * 4.5f;
	CHECK(scalarMulRes1.x() == 9.f);
	CHECK(scalarMulRes1.y() == 13.5f);
	CHECK(scalarMulRes1.z() == 18.f);

	auto scalarMulRes2 = 4.5f * a;
	CHECK(scalarMulRes2.x() == 9.f);
	CHECK(scalarMulRes2.y() == 13.5f);
	CHECK(scalarMulRes2.z() == 18.f);

	auto scalarDivRes = a / 2.f;
	CHECK(scalarDivRes.x() == 1.f);
	CHECK(scalarDivRes.y() == 1.5f);
	CHECK(scalarDivRes.z() == 2.f);

	auto hadamardMulRes = hadamardMul(a, b); 
	CHECK(hadamardMulRes.x() == -4.f);
	CHECK(hadamardMulRes.y() == 15.f);
	CHECK(hadamardMulRes.z() == 4.f);

	auto hadamardDivRes = hadamardDiv(a, b); 
	CHECK(hadamardDivRes.x() == -1.f);
	CHECK(hadamardDivRes.y() == 0.6f);
	CHECK(hadamardDivRes.z() == 4.f);

	auto negatedB = -b;
	CHECK(negatedB.x() == 2.f);
	CHECK(negatedB.y() == -5.f);
	CHECK(negatedB.z() == -1.f);

	auto minRes = min(a, b);
	CHECK(minRes.x() == -2.f);
	CHECK(minRes.y() == 3.f);
	CHECK(minRes.z() == 1.f);

	auto maxRes = max(a, b);
	CHECK(maxRes.x() == 2.f);
	CHECK(maxRes.y() == 5.f);
	CHECK(maxRes.z() == 4.f);

	auto absoluteB = abs(b);
	CHECK(absoluteB.x() == 2);
	CHECK(absoluteB.y() == 5);
	CHECK(absoluteB.z() == 1);

	auto normalizedB = normalize(b);
	CHECK(normalizedB.x() == floatCmp(b.x() / sqrt(30)));
	CHECK(normalizedB.y() == floatCmp(b.y() / sqrt(30)));
	CHECK(normalizedB.z() == floatCmp(b.z() / sqrt(30)));
	
	vec3 c(1.f, 0.f, 0.f);
	vec3 d(0.f, 1.f, 0.f);
	auto crossRes = cross(c, d);
	CHECK(crossRes.x() == 0.f);
	CHECK(crossRes.y() == 0.f);
	CHECK(crossRes.z() == 1.f);

	vec3 e(2,3,4);
	vec3 f(5,6,7);
	auto crossRes2 = cross(e, f);
	CHECK(crossRes2.x() == -3.f);
	CHECK(crossRes2.y() == 6.f);
	CHECK(crossRes2.z() == -3.f);

	CHECK(dot(a, b) == 15.f);
	CHECK(sumOfElements(b) == 4.f);
	CHECK(length(b) == floatCmp(sqrt(30.f)));
	CHECK(lengthSquared(b) == 30.f);
}
