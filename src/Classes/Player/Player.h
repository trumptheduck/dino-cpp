#ifndef __Player_H_INCLUDED__		// if Node.h hasn't been included yet...
#define __Player_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "Classes/GameObject/GameObject.h"
class Player : public GameObject {
public:
	Player(float x, float y, sf::Texture ptexture) : GameObject(x, y, 60, 170, ptexture) {};
	void jump() {
		if (isGrounded) {
			pos->y -= 10;
			speed->y = -28;
		}
		else {
			speed->y -= 0.2;
		}
	};
	void fall() {
		if (!isGrounded) {
			speed->y = 25;
		}
	}
};

#endif