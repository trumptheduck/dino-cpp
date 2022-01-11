#ifndef __LogicController_H_INCLUDED__	   // if Node.h hasn't been included yet...
#define __LogicController_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "Classes/GameObject/GameObject.h"

class LogicController
{
public:
	//Hàm kiểm tra va chạm giữa 2 vật thể game
	static bool checkForCollision(GameObject* obj1, GameObject* obj2)
	{
		float shrinkX = 1.2;
		float shrinkY = 1;
		float normalizedPos1X = obj1->pos->x + obj1->dim->x * (1 - 1 / shrinkX) / 2;
		float normalizedPos1Y = obj1->pos->y + obj1->dim->y * (1 - 1 / shrinkY) / 2;
		float normalizedDim1X = obj1->dim->x / shrinkX;
		float normalizedDim1Y = obj1->dim->y / shrinkY;
		float normalizedPos2X = obj2->pos->x + obj2->dim->x * (1 - 1 / shrinkX) / 2;
		float normalizedPos2Y = obj2->pos->y + obj2->dim->y * (1 - 1 / shrinkY) / 2;
		float normalizedDim2X = obj2->dim->x / shrinkX;
		float normalizedDim2Y = obj2->dim->y / shrinkY;

		return (normalizedPos1X < normalizedPos2X + normalizedDim2X &&
			normalizedPos1X + normalizedDim1X > normalizedPos2X &&
			normalizedPos1Y < normalizedPos2Y + normalizedDim2Y &&
			normalizedDim1Y + normalizedPos1Y > normalizedPos2Y);
	};
	//Hàm thực thi trọng lực
	static void implementGravity(GameObject* obj, int groundLevel)
	{
		if (obj->pos->y + obj->dim->y + obj->speed->y >= groundLevel)
		{
			obj->speed->y = 0;
			obj->pos->y = groundLevel - obj->dim->y;
			obj->isGrounded = true;
		}
		else
		{
			obj->isGrounded = false;
			obj->speed->y += 1;
			obj->pos->y += obj->speed->y;
		}
	}
};

#endif