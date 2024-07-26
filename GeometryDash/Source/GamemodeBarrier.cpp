#include "GamemodeBarrier.h"


void GamemodeBarrier::Draw(Renderer& renderer)
{
	m_model->DrawBox(renderer, m_transform, m_bgColor);
	Actor::Draw(renderer);
}