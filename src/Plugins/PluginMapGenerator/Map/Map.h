#pragma once

enum EMapType
{
	e_map_type_2d,
	e_map_type_3d,
};

class Map
{
public:
	explicit			Map		(void);
	virtual				~Map	(void);

	virtual EMapType	GetType	(void) const = 0;

private:

};
