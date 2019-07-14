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

	b2CircleShape circleShape;
	circleShape.m_radius = 20.0f * SH_TO_B2;

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &circleShape; // Circle shape to avoid ghost collisions
	boxFixtureDef.density = 1.0f;
	m_pBody->CreateFixture(&boxFixtureDef);

	m_pBody->SetUserData(this);

	//
	// Sprites
	m_aSpriteList.SetCount(animation_state_max);

	char szDirection[32];
	char szFinalSpriteIdentifier[128];

	for (int i = 0; i < animation_state_max; ++i)
	{
		switch ((EAnimationState)i)
		{
			case animation_walk_top:sprintf(szDirection, "top"); break;
			case animation_walk_bottom:sprintf(szDirection, "bottom"); break;
			case animation_walk_right:sprintf(szDirection, "right"); break;
			case animation_walk_left:sprintf(szDirection, "left"); break;
			case animation_idle:sprintf(szDirection, "idle"); break;
			default: SH_ASSERT_ALWAYS();
		}

		int id = 1;

		while (1)
		{
			sprintf(szFinalSpriteIdentifier, "player_%s_%02d", szDirection, id++);
			if (!ShSprite::Exists(CShIdentifier("game"), CShIdentifier(szFinalSpriteIdentifier)))
				break;
			ShSprite * pSprite = ShSprite::Find(CShIdentifier("game"), CShIdentifier(szFinalSpriteIdentifier));
			m_aSpriteList[i].Add(pSprite);
		}
	}

	SH_ASSERT(shNULL != m_aSpriteList[m_eCurrentAnimState][0])

	m_pEntity = ShEntity2::Create(levelIdentifier, GID(NULL), CShIdentifier("layer_default"), m_aSpriteList[m_eCurrentAnimState][0], CShVector3(200.0f, -200.0f, 10.0f), CShEulerAngles::ZERO, CShVector3::AXIS_ALL);
}

/**
 * @brief Release
 */
void PlayerCharacter::Release(void)
{
	BaseCharacter::Release();

	m_pInputManager = shNULL;
}

/**
 * @brief Update
 */
void PlayerCharacter::Update(float dt)
{
	BaseCharacter::Update(dt);

	b2Vec2 vImpulse(0.0f, 0.0f);
	
	EAnimationState eNewState = animation_idle;

	if (m_pInputManager->IsGoingLeft())
	{
		vImpulse.x = -1.0f;
		eNewState = animation_walk_left;
	}
	else if (m_pInputManager->IsGoingRight())
	{
		vImpulse.x = 1.0f;
		eNewState = animation_walk_right;
	}
	
	if (m_pInputManager->IsGoingUp())
	{
		vImpulse.y = 1.0f;
		eNewState = animation_walk_top;
	}
	else if (m_pInputManager->IsGoingDown())
	{
		vImpulse.y = -1.0f;
		eNewState = animation_walk_bottom;
	}

	vImpulse.Normalize();
	vImpulse *= 5.0f;
	m_pBody->SetLinearVelocity(vImpulse);

	SetState(eNewState);

	if (m_pInputManager->IsShooting())
	{
		Shoot();
	}
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
EObjectType PlayerCharacter::GetObjectType(void) const
{
	return EObjectType::player;
}

/**
 * @brief PlayerCharacter::Die
 */
void PlayerCharacter::Die(void)
{
	m_pBody->SetTransform(ShineToB2(CShVector2(100.f, -100.f)), 0.f);
	m_iLifePoints = m_iMaxLifePoints;
}
