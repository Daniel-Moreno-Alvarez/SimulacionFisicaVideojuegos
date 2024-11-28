#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double _k, double _resting_length, Particle* _other) :
	ForceGenerator(),
	K(_k),
	resting_length(_resting_length),
	other(_other)
{
	maxForceMagnitude = 50;
}

void SpringForceGenerator::addForce(Particle* particle, double t)
{
	Vector3 relative_pos_vector = other->getTransform().p - particle->getTransform().p;

	const float length = relative_pos_vector.normalize();
	const float delta_x = length - resting_length;

	Vector3 finalForce = relative_pos_vector * delta_x * K;
	if (finalForce.magnitude() > maxForceMagnitude) { // Corrige la fuerza si es demasido alta
		finalForce = finalForce.getNormalized() * maxForceMagnitude;
	}
	particle->addForce(finalForce);
}
