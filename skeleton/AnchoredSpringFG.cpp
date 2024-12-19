#include "AnchoredSpringFG.h"

AnchoredSpringFG::AnchoredSpringFG(double _k, double resting, const Vector3& _pos) :
	SpringForceGenerator(_k, resting)
{
	other = new Particle(_pos, { 0,0,0 }, { 0,0,0 }, 2.0, 1.0, CUBE);
	other->SetImmovable(true);
}

AnchoredSpringFG::~AnchoredSpringFG()
{
	delete other;
}