#pragma once
#include "RenderUtils.hpp"
#include "ForceGenerator.h"

class ParticleSystem
{
private:
	physx::PxTransform pose;
	float emisionRange;
	float limitRange;
	std::vector<Particle*>* particles;
	float generationTimeInterval;
	int particlesPerEmision;
	float lastTime = 0;
	float Damping = 0.98;
	const Vector3 gravity = {0,  -9.8 , 0};
	int setTipe = 0;

	std::vector<ForceGenerator*> forcegenerators;

public:
	ParticleSystem();
	ParticleSystem(Vector3 Pos);
	~ParticleSystem();
	Vector3 UniformDistributionVec(float nim, float max);
	float UniformDistribution(float min, float max);
	Vector3 NormalDistributionVec(float med, float destip);
	float NormalDistribution(float med, float destip);
	void integrate(double t);
	void fireTipe();
	void explosionTipe();
	void staticTipe();
	void generateParticle();
	void checkParticles(double t);

	void addForceGenerator(ForceGenerator* fg);
};

