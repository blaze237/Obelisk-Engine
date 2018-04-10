#include "Plane.h"



Plane::Plane(Vec3<float> point, Vec3<float> normal)
	:point(point), normal(normal)
{
	D = -normal.DotProd(point);
}


Plane::~Plane()
{
}
