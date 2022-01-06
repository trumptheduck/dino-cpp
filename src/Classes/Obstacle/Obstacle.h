#include "Classes/GameObject/GameObject.h"
#include "Classes/SFMLWindow/SFMLWindow.h"

#ifndef __Obstacle_H_INCLUDED__		// if Node.h hasn't been included yet...
	#define __Obstacle_H_INCLUDED__ //   #define this so the compiler knows it has been included

class Obstacle : public GameObject
{
public:
	//Tốc độ di chuyển của vật thể
	float speedX = 1;
	// Ghi đè lên hàm update vật thể
	void update()
	{
		//Khiến cho vật thể di chuyển mỗi lần update
		pos->x -= speedX;
	}
	Obstacle(float x, float y) :
		GameObject(x, y, 100, 100)
	{
		pos->x = x;
		pos->y = y;
	}
	Obstacle(float x, float y, float width, float height) :
		GameObject(x, y, width, height)
	{
		pos->x = x;
		pos->y = y;
		dim->x = width;
		dim->y = height;
	}
};
#endif