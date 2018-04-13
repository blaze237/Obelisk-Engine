#pragma once
#include "PlaneObj.h"
#include "PhysicsCam.h"
class CullPlane : public PlaneObj
{
public:
	CullPlane(Vec3<float> pos, PhysicsCam& cam, int side = 1);
	virtual ~CullPlane();

	virtual void Update(long tCurrent);


private:
	PhysicsCam& cam;
	//Give +ve for on plus z, -ve for minus
	int side;

};

