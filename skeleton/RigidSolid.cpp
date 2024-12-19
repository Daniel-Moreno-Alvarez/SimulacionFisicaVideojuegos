#include "RigidSolid.h"

using namespace physx;


RigidSolid::RigidSolid(PxScene* _gScene, Vector3 Pos, Vector3 size) : gScene(_gScene)
{
	solid = gScene->getPhysics().createRigidDynamic(PxTransform(Pos));
	shape = CreateShape(PxBoxGeometry(size));
	solid->attachShape(*shape);
	PxRigidBodyExt::updateMassAndInertia(*solid, 0.15);
	gScene->addActor(*solid);
	renderItem = new RenderItem(shape, solid, { 0.0, 0.8, 0.8, 1 });
	RegisterRenderItem(renderItem);
	age = 0;
	lifeLimit = NULL;
}

RigidSolid::RigidSolid(PxScene* gScene, Vector3 Pos, Vector3 Vel, Vector3 Acce, Vector3 Size)
	:	RigidSolid(gScene, Pos, Size)
{
	solid->setLinearVelocity(Vel);
	solid->addForce(Acce);
}

RigidSolid::~RigidSolid()
{
	isAlive = false;
	gScene->removeActor(*solid);
	gScene = nullptr;
	/*if (solid != nullptr && gScene != nullptr) {
		solid->release();
		
		gScene = nullptr;
	}

	if (renderItem != nullptr) {
		DeregisterRenderItem(renderItem);
		delete renderItem;
		renderItem = nullptr;
	}*/
}

void RigidSolid::integrate(double t)
{
	age += t;
}

bool RigidSolid::ItsAlive() {
	if (!isAlive) return false;
	if (lifeLimit != NULL) {
		if (age >= lifeLimit) {
			isAlive = false;
			return false;
		}
		else return true;
	}
	else return true;
}

void RigidSolid::SetLifeLimit(float LifeLimit)
{
	lifeLimit = age + LifeLimit;
}

physx::PxTransform RigidSolid::getTransform()
{
	return solid->getGlobalPose();
}

void RigidSolid::addForce(Vector3 force)
{
	solid->addForce(force);
}

Vector3 RigidSolid::getVelocity()
{
	return solid->getLinearVelocity();
}
