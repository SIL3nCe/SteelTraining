#include "Game.h"

Game * Game::m_pInstance = shNULL;

Game::Game(void)
{
	// ...
}

Game * Game::GetInstance(void)
{
	if (shNULL == m_pInstance)
	{
		m_pInstance = new Game();
	}

	return(m_pInstance);
}

void Game::Initialize(void)
{
	const CShIdentifier idLevel("level_test");
	if (!ShLevel::Load(idLevel))
	{
		SH_ASSERT_ALWAYS();
	}
}

void Game::Release(void)
{
	// Release level
}

void Game::Update(float dt)
{
}
