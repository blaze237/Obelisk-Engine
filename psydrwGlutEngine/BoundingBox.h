#pragma once
#include "Vec3.h"
#include <vector>
#include "BoxFace.h"
class BoundingBox
{
public:
	BoundingBox(float width, float height, float depth, const Vec3<float>& parentPos, const Vec3<float>& parentRot, Vec3<float>& parentScale, bool trigger = false);
	~BoundingBox();

	//Use for debugging
	void Render() const;

	//Calculate and return the position of each vertex based on parent position
	std::vector<Vec3<float>> GetIndicies(Vec3<float> posOffset = Vec3<float>(0,0,0), Vec3<float> rotOffset = Vec3<float>(0, 0, 0)) const;
	std::vector<BoxFace> GetFaces(Vec3<float> posOffset = Vec3<float>(0, 0, 0), Vec3<float> rotOffset = Vec3<float>(0,0,0)) const;


	bool IsTrigger() const
	{
		return trigger;
	}

	void SetTrigger(bool b)
	{
		trigger = b;
	}

public:
	float width, height, depth;
	//Keeps a reference to parent object position so that can use it to determine box wordlspace bounds at any given point.
	const Vec3<float>& parentPos;
	const Vec3<float>& parentRot;
	const Vec3<float>& parentScale;

	//Is this bounding box a trigger or a collider
	bool trigger;
};

