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
	Vector3 getVelocity();
	float getMass();
	void SetLifeLimit(float LifeLimit);
	void SetColor(Vector4 color);
	bool ItsAlive();
	void addForce(Vector3 force);
private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	Vector3 acce = Vector3(0, 0, 0);
	Vector3 acce_acum = Vector3(0,0,0);
	float damping;
	float mass;
	float factor = 10;
	float age = 0;
	float lifeLimit;
};

