#include "PhysicsCam.h"
#include "SceneManager.h"
#include "PhsyicsCamParent.h"

PhysicsCam::PhysicsCam(Vec3<float> eyePos, Vec3<float> viewDir,	Throwable& throwable)
	:FPSCamera(eyePos, viewDir), throwable(throwable)
{
}


PhysicsCam::~PhysicsCam()
{
}

void PhysicsCam::Update(long tCurrent)
{
	if (parent == nullptr)
		return;

	eyePos = parent->GetPos();
	FPSCamera::Update(tCurrent);

	//Check for attack input
	if (InputManager::Pressed(InputManager::MOUSE_LEFT))
		Fire();

}

void PhysicsCam::Fire()
{
	//Give the throwable velocity in direction of viewing
	Vec3<float> speed = n * throwSpeed;
	//Clamp y velocity, makes it easier to throw 
	//speed.y = MathHelp::Clamp(speed.y, 1.f, throwSpeed);;
	throwable.Activate(speed, eyePos);
}

void PhysicsCam::CheckMovement()
{
	//Grab current velocity
	Vec3<float> curVel = parent->GetVelocity();
	Vec3<float> startVel = curVel;

	//Velocity added by input is dependant upon camera axis in xz plane
	Vec3<float> u = this->u;
	u.y = 0;
	Vec3<float> n = this->n;
	n.y = 0;
	u.Normalise();
	n.Normalise();

	//Apply speed modifier
	if (InputManager::Pressed(InputManager::CTRL))
	{
		sprint = !sprint;
		if(sprint)
			movSpeed *= sprintMult;
		else
			movSpeed /= sprintMult;

	}


	//Forward
	if (InputManager::IsDown(inputU) && !InputManager::IsDown(inputD) && !InputManager::IsDown(inputR) && !InputManager::IsDown(inputL))
		curVel = n * movSpeed;
	//Backwards
	else if (InputManager::IsDown(inputD) && !InputManager::IsDown(inputU) && !InputManager::IsDown(inputR) && !InputManager::IsDown(inputL))
		curVel = n * -movSpeed;
	//Left
	else if (InputManager::IsDown(inputL) && !InputManager::IsDown(inputD) && !InputManager::IsDown(inputR) && !InputManager::IsDown(inputU))
		curVel = u * -movSpeed;
	//Left forward
	else if (InputManager::IsDown(inputL) && InputManager::IsDown(inputU))
	{
		//Give equal component of overal velocity in each movement direction
		float vComponent = sqrtf(movSpeed*movSpeed / 2);
		curVel = (u * -vComponent) + (n * vComponent);

	}
	//Left Backwards
	else if (InputManager::IsDown(inputL) && InputManager::IsDown(inputD))
	{
		//Give equal component of overal velocity in each movement direction
		float vComponent = sqrtf(movSpeed*movSpeed / 2);
		curVel = u * -vComponent + n * -vComponent;
	}
	//Right
	else if (InputManager::IsDown(inputR) && !InputManager::IsDown(inputD) && !InputManager::IsDown(inputL) && !InputManager::IsDown(inputU))
		curVel = u * movSpeed;
	//Right forwards
	else if (InputManager::IsDown(inputR) && InputManager::IsDown(inputU))
	{
		//Give equal component of overal velocity in each movement direction
		float vComponent = sqrtf(movSpeed*movSpeed / 2);
		curVel = u * vComponent + n * movSpeed;
	}
	//Right backwards
	else if (InputManager::IsDown(inputR) && InputManager::IsDown(inputD))
	{
		//Give equal component of overal velocity in each movement direction
		float vComponent = sqrtf(movSpeed*movSpeed / 2);
		curVel = u * vComponent + n * -vComponent;
	}
	

	//Re-add back on parents initial velocity that has been discared 
	curVel.y = startVel.y;

	//Jump
	if (InputManager::Pressed(inputJump) && parent->IsGrounded())
		curVel.y += jumpSpeed;


	//Apply velocity to parent object
	parent->SetVelocity(curVel);
}

void PhysicsCam::RegisterParent(std::shared_ptr<DisplayableObject> p)
{
	parent = p;
}
