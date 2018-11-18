#pragma once

#if defined(_WIN32)
#	if defined(Plugin_Editor_EXPORTS)
#		define PLUGIN_FACTORY_EXPORT __declspec(dllexport)
#	else
#		define PLUGIN_FACTORY_EXPORT //__declspec(dllimport)
#	endif // Plugin_Editor_EXPORTS
#else // defined(_WIN32)
#	define PLUGIN_FACTORY_EXPORT
#endif

class PluginST;

extern "C"
{
	PLUGIN_FACTORY_EXPORT void					RegisterPluginST		(void);
	PLUGIN_FACTORY_EXPORT void					UnRegisterPluginST		(void);
	PLUGIN_FACTORY_EXPORT PluginST *			GetPluginST				(void);
	
	PLUGIN_FACTORY_EXPORT void					TouchDownPluginST		(int iTouch, float positionX, float positionY);
	PLUGIN_FACTORY_EXPORT void					TouchUpPluginST			(int iTouch, float positionX, float positionY);
	PLUGIN_FACTORY_EXPORT void					TouchMovePluginST		(int iTouch, float positionX, float positionY);
}
