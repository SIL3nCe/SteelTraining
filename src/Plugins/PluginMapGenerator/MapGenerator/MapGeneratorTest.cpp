#include "MapGeneratorTest.h"

#include "../Map/Map2D.h"

/**
* @brief Constructor
*/
/*explicit*/ MapGeneratorTest::MapGeneratorTest(void)
: m_aMapEntity()
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
	//
	// Update representation for TileMap

	int iRowCount = pMap->GetColumnNb();
	for (int iRow = 1; iRow < iRowCount; ++iRow)
	{
		int iColumnCount = pMap->GetRowNb();
		for (int iColumn = 0; iColumn < iColumnCount; ++iColumn)
		{
			MapEntity mapEntity;
			FindNextMapEntity(iRow, iColumn, mapEntity);
		}
	}
}

/**
* @brief MapGeneratorTest::MapGenerationAlgorithm
*/
void MapGeneratorTest::FindNextMapEntity(int iRow, int iColumn, MapEntity & newMapEntity)
{
}

bool MapGeneratorTest::CanBePlacedHere(const MapEntity & mapEntity, Map2D *& pMap, int iColumn, int iRow)
{
	if (m_aMapEntity.IsEmpty()) return false;

	int iMapEntityWidth = mapEntity.m_width;
	int iMapEntityHeight = mapEntity.m_height;

	// Check if the entity is outside the map
	{
		if (0 > iColumn + iMapEntityWidth) return false;
		if (m_aMapEntity.GetCount() <= iColumn + iMapEntityWidth) return false;

		if (0 > iRow + iMapEntityHeight) return false;
		if (m_aMapEntity[0].GetCount() <= iRow + iMapEntityHeight) return false;
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
