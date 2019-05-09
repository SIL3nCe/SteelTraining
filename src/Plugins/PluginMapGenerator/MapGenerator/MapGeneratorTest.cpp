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
	int nRowCount = pMap->GetRowCount();
	for (int iRow = 0; iRow < nRowCount; ++iRow)
	{
		int nColumnCount = pMap->GetColumnCount();
		for (int iColumn = 0; iColumn < nColumnCount; ++iColumn)
		{
			if (0 == iColumn
				|| 0 == iRow
				|| iColumn == nColumnCount - 1 
				|| iRow == nRowCount - 1)
			{
				pMap->AddWall(iRow, iColumn);
			}
			else
			{
				MapEntity mapEntity;
				if (FindNextMapEntity(iRow, iColumn, mapEntity))
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

bool MapGeneratorTest::CanBePlacedHere(const MapEntity & mapEntity, Map2D *& pMap, int column, int row)
{
	if (m_aMapEntity.IsEmpty()) return false;

	int iMapEntityWidth = mapEntity.m_iWidth;
	int iMapEntityHeight = mapEntity.m_iHeight;

	// Check if the entity is outside the map
	{
		if (0 > column + iMapEntityWidth) return false;
		if (pMap->GetRowCount() <= column + iMapEntityWidth) return false;

		if (0 > row + iMapEntityHeight) return false;
		if (pMap->GetColumnCount() <= row + iMapEntityHeight) return false;
	}

	for (int iRow = 0; iRow < iMapEntityWidth; ++iRow)
	{
		for (int iCOlumn = 0; iCOlumn < iMapEntityWidth; ++iCOlumn)
		{
			EMapEntityTileType eMapEntityTileType = mapEntity.m_mNeededTiles[iRow][iCOlumn];
			
			if (EMapEntityTileType::e_map_entity_tile_type_none == eMapEntityTileType) continue;

			Tile * pTile = pMap->GetTile(iRow + row, iCOlumn + column);
			if (e_tile_block == pTile->m_eTileType || e_tile_wall == pTile->m_eTileType) return false;
		}
	}

	return true;
}
