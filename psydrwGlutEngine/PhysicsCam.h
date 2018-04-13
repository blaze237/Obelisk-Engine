#pragma once
#include "FPSCamera.h"
#include <memory>
#include "DisplayableObject.h"
#include <tuple>

class PhysicsCam :
	public FPSCamera
{
public:
	PhysicsCam(Vec3<float> eyePos, Vec3<float> viewDir);
	virtual ~PhysicsCam();

	virtual void Update(long tCurrent);
	virtual void CheckMovement();
	void RegisterParent(std::shared_ptr<DisplayableObject> p);

	virtual inline void SetEyePos(Vec3<float> v)
	{
		parent->SetPos(v);
	}

	virtual void OnCollide(std::string tag)
	{
	}
	
	void SetMovSpeed(float v)
	{
		movSpeed = v;
	}
	void SetJumpSpeed(float v)
	{
		jumpSpeed = v;
	}
private:

	bool sprint = false;
	std::shared_ptr<DisplayableObject> parent;
	float movSpeed = 0.5;
	float sprintMult = 2;
	float jumpSpeed = 2;
	char inputJump = ' ';
};

