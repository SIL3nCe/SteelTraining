#pragma once

#include <ShSDK/ShSDK.h>
#include <ShEntryPoint/ShEntryPoint.h>

#include <PluginST.h>
#include <PluginMapGeneratorFactory.h>

class Game
{
public:

	static Game * GetInstance(void);

	void Initialize(void);
	void Release(void);

	void Update(float dt);

private:
	explicit Game(void);

private:

	static Game *	m_pInstance;
};