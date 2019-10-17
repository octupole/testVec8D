//============================================================================
// Name        : testVec4.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#define MAX_VECTOR_SIZE 512
#include "../simdVectors/vectorclass.h"
#include <random>
#include <iostream>
#include <vector>
#include "Timers.hpp"
#include <memory>
#include "aligned_malloc.hpp"


#if INSTRSET == 7 || INSTRSET == 8
	using Vec4Bd=Vec4d;
	using Vec4Bui=Vec4ui;
	using Vec4Bi=Vec4i;
	using Vec4Buq=Vec4uq;
	using Vec4Bdb=Vec4db;
	using Vec4Bqb=Vec4qb;
	namespace simd{
	constexpr bool defineSimd{true};
	constexpr int vectorSize{4};
	}
#elif INSTRSET >=9
	using Vec4Bd=Vec8d;
	using Vec4Bui=Vec8uq;
	using Vec4Bi=Vec8q;
	using Vec4Buq=Vec8uq;
	using Vec4Bdb=Vec8db;
	using Vec4Bqb=Vec8qb;
	namespace simd{
	constexpr bool defineSimd{true};
	constexpr int vectorSize{8};
	}
#else
	using Vec4Bd=Vec4d;
	using Vec4Bui=Vec4ui;
	using Vec4Bi=Vec4i;
	using Vec4Buq=Vec4uq;
	using Vec4Bdb=Vec4db;
	using Vec4Bqb=Vec4qb;
	namespace simd{
	constexpr bool defineSimd{false};
	constexpr int vectorSize{1};
	}
#endif


using namespace std;

template <typename T>
constexpr T ceilingMultiple(T m, size_t N){
	return static_cast<T>(m%N?m+(N-m%N):m);
}
int main() {
	double three{3.0},result{0};
	Vec4Bd var0,var1,vthree;
    std::mt19937 gen;
    double Start{0.0},End{10.0};
    std::uniform_real_distribution<double>distr(Start, End);
    const size_t N{100000};
    unsigned int Nd=simd::vectorSize;
	timers::elTime Timer0;
	size_t NN=ceilingMultiple(N,Nd);
	size_t NN4d{NN/Nd};

	double * v=(double *)Aligned::aligned_malloc(64,NN*sizeof(double));
	cout << NN4d<< " -- "<< NN <<endl;

	Vec4Bd * di4=(Vec4Bd*)Aligned::aligned_malloc(64,NN4d*sizeof(Vec4Bd));

    for(size_t o{};o<NN;o++)
    	v[o]=distr(gen);
    unsigned K{0};
	Timer0();
    for(size_t o{};o<NN;o+=Nd){
    	di4[K++].load(&v[o]);
    }
    cout << " here 1 " << Nd<<endl;
    var1=0.0;
	vthree=three;
	unsigned int M=0;
	while(M <  10000){
		for(size_t o{};o< NN4d; o++){
			var1+=vthree*di4[o];
		}
		M++;
	}
	Timer0();
	cout << "elapsed 1 " << Timer0.ElapsedTime() <<endl;
	result=horizontal_add(var1);
	cout << result<<endl;
	Timer0();
	M=0;
	double vvar1{0};
	while(M <  10000){
		for(size_t o{};o< NN; o++){
			vvar1+=three*v[o];
		}
		M++;
	}
	Timer0();
	cout << "elapsed 1 " << Timer0.ElapsedTime() <<endl;

	result=vvar1;
	cout << result<<endl;
	return 0;
}
