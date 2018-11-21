#include "PlayerCharacter.h"
#include "../InputManager.h"

#include "ShSDK/ShSDK.h"

/**
 * @brief Constructor
 */
PlayerCharacter::PlayerCharacter(void)
: BaseCharacter()
, m_pInputManager(shNULL)
{
	// ...
}

/**
 * @brief Destructor
 */
PlayerCharacter::~PlayerCharacter(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void PlayerCharacter::Initialize(b2World * pWorld, PluginInputManager * pInputManager)
{
	BaseCharacter::Initialize(pWorld);

	m_pInputManager = pInputManager;
	SH_ASSERT(shNULL != m_pInputManager);
}

/**
 * @brief Release
 */
void PlayerCharacter::Release(void)
{
	m_pInputManager = shNULL;
}

/**
 * @brief Inputs::Update
 */
void PlayerCharacter::Update(float dt)
{
	bool bLeft = m_pInputManager->IsGoingLeft();
	bool bRight = m_pInputManager->IsGoingRight();
	bool bDown = m_pInputManager->IsGoingDown();
	bool bUp = m_pInputManager->IsGoingUp();

	if (bLeft)
	{

	}
	else if (bRight)
	{

	}

	if (bDown)
	{

	}
	else if (bUp)
	{

	}
}
