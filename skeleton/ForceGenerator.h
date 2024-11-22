#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator(Vector3 _pose, Vector3 _force);
	ForceGenerator(Vector3 _pose, Vector3 _volume, Vector3 _force);
	virtual ~ForceGenerator();
	virtual void addParticle(Particle* particle);
	virtual void update();
	virtual void addForce(Particle* particle) = 0;
	bool isInVolume(Particle* p);
protected:
	std::vector<Particle*> particles;
	physx::PxTransform pose;
	Vector3 force;
	Vector3 volume;
};

