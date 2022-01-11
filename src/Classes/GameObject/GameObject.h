#ifndef __GameObject_H_INCLUDED__	  // if Node.h hasn't been included yet...
#define __GameObject_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "Classes/SFMLWindow/SFMLWindow.h"
#include "Classes/Utils/Utils.h"
#include "Classes/Vector2/Vector2.h"

class GameObject
{
private:
	int generateUniqueId()
	{
		int minN = 10000000;
		int maxN = 99999999;
		return minN + rand() % (maxN + 1 - minN);
	}

public:
	// ID của vật thể trong game, dùng để nhận diện
	int uuid = generateUniqueId();
	// Vị trí vật thể
	Vector2* pos;
	// Kích cỡ vật thể
	Vector2* dim;
	// Gia tốc rơi của vật thể
	Vector2* speed = new Vector2(0, 0);
	// Vật thể có ở trên mặt đất hay không
	bool isGrounded = false;

	sf::Sprite sprite;
	sf::Texture texture;

	GameObject(float x, float y, float width, float height, sf::Texture ptexture)
	{
		pos = new Vector2(x, y);
		dim = new Vector2(width, height);
		texture = ptexture;
		sprite.setTexture(texture);
		float scaleX = dim->x / texture.getSize().x;
		float scaleY = dim->y / texture.getSize().y;
		sprite.setScale(sf::Vector2f(scaleX, scaleY));
	}
	//Hàm update
	void update()
	{
	}
	//Hàm vẽ hitbox
	void drawHitbox(SFMLWindow* window)
	{
		window->drawBox(pos->x, pos->y, dim->x, dim->y);
	}
	//Hàm vẽ chính
	void draw(SFMLWindow* window)
	{
		window->drawSprite(this->sprite, pos->x, pos->y);
	}
};
#endif