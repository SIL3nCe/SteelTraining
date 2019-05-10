//--------------------------------------------------------------------------------------------------
/// GameStateTitleMenuSettings.cpp
//--------------------------------------------------------------------------------------------------

#include "GameStateTitleMenuSettings.h"

#include "GameStateManager.h"

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
	m_pControlBranchRoot			= shNULL;
	m_pControlButtonResetToDefaults	= shNULL;
	m_pControlButtonBack			= shNULL;
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
	// ...
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenuSettings::OnButtonClickedResetToDefaults(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	// TODO

	return true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenuSettings::OnButtonClickedBack(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	//
	// Pop current GameState
	GameStateManager::GetInstance()->Pop();

	return true;
}