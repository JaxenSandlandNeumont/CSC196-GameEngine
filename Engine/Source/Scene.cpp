#include "Scene.h"
#include "Actor.h"
#include "Color.h"
#include "Engine.h"


void Scene::Update(float dt, float progressSpeed)
{

	//std::erase_if(m_actors, [](Actor* actor) {return actor->m_destroyed; });
	m_player->Update(dt);

	int playerCollisionLog = 0;

	for (Actor* actor : m_actors)
	{
		actor->GetTransform().position.x -= progressSpeed * g_engine.GetTime().GetDeltaTime();
		actor->Update(dt);
		playerCollisionLog += m_player->Collided(actor);
	}

	m_player->m_landed = (playerCollisionLog == 1);
}

void Scene::Draw(Renderer& renderer, bool drawHitboxes)
{
	Color playerColor{ 1, 1, 0, 1 };
	g_engine.GetRenderer().SetColor(playerColor);
	m_player->Draw(renderer);


	if (drawHitboxes)
	{
		Color playerHitboxColor{ 1, 0, 0, 1 };
		g_engine.GetRenderer().SetColor(playerHitboxColor);
		m_player->DrawHitbox(renderer);
	}


	for (Actor* actor : m_actors)
	{

		Color ObjectColor{ 1, 1, 1, 1 };
		g_engine.GetRenderer().SetColor(ObjectColor);
		actor->Draw(renderer);

		if (drawHitboxes)
		{
			Color hitboxColor{ 1, 0, 0, 1 };
			g_engine.GetRenderer().SetColor(hitboxColor);
			actor->DrawHitbox(renderer);
		}
	}
}

void Scene::AddActor(Actor* actor)
{
	actor-> m_scene = this;
	m_actors.push_back(actor);

}
