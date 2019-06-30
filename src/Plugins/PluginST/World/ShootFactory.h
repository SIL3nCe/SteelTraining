#pragma once

#include "ShSDK\ShSDK.h"

namespace ShootFactory
{
	void GenerateLinearShoot(const CShVector2 & vLocation, const CShVector2 & vDirection, int nbProjectile);
	void GenerateCircularShoot(const CShVector2 & vLocation, int nbProjectile, float fRadius);
};
