#pragma once

#include "ShSDK/ShSDK.h"
#include "../Object.h"

enum class EProjectileType
{
	classic,

	max
};

enum class EProjectileTrajectory
{
	linear,

	max
};

class b2World;
class b2Body;

class Projectile : public Object
{
public:

	//
	// Constructor / Destructor
								Projectile			(void);
	virtual						~Projectile			(void);

	void						Initialize			(b2World * pWorld, Projectile * pNext, const CShIdentifier & levelIdentifier);
	void						Release				(void);

	void						LaunchProjectile	(EObjectType eObjectType, EProjectileType eType, EProjectileTrajectory eTrajectory, const CShVector2 & vStart, const CShVector2 & vDirection);

	//
	// Update
	virtual void				Update				(float dt) SH_ATTRIBUTE_OVERRIDE;

	void						OnHit				(Object * pHitObject);

	//
	// Getters
	virtual EObjectType			GetObjectType		(void) const SH_ATTRIBUTE_OVERRIDE;

	virtual EProjectileType		GetProjectileType	(void) const;

	void						SetNextProjectile	(Projectile * pNext);
	Projectile *				GetNextProjectile	(void);

protected:
	Projectile * m_pNextProjectile;

	CShIdentifier m_levelIdentifier;

	b2World * m_pWorld;
	b2Body * m_pBody;

	ShEntity2 * m_pEntity;

	EProjectileType m_eType;
	EProjectileTrajectory m_eTrajectory;

	bool m_bDiscard;
};
