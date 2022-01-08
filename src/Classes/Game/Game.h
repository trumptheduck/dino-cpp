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
#include "Classes/Player/Player.h"
#include "Classes/Emitter/Emitter.h"
#include <string.h>


class Game
{

public:
	float mWidth = 0;
	float mHeight = 0;
	float groundLevel = 600;
	std::vector<Obstacle*> obstacles;
	std::vector<GameObject*> removeArray;
	Player* player = new Player(100, 100);
	Emitter* emitter;

	Game(float width, float height)
	{
		emitter = new Emitter(0.01, 60);
		emitter->emit = [&] {
			addObstacle(new Obstacle(300, 100, 50, 50, "content/sfml.png"));
		};
		mWidth = width;
		mHeight = height;
	};
	void tick(SFMLWindow* window) {
		removeUnusedObjects();
		update();
		draw(window);
	}
	void update()
	{
		//Kiểm tra bàn phím người chơi và update điều khiển

		//Update người chơi
		//Hàm implementGravity sẽ tạo trọng lực cho người chơi, người chơi sẽ rơi xuống cho tới khi
		// chạm tới tọa độ mặt đất ở tham số thứ 2, ở đây là 600;
		emitter->tick();
		LogicController::implementGravity(player, groundLevel);

		//Chạy hàm update cho người chơi
		player->update();

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
	void draw(SFMLWindow* window)
	{
		window->clear();
		// Vẽ hitbox của người chơi
		player->drawHitbox(window);
		player->draw(window);
		for (auto& gameObject : obstacles)
		{
			//Gọi hàm vẽ của vật cản
			gameObject->drawHitbox(window);
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
		return (object->pos->x < -mWidth || object->pos->x > 2 * mWidth || object->pos->y < -mHeight || object->pos->y > 2 * mHeight);
	}
};

#endif