#pragma once

struct ShUser;

extern "C"
{
	void	OnLogin				(ShUser * pUser);
	void	OnLogout			(ShUser * pUser);
	
	void	OnTouchDown			(int iTouch, float positionX, float positionY);
	void	OnTouchUp			(int iTouch, float positionX, float positionY);
	void	OnTouchMove			(int iTouch, float positionX, float positionY);
}
