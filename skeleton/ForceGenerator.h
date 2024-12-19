#pragma once
#include "Particle.h"
#include "RigidSolid.h"

class ForceGenerator
{
public:
	ForceGenerator();
	ForceGenerator(Vector3 _pose, Vector3 _force);
	ForceGenerator(Vector3 _pose, Vector3 _volume, Vector3 _force);
	virtual ~ForceGenerator();
	virtual void addParticle(Particle* particle);
	virtual void addRigidSolid(RigidSolid* sr);
	virtual void update(double t);
	virtual void addForce(Particle* particle, double t) = 0;
	virtual void addForce(RigidSolid* particle, double t) {};
	bool isInVolume(Vector3 p);
	virtual bool isSpring() const { return false; }
	virtual void setK(double _k) {};
	virtual void setPosition(Vector3 _pos);
	virtual void interact() {};
	bool isActive() const { return active; };
	void setActive(bool _active) { active = _active; };
	void turnActive() { active = !active; }
protected:
	std::vector<Particle*> particles;
	std::vector<RigidSolid*> rigidSolids;
	physx::PxTransform pose;
	Vector3 force;
	double maxForceMagnitude;
	Vector3 volume;
	bool active = true;
};

