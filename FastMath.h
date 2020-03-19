#ifndef FAST_MATH_H
#define FAST_MATH_H

#ifdef FM_USE_SSE2_INSTEAD_OF_SSE4
	#include <emmintrin.h>
#else
	#include <smmintrin.h>
#endif

// TODO: make FM_INLINE work on all compilers

#define FM_INLINE __forceinline
#define FM_CALL __vectorcall

namespace fm {

struct vec2
{
	FM_INLINE explicit vec2(const float* v) { m = _mm_set_ps(0.f, 0.f, v[1], v[0]); }  
	FM_INLINE vec2(float x, float y) { m = _mm_set_ps(0.f, 0.f, y, x); } 
	FM_INLINE explicit vec2(float a) { m = _mm_set1_ps(a); }
	FM_INLINE vec2(__m128 m) : m(m) {}
	FM_INLINE vec2() {} 

	FM_INLINE float FM_CALL x() const { return _mm_cvtss_f32(m); }
	FM_INLINE float FM_CALL u() const { return x(); } 
	FM_INLINE float FM_CALL left() const { return x(); } 
	FM_INLINE float FM_CALL width() const { return x(); } 

	FM_INLINE float FM_CALL y() const { return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(1, 1, 1, 1))); }
	FM_INLINE float FM_CALL v() const { return y(); } 
	FM_INLINE float FM_CALL top() const { return y(); } 
	FM_INLINE float FM_CALL height() const { return y(); } 

	FM_INLINE vec2 FM_CALL yx() const { return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 1))); }
	FM_INLINE vec2 FM_CALL vu() const { return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 1))); }

	FM_INLINE void FM_CALL storeTo(float* mem) { mem[0] = x(); mem[1] = y(); } 

	// TODO: Add setters
	// TODO: Add array style access

	__m128 m;
};
FM_INLINE vec2 FM_CALL operator+(vec2 a, vec2 b) { a.m = _mm_add_ps(a.m, b.m); return a; }
FM_INLINE vec2 FM_CALL operator-(vec2 a, vec2 b) { a.m = _mm_sub_ps(a.m, b.m); return a; }
FM_INLINE vec2 FM_CALL hadamardMul(vec2 a, vec2 b) { a.m = _mm_mul_ps(a.m, b.m); return a; }
FM_INLINE vec2 FM_CALL hadamardDiv(vec2 a, vec2 b) { a.m = _mm_div_ps(a.m, b.m); return a; }
FM_INLINE vec2 FM_CALL operator*(vec2 v, float scalar) { v.m = _mm_mul_ps(v.m, _mm_set1_ps(scalar)); return v; }
FM_INLINE vec2 FM_CALL operator*(float scalar, vec2 v) { v.m = _mm_mul_ps(v.m, _mm_set1_ps(scalar)); return v; }
FM_INLINE vec2 FM_CALL operator/(vec2 v, float scalar) { v.m = _mm_div_ps(v.m, _mm_set1_ps(scalar)); return v; }
// TODO: Add more operators, dot, length, normalize

struct vec2d
{
	FM_INLINE explicit vec2d(const double* v) { _mm_set_pd(v[1], v[0]); } 
	FM_INLINE vec2d(double x, double y) { m = _mm_set_pd(y, x); } 
	FM_INLINE explicit vec2d(double a) { m = _mm_set1_pd(a); } 
	FM_INLINE vec2d(__m128d m) : m(m) {}
	FM_INLINE vec2d() {}

	FM_INLINE double FM_CALL x() const { return _mm_cvtsd_f64(m); }
	FM_INLINE double FM_CALL u() const { return x(); }
	FM_INLINE double FM_CALL left() const { return x(); }
	FM_INLINE double FM_CALL width() const { return x(); }

	FM_INLINE double FM_CALL y() const { return _mm_cvtsd_f64(_mm_shuffle_pd(m, m, _MM_SHUFFLE(1, 1, 1, 1))); }
	FM_INLINE double FM_CALL v() const { return y(); }
	FM_INLINE double FM_CALL height() const { return y(); }
	FM_INLINE double FM_CALL top() const { return y(); }

	FM_INLINE vec2d FM_CALL yx() const { return vec2d(_mm_shuffle_pd(m, m, _MM_SHUFFLE(0, 0, 0, 1))); }
	FM_INLINE vec2d FM_CALL vu() const { return vec2d(_mm_shuffle_pd(m, m, _MM_SHUFFLE(0, 0, 0, 1))); }

	FM_INLINE void FM_CALL storeTo(double* mem) { _mm_storeu_pd(mem, m); } 
	FM_INLINE void FM_CALL storeTo16ByteAligned(double* mem) { _mm_store_pd(mem, m); }

	// TODO: Add setters
	// TODO: Add array style access

	__m128d m;
};
FM_INLINE vec2d FM_CALL operator+(vec2d a, vec2d b) { a.m = _mm_add_pd(a.m, b.m); return a; }
FM_INLINE vec2d FM_CALL operator-(vec2d a, vec2d b) { a.m = _mm_sub_pd(a.m, b.m); return a; }
FM_INLINE vec2d FM_CALL hadamardMul(vec2d a, vec2d b) { a.m = _mm_mul_pd(a.m, b.m); return a; }
FM_INLINE vec2d FM_CALL hadamardDiv(vec2d a, vec2d b) { a.m = _mm_div_pd(a.m, b.m); return a; }
FM_INLINE vec2d FM_CALL operator*(vec2d v, double scalar) { v.m = _mm_mul_pd(v.m, _mm_set1_pd(scalar)); return v; }
FM_INLINE vec2d FM_CALL operator*(double scalar, vec2d v) { v.m = _mm_mul_pd(v.m, _mm_set1_pd(scalar)); return v; } 
FM_INLINE vec2d FM_CALL operator/(vec2d v, double scalar) { v.m = _mm_div_pd(v.m, _mm_set1_pd(scalar)); return v; }
// TODO: Add more operators, dot, length, normalize

struct vec2i
{
	FM_INLINE explicit vec2i(const int* v) { m = _mm_set_epi32(0, 0, v[1], v[0]); }
	FM_INLINE vec2i(int x, int y) { m = _mm_set_epi32(0, 0, y, x); } 
	FM_INLINE explicit vec2i(int a) { m = _mm_set1_epi32(a); }
	FM_INLINE vec2i(__m128i m) :m(m) {}
	FM_INLINE vec2i() {}

	FM_INLINE int FM_CALL x() const { return _mm_cvtsi128_si32(m); } 
	FM_INLINE int FM_CALL u() const { return x(); }
	FM_INLINE int FM_CALL left() const { return x(); }
	FM_INLINE int FM_CALL width() const { return x(); }

	FM_INLINE int FM_CALL y() const { return _mm_cvtsi128_si32(_mm_shuffle_epi32(m, _MM_SHUFFLE(1, 1, 1, 1))); } 
	FM_INLINE int FM_CALL v() const { return y(); }
	FM_INLINE int FM_CALL top() const { return y(); }
	FM_INLINE int FM_CALL height() const { return y(); }

	FM_INLINE vec2i FM_CALL yx() const { return vec2i(_mm_shuffle_epi32(m, _MM_SHUFFLE(0, 0, 0, 1))); }
	FM_INLINE vec2i FM_CALL vu() const { return vec2i(_mm_shuffle_epi32(m, _MM_SHUFFLE(0, 0, 0, 1))); }

	FM_INLINE void FM_CALL storeTo(int* mem) { mem[0] = x(); mem[1] = y(); } 

	// TODO: Add setters
	// TODO: Add array style access

	__m128i m;
};
FM_INLINE vec2i FM_CALL operator+(vec2i a, vec2i b) { a.m = _mm_add_epi32(a.m, b.m); return a; }
FM_INLINE vec2i FM_CALL operator-(vec2i a, vec2i b) { a.m = _mm_sub_epi32(a.m, b.m); return a; }
FM_INLINE vec2i FM_CALL hadamardMul(vec2i a, vec2i b);
FM_INLINE vec2i FM_CALL operator*(vec2i v, int scalar); 
FM_INLINE vec2i FM_CALL operator*(int scalar, vec2i v);
// TODO: Add hadamardDiv() and operator/
// TODO: Add more operators


struct vec2u
{
	FM_INLINE explicit vec2u(const unsigned* v) { m = _mm_set_epi32(0, 0, v[1], v[0]); }
	FM_INLINE vec2u(unsigned x, unsigned y) { m = _mm_set_epi32(0, 0, y, x); }
	FM_INLINE explicit vec2u(unsigned a) { m = _mm_set1_epi32(a); } 
	FM_INLINE vec2u(__m128i m) :m(m) {}
	FM_INLINE vec2u() {}

	FM_INLINE unsigned FM_CALL x() const { return (unsigned)_mm_cvtsi128_si32(m); } 
	FM_INLINE unsigned FM_CALL u() const { return x(); }
	FM_INLINE unsigned FM_CALL left() const { return x(); }
	FM_INLINE unsigned FM_CALL width() const { return x(); }

	FM_INLINE unsigned FM_CALL y() const { return (unsigned)_mm_cvtsi128_si32(_mm_shuffle_epi32(m, _MM_SHUFFLE(1, 1, 1, 1))); } 
	FM_INLINE unsigned FM_CALL v() const { return y(); }
	FM_INLINE unsigned FM_CALL top() const { return y(); }
	FM_INLINE unsigned FM_CALL height() const { return y(); }

	FM_INLINE vec2u FM_CALL yx() const { return vec2u(_mm_shuffle_epi32(m, _MM_SHUFFLE(0, 0, 0, 1))); }
	FM_INLINE vec2u FM_CALL vu() const { return vec2u(_mm_shuffle_epi32(m, _MM_SHUFFLE(0, 0, 0, 1))); }

	FM_INLINE void FM_CALL storeTo(int* mem) { mem[0] = x(); mem[1] = y(); } 

	// TODO: Add setters
	// TODO: Add array style access

	__m128i m;
};
FM_INLINE vec2u FM_CALL operator+(vec2u a, vec2u b) { a.m = _mm_add_epi32(a.m, b.m); return a; }
FM_INLINE vec2u FM_CALL operator-(vec2u a, vec2u b) { a.m = _mm_sub_epi32(a.m, b.m); return a; }
FM_INLINE vec2u FM_CALL hadamardMul(vec2u a, vec2u b);
FM_INLINE vec2u FM_CALL operator*(vec2u v, unsigned scalar); 
FM_INLINE vec2u FM_CALL operator*(unsigned scalar, vec2u v);
// TODO: Add hadamardDiv() and operator/
// TODO: Add more operators

}

#endif // FAST_MATH_H


#ifdef FAST_MATH_IMPLEMENTATION

#include <math.h>

namespace fm {

/////////////////////
// vec2i functions //
/////////////////////
#ifdef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INLINE vec2i FM_CALL hadamardMul(vec2i a, vec2i b) 
{
	int aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = aArr[0] * bArr[0]; 
	aArr[1] = aArr[1] * bArr[1]; 
	return vec2i(aArr);
}

FM_INLINE vec2i FM_CALL operator*(vec2i v, int scalar) 
{
	int vArr[4];
	_mm_store_si128((__m128i*)vArr, v.m);
	vArr[0] *= scalar;
	vArr[1] *= scalar;
	return vec2i(vArr);
}
FM_INLINE vec2i FM_CALL operator*(int scalar, vec2i v) { return v * scalar; }
#else
FM_INLINE vec2i FM_CALL operator*(vec2i v, int scalar) { v.m = _mm_mullo_epi32(v.m, _mm_set1_epi32(scalar)); return v; }
FM_INLINE vec2i FM_CALL operator*(int scalar, vec2i v) { v.m =_mm_mullo_epi32(v.m, _mm_set1_epi32(scalar)); return v; }
FM_INLINE vec2i FM_CALL hadamardMul(vec2i a, vec2i b) { a.m = _mm_mullo_epi32(a.m, b.m); return a; }
#endif

/////////////////////
// vec2u functions //
/////////////////////
#ifdef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INLINE vec2u FM_CALL hadamardMul(vec2u a, vec2u b) 
{
	unsigned aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = aArr[0] * bArr[0]; 
	aArr[1] = aArr[1] * bArr[1]; 
	return vec2u(aArr);
}

FM_INLINE vec2u FM_CALL operator*(vec2u v, unsigned scalar) 
{
	unsigned vArr[4];
	_mm_store_si128((__m128i*)vArr, v.m);
	vArr[0] *= scalar;
	vArr[1] *= scalar;
	return vec2u(vArr);
}
FM_INLINE vec2u FM_CALL operator*(unsigned scalar, vec2u v) { return v * scalar; }
#else
FM_INLINE vec2u FM_CALL operator*(vec2u v, unsigned scalar) { v.m = _mm_mullo_epi32(v.m, _mm_set1_epi32(scalar)); return v; }
FM_INLINE vec2u FM_CALL operator*(unsigned scalar, vec2u v) { v.m =_mm_mullo_epi32(v.m, _mm_set1_epi32(scalar)); return v; }
FM_INLINE vec2u FM_CALL hadamardMul(vec2u a, vec2u b) { a.m = _mm_mullo_epi32(a.m, b.m); return a; }
#endif

} // !namespace fm

#endif FAST_MATH_IMPLEMENTATION

