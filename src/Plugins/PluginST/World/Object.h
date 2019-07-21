#pragma once

// If too much types for ushort, create another enum for b2 categories
enum class EObjectType : unsigned short
{
	wall = 1,
	character = 2,
	player = 4,
	projectile = 8,

	max
};

class Object
{
public:

	//
	// Constructor / Destructor
						Object				(void);
	virtual				~Object				(void);

	virtual	void		Release				(void);

	//
	// Update
	virtual	void		Update				(float dt) = 0;

	//
	// Getters
	virtual EObjectType		GetObjectType	(void) const = 0;
};
