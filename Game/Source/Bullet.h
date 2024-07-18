#pragma once
#include "Actor.h"

class Bullet : public Actor
{

public:

	Bullet() = default;

	Bullet(const Transform& transform) : Actor{ transform } {};

	Bullet(float speed, const Transform& transform, Model* model) :
		Actor{ transform , model },
		m_speed{ speed }

	{};

	void Update(float dt);


private:

	float m_speed = 0;


};