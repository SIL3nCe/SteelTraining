#pragma once

#include "ShSDK/ShSDK.h"

class Map;

enum EMapGeneratorType
{
	e_map_generator_type_test,
};

class MapGenerator
{
public:
	explicit						MapGenerator	(void);
	virtual							~MapGenerator	(void);

	virtual EMapGeneratorType		GetType			(void) const;
	virtual bool					GenerateMap		(Map *& pAbstractMap, const CShIdentifier & idLevel);

private:
};
