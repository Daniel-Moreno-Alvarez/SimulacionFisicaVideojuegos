#pragma once
#include "RenderUtils.hpp"

class RigidSolid
{
private:
	physx::PxRigidDynamic* solid = nullptr;
	physx::PxScene* gScene = nullptr;
	physx::PxShape* shape = nullptr;
	Vector3 vel;
	Vector3 acce;
	bool isAlive = true;
	RenderItem* renderItem = nullptr;
	float age = 0;
	float lifeLimit;
	Vector3 force_acum = Vector3(0,0,0);
public:
	RigidSolid(physx::PxScene* gScene, Vector3 Pos, Vector3 size);
	RigidSolid(physx::PxScene* gScene, Vector3 Pos, Vector3 Vel, Vector3 Acce, Vector3 size);
	~RigidSolid();

	void integrate(double t);
	bool ItsAlive();
	void SetLifeLimit(float LifeLimit);
	physx::PxTransform getTransform();
	void addForce(Vector3 force);
	Vector3 getVelocity();
};

