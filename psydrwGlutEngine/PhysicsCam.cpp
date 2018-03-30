#include "PhysicsCam.h"
#include "SceneManager.h"
#include "PhsyicsCamParent.h"

PhysicsCam::PhysicsCam(Vec3<float> eyePos, Vec3<float> viewDir)
	:FPSCamera(eyePos, viewDir)
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
}

void PhysicsCam::CheckMovement()
{
	Vec3<float> curVel = parent->GetVelocity();
	Vec3<float> startVel = curVel;

	Vec3<float> u = this->u;
	u.y = 0;
	Vec3<float> n = this->n;
	n.y = 0;

	u.Normalise();
	n.Normalise();


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
		curVel = (u * -movSpeed) + (n * movSpeed);
	//Left Backwards
	else if(InputManager::IsDown(inputL) && InputManager::IsDown(inputD))
		curVel = u * -movSpeed + n * -movSpeed;
	//Right
	else if (InputManager::IsDown(inputR) && !InputManager::IsDown(inputD) && !InputManager::IsDown(inputL) && !InputManager::IsDown(inputU))
		curVel = u * movSpeed;
	//Right forwards
	else if (InputManager::IsDown(inputR) && InputManager::IsDown(inputU))
		curVel = u * movSpeed + n * movSpeed;
	//Right backwards
	else if (InputManager::IsDown(inputR) && InputManager::IsDown(inputD))
		curVel = u * movSpeed + n * -movSpeed;

	//Re-add back on parents initial velocity that has been discared 
	curVel.y = startVel.y;

	//Jump
	if (InputManager::Pressed(inputJump) && parent->IsGrounded())
		curVel.y += jumpSpeed;

	if (InputManager::Released(inputL) || InputManager::Released(inputR))
		curVel.x = 0;
	if (InputManager::Released(inputU) || InputManager::Released(inputD))
		curVel.z = 0;

	parent->SetVelocity(curVel);
}

void PhysicsCam::RegisterParent(std::shared_ptr<DisplayableObject> p)
{
	parent = p;
}
