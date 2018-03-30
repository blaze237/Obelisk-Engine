#pragma once
#include "DisplayableObject.h"
#include "PhysicsCam.h"
#include <tuple>

class PhsyicsCamParent :
	public DisplayableObject
{
public:
	PhsyicsCamParent(Vec3<float> pos, Vec3<float> bBoxSize, std::string tag, PhysicsCam &cam);
	virtual ~PhsyicsCamParent();

	void OnCollide(std::string tag);

private:
	PhysicsCam &cam;
};

