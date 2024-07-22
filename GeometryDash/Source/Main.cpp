#include "Engine.h"
#include "ModelData.h"
#include "Player.h"
#include "Scene.h"
#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <SDL_ttf.h>

int main(int argc, char* argv[])
{




	bool levelManagerMode = false;
	if (levelManagerMode)
	{
		Game* game = new Game{};
		std::vector<std::vector<Vector2>>* allPoints = game->DrawMode();

		return 0;
	}


	Game* game = new Game{};
	game->RunGame(0);

	

	return 0;

}