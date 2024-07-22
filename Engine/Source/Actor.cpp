#include "Actor.h"
#include "Model.h"

void Actor::Update(float dt)
{

	if (m_lifespan != 0) 
	{
		m_lifespan -= dt;
		if (m_lifespan <= 0)
		{
			m_destroyed = true;
		}
	}


	m_transform.position += (m_velocity * dt);
	m_velocity *= 1.0f / (1.0f + m_damping * dt);
}

void Actor::Draw(Renderer& renderer)
{
	m_model->Draw(renderer, m_transform);
}

void Actor::SetHitBox(Vector2 hitbox[5])
{
	for (int i = 0; i < 5; i++)
	{
		m_hitbox[i] = hitbox[i];

		xMin = (hitbox[i].x < xMin) ? hitbox[i].x : xMin;
		xMax = (hitbox[i].x > xMin) ? hitbox[i].x : xMax;
		yMin = (hitbox[i].y < yMin) ? hitbox[i].y : yMin;
		yMax = (hitbox[i].y < yMin) ? hitbox[i].y : yMax;
	}
	

}
