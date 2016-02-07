#include <chrono>
#include "system.h"
#include <iostream>

void System::step()
{
	using namespace std::chrono;
	auto start = high_resolution_clock::now();
	
	doStep();
	
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<nanoseconds>(end - start).count();
	nsTaken = static_cast<int>(duration);
}
