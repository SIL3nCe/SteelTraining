#pragma once

#include <ShSDK/ShSDK.h>
#include <ShEntryPoint/ShEntryPoint.h>

#include <PluginST.h>
#include <PluginMapGeneratorFactory.h>

class Game
{
public:
	//
	// Singleton-related
	static Game *	GetInstance			(void);

	//
	// Initialize/Release
	void			Initialize			(void);
	void			Release				(void);

	//
	// Update
	void			Update				(float dt);

	//
	// Getters/Setters
	bool			IsInitialized		(void) const;

private:
	//
	// Constructor/Destructor
	explicit		Game				(void);
	virtual			~Game				(void);

private:
	//
	// Singleton-related
	static Game *	m_pInstance;

	//
	// Misc
	bool			m_bInitialized;
};