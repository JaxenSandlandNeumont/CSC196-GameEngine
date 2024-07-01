#include "Renderer.h"
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

	Vector2 v1{ 400, 500 };
	Vector2 v2{ 700, 500 };

	std::vector<Vector2> points;
		for (int i = 0; i < 100; i++)
		{
			points.push_back(Vector2{ rand() % 800, rand() % 600 });
		}

	while (true)
	{
		
		//input
		//update
		//draw

		//update
		Vector2 speed(0.1f, -0.1f);
		for (Vector2& point : points )
		{
			point = point + 0.002f;
		}

		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();

		renderer.DrawLine(400, 100, 100, 500);
		renderer.DrawLine(100, 500, 700, 500);
		renderer.DrawLine(700, 500, 400, 100);
		renderer.DrawLine(v1.x, v1.y, v2.x, v2.y);

		for (int i = 0; i < points.size() - 1; i++)
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