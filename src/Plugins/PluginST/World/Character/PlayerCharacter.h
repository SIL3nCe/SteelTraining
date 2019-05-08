#pragma once

#include "BaseCharacter.h"

class PluginInputManager;
class CShIdentifier;

class PlayerCharacter : public BaseCharacter
{
public:
	explicit			 PlayerCharacter	(void);
	virtual				~PlayerCharacter	(void);

	void				Initialize			(const CShIdentifier & levelIdentifier, b2World * pB2World, World * pSTWorld, PluginInputManager * pInputManager);
	void				Release				(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void		Update				(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual void		UpdateAnimations	(float dt) SH_ATTRIBUTE_OVERRIDE;

	virtual EType		GetObjectType		(void) const SH_ATTRIBUTE_OVERRIDE;

private:
	PluginInputManager *	m_pInputManager;
};
