#pragma once
#include "Actor.h"
#include "ModelData.h"
#include <vector>

/*
enum class Gamemodes
{
	cube,
	wave
};
*/

class Player : public Actor
{

public:



	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}

	Player(float jumpSpeed, const Transform& transform, Model* model, std::vector<Vector2> hitbox) :
		Actor{ transform , model },
		m_jumpSpeed{ jumpSpeed }

	{}

	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}

	void Update(float dt);
	void CubeUpdate(float dt, bool clicked);
	void ShipUpdate(float dt, bool clicked);
	int Collided(Actor* collider) override;

	void ChangeGamemode(uint8_t gamemode);
	uint8_t GetGamemode() { return m_gamemode; }

	void SetModel(ModelPreset modelPreset);


	bool m_destroyed = false;

private:

	uint8_t m_gamemode = 0;

	bool m_shipGoingUp{ true };

	float m_jumpSpeed = 100.0f;
	float m_maxFallSpeed = 700.0f;

	float m_cubeGravity = 2000.0f;

	float m_waveSpeed = m_jumpSpeed * 0.7f;

	float m_jumpHoldTimer = 0.0f;
	bool m_jumpBoost1 = false;
	bool m_jumpBoost2 = false;

};