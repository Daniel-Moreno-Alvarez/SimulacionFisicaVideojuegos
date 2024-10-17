#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acce, float Damping)
    : pose(Pos),  vel(Vel), acce(Acce), damping(Damping){
    renderItem = new RenderItem();
    renderItem->transform = &pose;
    renderItem->shape = CreateShape(physx::PxSphereGeometry(1.0));
    renderItem->color = { 1, 1, 0, 1 };
    

    Vector3 velr = vel;
    vel /= factor;

    acce = acce * pow(2, vel.magnitude()) / (pow(2, velr.magnitude()));

}

Particle::~Particle()
{
    DeregisterRenderItem(renderItem);
    delete renderItem;
}

void Particle::integrate(double t) {
    vel += acce * t;
    vel *= pow(damping, t);
    pose.p += vel * t;
}

RenderItem* Particle::getRenderItem()
{
    return renderItem;
}

physx::PxTransform Particle::getTransform()
{
    return pose;
}