#include "Engine.h"
#include "ModelData.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "FileManager.h"

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
		FileManager* lm = new FileManager();

		char drName[] = "LevelData";
		int result = lm->mkDir(drName);


		lm->WriteFile("LevelData/test2.txt", "string 1\nstring 2\nstring 3");
		std::vector<std::string> lines = lm->ReadFile("LevelData/test1.txt");
	
		for (std::string line : lines)
		{
			std::cout << line << "\n";
		}
		return 0;
	}








	g_engine.Initialize();


	//Create Systems



	Time time;

	Font* font = new Font();
	font->Load("Finland.ttf", 20);


	Text* text = new Text(font);
	text->Create(g_engine.GetRenderer(), "Hello World", Color{ 1.0f, 1.0f, 1.0f, 1.0f });


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


	Color color{ 1, 1, 0 };

	const int modelNum = 2;

	std::vector<std::vector<Vector2>> modelPoints = ModelData::GetModel(modelNum);
	Model* model = new Model{ modelPoints, color};
	//Transform transform{ { g_engine.GetRenderer().getWidth() >> 1 , g_engine.GetRenderer().getHeight() >> 1}, 0, 5};

	// >> 1 shifts binary over 1


	Scene* scene = new Scene();


	Transform transform{ { randomf(0, 800) , randomf(0, 600)}, 0, 5};

	Player* player = new Player(10, transform, model);
	player->SetDamping(4.0f);
	player->SetTag("Player");
	scene->AddActor(player);




	bool quit = false;
	while (!quit)
	{
		g_engine.GetAudio().Update();


		time.Tick();

		g_engine.GetAudio().AddSound("bass.wav");

		g_engine.GetInput().Update();

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		scene->Update(time.GetDeltaTime());

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Q)) {
			g_engine.GetAudio().PlaySound("bass.wav");
		}


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
		// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();



		// draw line


		text->Draw(g_engine.GetRenderer(), 40, 40);

		scene->Draw(g_engine.GetRenderer());




		// show screen
		g_engine.GetRenderer().EndFrame();
	}

	return 0;

}