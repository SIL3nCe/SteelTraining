#pragma once

class Projectile
{
public:

	enum class EProjectileType
	{
		classic,
		
		max
	};

	enum class EProjectileTrajectory
	{
		linear,
		
		max
	};

	//
	// Constructor / Destructor
								Projectile			(void);
	virtual						~Projectile			(void);

	void						Initialize			(EProjectileType eType, EProjectileTrajectory eTrajectory);

	//
	// Update
	void						Update				(float dt);

	//
	// Getters
	virtual EProjectileType		GetProjectileType	(void) const;

protected:
	EProjectileType m_eType;
	EProjectileTrajectory m_eTrajectory;
};
