#include "Renderer.h"
#include "Input.h"
#include "Vector2.h"
#include "Particle.h"
#include "Random.h"
#include "ETime.h"
#include "MathUtils.h"
#include "Model.h"
#include "Transform.h"

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

	std::vector<Particle> particles;
	float offset = 0.0f;

	std::vector<Vector2> points;
	points.push_back(Vector2{ 5, 0 });
	points.push_back(Vector2{ -5, -5 });
	points.push_back(Vector2{ -5, 5 });
	points.push_back(Vector2{ 5, 0 });
	Color color{ 1, 1, 0 };
	Model model{ points, color };
	Transform transform{ { renderer.getWidth() >> 1 , renderer.getHeight() >> 1 }, 0, 5 };

	// >> 1 shifts binary over 1


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


		float thrust = 0;
		if (input.GetKeyDown(SDL_SCANCODE_LEFT))
		{
			transform.rotation -= Math::DegToRad(200) * time.GetDeltaTime();
		}
		if (input.GetKeyDown(SDL_SCANCODE_RIGHT))
		{
			transform.rotation += Math::DegToRad(200) * time.GetDeltaTime();
		}
		if (input.GetKeyDown(SDL_SCANCODE_UP))		thrust = 400;
		if (input.GetKeyDown(SDL_SCANCODE_DOWN))	thrust = -400;

		Vector2 velocity = Vector2{ thrust, 0.0f }.Rotate(transform.rotation);
		transform.position += velocity * time.GetDeltaTime();
		transform.position.x = Math::Wrap(transform.position.x, (float)renderer.getWidth());
		transform.position.y = Math::Wrap(transform.position.y, (float)renderer.getHeight());

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
			audio->playSound(sounds[2], 0, false, nullptr); //Play hi-hat/close-hat
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



		for (Particle particle : particles)
		{
			if (particle.lifespan > 0)
			{
				renderer.SetColor(particle.color[0], particle.color[1], particle.color[2], particle.color[3]);
				particle.Draw(renderer);
			}
		}


		model.Draw(renderer, transform);


		renderer.EndFrame();
	}

	return 0;

}