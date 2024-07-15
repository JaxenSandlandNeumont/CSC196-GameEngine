#include "Engine.h"
#include "ModelData.h"
#include "Player.h"
#include "Scene.h"

#include <iostream>
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
	g_engine.Initialize();

	Time time;

	// create audio system
	
	std::vector<FMOD::Sound*> sounds;
	FMOD::Sound* sound = nullptr;

	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("snare.wav");


	std::vector<Particle> particles;
	float offset = 0.0f;

	std::vector<Vector2> points;
	points.push_back(Vector2{ 5, 0 });
	points.push_back(Vector2{ -5, -5 });
	points.push_back(Vector2{ -5, 5 });
	points.push_back(Vector2{ 5, 0 });
	Color color{ 1, 1, 0 };

	const int modelNum = 2;

	std::vector<std::vector<Vector2>> modelPoints = ModelData::GetModel(modelNum);
	Model model{ modelPoints, color};
	//Transform transform{ { g_engine.GetRenderer().getWidth() >> 1 , g_engine.GetRenderer().getHeight() >> 1}, 0, 5};

	// >> 1 shifts binary over 1


	Scene* scene = new Scene();

	for (int i = 0; i < 10; i++)
	{
		Transform transform{ { randomf(0, 800) , randomf(0, 600)}, 0, randomf(1,5)};

		Player* player = new Player( 200.0f, transform, &model);
		player->SetDamping(2.0f);
		scene->AddActor(player);
	}

	bool quit = false;
	while (!quit)
	{
		time.Tick();
		g_engine.Update();

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		scene->Update(time.GetDeltaTime());


		//float thrust = 0;
		//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT))
		//{
		//	transform.rotation -= Math::DegToRad(200) * time.GetDeltaTime();
		//}

		//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT))
		//{
		//	transform.rotation += Math::DegToRad(200) * time.GetDeltaTime();
		//}

		//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP))		thrust = 400;
		//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN))	thrust = -400;

		//Vector2 velocity = Vector2{ thrust, 0.0f }.Rotate(transform.rotation);
		//transform.position += velocity * time.GetDeltaTime();
		//transform.position.x = Math::Wrap(transform.position.x, (float)g_engine.GetRenderer().getWidth());
		//transform.position.y = Math::Wrap(transform.position.y, (float)g_engine.GetRenderer().getHeight());

		// Q = bass
		// W = snare
		// E = hi-hat
		//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Q))
		//{
		//	g_engine.GetAudio().PlaySound("bass.wav"); //Play bass
		//}

		//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_W) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_W))
		//{
		//	g_engine.GetAudio().PlaySound("snare.wav"); //Play bass
		//}

		//if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_E) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_E))
		//{
		//	g_engine.GetAudio().PlaySound("open-hat.wav"); //Play bass
		//}

		//UPDATE


		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
		if (!g_engine.GetInput().GetMouseButtonDown(0) && g_engine.GetInput().GetPreviousMouseButtonDown(0))
		{
			//std::array<uint8_t, 4> color{ {random(255), random(255), random(255), 0}};
			for (int i = 0; i < 1000; i++)
			{
				//particles.push_back(Particle(mousePosition, randomOnUnitCircle() * randomf(10, 300), randomf(0.4f, 1), color));
			}
		}

		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}


		//DRAW
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();



		for (Particle particle : particles)
		{
			if (particle.lifespan > 0)
			{
				g_engine.GetRenderer().SetColor(particle.color[0], particle.color[1], particle.color[2], particle.color[3]);
				particle.Draw(g_engine.GetRenderer());
			}
		}

		scene->Draw(g_engine.GetRenderer());


		g_engine.GetRenderer().EndFrame();
	}

	return 0;

}