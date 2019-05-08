#include "ObjectWall.h"
#include "../World.h"

/**
 * @brief Constructor
 */
ObjectWall::ObjectWall(void)
: Object()
, m_pWorld(shNULL)
, m_pBody(shNULL)
, m_aEntityList()
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
void ObjectWall::Initialize(ShEntity2 * pEntity)
{
	m_aEntityList.Add(pEntity);
}

/**
 * @brief Release
 */
void ObjectWall::Release(void)
{
	m_pBody = shNULL;
}

/**
 * @brief AddWall
 * Check if pEntity is a neighbor of its entities, keep it when it is.
 */
bool ObjectWall::AddWall(ShEntity2 * pEntity)
{
	int nEntityCount = m_aEntityList.GetCount();
	for (int i = 0; i < nEntityCount; ++i)
	{
		const CShVector2 & vWallLocation = ShEntity2::GetPosition2(m_aEntityList[i]);
		const CShVector2 & vNewWallLocation = ShEntity2::GetPosition2(pEntity);

		if (WALL_WIDTH >= shAbsf(vWallLocation.m_x - vNewWallLocation.m_x)
			|| WALL_HEIGHT >= shAbsf(vWallLocation.m_y - vNewWallLocation.m_y))
		{
			m_aEntityList.Add(pEntity);
			return true;
		}
	}

	return false;
}

/**
 * @brief GeneratePhysic
 */
void ObjectWall::GeneratePhysic(b2World * pB2World)
{
	return; //Wip
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.angle = 0;

	m_pBody = pB2World->CreateBody(&bodyDef);
	SH_ASSERT(shNULL != m_pBody)

	b2Vec2 aPointList[64];

	int nEntityCount = m_aEntityList.GetCount();
	for (int i = 0; i < nEntityCount; ++i)
	{
		// aPointList[id] = ShineToB2(vPoint);
	}

	b2PolygonShape b2PolyShape;
	b2PolyShape.Set(aPointList, 4);
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
Object::EType ObjectWall::GetObjectType(void) const
{
	return EType::wall;
}
