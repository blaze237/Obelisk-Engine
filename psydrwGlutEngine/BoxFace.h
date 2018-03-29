#pragma once
#include "Vec3.h"
#include <string>

struct BoxFace
{
	BoxFace(Vec3<float> A, Vec3<float> B, Vec3<float> C, std::string tag);


	//The normal to the face. Calculated on construction only
	Vec3<float> normal;
	//Face points A, B, C defined in counter-clockwise ordering
	Vec3<float> A, B, C;

	std::string tag;
};
