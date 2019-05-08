#include "EnemyCharacter.h"

/**
 * @brief EnemyCharacter::EnemyCharacter
 */
EnemyCharacter::EnemyCharacter(void)
: BaseCharacter ()
, m_eCurrentState(e_state_idle)
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
void EnemyCharacter::Initialize(b2World * pB2World, World * pSTWorld)
{
	BaseCharacter::Initialize(pB2World, pSTWorld);
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
