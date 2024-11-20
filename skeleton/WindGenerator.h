#pragma onceç
#include "ForceGenerator.h"
class WindGenerator : public ForceGenerator
{
public:
	WindGenerator(Vector3 _pose, Vector3 _volume, Vector3 _force);
	~WindGenerator() = default;
	void update() override;
	void addForce(Particle* particle) override;
	void quitForce(Particle* particle);
private:
	const Vector3 gravity = Vector3(0, -9.8f, 0);
};

