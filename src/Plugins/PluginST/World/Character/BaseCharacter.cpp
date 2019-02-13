#include "BaseCharacter.h"

#include "ShSDK/ShSDK.h"

/**
 * @brief Constructor
 */
BaseCharacter::BaseCharacter(void)
: m_pWorld(shNULL)
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
	m_pWorld = pWorld;
	SH_ASSERT(shNULL != m_pWorld);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 0);
	bodyDef.angle = 0;

	m_pBody = m_pWorld->CreateBody(&bodyDef);
	SH_ASSERT(shNULL != m_pBody);
}

/**
 * @brief Release
 */
void BaseCharacter::Release(void)
{
	m_pWorld->DestroyBody(m_pBody);

	m_pBody = shNULL;
	m_pWorld = shNULL;
}

/**
 * @brief Inputs::Update
 */
void BaseCharacter::Update(float dt)
{
}

/**
 * @brief Inputs::UpdateAnimations
 */
void BaseCharacter::UpdateAnimations(float dt)
{
	b2Vec2 bodyPos = m_pBody->GetPosition();
	//TODO make b2Toshine method for vector with coeff
	ShEntity2::SetRelativePosition2(m_pEntity, CShVector2(bodyPos.x, bodyPos.y));
}