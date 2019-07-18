#include "Projectile.h"
#include "../World.h"
#include "Box2D/Box2D.h"
#include "ProjectileManager.h"

/**
 * @brief Constructor
 */
Projectile::Projectile(void)
: Object()
, m_pNextProjectile(shNULL)
, m_pWorld(shNULL)
, m_pBody(shNULL)
, m_pEntity(shNULL)
, m_eType(EProjectileType::max)
, m_eTrajectory(EProjectileTrajectory::max)
, m_bDiscard(false)
{
	// ...
}

/**
 * @brief Destructor
 */
Projectile::~Projectile(void)
{
	// ...
}

/**
 * @brief Initialize
 */
void Projectile::Initialize(b2World * pWorld, Projectile * pNext, const CShIdentifier & levelIdentifier)
{
	m_pWorld = pWorld;
	m_pNextProjectile = pNext;
	m_levelIdentifier = levelIdentifier;
}

void Projectile::Release(void)
{
	m_pWorld->DestroyBody(m_pBody);
	m_pBody = shNULL;

	ShEntity2::Destroy(m_pEntity); // Delete as it could be used for another projectile type
	m_pEntity = shNULL;

	m_bDiscard = false;
}

/**
 * @brief LaunchProjectile
 */
void Projectile::LaunchProjectile(EObjectType eObjectType, EProjectileType eType, EProjectileTrajectory eTrajectory, const CShVector2 & vStart, const CShVector2 & vDirection)
{
	m_eType = eType;
	m_eTrajectory = eTrajectory;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2Vec2 vStartPosition = ShineToB2(vStart);
	bodyDef.position.Set(vStartPosition.x, vStartPosition.y);
	bodyDef.angle = 0.0f;

	m_pBody = m_pWorld->CreateBody(&bodyDef);
	SH_ASSERT(shNULL != m_pBody)

	b2CircleShape circleShape;
	circleShape.m_radius = 5.0f * SH_TO_B2;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;
	fixtureDef.density = 1.0f;
	fixtureDef.filter.categoryBits = (uint16)GetObjectType();
	fixtureDef.filter.maskBits = (uint16)EObjectType::wall | (uint16)((EObjectType::player == eObjectType) ? EObjectType::character : EObjectType::player);
	m_pBody->CreateFixture(&fixtureDef);

	m_pBody->SetUserData(this);

	float fSpeed = 10.0f; // TODO move this as arg ?
	b2Vec2 vLinearVelocity = ShineToB2(vDirection);
	vLinearVelocity.Normalize();
	vLinearVelocity *= fSpeed;
	m_pBody->SetLinearVelocity(vLinearVelocity);

	m_pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("character"), CShIdentifier("chicken_idle_left_0"), CShVector3(vStart, 2.0f), CShEulerAngles::ZERO, CShVector3(0.5f, 0.5f, 0.5f));
}

/**
 * @brief OnHit
 */
void Projectile::OnHit(Object * pHitObject)
{
	SH_ASSERT(shNULL != pHitObject);

	if (EObjectType::character == pHitObject->GetObjectType())
	{
		if (BaseCharacter * pCharac = static_cast<BaseCharacter *>(pHitObject))
		{
			pCharac->TakeDamage(30); // TODO use projectile attribut for damage value
		}
	}

	// Do not release b2Body here as it's called during world steps
	m_bDiscard = true;
}

/**
 * @brief Update
 */
void Projectile::Update(float dt)
{
	if (m_pBody)
	{
		if (m_bDiscard)
		{
			ProjectileManager::GetInstance()->FreeProjectile(this);
			return;
		}

		// Update sprite
		b2Vec2 bodyPos = m_pBody->GetPosition();
		ShEntity2::SetRelativePosition2(m_pEntity, B2ToShine(bodyPos));

		// Update physic for non linear (with mouse joint) (à faire dans un update à part en pré update ?)
	}
}

/**
 * @brief GetObjectType
 */
EObjectType Projectile::GetObjectType(void) const
{
	return EObjectType::projectile;
}

/**
 * @brief GetProjectileType
 */
EProjectileType Projectile::GetProjectileType(void) const
{
	return m_eType;
}

/**
 * @brief SetNextProjectile
 */
void Projectile::SetNextProjectile(Projectile * pNext)
{
	m_pNextProjectile = pNext;
}

/**
 * @brief GetNextProjectile
 */
Projectile * Projectile::GetNextProjectile(void)
{
	return m_pNextProjectile;
}