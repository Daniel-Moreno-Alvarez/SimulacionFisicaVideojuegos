#pragma once
#include "SpringForceGenerator.h"
class AnchoredSpringFG : public SpringForceGenerator
{
public:
	AnchoredSpringFG(double _k, double resting, const Vector3& _pos);
	~AnchoredSpringFG();
};

