#include "Projectile.h"

/**
 * @brief Constructor
 */
Projectile::Projectile(void)
{
	// ...
}

/**
 * @brief Destructor
 */
Projectile::~Projectile(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void Projectile::Initialize(EProjectileType eType, EProjectileTrajectory eTrajectory)
{
	m_eType = eType;
	m_eTrajectory = eTrajectory;
}

/**
 * @brief Update
 */
void Projectile::Update(float dt)
{
}

/**
 * @brief GetProjectileType
 */
Projectile::EProjectileType Projectile::GetProjectileType(void) const
{
	return m_eType;
}
