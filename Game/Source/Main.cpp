#include "Renderer.h"
#include "Input.h"
#include "Vector2.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"

#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	

	Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("Window", 800, 600);

	Input input;
	input.Initialize();

	Time time;


	Vector2 v1{ 400, 500 };
	Vector2 v2{ 700, 500 };

	std::vector<Vector2> points;

	std::vector<Particle> particles;
	//for (int i = 0; i < 0; i++)
	//{
	//	uint8_t color[4]{ rand() % 255, rand() % 255, rand() % 255, rand() % 255 };
	//	particles.push_back(Particle({ rand() % 800, rand() % 800 }, { randomf(100, 300), 0.0f }, 1, color));
	//}


	bool quit = false;
	while (!quit)
	{
		time.Tick();


		//INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		if (!input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0))
		{
			std::array<uint8_t, 4> color{ {random(255), random(255), random(255), 0}};
			for (int i = 0; i < 1000; i++)
			{
				particles.push_back(Particle(mousePosition, { randomf(-300, 300), randomf(-300, 300) }, randomf(0.4, 1), color));
			}
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}

		//DRAW
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();


		for (Particle particle : particles)
		{
			if (particle.lifespan > 0)
			{
				renderer.SetColor(particle.color[0], particle.color[1], particle.color[2], particle.color[3]);
				particle.Draw(renderer);
			}
		}

		renderer.EndFrame();
	}

	const int MAXWIDTH = 800;
	while (false)
	{
		//int value = rand() % 1000; // generate a number between 0-999
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
		//SDL_RenderClear(renderer);
		//
		//for (int i = 0; i < value; i++)
		//{
		//	SDL_SetRenderDrawColor(renderer, rand() % 256, rand() % 256, rand() % 256, 0); // create random color
		//	SDL_RenderDrawLine(renderer, rand() % MAXWIDTH, rand() % MAXWIDTH, rand() % MAXWIDTH, rand() % MAXWIDTH);
		//}
		//SDL_RenderPresent(renderer);
		
	}

	return 0;

}