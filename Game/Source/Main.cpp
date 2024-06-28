#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	// create window
	// returns pointer to window if successful or nullptr if failed
	SDL_Window* window = SDL_CreateWindow("Game Engine",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cerr << "Error creating SDL window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	// create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	while (false)
	{
		// clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		// draw line
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderDrawLine(renderer, 400, 100, 100, 500);
		SDL_RenderDrawLine(renderer, 100, 500, 700, 500);
		SDL_RenderDrawLine(renderer, 700, 500, 400, 100);

		// show screen
		SDL_RenderPresent(renderer);
	}

	const int MAXWIDTH = 800;
	while (true)
	{
		int value = rand() % 1000; // generate a number between 0-999
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		SDL_RenderClear(renderer);
		
		for (int i = 0; i < value; i++)
		{
			SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 0); // create random color
			SDL_RenderDrawLine(renderer, rand() % MAXWIDTH, rand() % MAXWIDTH, rand() % MAXWIDTH, rand() % MAXWIDTH);
		}
		SDL_RenderPresent(renderer);
		
	}

	return 0;
}