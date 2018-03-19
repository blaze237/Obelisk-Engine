#pragma once
#include "Vec3.h"
class BoundingBox
{
public:
	BoundingBox(int width, int height, int depth);
	~BoundingBox();

	//Use for debugging
	void Render();

private:
	float width, height, depth;
};

