#include "BaseCharacter.h"

#include "ShSDK/ShSDK.h"

/**
 * @brief Constructor
 */
BaseCharacter::BaseCharacter(void)
: m_pbWorld(shNULL)
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
	m_pbWorld = pWorld;
	SH_ASSERT(shNULL != m_pbWorld);
}

/**
 * @brief Release
 */
void BaseCharacter::Release(void)
{
	m_pbWorld = shNULL;
}

/**
 * @brief Inputs::Update
 */
void BaseCharacter::Update(float dt)
{
}
