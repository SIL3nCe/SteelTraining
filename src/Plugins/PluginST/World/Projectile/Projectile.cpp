#include "Projectile.h"
#include "../World.h"
#include "Box2D/Box2D.h"

/**
 * @brief Constructor
 */
Projectile::Projectile(void)
: m_pNextProjectile(shNULL)
, m_pWorld(shNULL)
, m_pBody(shNULL)
, m_pEntity(shNULL)
, m_eType(EProjectileType::max)
, m_eTrajectory(EProjectileTrajectory::max)
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

/**
 * @brief LaunchProjectile
 */
void Projectile::LaunchProjectile(EProjectileType eType, EProjectileTrajectory eTrajectory, const CShVector2 & vStart, const CShVector2 & vDirection)
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

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &circleShape;
	boxFixtureDef.density = 1.0f;
	m_pBody->CreateFixture(&boxFixtureDef);

	float fSpeed = 10.0f; // TODO move this as arg ?
	b2Vec2 vLinearVelocity = ShineToB2(vDirection);
	vLinearVelocity.Normalize();
	vLinearVelocity *= fSpeed;
	m_pBody->SetLinearVelocity(vLinearVelocity);

	m_pEntity = ShEntity2::Create(m_levelIdentifier, GID(NULL), CShIdentifier("layer_default"), CShIdentifier("character"), CShIdentifier("chicken_idle_left_0"), CShVector3(vStart, 2.0f), CShEulerAngles::ZERO, CShVector3(0.5f, 0.5f, 0.5f));
}

/**
 * @brief Update
 */
void Projectile::Update(float dt)
{
	if (shNULL == m_pNextProjectile)
	{
		// Update sprite
		b2Vec2 bodyPos = m_pBody->GetPosition();
		ShEntity2::SetRelativePosition2(m_pEntity, B2ToShine(bodyPos));

		// Update physic for non linear (with mouse joint) (à faire dans un update à part en pré update ?)

		// Tell projectilemanager when projectile is no more used (for free list handle) (add collision listener)
	}
}

/**
 * @brief GetObjectType
 */
Object::EObjectType Projectile::GetObjectType(void) const
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