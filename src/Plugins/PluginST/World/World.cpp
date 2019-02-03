#include "World.h"

#include "ShSDK/ShSDK.h"

/**
 * @brief Constructor
 */
World::World(void)
: m_pbWorld(shNULL)
{
	// ...
}

/**
 * @brief Destructor
 */
World::~World(void)
{
	// ...
}

/**
 * @brief Initialize
 * @param pUser
 */
void World::Initialize(void)
{
	b2Vec2 gravity(0, -9.8);
	m_pbWorld = new b2World(gravity);

	ShUser * pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != pUser);

	m_inputManager.Initialize(pUser);

	m_playerCharacter.Initialize(m_pbWorld, &m_inputManager);
}

/**
 * @brief Release
 */
void World::Release(void)
{
	m_playerCharacter.Release();
	m_inputManager.Release();

	SH_SAFE_DELETE(m_pbWorld);
}

/**
 * @brief Update
 */
void World::Update(float dt)
{
	m_inputManager.Update();

	m_playerCharacter.Update(dt);
}

/**
 * @brief Update
 */
const PluginInputManager & World::GetInputManager(void)
{
	return m_inputManager;
}