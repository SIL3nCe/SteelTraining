#include "MapGeneratorTest.h"

#include "../Map/Map2D.h"

/**
* @brief Constructor
*/
/*explicit*/ MapGeneratorTest::MapGeneratorTest(void)
: m_iRowNb(MAP_DEFAULT_ROW_NB)
, m_iColumnNb(MAP_DEFAULT_COLUMN_NB)
, m_iTileSize(MAP_DEFAULT_TILE_SIZE)
, m_aTileMap()
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ MapGeneratorTest::~MapGeneratorTest(void)
{
	// ...
}

/**
* @brief MapGeneratorTest::GetType
*/
/*virtual*/ EMapGeneratorType MapGeneratorTest::GetType(void) const
{
	return e_map_generator_type_test;
}

/**
* @brief MapGeneratorTest::GetType
*/
/*virtual*/ bool MapGeneratorTest::GenerateMap(Map *& pAbstractMap, const CShIdentifier & idLevel)
{
	if (pAbstractMap->GetType() != e_map_type_2d)
	{
		return false;
	}

	Map2D * pMap2D = static_cast<Map2D*>(pAbstractMap);
	if (!pMap2D->Initialize(m_iRowNb, m_iColumnNb, m_iTileSize))
	{
		return false;
	}

	MapGenerationAlgorithm(pMap2D, idLevel);

	return true;
}
	
/**
* @brief MapGeneratorTest::MapGenerationAlgorithm
*/
void MapGeneratorTest::MapGenerationAlgorithm(Map2D *& pMap, const CShIdentifier & idLevel)
{
	//
	// Update representation for TileMap
	for (int iRowIndex = 1; iRowIndex < m_iRowNb - 1; ++iRowIndex)
	{
		shU32 iRepr = 1;
		for (int iColumnIndex = 0; iColumnIndex < m_iColumnNb - 1; ++iColumnIndex)
		{
			ShSprite ** ppSprite = m_aTileMap.Find(iRepr);
			if (shNULL != ppSprite && shNULL != *ppSprite)
			{
				pMap->m_aaTiles[iRowIndex][iColumnIndex].iRepresentation = iRepr;
			}
		}

		iRepr = 2;
		for (int iColumnIndex = m_iColumnNb - 10; iColumnIndex < m_iColumnNb - 2 && iRowIndex < 10 && iRowIndex > 1; ++iColumnIndex)
		{
			ShSprite ** ppSprite = m_aTileMap.Find(iRepr);
			if (shNULL != ppSprite && shNULL != *ppSprite)
			{
				pMap->m_aaTiles[iRowIndex][iColumnIndex].iRepresentation = iRepr;
			}
		}
	}

	//
	// Create Entity2 according to representations
	for (int iRowIndex = 0; iRowIndex < m_iRowNb; ++iRowIndex)
	{
		for (int iColumnIndex = 0; iColumnIndex < m_iColumnNb; ++iColumnIndex)
		{
			shU32 iRepr = pMap->m_aaTiles[iRowIndex][iColumnIndex].iRepresentation;
			ShSprite ** ppSprite = m_aTileMap.Find(iRepr);
			if (shNULL != ppSprite && shNULL != *ppSprite)
			{
				pMap->m_aaTiles[iRowIndex][iColumnIndex].Initialize(iRepr, idLevel, *ppSprite, iRowIndex, iColumnIndex, m_iTileSize);
			}
		}
	}
}