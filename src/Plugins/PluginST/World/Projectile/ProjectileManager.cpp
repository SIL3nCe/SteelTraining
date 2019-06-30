#include "ProjectileManager.h"

/**
 * @brief Constructor
 */
ProjectileManager::ProjectileManager(void)
{
	// ...
}

/**
 * @brief Destructor
 */
ProjectileManager::~ProjectileManager(void)
{
	// ...
}

/**
 * @brief GetInstance
 */
ProjectileManager * ProjectileManager::GetInstance(void)
{
	static ProjectileManager * sProjectileManager = nullptr;
	if (!sProjectileManager)
	{
		sProjectileManager = new ProjectileManager();
	}

	return sProjectileManager;
}

/**
 * @brief Update
 */
void ProjectileManager::Update(float dt)
{
	//TODO update every projectile
}

/**
 * @brief CreateProjectile
 */
void ProjectileManager::CreateProjectile(Projectile::EProjectileType eType, Projectile::EProjectileTrajectory eTrajectory, const CShVector2 & vStart, const CShVector2 & vDirection)
{
	// Vitesse, valeur dégâts, type de dégâts (anti armure, élémentaire, etc), type d'impact (explose, rebondit, etc), couleur?, sprite?, taille?
	// TODO
}
