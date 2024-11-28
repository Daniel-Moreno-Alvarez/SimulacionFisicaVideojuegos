#include "Particle.h"
#include <cmath>

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acce, float size, float Damping, FORM form)
    : pose(Pos), vel(Vel), acce(Acce), damping(Damping) {
    renderItem = new RenderItem();
    renderItem->transform = &pose;
    switch (form)
    {
    case SPHERE:
        renderItem->shape = CreateShape(physx::PxSphereGeometry(size));
        break;
    case CUBE:
        renderItem->shape = CreateShape(physx::PxBoxGeometry(size, size, size));
        break;
    default:
        renderItem->shape = CreateShape(physx::PxSphereGeometry(size));
        break;
    }
    renderItem->color = { 1, 1, 0, 1 };
    RegisterRenderItem(renderItem);
    mass = 1.0;
    age = 0;
    lifeLimit = NULL;
}

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 Acce, float size, float Damping)
    : pose(Pos),  vel(Vel), acce(Acce), damping(Damping){
    renderItem = new RenderItem();
    renderItem->transform = &pose;
    renderItem->shape = CreateShape(physx::PxSphereGeometry(size));
    renderItem->color = { 1, 1, 0, 1 };
    RegisterRenderItem(renderItem);
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

void Particle::SetMass(float _mass)
{
    mass = _mass;
}

void Particle::integrate(double t) {
    age += t;

    vel += (acce + acce_acum) * t;
    vel *= pow(damping, t);
    if (!immovable){
        pose.p += vel * t;
    }

    acce_acum = {0, 0, 0};
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
    acce_acum += force / mass;
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
