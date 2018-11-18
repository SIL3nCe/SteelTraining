#include "PluginFactory.h"

#include "PluginST.h"

static PluginST * g_pInstanceST = shNULL;

extern "C"
{

/**
 * @brief RegisterPluginST
 */
PLUGIN_FACTORY_EXPORT void RegisterPluginST(void)
{
	if (!g_pInstanceST)
	{
		g_pInstanceST = new PluginST();
	}

	ShApplication::RegisterPlugin(g_pInstanceST);
}

/**
 * @brief UnRegisterPluginST
 */
PLUGIN_FACTORY_EXPORT void UnRegisterPluginST(void)
{
	ShApplication::UnRegisterPlugin(g_pInstanceST);
}

/**
 * @brief GetPluginST
 * @return
 */
PLUGIN_FACTORY_EXPORT PluginST * GetPluginST(void)
{
	return(g_pInstanceST);
}


/**
* @brief TouchDownPluginST
* @param iTouch
* @param positionX
* @param positionY
*/
PLUGIN_FACTORY_EXPORT void TouchDownPluginST(int iTouch, float positionX, float positionY)
{
	g_pInstanceST->OnTouchDown(iTouch, positionX, positionY);
}

/**
* @brief TouchUpPluginST
* @param iTouch
* @param positionX
* @param positionY
*/
PLUGIN_FACTORY_EXPORT void TouchUpPluginST(int iTouch, float positionX, float positionY)
{
	g_pInstanceST->OnTouchUp(iTouch, positionX, positionY);
}

/**
* @brief TouchMovePluginST
* @param iTouch
* @param positionX
* @param positionY
*/
PLUGIN_FACTORY_EXPORT void TouchMovePluginST(int iTouch, float positionX, float positionY)
{
	g_pInstanceST->OnTouchMove(iTouch, positionX, positionY);
}

}
