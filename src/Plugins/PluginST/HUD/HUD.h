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
	void					Initialize			(void);
	void					Release				(void);

	//
	// Show/Hide
	void					Toggle				(void);
	void					Show				(void);
	void					Hide				(void);

private:
	//
	// Root container
	ShGUIControlBranch *	m_pControlBranchHUD;
	ShGUIControlBranch *	m_pControlBranchHearts;
};
