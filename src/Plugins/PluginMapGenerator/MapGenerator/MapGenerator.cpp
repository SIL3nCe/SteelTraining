#include "MapGenerator.h"

/**
* @brief Constructor
*/
/*explicit*/ MapGenerator::MapGenerator(void)
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ MapGenerator::~MapGenerator(void)
{
	// ...
}

/**
* @brief
*/
EMapGeneratorType MapGenerator::GetType(void) const
{
	return EMapGeneratorType::e_map_generator_type_test;
}

