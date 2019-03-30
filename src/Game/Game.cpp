#include "Game.h"

#include "MapGenerator/MapGeneratorTest.h"

Game * Game::m_pInstance = shNULL;

Game::Game(void)
: m_pMapGenerator(shNULL)
, m_map()
{
	// ...
}

Game * Game::GetInstance(void)
{
	if (shNULL == m_pInstance)
	{
		m_pInstance = new Game();
	}

	return(m_pInstance);
}

void Game::Initialize(void)
{
	const CShIdentifier idLevel("level_test");
	if (!ShLevel::Load(idLevel))
	{
		SH_ASSERT_ALWAYS();
	}

	//
	// Get and configure MapGenerator
	m_pMapGenerator = GetPluginMapGenerator()->CreateMapGenerator(e_map_generator_type_test);
	{
		MapGeneratorTest * pMapGeneratorTest = reinterpret_cast<MapGeneratorTest*>(m_pMapGenerator);
		CShIdentifier idGame("game");
		ShSprite * pSpriteWall	= ShSprite::Find(idGame, CShIdentifier("wall"));
		ShSprite * pSpriteGrass	= ShSprite::Find(idGame, CShIdentifier("grass"));
		ShSprite * pSpriteWater	= ShSprite::Find(idGame, CShIdentifier("water"));

		SH_ASSERT(shNULL != pSpriteWall);
		SH_ASSERT(shNULL != pSpriteGrass);
		SH_ASSERT(shNULL != pSpriteWater);

//		pMapGeneratorTest->m_aTileMap.Add(0, pSpriteWall);
//		pMapGeneratorTest->m_aTileMap.Add(1, pSpriteGrass);
//		pMapGeneratorTest->m_aTileMap.Add(2, pSpriteWater);
	}

	//
	// Generate Map
	Map * pMap = &m_map;
	GetPluginMapGenerator()->GenerateMap(m_pMapGenerator, pMap, idLevel);

	int iRowCount		= m_map.GetRowCount();
	int iColumnCount	= m_map.GetColumnCount();
	for (int iRowIndex = 0; iRowIndex < iRowCount; ++iRowIndex)
	{
		for (int iColumnIndex = 0; iColumnIndex < iColumnCount; ++iColumnIndex)
		{

		}
	}
}

void Game::Release(void)
{
	GetPluginMapGenerator()->DestroyMapGenerator(m_pMapGenerator);
}

void Game::Update(float dt)
{
	float fFactor = 100.0f * dt;
	if (ShUser::HasTriggeredAction(ShUser::GetUser(0), CShIdentifier("right")))
	{
		ShCamera * pCamera = ShCamera::GetCamera2D();
		CShVector3 vDelta(1.0f * fFactor, 0.0f, 0.0f);
		ShCamera::Translate(pCamera, vDelta);
		ShCamera::SetTarget(pCamera, ShCamera::GetTarget(pCamera) + vDelta);
	}

	if (ShUser::HasTriggeredAction(ShUser::GetUser(0), CShIdentifier("left")))
	{
		ShCamera * pCamera = ShCamera::GetCamera2D();
		CShVector3 vDelta(-1.0f * fFactor, 0.0f, 0.0f);
		ShCamera::Translate(pCamera, vDelta);
		ShCamera::SetTarget(pCamera, ShCamera::GetTarget(pCamera) + vDelta);
	}
	
	if (ShUser::HasTriggeredAction(ShUser::GetUser(0), CShIdentifier("up")))
	{
		ShCamera * pCamera = ShCamera::GetCamera2D();
		CShVector3 vDelta(0.0f, 1.0f * fFactor, 0.0f);
		ShCamera::Translate(pCamera, vDelta);
		ShCamera::SetTarget(pCamera, ShCamera::GetTarget(pCamera) + vDelta);
	}
	
	if (ShUser::HasTriggeredAction(ShUser::GetUser(0), CShIdentifier("down")))
	{
		ShCamera * pCamera = ShCamera::GetCamera2D();
		CShVector3 vDelta(0.0f, -1.0f * fFactor, 0.0f);
		ShCamera::Translate(pCamera, vDelta);
		ShCamera::SetTarget(pCamera, ShCamera::GetTarget(pCamera) + vDelta);
	}
}