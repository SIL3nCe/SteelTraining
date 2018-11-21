#pragma once

#include "BaseCharacter.h"

class PluginInputManager;

class PlayerCharacter : public BaseCharacter
{
public:
	explicit	 PlayerCharacter	(void);
	virtual		~PlayerCharacter	(void);

	void		Initialize			(b2World * pWorld, PluginInputManager * pInputManager);
	void		Release				(void);

	void		Update				(float dt);

private:

	PluginInputManager *	m_pInputManager;

};
