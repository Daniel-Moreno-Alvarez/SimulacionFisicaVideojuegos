#include "Tirachinas.h"

Tirachinas::Tirachinas(double _k, double resting, const Vector3& _pos) :
	AnchoredSpringFG(_k, resting, _pos)
{
}

void Tirachinas::addForce(Particle* particle, double t)
{
	if (active && getDistanceToOther(particle->getTransform().p).normalize() < resting_length)
	{
		setActive(false);
	}
	if (active)
	{
		SpringForceGenerator::addForce(particle, t);
	}
}

void Tirachinas::addForce(RigidSolid* particle, double t)
{
	if (active && getDistanceToOther(particle->getTransform().p).normalize() < resting_length)
	{
		setActive(false);
	}
	if (active)
	{
		SpringForceGenerator::addForce(particle, t);
	}
}
