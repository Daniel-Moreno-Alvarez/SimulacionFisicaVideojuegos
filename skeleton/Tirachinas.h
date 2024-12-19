#pragma once
#include "AnchoredSpringFG.h"

class Tirachinas : public AnchoredSpringFG
{
public:
	Tirachinas(double _k, double resting, const Vector3& _pos);
	~Tirachinas() = default;
	void addForce(Particle* particle, double t) override;
	void addForce(RigidSolid* particle, double t) override;
};

