#pragma once

#include "Box2D/Box2D.h"

class ShEntity2;

class BaseCharacter
{
public:
	explicit		 BaseCharacter		(void);
	virtual			~BaseCharacter		(void);

	virtual	void	Initialize		(b2World * pWorld);
	virtual	void	Release			(void);

	virtual void	Update			(float dt);
	virtual void	UpdateAnimations(float dt);

protected:
	b2World * m_pWorld;

	b2Body * m_pBody;

	ShEntity2 * m_pEntity;
};
