#pragma once

#include "BaseCharacter.h"

class PluginInputManager;
class CShIdentifier;

class PlayerCharacter : public BaseCharacter
{
public:
	explicit	 PlayerCharacter	(void);
	virtual		~PlayerCharacter	(void);

	void			Initialize		(const CShIdentifier & levelIdentifier, b2World * pWorld, PluginInputManager * pInputManager);
	void			Release			(void);

	virtual void	Update			(float dt) override;
	virtual void	UpdateAnimations(float dt) override;

private:
	PluginInputManager *	m_pInputManager;
};
