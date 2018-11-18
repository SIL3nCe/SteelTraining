#include "Game.h"

Game * Game::m_pInstance = shNULL;

Game::Game(void)
{

}

Game * Game::GetInstance(void)
{
	if (shNULL == m_pInstance)
	{
		m_pInstance = new Game();
	}

	return(m_pInstance);
}

void Game::Initialize()
{
	if (!ShLevel::Load(CShIdentifier("level_test")))
	{
		SH_ASSERT_ALWAYS();
	}

}

void Game::Release()
{

}

void Game::Update(float dt)
{

}