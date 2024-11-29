#include "ElasticStripFG.h"

ElasticStripFG::ElasticStripFG(double _k, double resting, const Vector3& _pos) :
	AnchoredSpringFG(_k, resting, _pos)
{
	anchor = new AnchoredSpringFG(_k, resting, _pos);
}

ElasticStripFG::~ElasticStripFG()
{
	for (auto sfg : springsFG)
	{
		delete sfg;
	}
	springsFG.clear();

	delete anchor;
}

void ElasticStripFG::addParticle(Particle* particle)
{
	if (particles.empty()) {
		anchor->addParticle(particle);
	}
	else {
		Particle* anteriorPar = particles.back();
		SpringForceGenerator* f1 = new SpringForceGenerator(K, resting_length, anteriorPar);
		f1->addParticle(particle);
		springsFG.push_back(f1);

		SpringForceGenerator* f2 = new SpringForceGenerator(K, resting_length, particle);
		f2->addParticle(anteriorPar);
		springsFG.push_back(f2);
	}

	particles.push_back(particle);
}

void ElasticStripFG::update(double t)
{
	if (anchor)
	{
		anchor->update(t);
	}
	for (auto sfg : springsFG)
	{
		sfg->update(t);
	}
}

inline void ElasticStripFG::setK(double _k)
{
	for (auto sfg : springsFG)
	{
		sfg->setK(_k);
	}
}
