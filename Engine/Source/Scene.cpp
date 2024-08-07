#include "Scene.h"
#include "Actor.h"
#include "Color.h"
#include "Engine.h"

#include <vector>
#include <memory>


void Scene::Update(float dt, float progressSpeed)
{

	//std::erase_if(m_actors, [](Actor* actor) {return actor->m_destroyed; });
	if (m_player && !m_player->m_destroyed)
	{
		m_player->Update(dt);
	}

	int playerCollisionLog = 0;

	for (auto& actor : m_actors)
	{
		actor->GetTransform().position.x -= progressSpeed * g_engine.GetTime().GetDeltaTime();
		actor->Update(dt);
		if (m_player)
		{
			playerCollisionLog += m_player->Collided(actor.get());
		}
	}

	if (m_player)
	{
		m_player->m_landed = (playerCollisionLog == 1);
	}
}

void Scene::Draw(Renderer& renderer, bool drawHitboxes)
{
	if (m_player)
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

	}




	for (auto& actor : m_actors)
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

	for (Text* text : m_allText)
	{
		text->Draw(g_engine.GetRenderer());
	}
}

void Scene::AddActor(std::unique_ptr<Actor> actor)
{
	m_actors.push_back(std::move(actor));
}

void Scene::AddText(Text* text)
{
	m_allText.push_back(text);
}
