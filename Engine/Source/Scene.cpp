#include "Scene.h"
#include "Actor.h"

void Scene::Update(float dt)
{

	std::erase_if(m_actors, [](Actor* actor) {return actor->m_destroyed; });



	for (Actor* actor : m_actors)
	{
		actor->Update(dt);
	}
}

void Scene::Draw(Renderer& renderer)
{
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
