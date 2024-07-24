#pragma once
#include "Particle.h"
#include "Engine.h"

void Particle::Update(float dt)
{
	position = position + (velocity * dt);
	m_lifespan -= dt;

	if (m_lifespan <= 0.0f)
	{
		m_isActive = false;
	}
}

void const Particle::Draw(Renderer& renderer)
{
	g_engine.GetRenderer().SetColor(m_color);
	renderer.DrawRect(position.x, position.y, 3.0f, 3.0f);
}