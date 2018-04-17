#pragma once
#include "Vec3.h"
class Plane
{
public:
	Plane(Vec3<float> point, Vec3<float> normal);
	~Plane();


	inline float DistTo(Vec3<float> pos)
	{
		return normal.DotProd(pos) + D;
	}

private:
	Vec3<float> point;
	Vec3<float> normal;
	//From plane equation (Ax + By + Cz + D = 0)
	float D;
};

