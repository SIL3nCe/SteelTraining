#pragma once

#include "ShSDK/ShSDK.h"
#include "Map.h"

#define MAP_DEFAULT_ROW_NB 50
#define MAP_DEFAULT_COLUMN_NB 50
#define MAP_DEFAULT_TILE_SIZE 20

class Map2D : public Map
{
public:
	friend class MapGeneratorTest;
	friend class PluginMapGenerator;
	
	struct Tile
	{
		explicit	Tile		(void)	: iRepresentation(0), pEntity2(shNULL)	{}
		
		void		Initialize	(shU32 iRepresentation, const CShIdentifier & idLevel, ShSprite * pSprite, shU32 iRowIndex, shU32 iColumnIndex, shU32 iTileSize)
		{
			CShIdentifier idTile(CShString("tile_") + CShString::FromInt(iRowIndex) + CShString("x") + CShString::FromInt(iColumnIndex));
			pEntity2 = ShEntity2::Create(idLevel, idTile, CShIdentifier("layer_default"), pSprite, CShVector3(iColumnIndex * iTileSize, iRowIndex * iTileSize, 0.0f), CShEulerAngles::ZERO, CShVector3(1.0f, 1.0f, 1.0f));
		}

		void		Release		(void)
		{
			iRepresentation = 0;
			ShEntity2::Destroy(pEntity2);
		}

		shU32		iRepresentation;
	private:
		ShEntity2 *	pEntity2;
	};

	//
	// Constructor/Destructor
	explicit				Map2D			(void);
	virtual					~Map2D			(void);

	//
	// operators
	virtual explicit		operator bool	(void) const SH_ATTRIBUTE_OVERRIDE;

	//
	// Getters/Setters
	virtual EMapType		GetType			(void) const SH_ATTRIBUTE_OVERRIDE;
	shU32					GetRowNb		(void) const;
	shU32					GetColumnNb		(void) const;
	shU32					GetTileSize		(void) const;
	Map2D::Tile ** const	GetTiles		(void) const;
protected:
private:
	//
	// Initiale/Release
	bool					Initialize		(shU32 iRowNb, shU32 iColumnNb, shU32 iTileSize);
	bool					Release			(void);
private:

	shU32			m_iRow;
	shU32			m_iColumn;
	shU32			m_iTileSize;

	Map2D::Tile **	m_aaTiles;
};
