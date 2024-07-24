#pragma once
#include "Engine.h"

#include <vector>

class ParticleManager
{
public:

	ParticleManager() = default;

	void ExplodePlayer(Vector2 position);
	void Update(float dt);
	void Draw(Renderer& renderer);
	void ClearDeathParticles() { m_deathParticles.clear(); }

private:

	std::vector<Particle*> m_deathParticles{};

};