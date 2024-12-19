#include "GameManager.h"
#include <cmath>

using namespace physx;

GameManager::GameManager(PxScene* scene, Camera* _cam) : gScene(scene), cam(_cam)
{
	Vector3 positionSuelo = positionBlocks;
	positionSuelo.y -= 3;
	levelOneGen = new ParticleSystem(gScene, positionBlocks);
	levelOneGen->LevelOne(5);

	particlesBall = new ParticleSystem(gScene, initialPosBola);
	particlesBall->fireTipe();

	gg = new GravityGenerator({0,0,0});
	ggBola = new GravityGenerator({0,0,0});
	ggWin = new GravityGenerator({ 0,0,0 });
	wg = new WindGenerator({ 0, -50, 0 }, { 0,0,0 }, { 0, 0, 500 });
	wg->setActive(false);
	eg = new ExplosionGenerator(positionTirachinas, 50, 5000);

	levelOneGen->addForceGenerator(gg);
	levelOneGen->addForceGenerator(eg);
	particlesBall->addForceGenerator(eg);

	PxRigidStatic* suelo = gScene->getPhysics().createRigidStatic(PxTransform(positionSuelo));
	PxShape* sueloShape = CreateShape(PxBoxGeometry(20, 1, 50));
	suelo->attachShape(*sueloShape);
	gScene->addActor(*suelo);
	RenderItem* renderItem1 = new RenderItem(sueloShape, suelo, _blue);

	tirachinas = new Tirachinas(50, lenght, positionTirachinas);
	bola = new RigidSolid(gScene, initialPosBola, {5,5,5}, SPHERE_RS);
	bola->SetMass(10);
	bola->SetColor(_red);
	tirachinas->addRigidSolid(bola);
	ggBola->addRigidSolid(bola);
	wg->addRigidSolid(bola);
	cam->setDir({1, 0, 0});
	cam->setPos({-200, 40, 0});

	CreatePointerBall();

	Vector3 winPosition = cam->getEye() + Vector3(20, 40, 0);
	winParticles = new ParticleSystem(scene, winPosition);
	winParticles->winParticles();
	winParticles->addForceGenerator(ggWin);
}

GameManager::~GameManager() {
	delete gg;
	delete wg;
	delete eg;
	delete ggBola;
	delete ggWin;
	delete winParticles;
	delete levelOneGen;
	delete tirachinas;
}

void GameManager::update(double t)
{
	if (levelOneGen)
	{
		levelOneGen->integrate(t);
	}
	if (particlesBall)
	{
		particlesBall->setPosition(bola->getTransform().p);
		particlesBall->integrate(t);
	}

	if (wg->isActive())
	{
		currTimeWind += t;
		if (currTimeWind >= maxTimeWind)
		{
			wg->setActive(false);
			currTimeWind = 0;
		}
	}

	switch (currentState)
	{
	case GameManager::SETROTATE:
	{
		Vector3 initpos = bola->getTransform().p;
		if ((angularVel > 0 && currAngle > maxAngle) || (angularVel < 0 && currAngle < minAngle))
		{
			angularVel *= -1;
		}
		bola->SetPosition(rotateAroundSpot(initpos, positionTirachinas, t, angularVel));
		updatePointerBall();
		break;
	}
	case GameManager::SETPOTENTIA:
	{
		Vector3 initpos = bola->getTransform().p;
		if ((currDist < 0 && potvel < 0) || (currDist > maxDist && potvel > 0))
		{
			potvel *= -1;
		}
		bola->SetPosition(moveFromSpot(initpos, positionTirachinas, t, potvel));
		updatePointerBall();
		break;
	}
	case GameManager::CANRESET:
	{
		tirachinas->update(t);
		ggBola->update(t);
		wg->update(t);
	}
		break;
	default:
		break;
	}

	if (levelOneGen->getNumParticles() <= 0)
	{
		winParticles->integrate(t);
	}
}

void GameManager::keyPress(unsigned char key)
{
	switch (toupper(key))
	{
	case 'P':
		switch (currentState)
		{
		case GameManager::SETROTATE:
			currentState = SETPOTENTIA;
			break;
		case GameManager::SETPOTENTIA:
			currentState = CANRESET;
			break;
		case GameManager::CANRESET:
			resetBall();
			currentState = SETROTATE;
			break;
		default:
			break;
		}
		break;
	case 'E':
		if (explosion && currentState == GameManager::CANRESET)
		{
			bola->resetVel();
			eg->setPosition(bola->getTransform().p);
			eg->interact();
			explosion = false;
		}
		break;
	case 'V':
		if (wind && currentState == GameManager::CANRESET)
		{
			wg->setActive(true);
			wind = false;
		}
		break;
	default:
		break;
	}
}

void GameManager::CreatePointerBall()
{
	for (int i = 0; i < 12; i++)
	{
		Particle* p = new Particle(1.0);
		pointerBall.push_back(p);
	}
}

void GameManager::updatePointerBall()
{
	int i = 0;
	for (Particle* p : pointerBall)
	{
		Vector3 _pos = (positionTirachinas - bola->getTransform().p) * 0.1 * i + positionTirachinas;
		p->SetPos(_pos);
		i++;
	}
}

void GameManager::resetBall()
{
	wg->setActive(false);
	currTimeWind = 0;
	explosion = true;
	wind = true;
	currDist = 0;
	currAngle = 0;
	bola->resetVel();
	bola->SetPosition(initialPosBola);
	tirachinas->setActive(true);
}

Vector3 GameManager::rotateAroundSpot(const Vector3& pos, const Vector3& spot, double t, float angle)
{
	float angleInRadians = angle * t * (M_PI / 180.0f);

	Vector3 translatedPos = pos - spot;

	// Realizar la rotación alrededor del eje YZ
	float cosTheta = std::cos(angleInRadians);
	float sinTheta = std::sin(angleInRadians);

	Vector3 rotatedPos;
	rotatedPos.x = translatedPos.x; // La rotación no afecta la componente X
	rotatedPos.y = translatedPos.y * cosTheta - translatedPos.z * sinTheta;
	rotatedPos.z = translatedPos.y * sinTheta + translatedPos.z * cosTheta;

	rotatedPos = rotatedPos + spot;

	currAngle += angle * t;

	return rotatedPos;
}

Vector3 GameManager::moveFromSpot(const Vector3& pos, const Vector3& spot, double t, float vel)
{
	Vector3 direction = (pos - spot).getNormalized();

	Vector3 movePos = direction * t * vel + pos;

	currDist += t * vel;

	return movePos;
}