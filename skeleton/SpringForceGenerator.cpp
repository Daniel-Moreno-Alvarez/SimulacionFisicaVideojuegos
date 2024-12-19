#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double _k, double _resting_length) :
	ForceGenerator(),
	K(_k),
	resting_length(_resting_length),
	other(nullptr),
	otherRS(nullptr)
{
}

SpringForceGenerator::SpringForceGenerator(double _k, double _resting_length, Particle* _other) :
	ForceGenerator(),
	K(_k),
	resting_length(_resting_length),
	other(_other),
	otherRS(nullptr)
{
}

SpringForceGenerator::SpringForceGenerator(double _k, double _resting_length, RigidSolid* _other) :
	ForceGenerator(),
	K(_k),
	resting_length(_resting_length),
	other(nullptr),
	otherRS(_other)
{

}

Vector3 SpringForceGenerator::getDistanceToOther(Vector3 vec)
{
	if (other != nullptr)
	{
		return other->getTransform().p - vec;
	}
	else if (otherRS != nullptr){
		return otherRS->getTransform().p - vec;
	}
	else {
		return Vector3();
	}
}

void SpringForceGenerator::addForce(Particle* particle, double t)
{
	Vector3 relative_pos_vector = getDistanceToOther(particle->getTransform().p);
	const float length = relative_pos_vector.normalize();
	const float delta_x = length - resting_length;

	Vector3 finalForce = relative_pos_vector * delta_x * K;
	particle->addForce(finalForce);
}

void SpringForceGenerator::addForce(RigidSolid* particle, double t)
{
	Vector3 relative_pos_vector = getDistanceToOther(particle->getTransform().p);

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - resting_length;

	Vector3 finalForce = relative_pos_vector * delta_x * K;
	particle->addForce(finalForce);
}