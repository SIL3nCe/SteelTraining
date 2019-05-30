#include "TeleportingEnemyMeleeCharacter.h"
#include "../World.h"

/**
 * @brief TeleportingEnemyMeleeCharacter::TeleportingEnemyMeleeCharacter
 */
TeleportingEnemyMeleeCharacter::TeleportingEnemyMeleeCharacter(void)
: EnemyMeleeCharacter()
, m_fTPCooldown(1000.f)
, m_fTPCooldownMax(1000.f)
, m_iTPCurrentIndex(0)
, m_aeTPDirectionsOrder()
{
}

/**
 * @brief TeleportingEnemyMeleeCharacter::~TeleportingEnemyMeleeCharacter
 */
TeleportingEnemyMeleeCharacter::~TeleportingEnemyMeleeCharacter(void)
{

}

/**
 * @brief TeleportingEnemyMeleeCharacter::Initialize
 * @param idCharacter
 * @param levelIdentifier
 * @param pB2World
 * @param pSTWorld
 * @param vPosition
 */
void TeleportingEnemyMeleeCharacter::Initialize(const CShIdentifier &idCharacter, const CShIdentifier &levelIdentifier, b2World *pB2World, World *pSTWorld, const CShVector2 &vPosition)
{
	EnemyMeleeCharacter::Initialize(idCharacter, levelIdentifier, pB2World, pSTWorld, vPosition);
	m_aeTPDirectionsOrder.Add(e_teleport_left);
	m_aeTPDirectionsOrder.Add(e_teleport_none);
	m_aeTPDirectionsOrder.Add(e_teleport_right);
	m_aeTPDirectionsOrder.Add(e_teleport_right);
	m_aeTPDirectionsOrder.Add(e_teleport_left);
	m_aeTPDirectionsOrder.Add(e_teleport_none);
	m_aeTPDirectionsOrder.Add(e_teleport_none);
	m_aeTPDirectionsOrder.Add(e_teleport_right);
	m_aeTPDirectionsOrder.Add(e_teleport_forward);
	m_aeTPDirectionsOrder.Add(e_teleport_none);
	m_aeTPDirectionsOrder.Add(e_teleport_none);
	m_aeTPDirectionsOrder.Add(e_teleport_left);
}

/**
 * @brief TeleportingEnemyMeleeCharacter::Release
 */
void TeleportingEnemyMeleeCharacter::Release(void)
{
	EnemyMeleeCharacter::Release();
}

/**
 * @brief TeleportingEnemyMeleeCharacter::Update
 * @param dt
 */
void TeleportingEnemyMeleeCharacter::Update(float dt)
{
	EnemyMeleeCharacter::Update(dt);
	m_fTPCooldown -= dt*1000.f;
	if (m_fTPCooldown <= 0.f)
	{
		m_fTPCooldown = m_fTPCooldownMax;

		PlayerCharacter & player = m_pWorld->GetPlayerCharacter();
		if (m_eCurrentState == e_state_attacking && player.GetEntityLocation().Distance(GetEntityLocation()) > 20.f)
		{
			switch (m_aeTPDirectionsOrder[m_iTPCurrentIndex])
			{
				case e_teleport_left:
				{
					b2Vec2 vPos =m_pBody->GetPosition();
					b2Vec2 vVelocity = m_pBody->GetLinearVelocity();
					vVelocity.Normalize();
					vVelocity = b2Mul(b2Rot(SHC_PI_ON_2),vVelocity);
					vVelocity.Normalize();
					vPos.x = vPos.x + vVelocity.x*100.f*SH_TO_B2;
					vPos.y = vPos.y + vVelocity.y*100.f*SH_TO_B2;
					m_pBody->SetTransform(vPos, m_pBody->GetAngle());
					break;
				}
				case e_teleport_right:
				{
					b2Vec2 vPos =m_pBody->GetPosition();
					b2Vec2 vVelocity = m_pBody->GetLinearVelocity();
					vVelocity.Normalize();
					vVelocity = b2Mul(b2Rot(-SHC_PI_ON_2),vVelocity);
					vVelocity.Normalize();
					vPos.x = vPos.x + vVelocity.x*100.f*SH_TO_B2;
					vPos.y = vPos.y + vVelocity.y*100.f*SH_TO_B2;
					m_pBody->SetTransform(vPos, m_pBody->GetAngle());
					break;
				}
				case e_teleport_forward:
				{
					b2Vec2 vPos =m_pBody->GetPosition();
					b2Vec2 vVelocity = m_pBody->GetLinearVelocity();
					vVelocity.Normalize();
					vPos.x = vPos.x + vVelocity.x*50.f*SH_TO_B2;
					vPos.y = vPos.y + vVelocity.y*50.f*SH_TO_B2;
					m_pBody->SetTransform(vPos, m_pBody->GetAngle());
					break;
				}
				case e_teleport_none:
				{
					break;
				}
				default:
				{
					SH_ASSERT_ALWAYS()
					break;
				}
			}
			m_iTPCurrentIndex = (m_iTPCurrentIndex+1)%m_aeTPDirectionsOrder.GetCount();
		}
	}

}
