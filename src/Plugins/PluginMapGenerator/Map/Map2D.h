#pragma once

#include "ShSDK/ShSDK.h"
#include "Map.h"

#define MAP_DEFAULT_ROW_NB 50
#define MAP_DEFAULT_COLUMN_NB 50
#define MAP_DEFAULT_TILE_SIZE 20

enum ETileType
{
	e_tile_block,
	e_tile_wall,
	e_tile_void,
	e_tile_ground,
};

struct Tile
{
	int			iRow;
	int			iColumn;
	ETileType	m_eTileType;
};

class Map2D : public Map
{
public:
	friend class MapGeneratorTest;
	friend class PluginMapGenerator;

	

	//
	// Constructor/Destructor
	explicit				Map2D			(void);
	virtual					~Map2D			(void);

	//
	// operators
	virtual explicit		operator bool	(void) const SH_ATTRIBUTE_OVERRIDE;

	//
	// Getters/Setters
	virtual EMapType					GetType			(void) const SH_ATTRIBUTE_OVERRIDE;
	shU32								GetRowCount		(void) const;
	shU32								GetColumnCount		(void) const;
	shU32								GetTileSize		(void) const;
	const CShArray<CShArray<Tile*>> &	GetTiles		(void) const;
	Tile*								GetTile			(int nRow, int nColumn) const;
protected:
private:
	//
	// Initiale/Release
	bool					Initialize		(shU32 iRowNb, shU32 iColumnNb, shU32 iTileSize);
	bool					Release			(void);
private:

	shU32						m_iRow;
	shU32						m_iColumn;
	shU32						m_iTileSize;

	CShArray< CShArray<Tile*>>	m_mTiles;
};
