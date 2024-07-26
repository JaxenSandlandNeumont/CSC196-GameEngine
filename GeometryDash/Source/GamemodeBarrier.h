#pragma once
#include "Actor.h"
#include "Color.h"


class GamemodeBarrier : public Actor
{
public:
	GamemodeBarrier() = default;

	GamemodeBarrier(const Transform& transform, Model* model, Color bgColor, uint8_t toGamemode) :
		Actor{ transform, model },
		m_bgColor{ bgColor },
		m_toGamemode{ toGamemode }
	{}

	void Draw(Renderer& renderer);
	uint8_t GetToGamemode() { return m_toGamemode; };

private:
	Color m_bgColor{};
	uint8_t m_toGamemode{ 1 };

};

