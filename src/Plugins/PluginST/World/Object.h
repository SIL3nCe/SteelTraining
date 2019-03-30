#pragma once

class Object
{
public:

	enum class EType
	{
		wall,
		character,
		player,
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
	virtual EType		GetObjectType		(void) const = 0;
};
