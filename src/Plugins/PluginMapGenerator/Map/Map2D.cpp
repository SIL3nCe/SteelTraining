#include "Map2D.h"

/**
* @brief Default constructor
*/
/*explicit*/ Map2D::Map2D(void)
: Map()
, m_iRow(0)
, m_iColumn(0)
, m_mTiles()
, m_aMapEntity()
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ Map2D::~Map2D(void)
{
	// ...
}

/**
* @brief Map2D::Initialize
*/
bool Map2D::Initialize(shU32 iRowNb, shU32 iColumnNb)
{
	SH_ASSERT(0 != iRowNb);
	SH_ASSERT(0 != iColumnNb);

	if (0 == iRowNb || 0 == iColumnNb)
	{
		return false;
	}

	m_iRow = iRowNb;
	m_iColumn = iColumnNb;

	for (int nRow = 0; nRow < m_iRow; ++nRow)
	{
		m_mTiles.Add(CShArray<Tile*>());
		for (int nColumn = 0; nColumn < m_iColumn; ++nColumn)
		{
			Tile * pTile = new Tile();
			pTile->iRow = nRow;
			pTile->iColumn = nColumn;
			m_mTiles[nRow].Add(new Tile());
		}
	}

	return true;
}

/**
* @brief Map2D::Release
*/
bool Map2D::Release(void)
{
	m_iRow = 0;
	m_iColumn = 0;

	while (!m_mTiles.IsEmpty())
	{
		while (!m_mTiles[0].IsEmpty())
		{
			Tile * pTile = m_mTiles[0][0];
			SH_SAFE_DELETE(pTile);
			m_mTiles[0].Remove(0);
		}
		m_mTiles.Remove(0);
	}

	while (!m_aMapEntity.IsEmpty())
	{
		m_aMapEntity[0].Release();
		m_aMapEntity.Remove(0);
	}

	return true;
}

/**
* @brief Map2D::operator bool
*/
/*virtual explicit*/ Map2D::operator bool(void) const
{
	return m_mTiles.IsEmpty();
}

/**
* @brief Map2D::GetType
*/
/*virtual*/ EMapType Map2D::GetType(void) const
{
	return e_map_type_2d;
}

/**
* @brief Map2D::GetRowNb
*/
shU32 Map2D::GetRowCount(void) const
{
	return m_iRow;
}

/**
* @brief Map2D::GetColumnNb
*/
shU32 Map2D::GetColumnCount(void) const
{
	return m_iColumn;
}


/**
* @brief Map2D::GetTiles
*/
const CShArray<CShArray<Tile*>> & Map2D::GetTiles(void) const
{
	return m_mTiles;
}

/**
* @brief Map2D::GetTiles
*/
Tile * Map2D::GetTile(int nRow, int nColumn) const
{
	return m_mTiles[nRow][nColumn];
}

/**
* @brief
*/
void Map2D::AddWall(int iRowPosition, int iColumnPosition)
{
	m_mTiles[iRowPosition][iColumnPosition]->m_eTileType = ETileType::e_tile_wall;
}

/**
* @brief 
*/
void Map2D::AddMapEntity(const MapEntity & mapEntity, int iRowPosition, int iColumnPosition)
{
	if (mapEntity.m_mNeededTiles.IsEmpty()) return;
	int iRowCount = mapEntity.m_mNeededTiles.GetCount();
	for (int nRow = 0; nRow < iRowCount; ++nRow)
	{
		int iColumnCount = mapEntity.m_mNeededTiles[nRow].GetCount();
		for (int nColumn = 0; nColumn < iColumnCount; ++nColumn)
		{
			EMapEntityTileType eMapEntityTileType = mapEntity.m_mNeededTiles[nRow][nColumn];

			switch (eMapEntityTileType)
			{
			case EMapEntityTileType::e_map_entity_tile_type_block:
			{
				m_mTiles[nRow + iRowPosition][nColumn + iColumnPosition]->m_eTileType = ETileType::e_tile_block;
			}
			break;

			case EMapEntityTileType::e_map_entity_tile_type_area:
			{
				m_mTiles[nRow + iRowPosition][nColumn + iColumnPosition]->m_eTileType = ETileType::e_tile_entity_area;
			}
			break;

			case EMapEntityTileType::e_map_entity_tile_type_none:
			{
				// nothing
			}
			break;
			}
		}
	}
}
