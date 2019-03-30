#pragma once

class MapEntityWall
{
public:
	explicit			MapEntityWall				(void);
	virtual				~MapEntityWall			(void);

	//
	// Release
	virtual bool		Release			(void) = 0;

	//
	// Operators
	virtual explicit	operator bool	(void) const = 0;

	virtual EMapEntityWallType	GetType			(void) const = 0;

private:

};
