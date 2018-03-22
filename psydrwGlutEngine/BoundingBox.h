#pragma once
#include "Vec3.h"
#include <vector>
class BoundingBox
{
public:
	BoundingBox(float width, float height, float depth, const Vec3<float>& parentPos, const Vec3<float>& parentRot);
	~BoundingBox();

	//Use for debugging
	void Render();

	//Calculate and return the position of each vertex based on parent position
	std::vector<Vec3<float>> GetIndicies();

public:
	float width, height, depth;
	//Keeps a reference to parent object position so that can use it to determine box wordlspace bounds at any given point.
	const Vec3<float>& parentPos;
	const Vec3<float>& parentRot;

};

