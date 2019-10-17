/*
 * Timers.hpp
 *
 *  Created on: Jun 12, 2019
 *      Author: marchi
 */

#ifndef TOOLS_TIMERS_HPP_
#define TOOLS_TIMERS_HPP_
#include <iostream>
#include <chrono>
#include <string>
using std::cout;using std::endl;
using namespace std::chrono;
namespace timers{
struct elTime{
private:
	size_t N{0};
	std::chrono::high_resolution_clock::time_point start;
	std::chrono::high_resolution_clock::time_point finish;
	double factor{1};

	void Start(){start=std::chrono::high_resolution_clock::now();}
	void Finish(){finish=std::chrono::high_resolution_clock::now();}
public:
	elTime(): start{std::chrono::high_resolution_clock::now()}{};
	void operator()(){
		if(!(N%2)) this->Start();
		else {
			this->Finish();
		}
		N++;
	}
	double Val(){return std::chrono::duration<double>(finish - start).count();}
	void setFactor(double x){factor=x;}
	void Elapsed(std::string s=""){
		std::chrono::duration<double> elapsed = (finish - start);
		if(s=="")
			std::cout << "Elapsed time: " << elapsed.count()*factor << " s\n";
		else
			std::cout << "For "+s+" Elapsed time: " << elapsed.count()*factor << " s\n";
	}
	double ElapsedTime(){
		std::chrono::duration<double> elapsed = (finish - start);
		return elapsed.count()*factor;
	}
};

}

#endif /* TOOLS_TIMERS_HPP_ */
