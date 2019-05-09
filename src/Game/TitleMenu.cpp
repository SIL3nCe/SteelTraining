//--------------------------------------------------------------------------------------------------
/// TitleMenu.cpp
//--------------------------------------------------------------------------------------------------

#include "TitleMenu.h"

#include "Game.h"

//--------------------------------------------------------------------------------------------------
/// Static definitions
//--------------------------------------------------------------------------------------------------
/*static*/ CShString		TitleMenu::s_strGUITitleMenu("menu_title");
/*static*/ CShIdentifier	TitleMenu::s_idGUITitleMenu(s_strGUITitleMenu);

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
TitleMenu * TitleMenu::GetInstance(void)
{
	static TitleMenu * pInstance = shNULL;
	if (shNULL == pInstance)
	{
		pInstance = new TitleMenu();
	}

	return pInstance;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void TitleMenu::Initialize(void)
{
	//
	// GUI Loading
	if (!ShGUI::LoadGUIAndSSS(s_idGUITitleMenu, ShGUI::GetRootControl(), s_strGUITitleMenu))
	{
		SH_ASSERT_ALWAYS();
	}

	//
	// Retrieval
	m_pControlBranchBackground = static_cast<ShGUIControlBranch*>(ShGUIControl::GetElementById(CShIdentifier("container_background").Append(s_strGUITitleMenu.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pControlBranchBackground)
		
	m_pControlButtonPlay		= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_play").Append(s_strGUITitleMenu.Get()), m_pControlBranchBackground));
	m_pControlButtonSettings	= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_settings").Append(s_strGUITitleMenu.Get()), m_pControlBranchBackground));
	m_pControlButtonExit		= static_cast<ShGUIControlButton*>(ShGUIControl::GetElementById(CShIdentifier("button_exit").Append(s_strGUITitleMenu.Get()), m_pControlBranchBackground));
	SH_ASSERT(shNULL != m_pControlButtonPlay)
	SH_ASSERT(shNULL != m_pControlButtonSettings)
	SH_ASSERT(shNULL != m_pControlButtonExit)

	//
	// Set-up
	ShGUIControl::Hide(m_pControlBranchBackground);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonPlay,		TitleMenu::OnButtonClickedPlay);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonSettings,	TitleMenu::OnButtonClickedSettings);
	ShGUIControl::AddSignalFctPtrClick(m_pControlButtonExit,		TitleMenu::OnButtonClickedExit);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void TitleMenu::Release(void)
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
void TitleMenu::Activate(void)
{
	ShGUIControl::Show(m_pControlBranchBackground);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void TitleMenu::Deactivate(void)
{
	ShGUIControl::Hide(m_pControlBranchBackground);
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
void TitleMenu::Update(float dt)
{
	// ...
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool TitleMenu::OnButtonClickedPlay(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	//
	// Deactivate TitleMenu
	TitleMenu::GetInstance()->Deactivate();

	//
	// Initialize Game
	Game::GetInstance()->Initialize();

	return true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool TitleMenu::OnButtonClickedSettings(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	// TODO
	return false;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*static*/ bool TitleMenu::OnButtonClickedExit(ShGUIControl * pControl, const CShVector2 & vPosition)
{
	ShApplication::RequestQuit();
	return true;
}

//--------------------------------------------------------------------------------------------------
/// @todo comment
//--------------------------------------------------------------------------------------------------
/*explicit*/ TitleMenu::TitleMenu(void)
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
/*virtual*/ TitleMenu::~TitleMenu(void)
{
	// ...
}