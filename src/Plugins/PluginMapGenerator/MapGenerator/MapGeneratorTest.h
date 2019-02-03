#pragma once

#include "MapGenerator.h"
#include "../Map/Map2D.h"

class MapGeneratorTest : public MapGenerator
{
public:
	explicit 						MapGeneratorTest			(void);
	virtual							~MapGeneratorTest			(void);

	//
	// Getters/Setters
	virtual EMapGeneratorType		GetType						(void) const SH_ATTRIBUTE_OVERRIDE;

	//
	// Map Generation
	virtual bool					GenerateMap					(Map *& pAbstractMap, const CShIdentifier & idLevel) SH_ATTRIBUTE_OVERRIDE;
private:
	void							MapGenerationAlgorithm		(Map2D *& pMap, const CShIdentifier & idLevel);
public:
	//
	// Map related
	shU32							m_iRowNb;
	shU32							m_iColumnNb;
	shU32							m_iTileSize;

	//
	// Tile related
	CShArrayMap<shU32, ShSprite*>	m_aTileMap;
};
