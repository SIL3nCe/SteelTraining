#pragma once

#include "../Map/Map.h"

enum EMapGeneratorType
{
	e_map_generator_type_test,
};

class MapGenerator
{
public:
	explicit						MapGenerator	(void);
	virtual							~MapGenerator	(void);

	virtual EMapGeneratorType		GetType			(void) const = 0;
	virtual bool					GenerateMap		(Map * pMap) = 0;

private:

};
