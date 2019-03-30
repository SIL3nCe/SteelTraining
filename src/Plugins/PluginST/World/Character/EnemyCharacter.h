#ifndef EnemyCharacter_H
#define EnemyCharacter_H

#include "BaseCharacter.h"

class EnemyCharacter : public BaseCharacter
{
public:
	explicit		 EnemyCharacter	(void);
	virtual			~EnemyCharacter	(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Initialize			(b2World * pWorld) SH_ATTRIBUTE_OVERRIDE;
	virtual void	Release				(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Update				(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual void	UpdateAnimations	(float dt) SH_ATTRIBUTE_OVERRIDE;

};

#endif // EnemyCharacter_H
