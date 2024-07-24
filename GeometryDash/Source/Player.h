#pragma once
#include "Actor.h"

#include <vector>

class Player : public Actor
{

public:

	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}

	Player(float jumpSpeed, const Transform& transform, Model* model, Vector2 hitbox[5]) :
		Actor{ transform , model },
		m_jumpSpeed{ jumpSpeed }

	{}

	Player(float jumpSpeed, const Transform& transform, Model* model, std::vector<Vector2> hitbox) :
		Actor{ transform , model },
		m_jumpSpeed{ jumpSpeed }

	{}

	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}

	Player(const Transform& transform, Model* model, Vector2 hitbox[5]) :
		Actor{ transform, model }
	{}

	Player(const Transform& transform, Model* model, std::vector<Vector2> hitbox) :
		Actor{ transform, model }
	{}

	void Update(float dt);
	int Collided(Actor* collider) override;


	bool m_destroyed = false;

private:

	

	float m_jumpSpeed = 100.0f;
	float m_maxFallSpeed = 700.0f;
	float m_gravity = 2000.0f;

	float m_jumpHoldTimer = 0.0f;
	bool m_jumpBoost1 = false;
	bool m_jumpBoost2 = false;

};