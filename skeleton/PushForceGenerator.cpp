#include "PushForceGenerator.h"

PushForceGenerator::PushForceGenerator(Vector3 _pos, Vector3 _volume, double _liquid_density) :
	ForceGenerator(_pos, _volume, Vector3(0,0,0)),
	liquid_density(_liquid_density)
{
	Vector3 auxPos = _pos + Vector3(0,volume.y,0);
	surface = new Particle(auxPos, { 0,0,0 }, { 0,0,0 }, {_volume.x,0.1,volume.z }, 0.98);
	surface->SetColor({0,1,1,1});
}

void PushForceGenerator::addForce(Particle* particle, double t)
{
	float h0 = volume.y;
	float h = particle->getTransform().p.y;
	Vector3 auxVol = particle->getVolume();
	float _height = auxVol.y;
	float _volume = auxVol.y * auxVol.x * auxVol.z;
	float immersed;
	if (h - h0 > _height * 0.5) {
		immersed = 0.0;
	}
	else if (h0 - h > _height * 0.5) {
		immersed = 1.0;
	}
	else {
		immersed = (h0 - h) / _height + 0.5;
	}
	Vector3 finalForce = { 0,0,0 };
	finalForce.y = liquid_density * _volume * immersed * 9.8;
	particle->addForce(finalForce);

}

void PushForceGenerator::addForce(RigidSolid* particle, double t)
{

}