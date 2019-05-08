#ifndef EnemyCharacter_H
#define EnemyCharacter_H

#include "BaseCharacter.h"

class EnemyCharacter : public BaseCharacter
{
public:
	enum EEnemyState
	{
		e_state_idle,
		e_state_attacking
	};

public:
	explicit		 EnemyCharacter	(void);
	virtual			~EnemyCharacter	(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Initialize			(b2World * pB2World, World * pSTWorld, const CShVector2 & vPosition);
	virtual void	Release				(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Update				(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual void	UpdateAnimations	(float dt) SH_ATTRIBUTE_OVERRIDE;
protected:
private:
	virtual void	Initialize			(b2World *, World *) SH_ATTRIBUTE_OVERRIDE {} // prevent from use

public:
protected:
	EEnemyState		m_eCurrentState;	///< Current state of the ennemy
private:

};

#endif // EnemyCharacter_H
