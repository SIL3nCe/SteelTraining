#pragma once

#include <ShSDK/ShSDK.h>
#include <ShEntryPoint/ShEntryPoint.h>

#include <PluginST.h>
#include <PluginMapGeneratorFactory.h>

#include "PauseMenu.h"

class Game
{
public:
	//
	// Singleton-related
	static Game *	GetInstance			(void);

	//
	// Initialize/Release
	void			Initialize			(void);
	void			Release				(void);

	//
	// Update
	void			Update				(float dt);

	//
	// Getters/Setters
	bool			IsRequestedExit		(void) const;
	bool			IsPaused			(void) const;

	//
	// Misc
	void			TogglePause			(void);
	void			Pause				(void);
	void			UnPause				(void);

private:
	//
	// Constructor/Destructor
	explicit		Game				(void);
	virtual			~Game				(void);
public:
	//
	// Misc
	bool					m_bRequestedExit;
protected:
private:
	//
	// Singleton-related
	static Game *			s_pInstance;
	static CShIdentifier	s_idLevelTest;

	//
	// User
	ShUser *				m_pUser;

	//
	// PauseMenu
	PauseMenu				m_pauseMenu;
};