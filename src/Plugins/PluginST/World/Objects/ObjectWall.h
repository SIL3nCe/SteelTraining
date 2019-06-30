#pragma once

#include "Box2D/Box2D.h"
#include "ShSDK/ShSDK.h"
#include "../Object.h"

#define WALL_WIDTH 100.0f
#define WALL_HEIGHT 100.0f

class ObjectWall : public Object
{
public:
	explicit			 ObjectWall			(void);
	virtual				~ObjectWall			(void);

	virtual	void		Initialize			(ShEntity2 * pEntity, b2World * pB2World);
	virtual	void		Release				(void);

	virtual void		Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

	virtual EObjectType	GetObjectType		(void) const SH_ATTRIBUTE_OVERRIDE;

protected:
	b2World * m_pWorld;
	b2Body * m_pBody;

	ShEntity2 * m_pEntity;
};
