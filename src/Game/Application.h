#pragma once

class ShUser;

extern "C"
{
	void	OnPreInitialize		(void);
	void	OnPostInitialize	(void);
	void	OnPreUpdate			(float deltaTimeInMs);
	void	OnPostUpdate		(float deltaTimeInMs);
	void	OnPreRelease		(void);
	void	OnPostRelease		(void);
	void	OnActivate			(void);
	void	OnDeactivate		(bool & bAllowBackgroundUpdates, bool & bAllowBackgroundInputs);

	void	 OnLogin			(ShUser * pUser);
	void	OnLogout			(ShUser * pUser);
	
	void	OnTouchDown			(int iTouch, float positionX, float positionY);
	void	OnTouchUp			(int iTouch, float positionX, float positionY);
	void	OnTouchMove			(int iTouch, float positionX, float positionY);
}
