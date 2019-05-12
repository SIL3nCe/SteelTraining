#pragma once

#include "ShSDK/ShSDK.h"

class PauseMenu
{
public:
	//
	// Constructor/Destructor
	explicit				PauseMenu				(void);
	virtual					~PauseMenu				(void);

	//
	// Initialize/Release
	virtual	void			Initialize				(void);
	virtual	void			Release					(void);

	//
	// Show/Hide
	void					Toggle					(void);
	void					Show					(void);
	void					Hide					(void);

	//
	// Getters/Setters
	bool					IsShown					(void) const;
	bool					IsHidden				(void) const;

protected:
private:
	//
	// GUI Signals
	static bool				OnButtonClickedSettings	(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedSave		(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedResume	(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedExit		(ShGUIControl * pControl, const CShVector2 & vPosition);
public:
protected:
private:
	//
	// Root container
	ShGUIControlBranch *	m_pControlBranchPauseMenu;

	//
	// Buttons PauseMenu
	ShGUIControlButton *	m_pControlButtonSettings;
	ShGUIControlButton *	m_pControlButtonSave;
	ShGUIControlButton *	m_pControlButtonResume;
	ShGUIControlButton *	m_pControlButtonExit;

};
