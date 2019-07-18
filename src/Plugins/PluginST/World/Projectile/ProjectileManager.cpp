#include "ProjectileManager.h"

#include "Box2D/Box2D.h"

/**
 * @brief Constructor
 */
ProjectileManager::ProjectileManager(void)
: m_aProjectilePool()
, m_pNextUsableProjectile(shNULL)
{
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
 * @brief Initialize
 */
void ProjectileManager::Initialize(const CShIdentifier & levelIdentifier, b2World * pWorld)
{
	for (int i = 0; i < PROJECTILE_POOL_SIZE - 1; ++i)
	{
		m_aProjectilePool[i].Initialize(pWorld, &m_aProjectilePool[i + 1], levelIdentifier);
	}
	m_aProjectilePool[PROJECTILE_POOL_SIZE - 1].Initialize(pWorld, shNULL, levelIdentifier);

	m_pNextUsableProjectile = &m_aProjectilePool[0];
}

/**
 * @brief Update
 */
void ProjectileManager::Update(float dt)
{
	for (int i = 0; i < PROJECTILE_POOL_SIZE - 1; ++i)
	{
		m_aProjectilePool[i].Update(dt);
	}
}

/**
 * @brief CreateProjectile
 */
void ProjectileManager::CreateProjectile(EObjectType eObjectType, EProjectileType eType, EProjectileTrajectory eTrajectory, const CShVector2 & vStart, const CShVector2 & vDirection)
{
	if (!m_pNextUsableProjectile)
	{
		SH_TRACE("No more projectile to fire in the pool, stop spamming like an idiot.\n");
		return;
	}

	// Vitesse, valeur dégâts, type de dégâts (anti armure, élémentaire, etc), type d'impact (explose, rebondit, etc), couleur?, taille?, enum pour sprite à créer?
	// TODO Weapon class where every thing is stored ^
	// + struct for every param ?

	Projectile * pProj = m_pNextUsableProjectile;
	m_pNextUsableProjectile = pProj->GetNextProjectile();
	pProj->SetNextProjectile(shNULL);

	pProj->LaunchProjectile(eObjectType, eType, eTrajectory, vStart, vDirection);
}

void ProjectileManager::FreeProjectile(Projectile * pProjectile)
{
	SH_ASSERT(shNULL != pProjectile);

	pProjectile->Release();
	pProjectile->SetNextProjectile(m_pNextUsableProjectile);
	m_pNextUsableProjectile = pProjectile;
}
