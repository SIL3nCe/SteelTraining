#pragma once

#include "Box2D/Box2D.h"
#include "ShSDK/ShSDK.h"
#include "../Object.h"

class ObjectWall : public Object
{
public:
	explicit		 ObjectWall			(void);
	virtual			~ObjectWall			(void);

	virtual	void	Initialize			(void);
	virtual	void	Release				(void);

	virtual void	Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

	virtual EType	GetObjectType		(void) const SH_ATTRIBUTE_OVERRIDE;

protected:
	b2Body * m_pBody;
};
