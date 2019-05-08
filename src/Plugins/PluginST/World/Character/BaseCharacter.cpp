#include "BaseCharacter.h"
#include "../World.h"

/**
 * @brief Constructor
 */
BaseCharacter::BaseCharacter(void)
: Object()
, m_pBody(shNULL)
, m_pEntity(shNULL)
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
	bodyDef.position.Set(0, 0);
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
	SH_UNUSED(dt);
}

/**
 * @brief UpdateAnimations
 */
void BaseCharacter::UpdateAnimations(float dt)
{
	SH_UNUSED(dt);
	b2Vec2 bodyPos = m_pBody->GetPosition();
	ShEntity2::SetRelativePosition2(m_pEntity, World::B2ToShine(bodyPos));
}

 const CShVector3 & BaseCharacter::GetEntityLocation(void) const
 {
	 return ShEntity2::GetPosition(m_pEntity);
 }

/**
 * @brief GetObjectType
 */
Object::EType BaseCharacter::GetObjectType(void) const
{
	return EType::character;
}
