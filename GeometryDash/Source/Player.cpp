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
		
		acceleration += (Vector2(0.0f, 1.0f) * (gravity * g_engine.GetTime().GetDeltaTime())); //Add gravity
		m_velocity += acceleration;

		if (m_velocity.y > m_maxFallSpeed)
		{
			m_velocity.y = m_maxFallSpeed;
		}
	}
	else
	{
		if (m_velocity.y > 0)
		{
			m_velocity.y = 0.0f;
		}
		else
		{
			m_velocity += acceleration;
		}
	}

	

	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().GetWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());


	Actor::Update(dt);
}

void Player::OnCollision(Actor* actor)
{
	
}

int Actor::Collided(Actor* collider)
{
	
	float colliderYMax = collider->yMax + collider->GetTransform().position.y;
	float colliderYMin = collider->yMin + collider->GetTransform().position.y;
	float colliderXMax = collider->xMax + collider->GetTransform().position.x;
	float colliderXMin = collider->xMin + collider->GetTransform().position.x;


	bool playerMinBelowColliderYMax = colliderYMax > yMin + GetTransform().position.y;
	bool playerMaxAboveColliderYMin = colliderYMin < yMax + GetTransform().position.y;

	bool playerMinBelowColliderXMax = colliderXMax > xMin + GetTransform().position.x;
	bool playerMaxAboveColliderXMin = colliderXMin < xMax + GetTransform().position.x;

	//bool xCollide = collider->xMin + collider->GetTransform().position.x <= xMax + GetTransform().position.x && collider->xMax + collider->GetTransform().position.x >= xMin + GetTransform().position.x;



	if (playerMaxAboveColliderXMin && playerMinBelowColliderXMax && playerMaxAboveColliderYMin && playerMinBelowColliderYMax)
	{ //Put player on top of object

		GetTransform().position.y = colliderYMax - 39.5f;
		return 1;
			
	}
	else
	{
		return 0;
	}
	return 0;
}
