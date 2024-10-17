#include <random>
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() : pose({0, 0, 0}), emisionRange(10.0), 
limitRange(30.0), generationTimeInterval(0.1) {

}
ParticleSystem::ParticleSystem(Vector3 pos) : pose(pos), emisionRange(10.0), 
limitRange(30.0), generationTimeInterval(0.1) {

}
void ParticleSystem::integrate(double t) {
	lastTime += t;
	if (lastTime > generationTimeInterval) {
		generateParticle();
		lastTime = 0;
	}
	checkParticles(t);
}

void ParticleSystem::generateParticle() {
	Vector3 vel = UniformDistribution(-10.0, 10.0);

	Particle* p = new Particle(pose.p, vel, { 0, -10.0,0 }, 0.5, Damping);
	RegisterRenderItem(p->getRenderItem());
	particles.push_back(p);
}

Vector3 ParticleSystem::UniformDistribution(float min, float max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);

	Vector3 vec;
	vec.x = distrib(gen);
	vec.y = distrib(gen);
	vec.z = distrib(gen);

	return vec;
}
void ParticleSystem::checkParticles(double t) {
	for (auto it = particles.begin(); it != particles.end(); )
	{
		if (!(*it)->ItsAlive() || ((*it)->getTransform().p - pose.p).magnitude() > limitRange)
		{
			delete* it;
			it = particles.erase(it);
		}
		else
		{
			(*it)->integrate(t);
			++it;
		}
	}
}