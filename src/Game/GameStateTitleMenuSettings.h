#pragma once

#include <ShSDK/ShSDK.h>

#include "GameState.h"

class GameStateTitleMenuSettings : public GameState
{
	friend class GameStateManager;
public:
	//
	// Constructor/Destructor
	explicit				GameStateTitleMenuSettings					(void);
	virtual					~GameStateTitleMenuSettings					(void);

	//
	// Initialize/Release
	virtual void			InternalInitialize							(void) SH_ATTRIBUTE_OVERRIDE;
	virtual void			InternalRelease								(void) SH_ATTRIBUTE_OVERRIDE;

	//
	// Activate/Deactivate
	virtual void			InternalActivate							(void) SH_ATTRIBUTE_OVERRIDE;
	virtual void			InternalDeactivate							(void) SH_ATTRIBUTE_OVERRIDE;

	//
	// Update
	virtual void			InternalUpdate								(float dt) SH_ATTRIBUTE_OVERRIDE;

	//
	// Buttons signals
	static bool				OnButtonClickedChangeDifficultyToEasy		(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedChangeDifficultyToMedium		(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedChangeDifficultyToHard		(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedChangeDifficultyToHardcore	(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedResetToDefaults				(ShGUIControl * pControl, const CShVector2 & vPosition);
	static bool				OnButtonClickedBack							(ShGUIControl * pControl, const CShVector2 & vPosition);

protected:
private:

public:
	static CShString		s_strGUIGameStateTitleMenuSettings;		///< @todo comment
	static CShIdentifier	s_idGUIGameStateTitleMenuSettings;		///< @todo comment
protected:
private:
	//
	// Root container of the GUI file
	ShGUIControlBranch *	m_pControlBranchRoot;

	//
	// Difficulty
	ShGUIControlButton *	m_pControlButtonDifficultyEasy;
	ShGUIControlButton *	m_pControlButtonDifficultyMedium;
	ShGUIControlButton *	m_pControlButtonDifficultyHard;
	ShGUIControlButton *	m_pControlButtonDifficultyHardcore;

	//
	// Bottom buttons
	ShGUIControlButton *	m_pControlButtonResetToDefaults;
	ShGUIControlButton *	m_pControlButtonBack;
};