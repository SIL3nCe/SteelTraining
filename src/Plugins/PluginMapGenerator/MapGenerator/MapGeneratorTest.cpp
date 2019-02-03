#include "MapGeneratorTest.h"

#include "../Map/Map2D.h"

/**
* @brief Constructor
*/
/*explicit*/ MapGeneratorTest::MapGeneratorTest(void)
: m_iRowNb(MAP_DEFAULT_ROW_NB)
, m_iColumnNb(MAP_DEFAULT_COLUMN_NB)
, m_iTileSize(MAP_DEFAULT_TILE_SIZE)
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
/*virtual*/ bool MapGeneratorTest::GenerateMap(Map * pAbstractMap)
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

	//
	// TODO

	return true;
}