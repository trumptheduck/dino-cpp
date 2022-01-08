#ifndef __Game_H_INCLUDED__		// if Node.h hasn't been included yet...
#define __Game_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "Classes/Clock/Clock.h"
#include "Classes/GameObject/GameObject.h"
#include "Classes/InputController/InputController.h"
#include "Classes/LogicController/LogicController.h"
#include "Classes/Menu/Menu.h"
#include "Classes/Obstacle/Obstacle.h"
#include "Classes/SFMLWindow/SFMLWindow.h"
#include "Classes/Vector2/Vector2.h"
#include <string.h>


class Game
{

public:
	// Chiều rộng và chiều cao của cửa sổ;
	float const width = 1024;
	float const height = 768;
	// Đồng hồ lặp để chạy hàm clock.tick() một số lần nhất định trong 1s, ở đây là 120 lần/s
	Clock* clock = new Clock(60);
	// Khởi tạo cửa sổ qua class SFMLWindow
	SFMLWindow* window = new SFMLWindow(new Vector2(width, height), "Title");
	// Khởi tạo class nhận tín hiệu điều khiển của người chơi
	InputController* controller = new InputController();
	// GameObject* player = new GameObject();
	// Mảng chứa các vật cản
	std::vector<Obstacle*> obstacles;
	// Mảng chứa những GameObject cần xóa, đẩy GameObject vào đây để xóa nó
	std::vector<GameObject*> removeArray;
	Menu* menu = new Menu();

	Game()
	{
		//Khởi tạo hàm điều khiển người chơi
		controller->jump = [&] {
			menu->openWindow(0);
		};
		menu->openWindow(0);
		// controller->duck = [&] {
		// 	player->pos->y -= 2;
		// };

		//Thiết lập hàm tick bằng một hàm lambda
		clock->tick = [&] {
			if (menu->window->window.isOpen())
			{
				menu->tick();
			}
			else
			{
				std::cout << "aaa" << std::endl;
				window->window.setActive(true);
				removeUnusedObjects();
				window->poolEvents();
				update();
				draw();
				int minN = 0;
				int maxN = 10000;
				int r = minN + rand() % (maxN + 1 - minN);
				if (r < 100)
				{
					addObstacle(new Obstacle(300, 100, 50, 50, "content/sfml.png"));
				}
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
	void update()
	{
		//Kiểm tra bàn phím người chơi và update điều khiển
		controller->update();

		//Update người chơi
		//Hàm implementGravity sẽ tạo trọng lực cho người chơi, người chơi sẽ rơi xuống cho tới khi
		// chạm tới tọa độ mặt đất ở tham số thứ 2, ở đây là 600;

		// LogicController::implementGravity(player, 600);

		//Chạy hàm update cho người chơi
		// player->update();

		//Vòng lặp for tất cả GameObject ở trong mảng Vật cản obstacles
		for (auto& gameObject : obstacles)
		{
			//Update vật cản
			gameObject->update();
			//Kiểm tra xem vật cản đã vượt quá cửa sổ hay chưa
			if (checkIfObjectOutOfBound(gameObject))
			{

				//Nếu đã vượt quá cửa sổ, ta không cần vật cản đó nữa, nên xóa nó đi
				flagObjectForRemoval(gameObject);
			}
		}
		//Xóa những GameObject đã được thêm vào mảng xóa
	}
	void draw()
	{
		window->clear();
		// Vẽ hitbox của người chơi
		// player->drawHitbox(window);
		for (auto& gameObject : obstacles)
		{
			//Gọi hàm vẽ của vật cản
			gameObject->draw(window);
		}

		window->display();
	}
	//Thêm vật cản vào mảng vật cản
	void addObstacle(Obstacle* obstacle)
	{
		obstacles.push_back(obstacle);
	}
	//Thêm vật cản vào mảng xóa
	void flagObjectForRemoval(GameObject* object)
	{
		removeArray.push_back(object);
	}
	//Xóa những vật cản ở trong mảng xóa
	void removeUnusedObjects()
	{
		for (auto& objectToRemove : removeArray)
		{
			int index = 0;
			for (auto& object : obstacles)
			{
				index++;
				if (objectToRemove == object)
				{
					delete object;
					obstacles.erase(std::remove(obstacles.begin(), obstacles.end(), object), obstacles.end());
				}
			}
		}
		removeArray.clear();
	}
	//Kiểm tra nếu GameObject ở ngoài khoảng vẽ, tức là 2 lần kích cỡ màn hình, nếu ở ngoài trả về true và ngược lại
	bool checkIfObjectOutOfBound(GameObject* object)
	{
		return (object->pos->x < -width || object->pos->x > 2 * width || object->pos->y < -height || object->pos->y > 2 * width);
	}
};

#endif