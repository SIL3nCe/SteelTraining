#include "Extension.h"

#include <ShSDK/ShSDK.h>

//
// Include plugins
#include "../Plugins/Plugin/Plugin.h"

//
// Declare plugins
static Plugin plugin;

extern "C"
{
EXTENSION_EXPORT void ExtensionInitialize(void)
{
	//
	// Initialize plugins
	plugin.Initialize();

	// Register plugins here
	ShApplication::RegisterPlugin(&plugin);
}

EXTENSION_EXPORT void ExtensionRelease(void)
{
	// UnRegister plugins here
	ShApplication::UnRegisterPlugin(&plugin);

	// Release plugins here
	plugin.Release();
}
}
