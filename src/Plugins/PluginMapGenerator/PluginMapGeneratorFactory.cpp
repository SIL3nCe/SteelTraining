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

/**
* @brief TouchDownPluginMapGenerator
* @param iTouch
* @param positionX
* @param positionY
*/
PLUGIN_FACTORY_EXPORT void TouchDownPluginMapGenerator(int iTouch, float positionX, float positionY)
{
	g_pInstanceMapGenerator->OnTouchDown(iTouch, positionX, positionY);
}

/**
* @brief TouchUpPluginMapGenerator
* @param iTouch
* @param positionX
* @param positionY
*/
PLUGIN_FACTORY_EXPORT void TouchUpPluginMapGenerator(int iTouch, float positionX, float positionY)
{
	g_pInstanceMapGenerator->OnTouchUp(iTouch, positionX, positionY);
}

/**
* @brief TouchMovePluginMapGenerator
* @param iTouch
* @param positionX
* @param positionY
*/
PLUGIN_FACTORY_EXPORT void TouchMovePluginMapGenerator(int iTouch, float positionX, float positionY)
{
	g_pInstanceMapGenerator->OnTouchMove(iTouch, positionX, positionY);
}

}
