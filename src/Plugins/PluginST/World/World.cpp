#include "World.h"

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
void World::Initialize(const CShIdentifier & levelIdentifier)
{
	m_levelIdentifier = levelIdentifier;

	b2Vec2 gravity(0.0f, 0.0f);
	m_pbWorld = new b2World(gravity);

	ShUser * pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != pUser);

	m_inputManager.Initialize(pUser);

	m_playerCharacter.Initialize(m_levelIdentifier, m_pbWorld, &m_inputManager);
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

	float32 timeStep = 1 / 60.0f;   // TODO timeStep should match the number of times per second it will be called

	//velocityIterations: how strongly to correct velocity
	//positionIterations: how strongly to correct position
	// ^ Making these values higher will give you a more correct simulation, at the cost of some performance

	m_pbWorld->Step(timeStep, 8, 3);

	m_playerCharacter.UpdateAnimations(dt);
}

/**
 * @brief Update
 */
const PluginInputManager & World::GetInputManager(void)
{
	return m_inputManager;
}
