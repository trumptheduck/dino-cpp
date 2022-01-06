#include "Classes/Vector2/Vector2.h"
#include "Platform/Platform.hpp"

#ifndef __SFMLWindow_H_INCLUDED__	  // if Node.h hasn't been included yet...
	#define __SFMLWindow_H_INCLUDED__ //   #define this so the compiler knows it has been included

class SFMLWindow
{
public:
	sf::RenderWindow window;
	sf::Event event;

	SFMLWindow(Vector2* dim, std::string title)
	{
		util::Platform platform;
		float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
		window.create(sf::VideoMode(dim->x * screenScalingFactor, dim->y * screenScalingFactor), title);
		platform.setIcon(window.getSystemHandle());
		// while (window.isOpen())
		// {
		// 	while (window.pollEvent(event))
		// 	{
		// 		if (event.type == sf::Event::Closed)
		// 			window.close();
		// 	}
		// }
	}
	void poolEvents()
	{
		if (window.isOpen())
		{
			if (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					exit(0);
				}
			}
		}
	}
	void clear()
	{
		window.clear();
	}
	void display()
	{
		window.display();
	}
	void drawRect(float x, float y, float width, float height)
	{
		sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(width, height));
		shape->setPosition(x, y);
		shape->setFillColor(sf::Color::White);
		draw(*shape);
		//Free up space
		delete shape;
	}
	void drawBox(float x, float y, float width, float height)
	{
		sf::RectangleShape* shape = new sf::RectangleShape(sf::Vector2f(width, height));
		shape->setPosition(x, y);
		shape->setFillColor(sf::Color::Transparent);
		shape->setOutlineThickness(3);
		shape->setOutlineColor(sf::Color::Red);
		draw(*shape);
		//Free up space
		delete shape;
	}
	void drawSprite(sf::Sprite sprite, float x, float y)
	{
		sf::Sprite* mSprite = new sf::Sprite(sprite);
		mSprite->setPosition(x, y);
		draw(*mSprite);
		delete mSprite;
	}
	void draw(sf::Drawable& shape)
	{
		window.draw(shape);
	}
};

#endif