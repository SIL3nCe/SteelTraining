#include "ObjectWall.h"
#include "../World.h"

/**
 * @brief Constructor
 */
ObjectWall::ObjectWall(void)
: Object()
, m_pWorld(shNULL)
, m_pBody(shNULL)
, m_pEntity(shNULL)
{
	// ...
}

/**
 * @brief Destructor
 */
ObjectWall::~ObjectWall(void)
{
	// ...
}

/**
 * @brief Initialize
 * @param pUser
 */
void ObjectWall::Initialize(ShEntity2 * pEntity, b2World * pB2World)
{
	m_pEntity = pEntity;

	const b2Vec2 & vBodyLoc = ShineToB2(ShEntity2::GetPosition2(pEntity));

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(vBodyLoc.x, vBodyLoc.y);
	bodyDef.angle = 0; // Handle ?

	m_pBody = pB2World->CreateBody(&bodyDef);
	SH_ASSERT(shNULL != m_pBody)
	
	b2PolygonShape boxShape;
	boxShape.SetAsBox(WALL_WIDTH * 0.5f * SH_TO_B2, WALL_HEIGHT * 0.5f * SH_TO_B2);

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	m_pBody->CreateFixture(&boxFixtureDef);

	m_pBody->SetUserData(this);
}

/**
 * @brief Release
 */
void ObjectWall::Release(void)
{
	m_pBody = shNULL;
}

/**
 * @brief Update
 */
void ObjectWall::Update(float dt)
{
}

/**
 * @brief GetObjectType
 */
EObjectType ObjectWall::GetObjectType(void) const
{
	return EObjectType::wall;
}
