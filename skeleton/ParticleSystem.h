#pragma once
#include "RenderUtils.hpp"
#include "ForceGenerator.h"
#include "RigidSolid.h"

class ParticleSystem
{
private:
	physx::PxScene* scene;
	physx::PxTransform pose;
	float emisionRange;
	float limitRange;
	std::vector<Particle*>* particles;
	std::vector<RigidSolid*>* rigidSolids;
	float generationTimeInterval;
	int particlesPerEmision;
	int maxEmisions = NULL;
	int numEmisions = 0;
	float lastTime = 0;
	float Damping = 0.98;
	const Vector3 gravity = {0,  -9.8 , 0};
	int setTipe = 4;

	std::vector<ForceGenerator*> forcegenerators;

public:
	ParticleSystem(physx::PxScene* scene);
	ParticleSystem(physx::PxScene* scene, Vector3 Pos);
	~ParticleSystem();

	Vector3 UniformDistributionVec(float nim, float max);
	float UniformDistribution(float min, float max);
	Vector3 NormalDistributionVec(float med, float destip);
	float NormalDistribution(float med, float destip);
	void integrate(double t);
	void checkParticles(double t);
	void checkForceGenerator(double t);
	void fireTipe();
	void explosionTipe();
	void staticTipe();
	void stripLineTipe(int num);
	void RainCubeTipe();
	void solidCubesTipe();
	void solidCapsulesTipe();

	void generateParticle(int t);
	void generateSpringDemo(unsigned int _num, Vector3 anchor_pos);

	void addForceGenerator(ForceGenerator* fg);
};

