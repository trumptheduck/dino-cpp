#include "Classes/Game/Game.h"
#include "Classes/Obstacle/Obstacle.h"
int main()
{

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif
	// Khởi tạo trò chơi
	Game* game = new Game();
	// Thêm vật cản
	// Bắt đầu trò chơi
	game->start();
	return 0;
}
