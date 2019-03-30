#include "Map2D.h"

/**
* @brief Default constructor
*/
/*explicit*/ Map2D::Map2D(void)
: Map()
, m_iRow(0)
, m_iColumn(0)
, m_iTileSize(0)
, m_mTiles()
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
shU32 Map2D::GetRowNb(void) const
{
	return m_iRow;
}

/**
* @brief Map2D::GetColumnNb
*/
shU32 Map2D::GetColumnNb(void) const
{
	return m_iColumn;
}

/**
* @brief Map2D::GetTileSize
*/
shU32 Map2D::GetTileSize(void) const
{
	return m_iTileSize;
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
* @brief Map2D::Initialize
*/
bool Map2D::Initialize(shU32 iRowNb, shU32 iColumnNb, shU32 iTileSize)
{
	SH_ASSERT(0 != iRowNb);
	SH_ASSERT(0 != iColumnNb);
	SH_ASSERT(0 != iTileSize);
	
	if (0 == iRowNb || 0 == iColumnNb || 0 == iTileSize)
	{
		return false;
	}

	m_iRow		= iRowNb;
	m_iColumn	= iColumnNb;
	m_iTileSize	= iTileSize;

	m_aaTiles = static_cast<Tile**>(shMalloc(m_iRow * sizeof(Tile*)));
	for (int iRowIndex = 0; iRowIndex < m_iRow; ++iRowIndex)
	{
		m_aaTiles[iRowIndex] = static_cast<Tile*>(shMalloc(m_iColumn * sizeof(Tile)));
	}

	return true;
}

/**
* @brief Map2D::Release
*/
bool Map2D::Release(void)
{
	m_iRow		= 0;
	m_iColumn	= 0;
	m_iTileSize	= 0;

	for (int iRowIndex = 0; iRowIndex < m_iRow; ++iRowIndex)
	{
		SH_SAFE_RELEASE_FREE(m_aaTiles[iRowIndex]);
	}
	SH_SAFE_FREE(m_aaTiles);

	return true;
}