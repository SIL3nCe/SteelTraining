#include "ShootFactory.h"
#include "Projectile\ProjectileManager.h"

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
	for (int i = 0; i < nbProjectile; ++i)
	{
		//TODO 

		//pManager->CreateProjectile();
	}
}
