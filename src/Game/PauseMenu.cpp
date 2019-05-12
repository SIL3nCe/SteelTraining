#include "PauseMenu.h"

#include "GameStateManager.h"
#include "Game.h"

const CShString		g_strGUIPauseMenu			("ingame_pause");
const CShIdentifier	g_idGUIPauseMenu			(g_strGUIPauseMenu);
const CShIdentifier	g_idGUIContainerPauseMenu	("container_ingame_pause_background");

/**
* @brief Constructor
*/
/*explicit*/ PauseMenu::PauseMenu(void)
: m_pControlBranchPauseMenu(shNULL)
, m_pControlButtonSettings(shNULL)
, m_pControlButtonSave(shNULL)
, m_pControlButtonResume(shNULL)
, m_pControlButtonExit(shNULL)
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ PauseMenu::~PauseMenu(void)
{
	// ...
}

/**
* @brief Initialize
*/
void PauseMenu::Initialize(void)
{
	//
	// Load GUI
	bool bLoaded = ShGUI::LoadGUIAndSSS(g_idGUIPauseMenu, ShGUI::GetRootControl(), g_strGUIPauseMenu);
	SH_ASSERT(bLoaded)

	//
	// Retrieve Controls
	m_pControlBranchPauseMenu = static_cast<ShGUIControlBranch*>(ShGUIControl::GetElementById(g_idGUIContainerPauseMenu.Append(g_strGUIPauseMenu.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pControlBranchPauseMenu)

	m_pControlButtonSettings	 = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_settings").Append(g_strGUIPauseMenu.Get()), m_pControlBranchPauseMenu));
	m_pControlButtonSave		 = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_save").Append(g_strGUIPauseMenu.Get()), m_pControlBranchPauseMenu));
	m_pControlButtonResume		 = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_resume").Append(g_strGUIPauseMenu.Get()), m_pControlBranchPauseMenu));
	m_pControlButtonExit		 = static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_exit").Append(g_strGUIPauseMenu.Get()), m_pControlBranchPauseMenu));
	SH_ASSERT(shNULL != m_pControlButtonSettings)
	SH_ASSERT(shNULL != m_pControlButtonSave)
	SH_ASSERT(shNULL != m_pControlButtonResume)
	SH_ASSERT(shNULL != m_pControlButtonExit)

	//
	// Set-up
	ShGUIControl::Hide(m_pControlBranchPauseMenu);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonSettings,	PauseMenu::OnButtonClickedSettings);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonSave,		PauseMenu::OnButtonClickedSave);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonResume,		PauseMenu::OnButtonClickedResume);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonExit,		PauseMenu::OnButtonClickedExit);
}

/**
* @brief Release
*/
void PauseMenu::Release(void)
{
	ShGUIControl::Destroy(m_pControlBranchPauseMenu);
	m_pControlBranchPauseMenu = shNULL;
}

/**
* @brief Toggle
*/
void PauseMenu::Toggle(void)
{
	if (ShGUIControl::IsShown(m_pControlBranchPauseMenu))	{	ShGUIControl::Hide(m_pControlBranchPauseMenu);	}
	else													{	ShGUIControl::Show(m_pControlBranchPauseMenu);	}
}

/**
* @brief Show
*/
void PauseMenu::Show(void)
{
	ShGUIControl::Show(m_pControlBranchPauseMenu);
}

/**
* @brief Hide
*/
void PauseMenu::Hide(void)
{
	ShGUIControl::Hide(m_pControlBranchPauseMenu);
}

/**
* @brief IsShown
*/
bool PauseMenu::IsShown(void) const
{
	return ShGUIControl::IsShown(m_pControlBranchPauseMenu);
}

/**
* @brief IsHidden
*/
bool PauseMenu::IsHidden(void) const
{
	return ShGUIControl::IsHidden(m_pControlBranchPauseMenu);
}

/**
* @brief OnButtonClickedSettings
*/
/*static*/ bool PauseMenu::OnButtonClickedSettings(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);

	// TODO

	return true;
}

/**
* @brief OnButtonClickedSave
*/
/*static*/ bool PauseMenu::OnButtonClickedSave(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);

	// TODO

	return true;
}

/**
* @brief OnButtonClickedExit
*/
/*static*/ bool PauseMenu::OnButtonClickedExit(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);

	//
	// Pop current GameState
	GameStateManager::GetInstance()->RequestPop();

	return true;
}

/**
* @brief OnButtonClickedResume
*/
/*static*/ bool PauseMenu::OnButtonClickedResume(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	SH_UNUSED(pControl);
	SH_UNUSED(vPosition);

	Game::GetInstance()->UnPause();

	return true;
}