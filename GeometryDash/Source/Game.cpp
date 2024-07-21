#include "Game.h"

void Game::Initialize()
{

}

void Game::Shutdown()
{
}

void Game::Update(float dt)
{

	m_scene->Update(dt);
}

void Game::Draw(Renderer& renderer)
{
	switch (m_state)
	{
	case Game::eState::Title:
	{

	}
		break;
	case Game::eState::Level1:
	{

	}
		break;
	case Game::eState::Level2:
	{

	}
		break;
	case Game::eState::Level3:
	{

	}
		break;
	default:
		break;
	}
	m_scene->Draw(renderer);
}
