#include "ShootFactory.h"
#include "Projectile/ProjectileManager.h"

/**
 * @brief GenerateLinearShoot
 */
void ShootFactory::GenerateLinearShoot(const CShVector2 & vLocation, const CShVector2 & vDirection, int nbProjectile)
{
	//TODO move the loop in manager (CreateProjectile) ?
	ProjectileManager * pManager = ProjectileManager::GetInstance();
	for (int i = 0; i < nbProjectile; ++i)
	{
		pManager->CreateProjectile(EProjectileType::classic, EProjectileTrajectory::linear, vLocation, vDirection);
	}
}

/**
 * @brief GenerateCircularShoot
 */
void ShootFactory::GenerateCircleShoot(const CShVector2 & vLocation, int nbProjectile, float fRadius)
{
	ProjectileManager * pManager = ProjectileManager::GetInstance();

	float fCurrAngle = 0.0f;
	float fDeltaAngle = 360.0f / nbProjectile;
	CShVector2 vLocationOnCircle;
	CShVector2 vDirection;
	for (int i = 0; i < nbProjectile; ++i)
	{
		// x = cx + r * cos(a)
		// y = cy + r * sin(a)
		vLocationOnCircle.m_x = vLocation.m_x + fRadius * shCosf(shDeg2Rad(fCurrAngle));
		vLocationOnCircle.m_y = vLocation.m_y + fRadius * shSinf(shDeg2Rad(fCurrAngle));

		vDirection = vLocationOnCircle - vLocation;

		pManager->CreateProjectile(EProjectileType::classic, EProjectileTrajectory::linear, vLocationOnCircle, vDirection);

		fCurrAngle += fDeltaAngle;
	}
}
