#include <random>
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() : pose({ 0, 0, 0 }), emisionRange(0.0),
limitRange(30.0), generationTimeInterval(0.05), particlesPerEmision(1) {
	particles = new std::vector<Particle*>;
}
ParticleSystem::ParticleSystem(Vector3 pos) : pose(pos), emisionRange(0.0), 
limitRange(90.0), generationTimeInterval(0.05), particlesPerEmision(1) {
	particles = new std::vector<Particle*>;
}
ParticleSystem::~ParticleSystem()
{
	for (auto e : *particles)
	{
		delete e;
	}
	delete particles;

	for (auto e : forcegenerators)
	{
		delete e;
	}
	forcegenerators.clear();
}
void ParticleSystem::integrate(double t) {
	lastTime += t;
	if (lastTime > generationTimeInterval) {
		for (size_t i = 0; i < particlesPerEmision; i++)
		{
			generateParticle();
		}
		lastTime = 0;
	}
	checkParticles(t);
	for (auto gen : forcegenerators) {
		gen->update(t);
	}
}

void ParticleSystem::fireTipe()
{
	emisionRange = 3.0;
	limitRange = 50.0;
	generationTimeInterval = 0.01;
	particlesPerEmision = 1;
	setTipe = 1;
}

void ParticleSystem::explosionTipe()
{
	emisionRange = 0.0;
	limitRange = 30.0;
	generationTimeInterval = 1.0;
	particlesPerEmision = 30;
	setTipe = 2;
}

void ParticleSystem::staticTipe()
{
	emisionRange = 5.0;
	limitRange = 60.0;
	generationTimeInterval = 0.05;
	particlesPerEmision = 5;
	setTipe = 3;
}

void ParticleSystem::generateParticle() {
	Particle* p;
	switch (setTipe)
	{
	case 1: // fuego
	{
		Vector3 pos = pose.p + NormalDistributionVec(0, emisionRange);

		float y = NormalDistribution(8, 2);
		Vector3 vel = {0, y, 0};

		float tam = NormalDistribution(0.8, 0.2);
		p = new Particle(pos, vel, {0,0,0}, tam, Damping);

		p->SetLifeLimit(NormalDistribution(1, 0.5));
		p->SetColor({ 1,0,0,1 });
		RegisterRenderItem(p->getRenderItem());
		particles->push_back(p);

		break;
	}
	case 2: // exlposion
	{
		Vector3 vel = UniformDistributionVec(-1.0, 1.0);
		vel.normalize();
		vel *= 50;

		Vector3 acce = -vel;
		p = new Particle(pose.p, vel, acce, 2.0, Damping);

		p->SetLifeLimit(1.0);
		p->SetColor({ 0,1,1,1 });
		RegisterRenderItem(p->getRenderItem());
		particles->push_back(p);

		break;
	}
	case 3: // estaticas
	{
		Vector3 pos = pose.p + NormalDistributionVec(0, emisionRange);
		Vector3 vel = { 0,0,0 };
		Vector3 acce = { 0,0,0 };
		float mass = UniformDistribution(0.5, 2);
		float size = cbrt(mass);
		p = new Particle(pos, vel, acce, size, Damping);
		p->SetMass(mass);
		p->SetLifeLimit(10.0);
		p->SetColor({ 0,1,1,1 });
		RegisterRenderItem(p->getRenderItem());
		particles->push_back(p);

		break;
	}
	default: // chispas
	{
		Vector3 vel = { UniformDistribution(-2, 2), UniformDistribution(15, 20), UniformDistribution(-2, 2) };

		p = new Particle(pose.p, vel, Vector3(0,0,0), 0.5, Damping);
		p->SetLifeLimit(10.0);
		RegisterRenderItem(p->getRenderItem());
		particles->push_back(p);

		break;
	}
	}

	for (auto e : forcegenerators)
	{
		e->addParticle(p);
	}
}

Vector3 ParticleSystem::UniformDistributionVec(float min, float max) {

	Vector3 vec;
	vec.x = UniformDistribution(min, max);
	vec.y = UniformDistribution(min, max);
	vec.z = UniformDistribution(min, max);

	return vec;
}

float ParticleSystem::UniformDistribution(float min, float max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distrib(min, max);

	return distrib(gen);
}

Vector3 ParticleSystem::NormalDistributionVec(float med, float destip) {
	Vector3 vec;
	vec.x = NormalDistribution(med, destip);
	vec.y = NormalDistribution(med, destip);
	vec.z = NormalDistribution(med, destip);

	return vec;
}

float ParticleSystem::NormalDistribution(float med, float destip)
{
	if (destip == 0) {
		return med;
	}
	static std::mt19937 gen(std::random_device{}());
	std::normal_distribution<float> distrib(med, destip);

	return distrib(gen);
}

void ParticleSystem::checkParticles(double t) {
	for (auto it = particles->begin(); it != particles->end(); )
	{
		if (!(*it)->ItsAlive() || ((*it)->getTransform().p - pose.p).magnitude() > limitRange)
		{
			delete* it;
			it = particles->erase(it);
		}
		else
		{
			(*it)->integrate(t);
			++it;
		}
	}
}

void ParticleSystem::addForceGenerator(ForceGenerator* fg)
{
	forcegenerators.push_back(fg);
}
