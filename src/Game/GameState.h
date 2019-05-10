#pragma once

#include <ShSDK/ShSDK.h>

class GameState
{
public:
	//
	// Constructor/Destructor
	explicit				GameState					(void);
	virtual					~GameState					(void);

	//
	// Initialize/Release
	void					Initialize					(void);
	void					Release						(void);

	//
	// Activate/Deactivate
	void					Activate					(void);
	void					Deactivate					(void);

	//
	// Update
	void					Update						(float dt);

protected:
	//
	// Initialize/Release
	virtual void			InternalInitialize			(void) = 0;
	virtual void			InternalRelease				(void) = 0;

	//
	// Activate/Deactivate
	virtual void			InternalActivate			(void) = 0;
	virtual void			InternalDeactivate			(void) = 0;

	//
	// Update
	virtual void			InternalUpdate				(float dt) = 0;
private:

public:
protected:
	CShIdentifier			m_id;
private:
};