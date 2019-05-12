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

	//
	// Retrieve User
	m_pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != m_pUser)

	//
	// PauseMenu
	m_pauseMenu.Initialize();
}

void Game::Release(void)
{
	//
	// Release PauseMenu
	m_pauseMenu.Release();

	//
	// Release level
	ShLevel::Release();

	//
	// Unregister/Stop Plugin
	UnRegisterPluginST();
}

void Game::Update(float dt)
{
	//
	// Check for 'Pause'
	bool bPauseMenu = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("pause"));
	if (bPauseMenu)
	{
		TogglePause();
	}
}

bool Game::IsRequestedExit(void) const
{
	return m_bRequestedExit;
}

bool Game::IsPaused(void) const
{
	return m_pauseMenu.IsShown();
}

void Game::Pause(void)
{
	m_pauseMenu.Show();
	GetPluginST()->OnPlayPause(s_idLevelTest);
}

void Game::UnPause(void)
{
	m_pauseMenu.Hide();
	GetPluginST()->OnPlayResume(s_idLevelTest);
}

void Game::TogglePause(void)
{
	m_pauseMenu.Toggle();
	if (m_pauseMenu.IsShown())
	{
		GetPluginST()->OnPlayPause(s_idLevelTest);
	}
	else
	{
		GetPluginST()->OnPlayResume(s_idLevelTest);
	}
}

/*explicit*/ Game::Game(void)
: m_bRequestedExit(false)
, m_pUser(shNULL)
, m_pauseMenu()
{
	// ...
}

/*virtual*/ Game::~Game(void)
{
	// ...
}