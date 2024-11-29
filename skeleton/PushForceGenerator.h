#pragma once
#include "ForceGenerator.h"

class PushForceGenerator : public ForceGenerator
{
public:
	PushForceGenerator(Vector3 _pos, Vector3 _volume, double _liquid_density);
	~PushForceGenerator() = default;
	void addForce(Particle* particle, double t) override;
protected:
	double liquid_density;
	Particle* surface;
};

