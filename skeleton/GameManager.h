#pragma once

#include "RenderUtils.hpp"
#include "Particle.h"
#include "RigidSolid.h"
#include "Vector3D.h"
#include "ParticleSystem.h"
#include "GravityGenerator.h"
#include "WindGenerator.h";
#include "VortexGenerator.h"
#include "ExplosionGenerator.h"
#include "ElasticStripFG.h"
#include "PushForceGenerator.h"
#include "Tirachinas.h"

const Vector4 _blue = { 0.0, 0.6, 1.0, 1};
const Vector4 _darckblue = { 0.0, 0.0, 0.1, 1 };
const Vector4 _red = { 0.8, 0.1, 0.1, 1 };
const Vector4 _white = { 0.8, 0.8, 0.8, 1 };
const Vector4 _black = { 0.0, 0.0, 0.0, 1 };

const float M_PI = 3.14159265358979323846;

class GameManager
{
private:
	enum TIRACHINAS_ST {SETROTATE, SETPOTENTIA, CANRESET};
	TIRACHINAS_ST currentState = SETROTATE;
	physx::PxScene* gScene;

	GravityGenerator* gg;
	GravityGenerator* ggBola;
	GravityGenerator* ggWin;
	WindGenerator* wg;
	ExplosionGenerator* eg;
	ParticleSystem* levelOneGen;
	ParticleSystem* particlesBall;
	ParticleSystem* winParticles;

	Camera* cam;

	Tirachinas* tirachinas;
	RigidSolid* bola;

	Vector3 positionBlocks = { 0, 20, 90 };
	Vector3 positionTirachinas = { 0, 30, -90 };
	float lenght = 20;
	Vector3 initialPosBola = positionTirachinas + Vector3(0,-lenght , -lenght);

	// ROTATION_ST
	float currAngle = 0;
	float minAngle = -30;
	float maxAngle = 30;
	float angularVel = 30;

	// PONTENTIA_ST
	float currDist = 0;
	float maxDist = 20;
	float potvel = 20;

	std::vector<Particle*> pointerBall;

	// Powerups
	bool explosion = true;
	bool wind = true;
	float currTimeWind = 0;
	float maxTimeWind = 2;

public:
	GameManager(physx::PxScene* scene, Camera* cam);
	~GameManager();
	void update(double t);
	void keyPress(unsigned char key);

	void CreatePointerBall();
	void updatePointerBall();
	void resetBall();
	Vector3 rotateAroundSpot(const Vector3& pos, const Vector3& spot, double t, float angle);
	Vector3 moveFromSpot(const Vector3& pos, const Vector3& spot, double t, float potvel);
};

