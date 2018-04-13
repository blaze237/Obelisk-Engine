#pragma once
#include "Cube.h"
#include "CullPlane.h"
class CullPlaneSwitch :
	public Cube
{
public:
	CullPlaneSwitch(Vec3<float> pos, std::string tag, CullPlane& cPlane);
	virtual ~CullPlaneSwitch();

	virtual void OnTrigger(std::string tag);
	virtual void Update(long tCurrent);

private:
	CullPlane& cPlane;
	long curTime = 0;
	long timeTriggered = 0;
};

