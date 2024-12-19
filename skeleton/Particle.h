#pragma once
#include "RenderUtils.hpp"
#include <iostream>
enum FORM {
	SPHERE,
	CUBE
};

class Particle
{
public:
	Particle(float size);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acce, Vector3 size, float Damping);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acce, float size, float Damping, FORM);
	Particle(Vector3 Pos, Vector3 Vel, Vector3 Acce, float size, float Damping);
	~Particle();

	void integrate(double t);
	RenderItem* getRenderItem();
	physx::PxTransform getTransform();
	Vector3 getVelocity();
	float getMass();
	Vector3 getVolume();
	void SetLifeLimit(float LifeLimit);
	void SetColor(Vector4 color);
	void SetMass(float mass);
	void SetPos(Vector3 _pos);
	void SetImmovable(bool _immovable) { immovable = _immovable; };
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
	bool immovable = false;
	Vector3 volume;
};

