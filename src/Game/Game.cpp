#include "Game.h"

/**
 * Called before engine initialization
 */
void ShEntryPoint::OnPreInitialize(void)
{

}

/**
 * Called after engine initialization
 */
void ShEntryPoint::OnPostInitialize(void)
{
	Plugin * pPlugin = new Plugin();
	ShApplication::RegisterPlugin(pPlugin);
}

/**
 * Called on each frame, before the engine update
 */
void ShEntryPoint::OnPreUpdate(float dt)
{
	// nothing here
}

/**
 * Called on each frame, after the engine update
 */
void ShEntryPoint::OnPostUpdate(float dt)
{
	// nothing here
}

/**
 * Called before the engine release
 */
void ShEntryPoint::OnPreRelease(void)
{
	// nothing here
}

/**
 * Called after the engine release
 */
void ShEntryPoint::OnPostRelease(void)
{
	// nothing here
}
