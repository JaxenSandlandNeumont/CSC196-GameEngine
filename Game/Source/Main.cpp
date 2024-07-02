#include "Renderer.h"
#include "Input.h"
#include "Vector2.h"

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

	Vector2 v1{ 400, 500 };
	Vector2 v2{ 700, 500 };

	std::vector<Vector2> points;
	//for (int i = 0; i < 100; i++)
	//{
	//	points.push_back(Vector2{ rand() % 800, rand() % 600 });
	//}
	bool quit = false;
	while (!quit)
	{
		
		//input
		//update
		//draw

		//INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		if (input.GetMouseButtonDown(0) && !input.GetPreviousMouseButtonDown(0))
		{
			points.push_back(mousePosition);
		}

		if (input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0))
		{
			float distance = (points.back() - mousePosition).Length();
			if (distance > 10)
			{
				points.push_back(mousePosition);
			}
		}

		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		renderer.SetColor(500, 0, 500, 0);
		for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
		{

			renderer.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
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

	
//	+ create a std::vector of Vector2 outside the main loop, these are the points
//main loop (while):
//  // input
//  + check if mouse button is down and previous mouse button is up (mouse pressed)
//    + add (push_back) mouse position onto points vector
//  // render
//  // use for loop to render lines (point[i] -> point[i + 1])
//  + for (int i = 0; points.size() > 1 && i < points.size() - 1; i++)
//    + set color (have fun and set random color :))
//    + renderer draw line (points[i].x, points[i].y, points[i + 1].x, points[i + 1].y)

}