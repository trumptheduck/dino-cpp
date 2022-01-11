#ifndef __Obstacle_H_INCLUDED__		// if Node.h hasn't been included yet...
#define __Obstacle_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "Classes/GameObject/GameObject.h"
#include "Classes/SFMLWindow/SFMLWindow.h"


class Obstacle : public GameObject
{
public:
	//Tốc độ di chuyển của vật thể
	float gameSpeed = 0;
	// Ghi đè lên hàm update vật thể
	void update()
	{
		//Khiến cho vật thể di chuyển mỗi lần update
		pos->x -= speed->x + gameSpeed;
	}
	Obstacle(float x, float y, sf::Texture ptexture) :
		GameObject(x, y, 100, 100, ptexture)
	{
		pos->x = x;
		pos->y = y;
	}
	Obstacle(float x, float y, float width, float height, sf::Texture ptexture) :
		GameObject(x, y, width, height, ptexture)
	{
		pos->x = x;
		pos->y = y;
		dim->x = width;
		dim->y = height;
	}
	Obstacle(Obstacle* obstacle) :
		GameObject(obstacle->pos->x, obstacle->pos->y, obstacle->dim->x, obstacle->dim->y, obstacle->texture) {
		speed->y = obstacle->speed->y;
		speed->x = obstacle->speed->x;
		gameSpeed = obstacle->gameSpeed;
		isGrounded = obstacle->isGrounded;
	};
	void setSpeed(float speed) {
		gameSpeed = speed;
	}
};
#endif