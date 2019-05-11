#pragma once

#include <ShSDK/ShSDK.h>

class Settings
{
public:
	enum EDifficulty
	{
		e_difficulty_easy		= 0,
		e_difficulty_medium		= 1,
		e_difficulty_hard		= 2,
		e_difficulty_hardcore	= 3,

		e_difficulty_max		= e_difficulty_hardcore + 1,
	};

protected:
private:
	//
	// Constructor/Destructor
	explicit					Settings			(void);
	virtual						~Settings			(void);

public:
	static EDifficulty			s_eDifficulty;

protected:
private:
};