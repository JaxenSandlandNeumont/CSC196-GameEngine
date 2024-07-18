#pragma once
#include "Actor.h"

class Player : public Actor
{

public:

	Player() = default;
	Player(const Transform& transform) : Actor{ transform } {}

	Player(float speed, const Transform& transform, Model* model) :
		Actor{ transform , model },
		m_speed{ speed }

	{}
	Player(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}

	void Update(float dt);
	void OnCollision(Actor* actor);

private:

	float m_speed = 0;
	float m_fireTimer = 0;


};