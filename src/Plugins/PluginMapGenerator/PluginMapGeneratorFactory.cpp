#include "PluginMapGeneratorFactory.h"

#include "PluginMapGenerator.h"

static PluginMapGenerator * g_pInstanceMapGenerator = shNULL;

extern "C"
{

/**
 * @brief RegisterPluginMapGenerator
 */
PLUGIN_FACTORY_EXPORT void RegisterPluginMapGenerator(void)
{
	if (!g_pInstanceMapGenerator)
	{
		g_pInstanceMapGenerator = new PluginMapGenerator();
	}

	ShApplication::RegisterPlugin(g_pInstanceMapGenerator);
}

/**
 * @brief UnRegisterPluginMapGenerator
 */
PLUGIN_FACTORY_EXPORT void UnRegisterPluginMapGenerator(void)
{
	ShApplication::UnRegisterPlugin(g_pInstanceMapGenerator);
}

/**
 * @brief GetPluginMapGenerator
 * @return
 */
PLUGIN_FACTORY_EXPORT PluginMapGenerator * GetPluginMapGenerator(void)
{
	return(g_pInstanceMapGenerator);
}

}