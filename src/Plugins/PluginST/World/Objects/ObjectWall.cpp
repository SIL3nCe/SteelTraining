#include "ObjectWall.h"

/**
 * @brief Constructor
 */
ObjectWall::ObjectWall(void)
: Object()
, m_pBody(shNULL)
{
	// ...
}

/**
 * @brief Destructor
 */
ObjectWall::~ObjectWall(void)
{
	// ...
}

/**
 * @brief Initialize
 * @param pUser
 */
void ObjectWall::Initialize()
{
}

/**
 * @brief Release
 */
void ObjectWall::Release(void)
{
	m_pBody = shNULL;
}

/**
 * @brief Update
 */
void ObjectWall::Update(float dt)
{
}

/**
 * @brief GetObjectType
 */
Object::EType ObjectWall::GetObjectType(void) const
{
	return EType::wall;
}
