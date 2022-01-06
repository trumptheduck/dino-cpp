#ifndef __InputController_H_INCLUDED__ // if Node.h hasn't been included yet...
#define __InputController_H_INCLUDED__ //   #define this so the compiler knows it has been included
//Class điều khiển người chơi
class InputController
{
public:
	//Con trỏ của hai hàm thiết lập
	std::function<void()> jump;
	std::function<void()> duck;
	void update()
	{
		//Kiểm tra nếu người chơi ấn nút cách
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			jump();
		}
		//Kiểm tra nếu người chơi ấn shift
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			duck();
		}
	}
};
#endif