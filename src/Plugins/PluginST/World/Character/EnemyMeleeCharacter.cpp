#include "EnemyMeleeCharacter.h"
#include "../World.h"

/**
 * @brief EnemyMeleeCharacter::EnemyMeleeCharacter
 */
EnemyMeleeCharacter::EnemyMeleeCharacter(void)
	: EnemyCharacter ()
	, m_vLastPlayerPosition()
{
	m_iTransitionTime = 1000;
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
				if (m_iTransitionTime <=0)
				{
					m_eCurrentState = e_state_wandering;
				}
				else
				{
					break;
				}
			}
		}
		case e_state_wandering:
		{
			if (player.GetEntityLocation().Distance(GetEntityLocation()) < 300.f)
			{
				m_eCurrentState = e_state_attacking;
			}
			else
			{
				m_pBody->ApplyLinearImpulseToCenter(b2Vec2((rand()/static_cast<float>(RAND_MAX)-0.5f)/50.f, (rand()/static_cast<float>(RAND_MAX)-0.5f)/50.f), true);
				b2Vec2 vVelocity(m_pBody->GetLinearVelocity());
				vVelocity.x = shMax(shMin(1.f, vVelocity.x), -1.f);
				vVelocity.y = shMax(shMin(1.f, vVelocity.y), -1.f);
				m_pBody->SetLinearVelocity(vVelocity);
				break;
			}
			break;
		}
		case e_state_attacking:
		{
			if (player.GetEntityLocation().Distance(GetEntityLocation()) > 400.f)
			{
				m_eCurrentState = e_state_idle;
				m_iTransitionTime = 1000;
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
