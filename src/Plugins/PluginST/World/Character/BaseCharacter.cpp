#include "BaseCharacter.h"

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
void BaseCharacter::Initialize(b2World * pWorld)
{
	SH_ASSERT(shNULL != pWorld);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 0);
	bodyDef.angle = 0;

	m_pBody = pWorld->CreateBody(&bodyDef);
	SH_ASSERT(shNULL != m_pBody);
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
	ShEntity2::SetRelativePosition2(m_pEntity, CShVector2(bodyPos.x, bodyPos.y));
}

/**
 * @brief GetObjectType
 */
Object::EType BaseCharacter::GetObjectType(void) const
{
	return EType::character;
}
