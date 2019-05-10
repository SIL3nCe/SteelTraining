#pragma once

#include <ShSDK/ShSDK.h>

#include "GameState.h"

class GameStateTitleMenu : public GameState
{
	friend class GameStateManager;
public:
	//
	// Constructor/Destructor
	explicit				GameStateTitleMenu			(void);
	virtual					~GameStateTitleMenu			(void);

	//
	// Initialize/Release
	virtual void			InternalInitialize			(void) SH_ATTRIBUTE_OVERRIDE;
	virtual void			InternalRelease				(void) SH_ATTRIBUTE_OVERRIDE;

	//
	// Activate/Deactivate
	virtual void			InternalActivate			(void) SH_ATTRIBUTE_OVERRIDE;
	virtual void			InternalDeactivate			(void) SH_ATTRIBUTE_OVERRIDE;

	//
	// Update
	virtual void			InternalUpdate				(float dt) SH_ATTRIBUTE_OVERRIDE;

	//
	// Buttons signals
	static bool				OnButtonClickedPlay			(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedSettings		(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedExit			(ShGUIControl * pControl, const CShVector2 & vPosition);

protected:
private:

public:
	static CShString		s_strGUIGameStateTitleMenu;		///< @todo comment
	static CShIdentifier	s_idGUIGameStateTitleMenu;		///< @todo comment
protected:
private:
	//
	// GUI
	ShGUIControlBranch *	m_pControlBranchBackground;
	ShGUIControlButton *	m_pControlButtonPlay;
	ShGUIControlButton *	m_pControlButtonSettings;
	ShGUIControlButton *	m_pControlButtonExit;
};