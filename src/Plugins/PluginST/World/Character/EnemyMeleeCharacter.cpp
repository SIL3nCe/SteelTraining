#include "EnemyMeleeCharacter.h"
#include "../World.h"

/**
 * @brief EnemyMeleeCharacter::EnemyMeleeCharacter
 */
EnemyMeleeCharacter::EnemyMeleeCharacter(void)
	: EnemyCharacter ()
	, m_vLastPlayerPosition()
{
}
/**
 * @brief EnemyMeleeCharacter::~EnemyMeleeCharacter
 */
EnemyMeleeCharacter::~EnemyMeleeCharacter(void)
{
}

/**
 * @brief EnemyMeleeCharacter::Initialize
 * @param pWorld
 */
void EnemyMeleeCharacter::Initialize(b2World * pB2World, World * pSTWorld)
{
	EnemyCharacter::Initialize(pB2World, pSTWorld);
}

/**
 * @brief EnemyMeleeCharacter::Release
 */
void EnemyMeleeCharacter::Release(void)
{
	EnemyCharacter::Release();
}

/**
 * @brief EnemyMeleeCharacter::Update
 * @param dt
 */
void EnemyMeleeCharacter::Update(float dt)
{
	EnemyCharacter::Update(dt);
	switch (m_eCurrentState)
	{
		case e_state_idle:
		{
			if (m_pWorld->GetPlayerCharacter().GetEntityLocation().Distance(GetEntityLocation()) < 100.f)
			{
				m_eCurrentState = e_state_attacking;
			}
			else
			{
				break;
			}
		}
		case e_state_attacking:
		{
			if (m_pWorld->GetPlayerCharacter().GetEntityLocation().Distance(GetEntityLocation()) > 300.f)
			{
				m_eCurrentState = e_state_idle;
			}
			else
			{
				CShVector3 vDirection = m_pWorld->GetPlayerCharacter().GetEntityLocation() - GetEntityLocation();
				vDirection.Normalize();
				b2Vec2 vVelocity(vDirection.m_x * 50.f, vDirection.m_y * 50.f);
				m_pBody->SetLinearVelocity(vVelocity);
			}
			break;
		}
		default:
		{
			break;
		}
	}
}

/**
 * @brief EnemyMeleeCharacter::UpdateAnimations
 * @param dt
 */
void EnemyMeleeCharacter::UpdateAnimations(float dt)
{
	EnemyCharacter::UpdateAnimations(dt);
}
