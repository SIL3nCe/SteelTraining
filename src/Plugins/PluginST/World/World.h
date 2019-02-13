#pragma once

#include "InputManager.h"
#include "Character/PlayerCharacter.h"

#include "ShSDK/ShSDK.h"

class World
{
public:

	explicit					 World			(void);
	virtual						~World			(void);

	void						Initialize		(const CShIdentifier & levelIdentifier);
	void						Release			(void);

	void						Update			(float dt);

	const PluginInputManager & 	GetInputManager	(void);

private:
	
	CShIdentifier		m_levelIdentifier;

	b2World *			m_pbWorld;

	PluginInputManager	m_inputManager;

	PlayerCharacter		m_playerCharacter;
};

