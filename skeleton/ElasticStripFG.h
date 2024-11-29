#pragma once
#include "SpringForceGenerator.h"
#include "AnchoredSpringFG.h"

class ElasticStripFG : public AnchoredSpringFG
{
public:
	ElasticStripFG(double _k, double resting, const Vector3& _pos);
	~ElasticStripFG() override;
	virtual void addParticle(Particle* particle) override;
	virtual void update(double t) override;
	inline void setK(double _k) override;
protected:
	AnchoredSpringFG* anchor;
	std::vector<SpringForceGenerator*> springsFG;
};

