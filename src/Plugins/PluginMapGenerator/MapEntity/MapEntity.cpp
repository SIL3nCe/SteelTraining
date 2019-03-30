#include "MapEntity.h"

/**
* @brief Constructor
*/
/*explicit*/ MapEntity::MapEntity(void)
: m_eMapEntityType()
, m_iWidth(0)
, m_iHeight(0)
, m_iOccurenceChance(0)
, m_mNeededTiles()
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ MapEntity::~MapEntity(void)
{
	// ...
}
/**
* @brief Destructor
*/
void MapEntity::Initialize(EMapEntityType eMapEntityType, int iWidth, int iHeight, int iOccurenceChance, const CShArray<CShArray<EMapEntityTileType>> & mNeededTiles)
{
	m_eMapEntityType = eMapEntityType;
	m_iWidth = iWidth;
	m_iHeight = iHeight;
	m_iOccurenceChance = iOccurenceChance;
	m_mNeededTiles = mNeededTiles;
}

/**
* @brief Destructor
*/
void MapEntity::Release(void)
{
	
}
