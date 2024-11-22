#pragma onceç
#include "ForceGenerator.h"
class WindGenerator : public ForceGenerator
{
public:
	WindGenerator(Vector3 _pose, Vector3 _volume, Vector3 _force);
	~WindGenerator() = default;
	void addForce(Particle* particle) override;
private:
	float k1 = 1.0;
};

