#include "HUD.h"

const CShString		g_strGUIHUD				("hud");
const CShIdentifier	g_idGUIHUD				(g_strGUIHUD);
const CShIdentifier	g_idGUIContainerHUD		("container_hud");
const CShIdentifier	g_idGUIContainerHearts	("container_hearts");

const CShString		g_strGUIImageHeart		("image_heart");
const CShIdentifier	g_idGUIImageHeart		(g_strGUIImageHeart);

/**
* @brief Constructor
*/
/*explicit*/ HUD::HUD(void)
: m_pControlBranchHUD(shNULL)
, m_pControlBranchHearts(shNULL)
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ HUD::~HUD(void)
{
	// ...
}

/**
* @brief Initialize
*/
void HUD::Initialize(void)
{
	//
	// Load GUI
	bool bLoaded = ShGUI::LoadGUIAndSSS(g_idGUIHUD, ShGUI::GetRootControl(), g_strGUIHUD);
	SH_ASSERT(bLoaded)

	//
	// Retrieve Controls
	m_pControlBranchHUD = static_cast<ShGUIControlBranch*>(ShGUIControl::GetElementById(g_idGUIContainerHUD.Append(g_strGUIHUD.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pControlBranchHUD)

	m_pControlBranchHearts = static_cast<ShGUIControlBranch*>(ShGUIControl::GetElementById(g_idGUIContainerHearts.Append(g_strGUIHUD.Get()), ShGUI::GetRootControl()));
	SH_ASSERT(shNULL != m_pControlBranchHearts)

	//
	// Set-up
	const int iHeartCount = 5; // TODO : set relative to difficulty - depends on Plugin args
	for (int iHeartIndex = 0; iHeartIndex < iHeartCount; ++iHeartIndex)
	{
		bool bLoaded = ShGUI::LoadGUIAndSSS(g_idGUIImageHeart, m_pControlBranchHearts, CShString(g_strGUIImageHeart + CShString::FromInt(iHeartIndex)));
		SH_ASSERT(bLoaded)
	}
}

/**
* @brief Release
*/
void HUD::Release(void)
{
	ShGUIControl::Destroy(m_pControlBranchHUD);
	m_pControlBranchHUD = shNULL;
}

/**
* @brief Toggle
*/
void HUD::Toggle(void)
{
	if (ShGUIControl::IsShown(m_pControlBranchHUD))	{	ShGUIControl::Hide(m_pControlBranchHUD);	}
	else											{	ShGUIControl::Show(m_pControlBranchHUD);	}
}

/**
* @brief Show
*/
void HUD::Show(void)
{
	ShGUIControl::Show(m_pControlBranchHUD);
}

/**
* @brief Hide
*/
void HUD::Hide(void)
{
	ShGUIControl::Hide(m_pControlBranchHUD);
}