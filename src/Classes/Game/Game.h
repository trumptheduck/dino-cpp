#include "Classes/Clock/Clock.h"
#include "Classes/GameObject/GameObject.h"
#include "Classes/InputController/InputController.h"
#include "Classes/SFMLWindow/SFMLWindow.h"
#include "Classes/Vector2/Vector2.h"

#ifndef __Game_H_INCLUDED__		// if Node.h hasn't been included yet...
	#define __Game_H_INCLUDED__ //   #define this so the compiler knows it has been included

class Game
{

public:
	float width = 900;
	float height = 600;
	Clock* clock = new Clock(120);
	Vector2* dim = new Vector2(width, height);
	Vector2* pos = new Vector2(0, 0);
	SFMLWindow* window = new SFMLWindow(dim, "Title");
	InputController* controller = new InputController();
	GameObject* player = new GameObject();

	Game()
	{
		controller->jump = [&] {
			pos->y += 2;
		};
		controller->duck = [&] {
			pos->y -= 2;
		};
		clock->tick = [&] {
			window->poolEvents();
			controller->update();
			window->clear();
			window->drawRect(pos->x, pos->y, 300, 300);
			window->drawSprite(player->sprite, pos->x, pos->y);
			window->display();
		};
		clock->start();
	};
	void start()
	{
		clock->start();
	}
};

#endif