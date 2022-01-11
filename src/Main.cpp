#include "Classes/Game/Game.h"
#include "Classes/Obstacle/Obstacle.h"
#include <map>

class Program {
public:
	float const width = 1400;
	float const height = 768;
	SFMLWindow* window = new SFMLWindow(new Vector2(width, height), "Bach Khoa Survival");
	std::vector<MenuScreen*> menuArray = {
		new MenuScreen("You got admitted to HUST! What are you gonna do?", window->window.getSize().x,  window->window.getSize().y, "content/background1.jpg",
			MenuItem::generateItemList({
				new MenuItem("Attend university", [&] {
					newGame();
					menu->close();
				}),
				new MenuItem("Get ready", [&] {
					menu->close();
					menu->openMenu(1);
				}),
				new MenuItem("Stay home", [&] {
					exit(0);
				}),
			}, 100, 150, 50)),
		new MenuScreen("Options", window->window.getSize().x,  window->window.getSize().y, "content/background1.jpg",
			MenuItem::generateItemList({
				new MenuItem("Sounds", [&] {
					std::cout << "Sound pressed" << std::endl;
				}),
				new MenuItem("Graphics", [&] {
					std::cout << "Graphics pressed" << std::endl;
				}),
				new MenuItem("Return to Title", [&] {
					menu->close();
					menu->openMenu(0);
				}),
			}, 100, 150, 50)),
		new MenuScreen("Education reserved", window->window.getSize().x,  window->window.getSize().y, "content/background1.jpg",
			MenuItem::generateItemList({
				new MenuItem("Go back to study", [&] {
					menu->close();
				}),
				new MenuItem("Get ready", [&] {
					menu->close();
					menu->openMenu(1);
				}),
				new MenuItem("Retake test", [&] {
					menu->close();
					menu->openMenu(0);
				}),
			}, 100, 150, 50)),

	};
	Game* game;
	Menu* menu = new Menu(menuArray);
	InputController* keyboard = new InputController();
	Clock* clock = new Clock(120);
	Program() {
		newGame();
		keyboard->onUpPressed = [&] {
			if (menu->isOpened) {
				menu->moveIndex(-1);
			}
		};
		keyboard->onDownPressed = [&] {
			if (menu->isOpened) {
				menu->moveIndex(1);
			}
		};
		keyboard->onEnterPressed = [&] {
			if (menu->isOpened) {
				menu->confirm();
			}
		};
		keyboard->onSpacePressed = [&] {
			if (menu->isOpened) {}
			else {
				if (!game->isOver)
					if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) game->player->jump();
			}
		};
		keyboard->onShiftPressed = [&] {
			if (menu->isOpened) {}
			else {
				if (!game->isOver)
					game->player->fall();
			}
		};
		keyboard->onEscPressed = [&] {
			if (!menu->isOpened) {
				if (game->isOver) {
					menu->openMenu(0);
				}
				else {
					menu->openMenu(2);
				}
			}
		};
		menu->openMenu(0);
		clock->tick = [&] {
			window->poolEvents();
			keyboard->update();
			if (menu->isOpened) {
				menu->tick(window);
			}
			else {
				game->tick(window);
			}

		};
	};
	//Bắt đầu trò chơi
	void start()
	{
		clock->start();
	}
	//Tạm dừng trò chơi
	void pause()
	{
		clock->pause();
	}
	//Tiếp tục
	void unpause()
	{
		clock->unpause();
	}
	void newGame() {
		game = new Game(width, height);
	}
};

int main()
{

	// #if defined(_DEBUG)
	// 	std::cout << "Hello World!" << std::endl;
	// #endif

	Program* program = new Program();
	program->start();
	return 0;
}
