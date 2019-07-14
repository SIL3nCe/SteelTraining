#pragma once

#include "Box2D/Box2D.h"

class ContactListener : public b2ContactListener
{
public:
	explicit			ContactListener		(void);
	virtual				~ContactListener	(void);
	
	virtual void		BeginContact		(b2Contact* contact) override;
	virtual void		EndContact			(b2Contact* contact) override;
};
