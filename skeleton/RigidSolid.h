#pragma once
#include "RenderUtils.hpp"
enum FORM_RS {
	SPHERE_RS,
	CUBE_RS,
	CAPLSULE_RS
};

class RigidSolid
{
private:
	physx::PxRigidDynamic* solid = nullptr;
	physx::PxScene* gScene = nullptr;
	physx::PxShape* shape = nullptr;
	bool isAlive = true;
	RenderItem* renderItem = nullptr;
	float age = 0;
	float lifeLimit;
	Vector3 force_acum = Vector3(0,0,0);
public:
	RigidSolid(physx::PxScene* gScene, Vector3 Pos, Vector3 size, FORM_RS form = CUBE_RS);
	RigidSolid(physx::PxScene* gScene, Vector3 Pos, Vector3 Vel, Vector3 Acce, Vector3 size);
	~RigidSolid();

	void integrate(double t);
	bool ItsAlive();
	void SetLifeLimit(float LifeLimit);
	physx::PxTransform getTransform();
	void addForce(Vector3 force);
	void addAcceleration(Vector3 acce);
	void addTorque(Vector3 torque);
	Vector3 getVelocity();
	void SetColor(Vector4 color);
	void SetPosition(Vector3 pos);
	void SetMass(float _mass);
	void resetVel();
	void setMaterial(Vector3);
	float GetMass();
};

