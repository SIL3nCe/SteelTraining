#include "Game.h"

#include "MapGenerator/MapGeneratorTest.h"

Game * Game::m_pInstance = shNULL;

Game::Game(void)
{
	// ...
}

Game * Game::GetInstance(void)
{
	if (shNULL == m_pInstance)
	{
		m_pInstance = new Game();
	}

	return(m_pInstance);
}

void Game::Initialize(void)
{
	const CShIdentifier idLevel("level_test");
	if (!ShLevel::Load(idLevel))
	{
		SH_ASSERT_ALWAYS();
	}
}

void Game::Release(void)
{
//	GetPluginMapGenerator()->DestroyMapGenerator(m_pMapGenerator);
}

void Game::Update(float dt)
{
	float fFactor = 100.0f * dt;
	if (ShUser::HasTriggeredAction(ShUser::GetUser(0), CShIdentifier("right")))
	{
		ShCamera * pCamera = ShCamera::GetCamera2D();
		CShVector3 vDelta(1.0f * fFactor, 0.0f, 0.0f);
		ShCamera::Translate(pCamera, vDelta);
		ShCamera::SetTarget(pCamera, ShCamera::GetTarget(pCamera) + vDelta);
	}

	if (ShUser::HasTriggeredAction(ShUser::GetUser(0), CShIdentifier("left")))
	{
		ShCamera * pCamera = ShCamera::GetCamera2D();
		CShVector3 vDelta(-1.0f * fFactor, 0.0f, 0.0f);
		ShCamera::Translate(pCamera, vDelta);
		ShCamera::SetTarget(pCamera, ShCamera::GetTarget(pCamera) + vDelta);
	}
	
	if (ShUser::HasTriggeredAction(ShUser::GetUser(0), CShIdentifier("up")))
	{
		ShCamera * pCamera = ShCamera::GetCamera2D();
		CShVector3 vDelta(0.0f, 1.0f * fFactor, 0.0f);
		ShCamera::Translate(pCamera, vDelta);
		ShCamera::SetTarget(pCamera, ShCamera::GetTarget(pCamera) + vDelta);
	}
	
	if (ShUser::HasTriggeredAction(ShUser::GetUser(0), CShIdentifier("down")))
	{
		ShCamera * pCamera = ShCamera::GetCamera2D();
		CShVector3 vDelta(0.0f, -1.0f * fFactor, 0.0f);
		ShCamera::Translate(pCamera, vDelta);
		ShCamera::SetTarget(pCamera, ShCamera::GetTarget(pCamera) + vDelta);
	}
}