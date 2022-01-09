#include "Classes/GameObject/GameObject.h"

#ifndef __LogicController_H_INCLUDED__	   // if Node.h hasn't been included yet...
#define __LogicController_H_INCLUDED__ //   #define this so the compiler knows it has been included

class LogicController
{
public:
	//Hàm kiểm tra va chạm giữa 2 vật thể game
	static bool checkForCollision(GameObject* obj1, GameObject* obj2)
	{
		return (obj1->pos->x < obj2->pos->x + obj2->dim->x && obj1->pos->x + obj2->dim->x > obj2->pos->x && obj1->pos->y < obj2->pos->y + obj2->dim->y && obj1->dim->y + obj1->pos->y > obj2->pos->y);
	};
	//Hàm thực thi trọng lực
	static void implementGravity(GameObject* obj, int groundLevel)
	{
		if (obj->pos->y + obj->dim->y + obj->accelerationY >= groundLevel)
		{
			obj->accelerationY = 0;
			obj->pos->y = groundLevel - obj->dim->y;
			obj->isGrounded = true;
		}
		else
		{
			obj->isGrounded = false;
			obj->accelerationY += 1;
			obj->pos->y += obj->accelerationY;
		}
	}
};

#endif