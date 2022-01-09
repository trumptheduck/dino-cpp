#include "Classes/GameObject/GameObject.h"
#include "Classes/SFMLWindow/SFMLWindow.h"

#ifndef __Obstacle_H_INCLUDED__		// if Node.h hasn't been included yet...
#define __Obstacle_H_INCLUDED__ //   #define this so the compiler knows it has been included

class Obstacle : public GameObject
{
public:
	//Tốc độ di chuyển của vật thể
	float speedX = 20;
	float gameSpeed = 0;
	float money = 0;
	bool isInstaKill = false;
	bool increaseWarning = false;
	// Ghi đè lên hàm update vật thể
	void update()
	{
		//Khiến cho vật thể di chuyển mỗi lần update
		pos->x -= speedX + gameSpeed;
	}
	Obstacle(float x, float y, std::string src) :
		GameObject(x, y, 100, 100, src)
	{
		pos->x = x;
		pos->y = y;
	}
	Obstacle(float x, float y, float width, float height, std::string src) :
		GameObject(x, y, width, height, src)
	{
		pos->x = x;
		pos->y = y;
		dim->x = width;
		dim->y = height;
	}
	Obstacle(Obstacle* obstacle) :
		GameObject(obstacle->pos->x, obstacle->pos->y, obstacle->dim->x, obstacle->dim->y, obstacle->imageSource) {
		accelerationY = obstacle->accelerationY;
		gameSpeed = obstacle->gameSpeed;
		increaseWarning = obstacle->increaseWarning;
		isGrounded = obstacle->isGrounded;
		isInstaKill = obstacle->isInstaKill;
		money = obstacle->money;
		speedX = obstacle->speedX;
	};
	void setSpeed(float speed) {
		gameSpeed = speed;
	}
};
// class Trex : public Obstacle
// {
// public:
// 	float speedX = 0.5;
// 	Trex(float xx, float yy) :
// 		Obstacle(xx, yy, 100, 100, "content/slider2.jpg");
// };
#endif