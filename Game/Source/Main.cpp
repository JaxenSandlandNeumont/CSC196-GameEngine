#include "Renderer.h"
#include "Input.h"
#include "Vector2.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtils.h"

#include <fmod.hpp>
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

	// create audio system
	FMOD::System* audio;
	FMOD::System_Create(&audio);
	void* extradriverdata = nullptr;
	audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
	std::vector<FMOD::Sound*> sounds;
	FMOD::Sound* sound = nullptr;

	audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("cowbell.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
	sounds.push_back(sound);

	Vector2 v1{ 400, 500 };
	Vector2 v2{ 700, 500 };

	std::vector<Vector2> points;

	std::vector<Particle> particles;
	float offset = 0.0f;
	//for (int i = 0; i < 0; i++)
	//{
	//	uint8_t color[4]{ rand() % 255, rand() % 255, rand() % 255, rand() % 255 };
	//	particles.push_back(Particle({ rand() % 800, rand() % 800 }, { randomf(100, 300), 0.0f }, 1, color));
	//}


	audio->playSound(sounds[0], 0, false, nullptr);


	bool quit = false;
	while (!quit)
	{
		time.Tick();
		audio->update();

		//INPUT
		input.Update();

		if (input.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		// Q = bass
		// W = snare
		// E = hi-hat
		if (input.GetKeyDown(SDL_SCANCODE_Q) && !input.GetPrevKeyDown(SDL_SCANCODE_Q))
		{
			audio->playSound(sounds[0], 0, false, nullptr); //Play bass
		}
		if (input.GetKeyDown(SDL_SCANCODE_W) && !input.GetPrevKeyDown(SDL_SCANCODE_W))
		{
			audio->playSound(sounds[5], 0, false, nullptr); //Play snare
		}
		if (input.GetKeyDown(SDL_SCANCODE_E) && !input.GetPrevKeyDown(SDL_SCANCODE_E))
		{
			audio->playSound(sounds[2], 0, false, nullptr); //Play hi-hat/open-hat
		}


		//UPDATE
		Vector2 mousePosition = input.GetMousePosition();
		if (!input.GetMouseButtonDown(0) && input.GetPreviousMouseButtonDown(0))
		{
			std::array<uint8_t, 4> color{ {random(255), random(255), random(255), 0}};
			for (int i = 0; i < 1000; i++)
			{
				particles.push_back(Particle(mousePosition, randomOnUnitCircle() * randomf(10, 300), randomf(0.4, 1), color));
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


		renderer.SetColor(255, 255, 255, 0);
		{
			int steps = 20;
			float radius = 60;
			offset += (90 * time.GetDeltaTime());
			for (float angle = 0; angle < 360; angle += 360 / steps)
			{
				float x = Math::Cos(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * radius;
				float y = Math::Sin(Math::DegToRad(angle + offset)) * Math::Sin((offset + angle) * 0.1f) * radius;

				renderer.DrawRect(400 + x, 300 + y, 2.0f, 2.0f);
			}
		}


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