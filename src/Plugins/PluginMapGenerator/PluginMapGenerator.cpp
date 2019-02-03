#include "PluginMapGenerator.h"

const CShIdentifier plugin_identifier("PluginMapGenerator");

/**
* @brief Constructor
*/
PluginMapGenerator::PluginMapGenerator(void)
: CShPlugin(plugin_identifier)
{
	// ...
}

/**
* @brief Destructor
*/
/*virtual*/ PluginMapGenerator::~PluginMapGenerator(void)
{
	// ...
}

/**
* @brief OnPlayStart
*/
/*virtual*/ void PluginMapGenerator::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPlayStop
*/
/*virtual*/ void PluginMapGenerator::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPlayPause
*/
/*virtual*/ void PluginMapGenerator::OnPlayPause(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPlayResume
*/
/*virtual*/ void PluginMapGenerator::OnPlayResume(const CShIdentifier & levelIdentifier)
{
	// ...
}

/**
* @brief OnPreUpdate
*/
/*virtual*/ void PluginMapGenerator::OnPreUpdate(float dt)
{
	// ...
}

/**
* @brief OnPostUpdate
*/
/*virtual*/ void PluginMapGenerator::OnPostUpdate(float dt)
{
	// ...
}

/**
* @brief OnTouchDown
*/
void PluginMapGenerator::OnTouchDown(int iTouch, float positionX, float positionY)
{
	// ...
}

/**
* @brief OnTouchUp
*/
void PluginMapGenerator::OnTouchUp(int iTouch, float positionX, float positionY)
{
	// ...
}

/**
* @brief OnTouchMove
*/
void PluginMapGenerator::OnTouchMove(int iTouch, float positionX, float positionY)
{
	// ...
}