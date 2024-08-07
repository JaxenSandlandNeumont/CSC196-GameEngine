#pragma once
#include "Transform.h"
#include "Vector2.h"
#include "Model.h"
#include <string>
#include <vector>
#include <memory>

class Scene;
class Renderer;
class vector;

class Actor {

public:
	Actor() = default;


	Actor(const Transform& transform, Model* model = nullptr) :
		m_transform{ transform },
		m_model{ model }
	{}

	~Actor() = default;

	virtual void Update(float dt);
	virtual void Draw(Renderer& renderer);
	virtual void DrawHitbox(Renderer& renderer);

	void SetDamping(float damping) { m_damping = damping; }
	void SetLifespan(float lifespan) { m_lifespan = lifespan; }
	void SetTag(const std::string& tag) { m_tag = tag; }
	Model* GetModel() { return m_model; }
	const std::string& GetTag() { return m_tag; }

	Transform& GetTransform() { return m_transform; }

	virtual int Collided(Actor* collider) { return 0; }

	friend class Scene;

public:


	Vector2 m_hitbox[5] = { {-5, -5},{-5, 5},{5, 5},{5, -5}, { -5,-5 } };

protected:
	std::string m_tag;
	bool m_destroyed{ false };
	float m_lifespan = 0;
	bool m_landed = false;

	Transform m_transform{};
	Vector2 m_velocity{ 0, 0 };

	float m_damping = 0;

	Model* m_model{ nullptr };

};