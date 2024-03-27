#include "Enginepch.h"
#include "Timer.h"




Timer::Timer()
{
	frequency.QuadPart = 0;
	counterToMiliSecond = 0.0;
	previousTimeCounter.QuadPart = 0;
	currentTimeCounter.QuadPart = 0;
	deltaTime = 0.0;
}

void Timer::Init()
{
	QueryPerformanceFrequency(&frequency);
	counterToMiliSecond = 1.0 / (frequency.QuadPart * 0.001);
	QueryPerformanceCounter(&currentTimeCounter);
	previousTimeCounter = currentTimeCounter;
	deltaTime = 0.0;
}

void Timer::TimeUpdate()
{
	QueryPerformanceCounter(&currentTimeCounter);
	
	__int64 deltaTimeCount = currentTimeCounter.QuadPart - previousTimeCounter.QuadPart;
	deltaTime = deltaTimeCount * counterToMiliSecond;

	previousTimeCounter = currentTimeCounter;
}