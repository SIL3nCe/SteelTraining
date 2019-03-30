#include "EnemyCharacter.h"

/**
 * @brief EnemyCharacter::EnemyCharacter
 */
EnemyCharacter::EnemyCharacter(void)
: BaseCharacter ()
{
}
/**
 * @brief EnemyCharacter::~EnemyCharacter
 */
EnemyCharacter::~EnemyCharacter(void)
{
}

/**
 * @brief EnemyCharacter::Initialize
 * @param pWorld
 */
void EnemyCharacter::Initialize(b2World *pWorld)
{
	BaseCharacter::Initialize(pWorld);
}

/**
 * @brief EnemyCharacter::Release
 */
void EnemyCharacter::Release(void)
{
	BaseCharacter::Release();
}

/**
 * @brief EnemyCharacter::Update
 * @param dt
 */
void EnemyCharacter::Update(float dt)
{
	BaseCharacter::Update(dt);
}

/**
 * @brief EnemyCharacter::UpdateAnimations
 * @param dt
 */
void EnemyCharacter::UpdateAnimations(float dt)
{
	BaseCharacter::UpdateAnimations(dt);
}
