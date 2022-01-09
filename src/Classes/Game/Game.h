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
	float groundLevel = 700;

	float difficulty = 1;
	float gameSpeed = 10;
	float baseDistance = 20;
	float baseProbability = 0.005;
	float distanceFactor = 10;
	float probabilityFactor = 0.002;

	std::vector<Obstacle*> obstacles;
	std::vector<GameObject*> removeArray;
	std::vector<Obstacle*> obstacleArray;

	GameObject* road1 = new GameObject(0, 0, 3000, 300, "content/road.png");
	GameObject* road2 = new GameObject(3000, 0, 3000, 300, "content/road.png");
	Player* player = new Player(100, 100);
	Emitter* emitter;

	sf::Texture backGroundTexture;
	sf::Sprite backGroundSprite;

	Game(float width, float height)
	{
		backGroundTexture.loadFromFile("content/sky.png");
		backGroundSprite.setTexture(backGroundTexture);
		emitter = new Emitter(baseProbability, baseDistance);
		obstacleArray.push_back(new Obstacle(1500, 550, 170, 150, "content/cop.png"));
		obstacleArray.push_back(new Obstacle(1500, 400, 150, 150, "content/sfml.png"));
		obstacleArray.push_back(new Obstacle(1500, 300, 150, 150, "content/dino.png"));
		emitter->emit = [&] {
			Obstacle* selectedObstacle = selectRandomObject(obstacleArray);
			addObstacle(new Obstacle(selectedObstacle));
		};
		mWidth = width;
		mHeight = height;
	};
	Obstacle* selectRandomObject(std::vector<Obstacle*> array) {
		int minN = 0;
		int maxN = array.size() - 1;
		int r = minN + rand() % (maxN + 1 - minN);
		std::cout << r << "\n";
		return array[r];
	}
	void tick(SFMLWindow* window) {
		removeUnusedObjects();
		update(window);
		draw(window);
	}
	void update(SFMLWindow* window)
	{
		//Kiểm tra bàn phím người chơi và update điều khiển

		//Update người chơi
		//Hàm implementGravity sẽ tạo trọng lực cho người chơi, người chơi sẽ rơi xuống cho tới khi
		// chạm tới tọa độ mặt đất ở tham số thứ 2, ở đây là 600;
		difficulty += 0.0001;
		emitter->setParameters(
			baseProbability + probabilityFactor * difficulty,
			baseDistance + distanceFactor * difficulty);
		emitter->tick();
		LogicController::implementGravity(player, groundLevel);

		//Chạy hàm update cho người chơi
		player->update();
		road1->pos->x -= gameSpeed * difficulty;
		road2->pos->x -= gameSpeed * difficulty;
		if (road1->pos->x <= -road1->dim->x) {
			road1->pos->x += 2 * road1->dim->x;
		}
		if (road2->pos->x <= -road2->dim->x) {
			road2->pos->x += 2 * road2->dim->x;
		}
		road1->pos->y = window->window.getSize().y - road1->dim->y;
		road2->pos->y = window->window.getSize().y - road2->dim->y;
		//Vòng lặp for tất cả GameObject ở trong mảng Vật cản obstacles
		for (auto& gameObject : obstacles)
		{
			//Update vật cản
			gameObject->setSpeed(gameSpeed * difficulty + 10);
			gameObject->update();
			if (LogicController::checkForCollision(player, gameObject)) {
				std::cout << "Collided" << "\n";
			}
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
		window->drawSprite(backGroundSprite, 0, 0);
		road1->draw(window);
		road2->draw(window);
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