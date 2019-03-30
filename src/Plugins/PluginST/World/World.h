#pragma once

#include "ShSDK/ShSDK.h"

#include "InputManager.h"
#include "Character/PlayerCharacter.h"
#include "Object.h"
#include "../../PluginMapGenerator/PluginMapGenerator.h"
#include "../../PluginMapGenerator/MapGenerator/MapGenerator.h"
#include "../../PluginMapGenerator/MapGenerator/MapGeneratorTest.h"
#include "../../PluginMapGenerator/Map/Map.h"
#include "../../PluginMapGenerator/Map/Map2D.h"
#include "../../PluginMapGenerator/MapEntity/MapEntity.h"

#define SH_TO_B2 100

class World
{
public:

	explicit					 World			(void);
	virtual						~World			(void);

	void						Initialize		(const CShIdentifier & levelIdentifier);
	void						Release			(void);

	void						Update			(float dt);

	const PluginInputManager & 	GetInputManager	(void);
	

	static CShVector2			ShineToB2		(b2Vec2 vec);
	static b2Vec2				ShineToB2		(CShVector2 vec);

private:

	void						DatasetParser	(ShObject * pObject, ShDataSet * pDataSet);

	void						GenerateShape	(ShCollisionShape * pCollisionShape, const b2Vec2 & center, b2ChainShape & b2OutShape);
	void						GenerateShape	(ShDummyAABB2 * pObject, const b2Vec2 & center, b2PolygonShape & b2OutShape);

	//
	// Map control
	void						GenerateMap		(Map2D & map2D, int rowCount,  int ColumnCount);

private:
	
	CShIdentifier		m_levelIdentifier;

	b2World *			m_pbWorld;

	CShArray<Object*>	m_aObjectList;

	PluginInputManager	m_inputManager;

	PlayerCharacter		m_playerCharacter;

	//
	// Map related
	PluginMapGenerator *	m_pMapGeneratorPlugin;
	MapGenerator *			m_pMapGenerator;
	Map2D					m_map;
};

