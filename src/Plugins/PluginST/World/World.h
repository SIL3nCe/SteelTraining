#pragma once

#include "ShSDK/ShSDK.h"

#include "ContactListener/ContactListener.h"
#include "InputManager.h"
#include "Character/PlayerCharacter.h"
#include "../../PluginMapGenerator/Map/Map2D.h"

#define SH_TO_B2 0.01f

static inline CShVector2 B2ToShine(b2Vec2 vec)
{
	float fFactor = 1 / SH_TO_B2;
	vec *= fFactor;
	return CShVector2(vec.x, vec.y);
}

static inline b2Vec2 ShineToB2(CShVector2 vec)
{
	vec *= SH_TO_B2;
	return b2Vec2(vec.m_x, vec.m_y);
}

class EnemyCharacter;
class PluginMapGenerator;
class MapGenerator;
class ObjectWall;

class World
{
public:

	explicit					 World				(void);
	virtual						~World				(void);

	void						Initialize			(const CShIdentifier & levelIdentifier);
	void						Release				(void);

	void						Update				(float dt);
	void						UpdateCamera		(float dt);

	const PluginInputManager & 	GetInputManager		(void);

	PlayerCharacter &			GetPlayerCharacter	(void);

	void						KillEnemy			(EnemyCharacter * pEnemy);

	void						MarkB2BodyToDestroy	(b2Body * pBody);

protected:
private:

	void						GenerateShape		(ShCollisionShape * pCollisionShape, const b2Vec2 & center, b2ChainShape & b2OutShape);
	void						GenerateShape		(ShDummyAABB2 * pObject, const b2Vec2 & center, b2PolygonShape & b2OutShape);

	//
	// Map control
	void						GenerateMap			(Map2D & map2D, int rowCount, int ColumnCount);
	ShSprite *					GetWallSprite		(int iRowPosition,  int iColumnPosition);

public:
protected:
private:
	CShIdentifier				m_levelIdentifier;

	b2World *					m_pbWorld;
	float						m_fFixedTimestepAccumulator;
	CShArray<b2Body *>			m_aBodiesToDestroy; // Delay box2d body release as it cannot be done during world step

	ContactListener				m_contactListener;

	CShArray<EnemyCharacter*>	m_apEnemyList;
	CShArray<ObjectWall *>		m_aWallList;

	PluginInputManager			m_inputManager;

	PlayerCharacter				m_playerCharacter;

	//
	// Map related
	PluginMapGenerator *	m_pMapGeneratorPlugin;
	MapGenerator *			m_pMapGenerator;
	Map2D					m_map;
};

