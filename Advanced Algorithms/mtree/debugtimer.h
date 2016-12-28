#pragma once
#include <chrono>
#include <iostream>

#define TIME_ON false
#if TIME_ON
#define TIME(x) std::cout << "took " << x << " seconds" << std::endl;
#else
#define TIME(x)
#endif

using namespace std::chrono;

class BTimer
{
	public:
		BTimer() : isRunning(false){}
		void Start();
		double GetDeltaTime();
		double Stop();

	private:
		high_resolution_clock::time_point begin;
		high_resolution_clock::time_point lastcheck;
		bool isRunning;

};



void BTimer::Start()
{
	isRunning = true;
	begin = high_resolution_clock::now();
	lastcheck = high_resolution_clock::now();;
}

double BTimer::GetDeltaTime()
{
	if (isRunning)
	{
		high_resolution_clock::time_point check = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(check - lastcheck);
		lastcheck = check;
		return time_span.count();
	}
	return -1.0;
}

double BTimer::Stop()
{
	if (isRunning)
	{
		high_resolution_clock::time_point check = high_resolution_clock::now();
		duration<double> time_span = duration_cast<duration<double>>(check - begin);
		isRunning = false;
		return time_span.count();
	}
	return -1.0;
}