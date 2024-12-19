#include "GravityGenerator.h"

GravityGenerator::GravityGenerator(Vector3 _pose) : 
	ForceGenerator::ForceGenerator(_pose, gravity)
{ 
	force = gravity;
}

void GravityGenerator::addForce(Particle* particle, double t)
{
	// para que sea aceleracion independiente de la masa
	particle->addForce(force * particle->getMass());
}

void GravityGenerator::addForce(RigidSolid* particle, double t)
{
	particle->addAcceleration(force);
}
