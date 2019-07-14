#pragma once

#include "ShSDK/ShSDK.h"
#include "../Object.h"

class World;

class b2World;
class b2Body;

struct ShEntity2;

class BaseCharacter : public Object
{
public:
	enum EAnimationState
	{
		animation_idle,
		animation_walk_top,
		animation_walk_bottom,
		animation_walk_right,
		animation_walk_left,
		//attack_xxx, etc

		animation_state_max
	};

	explicit			 BaseCharacter		(void);
	virtual				~BaseCharacter		(void);

	virtual	void		Initialize			(b2World * pB2World, World * pSTWorld);
	virtual	void		Release				(void);

	virtual void		Update				(float dt) SH_ATTRIBUTE_OVERRIDE;
	virtual void		UpdateAnimations	(float dt);

	virtual EObjectType	GetObjectType		(void) const SH_ATTRIBUTE_OVERRIDE;

	const CShVector3 &	GetEntityLocation	(void) const;

	bool				TakeDamage			(int iDamages);

	void				SetState			(EAnimationState eState);

	virtual void		Shoot				(void);

protected:
	virtual void		Die					(void) = 0;

protected:
	b2Body *			m_pBody;
	
	ShEntity2 *			m_pEntity;
	CShArray<CShArray<ShSprite *>> m_aSpriteList;

	World *				m_pWorld;

	int					m_iLifePoints;
	int					m_iMaxLifePoints;
	int					m_iInvulnerabilityTime;

	int					m_animCpt;
	EAnimationState		m_eCurrentAnimState;

	float				m_fAnimationDt;
	float				m_fAnimationSpeed;

};
