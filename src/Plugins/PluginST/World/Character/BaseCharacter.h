#pragma once

#include "Box2D/Box2D.h"

class BaseCharacter
{
public:
	explicit	 BaseCharacter		(void);
	virtual		~BaseCharacter		(void);

	void		Initialize			(b2World * pWorld);
	void		Release				(void);

	void		Update				(float dt);

protected:
	b2World * m_pbWorld;
};

