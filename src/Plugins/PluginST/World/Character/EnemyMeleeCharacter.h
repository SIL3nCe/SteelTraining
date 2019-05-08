#ifndef EnemyMeleeCharacter_H
#define EnemyMeleeCharacter_H

#include "EnemyCharacter.h"

class EnemyMeleeCharacter : public EnemyCharacter
{

public:
	explicit		 EnemyMeleeCharacter	(void);
	virtual			~EnemyMeleeCharacter	(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Initialize				(const CShIdentifier & idCharacter, const CShIdentifier & levelIdentifier, b2World * pB2World, World * pSTWorld, const CShVector2 & vPosition);
	virtual void	Release					(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void	Update					(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual void	UpdateAnimations		(float dt) SH_ATTRIBUTE_OVERRIDE;
protected:
private:
	virtual void	Initialize				(b2World *, World *) SH_ATTRIBUTE_OVERRIDE {}
	virtual void	Initialize				(b2World *, World *, const CShVector2 &) SH_ATTRIBUTE_OVERRIDE {}

public:
protected:
private:
	CShVector2		m_vLastPlayerPosition;	///< @todo comment

};

#endif // EnemyMeleeCharacter_H
