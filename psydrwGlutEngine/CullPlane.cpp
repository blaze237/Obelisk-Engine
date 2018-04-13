#include "CullPlane.h"



CullPlane::CullPlane(Vec3<float> pos, PhysicsCam& cam, int side)
	:PlaneObj(pos, Texture2D("../textures/black.png"), "Cull Plane", 2), cam(cam)
{
	this->side = side / abs(side);
}


CullPlane::~CullPlane()
{
}

void CullPlane::Update(long tCurrent)
{
	if (abs(pos.z - cam.GetEyePos().z) != cam.GetFarDist() / 2 - 1)
	{
		pos.z = cam.GetEyePos().z + side*(cam.GetFarDist() / 2 - 1);
	}
}
