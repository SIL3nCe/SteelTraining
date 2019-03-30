#include "PluginST.h"

const CShIdentifier plugin_identifier("PluginSteelTraining");

/**
* @brief Constructor
*/
PluginST::PluginST(void)
: CShPlugin(plugin_identifier)
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
	m_world.Initialize(levelIdentifier);
}

/**
* @brief OnPlayStop
*/
/*virtual*/ void PluginST::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	m_world.Release();
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
