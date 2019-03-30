#include "Application.h"
#include "Game.h"

#include "ShEntryPoint/ShEntryPoint.h"

#include "PluginFactory.h"
#include "PluginMapGeneratorFactory.h"

/**
* @brief SetupDisplayProperties
*/
void ShEntryPoint::SetupDisplayProperties(bool & bLandscape, bool & bEnable3D, bool & bEnableZ, bool & bUseSpecular, bool & bUsePointLights, bool & bUseShadow, int & width, int & height)
{
	bLandscape	= true;
	width		= 1280;
	height		= 720;

	bEnable3D		= false;
	bEnableZ		= false;
	bUseSpecular	= false;
	bUsePointLights	= false;
	bUseShadow		= false;
}

/**
 * @brief OnPreInitialize
 */
void ShEntryPoint::OnPreInitialize(void)
{
	ShInput::AddOnTouchDown(OnTouchDown);
	ShInput::AddOnTouchUp(OnTouchUp);
	ShInput::AddOnTouchMove(OnTouchMove);

	ShUser::RegisterLoginCallback(OnLogin);
	ShUser::RegisterLogoutCallback(OnLogout);
}

/**
 * @brief OnPostInitialize
 */
void ShEntryPoint::OnPostInitialize(void)
{
	RegisterPluginST();
	
	Game * pGame = Game::GetInstance();
	pGame->Initialize();
}

/**
 * @brief OnPreUpdate
 * @param dt
 */
void ShEntryPoint::OnPreUpdate(float dt)
{
	SH_UNUSED(dt);
}

/**
 * @brief OnPostUpdate
 * @param dt
 */
void ShEntryPoint::OnPostUpdate(float dt)
{
	Game * pGame = Game::GetInstance();
	pGame->Update(dt);
}

/**
 * @brief OnPreRelease
 */
void ShEntryPoint::OnPreRelease(void)
{
	Game * pGame = Game::GetInstance();
	pGame->Release();

	UnRegisterPluginST();
}

/**
 * @brief OnPostRelease
 */
void ShEntryPoint::OnPostRelease(void)
{
	// ...
}

/**
 * @brief OnActivate
 */
void ShEntryPoint::OnActivate(void)
{
	// ...
}

/**
 * @brief OnDeactivate
 * @param bAllowBackgroundUpdates
 * @param bAllowBackgroundInputs
 */
void ShEntryPoint::OnDeactivate(bool & bAllowBackgroundUpdates, bool & bAllowBackgroundInputs)
{
	bAllowBackgroundUpdates = false;
	bAllowBackgroundInputs = false;
}

/**
* @brief OnLogin
* @param pUser
*/
void OnLogin(ShUser * pUser)
{
	//Game::instance().login(pUser);
}

/**
* @brief OnLogout
* @param pUser
*/
void OnLogout(ShUser * pUser)
{
	//Game::instance().logout(pUser);
}

/**
* @brief OnTouchDown
* @param iTouch
* @param positionX
* @param positionY
*/
void OnTouchDown(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		//Game & game = Game::instance();
		//game.touchBegin(pos);
	}
}

/**
* @brief OnTouchUp
* @param iTouch
* @param positionX
* @param positionY
*/
void OnTouchUp(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		//Game & game = Game::instance();
		//game.touchEnd(pos);
	}
}

/**
* @brief OnTouchMove
* @param iTouch
* @param positionX
* @param positionY
*/
void OnTouchMove(int iTouch, float positionX, float positionY)
{
	if (0 == iTouch)
	{
		CShVector2 pos(positionX, positionY);
		//Game & game = Game::instance();
		//game.touchMove(pos);
	}
}