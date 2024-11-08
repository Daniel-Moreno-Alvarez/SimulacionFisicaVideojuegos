#include "ForceGenerator.h"

ForceGenerator::ForceGenerator(Vector3 _pose, Vector3 _force) :
	pose(_pose),
	force(_force),
	volume(Vector3())
{
	particles = new std::vector<Particle*>;
}

ForceGenerator::ForceGenerator(Vector3 _pose, Vector3 _volume, Vector3 _force) :
	pose(_pose), 
	volume(_volume), 
	force(_force)
{
	particles = new std::vector<Particle*>;
}

ForceGenerator::~ForceGenerator()
{
	delete particles;
	particles->clear();
}

void ForceGenerator::addParticle(Particle* particle)
{
	particles->push_back(particle);
}
