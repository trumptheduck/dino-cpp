#ifndef __Clock_H_INCLUDED__	 // if Node.h hasn't been included yet...
#define __Clock_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include <chrono>
#include <cstdio>
#include <iostream>
#include <thread>


class Clock
{
private:
	bool isStopped = false;
	bool isPaused = false;
	int mFps = 30;
	double interval = 1000 / 30;

public:
	std::function<void()> tick;
	void start()
	{
		std::chrono::system_clock::time_point a = std::chrono::system_clock::now();
		std::chrono::system_clock::time_point b = std::chrono::system_clock::now();
		while (!isStopped)
		{
			a = std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> work_time = a - b;

			if (work_time.count() < interval)
			{
				std::chrono::duration<double, std::milli> delta_ms(interval - work_time.count());
				auto delta_ms_duration = std::chrono::duration_cast<std::chrono::milliseconds>(delta_ms);
				std::this_thread::sleep_for(std::chrono::milliseconds(delta_ms_duration.count()));
			}

			b = std::chrono::system_clock::now();
			std::chrono::duration<double, std::milli> sleep_time = b - a;
			if (!isPaused)
			{
				tick();
			}
			// printf("Time: %f \n", (work_time + sleep_time).count());
		}
	}
	Clock(int fps)
	{
		mFps = fps;
		interval = 1000 / mFps;
	}
	void pause()
	{
		isPaused = true;
	}
	void unpause()
	{
		isPaused = false;
	}
	void stop()
	{
		isStopped = true;
	}
};
#endif