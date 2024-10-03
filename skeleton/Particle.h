#pragma once
#include "RenderUtils.hpp"
#include <iostream>
class Particle
{
public:
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acce);
	~Particle();

	void integrate(double t);
	RenderItem* getRenderItem();
	physx::PxTransform getTransform();

private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	Vector3 acce;

};

