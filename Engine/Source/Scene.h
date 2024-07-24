#pragma once
#include "Actor.h"
#include <list>
#include <vector>
#include <memory>

class Renderer;

struct Vector2;

class Scene
{
public:
	Scene() = default;

	void Update(float dt, float progressSpeed);
	void Draw(Renderer& renderer, bool drawHitboxes);

	void AddActor(std::unique_ptr<Actor> actor);
	void ClearActors() { m_actors.clear(); };
	void SetPlayer(Actor* player) { m_player = player; };
	Actor* GetPlayer() { return m_player; };

	template<typename T>
	std::unique_ptr<Actor> GetActor();

protected:
	Actor* m_player{ nullptr };
	std::list<std::unique_ptr<Actor>> m_actors;
	std::vector<std::vector<Vector2>> levelActors;

};

template<typename T>
std::unique_ptr<Actor> Scene::GetActor()
{
	for (auto& actor : m_actors)
	{
		std::unique_ptr<Actor> result = dynamic_cast<std::unique_ptr<Actor>>(actor);
		if (result) return result;
	}

	return nullptr;
}