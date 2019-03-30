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
void PlayerCharacter::Initialize(const CShIdentifier & levelIdentifier, b2World * pWorld, PluginInputManager * pInputManager)
{
	BaseCharacter::Initialize(pWorld);

	m_pInputManager = pInputManager;
	SH_ASSERT(shNULL != m_pInputManager);

	m_pEntity = ShEntity2::Find(levelIdentifier, CShIdentifier("sprite_player_test"));
	SH_ASSERT(shNULL != m_pEntity);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(10, 10);

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
 * @brief Inputs::Update
 */
void PlayerCharacter::Update(float dt)
{
	bool bLeft = m_pInputManager->IsGoingLeft();
	bool bRight = m_pInputManager->IsGoingRight();
	bool bDown = m_pInputManager->IsGoingDown();
	bool bUp = m_pInputManager->IsGoingUp();

	b2Vec2 impulse(0.0f, 0.0f);

	if (bLeft)
	{
		impulse.x = -50.0f;
	}
	else if (bRight)
	{
		impulse.x = 50.0f;
	}
	
	if (bDown)
	{
		impulse.y = -50.0f;
	}
	else if (bUp)
	{
		impulse.y = 50.0f;
	}
	
	if (bLeft || bRight || bDown || bUp)
	{
		m_pBody->ApplyLinearImpulse(impulse, m_pBody->GetWorldCenter(), true);
	}
	else
	{
		m_pBody->SetLinearVelocity(impulse);
	}
}

/**
 * @brief Inputs::PostUpdate
 */
void PlayerCharacter::UpdateAnimations(float dt)
{
	// rotate for test
	//CShEulerAngles angle = ShEntity2::GetRelativeRotation(m_pEntity);
	//angle.m_z += 10.0f * dt;
	//ShEntity2::SetRelativeRotation(m_pEntity, angle);

	BaseCharacter::UpdateAnimations(dt);
}

/**
 * @brief Inputs::GetObjectType
 */
Object::EType PlayerCharacter::GetObjectType(void) const
{
	return EType::player;
}
