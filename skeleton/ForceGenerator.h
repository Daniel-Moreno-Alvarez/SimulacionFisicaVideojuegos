#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator();
	ForceGenerator(Vector3 _pose, Vector3 _force);
	ForceGenerator(Vector3 _pose, Vector3 _volume, Vector3 _force);
	virtual ~ForceGenerator();
	virtual void addParticle(Particle* particle);
	virtual void update(double t);
	virtual void addForce(Particle* particle, double t) = 0;
	bool isInVolume(Particle* p);
	virtual bool isSpring() const { return false; }
	virtual void setK(double _k) {};
	virtual void interact() {};
protected:
	std::vector<Particle*> particles;
	physx::PxTransform pose;
	Vector3 force;
	double maxForceMagnitude;
	Vector3 volume;
};

