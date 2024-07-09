#pragma once
#include "Particle.h"

void Particle::Update(float dt)
{
	position = position + (velocity * dt);
	lifespan = lifespan - dt;
}

void Particle::Draw(Renderer& renderer)
{
	renderer.DrawRect(position.x, position.y, 10.0f, 10.0f);
}