#pragma once

#include <ShSDK/ShSDK.h>
#include <ShEntryPoint/ShEntryPoint.h>

#include <PluginST.h>
#include <PluginMapGeneratorFactory.h>

class Game
{
public:

	static Game * GetInstance(void);

	void Initialize();
	void Release();

	void Update(float dt);

private:
	explicit Game(void);

private:

	static Game *	m_pInstance;

	//
	// Map related
	MapGenerator *	m_pMapGenerator;
	Map2D			m_map;
};