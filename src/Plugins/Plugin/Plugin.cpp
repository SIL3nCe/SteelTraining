#include "Plugin.h"

BEGIN_DERIVED_CLASS(Plugin, CShPlugin)
	// ...
END_CLASS()

Plugin::Plugin(void)
: CShPlugin(CShIdentifier("Example"))
{
	// ...
}

/*virtual*/ Plugin::~Plugin(void)
{
	// ...
}

void Plugin::Initialize(void)
{
	// ...
}

void Plugin::Release(void)
{
	// ...
}

/*virtual*/ void Plugin::OnPlayStart(const CShIdentifier & levelIdentifier)
{
	// ...
}

/*virtual*/ void Plugin::OnPlayStop(const CShIdentifier & levelIdentifier)
{
	// ...
}

/*virtual*/ void Plugin::OnPlayPause(const CShIdentifier & levelIdentifier)
{
	// ...
}

/*virtual*/ void Plugin::OnPlayResume(const CShIdentifier & levelIdentifier)
{
	// ...
}

/*virtual*/ void Plugin::OnPreUpdate(void)
{
	// ...
}

/*virtual*/ void Plugin::OnPostUpdate(float dt)
{
	// ...
}
