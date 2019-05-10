#pragma once

#include "ShSDK/ShSDK.h"
#include "ShEngineExt/ShEngineExt.h"

#include "World/World.h"

class PluginST : public CShPlugin
{
public:
							PluginST			(void);
	virtual					~PluginST			(void);

	virtual	void			OnPlayStart			(const CShIdentifier & levelIdentifier) SH_ATTRIBUTE_OVERRIDE;
	virtual	void			OnPlayStop			(const CShIdentifier & levelIdentifier) SH_ATTRIBUTE_OVERRIDE;
	virtual	void			OnPlayPause			(const CShIdentifier & levelIdentifier) SH_ATTRIBUTE_OVERRIDE;
	virtual	void			OnPlayResume		(const CShIdentifier & levelIdentifier) SH_ATTRIBUTE_OVERRIDE;

	virtual	void			OnPreUpdate			(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual	void			OnPostUpdate		(float dt) SH_ATTRIBUTE_OVERRIDE;
	
	//
	// Touch Events
	void					OnTouchDown			(int iTouch, float positionX, float positionY);
	void					OnTouchUp			(int iTouch, float positionX, float positionY);
	void					OnTouchMove			(int iTouch, float positionX, float positionY);

	World *					GetWorld			(void);

private:

	World		m_world;

public:

	bool		m_bRequestToStop;
};
