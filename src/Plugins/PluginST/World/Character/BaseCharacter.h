#pragma once

#include "Box2D/Box2D.h"
#include "ShSDK/ShSDK.h"
#include "../Object.h"

class World;

struct ShEntity2;

class BaseCharacter : public Object
{
public:
	explicit			 BaseCharacter		(void);
	virtual				~BaseCharacter		(void);

	virtual	void		Initialize			(b2World * pB2World, World * pSTWorld);
	virtual	void		Release				(void);

	virtual void		Update				(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual void		UpdateAnimations	(float dt);

	virtual EType		GetObjectType		(void) const SH_ATTRIBUTE_OVERRIDE;

	const CShVector3 &	GetEntityLocation	(void) const;

	bool				TakeDamage			(int iDamages);
protected:
	virtual void		Die					(void) = 0;
private:

public:
protected:
	b2Body *			m_pBody;

	ShEntity2 *			m_pEntity;

	World *				m_pWorld;

	int					m_iLifePoints;
	int					m_iMaxLifePoints;
	int					m_iInvulnerabilityTime;
private:
};
