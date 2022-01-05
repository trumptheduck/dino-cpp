#include "Classes/Game/Game.h"
#include "Classes/SFMLWindow/SFMLWindow.h"

int main()
{

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	Game* game = new Game();
	game->start();
	return 0;
}
