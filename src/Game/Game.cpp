#include "Game.h"

/*static*/ Game * Game::m_pInstance = shNULL;

/*static*/ Game * Game::GetInstance(void)
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
	m_bInitialized = ShLevel::Load(idLevel);
	if (!m_bInitialized)
	{
		SH_ASSERT_ALWAYS();
	}
}

void Game::Release(void)
{
	m_bInitialized = false;

	//
	// Release level
	ShLevel::Release();
}

void Game::Update(float dt)
{
	// ...
}

bool Game::IsInitialized(void) const
{
	return m_bInitialized;
}

/*explicit*/ Game::Game(void)
: m_bInitialized(false)
{
	// ...
}

/*virtual*/ Game::~Game(void)
{
	// ...
}