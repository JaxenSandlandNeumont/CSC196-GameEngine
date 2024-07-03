#pragma once
#include "Vector2.h"
#include "Renderer.h"

#include <array>

struct Particle
{
	Vector2 position{ 0,0 };
	Vector2 velocity{ 0,0 };
	float lifespan{ 0 };
	std::array<uint8_t, 4> color{ {255, 0, 0, 0} };

	Particle() = default;

	Particle(Vector2 position, Vector2 velocity) :
		position{ position },
		velocity{ velocity }
	{};

	Particle(Vector2 position, Vector2 velocity, float lifespan) :
		position{ position },
		velocity{ velocity },
		lifespan{ lifespan }
	{};

	Particle(Vector2 position, Vector2 velocity, float lifespan, const std::array<uint8_t, 4>& color) :
		position{ position },
		velocity{ velocity },
		lifespan{ lifespan },
		color{ color }
	{};

	Particle(Vector2 position, Vector2 velocity, const std::array<uint8_t, 4>& color) :
		position{ position },
		velocity{ velocity },
		color{ color }
	{};



	void Update(float dt);
	void Draw(Renderer& renderer);

};