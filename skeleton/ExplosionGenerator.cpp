#include "ExplosionGenerator.h"

ExplosionGenerator::ExplosionGenerator(Vector3 _pose, float _radio, float _intensity) :
    ForceGenerator::ForceGenerator(_pose, Vector3(_radio, _radio, _radio), { 0,0,0 }),
    intensity(_intensity),
    radio(_radio),
    lastTime(0.0),
    start(false),
    finishTime(1)
{
}

void ExplosionGenerator::update(double t)
{
    ForceGenerator::update(t);
    if (start) {
        lastTime += t;
        if (lastTime > finishTime) {
            start = false;
            lastTime = 0;
        }
    }
}

void ExplosionGenerator::addForce(Particle* particle, double t)
{
    if (start)
    {
        Vector3 particlePos = particle->getTransform().p;
        Vector3 center = pose.p;

        Vector3 direction = particlePos - center;
        float distance = direction.magnitude();

        // Solo se aplica la fuerza dependiendo del radio
        if (distance <= radio) {
            Vector3 finalForce = (intensity / (distance * distance)) * direction * pow(2.711828, t / lastTime);
            particle->addForce(finalForce);
        }
    }
}

void ExplosionGenerator::interact()
{
    start = true;
}
