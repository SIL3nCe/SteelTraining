#pragma once

#include <ShSDK/ShSDK.h>

#include "GameState.h"
#include "GameStateTitleMenu.h"
#include "GameStateTitleMenuSettings.h"
#include "GameStateGame.h"

#define GAME_STATE_STACK_COUNT 32

class GameStateManager
{
public:
	enum EGameState
	{
		e_game_state_title_menu				= 0,
		e_game_state_title_menu_settings	= 1,
		e_game_state_game					= 2,

		e_game_state_max					= e_game_state_game + 1,
	};

	//
	// Singleton-related
	static GameStateManager *	GetInstance					(void);

	//
	// Initialize/Release
	void						Initialize					(void);
	void						Release						(void);

	//
	// Update
	void						Update						(float dt);

	//
	// Stack-related
	void						Push						(EGameState eGameState);
	void						Pop							(void);

protected:
private:
	//
	// Constructor/Destructor
	explicit					GameStateManager			(void);
	virtual						~GameStateManager			(void);

public:
protected:
private:
	//
	// Stack
	CShStack<GameState*>			m_aStackGameState;

	//
	// GameStates
	GameState *						m_aGameState[e_game_state_max];
	GameStateTitleMenu				m_gameStateTitleMenu;
	GameStateTitleMenuSettings		m_gameStateTitleMenuSettings;
	GameStateGame					m_gameStateGame;
};