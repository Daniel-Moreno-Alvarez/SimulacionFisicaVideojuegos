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
	float lastTime = 0;
	float Damping = 0.98;
public:
	ParticleSystem();
	ParticleSystem(Vector3 Pos);
	Vector3 UniformDistribution(float nim, float max);
	void integrate(double t);
	void generateParticle();
	void checkParticles(double t);

};

