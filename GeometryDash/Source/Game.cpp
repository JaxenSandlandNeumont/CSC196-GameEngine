#include "Game.h"
#include "FileManager.h"
#include "Random.h"
#include "Player.h"
#include "Object.h"
#include "ModelData.h"
#include "ParticleManager.h"

#include <memory>
#include <iostream>

void Game::Initialize()
{
	g_engine.Initialize();
	m_scene = new Scene();
	m_particleManager = new ParticleManager();

	m_smallFont = new Font();
	m_smallFont->Load("Minercraftory.ttf", 15);

	m_mediumFont = new Font();
	m_mediumFont->Load("Minercraftory.ttf", 30);

	m_largeFont = new Font();
	m_largeFont->Load("Minercraftory.ttf", 60);
}

void Game::Shutdown()
{

}

void Game::Start()
{
	Start(m_state);
}

void Game::Start(eState state)
{

	
	m_ended = false;
	if (m_scene)
	{
		m_scene->ClearActors();
	}
	m_allText.clear();
	m_particleManager->ClearDeathParticles();
	

	m_state = state;

	switch (m_state)
	{
		case Game::eState::Title:
		{
			RunTitle();
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

		case Game::eState::Endless:
		{
			RunGame(eState::Endless);
		}
		break;

		default:

			break;
	}
}

void Game::Update(float dt)
{
	g_engine.Update();
	m_particleManager->Update(dt);

	m_scene->Update(dt, m_progressSpeed);
}

void Game::Draw(Renderer& renderer)
{
	for (Text* text : m_allText)
	{
		text->Draw(g_engine.GetRenderer());
	}
	
	m_particleManager->Draw(g_engine.GetRenderer());
	m_scene->Draw(g_engine.GetRenderer(), m_drawHitboxes);
}

void Game::CreateRandomPlatforms(int amount, Scene* scene)
{
	Color color{ 1, 1, 0 };
	for (int i = 0; i < amount; i++)
	{
		int randomHeight = random(400, 550);
		Transform transform1{ { 1400 + 200 * i , randomHeight }, 0 };
		std::vector<Vector2> basePlatePoints
		{
			{-50 , -20 }, {-50, 0}, {50, 0}, {50, -20}, {-50, -20}
		};
		Model* model = new Model{ basePlatePoints, color };
		auto basePlate = std::make_unique<Object>(transform1, model, basePlatePoints);
		scene->AddActor(std::move(basePlate));
	}
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

		g_engine.GetRenderer().SetColor((uint8_t)500, (uint8_t)0, (uint8_t)500, (uint8_t)1);

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





















void Game::RunGame(eState state)
{

	

	m_progressSpeed = m_finalProgressSpeed;

	

	//Create Systems





	Text* text = new Text(m_smallFont, Vector2{ g_engine.GetRenderer().GetWidth() >> 1, 40 });
	text->Create(g_engine.GetRenderer(), "Score: 0", Color{ 1.0f, 1.0f, 1.0f, 1.0f });
	m_allText.push_back(text);
	

	// create audio system

	std::vector<FMOD::Sound*> sounds;
	FMOD::Sound* sound = nullptr;

	g_engine.GetAudio().AddSound("bass.wav");
	g_engine.GetAudio().AddSound("clap.wav");
	g_engine.GetAudio().AddSound("close-hat.wav");
	g_engine.GetAudio().AddSound("cowbell.wav");
	g_engine.GetAudio().AddSound("open-hat.wav");
	g_engine.GetAudio().AddSound("snare.wav");



	CreateRandomPlatforms(100, m_scene);

	const int modelNum = 0;
	Color color{ 1, 1, 0 };

	std::vector<std::vector<Vector2>> modelPoints = ModelData::GetFriendlyModel(modelNum);
	std::vector<Vector2> playerHitbox = ModelData::GetFriendlyModel(modelNum)[0];
	Model* model = new Model{ modelPoints, color };
	Transform transform{ {  g_engine.GetRenderer().GetWidth() >> 1 , 400 }, 0};

	auto player = std::make_unique<Player>(600.0f, transform, model, playerHitbox);
	m_scene->SetPlayer(player.get());

	

	Transform transform1{ { 600 , 650 }, 0};
	std::vector<Vector2> basePlatePoints
	{
		{-600 , -200 }, {-600, 0}, {600, 0}, {600, -200}, {-600, -200}
	};
	Model* model1 = new Model { basePlatePoints, color };
	auto basePlate1 = std::make_unique<Object>(transform1, model1, basePlatePoints);
	m_scene->AddActor(std::move(basePlate1));


	Transform transform2{ { 600 , 300 }, 0};
	auto basePlate2 = std::make_unique<Object>(transform2, model1, basePlatePoints);
	m_scene->AddActor(std::move(basePlate2));


	g_engine.GetAudio().AddSound("bass.wav");


	while (!m_ended)
	{


		Update(g_engine.GetTime().GetDeltaTime());
		

		m_progressSpeed += 5.0f * g_engine.GetTime().GetDeltaTime();


		if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_Q) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_Q)) {
			g_engine.GetAudio().PlaySound("bass.wav");
		}


		if (m_scene->GetPlayer() && player->m_destroyed)
		{
			m_particleManager->ExplodePlayer(player->GetTransform().position);
			m_scene->SetPlayer(nullptr);
			EndGame(state);
		}

		


		//DRAW
		// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();


		//Draw the stuff
		Draw(g_engine.GetRenderer());


		// show screen
		g_engine.GetRenderer().EndFrame();
	}
	
	m_allText.clear();
	text = new Text(m_mediumFont, Vector2{ g_engine.GetRenderer().GetWidth() >> 1, g_engine.GetRenderer().GetHeight() >> 1 });
	text->Create(g_engine.GetRenderer(), "Click to restart", Color{ 1.0f, 1.0f, 1.0f, 1.0f });
	m_allText.push_back(text);

	while (!g_engine.GetInput().GetPreviousMouseButtonDown(0))
	{

		Update(g_engine.GetTime().GetDeltaTime());

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();



		// draw line
		Draw(g_engine.GetRenderer());



		// show screen
		g_engine.GetRenderer().EndFrame();


	}


	Start(state);
}






void Game::RunTitle()
{
	eState chosenLevel = eState::Title;

	Text* title = new Text(m_largeFont, Vector2{ g_engine.GetRenderer().GetWidth() >> 1, g_engine.GetRenderer().GetHeight() / 3 });
	title->Create(g_engine.GetRenderer(), "Trigonometry Run", Color{ 1.0f, 1.0f, 1.0f });
	m_allText.push_back(title);

	while (chosenLevel == eState::Title)
	{

		Update(g_engine.GetTime().GetDeltaTime());

		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();



		// draw line
		Draw(g_engine.GetRenderer());



		// show screen
		g_engine.GetRenderer().EndFrame();


	}

	Start(chosenLevel);
}



void Game::EndGame(eState state)
{
	m_progressSpeed = 0.0f;
	m_ended = true;
}
