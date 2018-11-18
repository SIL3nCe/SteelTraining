#include "PluginST.h"

const CShIdentifier plugin_identifier("PluginSteelTraining");

PluginST::PluginST(void)
: CShPlugin(plugin_identifier)
{
	// ...
}

/*virtual*/ PluginST::~PluginST(void)
{
	// ...
}

void PluginST::Initialize(void)
{
	// ...
}

void PluginST::Release(void)
{
	// ...
}

/*virtual*/ void PluginST::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	// ...
}

/*virtual*/ void PluginST::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	// ...
}

/*virtual*/ void PluginST::OnPlayPause(const CShIdentifier & levelIdentifier)
{
	// ...
}

/*virtual*/ void PluginST::OnPlayResume(const CShIdentifier & levelIdentifier)
{
	// ...
}

/*virtual*/ void PluginST::OnPreUpdate(float dt)
{
	// ...
}

/*virtual*/ void PluginST::OnPostUpdate(float dt)
{
	// ...
}

void PluginST::OnTouchDown(int iTouch, float positionX, float positionY)
{
	// ...
}

void PluginST::OnTouchUp(int iTouch, float positionX, float positionY)
{
	// ...
}

void PluginST::OnTouchMove(int iTouch, float positionX, float positionY)
{
	// ...
}