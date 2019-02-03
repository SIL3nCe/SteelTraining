#pragma once

enum EMapType
{
	e_map_type_2d,
	e_map_type_3d,
};

class Map
{
public:
	explicit			Map				(void);
	virtual				~Map			(void);

	//
	// Release
	virtual bool		Release			(void) = 0;

	//
	// Operators
	virtual explicit	operator bool	(void) const = 0;

	virtual EMapType	GetType			(void) const = 0;

private:

};
