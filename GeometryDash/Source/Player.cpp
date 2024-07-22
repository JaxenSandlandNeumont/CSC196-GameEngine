#include "Player.h"
#include "Game.h"
#include "Engine.h"
#include "Scene.h"
#include <iostream>


void Player::Update(float dt)
{
	float thrust = 0;
	float gravity = 2000.0f;


	if (g_engine.GetInput().GetMouseButtonDown(0) && !g_engine.GetInput().GetPreviousMouseButtonDown(0)
		|| g_engine.GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && !g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_SPACE))
	{
		if (m_landed)
		{
			thrust -= m_jumpSpeed;
		}
		
	}

	Vector2 acceleration = (Vector2{ 0.0f, 1.0f } * thrust);
	if (!m_landed)
	{
		acceleration += (Vector2(0.0f, 1.0f) * (gravity * g_engine.GetTime().GetDeltaTime()));
	}
	else
	{
		m_velocity.y = 0;
	}

	m_velocity += acceleration;

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());


	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	
}

int Actor::Collided(Actor* collider)
{
	
	for (int i = 0; i < 4; i++)
	{
		if (collider->yMax + collider->GetTransform().position.y >= yMin + GetTransform().position.y && collider->yMin + +collider->GetTransform().position.y <= yMax + GetTransform().position.y) // Match Y values
		{
			if (collider->xMin + collider->GetTransform().position.x <= xMin + GetTransform().position.x && collider->xMax + collider->GetTransform().position.x >= xMax + GetTransform().position.x) // Match X values
			{
				if (!m_landed)
				{
					GetTransform().position.y = -collider->yMax + collider->GetTransform().position.y + yMin + yMin;
					m_landed = true;
				}
				
				return 1;
			}
		}
		m_landed = false;

	}
	return 0;
}
