#include "Game.h"
#include <vector>

int main(int argc, char* argv[])
{

	bool levelManagerMode = false;
	if (levelManagerMode)
	{
		Game* game = new Game{};
		std::vector<std::vector<Vector2>> allPoints = game->DrawMode();

		return 0;
	}

 
	Game* game = new Game{};
	game->Start(Game::eState::Title);

	

	return 0;

}