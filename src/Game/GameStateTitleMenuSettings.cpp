//--------------------------------------------------------------------------------------------------
/// GameStateTitleMenuSettings.cpp
//--------------------------------------------------------------------------------------------------

#include "GameStateTitleMenuSettings.h"

#include "GameStateManager.h"
#include "Settings.h"

//--------------------------------------------------------------------------------------------------
/// Static definitions
//--------------------------------------------------------------------------------------------------
/*static*/ CShString		GameStateTitleMenuSettings::s_strGUIGameStateTitleMenuSettings("menu_title_settings");
/*static*/ CShIdentifier	GameStateTitleMenuSettings::s_idGUIGameStateTitleMenuSettings(s_strGUIGameStateTitleMenuSettings);

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameStateTitleMenuSettings::GameStateTitleMenuSettings(void)
: m_pControlBranchRoot(shNULL)
, m_pControlButtonDifficultyEasy(shNULL)
, m_pControlButtonDifficultyMedium(shNULL)
, m_pControlButtonDifficultyHard(shNULL)
, m_pControlButtonDifficultyHardcore(shNULL)
, m_pControlButtonResetToDefaults(shNULL)
, m_pControlButtonBack(shNULL)
{
	// ...
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameStateTitleMenuSettings::~GameStateTitleMenuSettings(void)
{
	// ...
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateTitleMenuSettings::InternalInitialize(void)
{
	//
	// Set GameState id
	m_id = CShIdentifier("game_state_title_menu_settings");

	//
	// GUI Loading
	if (!ShGUI::LoadGUIAndSSS(s_idGUIGameStateTitleMenuSettings, ShGUI::GetRootControl(), s_strGUIGameStateTitleMenuSettings))
	{
		SH_ASSERT_ALWAYS();
	}

	//
	// Retrieval
	m_pControlBranchRoot = static_cast<ShGUIControlBranch*>(ShGUIControl::GetElementById(CShIdentifier("container_settings").Append(s_strGUIGameStateTitleMenuSettings.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pControlBranchRoot)
	
	m_pControlButtonDifficultyEasy		= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_difficulty_easy").Append("import_difficulty").Append(s_strGUIGameStateTitleMenuSettings.Get()), m_pControlBranchRoot));
	m_pControlButtonDifficultyMedium	= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_difficulty_medium").Append("import_difficulty").Append(s_strGUIGameStateTitleMenuSettings.Get()), m_pControlBranchRoot));
	m_pControlButtonDifficultyHard		= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_difficulty_hard").Append("import_difficulty").Append(s_strGUIGameStateTitleMenuSettings.Get()), m_pControlBranchRoot));
	m_pControlButtonDifficultyHardcore	= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_difficulty_hardcore").Append("import_difficulty").Append(s_strGUIGameStateTitleMenuSettings.Get()), m_pControlBranchRoot));
	SH_ASSERT(shNULL != m_pControlButtonDifficultyEasy)
	SH_ASSERT(shNULL != m_pControlButtonDifficultyMedium)
	SH_ASSERT(shNULL != m_pControlButtonDifficultyHard)
	SH_ASSERT(shNULL != m_pControlButtonDifficultyHardcore)
		
	m_pControlButtonResetToDefaults	= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_default").Append(s_strGUIGameStateTitleMenuSettings.Get()), m_pControlBranchRoot));
	m_pControlButtonBack			= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_back").Append(s_strGUIGameStateTitleMenuSettings.Get()), m_pControlBranchRoot));
	SH_ASSERT(shNULL != m_pControlButtonResetToDefaults)
	SH_ASSERT(shNULL != m_pControlButtonBack)

	//
	// Set-up
	ShGUIControl::Hide(m_pControlBranchRoot);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonResetToDefaults,	GameStateTitleMenuSettings::OnButtonClickedResetToDefaults);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonBack,			GameStateTitleMenuSettings::OnButtonClickedBack);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateTitleMenuSettings::InternalRelease(void)
{
	//
	// Remove top container
	ShGUIControl::Destroy(m_pControlBranchRoot);
	m_pControlBranchRoot				= shNULL;
	m_pControlButtonDifficultyEasy		= shNULL;
	m_pControlButtonDifficultyMedium	= shNULL;
	m_pControlButtonDifficultyHard		= shNULL;
	m_pControlButtonDifficultyHardcore	= shNULL;
	m_pControlButtonResetToDefaults		= shNULL;
	m_pControlButtonBack				= shNULL;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateTitleMenuSettings::InternalActivate(void)
{
	ShGUIControl::Show(m_pControlBranchRoot);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateTitleMenuSettings::InternalDeactivate(void)
{
	ShGUIControl::Hide(m_pControlBranchRoot);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateTitleMenuSettings::InternalUpdate(float dt)
{
	SH_UNUSED(dt);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenuSettings::OnButtonClickedChangeDifficultyToEasy(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(vPosition);

	//
	// Set difficulty
	Settings::s_eDifficulty = Settings::e_difficulty_easy;

	//
	// Update GUI
	GameStateTitleMenuSettings * pGameStateTitleMenuSettings = static_cast<GameStateTitleMenuSettings*>(GameStateManager::GetInstance()->GetTop());
	if (!ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyEasy))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyEasy);
	}
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyMedium))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyMedium);
	}
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHard))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHard);
	}
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHardcore))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHardcore);
	}

	return true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenuSettings::OnButtonClickedChangeDifficultyToMedium(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(vPosition);

	//
	// Set difficulty
	Settings::s_eDifficulty = Settings::e_difficulty_medium;

	//
	// Update GUI
	GameStateTitleMenuSettings * pGameStateTitleMenuSettings = static_cast<GameStateTitleMenuSettings*>(GameStateManager::GetInstance()->GetTop());
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyEasy))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyEasy);
	}
	if (!ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyMedium))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyMedium);
	}
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHard))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHard);
	}
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHardcore))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHardcore);
	}

	return true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenuSettings::OnButtonClickedChangeDifficultyToHard(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(vPosition);

	//
	// Set difficulty
	Settings::s_eDifficulty = Settings::e_difficulty_hard;

	//
	// Update GUI
	GameStateTitleMenuSettings * pGameStateTitleMenuSettings = static_cast<GameStateTitleMenuSettings*>(GameStateManager::GetInstance()->GetTop());
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyEasy))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyEasy);
	}
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyMedium))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyMedium);
	}
	if (!ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHard))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHard);
	}
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHardcore))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHardcore);
	}

	return true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenuSettings::OnButtonClickedChangeDifficultyToHardcore(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(vPosition);

	//
	// Set difficulty
	Settings::s_eDifficulty = Settings::e_difficulty_hardcore;

	//
	// Update GUI
	GameStateTitleMenuSettings * pGameStateTitleMenuSettings = static_cast<GameStateTitleMenuSettings*>(GameStateManager::GetInstance()->GetTop());
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyEasy))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyEasy);
	}
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyMedium))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyMedium);
	}
	if (ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHard))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHard);
	}
	if (!ShGUIControlButton::IsSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHardcore))
	{
		ShGUIControlButton::SwitchSelected(pGameStateTitleMenuSettings->m_pControlButtonDifficultyHardcore);
	}

	return true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenuSettings::OnButtonClickedResetToDefaults(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(vPosition);

	// TODO

	return true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenuSettings::OnButtonClickedBack(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(vPosition);

	//
	// Pop current GameState
	GameStateManager::GetInstance()->Pop();

	return true;
}