#include "Bullet.h"

void Bullet::Update(float dt)
{
	m_velocity = Vector2(1, 0).Rotate(m_transform.rotation) * m_speed;
	Actor::Update(dt);
}

void Bullet::OnCollision(Actor* actor)
{
}