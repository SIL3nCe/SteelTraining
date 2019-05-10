//--------------------------------------------------------------------------------------------------
/// GameStateManager.cpp
//--------------------------------------------------------------------------------------------------

#include "GameStateManager.h"

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
GameStateManager * GameStateManager::GetInstance(void)
{
	static GameStateManager * pInstance = shNULL;
	if (shNULL == pInstance)
	{
		pInstance = new GameStateManager();
	}

	return pInstance;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateManager::Initialize(void)
{
	//
	// Initialize Stack
	m_aStackGameState.Resize(GAME_STATE_STACK_COUNT);

	//
	// Assigns GameState to GameStateArray
	m_aGameState[e_game_state_title_menu]			= &m_gameStateTitleMenu;
	m_aGameState[e_game_state_title_menu_settings]	= &m_gameStateTitleMenuSettings;
	m_aGameState[e_game_state_game]					= &m_gameStateGame;

	//
	// Initialize all GameStates
	for (int iGameStateIndex = 0; iGameStateIndex < GameStateManager::e_game_state_max; ++iGameStateIndex)
	{
		m_aGameState[iGameStateIndex]->Initialize();
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateManager::Release(void)
{
	int iGameStateCount = m_aStackGameState.GetElementsCount();
	for (int iGameStateIndex = 0; iGameStateIndex < iGameStateCount; ++iGameStateIndex)
	{
		m_aStackGameState.GetElement(iGameStateIndex)->Release();
	}
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateManager::Update(float dt)
{
	m_aStackGameState.GetTop()->Update(dt);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateManager::Push(EGameState eGameState)
{
	//
	// Deactivate current GameState
	if (!m_aStackGameState.IsEmpty())
	{
		m_aStackGameState.GetTop()->Deactivate();
	}

	//
	// Push next GameState
	m_aStackGameState.Push(m_aGameState[eGameState]);

	//
	// Activate new current GameState
	m_aStackGameState.GetTop()->Activate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void GameStateManager::Pop(void)
{
	//
	// Pop current GameState
	GameState * pGameState = shNULL;
	m_aStackGameState.Pop(pGameState);

	//
	// Deactivate old GameState
	pGameState->Deactivate();

	//
	// Activate new GameState
	m_aStackGameState.GetTop()->Activate();
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameStateManager::GameStateManager(void)
: m_aStackGameState()
// m_aGameState
, m_gameStateTitleMenu()
, m_gameStateTitleMenuSettings()
, m_gameStateGame()
{
	// ...
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameStateManager::~GameStateManager(void)
{
	// ...
}