#pragma once
#include "ForceGenerator.h"
class ExplosionGenerator :
    public ForceGenerator
{
public:
    ExplosionGenerator(Vector3 _pose, float _radio, float _intensity);
    ~ExplosionGenerator() = default;
    void update(double t) override;
    void addForce(Particle* particle, double t) override;
    void addForce(RigidSolid* particle, double t) override;
    void interact() override;
private:
    float intensity = 1.0;
    float radio;
    float lastTime;
    bool start;
    float finishTime;
};

