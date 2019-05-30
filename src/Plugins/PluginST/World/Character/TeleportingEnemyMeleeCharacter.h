#ifndef TELEPORTINGENEMYMELEECHARACTER_H
#define TELEPORTINGENEMYMELEECHARACTER_H

#include "EnemyMeleeCharacter.h"

class TeleportingEnemyMeleeCharacter : public EnemyMeleeCharacter
{
	enum ETPDirection
	{
		e_teleport_right,
		e_teleport_left,
		e_teleport_forward,
		e_teleport_none
	};
public:
	explicit				 TeleportingEnemyMeleeCharacter	(void);
	virtual					~TeleportingEnemyMeleeCharacter	(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void			Initialize						(const CShIdentifier & idCharacter, const CShIdentifier & levelIdentifier, b2World * pB2World, World * pSTWorld, const CShVector2 & vPosition) SH_ATTRIBUTE_OVERRIDE;
	virtual void			Release							(void) SH_ATTRIBUTE_OVERRIDE;

	virtual void			Update							(float dt) SH_ATTRIBUTE_OVERRIDE;

protected:
private:
	virtual void			Initialize						(b2World *, World *) SH_ATTRIBUTE_OVERRIDE {}
	virtual void			Initialize						(b2World *, World *, const CShVector2 &) SH_ATTRIBUTE_OVERRIDE {}

public:
protected:
private:
	float					m_fTPCooldown;					///< @todo
	float					m_fTPCooldownMax;				///< @todo
	int						m_iTPCurrentIndex;				///< @todo
	CShArray<ETPDirection>	m_aeTPDirectionsOrder;			///< @todo
};

#endif // TELEPORTINGENEMYMELEECHARACTER_H
