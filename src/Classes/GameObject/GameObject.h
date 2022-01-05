#include "Classes/Utils/Utils.h"
#include "Classes/Vector2/Vector2.h"

#ifndef __GameObject_H_INCLUDED__	  // if Node.h hasn't been included yet...
	#define __GameObject_H_INCLUDED__ //   #define this so the compiler knows it has been included

class GameObject
{
public:
	std::string uuid = Utils::generateUUID(16);
	Vector2* pos = new Vector2();
	Vector2* dim = new Vector2(300, 300);
	int frame = 0;
	int maxFrame = 5;
	float spriteWidth = 528 / 6;
	float spriteHeight = 94;
	sf::Texture texture;
	sf::Sprite sprite;
	GameObject()
	{
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(frame * spriteWidth, 0, spriteWidth, spriteHeight));
		float scaleX = dim->x / texture.getSize().x;
		std::cout << texture.getSize().x;
		float scaleY = dim->y / texture.getSize().y / 6;
		sprite.setScale(scaleX, scaleY);
	}
	void getSprite()
	{
	}
	void update()
	{
	}
};
#endif