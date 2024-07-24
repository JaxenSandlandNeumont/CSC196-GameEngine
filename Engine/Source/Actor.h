#pragma once
#include "Transform.h"
#include "Vector2.h"
#include <string>
#include <vector>
#include <memory>

class Scene;
class Model;
class Renderer;
class vector;

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
	virtual void DrawHitbox(Renderer& renderer);

	void SetDamping(float damping) { m_damping = damping; }
	void SetLifespan(float lifespan) { m_lifespan = lifespan; }
	void SetTag(const std::string& tag) { m_tag = tag; }
	const std::string& GetTag() { return m_tag; }

	Transform& GetTransform() { return m_transform; }

	virtual int Collided(Actor* collider) { return 0; }

	friend class Scene;

public:

	void SetHitBox(Vector2 hitbox[5]);
	void SetHitBox(std::vector<Vector2> hitbox);
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
	bool m_canJump = false;

	Transform m_transform;
	Vector2 m_velocity{ 0, 0 };

	float m_damping = 0;

	Model* m_model{ nullptr };

};