#pragma once

#include "ShSDK/ShSDK.h"

enum EMapEntityType
{
	e_map_entity_type_static_object,
	e_map_entity_type_dynamic_object,
	e_map_entity_type_pickable_object,
	e_map_entity_type_trap,
};

enum EMapEntityTileType
{
	e_map_entity_tile_type_block,
	e_map_entity_tile_type_area,
	e_map_entity_tile_type_none,
};

class MapEntity
{
public:
	explicit							MapEntity			(void);
	virtual								~MapEntity			(void);

	//
	// Release
	void								Initialize			(EMapEntityType eMapEntityType, int iWidth, int iHeight, int iOccurenceChance, const CShArray<CShArray<EMapEntityTileType>> & mNeededTiles);
	void								Release				(void);

public:
	EMapEntityType									m_eMapEntityType;

	int												m_iWidth;
	int												m_iHeight;

	int												m_iOccurenceChance;

	CShArray<CShArray<EMapEntityTileType>>			m_mNeededTiles;
};
