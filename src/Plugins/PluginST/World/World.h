#pragma once

#include "InputManager.h"
#include "Character/PlayerCharacter.h"

class World
{
public:

	explicit					 World			(void);
	virtual						~World			(void);

	void						Initialize		(void);
	void						Release			(void);

	void						Update			(float dt);

	const PluginInputManager & 	GetInputManager	(void);

private:

	b2World *			m_pbWorld;

	PluginInputManager	m_inputManager;

	PlayerCharacter		m_playerCharacter;
};

