#include "ForceGenerator.h"

ForceGenerator::ForceGenerator() :
	pose(Vector3(0, 0, 0)),
	force(Vector3(0, 0, 0)),
	volume(Vector3(0, 0, 0))
{
}

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

void ForceGenerator::update(double t) {
	for (auto it = particles.begin(); it != particles.end();) {
		Particle* p = *it;

		if (p == nullptr || !p->ItsAlive()) {
			it = particles.erase(it);
		}
		else {
			if (isInVolume(p->getTransform().p) || volume == Vector3(0,0,0)) {
				addForce(p, t);
			}
			++it;
		}
	}
	for (auto it = rigidSolids.begin(); it != rigidSolids.end();) {
		RigidSolid* p = *it;

		if (p == nullptr || !p->ItsAlive()) {
			it = rigidSolids.erase(it);
		}
		else {
			if (isInVolume(p->getTransform().p) || volume == Vector3(0, 0, 0)) {
				addForce(p, t);
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

	for (auto p : rigidSolids) {
		delete p;
	}
	rigidSolids.clear();
}

void ForceGenerator::addParticle(Particle* particle)
{
	particles.push_back(particle);
}

void ForceGenerator::addRigidSolid(RigidSolid* sr)
{
	rigidSolids.push_back(sr);
}

bool ForceGenerator::isInVolume(Vector3 vec)
{
	if (volume == Vector3())
	{
		return false;
	}

	return 
		(vec.x >= pose.p.x - volume.x && vec.x <= pose.p.x + volume.x) &&
		(vec.y >= pose.p.y - volume.y && vec.y <= pose.p.y + volume.y) &&
		(vec.z >= pose.p.z - volume.z && vec.z <= pose.p.z + volume.z);
}
