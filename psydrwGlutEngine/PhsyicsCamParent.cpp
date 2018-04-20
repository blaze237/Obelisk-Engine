#include "PhsyicsCamParent.h"



PhsyicsCamParent::PhsyicsCamParent(Vec3<float> pos, Vec3<float> bBoxSize, std::string tag, PhysicsCam &cam)
	:DisplayableObject(pos, bBoxSize, tag), cam(cam)
{
	kinematic = true;
	collidable = true;
	renderable = false;

	bBox.offset.y = -bBoxSize.y / 2;
	//renderCollider = true;
}


PhsyicsCamParent::~PhsyicsCamParent()
{
}


bool PhsyicsCamParent::OnCollide(std::string tag)
{
	return cam.OnCollide(tag);
}

