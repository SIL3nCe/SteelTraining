#include "MapGeneratorTest.h"

/**
* @brief Constructor
*/
/*explicit*/ MapGeneratorTest::MapGeneratorTest(void)
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
/*virtual*/ bool MapGeneratorTest::GenerateMap(Map * pMap)
{
	if (pMap->GetType() != e_map_type_2d)
	{
		return false;
	}

	//
	// TODO

	return true;
}