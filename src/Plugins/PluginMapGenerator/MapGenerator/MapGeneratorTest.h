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

	void							AddMapEntity				(const MapEntity & mapEntity);

	//
	// Map Generation
	virtual bool					GenerateMap					(Map *& pAbstractMap, const CShIdentifier & idLevel) SH_ATTRIBUTE_OVERRIDE;
private:
	void							MapGenerationAlgorithm		(Map2D *& pMap, const CShIdentifier & idLevel);
	bool							FindNextMapEntity			(int iRow, int iColumn, MapEntity & newMapEntity);

	bool							CanBePlacedHere				(const MapEntity & mapEntity, Map2D *& pMap, int iColumn, int iRow);
public:
	CShArray<MapEntity>				m_aMapEntity;
};
