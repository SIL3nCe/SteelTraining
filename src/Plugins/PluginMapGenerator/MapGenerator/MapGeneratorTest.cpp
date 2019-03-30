#include "MapGeneratorTest.h"

#include "../Map/Map2D.h"

/**
* @brief Constructor
*/
/*explicit*/ MapGeneratorTest::MapGeneratorTest(void)
: m_aMapEntity()
, randValue()
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

void MapGeneratorTest::AddMapEntity(const MapEntity & mapEntity)
{
	m_aMapEntity.Add(mapEntity);
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
	MapGenerationAlgorithm(pMap2D, idLevel);

	return true;
}
	
/**
* @brief MapGeneratorTest::MapGenerationAlgorithm
*/
void MapGeneratorTest::MapGenerationAlgorithm(Map2D *& pMap, const CShIdentifier & idLevel)
{
	int iRowCount = pMap->GetColumnCount();
	for (int nRow = 1; nRow < iRowCount; ++nRow)
	{
		int iColumnCount = pMap->GetRowCount();
		for (int nColumn = 0; nColumn < iColumnCount; ++nColumn)
		{
			if (0 == nColumn || iColumnCount + 1 == iColumnCount || 0 == nRow || iRowCount + 1 == iRowCount)
			{
				pMap->AddWall(nRow, nColumn);
			}
			else
			{
				MapEntity mapEntity;
				if (FindNextMapEntity(nRow, nColumn, mapEntity))
				{

				}
			}
		}
	}
}

/**
* @brief MapGeneratorTest::MapGenerationAlgorithm
*/
bool MapGeneratorTest::FindNextMapEntity(int iRow, int iColumn, MapEntity & newMapEntity)
{

	return false;
}

bool MapGeneratorTest::CanBePlacedHere(const MapEntity & mapEntity, Map2D *& pMap, int iColumn, int iRow)
{
	if (m_aMapEntity.IsEmpty()) return false;

	int iMapEntityWidth = mapEntity.m_iWidth;
	int iMapEntityHeight = mapEntity.m_iHeight;

	// Check if the entity is outside the map
	{
		if (0 > iColumn + iMapEntityWidth) return false;
		if (pMap->GetRowCount() <= iColumn + iMapEntityWidth) return false;

		if (0 > iRow + iMapEntityHeight) return false;
		if (pMap->GetColumnCount() <= iRow + iMapEntityHeight) return false;
	}

	for (int nRow = 0; nRow < iMapEntityWidth; ++nRow)
	{
		for (int nColumn = 0; nColumn < iMapEntityWidth; ++nColumn)
		{
			EMapEntityTileType eMapEntityTileType = mapEntity.m_mNeededTiles[nRow][nColumn];
			
			if (EMapEntityTileType::e_map_entity_tile_type_none == eMapEntityTileType) continue;

			Tile * pTile = pMap->GetTile(nRow + iRow, nColumn + iColumn);
			if (e_tile_block == pTile->m_eTileType || e_tile_wall == pTile->m_eTileType) return false;
		}
	}

	return true;
}
