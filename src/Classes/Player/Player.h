#ifndef __Player_H_INCLUDED__		// if Node.h hasn't been included yet...
#define __Player_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "Classes/GameObject/GameObject.h"
class Player : public GameObject {
public:
	Player(float x, float y) : GameObject(x, y, 70, 140, "content/player.png") {};
	void jump() {
		if (isGrounded) {
			pos->y -= 10;
			accelerationY = -24;
		}
		else {
			accelerationY -= 0.2;
		}
	};
};

#endif