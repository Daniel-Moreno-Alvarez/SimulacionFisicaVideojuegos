#pragma once
#include "Particle.h"
class ForceGenerator
{
public:
	ForceGenerator(Vector3 _pose, Vector3 _force);
	ForceGenerator(Vector3 _pose, Vector3 _volume, Vector3 _force);
	virtual ~ForceGenerator();
	void addParticle(Particle* particle);
	virtual void addForce(Particle* particle) = 0;
protected:
	std::vector<Particle*>* particles;
	physx::PxTransform pose;
	Vector3 force;
	Vector3 volume;
};

