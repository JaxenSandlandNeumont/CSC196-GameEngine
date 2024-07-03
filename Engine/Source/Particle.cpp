#pragma once
#include "Particle.h"

void Particle::Update(float dt)
{
	position = position + (velocity * dt);
	lifespan = lifespan - dt;
}

void Particle::Draw(Renderer& renderer)
{
	renderer.DrawPoint(position.x, position.y);
}