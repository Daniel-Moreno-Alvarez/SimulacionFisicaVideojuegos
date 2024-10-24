#pragma once
#include "RenderUtils.hpp"
#include <iostream>
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acce, float size, float Damping);
	~Particle();

	void integrate(double t);
	RenderItem* getRenderItem();
	physx::PxTransform getTransform();
	void SetLifeLimit(float LifeLimit);
	void SetColor(Vector4 color);
	bool ItsAlive();
private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	Vector3 acce;
	float damping;
	float wheigt;
	float factor = 10;
	float age = 0;
	float lifeLimit;
};

