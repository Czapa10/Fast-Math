#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS 
#include "doctest.h"

#define FM_IMPLEMENTATION
#include "../../FastMath.h"

#include <string>
#include <cmath>

using namespace fm;

static long long vElements;
static char binaryOutput[128];

#define logRegisterOf(v, name) \
	_mm_store_ps((float*)(&vElements), v.m); \
	for(int i = 0; i < 128; ++i) \
	{ \
		binaryOutput[i] = (vElements >> i) & 1 ? '1' : '0'; \
	} \
	INFO(name << " (binary): " << std::string(binaryOutput)); 

#define logIntRegisterOf(v, name) \
	_mm_store_si128((__m128i*)(&vElements), v.m); \
	for(int i = 0; i < 128; ++i) \
	{ \
		binaryOutput[i] = (vElements >> i) & 1 ? '1' : '0'; \
	} \
	INFO(name << " (binary): " << std::string(binaryOutput)); 

#define floatCmp(x) doctest::Approx(x).epsilon(0.01)

#include "utilityFunctionsTests.cpp"
#include "vector2Tests.cpp"
#include "vector3Tests.cpp"
