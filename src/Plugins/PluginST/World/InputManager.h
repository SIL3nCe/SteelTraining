#pragma once

struct ShUser;

class PluginInputManager
{
public:
	explicit	 PluginInputManager	(void);
	virtual		~PluginInputManager	(void);

	void		Initialize			(ShUser * pUser);
	void		Release				(void);

	void		Update				(void);

	bool		IsGoingUp			(void);
	bool		IsGoingDown			(void);
	bool		IsGoingLeft			(void);
	bool		IsGoingRight		(void);

private:
	ShUser *	m_pUser;

	bool		m_bUp;
	bool		m_bDown;
	bool		m_bLeft;
	bool		m_bRight;
};

