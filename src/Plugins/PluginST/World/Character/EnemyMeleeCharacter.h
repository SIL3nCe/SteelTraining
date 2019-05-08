#ifndef EnemyMeleeCharacter_H
#define EnemyMeleeCharacter_H

#include "EnemyCharacter.h"

class EnemyMeleeCharacter : public EnemyCharacter
{

public:
	explicit		 EnemyMeleeCharacter	(void);
	virtual			~EnemyMeleeCharacter	(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Initialize				(b2World * pB2World, World * pSTWorld) SH_ATTRIBUTE_OVERRIDE;
	virtual void	Release					(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Update					(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual void	UpdateAnimations		(float dt) SH_ATTRIBUTE_OVERRIDE;
protected:
private:

public:
protected:
private:
	CShVector2		m_vLastPlayerPosition;	///< @todo comment

};

#endif // EnemyMeleeCharacter_H
