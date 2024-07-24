#pragma once
#include "Scene.h"
#include "Text.h"
#include "Engine.h"
#include "ParticleManager.h"

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
	std::vector<std::vector<Vector2>>* DrawMode();
	void RunGame(eState state);
	void RunTitle();
	void EndGame(eState state);
	bool GetGameEnded() { return m_ended; };

protected:
	eState m_state{ eState::Title };
	Scene* m_scene{ nullptr };
	float m_respawnTimer{ 0 };
	float g_respawnTimer{ 0 };

private:
	float m_progressSpeed = 0.0f;
	std::vector<Text*> m_allText{};
	const float m_finalProgressSpeed{ 325.0f };
	ParticleManager* m_particleManager{ nullptr };
	bool m_drawHitboxes = false;
	bool m_ended = false;
	Font* m_smallFont;
	Font* m_mediumFont;
	Font* m_largeFont;

};