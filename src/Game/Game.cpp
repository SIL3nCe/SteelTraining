#include "Game.h"

#include "PluginFactory.h"

/*static*/ Game * Game::s_pInstance = shNULL;
/*static*/ CShIdentifier Game::s_idLevelTest("level_test");

/*static*/ Game * Game::GetInstance(void)
{
	if (shNULL == s_pInstance)
	{
		s_pInstance = new Game();
	}

	return s_pInstance;
}

void Game::Initialize(void)
{
	//
	// Register/Start Plugin
	RegisterPluginST();

	//
	// Load level
	if (!ShLevel::Load(s_idLevelTest))
	{
		SH_ASSERT_ALWAYS();
		return;
	}
}

void Game::Release(void)
{
	//
	// Release level
	ShLevel::Release();

	//
	// Unregister/Stop Plugin
	UnRegisterPluginST();
}

void Game::Update(float dt)
{
	// ...
}

bool Game::IsRequestedExit(void) const
{
	return m_bRequestedExit;
}

/*explicit*/ Game::Game(void)
: m_bRequestedExit(false)
{
	// ...
}

/*virtual*/ Game::~Game(void)
{
	// ...
}