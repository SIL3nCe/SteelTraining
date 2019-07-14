#pragma once

class Object
{
public:

	enum class EObjectType
	{
		wall,
		character,
		player,
		projectile,

		max
	};

	//
	// Constructor / Destructor
						Object				(void);
	virtual				~Object				(void);

	//
	// Update
	virtual	void		Update				(float dt) = 0;

	//
	// Getters
	virtual EObjectType		GetObjectType	(void) const = 0;
};
