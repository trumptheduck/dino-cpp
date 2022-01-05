#ifndef __InputController_H_INCLUDED__ // if Node.h hasn't been included yet...
#define __InputController_H_INCLUDED__ //   #define this so the compiler knows it has been included

class InputController
{
public:
	std::function<void()> jump;
	std::function<void()> duck;
	void update()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			jump();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			duck();
		}
	}
};
#endif