//--------------------------------------------------------------------------------------------------
/// GameStateTitleMenu.cpp
//--------------------------------------------------------------------------------------------------

#include "GameStateTitleMenu.h"

#include "GameStateManager.h"

//--------------------------------------------------------------------------------------------------
/// Static definitions
//--------------------------------------------------------------------------------------------------
/*static*/ CShString		GameStateTitleMenu::s_strGUIGameStateTitleMenu("menu_title");
/*static*/ CShIdentifier	GameStateTitleMenu::s_idGUIGameStateTitleMenu(s_strGUIGameStateTitleMenu);

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ GameStateTitleMenu::GameStateTitleMenu(void)
: m_pControlBranchBackground(shNULL)
, m_pControlButtonPlay(shNULL)
, m_pControlButtonSettings(shNULL)
, m_pControlButtonExit(shNULL)
{
	// ...
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ GameStateTitleMenu::~GameStateTitleMenu(void)
{
	// ...
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateTitleMenu::InternalInitialize(void)
{
	//
	// Set GameState id
	m_id = CShIdentifier("game_state_title_menu");

	//
	// GUI Loading
	if (!ShGUI::LoadGUIAndSSS(s_idGUIGameStateTitleMenu, ShGUI::GetRootControl(), s_strGUIGameStateTitleMenu))
	{
		SH_ASSERT_ALWAYS();
	}

	//
	// Retrieval
	m_pControlBranchBackground = static_cast<ShGUIControlBranch*>(ShGUIControl::GetElementById(CShIdentifier("container_background").Append(s_strGUIGameStateTitleMenu.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pControlBranchBackground)
		
	m_pControlButtonPlay		= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_play").Append(s_strGUIGameStateTitleMenu.Get()), m_pControlBranchBackground));
	m_pControlButtonSettings	= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_settings").Append(s_strGUIGameStateTitleMenu.Get()), m_pControlBranchBackground));
	m_pControlButtonExit		= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_exit").Append(s_strGUIGameStateTitleMenu.Get()), m_pControlBranchBackground));
	SH_ASSERT(shNULL != m_pControlButtonPlay)
	SH_ASSERT(shNULL != m_pControlButtonSettings)
	SH_ASSERT(shNULL != m_pControlButtonExit)

	//
	// Set-up
	ShGUIControl::Hide(m_pControlBranchBackground);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonPlay,		GameStateTitleMenu::OnButtonClickedPlay);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonSettings,	GameStateTitleMenu::OnButtonClickedSettings);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonExit,		GameStateTitleMenu::OnButtonClickedExit);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateTitleMenu::InternalRelease(void)
{
	//
	// Remove top container
	ShGUIControl::Destroy(m_pControlBranchBackground);
	m_pControlBranchBackground	= shNULL;
	m_pControlButtonPlay		= shNULL;
	m_pControlButtonSettings	= shNULL;
	m_pControlButtonExit		= shNULL;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateTitleMenu::InternalActivate(void)
{
	ShGUIControl::Show(m_pControlBranchBackground);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateTitleMenu::InternalDeactivate(void)
{
	ShGUIControl::Hide(m_pControlBranchBackground);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*virtual*/ void GameStateTitleMenu::InternalUpdate(float dt)
{
	// ...
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenu::OnButtonClickedPlay(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	//
	// Push GameStateGame
	//GameStateManager::GetInstance()->Push(GameStateManager::e_game_state_game);

	return true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenu::OnButtonClickedSettings(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	//
	// Push GameStateTitleMenuSettings
	GameStateManager::GetInstance()->Push(GameStateManager::e_game_state_title_menu_settings);

	return true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool GameStateTitleMenu::OnButtonClickedExit(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	ShApplication::RequestQuit();

	return true;
}