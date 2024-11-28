#pragma once
#include "ForceGenerator.h"
class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double _k, double _resting_length, Particle* _other);
	virtual ~SpringForceGenerator() {};
	virtual void addForce(Particle* particle, double t) override;
	virtual bool isSpring() const override { return true; }
	inline void setK(double _k) override { K += _k; };
protected:
	double K;
	double resting_length;
	Particle* other;
};

