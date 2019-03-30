#include "World.h"

/**
 * @brief Constructor
 */
World::World(void)
: m_pbWorld(shNULL)
, m_pMapGeneratorPlugin(shNULL)
, m_pMapGenerator(shNULL)
, m_map()
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
		
	// Map Generator
	m_pMapGeneratorPlugin = new PluginMapGenerator();
	ShApplication::RegisterPlugin(m_pMapGeneratorPlugin, false);
	
	GenerateMap(m_map, 20, 15);

	//
	// Load and parse all Collision Shape
	CShArray<ShCollisionShape*> aCollisionShape;
	ShCollisionShape::GetCollisionShapeArray(levelIdentifier, aCollisionShape);
	int nShapeCount = aCollisionShape.GetCount();

	for (int i = 0; i < nShapeCount; ++i)
	{
		ShCollisionShape * pShape = aCollisionShape[i];

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = ShineToB2(ShCollisionShape::GetWorldPosition2(pShape));
		bodyDef.angle = 0;

		b2Body * pBody = m_pbWorld->CreateBody(&bodyDef);

		b2ChainShape chainShape;
		GenerateShape(pShape, pBody->GetPosition(), chainShape);
		
		b2FixtureDef bodyFixture;
		bodyFixture.shape = &chainShape;
		pBody->CreateFixture(&bodyFixture);
	}
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

/**
* @brief DatasetParser
* @param pObject
* @param pDataSet
*/
void World::DatasetParser(ShObject * pObject, ShDataSet * pDataSet)
{
	bool isLethalBox = false, isInifinteBox = false;

	b2BodyDef bodyDef;
	b2FixtureDef bodyFixture;

	ShObject * pAttachedObject = shNULL;
	ShObject * pAttachedObject2 = shNULL;

	const CShIdentifier & idDataSetIdentifier = ShDataSet::GetDataSetIdentifier(pDataSet);

	int iDataCount = ShDataSet::GetDataCount(pDataSet);
	for (int nData = 0; nData < iDataCount; ++nData)
	{
		const CShIdentifier & idDataIdentifier = ShDataSet::GetDataIdentifier(pDataSet, nData);
		if (CShIdentifier("AttachedObject") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, &pAttachedObject);
		}
		else if (CShIdentifier("AttachedObject2") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, &pAttachedObject2);
		}
		else if (CShIdentifier("allowSleep") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, bodyDef.allowSleep);
		}
		else if (CShIdentifier("awake") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, bodyDef.awake);
		}
		else if (CShIdentifier("fixedRotation") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, bodyDef.fixedRotation);
		}
		else if (CShIdentifier("bullet") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, bodyDef.bullet);
		}
		else if (CShIdentifier("active") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, bodyDef.active);
		}
		else if (CShIdentifier("isStatic") == idDataIdentifier)
		{
			bool isStatic = true;
			ShDataSet::GetDataValue(pDataSet, nData, isStatic);

			if (isStatic)
			{
				bodyDef.type = b2_staticBody;
			}
			else
			{
				bodyDef.type = b2_dynamicBody;
			}
		}
		else if (CShIdentifier("isInifiniteBox") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, isInifinteBox);
		}
		else if (CShIdentifier("isLethalBox") == idDataIdentifier)
		{
			ShDataSet::GetDataValue(pDataSet, nData, isLethalBox);
		}
		else
		{
			//
			// Fixture
			if (CShIdentifier("friction") == idDataIdentifier)
			{
				float fFriction = 0.0f;
				ShDataSet::GetDataValue(pDataSet, nData, fFriction);
				bodyFixture.friction = fFriction;
			}
			else if (CShIdentifier("restitution") == idDataIdentifier)
			{
				float fRestitution = 0.0f;
				ShDataSet::GetDataValue(pDataSet, nData, fRestitution);
				bodyFixture.restitution = fRestitution;
			}
			else if (CShIdentifier("density") == idDataIdentifier)
			{
				float fDensity = 0.0f;
				ShDataSet::GetDataValue(pDataSet, nData, fDensity);
				bodyFixture.density = fDensity;
			}
			else if ((CShIdentifier("categoryBits") == idDataIdentifier))
			{
				int iCategories = 0;
				ShDataSet::GetDataValue(pDataSet, nData, iCategories);
				bodyFixture.filter.categoryBits = iCategories;
			}
			else if ((CShIdentifier("maskBits") == idDataIdentifier))
			{
				int iMask = 0;
				ShDataSet::GetDataValue(pDataSet, nData, iMask);
				bodyFixture.filter.maskBits = iMask;
			}
		}
	}

	bodyDef.angle = ShObject::GetWorldRotation(pObject).m_z; // convert euler angle to radian
	bodyDef.position = ShineToB2(ShObject::GetWorldPosition2(pObject));

	b2Body * pBody = m_pbWorld->CreateBody(&bodyDef);

	Object * pSTObject;

	if (CShIdentifier("object_static") == idDataSetIdentifier)
	{
		//TODO
	}
	else if (CShIdentifier("object_player") == idDataSetIdentifier)
	{
		//TODO
	}
	else
	{
		SH_ASSERT_ALWAYS();
	}

	m_aObjectList.Add(pSTObject);
	pBody->SetUserData(pSTObject);

	ShObject::EType objectType = ShObject::GetType(pObject);
	if (ShObject::e_type_dummy_aabb2 == objectType)
	{
		b2PolygonShape b2Shape;
		GenerateShape((ShDummyAABB2*)pObject, pBody->GetPosition(), b2Shape);
		bodyFixture.shape = &b2Shape;
		pBody->CreateFixture(&bodyFixture);
	}
	else if (ShObject::e_type_unknown == objectType)
	{
		b2ChainShape b2Shape;
		GenerateShape((ShCollisionShape *)pObject, pBody->GetPosition(), b2Shape);
		bodyFixture.shape = &b2Shape;
		pBody->CreateFixture(&bodyFixture);
	}
	else
	{
		SH_ASSERT_ALWAYS();
	}
}

/**
 * @brief GenerateShape
 * @param pCollisionShape
 * @param center
 * @param b2OutShape
 */
void World::GenerateShape(ShCollisionShape * pCollisionShape, const b2Vec2 & center, b2ChainShape & b2OutShape)
{
	SH_ASSERT(64 > ShCollisionShape::GetPointCount(pCollisionShape));

	b2Vec2 aVertex[64];

	const int pointCount = ShCollisionShape::GetPointCount(pCollisionShape);

	for (int i = 0; i < pointCount; ++i)
	{
		const CShVector2 & pos = ShCollisionShape::GetPoint(pCollisionShape, i);

		aVertex[i] = ShineToB2(pos);
	}

	b2OutShape.CreateLoop(aVertex, pointCount);
}

void World::GenerateShape(ShDummyAABB2 * pObject, const b2Vec2 & center, b2PolygonShape & b2OutShape)
{
	CShVector3 scale = ShObject::GetWorldScale(pObject);
	CShVector2 vDummyAABB2Translation = ShObject::GetWorldPosition2(pObject);

	const CShAABB2 & aabb2 = ShDummyAABB2::GetAABB(pObject);
	CShVector2 vPoint1(CShVector2(aabb2.m_min.m_x * scale.m_x, aabb2.m_min.m_y * scale.m_y) + vDummyAABB2Translation);
	CShVector2 vPoint2(CShVector2(aabb2.m_min.m_x * scale.m_x, aabb2.m_max.m_y * scale.m_y) + vDummyAABB2Translation);
	CShVector2 vPoint3(CShVector2(aabb2.m_max.m_x * scale.m_x, aabb2.m_max.m_y * scale.m_y) + vDummyAABB2Translation);
	CShVector2 vPoint4(CShVector2(aabb2.m_max.m_x * scale.m_x, aabb2.m_min.m_y * scale.m_y) + vDummyAABB2Translation);

	b2Vec2 aB2Point[4];
	aB2Point[0] = ShineToB2(vPoint1) - center;
	aB2Point[1] = ShineToB2(vPoint2) - center;
	aB2Point[2] = ShineToB2(vPoint3) - center;
	aB2Point[3] = ShineToB2(vPoint4) - center;

	b2OutShape.Set(aB2Point, 4);
}

/**
* @brief 
*/
void World::GenerateMap(Map2D & map2D, int rowCount, int ColumnCount)
{
	map2D.Release();
	map2D.Initialize(20, 15, 0);
//
//	//
//	// Map Generation
//	{
//		//
//		// Get and configure MapGenerator
//		m_pMapGenerator = GetPluginMapGenerator()->CreateMapGenerator(e_map_generator_type_test);
//		{
//			MapGeneratorTest * pMapGeneratorTest = reinterpret_cast<MapGeneratorTest*>(m_pMapGenerator);
//			CShIdentifier idGame("game");
//			ShSprite * pSpriteWall = ShSprite::Find(idGame, CShIdentifier("wall"));
//			ShSprite * pSpriteGrass = ShSprite::Find(idGame, CShIdentifier("grass"));
//			ShSprite * pSpriteWater = ShSprite::Find(idGame, CShIdentifier("water"));
//
//			SH_ASSERT(shNULL != pSpriteWall);
//			SH_ASSERT(shNULL != pSpriteGrass);
//			SH_ASSERT(shNULL != pSpriteWater);
//
//			//		pMapGeneratorTest->m_aTileMap.Add(0, pSpriteWall);
//			//		pMapGeneratorTest->m_aTileMap.Add(1, pSpriteGrass);
//			//		pMapGeneratorTest->m_aTileMap.Add(2, pSpriteWater);
//		}
//
//		//
//		// Generate Map
//		Map * pMap = &m_map;
//		GetPluginMapGenerator()->GenerateMap(m_pMapGenerator, pMap, idLevel);
//
//		int iRowCount = m_map.GetRowCount();
//		int iColumnCount = m_map.GetColumnCount();
//		for (int iRowIndex = 0; iRowIndex < iRowCount; ++iRowIndex)
//		{
//			for (int iColumnIndex = 0; iColumnIndex < iColumnCount; ++iColumnIndex)
//			{
//
//			}
//		}
//	}
}

/**
* @brief ShineToB2
* @param vec
*/
/*static*/ CShVector2 World::ShineToB2(b2Vec2 vec)
{
	return CShVector2(vec.x, vec.y) * CShVector2(SH_TO_B2, SH_TO_B2);
}

/**
* @brief ShineToB2
* @param vec
*/
/*static*/ b2Vec2 World::ShineToB2(CShVector2 vec)
{
	vec /= CShVector2(SH_TO_B2, SH_TO_B2);
	return b2Vec2(vec.m_x, vec.m_y);
}
