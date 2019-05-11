#include "HUD.h"

const CShString		g_strGUIHUD			("hud");
const CShIdentifier	g_idGUIHUD			(g_strGUIHUD);
const CShIdentifier	g_idGUIContainerHUD	("container_hud");

/**
* @brief Constructor
*/
/*explicit*/ HUD::HUD(void)
: m_pControlBranchHUD(shNULL)
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
	m_pControlBranchHUD = static_cast<ShGUIControlBranch*>(ShGUIControl::GetElementById(g_idGUIContainerHUD, ShGUI::GetRootControl()));

	//
	// Set-up
}

/**
* @brief Release
*/
void HUD::Release(void)
{
	ShGUIControl::Destroy(m_pControlBranchHUD);
	m_pControlBranchHUD = shNULL;
}