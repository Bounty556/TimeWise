#pragma once

namespace Soul
{
	/*
	Used to keep track of an elapsed amount of time - useful for profiling code.

	The timer only starts with Start() is called, and can be stopped with Stop(). At any time,
	whether the timer is running or not, GetElapsedMilliseconds() can be called to get the current number
	of elapsed milliseconds.
	*/
	class Timer
	{
	public:
		Timer();

		/*
		Starts the timer.
		*/
		void Start();

		/*
		Stops the timer.
		*/
		void Stop();

		/*
		Sets the current accumulated performance counts to 0.
		*/
		void Reset();

		/*
		Returns the length of time this timer has been running in (floating point) milliseconds
		and resets the counter to 0.
		*/
		float GetDeltaTime();

		/*
		Returns the length of time this timer has been running in milliseconds.
		*/
		long long GetElapsedMilliseconds();

		/*
		Returns the length of time this timer has been running in microseconds.
		*/
		long long GetElapsedMicroseconds();

	private:
		/*
		Our actual elapsed performance counts.
		*/
		long long m_ElapsedPerformanceCounts;

		/*
		This should be updated everytime we start, stop, or get current time.
		*/
		long long m_LastCounterCheckpoint;

		/*
		Whether this timer is currently running or not.
		*/
		bool m_IsRunning;
	};
}