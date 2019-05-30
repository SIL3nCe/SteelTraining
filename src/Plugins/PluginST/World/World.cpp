#include "World.h"
#include "Character/EnemyMeleeCharacter.h"

#if SH_PC
#	include <time.h>
#endif // SH_PC

/**
 * @brief Constructor
 */
World::World(void)
: m_levelIdentifier()
, m_pbWorld(shNULL)
, m_fFixedTimestepAccumulator(0.0f)
, m_apEnemyList()
, m_inputManager()
, m_playerCharacter()
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
	srand(static_cast<unsigned int>(time(shNULL)));

	m_levelIdentifier = levelIdentifier;

	b2Vec2 gravity(0.0f, 0.0f);
	m_pbWorld = new b2World(gravity);

	ShUser * pUser = ShUser::GetUser(0);
	SH_ASSERT(shNULL != pUser)

	m_inputManager.Initialize(pUser);

	m_playerCharacter.Initialize(m_levelIdentifier, m_pbWorld, this, &m_inputManager);

	EnemyMeleeCharacter * pEnemy = new EnemyMeleeCharacter();
	pEnemy->Initialize(CShIdentifier("enemy1"), m_levelIdentifier, m_pbWorld, this, CShVector2(300.f, -300.f));
	m_apEnemyList.Add(pEnemy);
	pEnemy = new EnemyMeleeCharacter();
	pEnemy->Initialize(CShIdentifier("enemy2"), m_levelIdentifier, m_pbWorld, this, CShVector2(300.f, -1300.f));
	m_apEnemyList.Add(pEnemy);
	pEnemy = new EnemyMeleeCharacter();
	pEnemy->Initialize(CShIdentifier("enemy3"), m_levelIdentifier, m_pbWorld, this, CShVector2(1300.f, -300.f));
	m_apEnemyList.Add(pEnemy);
	pEnemy = new EnemyMeleeCharacter();
	pEnemy->Initialize(CShIdentifier("enemy4"), m_levelIdentifier, m_pbWorld, this, CShVector2(1300.f, -1300.f));
	m_apEnemyList.Add(pEnemy);
		
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
	//
	// Plugin MapGenerator
	ShApplication::UnRegisterPlugin(m_pMapGeneratorPlugin);
	SH_SAFE_DELETE(m_pMapGeneratorPlugin);

	//
	// World-related
	m_playerCharacter.Release();
	m_inputManager.Release();

	int iEnemyCount = m_apEnemyList.GetCount();
	for (int iEnemyIndex = 0; iEnemyIndex < iEnemyCount; ++iEnemyIndex)
	{
		SH_SAFE_RELEASE_DELETE(m_apEnemyList[iEnemyIndex])
	}
	m_apEnemyList.Empty();

	SH_SAFE_DELETE(m_pbWorld)
}

/**
 * @brief Update
 */
void World::Update(float dt)
{
	m_inputManager.Update();

	m_playerCharacter.Update(dt);

	int iEnemyCount = m_apEnemyList.GetCount();
	for (int iEnemyIndex = 0; iEnemyIndex < iEnemyCount; ++iEnemyIndex)
	{
		m_apEnemyList[iEnemyIndex]->Update(dt);
	}

	// Physic
	const int MAX_STEPS = 5;
	const float FIXED_TIMESTEP = 1 / 60.0f;
 
	m_fFixedTimestepAccumulator += dt;

	const int nSteps = static_cast<int>(floorf(m_fFixedTimestepAccumulator / FIXED_TIMESTEP));
	if (nSteps > 0)
	{
		m_fFixedTimestepAccumulator -= nSteps * FIXED_TIMESTEP;
	}
 
	const int nStepsClamped = shMin(nSteps, MAX_STEPS);

	for (int i = 0; i < nStepsClamped; ++i)
	{
		//velocityIterations: how strongly to correct velocity
		//positionIterations: how strongly to correct position
		// ^ Making these values higher will give you a more correct simulation, at the cost of some performance
		m_pbWorld->Step(FIXED_TIMESTEP, 8, 3);
	}
	// Physic -

	m_playerCharacter.UpdateAnimations(dt);

	for (int iEnemyIndex = 0; iEnemyIndex < iEnemyCount; ++iEnemyIndex)
	{
		m_apEnemyList[iEnemyIndex]->UpdateAnimations(dt);
	}

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
* @brief GenerateMap
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
				if (Tile * pTile = m_map.GetTile(nRow, nColumn))
				{
					switch (pTile->m_eTileType)
					{
						case ETileType::e_tile_wall:
						{
							ShSprite * pSprite = GetWallSprite(nRow, nColumn);
							SH_ASSERT(shNULL != pSprite)

							float fWidth = ShSprite::GetWidth(pSprite);
							float fHeight = ShSprite::GetHeight(pSprite);
							
							SH_ASSERT(fWidth == WALL_WIDTH)
							SH_ASSERT(fHeight == WALL_HEIGHT)

							CShString strWallIdentifier("wall");
							strWallIdentifier += CShString::FromInt(nRow) + CShString::FromInt(nColumn);

							CShVector3 position(nColumn * fWidth, nRow * -fHeight, 1.0f);

							ShEntity2 * pWallEntity = ShEntity2::Create(m_levelIdentifier, CShIdentifier(strWallIdentifier), GID(layer_default), pSprite, position, CShEulerAngles::ZERO, CShVector3::AXIS_ALL);
							SH_ASSERT(shNULL != pWallEntity)

							ObjectWall wall;
							wall.Initialize(pWallEntity, m_pbWorld);
							m_aWallList.Add(wall);
						}
						break;
					}
				}
			}
		}
	}
}

/**
* @brief GetWallSprite
*/
ShSprite * World::GetWallSprite(int iRowPosition, int iColumnPosition)
{
	if (m_map.GetTiles().IsEmpty())
	{
		return shNULL;
	}

	bool bBorderTop = iRowPosition == 0;
	bool bBorderLeft = iColumnPosition == 0;
	bool bBorderBottom = m_map.GetRowCount() - 1 == iRowPosition;
	bool bBorderRight = m_map.GetColumnCount() - 1 == iColumnPosition;

	CShString strIdentifier("mur");

	if (bBorderTop) strIdentifier += "_haut";
	else if (bBorderBottom) strIdentifier += "_bas";
	if (bBorderRight) strIdentifier += "_droit";
	else if (bBorderLeft) strIdentifier += "_gauche";

	SH_ASSERT(ShSprite::Exists(CShIdentifier("mur"), CShIdentifier(strIdentifier)))

	return ShSprite::Find(CShIdentifier("mur"), CShIdentifier(strIdentifier));
}

/**
 * @brief World::GetPlayerCharacter
 * @return
 */
PlayerCharacter & World::GetPlayerCharacter(void)
{
	return m_playerCharacter;
}

/**
 * @brief World::KillEnemy
 * @param pEnemy
 */
void World::KillEnemy(EnemyCharacter *pEnemy)
{
	m_apEnemyList.RemoveFirstSwapLast(pEnemy);
	SH_SAFE_RELEASE_DELETE(pEnemy)
}
