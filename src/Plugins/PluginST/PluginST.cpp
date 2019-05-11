#include "PluginST.h"

const CShIdentifier g_idPlugin	("PluginSteelTraining");

/**
* @brief Constructor
*/
PluginST::PluginST(void)
: CShPlugin(g_idPlugin)
, m_world()
, m_hud()
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
	m_bRequestToStop = false;

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
	// ...
}

/**
* @brief OnPlayResume
*/
/*virtual*/ void PluginST::OnPlayResume(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPreUpdate
*/
/*virtual*/ void PluginST::OnPreUpdate(float dt)
{
	// ...
}

/**
* @brief OnPostUpdate
*/
/*virtual*/ void PluginST::OnPostUpdate(float dt)
{
	m_world.Update(dt);
}

/**
* @brief OnTouchDown
*/
void PluginST::OnTouchDown(int iTouch, float positionX, float positionY)
{
	// ...
}

/**
* @brief OnTouchUp
*/
void PluginST::OnTouchUp(int iTouch, float positionX, float positionY)
{
	// ...
}

/**
* @brief OnTouchMove
*/
void PluginST::OnTouchMove(int iTouch, float positionX, float positionY)
{
	// ...
}

/**
* @brief GetWorld
*/
World * PluginST::GetWorld(void)
{
	return &m_world;
}
