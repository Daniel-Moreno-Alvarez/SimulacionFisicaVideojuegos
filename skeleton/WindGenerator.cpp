#include "WindGenerator.h"

WindGenerator::WindGenerator(Vector3 _pose, Vector3 _volume, Vector3 _force) :
	ForceGenerator::ForceGenerator(_pose, _volume, _force)
{

}

void WindGenerator::update()
{
    for (auto it = particles.begin(); it != particles.end();) {
        Particle* p = it->first;
        if (p == nullptr) {
            delete it->first;
            it = particles.erase(it);
        }
        else if (isInVolume(p) && !it->second) {
            addForce(it->first);
            it->second = true;
            ++it;
        }
        else if (!isInVolume(p) && it->second) {
            quitForce(it->first);
            it->second = false;
            ++it;
        }
        else {
            ++it;
        }
    }
}

void WindGenerator::addForce(Particle* particle)
{
    particle->addForce(force);
}

void WindGenerator::quitForce(Particle* particle)
{
    particle->addForce(-force);
}

