#include "ContactListener.h"

#include "../Object.h"
#include "../Projectile/Projectile.h"

/**
 * @brief Constructor
 */
ContactListener::ContactListener(void)
{
	// ...
}

/**
 * @brief Destructor
 */
ContactListener::~ContactListener(void)
{
	// ...
}

/**
 * @brief BeginContact
 */
void ContactListener::BeginContact(b2Contact* contact)
{
	Object * pDataFixtureA = static_cast<Object *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Object * pDataFixtureB = static_cast<Object *>(contact->GetFixtureB()->GetBody()->GetUserData());

	if (pDataFixtureA && EObjectType::projectile == pDataFixtureA->GetObjectType())
	{
		if (Projectile * pProj = static_cast<Projectile *>(pDataFixtureA))
		{
			pProj->OnHit(pDataFixtureB);
		}
	}

	if (pDataFixtureB && EObjectType::projectile == pDataFixtureB->GetObjectType())
	{
		if (Projectile * pProj = static_cast<Projectile*>(pDataFixtureB))
		{
			pProj->OnHit(pDataFixtureA);
		}
	}
}

/**
 * @brief EndContact
 */
void ContactListener::EndContact(b2Contact* contact) 
{
	// Do smthg
}
