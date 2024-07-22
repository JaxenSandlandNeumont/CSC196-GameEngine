#include "Game.h"
#include "FileManager.h"
#include "Random.h"
#include "Player.h"
#include "Object.h"
#include "ModelData.h"

void Game::Initialize()
{

}

void Game::Shutdown()
{
}

void Game::Update(float dt)
{

	m_scene->Update(dt, m_progressSpeed);
}

void Game::Draw(Renderer& renderer)
{
	switch (m_state)
	{
	case Game::eState::Title:
	{

	}
		break;
	case Game::eState::Level1:
	{

	}
		break;
	case Game::eState::Level2:
	{

	}
		break;
	case Game::eState::Level3:
	{

	}
		break;
	default:
		break;
	}
	m_scene->Draw(renderer, m_drawHitboxes);
}

std::vector<std::vector<Vector2>>* Game::DrawMode()
{
	FileManager* lm = new FileManager();

	char drName[] = "LevelData";
	int result = lm->mkDir(drName);


	//lm->WriteFile("LevelData/test3.txt", "string 1\nstring 2\nstring 3");
	//std::vector<std::string> lines = lm->ReadFile("LevelData/test3.txt");
	/*
	for (std::string line : lines)
	{
		std::cout << line << "\n";
	}*/

	g_engine.Initialize();

	std::vector<Vector2> currentPoints;
	std::vector<std::vector<Vector2>> allPoints;
	bool quit = false;
	int xOffput = 0;
	int gridPlacement = 25;
	float holdButtonTimer = 0.0f;
	while (!quit)
	{
		g_engine.Update();
		holdButtonTimer += g_engine.GetTime().GetDeltaTime();


		Vector2 mousePosition = g_engine.GetInput().GetMousePosition();
		Vector2 clickedPosition = Vector2{ (int)mousePosition.x / gridPlacement, (int)mousePosition.y / gridPlacement } *gridPlacement + (gridPlacement / 2) - Vector2{ xOffput , 0 };

		// Left click
		if (g_engine.GetInput().GetMouseButtonDown(0) && g_engine.GetInput().GetPreviousMouseButtonDown(0))
		{
			if (currentPoints.empty())
			{
				currentPoints.push_back(clickedPosition);
			}
			else
			{
				float distance = (currentPoints.back() - clickedPosition).Length();
				if (distance > 10)
				{
					currentPoints.push_back(clickedPosition);
				}
			}
		}


		// Right click
		if (g_engine.GetInput().GetMouseButtonDown(2) && g_engine.GetInput().GetPreviousMouseButtonDown(2))
		{
			allPoints.push_back(currentPoints);
			currentPoints.clear();
		}

		// Left key
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT))
		{
			if (xOffput < 0)
			{
				if (holdButtonTimer >= 0.2f)
				{
					xOffput += gridPlacement;
					holdButtonTimer = 0;
				}
			}

		}

		// Right key
		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT))
		{
			if (holdButtonTimer >= 0.2f)
			{
				xOffput -= gridPlacement;
				holdButtonTimer = 0;
			}

		}



		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		g_engine.GetRenderer().SetColor(500, 0, 500, 1);

		// Draw current shape
		for (int i = 0; currentPoints.size() > 1 && i < currentPoints.size() - 1; i++)
		{
			g_engine.GetRenderer().DrawLine(currentPoints[i].x + xOffput, currentPoints[i].y, currentPoints[i + 1].x + xOffput, currentPoints[i + 1].y);
		}

		// Draw line from current shape to mouse
		if (!currentPoints.empty())
		{
			g_engine.GetRenderer().DrawLine(currentPoints.back().x + xOffput, currentPoints.back().y, clickedPosition.x + xOffput, clickedPosition.y);
		}

		// Draw the previous shapes
		for (int e = 0; allPoints.size() > 1 && e < allPoints.size() - 1; e++)
		{
			for (int i = 0; allPoints[e].size() > 1 && i < allPoints[e].size() - 1; i++)
			{

				g_engine.GetRenderer().DrawLine(allPoints[e][i].x + xOffput, allPoints[e][i].y, allPoints[e][i + 1].x + xOffput, allPoints[e][i + 1].y);
			}
		}




		// show screen
		g_engine.GetRenderer().EndFrame();

	}

	return &allPoints;

}





















void Game::RunGame(int level)
{

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

	const int modelNum = 0;



	Scene* scene = new Scene();


	std::vector<std::vector<Vector2>> modelPoints = ModelData::GetFriendlyModel(modelNum);
	Model* model = new Model{ modelPoints, color };
	Transform transform{ {  g_engine.GetRenderer().GetWidth() >> 1  , 300 }, 0};
	Vector2 playerHitBox[5]
	{
		{-25 , -25 }, {-25, 25 }, {25, 25}, {25, -25}, {-25, -25}
	};

	Player* player = new Player(800, transform, model, playerHitBox);
	player->SetDamping(0.0f);
	scene->SetPlayer(player);

	for (int i = 0; i < 50; i++)
	{
		int randomHeight = random(400, 550);
		Transform transform1{ { 550 + 200 * i , randomHeight }, 0 };
		std::vector<Vector2> basePlatePoints
		{
			{-50 , -10 }, {-50, 10}, {50, 10}, {50, -10}, {-50, -10}
		};
		model = new Model{ basePlatePoints, color };
		Object* basePlate = new Object(transform1, model, basePlatePoints);
		scene->AddActor(basePlate);
	}

	Transform transform1{ { 399 , 500 }, 0};
	std::vector<Vector2> basePlatePoints
	{
		{-400 , -10 }, {-400, 10}, {400, 10}, {400, -10}, {-400, -10}
	};
	model = new Model{ basePlatePoints, color };
	Object* basePlate = new Object(transform1, model, basePlatePoints);
	scene->AddActor(basePlate);


	g_engine.GetAudio().AddSound("bass.wav");


	while (!g_engine.IsQuit())
	{


		time.Tick();
		g_engine.Update();

		scene->Update(time.GetDeltaTime(), m_progressSpeed);

		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Q)) {
			g_engine.GetAudio().PlaySound("bass.wav");
		}


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

		/*
		for (Particle& particle : particles)
		{
			particle.Update(time.GetDeltaTime());
			if (particle.position.x > 800) particle.position.x = 0;
			if (particle.position.x < 0) particle.position.x = 800;
		}
		*/

		//DRAW
		// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();



		// draw line


		text->Draw(g_engine.GetRenderer(), 40, 40);

		scene->Draw(g_engine.GetRenderer(), m_drawHitboxes);




		// show screen
		g_engine.GetRenderer().EndFrame();
	}
}
