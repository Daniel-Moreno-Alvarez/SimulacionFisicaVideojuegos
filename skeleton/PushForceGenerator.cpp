#include "PushForceGenerator.h"

PushForceGenerator::PushForceGenerator(Vector3 _pos, Vector3 _volume, double _liquid_density) :
	ForceGenerator(_pos, _volume, Vector3(0,0,0)),
	liquid_density(_liquid_density)
{

}

void PushForceGenerator::addForce(Particle* particle, double t)
{

}
