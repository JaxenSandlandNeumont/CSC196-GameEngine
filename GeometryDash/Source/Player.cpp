#include "Player.h"
#include "Game.h"
#include "Engine.h"
#include "Scene.h"
#include <iostream>
#include <memory>


void Player::Update(float dt)
{
	float thrust = 0;

	bool clicked = g_engine.GetInput().GetPreviousMouseButtonDown(0)
		|| g_engine.GetInput().GetPrevKeyDown(SDL_SCANCODE_SPACE);
	if (m_gamemode == 0)
	{
		CubeUpdate(dt, clicked);
	}
	else if (m_gamemode == 1)
	{
		ShipUpdate(dt, clicked);
	}


	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().GetHeight());


	Actor::Update(dt);
}

void Player::CubeUpdate(float dt, bool clicked)
{
	float thrust = 0;

	if (clicked)
	{

		if (m_landed && !m_jumpHoldTimer)
		{
			m_jumpHoldTimer = 0.0f;
			m_jumpBoost1 = false;
			m_jumpBoost2 = false;

			g_engine.GetAudio().PlaySound("jumpSound.wav");

			thrust -= m_jumpSpeed;
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

	
		}

		if (m_jumpHoldTimer > 0.2f && !m_jumpBoost2)
		{
			m_jumpBoost2 = true;
			thrust -= m_jumpSpeed / 6;
		}

	}
	else
	{
		m_jumpHoldTimer = 0.0f;
		m_jumpBoost1 = false;
		m_jumpBoost2 = false;
	}

	Vector2 acceleration = (Vector2{ 0.0f, 1.0f } * thrust); // Make sure it's not moving rhe player on the X axis

	if (!m_landed)
	{
		acceleration += (Vector2(0.0f, 1.0f) * (m_cubeGravity * g_engine.GetTime().GetDeltaTime())); // Add gravity
		m_velocity += acceleration;

		if (m_velocity.y > m_maxFallSpeed)
		{
			m_velocity.y = m_maxFallSpeed;  // Limit fall speed
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
}




void Player::ShipUpdate(float dt, bool clicked)
{
	if (m_shipGoingUp)
	{
		m_velocity.y = -m_waveSpeed;

		m_transform.rotation = -45.0f;
	}
	else
	{
		m_velocity.y = m_waveSpeed;

		m_transform.rotation = 45.0f;
	}

	if (g_engine.GetInput().GetMouseButtonDown(0) && !g_engine.GetInput().GetPreviousMouseButtonDown(0))
	{
		g_engine.GetAudio().PlaySound("waveTurnSound.wav");
		m_shipGoingUp = !m_shipGoingUp;
	}

}





int Player::Collided(Actor* collider)
{
	
	float colliderYMax = collider->GetModel()->m_yMax + collider->GetTransform().position.y;
	float colliderYMin = collider->GetModel()->m_yMin + collider->GetTransform().position.y;
	float colliderXMax = collider->GetModel()->m_xMax + collider->GetTransform().position.x;
	float colliderXMin = collider->GetModel()->m_xMin + collider->GetTransform().position.x;


	float selfYMin = GetModel()->m_yMin + GetTransform().position.y;
	float selfYMax = GetModel()->m_yMax + GetTransform().position.y;
	float selfXMax = GetModel()->m_xMax + GetTransform().position.x;
	float selfXMin = GetModel()->m_xMin + GetTransform().position.x;


	bool playerMinBelowColliderYMax = colliderYMax > selfYMin;
	bool playerMaxAboveColliderYMin = colliderYMin < selfYMax;

	bool playerMinBelowColliderXMax = colliderXMax > selfXMin;
	bool playerMaxAboveColliderXMin = colliderXMin < selfXMax;

	//bool xCollide = collider->xMin + collider->GetTransform().position.x <= xMax + GetTransform().position.x && collider->xMax + collider->GetTransform().position.x >= xMin + GetTransform().position.x;

	bool collided = playerMaxAboveColliderXMin && playerMinBelowColliderXMax && playerMaxAboveColliderYMin && playerMinBelowColliderYMax;

	if (collided)
	{ 
		if (!collider->GetTag().compare("Barrier"))
		{
			GamemodeBarrier* barrier = (GamemodeBarrier*)collider;
			if (barrier->GetToGamemode() != m_gamemode)
			{
				ChangeGamemode(barrier->GetToGamemode());
			}
			return 0;
		}

		if (m_gamemode == 1)
		{
			m_destroyed = true;
			return -1;
		}

		float playerBottomDistanceFromColliderTop = Math::absValue(selfYMax - colliderYMin);
		float playerTopDistanceFromColliderBottom = Math::absValue(selfYMin - colliderYMax);
		float playerRightDistanceFromColliderLeft = Math::absValue(selfXMax - colliderXMin);

		float speedAdjustment = (Math::absValue(m_velocity.y) > 400) ? 2.0f : 0.0f;

		if (playerBottomDistanceFromColliderTop < 7 + speedAdjustment || playerRightDistanceFromColliderLeft > 10 )
		{
			GetTransform().position.y = colliderYMin - GetModel()->m_yMax * 0.98f;
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

void Player::ChangeGamemode(uint8_t gamemode)
{
	m_gamemode = gamemode;
	ModelPreset modelPreset = ModelData::GetFriendlyModel(gamemode);
	SetModel(modelPreset);
	m_transform.rotation = 0;
	g_engine.GetAudio().PlaySound("changeGamemodeSound.wav");
}

void Player::SetModel(ModelPreset modelPreset)
{
	m_model = new Model(modelPreset.m_model, modelPreset.m_color);
}

