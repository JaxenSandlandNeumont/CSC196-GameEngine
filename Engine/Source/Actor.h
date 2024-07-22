#pragma once
#include "Transform.h"
#include <string>

class Scene;
class Model;
class Renderer;

class Actor {

public:
	Actor() = default;

	Actor(const Transform& transform) : m_transform{ transform } {}

	Actor(const Transform& transform, Model* model) :
		m_transform{ transform },
		m_model{ model }
	{}

	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);

	void SetDamping(float damping) { m_damping = damping; }
	void SetLifespan(float lifespan) { m_lifespan = lifespan; }
	void SetTag(const std::string& tag) { m_tag = tag; }
	const std::string& GetTag() { return m_tag; }

	Transform& GetTransform() { return m_transform; }

	virtual void OnCollision(Actor* actor) = 0;
	virtual int Collided(Actor* collider);

	friend class Scene;

public:

	void SetHitBox(Vector2 hitbox[5]);
	int xMin = -5;
	int xMax = 5;
	int yMin = -5;
	int yMax = 5;
	Vector2 m_hitbox[5] = { {-5, -5},{-5, 5},{5, 5},{5, -5}, { -5,-5 } };

protected:
	std::string m_tag;
	bool m_destroyed{ false };
	float m_lifespan = 0;
	bool m_landed = false;

	Transform m_transform;
	Vector2 m_velocity{ 0, 0 };

	float m_damping = 0;

	Model* m_model{ nullptr };
	Scene* m_scene{ nullptr };

};