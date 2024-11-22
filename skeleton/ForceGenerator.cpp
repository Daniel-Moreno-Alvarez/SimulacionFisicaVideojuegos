#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(Vector3 _pose, Vector3 _force) :
	pose(_pose),
	force(_force),
	volume(Vector3(0,0,0))
{
}

ForceGenerator::ForceGenerator(Vector3 _pose, Vector3 _volume, Vector3 _force) :
	pose(_pose), 
	volume(_volume), 
	force(_force)
{
	if (volume.x < 0){
		volume.x *= -1;
	}
	if (volume.y < 0) {
		volume.y *= -1;
	}
	if (volume.z < 0) {
		volume.z *= -1;
	}
}

void ForceGenerator::update() {
	for (auto it = particles.begin(); it != particles.end();) {
		Particle* p = *it;

		if (p == nullptr || !p->ItsAlive()) {
			it = particles.erase(it);
		}
		else {
			if (isInVolume(p) || volume == Vector3(0,0,0)) {
				addForce(p);
			}
			++it;
		}
	}
}

ForceGenerator::~ForceGenerator()
{
	for (auto p : particles) {
		delete p;
	}
	particles.clear();
}

void ForceGenerator::addParticle(Particle* particle)
{
	particles.push_back(particle);
}

bool ForceGenerator::isInVolume(Particle* particle)
{
	if (volume == Vector3())
	{
		return false;
	}

	Vector3 parpos = particle->getTransform().p;

	return 
		(parpos.x >= pose.p.x - volume.x && parpos.x <= pose.p.x + volume.x) &&
		(parpos.y >= pose.p.y - volume.y && parpos.y <= pose.p.y + volume.y) &&
		(parpos.z >= pose.p.z - volume.z && parpos.z <= pose.p.z + volume.z);
}
