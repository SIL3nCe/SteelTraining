#pragma once

#include "ShSDK/ShSDK.h"

class HUD
{
public:
	//
	// Constructor/Destructor
	explicit				HUD					(void);
	virtual					~HUD				(void);

	//
	// Initialize/Release
	virtual	void			Initialize			(void);
	virtual	void			Release				(void);

private:
	//
	// Root container
	ShGUIControlBranch *	m_pControlBranchHUD;
public:
	bool					m_bRequestToStop;
};
