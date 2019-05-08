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
void EnemyMeleeCharacter::Initialize(const CShIdentifier & idCharacter, const CShIdentifier & levelIdentifier, b2World * pB2World, World * pSTWorld, const CShVector2 & vPosition)
{
	EnemyCharacter::Initialize(pB2World, pSTWorld, vPosition);

	m_pEntity = ShEntity2::Create(levelIdentifier, idCharacter, GID(layer_default), CShIdentifier("character"), CShIdentifier("chicken_idle_left_0"), CShVector3(vPosition, 0.f), CShEulerAngles::ZERO, CShVector3::AXIS_ALL);
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
	PlayerCharacter & player = m_pWorld->GetPlayerCharacter();
	switch (m_eCurrentState)
	{
		case e_state_idle:
		{
			if (player.GetEntityLocation().Distance(GetEntityLocation()) < 300.f)
			{
				m_eCurrentState = e_state_attacking;
			}
			else
			{
				m_pBody->SetLinearVelocity(b2Vec2(0.f, 0.f));
				break;
			}
		}
		case e_state_attacking:
		{
			if (player.GetEntityLocation().Distance(GetEntityLocation()) > 400.f)
			{
				m_eCurrentState = e_state_idle;
			}
			else
			{
				if (player.GetEntityLocation().Distance(GetEntityLocation()) > 40.f)
				{
					CShVector3 vDirection = player.GetEntityLocation() - GetEntityLocation();
					vDirection.Normalize();
					b2Vec2 vVelocity(vDirection.m_x * 2.f, vDirection.m_y * 2.f);
					m_pBody->SetLinearVelocity(vVelocity);
				}
				else
				{
					m_pBody->SetLinearVelocity(b2Vec2(0.f, 0.f));
					player.TakeDamage(30);
				}
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
