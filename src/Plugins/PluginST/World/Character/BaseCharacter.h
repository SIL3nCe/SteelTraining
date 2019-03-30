#pragma once

#include "Box2D/Box2D.h"
#include "ShSDK/ShSDK.h"
#include "../Object.h"

class ShEntity2;

class BaseCharacter : public Object
{
public:
	explicit		 BaseCharacter		(void);
	virtual			~BaseCharacter		(void);

	virtual	void	Initialize			(b2World * pWorld);
	virtual	void	Release				(void);

	virtual void	Update				(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual void	UpdateAnimations	(float dt);

	virtual EType	GetObjectType		(void) const SH_ATTRIBUTE_OVERRIDE;

protected:
	b2World * m_pWorld;

	b2Body * m_pBody;

	ShEntity2 * m_pEntity;
};
