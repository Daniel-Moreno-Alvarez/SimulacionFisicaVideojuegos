#pragma once
#include "ForceGenerator.h"
class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator(Vector3 _pose);
	~GravityGenerator() = default;
	void addForce(Particle* particle) override;
private:
	const Vector3 gravity = Vector3(0, -9.8f, 0);
};

