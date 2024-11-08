#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acce, float size, float Damping)
    : pose(Pos),  vel(Vel), acce(Acce), damping(Damping){
    renderItem = new RenderItem();
    renderItem->transform = &pose;
    renderItem->shape = CreateShape(physx::PxSphereGeometry(size));
    renderItem->color = { 1, 1, 0, 1 };
    
    mass = 1.0;
    age = 0;
    lifeLimit = NULL;

}

Particle::~Particle()
{
    DeregisterRenderItem(renderItem);
    delete renderItem;
}

void Particle::SetLifeLimit(float LifeLimit) {
    lifeLimit = age + LifeLimit;
}

void Particle::SetColor(Vector4 color)
{
    renderItem->color = color;
}

void Particle::integrate(double t) {
    age += t;

    vel += acce * t;
    vel *= pow(damping, t);
    pose.p += vel * t;
}

bool Particle::ItsAlive() {
    if (lifeLimit != NULL) {
        if (age >= lifeLimit) {
            return false;
        }
        else return true;
    }
    else return true;
}

void Particle::addForce(Vector3 force)
{
    acce += force / mass;
}

RenderItem* Particle::getRenderItem()
{
    return renderItem;
}

physx::PxTransform Particle::getTransform()
{
    return pose;
}

Vector3 Particle::getVelocity()
{
    return vel;
}

float Particle::getMass()
{
    return mass;
}
