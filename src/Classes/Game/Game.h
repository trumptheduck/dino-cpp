#ifndef __Game_H_INCLUDED__		// if Node.h hasn't been included yet...
#define __Game_H_INCLUDED__ //   #define this so the compiler knows it has been included

#include "Classes/Clock/Clock.h"
#include "Classes/GameObject/GameObject.h"
#include "Classes/InputController/InputController.h"
#include "Classes/LogicController/LogicController.h"
#include "Classes/Menu/Menu.h"
#include "Classes/Obstacle/Obstacle.h"
#include "Classes/Obstacle/Obstacles.h"
#include "Classes/SFMLWindow/SFMLWindow.h"
#include "Classes/Vector2/Vector2.h"
#include "Classes/Player/Player.h"
#include "Classes/Emitter/Emitter.h"
#include <math.h>
#include <fstream>


class Loader {
public:
	std::map<std::string, sf::Texture> textures;
	std::vector<std::string> sources;
	Loader(std::vector<std::string> imageSources) {
		sources = imageSources;
	}
	void load() {
		for (auto& source : sources) {
			sf::Texture texture;
			texture.loadFromFile(source);
			textures.insert(std::pair<std::string, sf::Texture>(source, texture));
		}
	}
};

class Game
{

public:
	static std::vector<int> getAllPoints() {
		std::vector<int> points;
		std::string line;

		std::ifstream input_file("content/get_score.txt");
		if (!input_file.is_open())
		{
			std::cout << "Could not open the file" << std::endl;
		}
		else
		{
			while (std::getline(input_file, line))
			{
				points.push_back(stoi(line));
			}
		}
		return points;
	}
	static void setPoint(int point) {
		std::vector<int> pointArray = getAllPoints();
		pointArray.push_back(point);
		std::sort(pointArray.begin(), pointArray.end(), std::greater<int>());
		int length = pointArray.size() < 10 ? pointArray.size() : 10;
		FILE* fp = NULL;
		fp = fopen("content/get_score.txt", "w");
		for (int i = 0; i < length; i++) {
			fprintf(fp, "%d\n", pointArray[i]);
		}
		fclose(fp);
	}
	static std::string getRank(int score) {
		float rankGap = 1000;
		if (score >= rankGap * 6) {
			return "S+";
		}
		if (score >= rankGap * 5) {
			return "S";
		}
		if (score >= rankGap * 4) {
			return "A";
		}
		if (score >= rankGap * 3) {
			return "B";
		}
		if (score >= rankGap * 2) {
			return "C";
		}
		if (score >= rankGap * 1) {
			return "D";
		}
		return "F";
	}
	//////////////////////////////////////////////////
	//Basic parameters
	float mWidth = 0;
	float mHeight = 0;
	//Game flags
	bool isOver = false;
	bool showHitbox = false;
	//Game parameters
	float difficulty = 1;
	float difficultyFactor = 0.0003;
	float gameSpeed = 5;
	float baseDistance = 20;
	float baseProbability = 0.005;
	float distanceFactor = 10;
	float probabilityFactor = 0.002;
	float scoreMultiplier = 1000;
	float groundLevel = 700;
	//Spawn position config
	Vector2* topSpawnPosition = new Vector2(1500, 300);
	Vector2* middleSpawnPosition = new Vector2(1500, 500);
	Vector2* bottomSpawnPosition = new Vector2(1500, 700);
	//Game data
	std::vector<Obstacle*> obstacles;
	std::vector<GameObject*> removeArray;
	std::vector<Obstacle*> regularObstacleCache;
	std::vector<Obstacle*> middleObstacleCache;
	Player* player;
	//Game dependencies
	Emitter* regularEmitter;
	Emitter* middleEmitter;
	std::vector<std::string> imageSources = {
	"content/cop.png",
	"content/algebra.jpg",
	"content/analysis.jpg",
	"content/physics.jpg",
	"content/philosophy.jpg",
	"content/girlfriend.png",
	"content/phonglon.png",
	"content/player.png",
	"content/road.png",
	"content/sami.png",
	};
	Loader* loader = new Loader(imageSources);
	//Game background
	GameObject* road1;
	GameObject* road2;
	sf::Texture backGroundTexture;
	sf::Sprite backGroundSprite;

	Game(float width, float height)
	{
		loader->load();
		player = new Player(100, 100, loader->textures["content/player.png"]);
		road1 = new GameObject(0, 0, 3000, 300, loader->textures["content/road.png"]);
		road2 = new GameObject(3000, 0, 3000, 300, loader->textures["content/road.png"]);
		backGroundTexture.loadFromFile("content/sky.png");
		backGroundSprite.setTexture(backGroundTexture);
		regularEmitter = new Emitter(baseProbability, baseDistance);
		middleEmitter = new Emitter(baseProbability / 3, baseDistance);
		//Thêm vật cản mẫu
		regularObstacleCache.push_back(new Cop(bottomSpawnPosition, loader->textures["content/cop.png"]));
		regularObstacleCache.push_back(new Girlfriend(bottomSpawnPosition, loader->textures["content/girlfriend.png"]));
		regularObstacleCache.push_back(new Analysis(bottomSpawnPosition, loader->textures["content/analysis.jpg"]));
		regularObstacleCache.push_back(new Analysis(topSpawnPosition, loader->textures["content/analysis.jpg"]));
		regularObstacleCache.push_back(new Algebra(bottomSpawnPosition, loader->textures["content/algebra.jpg"]));
		regularObstacleCache.push_back(new Algebra(topSpawnPosition, loader->textures["content/algebra.jpg"]));
		regularObstacleCache.push_back(new Physics(bottomSpawnPosition, loader->textures["content/physics.jpg"]));
		regularObstacleCache.push_back(new Physics(topSpawnPosition, loader->textures["content/physics.jpg"]));
		regularObstacleCache.push_back(new Philosophy(bottomSpawnPosition, loader->textures["content/philosophy.jpg"]));
		regularObstacleCache.push_back(new Philosophy(topSpawnPosition, loader->textures["content/philosophy.jpg"]));
		regularObstacleCache.push_back(new PigSpear(bottomSpawnPosition, loader->textures["content/phonglon.png"]));
		regularObstacleCache.push_back(new Sami(topSpawnPosition, loader->textures["content/sami.png"]));


		middleObstacleCache.push_back(new Analysis(middleSpawnPosition, loader->textures["content/analysis.jpg"]));
		middleObstacleCache.push_back(new Algebra(middleSpawnPosition, loader->textures["content/algebra.jpg"]));
		middleObstacleCache.push_back(new PigSpear(middleSpawnPosition, loader->textures["content/phonglon.png"]));
		middleObstacleCache.push_back(new Philosophy(middleSpawnPosition, loader->textures["content/philosophy.jpg"]));
		middleObstacleCache.push_back(new Sami(middleSpawnPosition, loader->textures["content/sami.png"]));

		//Thiết lập emit
		regularEmitter->emit = [&] {
			Obstacle* selectedObstacle = selectRandomObject(regularObstacleCache);
			addObstacle(new Obstacle(selectedObstacle));
		};
		middleEmitter->emit = [&] {
			Obstacle* selectedObstacle = selectRandomObject(middleObstacleCache);
			addObstacle(new Obstacle(selectedObstacle));
		};
		mWidth = width;
		mHeight = height;
	};
	Obstacle* selectRandomObject(std::vector<Obstacle*> array) {
		int minN = 0;
		int maxN = array.size() - 1;
		int r = minN + rand() % (maxN + 1 - minN);
		return array[r];
	}
	void lose() {
		setPoint(getPoint());
		isOver = true;
	}
	int getPoint() {
		return (int)round((difficulty - 1) * scoreMultiplier);
	}
	void tick(SFMLWindow* window) {
		//Xóa những GameObject đã được thêm vào mảng xóa
		removeUnusedObjects();
		if (!isOver) {
			update(window);
		}
		draw(window);
	}
	void update(SFMLWindow* window)
	{
		difficulty += difficultyFactor;
		regularEmitter->setParameters(
			baseProbability + probabilityFactor * difficulty,
			baseDistance + distanceFactor * difficulty);
		middleEmitter->setParameters(
			(baseProbability + probabilityFactor * difficulty) / 2,
			baseDistance + distanceFactor * difficulty);
		regularEmitter->tick();
		middleEmitter->tick();

		//Update người chơi
		//Hàm implementGravity sẽ tạo trọng lực cho người chơi, người chơi sẽ rơi xuống cho tới khi
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
				lose();
			}
			//Kiểm tra xem vật cản đã vượt quá cửa sổ hay chưa
			if (checkIfObjectOutOfBound(gameObject))
			{
				//Nếu đã vượt quá cửa sổ, ta không cần vật cản đó nữa, nên xóa nó đi
				flagObjectForRemoval(gameObject);
			}
		}
	}
	void draw(SFMLWindow* window)
	{
		window->clear();
		window->drawSprite(backGroundSprite, 0, 0);
		road1->draw(window);
		road2->draw(window);
		for (auto& gameObject : obstacles)
		{
			//Gọi hàm vẽ của vật cản
			if (showHitbox) gameObject->drawHitbox(window);
			gameObject->draw(window);
		}
		if (showHitbox) player->drawHitbox(window);
		player->draw(window);
		drawUI(window);
		window->display();
	}
	void drawUI(SFMLWindow* window) {
		window->drawText(20, 20, "Diem Ren Luyen: " + std::to_string(getPoint()), sf::Color::Red, 30);
		window->drawText(20, 70, "Hoc Bong: " + getRank(getPoint()), sf::Color::White, 30);
		if (isOver) {
			sf::RectangleShape overlay;
			overlay.setSize(sf::Vector2f(window->window.getSize().x, window->window.getSize().y));
			overlay.setFillColor(sf::Color(0, 0, 0, 128));
			window->window.draw(overlay);
			window->drawText(300, 250, "YOU CAN STUDY NOMORE!", sf::Color::Red, 60);
			window->drawText(300, 350, "Diem Ren Luyen: " + std::to_string(getPoint()), sf::Color::White, 30);
			window->drawText(300, 400, "Hoc Bong: " + getRank(getPoint()), sf::Color::White, 30);
			window->drawText(300, 450, "Press Esc to Retake Entrance Test", sf::Color::White, 30);
		}
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