#include "ShootFactory.h"
#include "Projectile\ProjectileManager.h"

/**
 * @brief GenerateLinearShoot
 */
void ShootFactory::GenerateLinearShoot(const CShVector2 & vLocation, const CShVector2 & vDirection, int nbProjectile)
{
	ProjectileManager * pManager = ProjectileManager::GetInstance();
	for (int i = 0; i < nbProjectile; ++i)
	{
		//TODO 

		//pManager->CreateProjectile();
	}
}

/**
 * @brief GenerateCircularShoot
 */
void ShootFactory::GenerateCircularShoot(const CShVector2 & vLocation, int nbProjectile, float fRadius)
{
	ProjectileManager * pManager = ProjectileManager::GetInstance();
	for (int i = 0; i < nbProjectile; ++i)
	{
		//TODO 

		//pManager->CreateProjectile();
	}
}
