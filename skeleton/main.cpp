#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>
#include <list>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include "Vector3D.h"
#include "ParticleSystem.h"
#include "GravityGenerator.h"
#include "WindGenerator.h";
#include "VortexGenerator.h"
#include "ExplosionGenerator.h"

#include <iostream>

std::string display_text = "This is a test";


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

ParticleSystem* particleGen1;
ParticleSystem* particleGen2;
ParticleSystem* particleGen3;
ParticleSystem* chainGen;

GravityGenerator* gg;
WindGenerator* wg;
VortexGenerator* vg;
ExplosionGenerator* eg;

WindGenerator* wgAux;

RenderItem* ejeX;
RenderItem* ejeY;
RenderItem* ejeZ;
RenderItem* origen;

const float distejes = 10.0f; // distancia de los ejes al origen
const float tamejes = 1.0f; // tamaño de los ejes

std::vector<Particle*> particulas;

const float Damping = 0.98f;
const float speed = 50.0f;
const float gravity = -9.8f;

void Ejes() {

	Vector3D posX = Vector3D(distejes, 0, 0);
	PxTransform* trsX = new PxTransform(posX.x, posX.y, posX.z);
	ejeX = new RenderItem(CreateShape(physx::PxSphereGeometry(tamejes)), trsX, {1, 0, 0, 1});

	Vector3D posY = Vector3D(0, distejes, 0);
	PxTransform* trsY = new PxTransform(posY.x, posY.y, posY.z);
	ejeY = new RenderItem(CreateShape(physx::PxSphereGeometry(tamejes)), trsY, {0, 1, 0, 1});

	Vector3D posZ = Vector3D(0, 0, distejes);
	PxTransform* trsZ = new PxTransform(posZ.x, posZ.y, posZ.z);
	ejeY = new RenderItem(CreateShape(physx::PxSphereGeometry(tamejes)), trsZ, { 0, 0, 1, 1 });

	Vector3D posO = Vector3D(0, 0, 0);
	PxTransform* trsO = new PxTransform(posO.x, posO.y, posO.z);
	ejeY = new RenderItem(CreateShape(physx::PxSphereGeometry(tamejes)), trsO, { 0, 0, 0, 1 });
}
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	////////////////////////////////////////

	Ejes();
	Vector3 position1 = { 0, 30, 0 };
	particleGen1 = new ParticleSystem(position1);
	particleGen1->staticTipe();
	Vector3 position2 = { -40, 30, 80 };
	particleGen2 = new ParticleSystem(position2);
	particleGen2->staticTipe();
	Vector3 position3 = { 80, 30, -40 };
	particleGen3 = new ParticleSystem(position3);
	particleGen3->staticTipe();

	/////////// PRACTICA 3

	gg = new GravityGenerator(position1);
	particleGen1->addForceGenerator(gg);

	wg = new WindGenerator(position1 + Vector3(0, -50, 0), {30, 30, 30}, {0, 0, 20});
	particleGen1->addForceGenerator(wg);

	vg = new VortexGenerator(position2, 60, 1);
	particleGen2->addForceGenerator(vg);

	eg = new ExplosionGenerator(position3, 30, 500);
	particleGen3->addForceGenerator(eg);

	/////////// PRACTICA 4

	chainGen = new ParticleSystem({ 0,0,0 });
	chainGen->addForceGenerator(gg);

	wgAux = new WindGenerator({ 0, 30,0}, { 30, 30, 30 }, { 0, 0, -20 });
	chainGen->addForceGenerator(wgAux);
	wgAux->setActive(false);

	chainGen->generateSpringDemo(5, { 0, 60, 0 });

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	
	for (auto it = particulas.begin(); it != particulas.end(); )
	{
		if ((*it)->getTransform().p.y <= 0) // condicion para que las particulas desaparezcan
		{
			delete *it;
			it = particulas.erase(it);
		}
		else
		{
			(*it)->integrate(t);
			++it;
		}
	}

	//particleGen1->integrate(t);
	//particleGen2->integrate(t);
	//particleGen3->integrate(t);
	chainGen->integrate(t);

	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	for (auto it = particulas.begin(); it != particulas.end(); )
	{
		delete *it;
	}

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	//case 'B': break;
	//case ' ':	break;
	case 'P':
	{
		Camera* cam = GetCamera();
		Vector3 offset = cam->getDir() * 5; // para que no esté pegado a la camara
		Particle* bala= new Particle(camera.p + offset, cam->getDir() * speed, {0,gravity,0}, 1.0, Damping);
		RegisterRenderItem(bala->getRenderItem());
		particulas.push_back(bala);
		break;
	}
	case 'E':
	{
		eg->interact();
		break;
	}
	case 'M':
	{
		chainGen->setSpringK(5);
		break;
	}
	case 'N':
	{
		chainGen->setSpringK(-5);
		break;
	}
	case 'V':
	{
		wgAux->turnActive();
	}
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}

int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}