#pragma once
#include "FPSCamera.h"
#include <memory>
#include "DisplayableObject.h"
#include <tuple>
#include "Throwable.h"

class PhysicsCam :
	public FPSCamera
{
public:
	PhysicsCam(Vec3<float> eyePos, Vec3<float> viewDir, Throwable& throwable);
	virtual ~PhysicsCam();

	virtual void Update(long tCurrent);
	void RegisterParent(std::shared_ptr<DisplayableObject> p);
	virtual void CheckMovement();
	virtual inline void SetEyePos(Vec3<float> v)
	{
		parent->SetPos(v);
	}

	virtual bool OnCollide(std::string tag)
	{
		//Ignore collisions with throwables
		if (!tag.compare("THROWABLE"))
			return true;

		return false;
	}
	
	void SetMovSpeed(float v)
	{
		movSpeed = v;
	}
	void SetJumpSpeed(float v)
	{
		jumpSpeed = v;
	}

protected:
	virtual void Fire();

private:

	//Throwable projectile object reference. Used to enable and disable the object and set its velocity
	Throwable& throwable;
	//What velocity to give to throwables in the direction of cam view dir
	float throwSpeed = 14;

	bool sprint = false;
	std::shared_ptr<DisplayableObject> parent;
	float movSpeed = 0.5;
	float sprintMult = 2;
	float jumpSpeed = 2;
	char inputJump = ' ';
};

