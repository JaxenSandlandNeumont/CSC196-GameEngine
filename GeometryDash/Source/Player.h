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

	{
		SetHitBox(hitbox);
	}

	Player(float jumpSpeed, const Transform& transform, Model* model, std::vector<Vector2> hitbox) :
		Actor{ transform , model },
		m_jumpSpeed{ jumpSpeed }

	{
		SetHitBox(hitbox);
	}

	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}

	Player(const Transform& transform, Model* model, Vector2 hitbox[5]) :
		Actor{ transform, model }
	{
		SetHitBox(hitbox);
	}

	Player(const Transform& transform, Model* model, std::vector<Vector2> hitbox) :
		Actor{ transform, model }
	{
		SetHitBox(hitbox);
	}

	void Update(float dt);
	void OnCollision(Actor* actor);
	

private:
	float m_jumpSpeed = 100;
	float m_maxFallSpeed = 700;
	float m_gravity = 2000.0f;

	float m_jumpHoldTimer = 0.0f;
	bool m_jumpBoost1 = false;
	bool m_jumpBoost2 = false;


};