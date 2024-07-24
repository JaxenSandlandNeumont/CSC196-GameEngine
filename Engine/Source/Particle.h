#pragma once
#include "Vector2.h"
#include "Renderer.h"
#include "Color.h"

#include <array>

struct Particle
{
	Vector2 position{ 0,0 };
	Vector2 velocity{ 0,0 };
	float m_lifespan{ 0 };
	Color m_color{ 255, 0, 0, 0 };
	bool m_isActive = true;

	Particle() = default;

	Particle(Vector2 position, Vector2 velocity) :
		position{ position },
		velocity{ velocity }
	{};

	Particle(Vector2 position, Vector2 velocity, float lifespan) :
		position{ position },
		velocity{ velocity },
		m_lifespan{ lifespan }
	{};

	Particle(Vector2 position, Vector2 velocity, float lifespan, const Color& color) :
		position{ position },
		velocity{ velocity },
		m_lifespan{ lifespan },
		m_color{ color }
	{};

	Particle(Vector2 position, Vector2 velocity, const Color& color) :
		position{ position },
		velocity{ velocity },
		m_color{ color }
	{};



	void Update(float dt);
	void const Draw(Renderer& renderer);

};