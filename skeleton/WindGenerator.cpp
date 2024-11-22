#include "WindGenerator.h"

WindGenerator::WindGenerator(Vector3 _pose, Vector3 _volume, Vector3 _velocity) :
	ForceGenerator::ForceGenerator(_pose, _volume, _velocity)
{

}

void WindGenerator::addForce(Particle* particle)
{
    Vector3 _force = k1 * (force - particle->getVelocity());
    particle->addForce(_force);
}

