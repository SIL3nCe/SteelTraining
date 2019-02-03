#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "Map/Map2D.h"
#include "MapGenerator/MapGenerator.h"

class PluginMapGenerator : public CShPlugin
{
public:
	explicit				PluginMapGenerator	(void);
	virtual					~PluginMapGenerator	(void);

	virtual	void			OnPlayStart			(const CShIdentifier & levelIdentifier) SH_ATTRIBUTE_OVERRIDE;
	virtual	void			OnPlayStop			(const CShIdentifier & levelIdentifier) SH_ATTRIBUTE_OVERRIDE;
	virtual	void			OnPlayPause			(const CShIdentifier & levelIdentifier) SH_ATTRIBUTE_OVERRIDE;
	virtual	void			OnPlayResume		(const CShIdentifier & levelIdentifier) SH_ATTRIBUTE_OVERRIDE;

	virtual	void			OnPreUpdate			(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual	void			OnPostUpdate		(float dt) SH_ATTRIBUTE_OVERRIDE;

	//
	// MapGenerators
	MapGenerator *			CreateMapGenerator	(EMapGeneratorType eType);
	bool					DestroyMapGenerator	(MapGenerator * pMapGenerator);

	//
	// Map Generation
	bool					GenerateMap			(MapGenerator * pMapGenerator, Map *& pMap, const CShIdentifier & idLevel);

private:



};
