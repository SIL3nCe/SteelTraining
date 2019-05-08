#include "BaseCharacter.h"
#include "../World.h"

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
	bodyDef.position.Set(200 * SH_TO_B2, 200 * SH_TO_B2);
	bodyDef.angle = 0;

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
}

/**
 * @brief Update
 */
void BaseCharacter::Update(float dt)
{
	if (m_iInvulnerabilityTime > 0)
	{
		m_iInvulnerabilityTime -= static_cast<int>(dt*1000.f);
	}
}

/**
 * @brief UpdateAnimations
 */
void BaseCharacter::UpdateAnimations(float dt)
{
	SH_UNUSED(dt);
	b2Vec2 bodyPos = m_pBody->GetPosition();
<<<<<<< Updated upstream
	ShEntity2::SetRelativePosition2(m_pEntity, World::B2ToShine(bodyPos));
	ShEntity2::SetColor(m_pEntity, m_iInvulnerabilityTime <=0 ? CShRGBAf_WHITE : CShRGBAf(1.f, 1.f,1.f, 1.f - shMax(m_iInvulnerabilityTime/1000.f, .2f)));
=======
	ShEntity2::SetRelativePosition2(m_pEntity, B2ToShine(bodyPos));
>>>>>>> Stashed changes
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
	}
}

/**
 * @brief GetObjectType
 */
Object::EType BaseCharacter::GetObjectType(void) const
{
	return EType::character;
}
