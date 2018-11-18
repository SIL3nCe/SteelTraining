#include "ExtensionST.h"

#include "ShSDK/ShSDK.h"

//
// Include plugins
#include "../Plugins/PluginST/PluginST.h"

typedef void(*register_fn)(void);
typedef void(*unregister_fn)(void);
typedef PluginST * (*get_instance_fn)(void);

static register_fn pRegisterST = shNULL;
static unregister_fn pUnRegisterST = shNULL;
static get_instance_fn pGetInstanceST = shNULL;

static FuncOnTouchDownPtr pOnTouchDownST = shNULL;
static FuncOnTouchUpPtr pOnTouchUpST = shNULL;
static FuncOnTouchMovePtr pOnTouchMoveST = shNULL;

#ifdef PLUGIN_ST_PATH
static const CShString strPluginSTFilePath(PLUGIN_ST_PATH);
#else
#	error "Plugin path not defined"
#endif

static CShDynamicLibrary pluginST_library(strPluginSTFilePath);

extern "C"
{

EXTENSION_ST_EXPORT void ExtensionInitialize(void)
{
	//
	// Load Library
	bool bInit = pluginST_library.Initialize();

	//
	// Get Functions
	if (bInit)
	{
		pRegisterST = (register_fn)pluginST_library.GetFunctionAddress(CShString("RegisterPluginST"));
		SH_ASSERT(shNULL != pRegisterST);

		pUnRegisterST = (register_fn)pluginST_library.GetFunctionAddress(CShString("UnRegisterPluginST"));
		SH_ASSERT(shNULL != pUnRegisterST);

		pGetInstanceST = (get_instance_fn)pluginST_library.GetFunctionAddress(CShString("GetPluginST"));
		SH_ASSERT(shNULL != pGetInstanceST);
	}

	//
	// Call factory (auto-register)
	if (shNULL != pRegisterST)
	{
		pRegisterST();
	}
}

EXTENSION_ST_EXPORT void ExtensionRelease(void)
{
	//
	// Call factory (auto-unregister)
	if (shNULL != pUnRegisterST)
	{
		pUnRegisterST();
	}

	//
	// Reset function pointers
	{
		pGetInstanceST = shNULL;
		pUnRegisterST = shNULL;
		pRegisterST = shNULL;
	}

	//
	// Unload Library
	pluginST_library.Release();
}

EXTENSION_ST_EXPORT void ExtensionOnPluginStarted(const CShIdentifier & levelIdentifier)
{
	if (shNULL != pRegisterST)
	{
		pOnTouchDownST = (FuncOnTouchDownPtr)pluginST_library.GetFunctionAddress(CShString("TouchDownPluginST"));
		SH_ASSERT(shNULL != pOnTouchDownST);

		pOnTouchUpST = (FuncOnTouchUpPtr)pluginST_library.GetFunctionAddress(CShString("TouchUpPluginST"));
		SH_ASSERT(shNULL != pOnTouchUpST);

		pOnTouchMoveST = (FuncOnTouchMovePtr)pluginST_library.GetFunctionAddress(CShString("TouchMovePluginST"));
		SH_ASSERT(shNULL != pOnTouchMoveST)

		ShInput::AddOnTouchDown(pOnTouchDownST);
		ShInput::AddOnTouchUp(pOnTouchUpST);
		ShInput::AddOnTouchMove(pOnTouchMoveST);
	}
}

EXTENSION_ST_EXPORT void ExtensionOnPluginStopped(const CShIdentifier & levelIdentifier)
{
	if (shNULL != pRegisterST)
	{
		ShInput::RemoveOnTouchDown(pOnTouchDownST);
		ShInput::RemoveOnTouchUp(pOnTouchUpST);
		ShInput::RemoveOnTouchMove(pOnTouchMoveST);

		pOnTouchDownST = shNULL;
		pOnTouchUpST = shNULL;
		pOnTouchMoveST = shNULL;
	}
}

}
