#include "ParticleManager.h"

void ParticleManager::ExplodePlayer(Vector2 position)
{
	Color color{ (uint8_t)255, (uint8_t)255, (uint8_t)255, 0};
	for (int i = 0; i < 300; i++)
	{
		m_deathParticles.push_back(new Particle(position, randomOnUnitCircle() * randomf(300, 700), randomf(0.2f, 0.5f), color));
	}

}

void ParticleManager::Update(float dt)
{

	std::erase_if(m_deathParticles, [](Particle* particle) {return !particle->m_isActive; });

	for (Particle* particle : m_deathParticles)
	{
		particle->Update(dt);
	}
	
}

void ParticleManager::Draw(Renderer& renderer)
{
	for (Particle* particle : m_deathParticles)
	{
		particle->Draw(renderer);
	}
}
