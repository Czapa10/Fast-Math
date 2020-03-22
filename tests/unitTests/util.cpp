#ifndef TESTS_UTIL
#define TESTS_UTIL

#include <string>
#include <cmath>

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

#endif // TESTS_UTIL
