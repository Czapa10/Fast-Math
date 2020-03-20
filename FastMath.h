#ifndef FAST_MATH_H
#define FAST_MATH_H

#include <emmintrin.h>

// TODO: make FM_INLINE work on all compilers

#define FM_INLINE __forceinline
#define FM_CALL __vectorcall

namespace fm {

FM_INLINE float min(float a, float b);
FM_INLINE float max(float a, float b);
FM_INLINE double min(double a, double b);
FM_INLINE double max(double a, double b);
FM_INLINE int min(int a, int b);
FM_INLINE int max(int a, int b);
FM_INLINE unsigned min(unsigned a, unsigned b);
FM_INLINE unsigned max(unsigned a, unsigned b);

FM_INLINE float abs(float a); 
FM_INLINE double abs(double a); 
FM_INLINE int abs(int a);

struct vec2
{
	FM_INLINE explicit vec2(const float* v); 
	FM_INLINE vec2(float x, float y);
	FM_INLINE explicit vec2(float a);
	FM_INLINE vec2(__m128 m);
	FM_INLINE vec2();

	FM_INLINE float FM_CALL x() const;
	FM_INLINE float FM_CALL u() const { return x(); }
	FM_INLINE float FM_CALL left() const { return x(); }
	FM_INLINE float FM_CALL width() const { return x(); }

	FM_INLINE float FM_CALL y() const;
	FM_INLINE float FM_CALL v() const { return y(); }
	FM_INLINE float FM_CALL top() const { return y(); }
	FM_INLINE float FM_CALL height() const { return y(); }

	FM_INLINE vec2 FM_CALL yx() const;
	FM_INLINE vec2 FM_CALL vu() const;

	FM_INLINE void FM_CALL storeTo(float* mem);

	FM_INLINE void FM_CALL setX(float x);
	FM_INLINE void FM_CALL setY(float y); 

	__m128 m;
};
FM_INLINE vec2 FM_CALL operator+(vec2 a, vec2 b);
FM_INLINE vec2 FM_CALL operator-(vec2 a, vec2 b);
FM_INLINE vec2& FM_CALL operator+=(vec2& a, vec2 b);
FM_INLINE vec2& FM_CALL operator-=(vec2& a, vec2 b);
FM_INLINE vec2 FM_CALL hadamardMul(vec2 a, vec2 b);
FM_INLINE vec2 FM_CALL hadamardDiv(vec2 a, vec2 b);
FM_INLINE vec2 FM_CALL operator*(vec2 v, float scalar);
FM_INLINE vec2 FM_CALL operator*(float scalar, vec2 v);
FM_INLINE vec2 FM_CALL operator/(vec2 v, float scalar); 
FM_INLINE vec2 FM_CALL operator-(vec2 v); 
FM_INLINE vec2 FM_CALL min(vec2 a, vec2 b); 
FM_INLINE vec2 FM_CALL max(vec2 a, vec2 b); 
FM_INLINE vec2 FM_CALL abs(vec2 v); 
// TODO: Add more operators, dot, length, normalize

struct vec2d
{
	FM_INLINE explicit vec2d(const double* v);
	FM_INLINE vec2d(double x, double y);
	FM_INLINE explicit vec2d(double a);
	FM_INLINE vec2d(__m128d m);
	FM_INLINE vec2d();

	FM_INLINE double FM_CALL x() const;
	FM_INLINE double FM_CALL u() const { return x(); }
	FM_INLINE double FM_CALL left() const { return x(); }
	FM_INLINE double FM_CALL width() const { return x(); }

	FM_INLINE double FM_CALL y() const;
	FM_INLINE double FM_CALL v() const { return y(); }
	FM_INLINE double FM_CALL height() const { return y(); }
	FM_INLINE double FM_CALL top() const { return y(); }

	FM_INLINE vec2d FM_CALL yx() const;
	FM_INLINE vec2d FM_CALL vu() const;

	FM_INLINE void FM_CALL storeTo(double* mem);
	FM_INLINE void FM_CALL storeTo16ByteAligned(double* mem);

	FM_INLINE void FM_CALL setX(double x);
	FM_INLINE void FM_CALL setY(double y);

	__m128d m;
};
FM_INLINE vec2d FM_CALL operator+(vec2d a, vec2d b); 
FM_INLINE vec2d FM_CALL operator-(vec2d a, vec2d b);
FM_INLINE vec2d& FM_CALL operator+=(vec2d& a, vec2d b);
FM_INLINE vec2d& FM_CALL operator-=(vec2d& a, vec2d b);
FM_INLINE vec2d FM_CALL hadamardMul(vec2d a, vec2d b);
FM_INLINE vec2d FM_CALL hadamardDiv(vec2d a, vec2d b);
FM_INLINE vec2d FM_CALL operator*(vec2d v, double scalar);
FM_INLINE vec2d FM_CALL operator*(double scalar, vec2d v);
FM_INLINE vec2d FM_CALL operator/(vec2d v, double scalar);
FM_INLINE vec2d FM_CALL operator-(vec2d v); 
FM_INLINE vec2d FM_CALL min(vec2d a, vec2d b); 
FM_INLINE vec2d FM_CALL max(vec2d a, vec2d b); 
FM_INLINE vec2d FM_CALL abs(vec2d v); 
// TODO: Add more operators, dot, length, normalize

struct vec2i
{
	FM_INLINE explicit vec2i(const int* v);
	FM_INLINE vec2i(int x, int y);
	FM_INLINE explicit vec2i(int a); 
	FM_INLINE vec2i(__m128i m); 
	FM_INLINE vec2i();

	FM_INLINE int FM_CALL x() const;
	FM_INLINE int FM_CALL u() const { return x(); }
	FM_INLINE int FM_CALL left() const { return x(); }
	FM_INLINE int FM_CALL width() const { return x(); }

	FM_INLINE int FM_CALL y() const;
	FM_INLINE int FM_CALL v() const { return y(); }
	FM_INLINE int FM_CALL top() const { return y(); }
	FM_INLINE int FM_CALL height() const { return y(); }

	FM_INLINE vec2i FM_CALL yx() const;
	FM_INLINE vec2i FM_CALL vu() const;

	FM_INLINE void FM_CALL storeTo(int* mem); 

	FM_INLINE void FM_CALL setX(int x);
	FM_INLINE void FM_CALL setY(int y);

	__m128i m;
};
FM_INLINE vec2i FM_CALL operator+(vec2i a, vec2i b);
FM_INLINE vec2i FM_CALL operator-(vec2i a, vec2i b); 
FM_INLINE vec2i& FM_CALL operator+=(vec2i& a, vec2i b);
FM_INLINE vec2i& FM_CALL operator-=(vec2i& a, vec2i b);
FM_INLINE vec2i FM_CALL hadamardMul(vec2i a, vec2i b);
FM_INLINE vec2i FM_CALL operator*(vec2i v, int scalar); 
FM_INLINE vec2i FM_CALL operator*(int scalar, vec2i v);
FM_INLINE vec2i FM_CALL operator-(vec2i v); 
FM_INLINE vec2i FM_CALL min(vec2i a, vec2i b); 
FM_INLINE vec2i FM_CALL max(vec2i a, vec2i b); 
FM_INLINE vec2i FM_CALL abs(vec2i v); 
// TODO: Add hadamardDiv() and operator/ - Maybe I can do that using cast instructions?
// TODO: Add more operators


struct vec2u
{
	FM_INLINE explicit vec2u(const unsigned* v); 
	FM_INLINE vec2u(unsigned x, unsigned y); 
	FM_INLINE explicit vec2u(unsigned a);
	FM_INLINE vec2u(__m128i m);
	FM_INLINE vec2u();

	FM_INLINE unsigned FM_CALL x() const;
	FM_INLINE unsigned FM_CALL u() const { return x(); }
	FM_INLINE unsigned FM_CALL left() const { return x(); }
	FM_INLINE unsigned FM_CALL width() const { return x(); }

	FM_INLINE unsigned FM_CALL y() const;
	FM_INLINE unsigned FM_CALL v() const { return y(); }
	FM_INLINE unsigned FM_CALL top() const { return y(); }
	FM_INLINE unsigned FM_CALL height() const { return y(); }

	FM_INLINE vec2u FM_CALL yx() const;
	FM_INLINE vec2u FM_CALL vu() const;

	FM_INLINE void FM_CALL storeTo(unsigned* mem);

	FM_INLINE void FM_CALL setX(unsigned x);
	FM_INLINE void FM_CALL setY(unsigned y);

	__m128i m;
};
FM_INLINE vec2u FM_CALL operator+(vec2u a, vec2u b);
FM_INLINE vec2u FM_CALL operator-(vec2u a, vec2u b);
FM_INLINE vec2u& FM_CALL operator+=(vec2u& a, vec2u b);
FM_INLINE vec2u& FM_CALL operator-=(vec2u& a, vec2u b);
FM_INLINE vec2u FM_CALL hadamardMul(vec2u a, vec2u b);
FM_INLINE vec2u FM_CALL operator*(vec2u v, unsigned scalar); 
FM_INLINE vec2u FM_CALL operator*(unsigned scalar, vec2u v);
FM_INLINE vec2i FM_CALL min(vec2i a, vec2i b); 
FM_INLINE vec2i FM_CALL max(vec2i a, vec2i b); 
// TODO: Add hadamardDiv() and operator/
// TODO: Add more operators

}

#endif // FAST_MATH_H


#ifdef FM_IMPLEMENTATION

#include <math.h>

#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
	#include <smmintrin.h>
#endif

namespace fm {

///////////////////////
// utility functions //
///////////////////////
FM_INLINE float min(float a, float b) {
	return a < b ? a : b; 
}
FM_INLINE float max(float a, float b) {
	return a > b ? a : b;
}
FM_INLINE double min(double a, double b) {
	return a < b ? a : b; 
}
FM_INLINE double max(double a, double b) {
	return a > b ? a : b;
}
FM_INLINE int min(int a, int b) {
	return a < b ? a : b; 
}
FM_INLINE int max(int a, int b) {
	return a > b ? a : b;
}
FM_INLINE unsigned min(unsigned a, unsigned b) {
	return a < b ? a : b; 
}
FM_INLINE unsigned max(unsigned a, unsigned b) {
	return a > b ? a : b;
}
FM_INLINE float abs(float a) {
	return a < 0 ? -a : a;
}
FM_INLINE double abs(double a) {
	return a < 0 ? -a : a;
}
FM_INLINE int abs(int a) {
	return a < 0 ? -a : a;
}

////////////////////
// vec2 functions //
////////////////////
FM_INLINE vec2::vec2(const float* v) {
	m = _mm_set_ps(0.f, 0.f, v[1], v[0]); 
}  
FM_INLINE vec2::vec2(float x, float y) {
	m = _mm_set_ps(0.f, 0.f, y, x); 
} 
FM_INLINE vec2::vec2(float a) {
	m = _mm_set1_ps(a); 
}
FM_INLINE vec2::vec2(__m128 m) 
	:m(m) {}
FM_INLINE vec2::vec2() {
	m = _mm_setzero_ps(); 
} 
FM_INLINE float FM_CALL vec2::x() const { 
	return _mm_cvtss_f32(m); 
}
FM_INLINE float FM_CALL vec2::y() const {
	return _mm_cvtss_f32(_mm_shuffle_ps(m, m, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE vec2 FM_CALL vec2::yx() const {
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE vec2 FM_CALL vec2::vu() const { 
	return vec2(_mm_shuffle_ps(m, m, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE void FM_CALL vec2::storeTo(float* mem) {
	mem[0] = x();
	mem[1] = y(); 
} 
FM_INLINE void FM_CALL vec2::setX(float x) {
	m = _mm_move_ss(m, _mm_set_ss(x)); 
}
FM_INLINE void FM_CALL vec2::setY(float y) { 
	__m128 temp = _mm_move_ss(m, _mm_set_ss(y));
	temp = _mm_shuffle_ps(temp, temp, _MM_SHUFFLE(3, 2, 0, 0));
	m = _mm_move_ss(temp, m);
}  
FM_INLINE vec2 FM_CALL operator+(vec2 a, vec2 b) {
	a.m = _mm_add_ps(a.m, b.m);
	return a; 
}
FM_INLINE vec2 FM_CALL operator-(vec2 a, vec2 b) {
	a.m = _mm_sub_ps(a.m, b.m);
	return a; 
}
FM_INLINE vec2& FM_CALL operator+=(vec2& a, vec2 b) {
	a.m = _mm_add_ps(a.m, b.m);
	return a; 
}
FM_INLINE vec2& FM_CALL operator-=(vec2& a, vec2 b) {
	a.m = _mm_sub_ps(a.m, b.m);
	return a; 
}
FM_INLINE vec2 FM_CALL hadamardMul(vec2 a, vec2 b) {
	a.m = _mm_mul_ps(a.m, b.m);
	return a;
}
FM_INLINE vec2 FM_CALL hadamardDiv(vec2 a, vec2 b) {
	a.m = _mm_div_ps(a.m, b.m);
	return a; 
}
FM_INLINE vec2 FM_CALL operator*(vec2 v, float scalar) {
	v.m = _mm_mul_ps(v.m, _mm_set1_ps(scalar)); 
	return v; 
}
FM_INLINE vec2 FM_CALL operator*(float scalar, vec2 v) { 
	v.m = _mm_mul_ps(v.m, _mm_set1_ps(scalar));
	return v; 
}
FM_INLINE vec2 FM_CALL operator/(vec2 v, float scalar) {
	v.m = _mm_div_ps(v.m, _mm_set1_ps(scalar));
	return v; 
}
FM_INLINE vec2 FM_CALL operator-(vec2 v) {
	// TODO: Maybe do that with static sign mask
	v.m = _mm_sub_ps(_mm_setzero_ps(), v.m);
	return v;
}
FM_INLINE vec2 FM_CALL min(vec2 a, vec2 b) {
	a.m = _mm_min_ps(a.m, b.m);
	return a;
}
FM_INLINE vec2 FM_CALL max(vec2 a, vec2 b) {
	a.m = _mm_max_ps(a.m, b.m);
	return a;
}
FM_INLINE vec2 FM_CALL abs(vec2 v) {
	__m128 signMask = _mm_castsi128_ps(_mm_set1_epi32(0x80000000)); 
	v.m = _mm_andnot_ps(signMask, v.m);
	return v;
}

/////////////////////
// vec2d functions //
/////////////////////
FM_INLINE vec2d::vec2d(const double* v) { 
	m = _mm_set_pd(v[1], v[0]); 
} 
FM_INLINE vec2d::vec2d(double x, double y) {
	m = _mm_set_pd(y, x); 
} 
FM_INLINE vec2d::vec2d(double a) {
	m = _mm_set1_pd(a);
} 
FM_INLINE vec2d::vec2d(__m128d m) 
	: m(m) {}
FM_INLINE vec2d::vec2d() { 
	m = _mm_setzero_pd(); 
}
FM_INLINE double FM_CALL vec2d::x() const {
	return _mm_cvtsd_f64(m);
}
FM_INLINE double FM_CALL vec2d::y() const { 
	return _mm_cvtsd_f64(_mm_shuffle_pd(m, m, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE vec2d FM_CALL vec2d::yx() const { 
	return vec2d(_mm_shuffle_pd(m, m, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE vec2d FM_CALL vec2d::vu() const { 
	return vec2d(_mm_shuffle_pd(m, m, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE void FM_CALL vec2d::storeTo(double* mem) { 
	_mm_storeu_pd(mem, m); 
} 
FM_INLINE void FM_CALL vec2d::storeTo16ByteAligned(double* mem) {
	_mm_store_pd(mem, m); 
}
FM_INLINE void FM_CALL vec2d::setX(double x) {
	m = _mm_move_sd(m, _mm_set_sd(x)); 
}
FM_INLINE void FM_CALL vec2d::setY(double y) {
	m = _mm_unpacklo_pd(m, _mm_set_sd(y)); 
}
FM_INLINE vec2d FM_CALL operator+(vec2d a, vec2d b) {
	a.m = _mm_add_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d FM_CALL operator-(vec2d a, vec2d b) {
	a.m = _mm_sub_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d& FM_CALL operator+=(vec2d& a, vec2d b) {
	a.m = _mm_add_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d& FM_CALL operator-=(vec2d& a, vec2d b) {
	a.m = _mm_sub_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d FM_CALL hadamardMul(vec2d a, vec2d b) {
	a.m = _mm_mul_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d FM_CALL hadamardDiv(vec2d a, vec2d b) {
	a.m = _mm_div_pd(a.m, b.m);
	return a; 
}
FM_INLINE vec2d FM_CALL operator*(vec2d v, double scalar) {
	v.m = _mm_mul_pd(v.m, _mm_set1_pd(scalar));
	return v; 
}
FM_INLINE vec2d FM_CALL operator*(double scalar, vec2d v) {
	v.m = _mm_mul_pd(v.m, _mm_set1_pd(scalar));
	return v; 
} 
FM_INLINE vec2d FM_CALL operator/(vec2d v, double scalar) {
	v.m = _mm_div_pd(v.m, _mm_set1_pd(scalar));
	return v; 
}
FM_INLINE vec2d FM_CALL operator-(vec2d v) {
	v.m = _mm_sub_pd(_mm_setzero_pd(), v.m);
	return v;
}
FM_INLINE vec2d FM_CALL min(vec2d a, vec2d b) {
	a.m = _mm_min_pd(a.m, b.m);
	return a;
}
FM_INLINE vec2d FM_CALL max(vec2d a, vec2d b) {
	a.m = _mm_max_pd(a.m, b.m);
	return a;
}
FM_INLINE vec2d FM_CALL abs(vec2d v) {
	__m128d signBits = _mm_castsi128_pd(_mm_set1_epi32(0x80000000));
	v.m = _mm_andnot_pd(signBits, v.m);
	return v;
}

/////////////////////
// vec2i functions //
/////////////////////
FM_INLINE vec2i::vec2i(const int* v) {
	m = _mm_set_epi32(0, 0, v[1], v[0]); 
}
FM_INLINE vec2i::vec2i(int x, int y) {
	m = _mm_set_epi32(0, 0, y, x); 
}
FM_INLINE vec2i::vec2i(int a) { 
	m = _mm_set1_epi32(a); 
}
FM_INLINE vec2i::vec2i(__m128i m) 
	:m(m) {}
FM_INLINE vec2i::vec2i() {
	m = _mm_setzero_si128();
}
FM_INLINE int FM_CALL vec2i::x() const { 
	return _mm_cvtsi128_si32(m); 
} 
FM_INLINE int FM_CALL vec2i::y() const {
	return _mm_cvtsi128_si32(_mm_shuffle_epi32(m, _MM_SHUFFLE(1, 1, 1, 1))); 
} 
FM_INLINE vec2i FM_CALL vec2i::yx() const {
	return vec2i(_mm_shuffle_epi32(m, _MM_SHUFFLE(0, 0, 0, 1)));
}
FM_INLINE vec2i FM_CALL vec2i::vu() const {
	return vec2i(_mm_shuffle_epi32(m, _MM_SHUFFLE(0, 0, 0, 1)));
}
FM_INLINE void FM_CALL vec2i::storeTo(int* mem) {
	mem[0] = x();
	mem[1] = y();
} 
FM_INLINE vec2i FM_CALL operator+(vec2i a, vec2i b) {
	a.m = _mm_add_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2i FM_CALL operator-(vec2i a, vec2i b) {
	a.m = _mm_sub_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2i& FM_CALL operator+=(vec2i& a, vec2i b) {
	a.m = _mm_add_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2i& FM_CALL operator-=(vec2i& a, vec2i b) {
	a.m = _mm_sub_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2i FM_CALL operator-(vec2i v) {
	v.m = _mm_sub_epi32(_mm_setzero_si128(), v.m);
	return v;
}
#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INLINE void FM_CALL vec2i::setX(int x) {
	m = _mm_insert_epi32(m, x, 0);
}
FM_INLINE void FM_CALL vec2i::setY(int y) {
	m = _mm_insert_epi32(m, y, 1);
}
FM_INLINE vec2i FM_CALL operator*(vec2i v, int scalar) {
	v.m = _mm_mullo_epi32(v.m, _mm_set1_epi32(scalar));
	return v; 
}
FM_INLINE vec2i FM_CALL operator*(int scalar, vec2i v) {
	v.m =_mm_mullo_epi32(v.m, _mm_set1_epi32(scalar)); 
	return v; 
}
FM_INLINE vec2i FM_CALL hadamardMul(vec2i a, vec2i b) {
	a.m = _mm_mullo_epi32(a.m, b.m); 
	return a; 
}
FM_INLINE vec2i FM_CALL min(vec2i a, vec2i b) {
	a.m = _mm_min_epi32(a.m, b.m);
	return a;
}
FM_INLINE vec2i FM_CALL max(vec2i a, vec2i b) {
	a.m = _mm_max_epi32(a.m, b.m);
	return a;
}
FM_INLINE vec2i FM_CALL abs(vec2i v) {
	v.m = _mm_abs_epi32(v.m);
	return v;
}
#else // SSE 2 implementations 
FM_INLINE void FM_CALL vec2i::setX(int x) {
	int arr[4];
	_mm_store_si128((__m128i*)arr, m);
	arr[0] = x;
	m = _mm_load_si128((__m128i*)arr);
}
FM_INLINE void FM_CALL vec2i::setY(int y) {
	int arr[4];
	_mm_store_si128((__m128i*)arr, m);
	arr[1] = y;
	m = _mm_load_si128((__m128i*)arr);
	// TODO: This code is repeated. Make utility function!
}
FM_INLINE vec2i FM_CALL hadamardMul(vec2i a, vec2i b) {
	int aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = aArr[0] * bArr[0]; 
	aArr[1] = aArr[1] * bArr[1]; 
	return vec2i(aArr);
}
FM_INLINE vec2i FM_CALL operator*(vec2i v, int scalar) {
	int vArr[4];
	_mm_store_si128((__m128i*)vArr, v.m);
	vArr[0] *= scalar;
	vArr[1] *= scalar;
	return vec2i(vArr);
	// TODO: This code is repeated. Make utility function!
}
FM_INLINE vec2i FM_CALL operator*(int scalar, vec2i v) {
	return v * scalar; 
}
FM_INLINE vec2i FM_CALL min(vec2i a, vec2i b) {
	int aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = min(aArr[0], bArr[0]);
	aArr[1] = min(aArr[1], bArr[1]);
	return vec2i(aArr);
}
FM_INLINE vec2i FM_CALL max(vec2i a, vec2i b) {
	int aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = max(aArr[0], bArr[0]);
	aArr[1] = max(aArr[1], bArr[1]);
	return vec2i(aArr);
	// TODO: This code is repeated. Make utility function!
}
FM_INLINE vec2i FM_CALL abs(vec2i v) {
	int vArr[4];
	_mm_store_si128((__m128i*)vArr, v.m);
	vArr[0] = abs(vArr[0]);
	vArr[1] = abs(vArr[1]);
	return vec2i(vArr);
}
#endif

/////////////////////
// vec2u functions //
/////////////////////
FM_INLINE vec2u::vec2u(const unsigned* v) {
	m = _mm_set_epi32(0, 0, v[1], v[0]); 
}
FM_INLINE vec2u::vec2u(unsigned x, unsigned y) {
	m = _mm_set_epi32(0, 0, y, x); 
}
FM_INLINE vec2u::vec2u(unsigned a) {
	m = _mm_set1_epi32(a); 
} 
FM_INLINE vec2u::vec2u(__m128i m) 
	:m(m) {}
FM_INLINE vec2u::vec2u() {
	m = _mm_setzero_si128(); 
}
FM_INLINE unsigned FM_CALL vec2u::x() const {
	return (unsigned)_mm_cvtsi128_si32(m); 
} 
FM_INLINE unsigned FM_CALL vec2u::y() const { 
	return (unsigned)_mm_cvtsi128_si32(_mm_shuffle_epi32(m, _MM_SHUFFLE(1, 1, 1, 1))); 
}
FM_INLINE vec2u FM_CALL vec2u::yx() const { 
	return vec2u(_mm_shuffle_epi32(m, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE vec2u FM_CALL vec2u::vu() const {
	return vec2u(_mm_shuffle_epi32(m, _MM_SHUFFLE(0, 0, 0, 1))); 
}
FM_INLINE void FM_CALL vec2u::storeTo(unsigned* mem) {
	mem[0] = x();
	mem[1] = y();
} 
FM_INLINE vec2u FM_CALL operator+(vec2u a, vec2u b) {
	a.m = _mm_add_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2u FM_CALL operator-(vec2u a, vec2u b) {
	a.m = _mm_sub_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2u& FM_CALL operator+=(vec2u& a, vec2u b) {
	a.m = _mm_add_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2u& FM_CALL operator-=(vec2u& a, vec2u b) {
	a.m = _mm_sub_epi32(a.m, b.m);
	return a; 
}
#ifndef FM_USE_SSE2_INSTEAD_OF_SSE4
FM_INLINE void FM_CALL vec2u::setX(unsigned x) {
	m = _mm_insert_epi32(m, (int)x, 0);
}
FM_INLINE void FM_CALL vec2u::setY(unsigned y) {
	m = _mm_insert_epi32(m, (int)y, 1);
}
FM_INLINE vec2u FM_CALL operator*(vec2u v, unsigned scalar) {
	v.m = _mm_mullo_epi32(v.m, _mm_set1_epi32(scalar)); 
	return v; 
}
FM_INLINE vec2u FM_CALL operator*(unsigned scalar, vec2u v) {
	v.m =_mm_mullo_epi32(v.m, _mm_set1_epi32(scalar));
	return v; 
}
FM_INLINE vec2u FM_CALL hadamardMul(vec2u a, vec2u b) {
	a.m = _mm_mullo_epi32(a.m, b.m);
	return a; 
}
FM_INLINE vec2u FM_CALL min(vec2u a, vec2u b) {
	a.m = _mm_min_epu32(a.m, b.m);
	return a;
}
FM_INLINE vec2u FM_CALL max(vec2u a, vec2u b) {
	a.m = _mm_max_epu32(a.m, b.m);
	return a;
}
#else // SSE 2 implementations
FM_INLINE void FM_CALL vec2u::setX(unsigned x) {
	unsigned arr[4];
	_mm_store_si128((__m128i*)arr, m);
	arr[0] = x;
	m = _mm_load_si128((__m128i*)arr);
}
FM_INLINE void FM_CALL vec2u::setY(unsigned y) {
	unsigned arr[4];
	_mm_store_si128((__m128i*)arr, m);
	arr[1] = y;
	m = _mm_load_si128((__m128i*)arr);
	// TODO: This code is repeated. Make utility function!
}
FM_INLINE vec2u FM_CALL hadamardMul(vec2u a, vec2u b) {
	unsigned aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = aArr[0] * bArr[0]; 
	aArr[1] = aArr[1] * bArr[1]; 
	return vec2u(aArr);
}
FM_INLINE vec2u FM_CALL operator*(vec2u v, unsigned scalar) {
	unsigned vArr[4];
	_mm_store_si128((__m128i*)vArr, v.m);
	vArr[0] *= scalar;
	vArr[1] *= scalar;
	return vec2u(vArr);
}
FM_INLINE vec2u FM_CALL operator*(unsigned scalar, vec2u v) {
	return v * scalar;
}
FM_INLINE vec2u FM_CALL min(vec2u a, vec2u b) {
	unsigned aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = min(aArr[0], bArr[0]);
	aArr[1] = min(aArr[1], bArr[1]);
	return vec2u(aArr);
}
FM_INLINE vec2u FM_CALL max(vec2u a, vec2u b) {
	unsigned aArr[4], bArr[4];
	_mm_store_si128((__m128i*)aArr, a.m);
	_mm_store_si128((__m128i*)bArr, b.m);
	aArr[0] = max(aArr[0], bArr[0]);
	aArr[1] = max(aArr[1], bArr[1]);
	return vec2u(aArr);
}
#endif

} // !namespace fm

#endif // FM_IMPLEMENTATION

