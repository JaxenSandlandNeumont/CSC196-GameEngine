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
void Actor::DrawHitbox(Renderer& renderer)
{
	m_model->Draw(m_hitbox, renderer, m_transform);
}

void Actor::SetHitBox(Vector2 hitbox[5])
{
	for (int i = 0; i < 5; i++)
	{
		m_hitbox[i] = hitbox[i];

		xMin = (hitbox[i].x < (float)xMin) ? hitbox[i].x : (float)xMin;
		xMax = (hitbox[i].x > (float)xMax) ? hitbox[i].x : (float)xMax;
		yMin = (hitbox[i].y < (float)yMin) ? hitbox[i].y : (float)yMin;
		yMax = (hitbox[i].y > (float)yMax) ? hitbox[i].y : (float)yMax;
	}
	

}


void Actor::SetHitBox(std::vector<Vector2> hitbox)
{
	if (hitbox.size() > 5 || hitbox.size() < 5)
	{
		//std::cout << "Invalid hitbox vector to array conversion";
	}

	for (int i = 0; i < 5; i++)
	{
		m_hitbox[i] = hitbox.at(i);

		xMin = (hitbox.at(i).x < (float)xMin) ? hitbox.at(i).x : (float)xMin;
		xMax = (hitbox.at(i).x > (float)xMax) ? hitbox.at(i).x : (float)xMax;
		yMin = (hitbox.at(i).y < (float)yMin) ? hitbox.at(i).y : (float)yMin;
		yMax = (hitbox.at(i).y > (float)yMax) ? hitbox.at(i).y : (float)yMax;
	}											
}
