#include "EnemyCharacter.h"
#include "../World.h"

/**
 * @brief EnemyCharacter::EnemyCharacter
 */
EnemyCharacter::EnemyCharacter(void)
: BaseCharacter ()
, m_eCurrentState(e_state_idle)
, m_iTransitionTime(0)
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
void EnemyCharacter::Initialize(b2World * pB2World, World * pSTWorld, const CShVector2 & vPosition)
{
	BaseCharacter::Initialize(pB2World, pSTWorld);

	m_pBody->SetTransform(ShineToB2(vPosition), 0.f);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(15.0f * SH_TO_B2, 15.0f * SH_TO_B2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 0.5;
	fixtureDef.filter.categoryBits = (uint16)GetObjectType();
	m_pBody->CreateFixture(&fixtureDef);

	m_pBody->SetUserData(this);
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
	if (m_iTransitionTime > 0)
	{
		m_iTransitionTime -= static_cast<int>(dt*1000.f);
	}
}

/**
 * @brief EnemyCharacter::UpdateAnimations
 * @param dt
 */
void EnemyCharacter::UpdateAnimations(float dt)
{
	BaseCharacter::UpdateAnimations(dt);
}

/**
 * @brief EnemyCharacter::Die
 */
void EnemyCharacter::Die(void)
{
	m_pWorld->KillEnemy(this);
}
