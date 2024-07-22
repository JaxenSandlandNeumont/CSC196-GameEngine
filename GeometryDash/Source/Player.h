#pragma once
#include "Actor.h"

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

	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}

	Player(const Transform& transform, Model* model, Vector2 hitbox[5]) :
		Actor{ transform, model }
	{
		SetHitBox(hitbox);
	}

	void Update(float dt);
	void OnCollision(Actor* actor);
	

private:
	float m_jumpSpeed = 100;
	float m_maxFallSpeed = 700;


};