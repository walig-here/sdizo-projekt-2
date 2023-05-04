#include "app/utility/Timer.h"
#include <Windows.h>

Timer::Timer(){

    QueryPerformanceFrequency((LARGE_INTEGER*) &frequency);

}

Timer::~Timer(){

}

void Timer::start(){

    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    last_start = (long long int)count.QuadPart;

}

void Timer::stop(){

    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    last_result = (long long int)count.QuadPart - last_start;

}

double Timer::getResult(TimeUnits unit)
{

    switch (unit){
        case miliseconds: return (1000.0 * last_result) / frequency;
        case microseconds: return (1000000.0 * last_result) / frequency;
        default: return (float)last_result / frequency;
    }

}
