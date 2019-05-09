#pragma once

#include <ShSDK/ShSDK.h>

class TitleMenu
{
public:
	//
	// Singleton-related
	static TitleMenu *		GetInstance					(void);

	//
	// Initialize/Release
	void					Initialize					(void);
	void					Release						(void);

	//
	// Activate/Deactivate
	void					Activate					(void);
	void					Deactivate					(void);

	//
	// Update
	void					Update						(float dt);

	//
	// Buttons signals
	static bool				OnButtonClickedPlay			(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedSettings		(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedExit			(ShGUIControl * pControl, const CShVector2 & vPosition);

protected:
private:
	//
	// Constructor/Destructor
	explicit				TitleMenu					(void);
	virtual					~TitleMenu					(void);

public:
	static CShString		s_strGUITitleMenu;		///< @todo comment
	static CShIdentifier	s_idGUITitleMenu;		///< @todo comment
protected:
private:
	//
	// GUI
	ShGUIControlBranch *	m_pControlBranchBackground;
	ShGUIControlButton *	m_pControlButtonPlay;
	ShGUIControlButton *	m_pControlButtonSettings;
	ShGUIControlButton *	m_pControlButtonExit;
};