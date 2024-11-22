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

    Vector3 diff = p - c;
    float distance = diff.magnitude();

    Vector3 finalforce = intensity * distance * Vector3(-(p.y - c.y), (p.z - c.z), -(p.x - c.x));
    particle->addForce(finalforce);
}
