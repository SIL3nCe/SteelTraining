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

#include "PluginMapGenerator.h"

extern "C"
{
}
