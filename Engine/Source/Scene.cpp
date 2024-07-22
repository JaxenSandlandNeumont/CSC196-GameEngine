#include "Scene.h"
#include "Actor.h"
void Scene::Update(float dt)
{

	//std::erase_if(m_actors, [](Actor* actor) {return actor->m_destroyed; });

	m_player->Update(dt);

	for (Actor* actor : m_actors)
	{
		actor->Update(dt);
		m_player->Collided(actor);
	}
}

void Scene::Draw(Renderer& renderer)
{
	m_player->Draw(renderer);
	for (Actor* actor : m_actors)
	{
		actor->Draw(renderer);
	}
}

void Scene::AddActor(Actor* actor)
{
	actor-> m_scene = this;
	m_actors.push_back(actor);

}
