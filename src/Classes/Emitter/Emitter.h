#ifndef __Emitter_H_INCLUDED__	  // if Node.h hasn't been included yet...
#define __Emitter_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "Classes/Obstacle/Obstacle.h"


class Emitter {
public:
	float mRate = 0;
	float mInterval = 0;
	int counter = 0;
	std::function<void()> emit;
	Emitter(float rate, float interval) {
		mRate = rate;
		mInterval = interval;
	}
	void tick() {
		if (counter > 0) {
			counter--;
			std::cout << counter << std::endl;
		}
		else {
			int minN = 0;
			int maxN = 10000;
			int r = minN + rand() % (maxN + 1 - minN);
			if (r < mRate * maxN) {
				std::cout << "Xac suat dung" << std::endl;
				emit();
				counter = mInterval;
			}
			else {
				std::cout << "Xac suat sai" << std::endl;
			}
		}
	}

};

#endif