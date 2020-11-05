#include "Timer.h"

#include <Windows.h>

namespace Soul
{
	Timer::Timer() :
		m_ElapsedPerformanceCounts(0),
		m_LastCounterCheckpoint(0),
		m_IsRunning(false)
	{

	}

	void Timer::Start()
	{
		if (!m_IsRunning)
		{
			m_IsRunning = true;

			LARGE_INTEGER performanceCount;
			QueryPerformanceCounter(&performanceCount);
			m_LastCounterCheckpoint = performanceCount.QuadPart;
		}
	}

	void Timer::Stop()
	{
		if (m_IsRunning)
		{
			m_IsRunning = false;

			LARGE_INTEGER performanceCount;
			QueryPerformanceCounter(&performanceCount);
			m_ElapsedPerformanceCounts += performanceCount.QuadPart - m_LastCounterCheckpoint;
		}
	}

	void Timer::Reset()
	{
		LARGE_INTEGER performanceCount;
		QueryPerformanceCounter(&performanceCount);
		m_LastCounterCheckpoint = performanceCount.QuadPart;
		m_ElapsedPerformanceCounts = 0;
	}

	long long Timer::GetElapsedMilliseconds()
	{
		if (m_IsRunning)
		{
			LARGE_INTEGER performanceCount;
			QueryPerformanceCounter(&performanceCount);
			m_ElapsedPerformanceCounts += performanceCount.QuadPart - m_LastCounterCheckpoint;
			m_LastCounterCheckpoint = performanceCount.QuadPart;
		}

		LARGE_INTEGER performanceFrequency;
		QueryPerformanceFrequency(&performanceFrequency);
		performanceFrequency.QuadPart /= 1000; // We want this in milliseconds, not seconds

		return m_ElapsedPerformanceCounts / performanceFrequency.QuadPart;
	}
}