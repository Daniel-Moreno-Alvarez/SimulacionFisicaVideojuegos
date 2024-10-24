#pragma once
#include "RenderUtils.hpp"
#include "Particle.h"

class ParticleSystem
{
private:
	physx::PxTransform pose;
	float emisionRange;
	float limitRange;
	std::vector<Particle*> particles;
	float generationTimeInterval;
	int particlesPerEmision;
	float lastTime = 0;
	float Damping = 0.98;
	const Vector3 gravity = {0,  -9.8 , 0};
	int setTipe = 0;

public:
	ParticleSystem();
	ParticleSystem(Vector3 Pos);
	Vector3 UniformDistribution(float nim, float max);
	Vector3 NormalDistribution(float med, float distip);
	void integrate(double t);
	void fireTipe();
	void explosionTipe();
	void generateParticle();
	void checkParticles(double t);

};

