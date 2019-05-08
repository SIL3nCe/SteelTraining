#include "PlayerCharacter.h"
#include "../InputManager.h"
#include "../World.h"

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
void PlayerCharacter::Initialize(const CShIdentifier & levelIdentifier, b2World * pB2World, World * pSTWorld, PluginInputManager * pInputManager)
{
	BaseCharacter::Initialize(pB2World, pSTWorld);

	m_pInputManager = pInputManager;
	SH_ASSERT(shNULL != m_pInputManager)

	m_pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_player_test"));
	SH_ASSERT(shNULL != m_pEntity)

	b2PolygonShape boxShape;
	boxShape.SetAsBox(64.0f * SH_TO_B2, 64.0f * SH_TO_B2);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	m_pBody->CreateFixture(&boxFixtureDef);
}

/**
 * @brief Release
 */
void PlayerCharacter::Release(void)
{
	m_pInputManager = shNULL;
}

/**
 * @brief Update
 */
void PlayerCharacter::Update(float dt)
{
	bool bLeft = m_pInputManager->IsGoingLeft();
	bool bRight = m_pInputManager->IsGoingRight();
	bool bDown = m_pInputManager->IsGoingDown();
	bool bUp = m_pInputManager->IsGoingUp();

	b2Vec2 vImpulse(0.0f, 0.0f);
	
	if (bLeft)
	{
		vImpulse.x = -1.0f;
	}
	else if (bRight)
	{
		vImpulse.x = 1.0f;
	}
	
	if (bUp)
	{
		vImpulse.y = 1.0f;
	}
	else if (bDown)
	{
		vImpulse.y = -1.0f;
	}

	vImpulse.Normalize();
	vImpulse *= 5.0f;
	m_pBody->SetLinearVelocity(vImpulse);
}

/**
 * @brief PostUpdate
 */
void PlayerCharacter::UpdateAnimations(float dt)
{
	BaseCharacter::UpdateAnimations(dt);
}

/**
 * @brief GetObjectType
 */
Object::EType PlayerCharacter::GetObjectType(void) const
{
	return EType::player;
}
