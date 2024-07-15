#include "Player.h"
#include "Engine.h"

#include <SDL.h>

void Player::Update(float dt)
{
	float thrust = 0;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_LEFT))
	{
		m_transform.rotation -= Math::DegToRad(200) * dt;
	}

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_transform.rotation += Math::DegToRad(200) * dt;
	}

	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_UP))		thrust = m_speed;
	if (g_engine.GetInput().GetKeyDown(SDL_SCANCODE_DOWN))	thrust = -m_speed;

	Vector2 velocity = Vector2{ thrust, 0.0f }.Rotate(m_transform.rotation);
	m_transform.position += velocity * dt;
	m_transform.position.x = Math::Wrap(m_transform.position.x, (float)g_engine.GetRenderer().getWidth());
	m_transform.position.y = Math::Wrap(m_transform.position.y, (float)g_engine.GetRenderer().getHeight());

	Actor::Update(dt);

}
