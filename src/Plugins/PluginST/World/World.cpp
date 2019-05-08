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

	m_playerCharacter.Initialize(m_levelIdentifier, m_pbWorld, this, &m_inputManager);
		
	// Map Generator
	m_pMapGeneratorPlugin = new PluginMapGenerator();
	ShApplication::RegisterPlugin(m_pMapGeneratorPlugin, false);
	
	GenerateMap(m_map, 20, 15);
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

	UpdateCamera(dt);
}

/**
 * @brief UpdateCamera
 */
void World::UpdateCamera(float dt)
{
	if (ShCamera * pCamera = ShCamera::GetCamera2D())
	{
		const CShVector3 & vPlayerLocation = m_playerCharacter.GetEntityLocation();
		ShCamera::SetPosition2(pCamera, vPlayerLocation.XY());
		ShCamera::SetTarget(pCamera, CShVector3(vPlayerLocation.XY(), 0.0f));
	}
}

/**
 * @brief Update
 */
const PluginInputManager & World::GetInputManager(void)
{
	return m_inputManager;
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

		aVertex[i] = B2ToShine(pos);
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
	aB2Point[0] = B2ToShine(vPoint1) - center;
	aB2Point[1] = B2ToShine(vPoint2) - center;
	aB2Point[2] = B2ToShine(vPoint3) - center;
	aB2Point[3] = B2ToShine(vPoint4) - center;

	b2OutShape.Set(aB2Point, 4);
}

/**
* @brief 
*/
void World::GenerateMap(Map2D & map2D, int rowCount, int ColumnCount)
{
	map2D.Release();
	map2D.Initialize(20, 15);

	//
	// Map Generation
	{
		//
		// Get and configure MapGenerator
		m_pMapGenerator = m_pMapGeneratorPlugin->CreateMapGenerator(e_map_generator_type_test);
		{
			MapGeneratorTest * pMapGeneratorTest = reinterpret_cast<MapGeneratorTest*>(m_pMapGenerator);
			CShIdentifier idGame("game");
		}

		//
		// Generate Map
		Map * pMap = &m_map;
		m_pMapGeneratorPlugin->GenerateMap(m_pMapGenerator, pMap, m_levelIdentifier);

		//
		int iRowCount = m_map.GetRowCount();
		int iColumnCount = m_map.GetColumnCount();
		for (int nRow = 0; nRow < iRowCount; ++nRow)
		{
			for (int nColumn = 0; nColumn < iColumnCount; ++nColumn)
			{
				Tile * pTile = m_map.GetTile(nRow, nColumn);
				switch (pTile->m_eTileType)
				{
				case ETileType::e_tile_wall:
				{
					ShSprite * pSprite = GetWallSprite(nRow, nColumn);
					CShString strWallIdentifier("wall");
					strWallIdentifier += CShString::FromInt(nRow) + CShString::FromInt(nColumn);

					CShVector3 position(nRow * 100, nColumn * 100, 0.0f);
					CShEulerAngles angle;
					CShVector3 scale(1.0f, 1.0f, 1.0f);
					
					ShEntity2 * pWallEntity2 = ShEntity2::Create(m_levelIdentifier, CShIdentifier(strWallIdentifier), GID(layer_default), pSprite, position, angle, scale, true);
				}
				break;
					
				}
			}
		}
	}
}

/**
* @brief 
*/
ShSprite * World::GetWallSprite(int iRowPosition, int iColumnPosition)
{
	if (m_map.GetTiles().IsEmpty())
	{
		return shNULL;
	}

	bool bBorderTop = iRowPosition == 0;
	bool bBorderRight = iColumnPosition == 0;
	bool bBorderBottom = m_map.GetRowCount() - 1 == iRowPosition;
	bool bBorderLeft = m_map.GetColumnCount() - 1 == iRowPosition;

	CShString strIdentifier("mur");

	if (bBorderTop) strIdentifier += "_haut";
	else if (bBorderBottom) strIdentifier += "_bas";
	if (bBorderRight) strIdentifier += "_droit";
	else if (bBorderLeft) strIdentifier += "_gauche";

	SH_ASSERT(ShSprite::Exists(CShIdentifier("mur"), CShIdentifier(strIdentifier)))
		
	ShSprite * pSprite = ShSprite::Find(CShIdentifier("mur"), CShIdentifier(strIdentifier));


	return pSprite;
}

/**
* @brief ShineToB2
* @param vec
*/
/*static*/ CShVector2 World::ShineToB2(b2Vec2 vec)
{
	return CShVector2(vec.x, vec.y) * SH_TO_B2;
}

/**
* @brief B2ToShine
* @param vec
*/
/*static*/ b2Vec2 World::B2ToShine(CShVector2 vec)
{
	float fFactor = 1 / SH_TO_B2;
	vec *= fFactor;
	return b2Vec2(vec.m_x, vec.m_y);
}

/**
 * @brief World::GetPlayerCharacter
 * @return
 */
const PlayerCharacter & World::GetPlayerCharacter(void) const
{
	return m_playerCharacter;
}
