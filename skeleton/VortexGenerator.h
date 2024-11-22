#pragma once
#include "ForceGenerator.h"

class VortexGenerator : public ForceGenerator
{
public:
    VortexGenerator(Vector3 _pose, float _radio, float _intensity);
    ~VortexGenerator() = default;
    virtual void addForce(Particle* particle) override;
private:
    float intensity = 1.0;
};

