#include "PluginST.h"

const CShIdentifier g_idPlugin	("PluginSteelTraining");

/**
* @brief Constructor
*/
PluginST::PluginST(void)
: CShPlugin(g_idPlugin)
, m_world()
, m_hud()
, m_bPaused(false)
, m_bRequestToStop(false)
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ PluginST::~PluginST(void)
{
	// ...
}

/**
* @brief OnPlayStart
*/
/*virtual*/ void PluginST::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	//
	// Plugin states
	m_bPaused			= false;
	m_bRequestToStop	= false;

	//
	// World
	m_world.Initialize(levelIdentifier);

#if 0
	//
	// HUD
	m_hud.Initialize();
#endif // 0
}

/**
* @brief OnPlayStop
*/
/*virtual*/ void PluginST::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	SH_UNUSED(levelIdentifier);

	//
	// World
	m_world.Release();

#if 0
	//
	// HUD
	m_hud.Release();
#endif // 0
}

/**
* @brief OnPlayPause
*/
/*virtual*/ void PluginST::OnPlayPause(const CShIdentifier & levelIdentifier)
{
	SH_UNUSED(levelIdentifier);

	m_bPaused = true;
}

/**
* @brief OnPlayResume
*/
/*virtual*/ void PluginST::OnPlayResume(const CShIdentifier & levelIdentifier)
{
	SH_UNUSED(levelIdentifier);

	m_bPaused = false;
}

/**
* @brief OnPreUpdate
*/
/*virtual*/ void PluginST::OnPreUpdate(float dt)
{
	SH_UNUSED(dt);
}

/**
* @brief OnPostUpdate
*/
/*virtual*/ void PluginST::OnPostUpdate(float dt)
{
	if (!m_bPaused)
	{
		m_world.Update(dt);
	}
}

/**
* @brief OnTouchDown
*/
void PluginST::OnTouchDown(int iTouch, float positionX, float positionY)
{
	SH_UNUSED(iTouch);
	SH_UNUSED(positionX);
	SH_UNUSED(positionY);
}

/**
* @brief OnTouchUp
*/
void PluginST::OnTouchUp(int iTouch, float positionX, float positionY)
{
	SH_UNUSED(iTouch);
	SH_UNUSED(positionX);
	SH_UNUSED(positionY);
}

/**
* @brief OnTouchMove
*/
void PluginST::OnTouchMove(int iTouch, float positionX, float positionY)
{
	SH_UNUSED(iTouch);
	SH_UNUSED(positionX);
	SH_UNUSED(positionY);
}

/**
* @brief GetWorld
*/
World * PluginST::GetWorld(void)
{
	return &m_world;
}
