#pragma once

#include <ShSDK/ShSDK.h>

#include "GameState.h"

class GameStateGame : public GameState
{
	friend class GameStateManager;
public:
	//
	// Constructor/Destructor
	explicit				GameStateGame			(void);
	virtual					~GameStateGame			(void);

	//
	// Initialize/Release
	virtual void			InternalInitialize					(void) SH_ATTRIBUTE_OVERRIDE;
	virtual void			InternalRelease						(void) SH_ATTRIBUTE_OVERRIDE;

	//
	// Activate/Deactivate
	virtual void			InternalActivate					(void) SH_ATTRIBUTE_OVERRIDE;
	virtual void			InternalDeactivate					(void) SH_ATTRIBUTE_OVERRIDE;

	//
	// Update
	virtual void			InternalUpdate						(float dt) SH_ATTRIBUTE_OVERRIDE;

protected:
private:

public:
protected:
private:
};