#include "InputManager.h"

#include "ShSDK/ShSDK.h"

/**
 * @brief Constructor
 */
PluginInputManager::PluginInputManager(void)
: m_pUser(shNULL)
, m_bUp(false)
, m_bDown(false)
, m_bLeft(false)
, m_bRight(false)
, m_bShooting(false)
{
	// ...
}

/**
 * @brief Destructor
 */
PluginInputManager::~PluginInputManager(void)
{
	// ...
}

/**
 * @brief Initialize
 * @param pUser
 */
void PluginInputManager::Initialize(ShUser * pUser)
{
	SH_ASSERT(shNULL != pUser);
	m_pUser = pUser;
}

/**
 * @brief Release
 */
void PluginInputManager::Release(void)
{
	// ...
}

/**
 * @brief Inputs::Update
 */
void PluginInputManager::Update(void)
{
	if (shNULL != m_pUser)
	{
		m_bUp = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("up"));
		m_bDown = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("down"));
		m_bLeft = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("left"));
		m_bRight = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("right"));

		m_bShooting = ShUser::HasTriggeredAction(m_pUser, CShIdentifier("shoot"));
	}
}

bool PluginInputManager::IsGoingUp(void)
{
	return m_bUp;
}

bool PluginInputManager::IsGoingDown(void)
{
	return m_bDown;
}

bool PluginInputManager::IsGoingLeft(void)
{
	return m_bLeft;
}

bool PluginInputManager::IsGoingRight(void)
{
	return m_bRight;
}

bool PluginInputManager::IsShooting(void)
{
	return m_bShooting;
}
