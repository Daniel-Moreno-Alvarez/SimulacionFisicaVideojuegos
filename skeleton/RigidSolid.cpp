#include "RigidSolid.h"

using namespace physx;

RigidSolid::RigidSolid(PxScene* _gScene, Vector3 Pos, Vector3 size, FORM_RS form) : gScene(_gScene)
{
	switch (form)
	{
	case SPHERE_RS:
		shape = CreateShape(PxSphereGeometry(size.x));
		break;
	case CUBE_RS:
		shape = CreateShape(PxBoxGeometry(size));
		break;
	case CAPLSULE_RS:
		shape = CreateShape(PxCapsuleGeometry(size.x, size.y));
		break;
	default:
		shape = CreateShape(PxSphereGeometry(size.x));
		break;
	}
	solid = gScene->getPhysics().createRigidDynamic(PxTransform(Pos));
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
	shape = nullptr;
	solid = nullptr;
	/*if (solid != nullptr && gScene != nullptr) {
		gScene->removeActor(*solid);
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
	solid->addForce(force, PxForceMode::eFORCE);
}

void RigidSolid::addAcceleration(Vector3 acce)
{
	solid->addForce(acce, PxForceMode::eACCELERATION);
}

void RigidSolid::addTorque(Vector3 torque)
{
	solid->addTorque(torque);
}

Vector3 RigidSolid::getVelocity()
{
	return solid->getLinearVelocity();
}

void RigidSolid::SetColor(Vector4 color)
{
	renderItem->color = color;
}

void RigidSolid::SetPosition(Vector3 pos)
{
	solid->setGlobalPose(PxTransform(pos));
}

void RigidSolid::SetMass(float _mass)
{
	solid->setMass(_mass);
}

void RigidSolid::resetVel()
{
	solid->setLinearVelocity({0,0,0});
	solid->setAngularVelocity({ 0,0,0 });
}

void RigidSolid::setMaterial(Vector3 mat)
{
	// Obtener el material actual para liberarlo
	PxMaterial* currentMaterial;
	PxU32 materialCount = shape->getNbMaterials();
	if (materialCount > 0) {
		shape->getMaterials(&currentMaterial, materialCount);
		currentMaterial->release();
	}

	PxMaterial* newMaterial = gScene->getPhysics().createMaterial(mat.x, mat.y, mat.z);
	shape->setMaterials(&newMaterial, 1);
}

float RigidSolid::GetMass()
{
	return solid->getMass();
}