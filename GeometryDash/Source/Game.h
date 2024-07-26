#pragma once
#include "Scene.h"
#include "Text.h"
#include "Button.h"
#include "GamemodeBarrier.h"
#include "Engine.h"
#include "ParticleManager.h"
#include "Button.h"

class Game
{
public:
	enum class eState
	{
		Title,
		Level1,
		Level2,
		Level3,
		Endless
	};

public:
	Game() { Initialize(); }
	~Game() = default;

	void Initialize();
	void Shutdown();
	void Start();
	void Start(eState state);
	void Update(float dt);
	void Draw(Renderer& renderer);
	void CreateRandomPlatforms(int amount, Scene* scene);
	std::vector<std::vector<Vector2>> DrawMode();
	void RunGame(eState state);
	void RunTitle();
	std::vector<Button*> CreateTitleScreen();
	std::vector<Button*> CreateGameOverScreen(int finalScore);
	void EndGame(eState state);
	bool GetGameEnded() const { return m_ended; };

	void CreateChangeGamemodeBarrier(int x, uint8_t gamemode);

protected:
	eState m_state{ eState::Title };
	Scene* m_scene{ nullptr };

private:

	void UpdateScoreText(Text* scoreText, int score) {
		scoreText->Create(g_engine.GetRenderer(), std::to_string(score), Color{ 1.0f, 1.0f, 1.0f, 1.0f });
	}

	float m_progressSpeed = 0.0f;
	const float m_finalProgressSpeed{ 450.0f };

	ParticleManager* m_particleManager{ nullptr };
	bool m_drawHitboxes = true;
	bool m_ended = false;

	Font* m_smallFont;
	Font* m_mediumFont;
	Font* m_largeFont;


	float m_progress;
};