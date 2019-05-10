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
	// Load level
	if (!ShLevel::Load(s_idLevelTest))
	{
		SH_ASSERT_ALWAYS();
		return;
	}

	//
	// Start Plugin
	GetPluginST()->OnPlayStart(s_idLevelTest);
}

void Game::Release(void)
{
	//
	// Stop Plugin
	GetPluginST()->OnPlayStop(s_idLevelTest);

	//
	// Release level
	ShLevel::Release();
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