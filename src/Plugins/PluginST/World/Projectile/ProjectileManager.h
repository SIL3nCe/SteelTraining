#pragma once

#include "ShSDK\ShSDK.h"
#include "Projectile.h"

class ProjectileManager
{
public:
	virtual							~ProjectileManager	(void);

	static ProjectileManager *		GetInstance			(void);

	void							Update				(float dt);

	void							CreateProjectile	(Projectile::EProjectileType eType, Projectile::EProjectileTrajectory eTrajectory, const CShVector2 & vStart, const CShVector2 & vDirection);

private:

	explicit						ProjectileManager	(void);
};
