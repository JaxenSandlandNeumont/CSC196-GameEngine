#include "Player.h"
#include "Game.h"
#include "Engine.h"
#include "Scene.h"
#include <iostream>
#include <memory>


void Player::Update(float dt)
{
	float thrust = 0;


	if (g_engine.GetInput().GetPreviousMouseButtonDown(0)
		|| g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_SPACE))
	{
		if (m_landed && !m_jumpHoldTimer)
		{
			m_jumpHoldTimer = 0.0f;
			m_jumpBoost1 = false;
			m_jumpBoost2 = false;

			thrust -= m_jumpSpeed;
			std::cout << "Boost 0! \n";
			m_jumpHoldTimer += g_engine.GetTime().GetDeltaTime();
		}

		if (m_jumpHoldTimer)
		{
			m_jumpHoldTimer += g_engine.GetTime().GetDeltaTime();
		}



		if (m_jumpHoldTimer > 0.1f && !m_jumpBoost1)
		{
			m_jumpBoost1 = true;
			thrust -= m_jumpSpeed / 4;
			std::cout << "Boost 1!\n ";
		}

		if (m_jumpHoldTimer > 0.2f && !m_jumpBoost2)
		{
			m_jumpBoost2 = true;
			thrust -= m_jumpSpeed / 6;
			std::cout << "Boost 2! \n";
		}
		
	}
	else
	{
		m_jumpHoldTimer = 0.0f;
		m_jumpBoost1 = false;
		m_jumpBoost2 = false;
	}


	Vector2 acceleration = (Vector2{ 0.0f, 1.0f } * thrust);
	if (!m_landed)
	{
		
		acceleration += (Vector2(0.0f, 1.0f) * (m_gravity * g_engine.GetTime().GetDeltaTime())); //Add gravity
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

int Player::Collided(Actor* collider)
{
	
	float colliderYMax = collider->yMax + collider->GetTransform().position.y;
	float colliderYMin = collider->yMin + collider->GetTransform().position.y;
	float colliderXMax = collider->xMax + collider->GetTransform().position.x;
	float colliderXMin = collider->xMin + collider->GetTransform().position.x;


	float selfYMin = yMin + GetTransform().position.y;
	float selfYMax = yMax + GetTransform().position.y;
	float selfXMax = xMax + GetTransform().position.x;
	float selfXMin = xMin + GetTransform().position.x;


	bool playerMinBelowColliderYMax = colliderYMax > selfYMin;
	bool playerMaxAboveColliderYMin = colliderYMin < selfYMax;

	bool playerMinBelowColliderXMax = colliderXMax > selfXMin;
	bool playerMaxAboveColliderXMin = colliderXMin < selfXMax;

	//bool xCollide = collider->xMin + collider->GetTransform().position.x <= xMax + GetTransform().position.x && collider->xMax + collider->GetTransform().position.x >= xMin + GetTransform().position.x;

	bool collided = playerMaxAboveColliderXMin && playerMinBelowColliderXMax && playerMaxAboveColliderYMin && playerMinBelowColliderYMax;

	if (collided)
	{ 
		float playerBottomDistanceFromColliderTop = Math::absValue(selfYMax - colliderYMin);
		float playerTopDistanceFromColliderBottom = Math::absValue(selfYMin - colliderYMax);

		float speedAdjustment = (Math::absValue(m_velocity.y) > 400) ? 2.0f : 0.0f;

		if (playerBottomDistanceFromColliderTop < 7 + speedAdjustment)
		{
			GetTransform().position.y = colliderYMin - yMax * 0.98f;
			//std::cout << "Safe landing!\n";
		}
		else if (playerTopDistanceFromColliderBottom < 5 + speedAdjustment)
		{
			m_velocity.y = (m_velocity.y < 0) ? 2000.0f * g_engine.GetTime().GetDeltaTime() : m_velocity.y;
			//std::cout << "Ceiling hit!\n";
			return 0;
		}
		else
		{
			std::cout << "DEATH FROM " << playerBottomDistanceFromColliderTop << "\n";
			m_destroyed = true;
			return -1;
		}
		
		return 1;
	}
	else
	{
		return 0;
	}
	return 0;
}

