#include "VortexGenerator.h"

VortexGenerator::VortexGenerator(Vector3 _pose, float _radio, float _intensity) :
	ForceGenerator::ForceGenerator(_pose, Vector3(_radio, _radio, _radio), {0,0,0})
{
    intensity = _intensity;
}

void VortexGenerator::addForce(Particle* particle, double t)
{
    Vector3 p = particle->getTransform().p;
    Vector3 c = pose.p;

    Vector3 diff = c - p;
    // esta es la cuerza que ponen en el enunciado 
    Vector3 finalforce = intensity * Vector3(-diff.z, 0, diff.x);
    // le voy a hacer una pequeña modificación para que no salgan hacia afuera
    float aux = 0.5;
    finalforce += Vector3(diff.x, 0, diff.z) * aux;
    particle->addForce(finalforce);
}

void VortexGenerator::addForce(RigidSolid* particle, double t)
{
    Vector3 p = particle->getTransform().p;
    Vector3 c = pose.p;

    Vector3 diff = c - p;
    // esta es la cuerza que ponen en el enunciado 
    Vector3 finalforce = intensity * Vector3(-diff.z, 0, diff.x);
    // le voy a hacer una pequeña modificación para que no salgan hacia afuera
    float aux = 0.5;
    finalforce += Vector3(diff.x, 0, diff.z) * aux;
    Vector3 torque(0.0f, 10.0f, 0.0f);

    particle->addTorque(torque);
    particle->addForce(finalforce);
}
