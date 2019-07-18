#pragma once

#include "ShSDK/ShSDK.h"

enum class EObjectType : unsigned short;

namespace ShootFactory
{
	void GenerateLinearShoot(EObjectType eObjectType, const CShVector2 & vLocation, const CShVector2 & vDirection, int nbProjectile);
	void GenerateCircleShoot(EObjectType eObjectType, const CShVector2 & vLocation, int nbProjectile, float fRadius);
};
