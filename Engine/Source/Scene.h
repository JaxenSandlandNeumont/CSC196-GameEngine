#pragma once
#include <list>
#include <vector>

class Renderer;
class Actor;
struct Vector2;

class Scene
{
public:
	Scene() = default;

	void Update(float dt);
	void Draw(Renderer& renderer);

	void AddActor(Actor* actor);
	void SetPlayer(Actor* actor) { m_player = actor; };

	template<typename T>
	T* GetActor();

protected:
	Actor* m_player;
	std::list <Actor*> m_actors;
	std::vector<std::vector<Vector2>> levelActors;

};

template<typename T>
T* Scene::GetActor()
{
	for (Actor* actor : m_actors)
	{
		T* result = dynamic_cast<T*>(actor);
		if (result) return result;
	}

	return nullptr;
}