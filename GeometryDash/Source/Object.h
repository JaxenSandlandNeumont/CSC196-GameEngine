#pragma once
#include "Actor.h"

class Object : public Actor
{
public:
	Object() = default;
	Object(const Transform& transform) : Actor{ transform } {}

	Object(const Transform& transform, Model* model) :
		Actor{ transform, model }
	{}

	Object(const Transform& transform, Model* model, Vector2 hitbox[5]) :
		Actor{ transform, model }
	{
		SetHitBox(hitbox);
	}

	
	Object(const Transform& transform, Model* model, std::vector<Vector2> hitbox) :
		Actor{ transform, model }
	{
		SetHitBox(hitbox);
	}
	


	void Update(float dt);
	void OnCollision(Actor* actor);
};
