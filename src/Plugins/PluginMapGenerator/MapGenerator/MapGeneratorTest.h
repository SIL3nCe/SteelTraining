#pragma once

#include "ShSDK/ShSDK.h"
#include "MapGenerator.h"

class MapGeneratorTest : public MapGenerator
{
public:
	explicit 						MapGeneratorTest	(void);
	virtual							~MapGeneratorTest	(void);

	//
	// Getters/Setters
	virtual EMapGeneratorType		GetType				(void) const SH_ATTRIBUTE_OVERRIDE;

	//
	// Map Generation
	virtual bool					GenerateMap			(Map * pAbstractMap) SH_ATTRIBUTE_OVERRIDE;
private:
public:
	//
	// Map related
	shU32			m_iRowNb;
	shU32			m_iColumnNb;
	shU32			m_iTileSize;

	//
	//	
};
