#pragma once
#include "Vec3.h"
class BoundingBox
{
public:
	BoundingBox(float width, float height, float depth);
	~BoundingBox();

	//Use for debugging
	void Render();

public:
	float width, height, depth;
};

