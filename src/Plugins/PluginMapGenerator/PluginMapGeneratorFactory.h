#pragma once

#if defined(_WIN32)
#	if defined(PluginMapGenerator_Editor_EXPORTS)
#		define PLUGIN_FACTORY_EXPORT __declspec(dllexport)
#	else
#		define PLUGIN_FACTORY_EXPORT //__declspec(dllimport)
#	endif // PluginMapGenerator_Editor_EXPORTS
#else // defined(_WIN32)
#	define PLUGIN_FACTORY_EXPORT
#endif

class PluginMapGenerator;

extern "C"
{
	PLUGIN_FACTORY_EXPORT void					RegiMapGeneratorerPluginMapGenerator	(void);
	PLUGIN_FACTORY_EXPORT void					UnRegistererPluginMapGenerator			(void);
	PLUGIN_FACTORY_EXPORT PluginMapGenerator *	GetPluginMapGenerator					(void);

	PLUGIN_FACTORY_EXPORT void					TouchDownPluginMapGenerator				(int iTouch, float positionX, float positionY);
	PLUGIN_FACTORY_EXPORT void					TouchUpPluginMapGenerator				(int iTouch, float positionX, float positionY);
	PLUGIN_FACTORY_EXPORT void					TouchMovePluginMapGenerator				(int iTouch, float positionX, float positionY);
}
