#include "WindGenerator.h"

WindGenerator::WindGenerator(Vector3 _pose, Vector3 _volume, Vector3 _force) :
	ForceGenerator::ForceGenerator(_pose, _volume, _force)
{

}

void WindGenerator::update()
{
	for (auto it = particles->begin(); it != particles->end(); ) {
		Particle* p = (*it);

		if (p == nullptr || !p->ItsAlive())
		{
			particles->erase(it);
		}
		else if () {

		}
	}
}

