#ifndef __InputController_H_INCLUDED__ // if Node.h hasn't been included yet...
#define __InputController_H_INCLUDED__ //   #define this so the compiler knows it has been included
//Class điều khiển người chơi
class InputController
{
public:
	std::function<void()> onSpacePressed;
	std::function<void()> onShiftPressed;
	std::function<void()> onUpPressed;
	std::function<void()> onDownPressed;
	std::function<void()> onEnterPressed;
	std::function<void()> onEscPressed;
	void update()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			onSpacePressed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			onShiftPressed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			onUpPressed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			onDownPressed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			onEnterPressed();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			onEscPressed();
		}
	}
};
#endif