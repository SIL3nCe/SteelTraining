#pragma once

#include "Box2D/Box2D.h"
#include "ShSDK/ShSDK.h"
#include "../Object.h"

#define WALL_WIDTH 100.0f
#define WALL_HEIGHT 100.0f

// ObjectWall is a collection of neighbor wall entity used to generate collisions and store entities for release
class ObjectWall : public Object
{
public:
	explicit		 ObjectWall			(void);
	virtual			~ObjectWall			(void);

	virtual	void	Initialize			(ShEntity2 * pEntity);
	virtual	void	Release				(void);

	virtual void	Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

	virtual EType	GetObjectType		(void) const SH_ATTRIBUTE_OVERRIDE;

	bool			AddWall				(ShEntity2 * pEntity);
	void			GeneratePhysic		(b2World * pB2World);

protected:
	b2World * m_pWorld;
	b2Body * m_pBody;

	CShArray<ShEntity2 *> m_aEntityList;
};
