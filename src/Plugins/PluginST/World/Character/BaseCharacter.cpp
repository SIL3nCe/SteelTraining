#include "BaseCharacter.h"
#include "Box2D/Box2D.h"
#include "../World.h"
#include "../ShootFactory.h"

/**
 * @brief Constructor
 */
BaseCharacter::BaseCharacter(void)
: Object()
, m_pBody(shNULL)
, m_pEntity(shNULL)
, m_pWorld(shNULL)
, m_iLifePoints(100)
, m_iMaxLifePoints(100)
, m_iInvulnerabilityTime(0)
, m_animCpt(0)
, m_eCurrentAnimState(animation_idle)
, m_fAnimationDt(0.0f)
, m_fAnimationSpeed(0.5f)
{
	// ...
}

/**
 * @brief Destructor
 */
BaseCharacter::~BaseCharacter(void)
{
	// ...
}

/**
 * @brief Initialize
 * @param pUser
 */
void BaseCharacter::Initialize(b2World * pB2World, World * pSTWorld)
{
	SH_ASSERT(shNULL != pB2World && shNULL != pSTWorld)

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(200 * SH_TO_B2, -200 * SH_TO_B2);
	bodyDef.angle = 0.0f;
	bodyDef.fixedRotation = true;

	m_pBody = pB2World->CreateBody(&bodyDef);
	SH_ASSERT(shNULL != m_pBody)

	m_pWorld = pSTWorld;
}

/**
 * @brief Release
 */
void BaseCharacter::Release(void)
{
	m_pBody->GetWorld()->DestroyBody(m_pBody);
	m_pBody = shNULL;

	m_aSpriteList.Deallocate();

	ShEntity2::Destroy(m_pEntity);
}

/**
 * @brief Update
 */
void BaseCharacter::Update(float dt)
{
	if (m_iInvulnerabilityTime > 0)
	{
		m_iInvulnerabilityTime -= static_cast<int>(dt * 1000.0f);
	}
}

/**
 * @brief UpdateAnimations
 */
void BaseCharacter::UpdateAnimations(float dt)
{
	m_fAnimationDt += dt;

	b2Vec2 bodyPos = m_pBody->GetPosition();
	ShEntity2::SetRelativePosition2(m_pEntity, B2ToShine(bodyPos));

	if (m_fAnimationSpeed < m_fAnimationDt)
	{
		m_animCpt = (m_animCpt + 1) % m_aSpriteList[m_eCurrentAnimState].GetCount();
		ShEntity2::SetSprite(m_pEntity, m_aSpriteList[m_eCurrentAnimState][m_animCpt]);
		m_fAnimationDt = 0.0f;
	}

	ShEntity2::SetColor(m_pEntity, m_iInvulnerabilityTime <= 0 ? CShRGBAf_WHITE : CShRGBAf(1.0f, 1.0f, 1.0f, 1.0f - shMax(m_iInvulnerabilityTime / 1000.0f, 0.2f)));
}

/**
  * @brief BaseCharacter::GetEntityLocation
  * @return
  */
const CShVector3 & BaseCharacter::GetEntityLocation(void) const
{
	return ShEntity2::GetPosition(m_pEntity);
}

 /**
  * @brief BaseCharacter::TakeDamage
  * @param iDamages
  * @return
  */
bool BaseCharacter::TakeDamage(int iDamages)
{
	if (m_iInvulnerabilityTime <= 0)
	{
		m_iLifePoints -= iDamages;
		m_iInvulnerabilityTime = 1000;
		if (m_iLifePoints <= 0)
		{
			Die();
		}
		return true;
	}
	return false;
}

void BaseCharacter::SetState(EAnimationState eState)
{
	if (eState == m_eCurrentAnimState)
		return;

	//switch (m_eCurrentState)
	//{ // Leaving state
	//
	//}

	m_eCurrentAnimState = eState;
	m_animCpt = 0;
	m_fAnimationDt = 0.0f;
	ShEntity2::SetSprite(m_pEntity, m_aSpriteList[m_eCurrentAnimState][m_animCpt]);

	//switch (m_eCurrentAnimState)
	//{ // Entering state
	//
	//}
}

/**
 * @brief Shoot - TODO Add ShootPreset enum as parameter
 */
void BaseCharacter::Shoot(void)
{
	CShVector2 vStartLocation = ShEntity2::GetPosition2(m_pEntity);

	//
	// Shoot ahead
	//TODO use an anchor on sprite with a point (make a prefab?) as starting location
	CShVector2 vDirection(0.0f, 0.0f);
	switch (m_eCurrentAnimState)
	{
		case animation_walk_top:	vDirection.m_y = 20.0f; break;
		case animation_walk_bottom:	vDirection.m_y = -20.0f; break;
		case animation_walk_right:	vDirection.m_x = 20.0f; break;
		case animation_walk_left:	vDirection.m_x = -20.0f; break;
		default: vDirection.m_x = 20.0f;
	}

	//ShootFactory::GenerateLinearShoot(GetObjectType(), vStartLocation + vDirection, vDirection, 1);

	//
	// Circular shoot from pos
	ShootFactory::GenerateCircleShoot(GetObjectType(), vStartLocation, 12, 30.0f);
}

/**
 * @brief GetObjectType
 */
EObjectType BaseCharacter::GetObjectType(void) const
{
	return EObjectType::character;
}
