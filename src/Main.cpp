#include "Classes/Game/Game.h"
#include "Classes/Obstacle/Obstacle.h"

class Program {
public:
	float const width = 1024;
	float const height = 768;
	SFMLWindow* window = new SFMLWindow(new Vector2(width, height), "Title");
	std::vector<MenuScreen*> menuArray = {
		new MenuScreen("Main Menu", window->window.getSize().x,  window->window.getSize().y, "content/background1.jpg",
			MenuItem::generateItemList({
				new MenuItem("New Game", [&] {
					menu->close();
				}),
				new MenuItem("Options", [&] {
					menu->close();
					menu->openMenu(1);
				}),
				new MenuItem("Quit game", [&] {
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
		new MenuScreen("Game Paused", window->window.getSize().x,  window->window.getSize().y, "content/background1.jpg",
			MenuItem::generateItemList({
				new MenuItem("Continue", [&] {
					menu->close();
				}),
				new MenuItem("Options", [&] {
					menu->close();
					menu->openMenu(1);
				}),
				new MenuItem("Return to Title", [&] {
					menu->close();
					menu->openMenu(0);
				}),
			}, 100, 150, 50)),

	};
	Game* game = new Game(width, height);
	Menu* menu = new Menu(menuArray);
	InputController* keyboard = new InputController();
	Clock* clock = new Clock(120);
	Program() {
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
				game->player->jump();
			}
		};
		keyboard->onShiftPressed = [&] {

		};
		keyboard->onEscPressed = [&] {
			if (!menu->isOpened) {
				menu->openMenu(2);
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
};

int main()
{

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	Program* program = new Program();
	program->start();
	return 0;
}
