#include "VortexGenerator.h"

VortexGenerator::VortexGenerator(Vector3 _pose, float _radio, float _intensity) :
	ForceGenerator::ForceGenerator(_pose, Vector3(_radio, _radio, _radio), {0,0,0})
{
    intensity = _intensity;
}

void VortexGenerator::addForce(Particle* particle)
{
    Vector3 p = particle->getTransform().p;
    Vector3 c = pose.p;

    Vector3 diff = c - p;

    Vector3 finalforce = intensity * Vector3(-diff.z, 0, diff.x);
    particle->addForce(finalforce);
}
